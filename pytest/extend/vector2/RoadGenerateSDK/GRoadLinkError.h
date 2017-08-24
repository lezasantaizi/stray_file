/*-----------------------------------------------------------------------------

	���ߣ����� 2016/06/15
	��ע��
	��ˣ�

-----------------------------------------------------------------------------*/
#pragma once

#include "RoadGenerateSDK_base.h"
#include "GDataStructure.h"
#include "Geometry.h"

namespace ROADGEN
{
    class Error;
    typedef Error* ErrorPtr;

    class ErrorGroup;
    typedef ErrorGroup* ErrorGroupPtr;

    class ErrorCollector;
    typedef ErrorCollector* ErrorCollectorPtr;

    /**
    * @brief �����ʶ��, ���������޸�, ����˳�������س̶�û�й�ϵ
    * @author ningning.gn
    * @remark
    **/
    enum ErrorType
    {
        etNULL                      = 0,    // ��, ���Բ�λ
        etTopology                  = 1,    // ���˴���
        etRoadConflct               = 2,    // ��·��ͻ
        etRoadShrinkExcess          = 3,    // ��·����
        etCoupleLineNotValid        = 4,    // �����߲��Ϸ�
        etJunctionInvalid           = 5,    // ·���ߴ���
        etUncategorized             = 100   // δ�����
    };
    
    /**
    * @brief ���󼶱�, ����Խ�����Խ����
    * @author ningning.gn
    * @remark
    **/
    enum ErrorLevel
    {
        elNULL              = 0,    // ��, ���Բ�λ
        elLog               = 1,    // ��־
        elWarning           = 2,    // ����
        elNormalError       = 3,    // ��ͨ���� (������Ժ���, �����������ܴ���)
        elCatastrophe       = 4,    // �������� (�����޷���������)
        elUttermost         = 5     // ����, ���Բ�λ
    };

    /**
    * @brief ��¼�������Ļ���
    * @author ningning.gn
    * @remark
    **/
    class Error
    {
        friend class ErrorGroup;

    protected:
        ErrorGroupPtr m_OwnerGroup;
        ErrorType m_ErrorType;
        ErrorLevel m_ErrorLevel;

    public:
        Error(Utility_In ErrorType A_ErrorType, Utility_In ErrorLevel A_ErrorLevel);
        virtual ~Error();

        // ��ȡ��������
        ErrorType GetErrorType() const { return m_ErrorType; }

        // ���󼶱�
        inline ErrorLevel GetErrorLevel() const { return m_ErrorLevel; }

        // ��ȡ��������
        virtual AnGeoString GetDescription() const = 0;

        // ��������ж�, ��ֹ�ظ�������ͬ����
        virtual Gbool Equal(Utility_In ErrorPtr A_Other) const = 0;

        // ����������ת��Ϊ�ַ���
        static AnGeoString ErrorTypeToString(Utility_In ErrorType A_Type);

    };//end Error

    /**
    * @brief ���˴���
    * @author ningning.gn
    * @remark
    **/
    class ErrorTopology : public Error
    {
    public:
        enum TopologyErrorType
        {
            tetNULL                 = 0,
            tetDataEmpty            = 1,    // ����Ϊ��
            tetNodeMismatch         = 2,    // �ڵ�λ�ò�ƥ��
            tetRoadSampleLack       = 3,    // ��·�����㲻��
            tetNodeOverlap          = 4,    // �����ڵ��غ�
            tetRoadIdRepeated       = 5,    // ��· Id �ظ�
            tetRoadSampleOverlap    = 6     // ��·�������ص�
        };

    private:
        TopologyErrorType m_TopologyErrorType;
        Guint64 m_ItemIdA;
        Guint64 m_ItemIdB;
        Gdouble m_HeightDiff;

    public:
        ErrorTopology() : Error(etTopology, elCatastrophe) {}

        // ����������ת��Ϊ�ַ���
        virtual AnGeoString GetDescription() const;

        // ��������ж�, ��ֹ�ظ�������ͬ����
        virtual Gbool Equal(Utility_In ErrorPtr A_Other) const;
        bool operator == (Utility_In ErrorTopology& A_Other) const;

        // ���˴�������
        inline TopologyErrorType GetTopologyErrorType() const { return m_TopologyErrorType; }

        // ����Ϊ��
        void SetDataEmpty();

        // �ڵ�λ�ò�ƥ��
        void SetNodeMismatch(Utility_In Guint64 A_NodeId, Utility_In Gdouble A_HeightDiff);
        Gbool GetNodeMismatchDetail(
            Utility_Out Guint64& A_NodeId,
            Utility_Out Gdouble& A_HeightDiff);

        // �����㲻��
        void SetRoadSampleLack(Utility_In Guint64 A_RoadId);
        Gbool GetRoadSampleLackDetail(Utility_Out Guint64& A_RoadId);

        // �ڵ��غ�
        void SetNodeOverlap(Utility_In Guint64 A_NodeIdA, Utility_In Guint64 A_NodeIdB);
        Gbool GetNodeOverlapDetail(
            Utility_Out Guint64& A_NodeIdA, 
            Utility_Out Guint64& A_NodeIdB);

        // ��· Id ��ͬ
        void SetRoadIdRepeated(Utility_In Guint64 A_RoadId);
        Gbool GetRoadIdRepeatedDetail(Utility_Out Guint64& A_RoadId);

        void SetRoadSampleOverlap(Utility_In Guint64 A_RoadId);
        Gbool GetRoadSampleOverlapDetail(Utility_Out Guint64& A_RoadId);

    };//end ErrorTopology
    typedef ErrorTopology* ErrorTopologyPtr;

    /**
    * @brief �����߲��Ϸ�
    * @author ningning.gn
    * @remark
    **/
    class ErrorCoupleLineNotValid : public Error
    {
    public:
        enum CoupleErrorType
        {
            cetNULL                  = 0,
            cetTerminalDispart       = 1,
            cetCoupleLineDispart     = 2,
            cetTinyCoupleCenter      = 3
        };

    private:
        CoupleErrorType m_ErrorType;
        GEO::Vector m_ErrorPositoin;
        AnGeoString m_ErrorDesc;

    public:
        ErrorCoupleLineNotValid(Utility_In ErrorLevel A_ErrorLevel) : Error(etCoupleLineNotValid, A_ErrorLevel), m_ErrorType(cetNULL) {}
        
        // ����������ת��Ϊ�ַ���
        virtual AnGeoString GetDescription() const;

        // ��������ж�, ��ֹ�ظ�������ͬ����
        virtual Gbool Equal(Utility_In ErrorPtr A_Other) const { return false; }

        inline void SetErrorType(Utility_In CoupleErrorType A_ErrorType) { m_ErrorType = A_ErrorType; }
        inline CoupleErrorType GetErrorType() { return m_ErrorType; }

        inline void SetErrorDesc(Utility_In AnGeoString A_ErrorDesc) { m_ErrorDesc = A_ErrorDesc; }
        inline AnGeoString GetErrorDesc() { return m_ErrorDesc; }

        inline void SetErrorPosition(Utility_In GEO::Vector& A_Pos) { m_ErrorPositoin = A_Pos; }
        inline const GEO::Vector& GetErrorPosition() const { return m_ErrorPositoin; }

    };//end ErrorCoupleLineNotValid
    typedef ErrorCoupleLineNotValid* ErrorCoupleLineNotValidPtr;

    /** 
    * @brief ·���ߴ���
    * @author ningning.gn
    * @remark
    **/
    class ErrorJunctionInvalid : public Error
    {
    public:
        enum JunctionErrorType
        {
            jetNULL             = 0,
            jetTinyBufferLine   = 1,
        };

    private:
        JunctionErrorType m_JunctionErrorType;
        Guint16 m_RoadId;
        GEO::Vector m_ErrorPos;

    public:
        ErrorJunctionInvalid();
        void SetTinyBufferLine(Utility_In Guint64& A_RoadId, Utility_In GEO::Vector& A_Pos);

        // ����������ת��Ϊ�ַ���
        virtual AnGeoString GetDescription() const;

        virtual Gbool Equal(Utility_In ErrorPtr A_Other) const;

        inline const GEO::Vector& GetErrorPosition() const { return m_ErrorPos; }

    };//end ErrorJunctionInvalid
    typedef ErrorJunctionInvalid* ErrorJunctionInvalidPtr;

    /**
    * @brief ��ͻ����
    * @author ningning.gn
    * @remark
    **/
    class ErrorRoadConflcit : public Error
    {
    private:
        Guint64 m_UniqueIdRoadA;
        Guint64 m_UniqueIdRoadB;
        GEO::Vector m_ConflictPos;

    public:
        ErrorRoadConflcit(
            Utility_In Guint64& A_UniqueIdRoadA,
            Utility_In Guint64& A_UniqueIdRoadB,
            Utility_In GEO::Vector& A_ConflictPos);

        // ����������ת��Ϊ�ַ���
        virtual AnGeoString GetDescription() const;

        // ��������ж�, ��ֹ�ظ�������ͬ����
        virtual Gbool Equal(Utility_In ErrorPtr A_Other) const;
        bool operator == (Utility_In ErrorRoadConflcit& A_Other) const;

        inline Guint64 GetUniqueIdRoadA() const { return m_UniqueIdRoadA; }
        inline Guint64 GetUniqueIdRoadB() const { return m_UniqueIdRoadB; }
        inline const GEO::Vector& GetConflictPos() const { return m_ConflictPos; }

    };//end ErrorRoadConflcit
    typedef ErrorRoadConflcit* ErrorRoadConflcitPtr;

    /**
    * @brief ��·����
    * @author ningning.gn
    * @remark
    **/
    class ErrorRoadShinkExcess : public Error
    {
    private:
        Guint64 m_RoadUniqueId;

    public:
        ErrorRoadShinkExcess(Utility_In Guint64& A_RoadUniqueId, Utility_In ErrorLevel A_ErrorLevel);

        // ����������ת��Ϊ�ַ���
        virtual AnGeoString GetDescription() const;

        // ��������ж�, ��ֹ�ظ�������ͬ����
        virtual Gbool Equal(Utility_In ErrorPtr A_Other) const;

        inline Guint64 GetRoadUniqueId() const { return m_RoadUniqueId; }

    };//end ErrorRoadShinkExcess
    typedef ErrorRoadShinkExcess* ErrorRoadShinkExcessPtr;

    /**
    * @brief ������
    * @author ningning.gn
    * @remark
    **/
    class ErrorGroup
    {
    private:
        ErrorCollectorPtr m_OwnerCollector;

        AnGeoString m_GroupName;
        ErrorType m_ErrorType;
        GDS::ObjectArray<Error> m_ErrorArr;

    public:
        ErrorGroup(
            Utility_In ErrorCollectorPtr A_OwnerCollector, 
            Utility_In ErrorType A_ErrorType);

        ~ErrorGroup();

        // ��ȡ��������
        ErrorType GetErrorType() { return m_ErrorType; }

        // ��ȡ����������
        const AnGeoString& GetGroupName() const { return m_GroupName; }

        // ��Ӵ���
        void AddError(Utility_In ErrorPtr A_Error);

        // ��ȡ��������
        inline Gint32 GetErrorCount() const { return m_ErrorArr.GetSize(); }
        inline ErrorPtr GetErrorAt(Utility_In Gint32 A_Index) const { return m_ErrorArr[A_Index]; }

    };//end ErrorGroup

    /**
    * @brief �����ռ���
    * @author ningning.gn
    * @remark
    **/
    class ErrorCollector
    {
    private:
        ErrorLevel m_QuitErrorLevel;
        GDS::ObjectArray<ErrorGroup> m_GroupArr;
        AnGeoMap<ErrorType, ErrorGroupPtr> m_GroupMap;

        void GetAllErrorItems(Utility_Out AnGeoVector<ErrorPtr>& A_ErrorArr) const;

    public:
        ErrorCollector();

        // ��ȡ������
        Gint32 GetErrorGroupCount() const { return m_GroupArr.GetSize(); }
        ErrorGroupPtr GetErrorGroupAt(Utility_In Gint32 A_Index) const { return m_GroupArr[A_Index]; }
        ErrorGroupPtr operator [] (Utility_In Gint32 A_Index) const { return m_GroupArr[A_Index]; }

        // ��մ�����
        void Clear();

        // ���Ҹ����͵Ĵ�����
        ErrorGroupPtr ForceGetErrorGroup(Utility_In ErrorType A_Type);

        ErrorGroupPtr GetErrorGroup(Utility_In ErrorType A_Type) const;

        // �Ƿ��������
        Gbool IsEmpty() const;

        // ��ȡ�������Ĵ�����
        ErrorType GetSignificantErrorType() const;

        // �����˳�����Ĵ��󼶱�
        inline void SetQuitErrorLevel(Utility_In ErrorLevel A_Level) { m_QuitErrorLevel = A_Level; }

        // �ж��Ƿ���Ҫ�˳�����
        Gbool NeedToQuit() const;

        // ����������ת��Ϊ�ַ��� for debug
//        AnGeoString GetDescriptions() const;

    };//end ErrorGroupCntr
    
}//end ROADGEN
