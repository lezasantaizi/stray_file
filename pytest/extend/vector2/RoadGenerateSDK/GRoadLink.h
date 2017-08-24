/*-----------------------------------------------------------------------------
                               ��··����������
    ���ߣ����� 2016/05/20
    ��ע��
    ��ˣ�

-----------------------------------------------------------------------------*/
#pragma once

#include "ThreadTools.h"
#include "GMesh.h"
#include "CoupleLineMerge.h"
#include "CoupleLineCombine.h"
#include "GSelectSet.h"
#include "HigherRoad.h"
#include "GRoadIdMapping.h"
#include "RoadLinkBindObjBase.h"
#include "RoadLinkCallback.h"
#include "GRoadLinkParam.h"
#include "GRoadLinkTools.h"
#include "GRoadLinkError.h"
#include "GRoadHoles.h"
struct JZ_LinkRecord;

/**
* @brief 
* @author ningning.gn
* @remark
**/
class ROAD_EXPORT DebugDraw
{
private:
    GEO::VectorArray m_PointArr;
    AnGeoVector<GEO::Box> m_BoxArr;
    AnGeoVector<GEO::VectorArray> m_PolylineArr;
    AnGeoVector<GEO::VectorArray> m_PolygonArr;
    AnGeoVector<GEO::VectorArray> m_ArrowArr;
    AnGeoVector<ColorRGBA> m_PolygonColorArr;

public:
    void AddPoint(Utility_In GEO::Vector& A_Pos) { m_PointArr.push_back(A_Pos); }
    void AddPoint(Utility_In GEO::Vector3& A_Pos) { m_PointArr.push_back(GEO::VectorTools::Vector3dTo2d(A_Pos)); }
    void AddBox(Utility_In GEO::Box& A_Box) { m_BoxArr.push_back(A_Box); }
    void AddLine(Utility_In GEO::VectorArray& A_VectorArr);
    void AddLine(Utility_In GEO::VectorArray3& A_VectorArr);

    void AddPolygon(Utility_In GEO::VectorArray& A_VectorArr, Utility_In ColorRGBA& A_Color);

    void AddArrow(Utility_In GEO::VectorArray3& A_VectorArr);

    void Clear();

#if ROAD_CANVAS
    void Draw(Utility_In GRAPHIC::CanvasPtr A_Canvas);
#endif

};//end DebugDraw

/**
* @brief 
* @author ningning.gn
* @remark
**/
class ROAD_EXPORT GRoadLink
{
    friend class GRoadLinkModifier;
    friend class GRoadLinkModifierTools;

public:
#if ROAD_CANVAS
    static Gbool s_ShowNode;
    static Gbool s_ShowRoadCenter;
    static Gbool s_ShowRoadSide;
    static Gbool s_ShowSegment;
    static Gbool s_ShowCurNodeRoad;
    static Gbool s_ShowJunctionCenterZone;
    static Gbool s_ShowSelSetMessage;
    static Gbool s_ShowBufferLine;
    static Gbool s_ShowCoupleLine;
#endif

private:
    AnGeoVector<GMesh> m_MeshArr;
    AnGeoVector<GShapeRoadPtr> m_ShapeRoadArr;
    AnGeoMap<Guint64, GShapeNodePtr> m_NodeMap;    // �ڵ�Id -> �ڵ����
    
    GEO::Vector m_Center;
    Gdouble m_MaxZ;
    Gdouble m_MinZ;

    GSelectSet m_SelSet;
    ROADGEN::ThreadCommonData m_ThreadCommonData;
    ROADGEN::CoupleLineMerge m_CoupleLineMerge;
#if ROAD_CANVAS
    ROADGEN::CoupleLineCombine m_CoupleLineCombine;
#endif
    BridgePier          m_BridgePier;
    BridgeRail          m_BredgeRail;
    Tunnel              m_Tunnel;
    GRoadHoles          m_Holes;
    ROADGEN::GRoadUniqueIdMappingPtr m_RoadUniqueIdMapping;

    GEO::Box m_BoundingBox;
    QuadTree* m_QuadTree;
    Gint32 m_ModifyDepth;

    RoadLinkCallbackProxy m_CallbackProxy;

    RoadLinkParam m_RoadLinkParam;

    //========================= Debug data =========================//

    AnGeoVector<GEO::VectorArray> m_LoopArr;
    AnGeoVector<GEO::Vector> m_ErrorPoints;
    DebugDraw m_DebugDraw;

    GDS::ObjectArray<GRoadLinkBindObjBase> m_RoadLinkBindObjArr;

    GShapeRoadPtr GenerateShapeRoad(SHP::ShapeRoadPtr A_Road);
    void TryAddStartNode(Utility_In GShapeRoadPtr A_Road);
    void TryAddEndNode(Utility_In GShapeRoadPtr A_Road);
    void RemoveNodeWithTwoJoint(GShapeNodePtr pNode);

public:
    GRoadLink();
    ~GRoadLink();

    RoadLinkParam& GetRoadLinkParam() { return m_RoadLinkParam; }

    Gbool ImportData(SHP::DataImporter& A_Importer);
    Gbool ImportData(
        Utility_In SHP::DataSourcePtr A_Importer,
        Utility_InOut SHP::ImportParam& A_ShapeParam,
        Utility_InOut RoadLinkInitParam& A_InitParam);

    //========================= �û��Զ������� =========================//

    // ����û��Զ�������, ��� Id ���ظ�, ���� false
    Gbool AddRoadLinkBindObj(Utility_In GRoadLinkBindObjBasePtr A_RoadLinkBindObj);

    // ɾ��ָ��Id������, ���û���ҵ� Id ���� false
    Gbool DeleteRoadLinkBindObj(Utility_In Gint32 A_Id);

    // ��ȡָ��Id������,  ���û���ҵ���Ӧ��Id, ���� NULL
    GRoadLinkBindObjBasePtr GetRoadLinkBindObj(Utility_In Gint32 A_Id);

    //========================= �ص� =========================//

    void SetErrorCollector(Utility_In ROADGEN::ErrorCollectorPtr A_ErrorGroupCntr);
    RoadLinkCallbackProxy& GetCallbackProxy();

    //========================= ѡ����� =========================//

    GShapeNodePtr NodeHitTest(Utility_In GEO::Vector& A_HitPt, Utility_In Gdouble A_Tolerance) const;
    void NodeHitTest(Utility_In GEO::Vector& A_HitPt, Utility_In Gdouble A_Tolerance,
        Utility_Out AnGeoVector<GShapeNodePtr>& A_Nodes) const;

    GShapeRoadPtr RoadHitTest(Utility_In GEO::Vector& A_HitPt, Utility_In Gdouble A_Tolerance) const;
    void RoadBoxShapeHitTest(Utility_In GEO::Box& A_Box, Utility_Out AnGeoVector<GShapeRoadPtr>& A_RoadArr) const;
    void RoadBoxBoxHitTest(Utility_In GEO::Box& A_Box, Utility_Out AnGeoVector<GShapeRoadPtr>& A_RoadArr) const;
    void RoadBoxContain(Utility_In GEO::Box& A_Box, Utility_Out AnGeoVector<GShapeRoadPtr>& A_RoadArr) const;

    //========================= Ԫ�ػ�ȡ =========================//

    void GetAllNodes(Utility_Out AnGeoVector<GShapeNodePtr>& oNodeArr) const;
    void GetJuntionGroupNodeArr(Utility_In Gint32 A_GroupId, Utility_Out AnGeoVector<GShapeNodePtr>& A_NodeArr);

    Gint32 GetNoadCount() const;
    inline Gint32 GetRoadCount() const { return m_ShapeRoadArr.size(); }
    inline GShapeRoadPtr GetRoadAt(Utility_In Gint32 nIndex) const { return m_ShapeRoadArr[nIndex]; }
    
    Gint32 GetRoadByStartEndNodeId(
        Utility_In Guint64& A_StartNodeId, Utility_In Guint64& A_EndNodeId,
        Utility_Out AnGeoVector<GShapeRoadPtr>& A_Roads, Utility_In RoadFilterPtr A_Filter = NULL) const;

    // ������
    GShapeNodePtr FindNodeById(Utility_In Guint64 nUniqueNodeId) const;
    GShapeRoadPtr FindRoadById(Utility_In Guint64 A_RoadId) const;
    GMeshPtr FindMeshByMeshId(Utility_In Gint32 A_MeshId);
    GMeshPtr ForceGetMeshByMeshId(Utility_In Gint32 A_MeshId);

    //========================= ������ =========================//

    void BeginModify();
    void EndModify();

    void Clear();
    void GenerateAllJunctions(Utility_In GenerateJunctionParam& A_Param);

    void CalcRemovableNodes(Utility_Out AnGeoVector<GShapeNodePtr>& A_Nodes);
    void RemovePseudoJunctions();

    // ��С����·�εĿ��
    Gint32 ShrinkInvalidRoad();
    void ResetRoadWidth();

    // ɾ���ڵ㲢������·���Ķ˵� Id ����Ϊ -1
    void RemoveNode(Guint64 nNodeId);

    // ɾ��·��, ���ӹ����ڵ���ڽӱ���ɾ���Լ�
    void RemoveRoad(GShapeRoadPtr pRoad);
    void RemoveRoads(Utility_In GShapeRoadArray& A_Roads);

    //========================= ���귶Χ =========================//

    // ������ĵ���ת������ϵ֮���
    inline Gdouble GetCenterX() const { return m_Center.x; }
    inline Gdouble GetCenterY() const { return m_Center.y; }
    inline GEO::Vector3 GetCenter3D() const { return GEO::Vector3(m_Center.x, m_Center.y, 0.0); }
    inline GEO::Vector GetCenter2D() const { return m_Center; }
    GEO::Vector CalcCenterPoint() const;

    inline const GEO::Box& GetBoundingBox() const { return m_BoundingBox; }
    inline Gdouble GetMaxZ() const { return m_MaxZ; }
    inline Gdouble GetMinZ() const { return m_MinZ; }

    //========================= ��ȡģ�� =========================//
#if ROAD_CANVAS
    inline ROADGEN::CoupleLineCombine& GetCoupleLineCombine() { return m_CoupleLineCombine; }
#endif
    inline ROADGEN::CoupleLineMerge& GetCoupleLineMerge() { return m_CoupleLineMerge; }
    inline BridgePier& GetBridgePier() { return m_BridgePier; }
    inline BridgeRail& GetBridgeRail() { return m_BredgeRail; }
    inline Tunnel& GetTunnel() { return m_Tunnel; }
    inline GRoadHoles& GetRoadHoles() { return m_Holes; }
    inline GSelectSet& GetSelSet() { return m_SelSet; }
    inline ROADGEN::ThreadCommonData& GetThreadCommonData() { return m_ThreadCommonData; }
    inline ROADGEN::GRoadUniqueIdMappingPtr GetRoadMapping() { return m_RoadUniqueIdMapping; }
    inline DebugDraw& GetDebugDraw() { return m_DebugDraw; }

    void Modify(GRoadLinkModifier& A_Modifier);

    Gint32 GetMeshCount() const { return m_MeshArr.size(); }
    GMesh& GetMeshAt(Utility_In Gint32 A_Index) { return m_MeshArr[A_Index]; }

    //========================= ��ʾ��� =========================//

#if ROAD_CANVAS
    void ShowNode(Gbool bShow);
    void ShowRoadCenter(Gbool bShow);
    void ShowRoadSide(Gbool bShow);
    void ShowRoadSegment(Gbool bShow);
    void ShowCurNodeRoad(Gbool bShow);
    void ShowJunctionCenterZone(Gbool bShow);
    void ShowSelSetMsg(Gbool bShow);
    void ShowBufferLine(Gbool bShow);
    void ShowCoupleLine(Gbool bShow);
    void Draw(Utility_In GRAPHIC::CanvasPtr A_Canvas);
#endif

    //========================= interface for modifiers =========================//

    GShapeRoadPtr CreateRoad(
        Utility_In Guint64& A_UniqueId,
        Utility_In Gint32 A_LaneCount,
        Utility_In Gdouble A_LaneWidth,
        Utility_In SHP::FormWay A_FormWay,
        Utility_In AnGeoString& A_RoadName,
        Utility_In SHP::RoadClass A_RoadClass,
        Utility_In SHP::LinkType A_LinkType,
        Utility_In Guint64& A_StartNodeId,
        Utility_In Guint64& A_EndNodeId,
        Utility_In Gbool A_IsTurnRound,
        Utility_In GEO::VectorArray3& A_Samples);

    void AddRoad(GShapeRoadPtr A_Road);
    void AddNode(GShapeNodePtr A_Node);

    void RawAddRoad(GShapeRoadPtr A_Road) { m_ShapeRoadArr.push_back(A_Road); }
    void RawSetBoundBox(Utility_In GEO::Box& A_Box) { m_BoundingBox = A_Box; }
    AnGeoMap<Guint64, GShapeNodePtr>& RawGetNodeMap() { return m_NodeMap; }
//    MeshBoundary& RawGetMeshBound() { return m_MeshBound; }
    void SetCenter(TVector2d& vCenter){m_Center =vCenter;}

    void RebuildBoundingBox();

    // ����ͼ��, ���ڼ����ļ�ʱ����, �Ժ��ٸ�����, ֻ���������µĵ�·��ڵ� Id ��
    void BuildMesh();

    //========================= Debug =========================//

    void AddLoop(Utility_In RoadLoop& A_RoadLoop);
    inline void ClearLoops() { m_LoopArr.clear(); }
    inline void AddErrorPoint(Utility_In GEO::Vector& A_Pt) { m_ErrorPoints.push_back(A_Pt); }

};//end GRoadLink
