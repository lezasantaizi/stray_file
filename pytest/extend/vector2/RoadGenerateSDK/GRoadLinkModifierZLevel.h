/*-----------------------------------------------------------------------------

	���ߣ����� 2016/06/05
	��ע��
	��ˣ�

-----------------------------------------------------------------------------*/
#pragma once

#include "GRoadLinkModifier.h"

/**
* @brief 
* @author ningning.gn
* @remark
**/
class ROAD_EXPORT GRoadLinkModifierZLevel : public GRoadLinkModifier
{
public:
    GRoadLinkModifierZLevel()
        : GRoadLinkModifier() {}

    virtual void DoModify();

};//end GRoadLinkModifierZLevel
