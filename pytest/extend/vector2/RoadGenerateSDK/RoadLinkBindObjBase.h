/*-----------------------------------------------------------------------------

	���ߣ����� 2016/06/22
	��ע��
	��ˣ�

-----------------------------------------------------------------------------*/
#pragma once


#include "GBox.h"
#include "Geometry.h"

#define BIND_OBJECT_ID_ZOOMFILE_BOUNDBOX    1
#define BIND_OBJECT_ID_ZOOMFILE_NAVIPATH    2
#define BIND_OBJECT_ID_ZOOMFILE_NAVIPARAM	3
#define BIND_OBJECT_ID_ZOOMFILE_NAVICENTER	4
/**
* @brief 
* @author ningning.gn
* @remark
**/
class ROAD_EXPORT GRoadLinkBindObjBase
{
    friend class GRoadLink;

protected:
    GRoadLinkPtr m_OwnerRoadLink;

public:
    GRoadLinkBindObjBase() : m_OwnerRoadLink(NULL) {}
    virtual ~GRoadLinkBindObjBase(){};

    // �ص�Id, ����Ψһ, �����ʱ�᷵�� false
    virtual Gint32 GetObjId() const = 0;

    // ��������� RoadLink �ڲ��Զ��ͷ�, �򷵻� false, ����������ⲿ�ͷ�, �򷵻� true
    virtual Gbool IsDummyBindObj() const{ return false; }

};//end GRoadLinkBindObjBase
typedef GRoadLinkBindObjBase* GRoadLinkBindObjBasePtr;

/**
* @brief 
* @author ningning.gn
* @remark
**/
class ROAD_EXPORT BindObject_ZoomFileBoundBox:
    public GRoadLinkBindObjBase
{
protected:
    GEO::Box m_FileBoundingBox;

public:
    BindObject_ZoomFileBoundBox(GEO::Box& box)
    {
        m_FileBoundingBox   =box;
    }
	GEO::Box& GetBoundingBox()
	{
		return m_FileBoundingBox;
	}
    virtual ~BindObject_ZoomFileBoundBox()
    {
    }
    virtual Gint32 GetObjId() const 
    { 
		return BIND_OBJECT_ID_ZOOMFILE_BOUNDBOX;
    }
};

class ROAD_EXPORT BindObject_ZoomFileCenterZone :
	public GRoadLinkBindObjBase
{
protected:
	GEO::Box	m_FileBoundingBox;
	Gint64		m_nodeID;

public:
	BindObject_ZoomFileCenterZone(Gint64 nodeID)
	{
		m_nodeID = nodeID;
	}
	GEO::Box& GetBoundingBox()
	{
		return m_FileBoundingBox;
	}
	virtual ~BindObject_ZoomFileCenterZone()
	{
	}
	virtual Gint32 GetObjId() const
	{
		return BIND_OBJECT_ID_ZOOMFILE_NAVICENTER;
	}

    // ����ڵ�İ�Χ��, ���ڵ���·�����ɼ���֮����ô˺���
    void CalcBoundingBox();

};

class ROAD_EXPORT BindObject_NaviParam :
	public GRoadLinkBindObjBase
{
protected:
	GEO::Box        m_FileBoundingBoxIn;
	GEO::Box        m_FileBoundingBoxOut;
	GEO::Vector		m_FileCenter;
	Gfloat			m_FileAngle;

public:
	BindObject_NaviParam(GEO::Box& inbox, GEO::Box& outbox,
		GEO::Vector center, Gfloat angle)
	{
		m_FileBoundingBoxIn = inbox;
		m_FileBoundingBoxOut = outbox;
		m_FileCenter = center;
		m_FileAngle = angle;
	}
	virtual ~BindObject_NaviParam()
	{
	}
	virtual Gint32 GetObjId() const
	{
		return BIND_OBJECT_ID_ZOOMFILE_NAVIPARAM;
	}
	GEO::Box& GetBoxIn()
	{
		return m_FileBoundingBoxIn;
	}
	GEO::Box& GetBoxOut()
	{
		return m_FileBoundingBoxOut;
	}
	GEO::Vector& GetCenter()
	{
		return m_FileCenter;
	}
	Gfloat GetAngle()
	{
		return m_FileAngle;
	}
};

class ROAD_EXPORT BindObject_NaviPath:
    public GRoadLinkBindObjBase
{
public:
    static const  Gfloat        m_fPathCutRate;         //������ͷ�ü�����
protected:
    AnGeoVector<Guint64>		m_naviPathRoadIdArray;
	GEO::Box					m_clipBox;
	GEO::Vector					m_clipcenter;
	Gdouble						m_rotateAngle;		// �Ƕȣ�����Ϊ0����ʱ����ת
    GEO::Polyline3              m_NaviPathSamplers;
	Gfloat						m_fNaviRoadMinWidth;
public:
    BindObject_NaviPath(
        Utility_In AnGeoVector<Guint64>& roadIdArray, 
        Utility_In GEO::Box& clipBox,
        Utility_In GEO::Vector& center,
        Utility_In Gdouble angle) : 
        m_naviPathRoadIdArray(roadIdArray),
        m_clipBox(clipBox),
        m_clipcenter(center),
        m_rotateAngle(angle),
		m_fNaviRoadMinWidth(5.0f)
    {}

    virtual ~BindObject_NaviPath()
    {
    }
    const GEO::Polyline3&       GetNaviPathSamplers()
    {
        return m_NaviPathSamplers;
    }
    virtual Gint32 GetObjId() const 
    { 
        return BIND_OBJECT_ID_ZOOMFILE_NAVIPATH; 
    }
	GEO::Box& GetClipBox()
	{
		return m_clipBox;
	}
	GEO::Vector& GetClipCenter()
	{
		return m_clipcenter;
	}
    void    SetNaviPath(AnGeoVector<Guint64>& roadIdArray)
    {
        m_naviPathRoadIdArray =roadIdArray;
    }
    AnGeoVector<Guint64>&    GetNaviPath()
    {
        return m_naviPathRoadIdArray;
    }
    int    GetNaviRoadCount()
    {
        return m_naviPathRoadIdArray.size();
    }
    Guint64    GetNaviRoadId(Gint32 index)
    {
        return m_naviPathRoadIdArray[index];
    }

	// ��õ�����·��խ��·��
	Gfloat		GetNaviRoadWidth()
	{
		return m_fNaviRoadMinWidth;
	}

    // �Ƕȣ�����Ϊ0����ʱ����ת
    Gdouble GetClipBoxAngle() const{ return m_rotateAngle; }

    void CalcNaviSamples();

    static void CalcNaviSamples(
        Utility_In GRoadLinkPtr A_RoadLink,
        Utility_In Gdouble m_ArrowLength,
        Utility_In GEO::Box& A_ClipBox,             // ���о���, ȫ������
        Utility_In Gdouble A_Angle,                 // ������ת�Ƕ� ����
        Utility_In GEO::Vector& A_Center,           // ��������, ȫ������
        Utility_In AnGeoVector<Guint64>& A_NaviIds, // ������· Id
        Utility_Out GEO::Polyline3& A_NaviSamples); // ������, ȫ������
        
    static void CalcNaviSamples(
        Utility_In GRoadLinkPtr A_RoadLink,
        Utility_In Gdouble m_ArrowLength,
        Utility_In Gdouble A_ClipDis,               // ���о���
        Utility_In GEO::Vector& A_Center,           // ��������, ȫ������
        Utility_In AnGeoVector<Guint64>& A_NaviIds, // ������· Id
        Utility_Out GEO::Polyline3& A_NaviSamples); // ������, ȫ������

    static Gbool CalcNaviSamplesByOuterBox(
        Utility_In GRoadLinkPtr A_RoadLink,
        Utility_In Gdouble m_ArrowLength,
        Utility_In GEO::Box& A_ClipBox,             // ���о���, ȫ������
        Utility_In Gdouble A_Angle,                 // ������ת�Ƕ� ����
        Utility_In GEO::Vector& A_Center,           // ��������, ȫ������
        Utility_Out GEO::Polyline3& A_NaviSamples); // ������, ȫ������

    static Gbool CalcNaviSamplesByInnerBox(
        Utility_In GRoadLinkPtr A_RoadLink,
        Utility_In Gdouble m_ArrowLength,
        Utility_In GEO::Box& A_ClipBox,             // ���о���, ȫ������
        Utility_In Gdouble A_Angle,                 // ������ת�Ƕ� ����
        Utility_In GEO::Vector& A_Center,           // ��������, ȫ������
        Utility_Out GEO::Polyline3& A_NaviSamples); // ������, ȫ������

public:
		Gfloat		CalculateNaviRoadMinWidth();

};//end BindObject_NaviPath
typedef BindObject_NaviPath* BindObject_NaviPathPtr;
