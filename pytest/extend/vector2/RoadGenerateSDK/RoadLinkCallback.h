/*-----------------------------------------------------------------------------

	���ߣ����� 2016/06/20
	��ע��
	��ˣ�

-----------------------------------------------------------------------------*/
#pragma once

#include "GMesh.h"
#include "GRoadLinkTools.h"
#include "GRoadLinkError.h"

#define ROAD_LINK_MODIFIER_REMOVEINNERROADS     0xFF000002

/**
* @brief ��Ϣ�ص�
* @author ningning.gn
* @remark
**/
class ROAD_EXPORT RoadLinkCallback
{
private:
    Gint32 m_CallbackId;

protected:
    inline void SetCallbackId(Utility_In Gint32 A_ID) { m_CallbackId = A_ID; }

public:
    RoadLinkCallback() {}
    virtual ~RoadLinkCallback() {}

    virtual void OnBeginImportFile() {}
    virtual void OnEndImportFile() {}

    virtual void OnAddBindObject(Utility_In Gint32 A_BindObjId) {}
    virtual void OnDeleteBindObject(Utility_In Gint32 A_BindObjId) {}

    virtual void OnWarning(Utility_In AnGeoString& A_Warning) {}

    // �ص�Id, ����Ψһ, �����ʱ�᷵�� false
    inline Gint32 GetCallbackId() const { return m_CallbackId; }

    // ��������� RoadLink �ڲ��Զ��ͷ�, �򷵻� false, ����������ⲿ�ͷ�, �򷵻� true
    virtual Gbool IsDummyCallback() const = 0;

};//end RoadLinkCallback
typedef RoadLinkCallback* RoadLinkCallbackPtr;

/**
* @brief �ص������� RoadLinkCallbackProxy
* @author ningning.gn
* @remark
**/
class ROAD_EXPORT RoadLinkCallbackProxy
{
    friend class GRoadLink;

private:
    GDS::ObjectArray<RoadLinkCallback> m_CallbackArr;
    ROADGEN::ErrorCollectorPtr m_ErrorCollector;

    void SetErrorCollector(Utility_In ROADGEN::ErrorCollectorPtr A_ErrorGroupCntr) { m_ErrorCollector = A_ErrorGroupCntr; }

public:
    RoadLinkCallbackProxy();
    ~RoadLinkCallbackProxy();

    // �󶨻ص���, �������ΪNULL��ص���Id��ͻ, �򷵻� false �Ҷ��󲻻�󶨵� RoadLinkCallbackProxy ��
    Gbool BindCallback(Utility_In RoadLinkCallbackPtr A_Callback);

    // �Ƴ��ص���, ���û���ҵ�����, ���� false
    Gbool RemoveCallback(Utility_In Gint32 A_CallBackId);

    // ͨ�� Id ���һص�����, û�ҵ����� NULL
    RoadLinkCallbackPtr FindCallback(Utility_In Gint32 A_CallbackId);

    inline ROADGEN::ErrorCollectorPtr GetErrorCollector() const { return m_ErrorCollector; }

    //========================= �ǽӿ� =========================//

    // �ص�����
    void OnBeginImportFile();
    void OnEndImportFile();

    void OnAddBindObject(Utility_In Gint32 A_BindObjId);
    void OnDeleteBindObject(Utility_In Gint32 A_BindObjId);

    void OnWarning(Utility_In AnGeoString& A_Warning);

};//end RoadLinkCallbackProxy
