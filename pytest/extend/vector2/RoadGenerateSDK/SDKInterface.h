/*-----------------------------------------------------------------------------

	���ߣ����� 2016/05/28
	��ע��
	��ˣ�

-----------------------------------------------------------------------------*/
#pragma once

#include "Geometry.h"

namespace SHP
{
    // ��·�ȼ�
    enum RoadClass
    {
        rcExpressWay            = 41000, // ���ٹ�·
        rcNationalRoad          = 42000, // ����
        rcCityExpressWay        = 43000, // ���п���·
        rcMainRoad              = 44000, // ��Ҫ��·
        rcSecondaryRoad         = 45000, // ��Ҫ��·
        rcNormalRoad            = 47000, // ��ͨ��·
        rcProvinceRoad          = 51000, // ʡ��
        rcCountryRoad           = 52000, // �ع�·
        rcVillageRoad           = 53000, // �繫·
        rcVillageInnerRoad      = 54000, // ������ڲ���·
        rcMiniRoad              = 49,    // С·
        rcOutLine               = 100    // ͼ����
    };

    // ��·����
    enum FormWay
    {
        fwCoupleLine                     = 1,  // ������
        fwJunction                       = 2,  // �����
        fwJCT                            = 3,  // JCT
        fwRoundabout                     = 4,  // ����
        fwServiceZone                    = 5,  // ������
        fwGuideRoad                      = 6,  // ��·
        fwAssistant                      = 7,  // ��·
        fwGuideJCT                       = 8,  // ��·+JCT
        fwExit                           = 9,  // ����
        fwEntrance                       = 10, // ���
        fwRightAheadA                    = 11, // ��ǰ��ת
        fwRightAheadB                    = 12, // ��ǰ��ת
        fwLeftAheadA                     = 13, // ��ǰ��ת
        fwLeftAheadB                     = 14, // ��ǰ��ת
        fwNormal                         = 15, // ��ͨ��·
        fwLeftRightTurn                  = 16, // ����ת
        fwServiceJCT                     = 53, // ������ + JCT
        fwServiceGuide                   = 56, // ������ + ��·
        fwServiceGrideJCT                = 58, // ������ + ��· + JCT
        fwFrontDoor                      = 59, // ��ǰ��·
        fwNonmotorVehicleTakeAdvantage   = 17  // �ǻ��������
    };

    // ��·����
    enum RoadDirectoin
    {
        rdBothWay   = 1, // ˫��ͨ��
        rdForward   = 2, // ����ͨ��
        rdBackward  = 3, // ����ͨ��
        rdForbidden = 4  // ˫�����
    };

    // ���ӷ�ʽ
    enum LinkType
    {
        ltRoad          = 0,
        ltFerry         = 1,
        ltTunnel        = 2,
        ltBridge        = 3,
        ltUnderground   = 4
    };

    // ��·����
    enum OwnerShip
    {
        osPublicRoad        = 0, // ������·
        osInnerRoad         = 1, // �ڲ���·
        osPrivateRoad       = 2, // ˽�е�·
        osUndergroundPark   = 3, // ����ͣ������·
        os3DPark            = 4, // ����ͣ������·
        osOutdoorPark       = 5, // ����ͣ������·
        osParkBuildBase     = 6  // ͣ��¥һ���·
    };

    // Ta �� FormWay ֵ
    enum FOW
    {
        fowDefault                  = -1,
        fowCoupleHighWay            = 1,
        fowCoupleNormalWay          = 2,
        fowNormalRoad               = 4,
        fowRoundabout               = 5,
        fowInnerPark                = 6,
        fowParallel                 = 101,
        fowMainLink                 = 102,
        fowLeftRightTurn            = 103,
        fowMainLineLeftRightTurn    = 104,
        fowSpecialService           = 11,
        fowEntranceExitPart         = 12,
        fowCommercial               = 14,
        fowWalkWay                  = 15,
        fowRoundaboutLike           = 17
    };

    // ������·����
    enum NaviState
    {
        nsOrdinary = 0,     // �ǵ�����·
        nsNaviRoad = 1,     // ������·
        nsExitRoad = 2      // �˳���·
    };

    /**
    * @brief 
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT ShapeRoad
    {
    private:
        Guint64 m_RoadUniqueId;
        Guint64 m_Fnd;
        Guint64 m_Tnd;
        Gdouble m_LaneWidth;
        Gdouble m_LaneWidthOriginal;
        Guint32 m_MeshId;
        Guint32 m_RoadId;
        Gint32 m_LaneCount;
        Gint32 m_LaneCountOriginal;
        Gint32 m_Direction;
        Gbool m_IsTurnRound;
        RoadClass m_RoadClass;
        OwnerShip m_OwnerShip;
        FormWay m_FormWay;
        LinkType m_LinkType;
        NaviState m_NaviState;

        AnGeoString m_RoadName;
        GEO::VectorArray3 m_Points;

    public:

        //========================= ���õ�·�������� =========================//

        void SetValue(
            Utility_In Guint64& A_RoadUniqueId,     // ��· Id
            Utility_In Gdouble A_LaneWidth,         // �������
            Utility_In Gint32 A_LaneCount,          // ������
            Utility_In Guint64& A_FNodeId,          // ��ʼ��Id
            Utility_In Guint64& A_TNodeId,          // ��ֹ��Id
            Utility_In FormWay A_FormWay,           // ��·����
            Utility_In RoadClass A_RoadClass,       // ��·�ȼ�
            Utility_In OwnerShip A_OwnerShip,       // ��·����
            Utility_In LinkType A_LinkType,         // ���ӷ�ʽ
            Utility_In Gbool A_TurnRound,           // �Ƿ���ת
            Utility_In Gint32 A_Direction,          // ��·����
            Utility_In AnGeoString& A_Name);        // ��·����

        //========================= ���õ�·��չ���� =========================//

        // ԭʼ��·���
        void SetOriginalRoadWidth(
            Utility_In Gdouble A_LaneWidth, Utility_In Gint32 A_LaneCount);

        // ��������
        inline void SetNaviState(Utility_In NaviState A_NaviState) { m_NaviState = A_NaviState; }

        //========================= �������ýӿ� =========================//

        inline void Clear() { m_Points.clear(); }

        // ��·����
        void InverseRoad();

        // ��·������
        inline void AddPoint(const GEO::Vector3& oPoint) { m_Points.push_back(oPoint); }

        //========================= ���ݻ�ȡ�ӿ� =========================//

        inline Gint32 GetPointCount() const { return m_Points.size(); }
        inline GEO::Vector3& GetPointAt(Gint32 i) { return m_Points[i]; }

        inline Guint64 GetRoadUniqueId() const { return m_RoadUniqueId; }
        inline Guint32 GetRoadId() const { return m_RoadId; }
        inline Guint32 GetMeshId() const { return m_MeshId; }
        inline Gdouble GetLaneWidth() const { return m_LaneWidth; }
        inline Gint32 GetLaneCount() const { return m_LaneCount; }
        inline Gdouble GetOriginaltLaneWidth() const { return m_LaneWidthOriginal; }
        inline Gint32 GetOriginalLaneCount() const { return m_LaneCountOriginal; }

        inline Guint64 GetUniqueStartNodeId() const { return m_Fnd; }
        inline Guint64 GetUniqueEndNodeId() const { return m_Tnd; }

        inline RoadClass GetRoadClass() const { return m_RoadClass; }
        inline Gbool IsTurnRound() const { return m_IsTurnRound; }
        inline Gint32 GetDirection() const { return m_Direction; }
        inline const LinkType GetLinkType() const { return m_LinkType; }
        inline FormWay GetFormWay() const { return m_FormWay; }
        inline const AnGeoString& GetRoadName() const { return m_RoadName; }

        inline NaviState GetNaviState() const { return m_NaviState; }

    };//end ShapeRoad
    typedef ShapeRoad* ShapeRoadPtr;

    /**
    * @brief 
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT ImportParam
    {
    public:
        GEO::Vector3 m_Position;
        Gdouble m_Range;
        Gbool m_ImportLeftTurn;
        
    };//end ImportParam
    typedef ImportParam* ImportParamPtr;

    /**
    * @brief 
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT DataSourceCallback
    {
    public:
        DataSourceCallback() {}
        virtual ~DataSourceCallback() {}

    public:
        virtual void OnTaskDesc(Utility_In AnGeoString& A_TaskDesc) {}
        virtual void OnLoadRoad(Utility_In ShapeRoadPtr A_Road) {}
        virtual void OnProgress(Utility_In Gdouble A_Progress) {}

    };//end ShapeImporterCallback
    typedef DataSourceCallback* DataSourceCallbackPtr;

    /**
    * @brief 
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT DataSource
    {
    protected:
        AnGeoVector<ShapeRoad*> m_Roads;

        Gdouble m_CenterX;
        Gdouble m_CenterY;
        Gdouble m_MaxZ;
        Gdouble m_MinZ;

        DataSourceCallbackPtr m_Callback;

    public:
        DataSource() : m_Callback(NULL) {}
        virtual ~DataSource();

        inline Gint32 GetRoadCount() const { return m_Roads.size(); }
        inline ShapeRoad* GetRoadAt(Gint32 i) const { return m_Roads[i]; }

        inline void BindCallback(Utility_In DataSourceCallbackPtr A_Callback) { m_Callback = A_Callback; }

        inline Gdouble GetMaxZ() const { return m_MaxZ; }
        inline Gdouble GetMinZ() const { return m_MinZ; }

        inline Gdouble GetCenterX() const { return m_CenterX; }
        inline Gdouble GetCenterY() const { return m_CenterY; }

    };//end DataSource
    typedef DataSource* DataSourcePtr;

    /**
    * @brief
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT DataImporter
    {
    protected:
        GRoadLinkPtr m_RoadLink;

    public:
        DataImporter(GRoadLinkPtr A_RoadLink) : m_RoadLink(A_RoadLink) {}
        virtual ~DataImporter() {}

        virtual Gbool DoImport() = 0;

    };//end DataImporter

    /**
    * @brief 
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT JunctionLink
    {
        friend class Junction;

    private:
        RoadDir m_Dir;
        Guint64 m_RoadUniqueId;
        GEO::Polyline3 m_LeftLine;
        GEO::Polyline3 m_RightLine;
        GEO::Polyline3 m_ArcLine;
        Gint32 m_LeftDegradationId;
        Gint32 m_RightDegradationId;
        Gbool m_ArcExist;
        Gbool m_LeftDegradation;
        Gbool m_RightDegradation;
        Gbool m_GenEdgeAttachment;   // �����Ƿ����ɵ�·����
        Gbool m_GenFlowarea;            //�Ƿ����ɵ�����

    public:

        //========================= �ӿ� =========================//

        inline RoadDir GetRoadLinkDirection() const { return m_Dir; }
        inline const Guint64& GetRoadUniqueId() const { return m_RoadUniqueId; }

        inline const GEO::Polyline3& GetLeftLine() const { return m_LeftLine; }
        inline const GEO::Polyline3& GetRightLine() const { return m_RightLine; }
        inline const GEO::Polyline3& GetArcLine() const { return m_ArcLine; }

        inline Gint32 GetLeftDegradationId() const { return m_LeftDegradationId; }
        inline Gint32 GetRightDegradationId() const { return m_RightDegradationId; }

        inline Gbool IsArcExist() const { return m_ArcExist; }
        inline Gbool GetLeftDegradation() const { return m_LeftDegradation; }
        inline Gbool GetRightDegradation() const { return m_RightDegradation; }

        // �����Ƿ����ɵ�·����
        inline Gbool GetGenEdgeAttachment() const { return m_GenEdgeAttachment; }
        inline Gbool GetGenFlowarea() const { return m_GenFlowarea; }

        //========================= �ǽӿ� =========================//

        void SetRoadLinkDirection(Utility_In RoadDir A_Dir) { m_Dir = A_Dir; }
        void SetRoadUniqueId(Utility_In Guint64& A_UniqueId);
        void SetLeftLine(Utility_In GEO::Polyline3& A_Line, Utility_In Gbool A_LeftDegradation, Utility_In Gint32 A_DegradationId);
        void SetRightLine(Utility_In GEO::Polyline3& A_Line, Utility_In Gbool A_RightDegradation, Utility_In Gint32 A_DegradationId);
        void SetArcLine(Utility_In GEO::Polyline3& A_ArcLine, Utility_In Gbool A_ArcExist);
        void SetGenEdgeAttachment(Utility_In Gbool A_Value) { m_GenEdgeAttachment = A_Value; }
        void SetGenFlowarea(Utility_In Gbool A_Value) { m_GenFlowarea = A_Value; }

    };//end JunctionLink
    typedef JunctionLink* JunctionLinkPtr;

    /**
    * @brief 
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT JunctionData
    {
    private:
        Guint64 m_NodeUniqueId;
        Gint32 m_DegradationId;
        AnGeoVector<JunctionLink> m_JunctionLinkArr;

    public:

        //========================= �ӿ� =========================//

        inline const Guint64& GetNodeUniqueId() const { return m_NodeUniqueId; }
        inline Gint32 GetJunctionLinkCount() const { return m_JunctionLinkArr.size(); }
        inline const JunctionLink& GetJunctionLinkAt(Utility_In Gint32 A_Index) const { return m_JunctionLinkArr[A_Index]; }

        //========================= �ǽӿ� =========================//

        inline void SetNodeUniqueId(Utility_In Guint64& A_UniqueId) { m_NodeUniqueId = A_UniqueId; }
        inline void SetDegradationId(Utility_In Gint32 A_Id) { m_DegradationId = A_Id; }
        inline void AddJunctionLink(Utility_In JunctionLink& A_JunctionLink) { m_JunctionLinkArr.push_back(A_JunctionLink); }

    };//end JunctionData
    typedef JunctionData* JunctionDataPtr;

    /**
    * @brief ����·��������
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT JunctionExporter
    {
    public:

        //========================= �ӿ� =========================//

        JunctionExporter();
        virtual ~JunctionExporter();

        virtual void BeginExport() = 0;

        // ���� true ��ʾ A_JunctionData ���ⲿ�ͷ�
        virtual Gbool OnAddJunction(Utility_In JunctionDataPtr A_JunctionData) = 0;

        virtual void EndExport() = 0;

        //========================= �ǽӿ� =========================//

        void AddJunction(Utility_In JunctionDataPtr A_JunctionData);

    };//end JunctionExporter
    typedef JunctionExporter* JunctionExporterPtr;

    /**
    * @brief �ڵ�����
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT NodeData
    {
    private:
        Guint64 m_NodeUniqueId;
        Guint64 m_GroupId;
        GEO::Vector3 m_NodePos;

    public:

        //========================= �ӿ� =========================//

        NodeData() {}

        const Guint64& GetNodeUniqueId() const { return m_NodeUniqueId; }
        const Guint64& GetGroupId() const { return m_GroupId; }
        const GEO::Vector3& GetNodePosition() const { return m_NodePos; }

        //========================= �ǽӿ� =========================//

        void SetNodeUniqueId(Utility_In Guint64& A_Id) { m_NodeUniqueId = A_Id; }
        void SetGroupId(Utility_In Guint64& A_Id) { m_GroupId = A_Id; }
        void SetNodePosition(Utility_In GEO::Vector3& A_Pos) { m_NodePos = A_Pos; }

    };//end NodeData
    typedef NodeData* NodeDataPtr;

    /**
    * @brief �����ڵ�����
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT NodeExporter
    {
    public:

        //========================= �ӿ� =========================//

        NodeExporter() {}
        virtual ~NodeExporter() {}

        virtual void BeginExporter() = 0;

        // ���� true ��ʾ A_NodeData ���ⲿ�ͷ�
        virtual Gbool OnAddNode(Utility_In NodeDataPtr A_NodeData) = 0;

        virtual void EndExporter() = 0;

        //========================= �ǽӿ� =========================//

        void AddNode(Utility_In NodeDataPtr A_NodeData);

    };//end NodeExporter
    typedef NodeExporter* NodeExporterPtr;

    /**
    * @brief ��·����
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT RoadData
    {
    private:
        GEO::VectorArray3 m_Samples;
        Gint32 m_MeshId;
        Guint64 m_RoadUniqueId;
        Guint64 m_FNodeUniqueId;
        Guint64 m_TNodeUniqueId;
        RoadBreakPoint m_StartBreakPt;
        RoadBreakPoint m_EndBreakPt;
        Gdouble m_WidthL;
        Gdouble m_widthR;
        Gint32 m_LaneCount;
        SHP::RoadClass m_RoadClass;
        Gint32 m_Direction;
        SHP::FormWay    m_Formway;
        Gbool           m_bGenLeftEdgeAttachment;
        Gbool           m_bGenRightEdgeAttachment;
    public:

        //========================= �ӿ� =========================//

        inline const GEO::VectorArray3& GetRoadSamples() const { return m_Samples; }
        inline Gint32 GetMeshId() const { return m_MeshId; }
        inline const Guint64& GetRoadUniqueId() const { return m_RoadUniqueId; }

        inline const Guint64& GetFNodeUniqueId() const { return m_FNodeUniqueId; }
        inline const Guint64& getTNodeUniqueId() const { return m_TNodeUniqueId; }

        inline const RoadBreakPoint& GetStartRoadBreakPoint() const { return m_StartBreakPt; }
        inline const RoadBreakPoint& GetEndRoadBreakPoint() const { return m_EndBreakPt; }

        inline Gdouble GetWidthLeft() const { return m_WidthL; }
        inline Gdouble GetWidthRight() const { return m_widthR; }

        inline Gint32 GetLaneCount() const { return m_LaneCount; }
        inline SHP::RoadClass GetRoadClass() const { return m_RoadClass; }
        inline Gint32 GetDirection() const { return m_Direction; }
        inline SHP::FormWay GetFormway() const { return m_Formway; }

        inline Gbool    IsGenLeftEdgeAttachment(){return m_bGenLeftEdgeAttachment;}
        inline Gbool    IsGenRightEdgeAttachment(){return m_bGenRightEdgeAttachment;}

        //========================= �ǽӿ� =========================//

        inline void SetRoadSamples(Utility_In GEO::VectorArray3& A_Samples) { m_Samples = A_Samples; }
        inline void SetMeshId(Utility_In Gint32 A_MeshId) { m_MeshId = A_MeshId; }
        inline void SetRoadUniqueId(Utility_In Guint64& A_Id) { m_RoadUniqueId = A_Id; }

        inline void SetFNodeUniqueId(Utility_In Guint64& A_Id) { m_FNodeUniqueId = A_Id; }
        inline void SetTNodeUniqueId(Utility_In Guint64& A_Id) { m_TNodeUniqueId = A_Id; }

        inline void SetStartRoadBreakPoint(Utility_In RoadBreakPoint& A_BreakPt) { m_StartBreakPt = A_BreakPt; }
        inline void SetEndRoadBreakPoint(Utility_In RoadBreakPoint& A_BreakPt) { m_EndBreakPt = A_BreakPt; }

        inline void SetWidth(Utility_In Gdouble A_Left, Utility_In Gdouble A_Right) { m_WidthL = A_Left; m_widthR = A_Right; }

        inline void SetLaneCount(Utility_In Gint32 A_LaneCount) { m_LaneCount = A_LaneCount; }
        inline void SetRoadClass(Utility_In SHP::RoadClass A_RoadClass) { m_RoadClass = A_RoadClass; }
        inline void SetDirection(Utility_In Gint32 A_Dir) { m_Direction = A_Dir; }
        inline void SetFormway(Utility_In SHP::FormWay formway) { m_Formway = formway; }

        inline void SetGenLeftEdgeAttachment(Gbool bGen){m_bGenLeftEdgeAttachment=bGen;}
        inline void SetGenRightEdgeAttachment(Gbool bGen){m_bGenRightEdgeAttachment=bGen;}

    };//end RoadData
    typedef RoadData* RoadDataPtr;

    /**
    * @brief ������·����
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT RoadExporter
    {
    public:

        //========================= �ӿ� =========================//

        RoadExporter(){}
        virtual ~RoadExporter(){}

        virtual void BeginExport() = 0;

        // ���� true ��ʾ A_RoadData ���ⲿ�ͷ�
        virtual Gbool OnAddRoad(Utility_In RoadDataPtr A_RoadData) = 0;

        virtual void EndExport() = 0;

        //========================= �ǽӿ� =========================//

        void AddRoad(Utility_In RoadDataPtr A_RoadData);

    };//end TableExporter
    typedef RoadExporter* RoadExporterPtr;

    /**
    * @brief ������Χ��
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT RoadBoxExporter
    {
    public:

        //========================= �ӿ� =========================//

        RoadBoxExporter() {}
        virtual ~RoadBoxExporter() {}

        virtual void BeginExport() = 0;

        virtual void SetBox(Utility_In GEO::Box& A_Box) = 0;

        virtual void EndExport() = 0;

    };//end RoadBoxExporter
    typedef RoadBoxExporter* RoadBoxExporterPtr;

    /**
    * @brief ���������·������
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT TunnelRoadData
    {
    private:
        GEO::VectorArray3 m_Samples;
        Gint32 m_MeshId;
        Gdouble m_Width;
        Gint32 m_Tunnel;

    public:

        //========================= �ӿ� =========================//

        inline const GEO::VectorArray3& GetSamples() const { return m_Samples; }
        inline Gint32 GetMeshId() const { return m_MeshId; }
        inline Gdouble GetWidth() const { return m_Width; }
        inline Gint32 GetTunnel() const { return m_Tunnel; }

        //========================= �ǽӿ� =========================//

        inline void SetSamples(Utility_In GEO::VectorArray3& A_Samples) { m_Samples = A_Samples; }
        inline void SetMeshId(Utility_In Gint32 A_MeshId) { m_MeshId = A_MeshId; }
        inline void SetWidth(Utility_In Gdouble A_Width) { m_Width = A_Width; }
        inline void SetTunnel(Utility_In Gint32 A_Tunnel) { m_Tunnel = A_Tunnel; }

    };//end TunnelRoadData
    typedef TunnelRoadData* TunnelRoadDataPtr;

    /**
    * @brief ���������·��
    * @author
    * @remark
    **/
    class ROAD_EXPORT TunnelRoadExporter
    {
    public:

        //========================= �ӿ� =========================//

        TunnelRoadExporter() {}
        virtual ~TunnelRoadExporter() {}

        virtual void BeginExport() = 0;

        // ���� true ��ʾ A_Data ���ⲿ�ͷ�
        virtual Gbool OnAddTunnelRoad(Utility_In TunnelRoadDataPtr A_Data) = 0;

        virtual void EndExport() = 0;

        //========================= �ǽӿ� =========================//

        void AddTunnelRoad(Utility_In TunnelRoadDataPtr A_Data);

    };//end TunnelRoadExporter
    typedef TunnelRoadExporter* TunnelRoadExporterPtr;

    /**
    * @brief �Ŷ�����
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT PierData
    {
    private:
        Gint32 m_MeshId;
        Guint64 m_RoadUniqueId;
        RoadBreakPoint m_StartBreakPt;
        RoadBreakPoint m_EndBreakPt;
        Gdouble m_PierSpan;

    public:

        //========================= �ӿ� =========================//

        inline Gint32 GetMeshId() const { return m_MeshId; }
        inline const Guint64& GetRoadUniqueId() const { return m_RoadUniqueId; }
        inline const RoadBreakPoint& GetStartBreakPt() const { return m_StartBreakPt; }
        inline const RoadBreakPoint& GetEndBreakPt() const { return m_EndBreakPt; }
        inline Gdouble GetPierSpan() const { return m_PierSpan; }

        //========================= �ǽӿ� =========================//

        inline void SetMeshId(Utility_In Gint32 A_Id) { m_MeshId = A_Id; }
        inline void SetRoadUniqueId(Utility_In Guint64& A_Id) { m_RoadUniqueId = A_Id; }
        inline void SetStartBreakPt(Utility_In RoadBreakPoint& A_RoadBreakPt) { m_StartBreakPt = A_RoadBreakPt; }
        inline void SetEndBreakPt(Utility_In RoadBreakPoint& A_RoadBreakPt) { m_EndBreakPt = A_RoadBreakPt; }
        inline void SetPierSpan(Utility_In Gdouble A_PierSpan) { m_PierSpan = A_PierSpan; }

    };//end PierData
    typedef PierData* PierDataPtr;

    /**
    * @brief �����Ŷ�����
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT PierExporter
    {
    public:

        //========================= �ӿ� =========================//

        PierExporter() {}
        virtual ~PierExporter() {}

        virtual void BeginExport() = 0;

        // ���� true ��ʾ A_PierData ���ⲿ�ͷ�
        virtual Gbool OnAddPierData(Utility_In PierDataPtr A_PierData) = 0;

        virtual void EndExport() = 0;

        //========================= �ǽӿ� =========================//

        void AddPierData(Utility_In PierDataPtr A_PierData);

    };//end PierExporter
    typedef PierExporter* PierExporterPtr;

    /**
    * @brief ��������
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT RailData
    {
    public:
        enum RoadSide
        {
            eLeftSide = 0,
            eRightSide = 1
        };

        enum RailType
        {
            rtNormal = 11,
            rtNormalCoupleMerge = 31,
            rtHighRoadMerge = 32
        };

    private:
        Gint32 m_MeshId;
        Guint64 m_RoadIds;
        RoadBreakPoint m_StartBreakPt;
        RoadBreakPoint m_EndBreakPt;
        RoadSide m_Side;
        RailType m_Type;

    public:

        //========================= �ӿ� =========================//

        inline Gint32 GetMeshId() const { return m_MeshId; }
        inline const Guint64& GetRoadUniqueId() const { return m_RoadIds; }
        inline const RoadBreakPoint& GetStartBreakPt() const { return m_StartBreakPt; }
        inline const RoadBreakPoint& GetEndBreakPt() const { return m_EndBreakPt; }
        inline RoadSide GetRoadSide() const { return m_Side; }
        inline RailType GetRailType() const { return m_Type; }

        //========================= �ǽӿ� =========================//

        inline void SetMeshId(Utility_In Gint32 A_MeshId) { m_MeshId = A_MeshId; }
        inline void SetRoadUniqueId(Utility_In Guint64& A_Id) { m_RoadIds = A_Id; }
        inline void SetStartBreakPt(Utility_In RoadBreakPoint& A_RoadBreakPt) { m_StartBreakPt = A_RoadBreakPt; }
        inline void SetEndBreakPt(Utility_In RoadBreakPoint& A_RoadBreakPt) { m_EndBreakPt = A_RoadBreakPt; }
        inline void SetRoadSide(Utility_In RoadSide A_Side) { m_Side = A_Side; }
        inline void SetRailType(Utility_In RailType A_Type) { m_Type = A_Type; }

    };//end RailData
    typedef RailData* RailDataPtr;

    /**
    * @brief ������������
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT RailExporter
    {
    public:

        //========================= �ӿ� =========================//

        RailExporter() {}
        virtual ~RailExporter() {}

        virtual void BeginExport() = 0;

        // ���� true ��ʾ A_RailData ���ⲿ�ͷ�
        virtual Gbool OnAddRailData(Utility_In RailDataPtr A_RailData) = 0;

        virtual void EndExport() = 0;

        //========================= �ǽӿ� =========================//

        void AddRailData(Utility_In RailDataPtr A_RailData);

    };//end PierExporter
    typedef RailExporter* RailExporterPtr;

    /**
    * @brief �������
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT TunnelData
    {
    private:
        Guint64 m_RoadUniqueId;
        RoadBreakPoint m_StartBreakPt;
        RoadBreakPoint m_EndBreakPt;
        Gint32 m_HaveTop;
        Gint32 m_TopStyle;

    public:

        //========================= �ӿ� =========================//

        const Guint64& GetRoadUniqueId() const { return m_RoadUniqueId; }
        const RoadBreakPoint& GetStartBreakPt() const { return m_StartBreakPt; }
        const RoadBreakPoint& GetEndBreakPt() const { return m_EndBreakPt; }
        Gint32 GetHaveTop() const { return m_HaveTop; }
        Gint32 GetTopStyle() const { return m_TopStyle; }

        //========================= �ǽӿ� =========================//

        void SetRoadUniqueId(Utility_In Guint64& A_Id) { m_RoadUniqueId = A_Id; }
        void SetStartBreakPt(Utility_In RoadBreakPoint& A_BreakPt) { m_StartBreakPt = A_BreakPt; }
        void SetEndBreakPt(Utility_In RoadBreakPoint& A_BreakPt) { m_EndBreakPt = A_BreakPt; }
        void SetHaveTop(Utility_In Gint32 A_HaveTop) { m_HaveTop = A_HaveTop; }
        void SetTopStyle(Utility_In Gint32 A_TopStyle) { m_TopStyle = A_TopStyle; }

    };//end TunnelData
    typedef TunnelData* TunnelDataPtr;

    /**
    * @brief �����������
    * @author jianjia.wang
    * @remark
    **/
    class ROAD_EXPORT TunnelExporter
    {
    public:

        //========================= �ӿ� =========================//

        TunnelExporter() {}
        virtual ~TunnelExporter() {}

        virtual void BeginExport() = 0;

        // ���� true ��ʾ A_Data ���ⲿ�ͷ�
        virtual Gbool OnAddTunnelData(Utility_In TunnelDataPtr A_Data) = 0;

        virtual void EndExport() = 0;

        //========================= �ǽӿ� =========================//

        void AddTunnelData(Utility_In TunnelDataPtr A_Data);

    };//end TunnelExporter
    typedef TunnelExporter* TunnelExporterPtr;

    /**
    * @brief 
    * @author ningning.gn
    * @remark
    **/
    class TunnelAreaData
    {
    private:
        GEO::VectorArray m_Area;

    public:
        const GEO::VectorArray& GetArea() const { return m_Area; }

        void SetArea(Utility_In GEO::VectorArray& A_Area) { m_Area = A_Area; }

    };//end TunnelAreaData
    typedef TunnelAreaData* TunnelAreaDataPtr;

    /**
    * @brief �����������
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT TunnelAreaExporter
    {
    public:

        //========================= �ӿ� =========================//

        TunnelAreaExporter() {}
        virtual ~TunnelAreaExporter() {}

        virtual void BeginExport() = 0;

        // ���� true ��ʾ A_TunnelArea ���ⲿ�ͷ�
        virtual Gbool OnAddTunnelArea(Utility_In TunnelAreaDataPtr A_TunnelArea) = 0;

        virtual void EndExport() = 0;

        //========================= �ǽӿ� =========================//

        void AddTunnelArea(Utility_In TunnelAreaDataPtr A_TunnelArea);

    };//end TunnelAreaExporter
    typedef TunnelAreaExporter* TunnelAreaExporterPtr;

    /**
    * @brief ˫��������
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT CenterLineData
    {
    private:
        GEO::VectorArray3 m_CenterLine;
        Gint32 m_Type;

    public:

        //========================= �ӿ� =========================//

        CenterLineData() : m_Type(PST_ROAD_DYELLOWLINE_NORMAL) {}

        const GEO::VectorArray3& GetCenterLine() const { return m_CenterLine; }
        Gint32 GetType() const { return m_Type; }

        //========================= �ǽӿ� =========================//

        void SetCenterLine(Utility_In GEO::VectorArray3& A_Line) { m_CenterLine = A_Line; }
        void SetType(Utility_In Gint32 A_Type) { m_Type = A_Type; }

    };//end CenterLineData
    typedef CenterLineData* CenterLineDataPtr;

    /**
    * @brief ˫���ߵ���
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT CenterLineExporter
    {
    public:

        //========================= �ӿ� =========================//

        CenterLineExporter() {}
        virtual ~CenterLineExporter() {}

        virtual void BeginExport() = 0;

        // ���� true ��ʾ A_Data ���ⲿ�ͷ�, ��λ: Mercator ��
        virtual Gbool OnAddCenterLine(Utility_In CenterLineDataPtr A_Data) = 0;

        virtual void EndExport() = 0;

        //========================= �ǽӿ� =========================//

        void AddCenterLine(Utility_In CenterLineDataPtr A_Data);

    };//end CenterLineExporter
    typedef CenterLineExporter* CenterLineExporterPtr;



    class ROAD_EXPORT RoadHolePatchData
    {
    protected:
        Gint32                  m_iPatchStyle;      //������ʽ
        GEO::VectorArray3       m_HoleVertexArray;
        AnGeoVector<Gint32>     m_HoleIndexArray;

    public:
        RoadHolePatchData(Gint32 iStyle,const GEO::VectorArray3& vertex,const AnGeoVector<Gint32>& indicates)
        {
            m_iPatchStyle       =iStyle;
            m_HoleVertexArray   =vertex;
            m_HoleIndexArray    =indicates;
        }
    public:
        GEO::VectorArray3&          GetVertex(){return m_HoleVertexArray;}
        Gint32                      GetStyle(){return m_iPatchStyle;}
        AnGeoVector<Gint32>&        GetIndicates(){return m_HoleIndexArray;}
        void                        SetVertex(const GEO::VectorArray3& vertex){m_HoleVertexArray=vertex;}
        void                        SetStyle(Gint32 iStyle){m_iPatchStyle=iStyle;}

    };
    typedef RoadHolePatchData* RoadHolePatchDataPtr;
    class ROAD_EXPORT RoadHolePatchExporter
    {
    public:
        //========================= �ӿ� =========================//
        RoadHolePatchExporter() {}
        virtual ~RoadHolePatchExporter() {}
        virtual void BeginExport() = 0;
        // ���� true ��ʾ A_Data ���ⲿ�ͷ�, ��λ: Mercator ��
        virtual Gbool OnAddHolePathData(Utility_In RoadHolePatchDataPtr A_Data) = 0;
        virtual void EndExport() = 0;
        //========================= �ǽӿ� =========================//
        void AddHolePatchData(Utility_In RoadHolePatchDataPtr A_Data);
    };
    typedef RoadHolePatchExporter* RoadHolePatchExporterPtr;


    /**
    * @brief 
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT DataExporterForAll
    {
    private:
        GRoadLinkPtr m_RoadLink;
        JunctionExporterPtr m_JunctionExporter;
        NodeExporterPtr m_NodeExporter;
        RoadExporterPtr m_RoadExporter;
        RoadBoxExporterPtr m_BoxExporter;
        TunnelRoadExporterPtr m_TunnelRoadExporter;
        PierExporterPtr m_PierExporter;
        RailExporterPtr m_RailExporter;
        TunnelExporterPtr m_TunnelExporter;
        CenterLineExporterPtr m_CenterLineExporter;
        TunnelAreaExporterPtr m_TunnelSinkExporter;
        TunnelAreaExporterPtr m_TunnelUnderGroundAreaExporter;
        RoadHolePatchExporterPtr    m_HolePatchExporter;
    public:

        //========================= �ӿ� =========================//

        DataExporterForAll();
        virtual ~DataExporterForAll();

        inline GRoadLinkPtr GetRoadLink() { return m_RoadLink; }

        virtual void OnBeginExport() = 0;

        // ���� false ��ʾ �������� ����Ӧ���Լ��ͷ�
        virtual Gbool OnAddRoad(Utility_In RoadDataPtr A_RoadData) = 0;
        virtual Gbool OnAddNode(Utility_In NodeDataPtr A_NodeData) = 0;
        virtual Gbool OnAddJunction(Utility_In JunctionDataPtr A_JunctionData) = 0;
        virtual void OnRoadBox(Utility_In GEO::Box& A_Box) = 0;
        virtual Gbool OnAddPierData(Utility_In PierDataPtr A_PierData) = 0;
        virtual Gbool OnAddRailData(Utility_In RailDataPtr A_RailData) = 0;
        virtual Gbool OnAddTunnelRoad(Utility_In TunnelRoadDataPtr A_Data) = 0;
        virtual Gbool OnAddTunnelData(Utility_In TunnelDataPtr A_Data) = 0;
        virtual Gbool OnAddTunnelSinkArea(Utility_In TunnelAreaDataPtr A_TunnelArea) = 0;
        virtual Gbool OnAddTunnelUnderGroundArea(Utility_In TunnelAreaDataPtr A_TunnelArea) = 0;
        virtual Gbool OnAddCenterLine(Utility_In CenterLineDataPtr A_Data) = 0;
        virtual Gbool OnAddHolePatchData(Utility_In RoadHolePatchDataPtr A_Data) = 0;

        virtual void OnEndExport() = 0;

        //========================= �ǽӿ� =========================//

        inline void SetRoadLink(Utility_In GRoadLinkPtr A_RodLink)      { m_RoadLink = A_RodLink; }
        inline JunctionExporterPtr GetJunctionExporter()        { return m_JunctionExporter; }
        inline NodeExporterPtr GetNodeExporter()                { return m_NodeExporter; }
        inline RoadExporterPtr GetRoadExporter()                { return m_RoadExporter; }
        inline RoadBoxExporterPtr GetBoxExporter()              { return m_BoxExporter; }
        inline TunnelRoadExporterPtr GetTunnelRoadExporter()    { return m_TunnelRoadExporter; }
        inline PierExporterPtr GetPierExporter()                { return m_PierExporter; }
        inline RailExporterPtr GetRailExporter()                { return m_RailExporter; }
        inline TunnelExporterPtr GetTunnelExporter()            { return m_TunnelExporter; }
        inline CenterLineExporterPtr GetCenterLineExporter()    { return m_CenterLineExporter; }
        inline TunnelAreaExporterPtr GetTunnelSinkExporter()    { return m_TunnelSinkExporter; }
        inline TunnelAreaExporterPtr GetTunnelUnderGroundAreaExporter() { return m_TunnelUnderGroundAreaExporter; }
        inline RoadHolePatchExporterPtr GetRoadHolePatchExporter() { return m_HolePatchExporter; }

    };//end DataExporter
    typedef DataExporterForAll* DataExporterForAllPtr;

}//end SHP
