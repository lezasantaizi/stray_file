/*-----------------------------------------------------------------------------
                                 ��·�޸�������
    ���ߣ����� 2016/04/29
    ��ע��
    ��ˣ�

-----------------------------------------------------------------------------*/
#pragma once

#include "RoadGenerateSDK_base.h"

class  GRoadLink;

/**
* @brief 
* @author ningning.gn
* @remark
**/
class ROAD_EXPORT GRoadLinkModifier
{
protected:
    GRoadLinkPtr m_RoadLink;

public:
    GRoadLinkModifier();
    ~GRoadLinkModifier();

    void Process(Utility_InOut GRoadLinkPtr A_RoadLink);

    virtual void DoModify() = 0;

};//end GRoadLinkModifier
