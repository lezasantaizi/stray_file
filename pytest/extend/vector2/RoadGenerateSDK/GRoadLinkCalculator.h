/*-----------------------------------------------------------------------------

	���ߣ����� 2016/05/31
	��ע��
	��ˣ�

-----------------------------------------------------------------------------*/
#pragma once

#include "GRoadLink.h"

/**
* @brief ȫ������
* @author ningning.gn
* @remark
**/
class GRoadLinkCalculator
{
public:
    enum StepFlag
    {
        eJunctions = 0,
        eBridge = 1,
        eTunnel = 2,
        eAlignT = 3,
        eRoadAvoid = 4,
        eRemoveTinyLoop = 5,
        eZLevel = 6,
        eCheckRoadBufferLine = 7,
        eCheckRoadRepeatedRoadId = 8,
        eCheckRoadWidthShrink = 9,
        eSmoothAllRoad = 10,
        eStatisticsHoles = 11,

        eMaxStep = 12
    };

private:
    GRoadLinkPtr m_RoadLink;
    GenerateJunctionParam m_GenerateJunctionParam;
    BridgePierGenParam m_BridgePierGenParam;
    BridgeRailGenParam m_BridgeRailGenParam;

    Gbool m_StepMask[(Gint32)eMaxStep];

public:
    GRoadLinkCalculator(Utility_In GRoadLinkPtr A_RoadLink);

    // ����
    void EnableStep(Utility_In StepFlag A_Flag);
    void DisableStep(Utility_In StepFlag A_Flag);

    // �������ɲ���
    void SetGenerateJunctionParam(Utility_In GenerateJunctionParam& A_GenerateJunctionParam);
    void SetBridgePierGenParam(Utility_In BridgePierGenParam& A_BridgePierGenParam);
    void SetBridgeRailGenParam(Utility_In BridgeRailGenParam& A_BridgeRailGenParam);

    // ȫ������
    Gbool CalculateAll();

};//end GRoadLinkCalculate
