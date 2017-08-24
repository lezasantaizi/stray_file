/*-----------------------------------------------------------------------------

    ���ߣ����� 2016/05/20
    ��ע��
    ��ˣ�

-----------------------------------------------------------------------------*/
#pragma once

#include "GRoadLinkTools.h"
#include "SDKInterface.h"

class RoadLinkInitParam;

enum RoadJunctionBufferSide
{
    bsBoth = 0,
    bsNeither = 1,
    bsLeft = 2, 
    bsRight = 3
};

/**
* @brief ���ֺϲ��ĵ�·�� ��Id
* @author ningning.gn
* @remark
**/
class ROAD_EXPORT SubRoadManager
{
private:
    GShapeRoadPtr m_Owner;
    AnGeoList<Guint64> m_SubRoadIdArr;
    AnGeoList<Gbool> m_SubRoadSampleDir;
	AnGeoList<GEO::Vector3> m_SubRoadBreakPtArr;
    AnGeoVector<GEO::Polyline3> m_SubRoadSamples;
    AnGeoVector<Gbool> m_SubRoadSamplesInv;

public:
    SubRoadManager(Utility_In GShapeRoadPtr A_OwnerRoad) : m_Owner(A_OwnerRoad) {}

    void Merge(Utility_In GShapeRoad& A_OtherRoad);
    void MergeInv(Utility_In GShapeRoad& A_OtherRoad);
    void InvMerge(Utility_In GShapeRoad& A_OtherRoad);
    void InvMergeInv(Utility_In GShapeRoad& A_OtherRoad);

    void GetSubRoadUniqueIdArr(Utility_Out AnGeoVector<Guint64>& A_UniqueIdArr) const;

    void CalcSubRoadSamples();

    Gbool GetSubRoadSamples(Utility_In Guint64& A_SubRoadId, Utility_Out GEO::Polyline3& A_Samples);

    AnGeoString GetDescription() const;

#if ROAD_CANVAS
    void Draw(Utility_In GRAPHIC::CanvasPtr A_Canvas) const;
#endif

};//end SubRoad

/**
* @brief
* @author ningning.gn
* @remark
**/
class ROAD_EXPORT GShapeRoad
{
	friend class SubRoadManager;
    friend class GRoadLink;
    friend class GShapeNode;
    friend class GRoadLinkModifier;
    friend class GRoadLinkModifierTools;
    friend class GRoadLinkModifierFindRoadConflict;
    friend class GRoadLinkModifierRoadConflictBase;

public:
    class BufferArc
    {
        friend class GShapeNode;

    private:
        Gint32 m_iJointIndex;
        Guint64 m_StartRoadId;
        Guint64 m_EndRoadId;
        GEO::VectorArray3 m_BufferArc;
        GEO::Vector3 m_PtA; // ���� Arc ��ê��
        GEO::Vector3 m_PtB; // ���� Arc ��ê��
        GEO::Vector3 m_PtC; // ���� Arc ��ê��
        Gbool m_ArcExist;
        Gbool m_GenEdgeAttachment;   // �����Ƿ����ɵ�·����
        Gbool   m_GenFlowarea;      // �Ƿ����ɵ�����
        ColorRGBA m_Color;

    public:
        BufferArc() : m_ArcExist(false), m_GenEdgeAttachment(true),m_GenFlowarea(true) { m_Color = ColorRGBA::ColorRed(); }

        Gint32 GetJointIndex() const { return m_iJointIndex; }
        Gbool IsArcExist() const { return m_ArcExist; }
        inline const GEO::VectorArray3& GetBufferArc() const { return m_BufferArc; }

        void SetColor(Utility_In ColorRGBA& A_Color) { m_Color = A_Color; }
        const ColorRGBA& GetColor() const { return m_Color; }

        GEO::VectorArray3& GetArcSamples() { return m_BufferArc; }

        void SetGenEdgeAttachment(Utility_In Gbool A_Value) { m_GenEdgeAttachment = A_Value; }
        Gbool GetGenEdgeAttachment() const { return m_GenEdgeAttachment; }

        void SetGenFlowarea(Utility_In Gbool A_Value) { m_GenFlowarea = A_Value; }
        Gbool GetGenFlowarea() const { return m_GenFlowarea; }

        inline const GEO::Vector3& GetAnchorPtA() const { return m_PtA; }
        inline const GEO::Vector3& GetAnchorPtB() const { return m_PtB; }
        inline const GEO::Vector3& GetAnchorPtC() const { return m_PtC; }

    };//end BufferArc

private:
    GRoadLinkPtr m_Owner;

    //========================= �������� =========================//

    Guint64 m_RoadUniqueId;
    Guint32 m_RoadId;
    Guint32 m_MeshId;
    AnGeoString m_RoadName;

    Guint64 m_UniqueStartNodeId;
    Guint64 m_UniqueEndNodeId;

    SHP::RoadClass m_RoadClass;
    SHP::LinkType m_LinkType;
    Gdouble m_LaneWidth;
    Gint32 m_LaneCount;
    Gdouble m_LaneWidthOri;
    Gint32 m_LaneCountOri;
    Gint32 m_Direction;
    Gdouble m_WidthLeft;
    Gdouble m_WidthRight;
    Gdouble m_ShrinkRatioL;
    Gdouble m_ShrinkRatioR;
    SHP::FormWay m_FormWay;
    RoadFlag m_RoadFlag;
    Gint32 m_JunctionGroupId;    // 0 ��ʾ�޷���, >0 ��ʾ�����ض���

    Gbool m_IsTurnRound;
    Gbool m_Visible;
    Gbool m_CapStart;
    Gbool m_CapEnd;
    Gbool m_BreakedRoad;

    //========================= �������� =========================//

    GEO::VectorArray m_Samples2;
    GEO::VectorArray3 m_Samples3;
    GEO::VectorArray m_SamplesL;
    GEO::VectorArray m_SamplesR;
    GEO::Box m_Box;
    Gdouble m_StartBufferLen;
    Gdouble m_EndBufferLen;

    GEO::VectorArray m_SamplesSideL;
    GEO::VectorArray m_SamplesSideR;

    //========================= ·�ڶϵ�λ�� =========================//

    RoadBreakPoint m_StartBreakL;
    RoadBreakPoint m_EndBreakL;

    RoadBreakPoint m_StartBreakR;
    RoadBreakPoint m_EndBreakR;

    RoadBreakPoint m_BufferStartBreakL;
    RoadBreakPoint m_BufferEndBreakL;
    RoadBreakPoint m_BufferStartBreakR;
    RoadBreakPoint m_BufferEndBreakR;

    //========================= �˿������� =========================//

    GEO::VectorArray m_StartTriangle;
    GEO::VectorArray m_EndTriangle;

    //========================= ·�ڻ���Ķ˵� =========================//

    GEO::Vector m_FBufferEndPtL;
    GEO::Vector m_FBufferEndPtR;
    GEO::Vector m_TBufferEndPtL;
    GEO::Vector m_TBufferEndPtR;

    //========================= ·�ڻ���ı�Ե�� =========================//

    GEO::VectorArray3 m_StartBufferLineL;
    GEO::VectorArray3 m_StartBufferLineR;
    BufferArc m_StartBufferArc;

    GEO::VectorArray3 m_EndBufferLineL;
    GEO::VectorArray3 m_EndBufferLineR;
    BufferArc m_EndBufferArc;

    RoadJunctionBufferSide m_BufferSide;    // ����·�ڻ������ı�
    GEO::Vector3 m_LeftVanishingPoint;      // ����˻���
    GEO::Vector3 m_RightVanishingPoint;     // �Ҳ��˻���
    Gint32 m_LeftVanishingGroupId;          // ����˻����� Id
    Gint32 m_RightVanishingGroupId;         // �Ҳ��˻����� Id
    static Gdouble s_VanishSize;            // �˻��㲻��Ϊ 0, ���һ����С�ĳ��� 0.0001

    ColorRGBA m_LineColor;
    Gdouble m_CenterLineWidth;

    Gbool m_JuncGenSuccess;
    Gbool m_Valid;    // ����·���Ƿ���ȷ, ͨ�������־���ж��Ƿ�����һ�� ^_^

    Gbool m_LeftCouple;
    Gbool m_RightCouple;


    AnGeoString m_ErrorDescription;

    // �ӵ�·�ļ�ϵ�
    SubRoadManager      m_SubRoadManager;

    Gbool               m_bGenLeftEdgeAttachment;       //�Ƿ���������Ե�ϵĸ�����磺���ߡ������� )
    Gbool               m_bGenRightEdgeAttachment;      //�Ƿ������Ҳ��Ե�ϵĵĸ�����


protected:
    void SetUniqueId(Utility_In Guint64& A_Id);

    RoadBreakPoint GetStartBreakCenter() const;
    RoadBreakPoint GetEndBreakCenter() const;

    GEO::Vector CalcStartBreakPointL();
    GEO::Vector CalcEndBreakPointL();

    GEO::Vector CalcStartBreakPointR();
    GEO::Vector CalcEndBreakPointR();

    GEO::Vector CalcStartBreakPointCenter();
    GEO::Vector CalcEndBreakPointCenter();

    void BuildTerminalTriangles();

    // ����·�����˵Ļ���������
    void CalcStartBufferLine();
    void CalcEndBufferLine();

//     void CalcStartBufferLineStagger();
//     void CalcEndBufferLineStagger();

    // ����·�����˵Ļ�����
    void CalcTerminalBuffer(Utility_Out GEO::VectorArray3& A_StartBuff, Utility_Out GEO::VectorArray3& A_EndBuff);

    inline GEO::VectorArray& GetStartTriangle() { return m_StartTriangle; }
    inline GEO::VectorArray& GetEndTriangle() { return m_EndTriangle; }

    inline PolyLine GetLeftPolyLine() { return PolyLine(&m_SamplesL, &m_StartBreakL, &m_EndBreakL, this); }
    inline PolyLine GetRightPolyLine() { return PolyLine(&m_SamplesR, &m_StartBreakR, &m_EndBreakR, this); }

public:
    GShapeRoad(GRoadLinkPtr A_Owner);
    ~GShapeRoad();

    inline GRoadLinkPtr GetOwner() const { return m_Owner; }

    void Initialize(Utility_In RoadLinkInitParam& A_InitParam);

    inline SubRoadManager& GetSubRoadManager() { return m_SubRoadManager; }

    // �� m_Samples �� m_Samples3 ��ϡ
    void MakeSparse(Utility_In RoadLinkInitParam& A_InitParam);

    void ResetSamples(Utility_In GEO::VectorArray3& A_Samples3);
    void ResetSamples(Utility_In GEO::VectorArray& A_Samples);

    // ���ò�����λ��, ���ǵ��ٶ�ע�����ﲻ��� A_Index �ķ�Χ�Ƿ���ȷ
    void ResetSamplePoint(Utility_In Gint32 A_Index, Utility_In GEO::Vector& A_NewPos);
    void ResetSamplePoint(Utility_In Gint32 A_Index, Utility_In GEO::Vector3& A_NewPos);
    void ResetSamplePointHeight(Utility_In Gint32 A_Index, Utility_In Gdouble A_NewHeight);

    inline void SetLeftCouple(Utility_In Gbool A_LeftCouple) { m_LeftCouple = A_LeftCouple; }
    inline void SetRightCouple(Utility_In Gbool A_RightCouple) { m_RightCouple = A_RightCouple; }

    inline Gbool GetLeftCouple() const { return m_LeftCouple; }
    inline Gbool GetRightCouple() const { return m_RightCouple; }
    inline Gbool IsCoupleRoad() const { return m_LeftCouple || m_RightCouple; }

    void SetBreakedRoad() { m_BreakedRoad = true; }
    Gbool GetBreakedRoad() const { return m_BreakedRoad; }

    void ExpandLine();
    void ExpandLine(Utility_In GEO::VectorArray& A_Samples,
        Utility_Out GEO::VectorArray& A_LeftLine, Utility_Out GEO::VectorArray& A_RightLine);

#if ROAD_CANVAS
    void Draw(Utility_In GRAPHIC::CanvasPtr A_Canvas) const;
#endif
    inline void SetVisible(Utility_In Gbool A_Visible) { m_Visible = A_Visible; }

    void SetLineColor(Utility_In ColorRGBA& A_Color);

    inline void SetCenterLineWidth(Utility_In Gdouble A_Width) { m_CenterLineWidth = A_Width; }
    inline Gdouble GetCenterLineWidth() const { return m_CenterLineWidth; }

    inline Gbool IsTurnRound() const { return m_IsTurnRound; }

    inline void SetRoadFlag(Utility_In RoadFlag A_RoadFlag) { m_RoadFlag = A_RoadFlag; }
    inline RoadFlag GetRoadFlag() const { return m_RoadFlag; }

    inline void SetBufferSide(Utility_In RoadJunctionBufferSide& A_Side) { m_BufferSide = A_Side; }
    void ForbidBufferSide(Utility_In RoadJunctionBufferSide& A_Side);
    inline RoadJunctionBufferSide GetBufferSide() const { return m_BufferSide; }

    void SetLeftVanishingPoint(Utility_In GEO::Vector3& A_Point);
    void SetRightVanishingPoint(Utility_In GEO::Vector3& A_Point);

    inline void SetLeftVanishingGroupId(Utility_In Gint32 A_Id) { m_LeftVanishingGroupId = A_Id; }
    inline void SetRightVanishingGroupId(Utility_In Gint32 A_Id) { m_RightVanishingGroupId = A_Id; }

    inline Gint32 GetLeftVanishingGroupId() const { return m_LeftVanishingGroupId; }
    inline Gint32 GetRightVanishingGroupId() const { return m_RightVanishingGroupId; }

    //========================= ·�߻������� =========================//

    inline Guint32 GetRoadId() const { return UniqueIdTools::UniqueIdToId32(m_RoadUniqueId); }
    inline Guint32 GetMeshId() const { return m_MeshId; }
    inline Guint64 GetUniqueRoadId() const { return m_RoadUniqueId; }

    inline Guint32 GetStartNodeId() const { return UniqueIdTools::UniqueIdToId32(m_UniqueStartNodeId); }
    inline Guint64 GetUniqueStartNodeId() const { return m_UniqueStartNodeId; }
    void SetStartNodeId(Guint64 id){m_UniqueStartNodeId=id;}

    inline Guint32 GetEndNodeId() const { return UniqueIdTools::UniqueIdToId32(m_UniqueEndNodeId); }
    inline Guint64 GetUniqueEndNodeId() const { return m_UniqueEndNodeId; }
    void SetEndNodeId(Guint64 id){m_UniqueEndNodeId=id;}

    inline SHP::RoadClass GetRoadClass() const { return m_RoadClass; }
    inline SHP::LinkType GetLinkType() const { return m_LinkType; }
    inline Gint32 GetDirection() const { return m_Direction; }

    // ·��
    Gdouble GetWidth() const;
    Gdouble GetOriginalWidth() const;
    Gdouble GetLeftWidth() const;
    Gdouble GetRightWidth() const;
    Gdouble GetMaxWidth() const;
    void BalanceLeftRightWidth();    // �������ұ���, ʹ�����߾���

    // ���ƫ��, ����Ϊ��
    void WidthBias(Utility_In Gdouble A_Bias);
    void SetWidthBias(Utility_In Gdouble A_Bias);
    Gdouble GetWidthBias() const;

    void SetLaneCount(Utility_In Gint32 A_LaneCount);

    void SetLaneWidth(Utility_In Gdouble A_LaneWidth);
    Gdouble GetLaneWidth() const { return m_LaneWidth; }

    inline Gint32 GetLaneCount() const { return m_LaneCount; }
    inline const AnGeoString& GetRoadName() const { return m_RoadName; }
    inline SHP::FormWay GetFormWay() const { return m_FormWay; }
    GShapeNodePtr GetStartNode() const;
    GShapeNodePtr GetEndNode() const;

    // ����·����һͷ�Ľڵ�
    Guint64 GetNodeIdOnOtherSide(Utility_In Guint64 A_CurNodeId) const;
    GShapeNodePtr GetNodeOnOtherSide(Utility_In GShapeNodePtr A_CurNode) const;

    inline void GetCapState(Utility_Out Gbool& A_CapStart, Utility_Out Gbool& A_CapEnd) { A_CapStart = m_CapStart; A_CapEnd = m_CapEnd; }

    void SetJunctionGroupId(Utility_In Gint32 A_GroupId) { m_JunctionGroupId = A_GroupId; }
    Gint32 GetJunctionGroupId() const { return m_JunctionGroupId; }

    // ��������
    void SetErrorDescription(Utility_In AnGeoString& A_Desc) { m_ErrorDescription = A_Desc; }
    const AnGeoString& GetErrorDescription() const { return m_ErrorDescription; }

    //========================= ·�߼������� =========================//

    inline const GEO::VectorArray3& GetSamples3D() const { return m_Samples3; }
    inline const GEO::VectorArray& GetSamples2D() const { return m_Samples2; }
    inline Gint32 GetSampleCount() const { return (Gint32)m_Samples2.size(); }
    inline const GEO::Vector& GetSample2DAt(Utility_In Gint32 A_Index) const { return m_Samples2[A_Index]; }
    inline const GEO::Vector3& GetSample3DAt(Utility_In Gint32 A_Index) const { return m_Samples3[A_Index]; }

    inline const GEO::Vector& GetFirstSample2D() const { return m_Samples2[0]; }
    inline const GEO::Vector& GetLastSample2D() const { return m_Samples2[m_Samples2.size() - 1]; }
    inline const GEO::Vector3& GetFirstSample3D() const { return m_Samples3[0]; }
    inline const GEO::Vector3& GetLastSample3D() const { return m_Samples3[m_Samples3.size() - 1]; }

    inline const GEO::VectorArray& GetSamples2D_L() const { return m_SamplesL; }
    inline const GEO::VectorArray& GetSamples2D_R() const { return m_SamplesR; }

    // ��ȡ�������ʼ����, ���Ϊ��λ����,    Start->-------------------End
    GEO::Vector GetStartDir() const;
    // ��ȡ�������ֹ����, ���Ϊ��λ����,    Start-------------------<-End
    GEO::Vector GetEndDir() const;

    //========================= �����ຯ�� =========================//

    void RebuildBox();
    inline const GEO::Box& GetBox() const { return m_Box; }

    // ���� A_BreakPoint λ�õĴ�ֱ�������չ���ߵĽ���
    void CalcSectionPoints(RoadBreakPoint A_BreakPoint,
        Utility_Out GEO::Vector& A_Left, Utility_Out GEO::Vector& A_Right);

    // ���·����ͷ�Ľڵ���� nNodeId, ����Ϊ -1
    void RemoveNodeId(Guint64 nNodeId);

    /**
    * @brief �ϲ���·
    * @remark Forward == true  : -----CurRoad---->*-------OtherRoad----->
    *         Forward == false : -----CurRoad---->*<------OtherRoad------
    **/
    void AppendTail(Utility_In GShapeRoad& A_OtherRoad, Gbool bForward);

    /**
    * @brief �ϲ���·
    * @remark Forward == true  : -----OtherRoad---->*-------CurRoad----->
    *         Forward == false : <----OtherRoad-----*-------CurRoad----->
    **/
    void AppendHead(Utility_In GShapeRoad& A_OtherRoad, Gbool bForward);

    enum InvalidFlag
    {
        ifBreakPointInverse,
        ifNotIntersect,
        ifCorrect
    };

    // ����ϵ��Ƿ�Ϸ�
    InvalidFlag CheckBreakPointValid() const;

    // ·�߱�խ
    void SetShrinkRatio(Utility_In Gdouble A_Value);
    Gdouble GetShrinkRatio() const;
    void ShrinkWidth();
    void ForceShrinkWidth();
    inline void ExpandWidth() { m_ShrinkRatioL /= 0.9; m_ShrinkRatioR /= 0.9; }

    // �Ƿ���ȱ�խ
    Gbool IsShrinkExcess() const;

    // ��ȡ����ԭʼ�ĵ�·�����Ƚϵĵ�·��խ����
    Gdouble GetShrinkRatioCompareToOri() const;

    // ������� m_BufferStartBreak �� m_BufferEndBreak
    void CalcBufferStartEndBreakPoint();
    void CalcBufferStartEndBreakPointSymmetric();
    void CalcBufferStartEndBreakPointStaggered();

    Gdouble CalcRoadLength() const;

    // �����߶ζ˵�����ݽṹ, �� RoadBreakPoint �������֮�����
    void BuildTerminalLine();

    inline void MakeValid() { m_Valid = true; }
    inline void MakeInvalid() { m_Valid = false; }

    inline Gbool IsJunctionGenSuccess() const { return m_JuncGenSuccess; }
    inline void MakeJunctionGenSuccess(Gbool A_Success) { m_JuncGenSuccess = A_Success; }

    //========================= ��ȡ·�ڼ�����Ϣ =========================//

    inline const RoadBreakPoint& GetBufferStartBreak() const { return m_BufferStartBreakL; }
    inline const RoadBreakPoint& GetBufferEndBreak() const { return m_BufferEndBreakL; }

    inline const RoadBreakPoint& GetBufferStartBreakL() const { return m_BufferStartBreakL; }
    inline const RoadBreakPoint& GetBufferEndBreakL() const { return m_BufferEndBreakL; }
    inline const RoadBreakPoint& GetBufferStartBreakR() const { return m_BufferStartBreakR; }
    inline const RoadBreakPoint& GetBufferEndBreakR() const { return m_BufferEndBreakR; }

    RoadBreakPoint GetClampedBufferStartBreak() const;
    RoadBreakPoint GetClampedBufferEndBreak() const;

    void ClampBreakPointStart(Utility_InOut RoadBreakPoint& A_BreakPoint);
    void ClampBreakPointEnd(Utility_InOut RoadBreakPoint& A_BreakPoint);

    // �����������´������
    void GetStartBufferLine(Utility_Out GEO::VectorArray3& A_StartLineL,
        Utility_Out GEO::VectorArray3& A_StartLineR) const;
    void GetEndBufferLine(Utility_Out GEO::VectorArray3& A_EndLineL,
        Utility_Out GEO::VectorArray3& A_EndLineR) const;

    // ����������ֱ�ӷ�������, ������߲�Ҫ�Ҹ�
    inline GEO::VectorArray3& GetStartBufferLineL() { return m_StartBufferLineL; }
    inline GEO::VectorArray3& GetStartBufferLineR() { return m_StartBufferLineR; }
    inline BufferArc& GetStartBufferArc() { return m_StartBufferArc; }
    inline GEO::VectorArray3& GetEndBufferLineL() { return m_EndBufferLineL; }
    inline GEO::VectorArray3& GetEndBufferLineR() { return m_EndBufferLineR; }
    inline BufferArc& GetEndBufferArc() { return m_EndBufferArc; }

    Gbool PointHitTest(Utility_In GEO::Vector& A_HitPt, Utility_In Gdouble A_Tolerance) const;
    Gbool BoxHitTest(Utility_In GEO::Box& A_Box) const;

    Gbool GetBreakPoint(RoadBreakPoint breakPoint, Utility_Out GEO::Vector3& point);

public:
    void    ResetNode();
    Gbool   IsElevated();//�Ƿ��Ǹ߼�
    void    SetGenLeftEdgeAttachment(Gbool bGen){m_bGenLeftEdgeAttachment=bGen;}
    Gbool   GetGenLeftEdgeAttachment(){return m_bGenLeftEdgeAttachment;}
    void    SetGenRightEdgeAttachment(Gbool bGen){m_bGenRightEdgeAttachment=bGen;}
    Gbool   GetGenRightEdgeAttachment(){return m_bGenRightEdgeAttachment;}



};//end GShapeRoad

/**
* @brief 
* @author ningning.gn
* @remark
**/
class GShapeRoadTools
{
public:
    static Gbool TwoRoadWithId(
        GShapeRoadPtr A_RoadA, GShapeRoadPtr A_RoadB, 
        Guint64 A_RoadIdA, Guint64 A_RoadIdB);

};//end GShapeRoadTools
