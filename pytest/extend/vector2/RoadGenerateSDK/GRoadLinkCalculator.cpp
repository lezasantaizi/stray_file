/*-----------------------------------------------------------------------------

	���ߣ����� 2016/05/31
	��ע��
	��ˣ�

-----------------------------------------------------------------------------*/

#include "GRoadLinkModifierConflict.h"
#include "GRoadLinkModifierRoadAlign.h"
#include "GRoadLinkModifierCoupleLine.h"
#include "GRoadLinkModifierLoop.h"
#include "GRoadLinkModifierRoadBreak.h"
#include "GRoadLinkModifierJunctionZone.h"
#include "GRoadLinkModifierZLevel.h"
#include "GRoadLinkModifierFilter.h"
#include "GRoadLinkModifierAuxiliary.h"
#include "GRoadLinkModifierRoadSmooth.h"
#include "GRoadLinkCalculator.h"

/**
* @brief
* @author ningning.gn
* @remark
**/
GRoadLinkCalculator::GRoadLinkCalculator(Utility_In GRoadLinkPtr A_RoadLink) : m_RoadLink(A_RoadLink)
{
    for (Gint32 i = 0; i < (Gint32)eMaxStep; i++)
        m_StepMask[i] = true;

    DisableStep(eZLevel);
}

void GRoadLinkCalculator::EnableStep(Utility_In StepFlag A_Flag)
{
    m_StepMask[(Gint32)A_Flag] = true;
}

void GRoadLinkCalculator::DisableStep(Utility_In StepFlag A_Flag)
{
    m_StepMask[(Gint32)A_Flag] = false;
}

/**
* @brief �������е�����
* @remark
**/
Gbool GRoadLinkCalculator::CalculateAll()
{
    if (m_RoadLink == NULL)
        return false;

    ROADGEN::ErrorCollectorPtr oErrorCollector = 
        m_RoadLink->GetCallbackProxy().GetErrorCollector();

    if (oErrorCollector != NULL && oErrorCollector->NeedToQuit())
    {
        return false;
    }

    if (m_StepMask[eZLevel])
    {
        GRoadLinkModifierZLevel oRoadLinkModifierZLevel;
        m_RoadLink->Modify(oRoadLinkModifierZLevel);
    }

    if (m_StepMask[eJunctions])
    {
        ProjectData::ResetVanishingPtGroupId();

        // ���������߽ڵ��
        m_RoadLink->GetCoupleLineMerge().GetFindNodeCouples().SeekNodeCouples();

        // �����ת��
        GRoadLinkModifierBreakLeftTurn oModifier;
        m_RoadLink->Modify(oModifier);

        // �Ƴ�α�ڵ�
        m_RoadLink->RemovePseudoJunctions();

        // �Ƴ���·
        GRoadLinkModifierFilter_RemoveTinyRoad oDelShortRoad(10.0);
        m_RoadLink->Modify(oDelShortRoad);

        // Y ·�ڴ���
        GRoadLinkModifierY oJunctionY;
        m_RoadLink->Modify(oJunctionY);

        BindObject_NaviPathPtr oNaviPath = DynamicTypeCast<BindObject_NaviPathPtr>(
            m_RoadLink->GetRoadLinkBindObj(BIND_OBJECT_ID_ZOOMFILE_NAVIPATH));
        if (oNaviPath != NULL)
        {
            AnGeoVector<Guint64>& oPath = oNaviPath->GetNaviPath();
            if (oPath.size() >= 2)
            {
                GRoadLinkModifierYEx oJunctoinYEx(oPath);
                m_RoadLink->Modify(oJunctoinYEx);
            }
        }

//         // ƽ�����е�·
//         if (m_StepMask[eSmoothAllRoad])
//         {
//             GRoadLinkModifierRoadSmoothAll oSmoothAll;
//             m_RoadLink->Modify(oSmoothAll);
//         }

        // ����·�ཻ���
        GRoadLinkModifierConflictCheck oConflictCheck;
        m_RoadLink->Modify(oConflictCheck);
        if (oErrorCollector != NULL && oErrorCollector->NeedToQuit())
        {
            return false;
        }

        // ����·������
        {
            GRoadLinkModifierFindJunctionZone oJunctionZone;
            m_RoadLink->Modify(oJunctionZone);
        }

        {
            GModifierJunctionLeftTurnCross oJunctionLeftTurnCross;
            m_RoadLink->Modify(oJunctionLeftTurnCross);
            if (oJunctionLeftTurnCross.IsDoSomething())
            {
                GRoadLinkModifierFindJunctionZone oJunctionZone;
                m_RoadLink->Modify(oJunctionZone);
            }
        }

        // ȥ��·��С��
        if (m_StepMask[eRemoveTinyLoop])
        {
            GRoadLinkModifierDegradeTinyLoop oDegradeTinyLoop;
            m_RoadLink->Modify(oDegradeTinyLoop);
        }

        //����������
        GRoadLinkModifierCoupleProcessAll oCoupleMerge;
        m_RoadLink->Modify(oCoupleMerge);

        // ����·��
        m_RoadLink->GenerateAllJunctions(m_GenerateJunctionParam);

        // T·�ڶ���
        if (m_StepMask[eAlignT])
        {
            GRoadLinkModifierTNodeAdjust oTNodeAdjust;
            m_RoadLink->Modify(oTNodeAdjust);
        }

        // ��·����
        if (m_StepMask[eRoadAvoid])
        {
            GRoadLinkModifierAvoidConflictAll oConflictAvoidAll;
            m_RoadLink->Modify(oConflictAvoidAll);

            if (oErrorCollector != NULL && oErrorCollector->NeedToQuit())
            {
                return false;
            }
        }

        // ƽ�����е�·
        if (m_StepMask[eSmoothAllRoad])
        {
            GRoadLinkModifierRoadSmoothAll oSmoothAll;
            m_RoadLink->Modify(oSmoothAll);
        }

        // ��������·��
        m_RoadLink->GenerateAllJunctions(m_GenerateJunctionParam);

        // �и����Ļ���
        GRoadLinkModifierCutCenterLine oCutCenter;
        m_RoadLink->Modify(oCutCenter);

        // ���һ��·�ڵĻ�����
        if (m_StepMask[eCheckRoadBufferLine])
        {
            GRoadLinkModifierTinyBufferLineCheck oCheck;
            m_RoadLink->Modify(oCheck);
        }

        // ������·�ڻ��߻���
        GRoadLinkModifierCoupleArc oCoupleArc;
        m_RoadLink->Modify(oCoupleArc);

        // ������·������, ������ͷʹ�õ�����
		Guint32 nRoadCount = m_RoadLink->GetRoadCount();
		for (Guint32 i = 0; i < nRoadCount; i++)
        {
            GShapeRoadPtr oRoad = m_RoadLink->GetRoadAt((Gint32)i);
            oRoad->GetSubRoadManager().CalcSubRoadSamples();
        }

        // ����·�ཻ���, �����߼���֮�󻹿��ܳ��ֵ�·�ཻ����
        GRoadLinkModifierConflictCheck oConflictCheck2;
        m_RoadLink->Modify(oConflictCheck2);
        if (oErrorCollector != NULL && oErrorCollector->NeedToQuit())
        {
            return false;
        }

        // ��·��ȼ��
        if (m_StepMask[eCheckRoadWidthShrink])
        {
            GRoadLinkModifierRoadShrinkCheck oRoadShrinkCheck;
            m_RoadLink->Modify(oRoadShrinkCheck);
            if (oErrorCollector != NULL && oErrorCollector->NeedToQuit())
            {
                return false;
            }
        }

        // ����· Id ��ͻ
        if (m_StepMask[eCheckRoadRepeatedRoadId])
        {
            GRoadLinkModifierRepeatedRoadIdCheck oRepeatedRoadIdCheck;
            m_RoadLink->Modify(oRepeatedRoadIdCheck);
        }
    }

    if (m_StepMask[eBridge])
    {
        m_RoadLink->GetBridgePier().DoGenBridgePier(m_BridgePierGenParam);
        m_BridgeRailGenParam.SetBridgeHeight(-100);
        m_RoadLink->GetBridgeRail().DoGenBridgeRail(m_BridgeRailGenParam);
    }

    if (m_StepMask[eTunnel])
    {
        m_RoadLink->GetTunnel().DoGenTunnel(-0.5f);
    }

    if (m_StepMask[eStatisticsHoles])
    {   //ͳ�Ƶ�·�м�Ŀն�
        m_RoadLink->GetRoadHoles().StatisticsHoles(200.0);
    }

    m_RoadLink->BeginModify();
    m_RoadLink->RebuildBoundingBox();
    m_RoadLink->EndModify();
    
    return true;
}

void GRoadLinkCalculator::SetGenerateJunctionParam(Utility_In GenerateJunctionParam& A_GenerateJunctionParam)
{
    m_GenerateJunctionParam = A_GenerateJunctionParam;
}

void GRoadLinkCalculator::SetBridgePierGenParam(Utility_In BridgePierGenParam& A_BridgePierGenParam)
{
    m_BridgePierGenParam = A_BridgePierGenParam;
}

void GRoadLinkCalculator::SetBridgeRailGenParam(Utility_In BridgeRailGenParam& A_BridgeRailGenParam)
{
    m_BridgeRailGenParam = A_BridgeRailGenParam;
}
