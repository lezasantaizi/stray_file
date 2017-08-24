#ifndef _VECTOR_EXPORT_IMPLEMENT_HEADER_FILE
#define _VECTOR_EXPORT_IMPLEMENT_HEADER_FILE


/*!*********************************************************************
 * \class  CVector3DExportImplement
 *
 * TODO:   ��άʸ�����ݵ���ʵ����
 *
 * \author lbhna
 * \date   2016/06/02 
 ***********************************************************************/




#include "VectorExporterPlatform.h"
#include "VectorExporterDefine.h"
#include "VectorExportModelingFile.h"





class CVectorExporterProxy;
namespace SHP
{
    class CVector3DExportImplement:
        public DataExporterForAll
    {
    protected:
        CVectorExporterProxy*   m_pProxy;
        ROADINDEX_MAP           m_RoadIndexMap;
        CVectorExportModelingFile     m_theModelingFile;
        TVector2d                m_vCenter;
        AnGeoString             m_strOutputFileName;
        GEO::Box                m_BoundingBox;
    public:
		CVector3DExportImplement(CVectorExporterProxy* pProxy, AnGeoString& strOutputFileName);
        virtual ~CVector3DExportImplement();

    public:
        const GEO::Box&         GetBoundingBox();

    public:
        virtual void            OnBeginExport();
        virtual Gbool           OnAddJunction(Utility_In JunctionDataPtr A_JunctionData);// ���� false  ��ʾ �������� ����Ӧ���Լ��ͷ�//��ͬ
        virtual Gbool           OnAddNode(Utility_In NodeDataPtr A_NodeData);
        virtual Gbool           OnAddRoad(Utility_In RoadDataPtr A_RoadData);
        virtual void            OnRoadBox(Utility_In GEO::Box& A_Box);
        virtual Gbool           OnAddTunnelRoad(Utility_In TunnelRoadDataPtr A_Data);
        virtual Gbool           OnAddPierData(Utility_In PierDataPtr A_PierData);
        virtual Gbool           OnAddRailData(Utility_In RailDataPtr A_RailData);
        virtual Gbool           OnAddTunnelData(Utility_In TunnelDataPtr A_Data);
        virtual Gbool           OnAddTunnelSinkArea(Utility_In TunnelAreaDataPtr A_TunnelArea);
        virtual Gbool           OnAddTunnelUnderGroundArea(Utility_In TunnelAreaDataPtr A_TunnelArea);
        virtual Gbool           OnAddCenterLine(Utility_In CenterLineDataPtr A_Data);
        virtual Gbool           OnAddHolePatchData(Utility_In RoadHolePatchDataPtr A_Data);
        virtual void            OnEndExport();

    protected:
        Gint32                   GetRoadIndex(Gulong64 roadId);
        Gbool                   MapRoadIndex(Gulong64 roadId,Gint32 index);
        void                    ClearState();
    protected:
        Gbool                   IsHedge(Guint32 roadClass);    //�Ƿ�������
        Gbool                   IsElevated(Guint32 roadClass);//�Ƿ��Ǹ߼�
        void                    AddBridgeBottom(Gint32 lRoadIndex,Guint8 type);
        void                    AddSection(Gint32 lRoadIndex,Guint8 type,Guint8 locate);
        void                    AddNaviLine(const GEO::Polyline3& naviPoints,BindObject_NaviParam*   pPara);
        void                    AddRoadEdgeWhitePipeline(Gint32 iRoadIndex);

    };



};










#endif