/*-----------------------------------------------------------------------------

	���ߣ����� 2016/06/22
	��ע��
	��ˣ�

-----------------------------------------------------------------------------*/
#include "GRoadLinkModifierRoadSmooth.h"
#include "GNode.h"
#include "GRoadLink.h"
#include "GSmoothUtils.h"

/**
* @brief
* @author ningning.gn
* @remark
**/
void GRoadLinkModifierRoadSmooth::DoModify()
{
    if (m_Road->GetSampleCount() <= 2)
        return;

    // ���µȾ���� 
    GEO::ResamplePolyline oResample(m_Road->GetSamples3D());
    if (!oResample.DoCalculate())
        return;

    // ƽ��
    GEO::GaussianSmooth oSmooth;
    oSmooth.SetLineData(oResample.GetResults());
    oSmooth.SetSmoothIntensity(GEO::MathTools::Min(10, oResample.GetResults().size() / 2));
    if (!oSmooth.DoSmooth())
        return;

    // ��ϡ
    GEO::VectorArray3 oResult;
    GEO::DilutingTool::MakeSparce(oSmooth.GetSmoothResult(), oResult, 0.2);

    // ���ò�����
    m_Road->ResetSamples(oResult);

    GShapeNodePtr oStartNode = m_Road->GetStartNode();
    if (oStartNode != NULL)
        oStartNode->Initialize();

    GShapeNodePtr oEndNode = m_Road->GetEndNode();
    if (oEndNode != NULL)
        oEndNode->Initialize();
}

/**
* @brief 
* @author ningning.gn
* @remark
**/
void GRoadLinkModifierRoadSmoothAll::DoModify()
{
    for (Gint32 i = 0; i < m_RoadLink->GetRoadCount(); i++)
    {
        GRoadLinkModifierRoadSmooth oSmooth(m_RoadLink->GetRoadAt(i));
        m_RoadLink->Modify(oSmooth);
    }
}
