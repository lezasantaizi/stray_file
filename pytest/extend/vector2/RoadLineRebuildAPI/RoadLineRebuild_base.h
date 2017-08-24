#ifndef __ROADLINEREBUILD_BASE_H__
#define __ROADLINEREBUILD_BASE_H__

#define USE_SHAPE 0

#include "../RoadGenerateSDK/RoadGenerateSDK_api.h"
/************************************************************************/
/*					errorcode											*/
/*	101	����bufferΪ��													*/
/*	102 ���������������													*/
/*	103 �󶨵����ߴ���														*/
/*	104 �����Χ����														*/
/*	111 ��·���˹�ϵ����													*/
/*	112 ��·��ͻ															*/
/*	113 ��·����̫����														*/
/************************************************************************/
class MediaObject
{
public:

	MediaObject();

	virtual ~MediaObject();

	GRoadLinkPtr GetRoadLink() const { return m_pRoadLink; }

	ROADGEN::ErrorCollectorPtr ErrorCollect() const { return m_errorCollect; }
	void SetErrorCode(Gint32 val) { m_errorcode = val; }

	Gint32 GetErrorCode()const ;
private:
	GRoadLinkPtr				m_pRoadLink;
	ROADGEN::ErrorCollectorPtr	m_errorCollect;
	Gint32						m_errorcode;
	// ������¼
public:

	double	m_centerx;					// ���ĵ�X	��ī������
	double	m_centery;					// ���ĵ�Y	��ī������
	float	m_inRoadAngle;				// �ӽǵĽǶ�	����Ϊ0����ʱ��仯����λ����
	float	m_naviLineWidth;			// ����������Ĭ��5��
	int		m_navipointnum;				// ����·�ߵĵ����
	double* m_navixs;					// ������X��������		��ī������
	double* m_naviys;					// ������Y��������		��ī������
	double* m_navizs;					// ������Z��������		��ī������

	/************************************************************************/
	/*		������Ϣ����                                                      */
	/************************************************************************/
	GEO::Vector		m_inLink1;
	GEO::Vector		m_inLink2;
	GEO::Vector		m_outLink1;
	GEO::Vector		m_outLink2;

	GEO::Box m_minbox;					// ʸ��ͼ��������С��Χ		��ī������
	GEO::Box m_maxbox;					// ʸ��ͼ���������Χ		��ī������
};

Gint32 GetErrorCodeFromCollect(ROADGEN::ErrorCollectorPtr ecp);

#endif // __ROADLINEREBUILD_BASE_H__