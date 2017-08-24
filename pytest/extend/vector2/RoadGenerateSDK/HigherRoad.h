/*-----------------------------------------------------------------------------

    ���ߣ����� 2016/05/20
    ��ע��
    ��ˣ�

-----------------------------------------------------------------------------*/
#pragma once

#include "GDataStructure.h"
#include "SDKInterface.h"

typedef enum 
{
    Adjace_none        =0x00,        //�ö�û���κ�������ϵ
    Adjace_head        =0x01,        //�öκ�·ͷ������
    Adjace_tail        =0x02,        //�öκ�·β������
    Adjace_all        =0x03,        //�öκ�ͷβ������

}SegmentAdjacencyFlag;

/**
* @brief
* @author ningning.gn
* @remark
**/
class ROAD_EXPORT HigherRoad
{
private:
    GShapeRoadPtr m_RoadQuote;
    RoadRange m_AvalibleRange;    // ���յĺϷ�����
    RoadItemRange m_InitRange;
    AnGeoVector<RoadItemRange> m_GapArr;    // ȱ��, ��������, ���Ǳ����·���·�Ĳ���
    Gint32 m_Flag;

    // ��ͼ�õĲ�����
    GEO::VectorArray3 m_SampleWhole;
    AnGeoVector<GEO::VectorArray3> m_SampleArr;

public:
    SegmentAdjacencyFlag m_AdjaceFlag;    //�͵�·�����Ĺ�ϵ
    Gint32    m_headAdjaceIndex;
    Gint32    m_tailAdjaceIndex;

public:
    HigherRoad();

    //========================= ���㲿�� =========================//

    inline Gint32 GetFlag(){ return m_Flag; }
    inline void SetFlag(Gint32 value){ m_Flag = value; }
    inline void SetRoadQuote(Utility_In GShapeRoadPtr A_Road) { m_RoadQuote = A_Road; }
    void CalcAvaliableRange(Utility_InOut AnGeoList<RoadBreakPoint>& A_RangePt, Gbool A_AvoidJunction);

    void InsertGap(Utility_In RoadBreakPoint& A_Start, Utility_In RoadBreakPoint& A_End);
    void SplitByGaps();
    void RemoveTinyRange(Utility_In Gdouble A_MinLength);

    void OnFinish();

    inline AnGeoVector<GEO::VectorArray3>& GetSampleArray()  { return m_SampleArr; }

    //========================= ���Ի�ȡ =========================//

    inline GShapeRoadPtr GetRoadQuote() const { return m_RoadQuote; }

    Gint32 GetRangeCount();
    const RoadItemRange& GetRangeAt(Utility_In Gint32 A_Index) const;

#if ROAD_CANVAS
    void Draw(Utility_In GRAPHIC::CanvasPtr A_Canvas);
#endif

public:
    SegmentAdjacencyFlag GetAdjaceFlag(){return m_AdjaceFlag;}

protected:
    void        CalculateAdjaceRelation();

};//end HigherRoad
typedef HigherRoad* HigherRoadPtr;

class RoadHeightOperator
{
public:
    virtual Gbool operator () (Utility_In Gdouble a, Utility_In Gdouble b) const = 0;

};//end RoadHeightOperator

class RoadHeightOperatorHigher : public RoadHeightOperator
{
public:
    virtual Gbool operator () (Utility_In Gdouble a, Utility_In Gdouble b) const
    {
        return a > b;
    }

};//end RoadHeightOperatorHigher

class RoadHeightOperatorLower : public RoadHeightOperator
{
public:
    virtual Gbool operator () (Utility_In Gdouble a, Utility_In Gdouble b) const
    {
        return a < b;
    }

};//end RoadHeightOperatorLower

enum RoadFilterFlag
{
    eAdd,
    eIgnor,
    eCalc
};

/**
* @brief
* @author ningning.gn
* @remark
**/
class ROAD_EXPORT HigherRoadContainer
{
protected:
    Gbool m_Show;
    GRoadLinkPtr m_RoadLink;
    GDS::ObjectArray<HigherRoad> m_HigherRoadArr;

    void AddHigherRoad(GShapeRoadPtr A_Road,
        AnGeoList<RoadBreakPoint>& A_BreakPointList, Gbool A_AvoidJunc);
    RoadBreakPoint TransformBreakPointToBaidu(Utility_In RoadBreakPoint& A_Start,
        Utility_In RoadBreakPoint& A_End, Utility_In RoadBreakPoint& A_CurPos);
    void CalcHigherRoad(Utility_In Gdouble A_Height, Utility_In Gbool A_AvoidJunc, 
        Utility_In RoadHeightOperator& A_Operator);

    void ModifyOffset(Utility_In RoadBreakPoint& A_SubRoadStart, Utility_In RoadBreakPoint& A_SubRoadEnd,
        Utility_In RoadBreakPoint& A_RangeStart, Utility_In RoadBreakPoint& A_RangeEnd,
        Utility_Out RoadBreakPoint& A_RangeResultStart, Utility_Out RoadBreakPoint& A_RangeResultEnd, Utility_Out Gbool& A_Empty);

    virtual RoadFilterFlag CalcHigherRoadFilter(Utility_In GShapeRoadPtr A_Road) = 0;

public:
    HigherRoadContainer(Utility_In GRoadLinkPtr A_RoadLink) : m_Show(true), m_RoadLink(A_RoadLink) {}
    void Show(Utility_In Gbool A_Show) { m_Show = A_Show; }
    void Clear();

#if ROAD_CANVAS
    void Draw(Utility_In GRAPHIC::CanvasPtr A_Canvas);
#endif

    Gint32 GetRoadCount() const { return m_HigherRoadArr.GetSize(); }
    HigherRoadPtr GetRoadAt(Utility_In Gint32 A_Index) { return m_HigherRoadArr[A_Index]; }

};//end HigherRoadContainer

/**
* @brief ���ɲ���
* @author ningning.gn
* @remark
**/
class ROAD_EXPORT BridgePierGenParam
{
    friend class BridgePier;

protected:
    Gbool m_AvoidJunction;
    Gbool m_LowerAvoidHigher;
    Gdouble m_PierAvoidDistance;
    Gdouble m_MinLength;
    Gdouble m_BridgeHeight;
    Gdouble m_PierSpan;

public:
    BridgePierGenParam() :
        m_AvoidJunction(false),
        m_LowerAvoidHigher(true),
        m_PierAvoidDistance(10.0),
        m_MinLength(10.0),
        m_BridgeHeight(2.0),
        m_PierSpan(0.0)
    {}

    inline void SetAvoidJunction(Utility_In Gbool A_Avoid) { m_AvoidJunction = A_Avoid; }
    inline void SetPierAvoidDis(Utility_In Gdouble A_Tol) { m_PierAvoidDistance = A_Tol; }
    inline void SetMinLength(Utility_In Gdouble A_Length) { m_MinLength = A_Length; }
    inline void SetBridgeHeight(Utility_In Gdouble A_Height) { m_BridgeHeight = A_Height; }
    inline void SetLowerAvoidHigher(Utility_In Gbool A_Avoid) { m_LowerAvoidHigher = A_Avoid; }
    inline void SetPierSpan(Utility_In Gdouble A_Span) { m_PierSpan = A_Span; }
    inline Gdouble GetPierSpan() const { return m_PierSpan; }

};//end BridgePierGenParam

/**
* @brief
* @author ningning.gn
* @remark
**/
class ROAD_EXPORT BridgePier : public HigherRoadContainer
{
protected:
    Gdouble m_PierSpan;

    void BreakByIntersection(Utility_In BridgePierGenParam& A_Param);
    Gbool IsRoadAdj(Utility_In GShapeRoadPtr A_Road, Utility_In GShapeRoadPtr A_RoadMaybeAdj);
    virtual RoadFilterFlag CalcHigherRoadFilter(Utility_In GShapeRoadPtr A_Road);

public:
    BridgePier(Utility_In GRoadLinkPtr A_RoadLink) : HigherRoadContainer(A_RoadLink), m_PierSpan(50.0) {}

    void DoGenBridgePier(Utility_In BridgePierGenParam& A_Param);
    void ExportData(Utility_In SHP::PierExporterPtr A_Exporter);

};//end BridgePier

/**
* @brief ���ɲ���
* @author ningning.gn
* @remark
**/
class ROAD_EXPORT BridgeRailGenParam
{
    friend class BridgeRail;

protected:
    Gbool m_AvoidJunction;
    Gdouble m_MinLength;
    Gdouble m_BridgeHeight;

public:
    BridgeRailGenParam() :
        m_AvoidJunction(false), 
        m_MinLength(10.0), 
        m_BridgeHeight(0.5) 
    {}

    inline void SetAvoidJunction(Utility_In Gbool A_Avoid) { m_AvoidJunction = A_Avoid; }
    inline void SetMinLength(Utility_In Gdouble A_Length) { m_MinLength = A_Length; }
    inline void SetBridgeHeight(Utility_In Gdouble A_Height) { m_BridgeHeight = A_Height; }

};//end BridgeRailGenParam

/**
* @brief ����
* @author ningning.gn
* @remark
**/
class ROAD_EXPORT BridgeRail : public HigherRoadContainer
{
protected:
    virtual RoadFilterFlag CalcHigherRoadFilter(Utility_In GShapeRoadPtr A_Road);

public:
    BridgeRail(Utility_In GRoadLinkPtr A_RoadLink) : HigherRoadContainer(A_RoadLink) {}

    void DoGenBridgeRail(Utility_In BridgeRailGenParam& A_Param);
    void ExportData(Utility_In SHP::RailExporterPtr A_PierExporter);

};//end BridgeRail


/**
* @brief ���
* @author jianjia.wang
* @remark
**/
typedef AnGeoVector<HigherRoadPtr>  HigherRoadPtrType;
typedef AnGeoMap< GShapeNodePtr, HigherRoadPtrType > TunnelCombineMap;
struct  TunnelSegmentNode
{
    Gint32                    index;
    GEO::VectorArray    leftPoints;
    GEO::VectorArray    rightPoints;

    HigherRoadPtr        pRoadSegments;    
    Gint32                    segmentIndex;

    GShapeNodePtr        pLinkNode;    

    GShapeNodePtr        pNextLinkNode;    

    TunnelSegmentNode*    pNext;
    TunnelSegmentNode*    pPrev;
};

class ROAD_EXPORT Tunnel : public HigherRoadContainer
{
protected:
    virtual RoadFilterFlag CalcHigherRoadFilter(Utility_In GShapeRoadPtr A_Road);

    void ExportArea(/*Utility_In */GEO::VectorArray& A_Area, Utility_InOut SHP::TunnelAreaExporterPtr A_Exporter);

public:
    Tunnel(Utility_In GRoadLinkPtr A_RoadLink) : HigherRoadContainer(A_RoadLink), m_IsTunnel(0)
    {}

    void DoGenTunnel(Gdouble height);
    void ExportData(
        Utility_In SHP::TunnelExporterPtr A_TunnelExporter,
        Utility_In SHP::TunnelRoadExporterPtr A_TunnelRoadExporter);

    void ExportTunnelSink(Utility_Out SHP::TunnelAreaExporterPtr A_TunnelArea);
    void ExportTunnelSink_old(Utility_Out SHP::TunnelAreaExporterPtr A_TunnelArea);
    void ExportTunnelSink_new(Utility_Out SHP::TunnelAreaExporterPtr A_TunnelArea);

    void ExportTunnelUnderGroundArea(Utility_Out SHP::TunnelAreaExporterPtr A_TunnelArea);

protected:
    void        makeArea(GEO::VectorArray& area,HigherRoadPtr segment,Guint32 exclude1=-1,Guint32 exclude2=-1);
    void        makeArea(TunnelCombineMap& combineMap,GEO::VectorArray& area,GShapeNodePtr roadJunction,AnGeoVector<HigherRoadPtr>& segmentArray);
    Gint32         findSegment(AnGeoVector<HigherRoadPtr>& segmentArray,GShapeRoadPtr pRoad);

    void        sortCombineArray(GShapeNodePtr roadJunction,AnGeoVector<HigherRoadPtr>& segmentArray);
private:
    Gint32 m_IsTunnel;

};//end TunnelRail
