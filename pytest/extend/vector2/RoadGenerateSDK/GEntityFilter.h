/*-----------------------------------------------------------------------------
                                   ������
    ���ߣ����� 2016/05/10
    ��ע��
    ��ˣ�

-----------------------------------------------------------------------------*/
#pragma once

#include "GDataStructure.h"
#include "SDKInterface.h"

/**
* @brief ��·����������
* @author ningning.gn
* @remark
**/
class ROAD_EXPORT RoadFilter
{
public:
    RoadFilter() {}
    virtual ~RoadFilter() {}
    virtual Gbool IsRoadPass(Utility_In GShapeRoadPtr A_Road) = 0;

};//end RoadFilter

/**
* @brief ��·���Ϲ�����
* @author ningning.gn
* @remark
**/
class ROAD_EXPORT RoadFilter_Set : public RoadFilter
{
private:
    AnGeoSet<GShapeRoadPtr> m_RoadSet;

public:
    void AppendRoad(Utility_In GShapeRoadPtr A_Road);
    void AppendRoad(Utility_In AnGeoVector<GShapeRoadPtr>& A_RoadArr);
    void AppendRoad(Utility_In AnGeoSet<GShapeRoadPtr>& A_RoadArr);
    virtual Gbool IsRoadPass(Utility_In GShapeRoadPtr A_Road);

};//end RoadFilter_Set

/**
* @brief ��·���ɹ�����
* @author ningning.gn
* @remark
**/
class ROAD_EXPORT RoadFilter_FormWay : public RoadFilter
{
private:
    AnGeoSet<SHP::FormWay> m_FormWaySet;

public:
    void AppendFormWay(Utility_In SHP::FormWay A_FormWay);
    void AppendFormWay(Utility_In AnGeoVector<SHP::FormWay>& A_A_FormWayArr);
    void AppendFormWay(Utility_In AnGeoSet<SHP::FormWay>& A_A_FormWayArr);

    virtual Gbool IsRoadPass(Utility_In GShapeRoadPtr A_Road);

};//RoadFilter_FormWay

/**
* @brief ��·�ȼ�������
* @author ningning.gn
* @remark
**/
class ROAD_EXPORT RoadFilter_RoadClass : public RoadFilter
{
private:
    AnGeoSet<SHP::RoadClass> m_RoadClassSet;

public:
    void AppendRoadClass(Utility_In SHP::RoadClass A_RoadClass);
    void AppendRoadClass(Utility_In AnGeoVector<SHP::RoadClass>& A_RoadClassArr);
    void AppendRoadClass(Utility_In AnGeoSet<SHP::RoadClass>& A_RoadClassArr);

    virtual Gbool IsRoadPass(Utility_In GShapeRoadPtr A_Road);

};//endRoadFilter_RoadClass

/**
* @brief ��·����
* @author ningning.gn
* @remark
**/
class ROAD_EXPORT RoadFilter_LinkType : public RoadFilter
{
private:
    AnGeoSet<SHP::LinkType> m_LinkTypeSet;

public:
    void AppendLinkType(Utility_In SHP::LinkType A_LinkType);
    void AppendLinkType(Utility_In AnGeoVector<SHP::LinkType>& A_LinkTypeArr);
    void AppendLinkType(Utility_In AnGeoSet<SHP::LinkType>& A_LinkTypeArr);

    virtual Gbool IsRoadPass(Utility_In GShapeRoadPtr A_Road);

};//end RoadFilter_LinkType

/**
* @brief �� ������, ֻ��ͨ��ȫ������������ɹ�
* @author ningning.gn
* @remark
**/
class ROAD_EXPORT RoadFilterCompound_And : public RoadFilter
{
private:
    GDS::ObjectArray<RoadFilter> m_FilterArr;

public:
    inline void AddFilter(Utility_In RoadFilterPtr A_Filter) { m_FilterArr.Add(A_Filter); }

    virtual Gbool IsRoadPass(Utility_In GShapeRoadPtr A_Road);

};//end RoadFilterCompound_And

/**
* @brief �� ������, ��һ��ͨ����ͨ��
* @author ningning.gn
* @remark
**/
class ROAD_EXPORT RoadFilterCompound_Or : public RoadFilter
{
private:
    GDS::ObjectArray<RoadFilter> m_FilterArr;

public:
    inline void AddFilter(Utility_In RoadFilterPtr A_Filter) { m_FilterArr.Add(A_Filter); }

    virtual Gbool IsRoadPass(Utility_In GShapeRoadPtr A_Road);

};//end RoadFilterCompound_Or

/**
* @brief �� ������
* @author ningning.gn
* @remark
**/
class ROAD_EXPORT RoadFilterCompound_Not : public RoadFilter
{
private:
    RoadFilterPtr m_Filter;

public:
    RoadFilterCompound_Not() : RoadFilter(), m_Filter(NULL) {}
    virtual ~RoadFilterCompound_Not() { delete m_Filter; }

    inline void SetFilter(Utility_In RoadFilterPtr A_Filter);
    virtual Gbool IsRoadPass(Utility_In GShapeRoadPtr A_Road);

};//end RoadFilterCompound_Not

/**
* @brief ������Ԥ��
* @author ningning.gn
* @remark
**/
class ROAD_EXPORT RoadFilterPreset
{
private:
     RoadFilter_FormWay*   m_LeftRightTurnRoad;
     RoadFilter_LinkType*  m_TunnelRoad;

    RoadFilterPreset();
    ~RoadFilterPreset();
    static RoadFilterPreset& GetRoadFilterPreset();

public:
    // ����ת�߹�����
    static RoadFilterPtr GetLeftRightTurnRoadFilter();
    static RoadFilterPtr GetTunnelRoadFilter();

};//end RoadFilterPreset
