/*-----------------------------------------------------------------------------

	���ߣ����� 2016/06/21
	��ע��
	��ˣ�

-----------------------------------------------------------------------------*/
#pragma once
#include "GRoadLinkModifier.h"
#include "GVector.h"


/*!*********************************************************************
 * \class  GRoadLinkModifierFilter_DeleteShortRoad
 *
 * TODO:   ��·��������-���ǵ����̵�·
 *
 * \author lbhna
 * \date   2016/05/27 
 ***********************************************************************/
class GRoadLinkModifierFilter_RemoveTinyRoad: 
    public GRoadLinkModifier
{
protected:
    Gdouble           m_fLengthTolerance;//�������С�����ݲ�
public:
    GRoadLinkModifierFilter_RemoveTinyRoad(Gdouble fLengthTolerance);
    virtual ~GRoadLinkModifierFilter_RemoveTinyRoad();
public:
    virtual void    DoModify();
protected:
    void            Filter();

};

/*!*********************************************************************
 * \class  GRoadLinkModifierFilter_ExtendShortRoad
 *
 * TODO:   ��·�������� �����̵ĵ�·���������ӳ�����
 *
 * \author lbhna
 * \date   2016/05/27 
 ***********************************************************************/

class GRoadLinkModifierFilter_ExtendShortRoad: 
    public GRoadLinkModifier
{
protected:
    Gdouble           m_fLengthTolerance; //�������С�����ݲ�
    Gdouble           m_fExtendScale;     //���·��Ķ��ٱ�

public:
    GRoadLinkModifierFilter_ExtendShortRoad(Gdouble fLengthTolerance,Gdouble fExtendScale);
    virtual ~GRoadLinkModifierFilter_ExtendShortRoad();

public:
    virtual void DoModify();

protected:
    void Filter();
    Gdouble GetRoadLenght(GShapeRoadPtr pRoad);
    void ExtendRoad(GShapeRoadPtr pRoad,Gdouble fExtendScale,Gbool bTail);
    Gdouble GetJunctionRoadsMaxWidth(GShapeNodePtr pNode);
    void ExtendPoint(Utility_In GEO::Vector& start,Utility_InOut GEO::Vector& end,Gdouble fDistance);
    void ExtendPoint(Utility_In GEO::Vector3& start,Utility_InOut GEO::Vector3& end,Gdouble fDistance);

};

/**
* @brief ������˴���
* @author ningning.gn
* @remark
**/
class GRoadLinkModifierTopologyCheck : public GRoadLinkModifier
{
public:
    virtual void DoModify();

};//end GRoadLinkModifierTopologyCheck

/**
* @brief ����·��խ���ȵ�����
* @author ningning.gn
* @remark
**/
class GRoadLinkModifierRoadShrinkCheck : public GRoadLinkModifier
{
public:
    virtual void DoModify();

};//end GRoadLinkModifierRoadShrinkCheck

/**
* @brief ����ظ���· Id
* @author ningning.gn
* @remark
**/
class GRoadLinkModifierRepeatedRoadIdCheck : public GRoadLinkModifier
{
public:
    virtual void DoModify();

};//end GRoadLinkModifierRepeatedRoadIdCheck

/**
* @brief ·�ڻ�����̫�̵ļ��
* @author ningning.gn
* @remark
**/
class GRoadLinkModifierTinyBufferLineCheck : public GRoadLinkModifier
{
public:
    virtual void DoModify();

};//end GRoadLinkModifierTinyBufferLineCheck
