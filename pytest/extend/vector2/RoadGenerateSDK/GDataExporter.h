/*-----------------------------------------------------------------------------

	���ߣ����� 2016/05/29
	��ע��
	��ˣ�

-----------------------------------------------------------------------------*/
#pragma once

#include "SDKInterface.h"

/**
* @brief �����ռ�����������������
* @author ningning.gn
* @remark
**/
class ROAD_EXPORT GDataExporterTool
{
private:
    GRoadLinkPtr m_RoadLink;

//     static void AddJunctionRecordScd(
//         SHP::JunctionExporterPtr A_Exporter, Utility_In GEO::VectorArray3& A_Line,
//         Gint32 A_NodeId, Gint32 A_RoadId,
//         Gpstr A_NodeIds, Gpstr A_RoadIds,
//         Gint32 A_InnerIndex, Gbool A_GenStreamGuidance, Gbool A_Degradation, Gint32 A_DegradationId);
// 
//     static void AddJunctionRecordMeter(
//         SHP::JunctionExporterPtr A_Exporter, Utility_In GEO::VectorArray3& A_Line,
//         Gint32 A_NodeId, Gint32 A_RoadId,
//         Gpstr A_NodeIds, Gpstr A_RoadIds,
//         Gint32 A_InnerIndex, Gbool A_GenStreamGuidance, Gbool A_Degradation, Gint32 A_DegradationId);

public:
    explicit GDataExporterTool(Utility_In GRoadLinkPtr A_RoadLink);
    ~GDataExporterTool();

    // ����ȫ������
    void ExportDataAll(Utility_In SHP::DataExporterForAllPtr A_Exporter);

    // �����ڵ�������
    void ExportJunction(SHP::JunctionExporterPtr A_JunctionExporter);

    // �����ڵ�
    void ExportNode(Utility_Out SHP::NodeExporterPtr A_NodeExporter);

    // ������·�����·���� buffer ��λ��
    void ExportRoadLine(
        SHP::RoadExporterPtr oRoadExporter,
        SHP::RoadBoxExporterPtr oRoadBoxExporter);

    // �����Ŷ�����
    void ExportBridgePier(Utility_In SHP::PierExporterPtr A_Exporter);

    // ������������
    void ExportBridgeRail(Utility_In SHP::RailExporterPtr A_Exporter);

    // �����������
    void ExportTunnelData(
        Utility_In SHP::TunnelExporterPtr A_TunnelExporter,
        Utility_In SHP::TunnelRoadExporterPtr A_TunnelRoadExporter);

    void ExportTunnelSink(Utility_Out SHP::TunnelAreaExporterPtr A_TunnelAreaExporter);

    void ExportTunnelUnderGroundArea(Utility_Out SHP::TunnelAreaExporterPtr A_TunnelArea);

};//end GDataExporter
