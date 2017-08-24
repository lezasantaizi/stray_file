/*-----------------------------------------------------------------------------

	���ߣ����� 2016/06/15
	��ע��
	��ˣ�

-----------------------------------------------------------------------------*/
#include "GRoadLinkError.h"
#include "StringTools.h"

namespace ROADGEN
{
    /**
    * @brief 
    * @author ningning.gn
    * @remark
    **/
    Error::Error(Utility_In ErrorType A_ErrorType, Utility_In ErrorLevel A_ErrorLevel) : 
        m_OwnerGroup(NULL), 
        m_ErrorType(A_ErrorType), 
        m_ErrorLevel(A_ErrorLevel)
    {}

    Error::~Error()
    {}

    AnGeoString Error::ErrorTypeToString(Utility_In ErrorType A_Type)
    {
        switch (A_Type)
        {
        case etNULL:                return AnGeoString("�޴���");
        case etTopology:            return AnGeoString("���˴���");
        case etRoadConflct:         return AnGeoString("��·��ͻ");
        case etRoadShrinkExcess:    return AnGeoString("����ȹ���");
        case etCoupleLineNotValid:  return AnGeoString("�����߲��Ϸ�");
        default:                    return AnGeoString("δ֪���ʹ���");
        }
    }

    /**
    * @brief 
    * @author ningning.gn
    * @remark
    **/
    AnGeoString ErrorTopology::GetDescription() const
    {
        switch (m_TopologyErrorType)
        {
        case tetDataEmpty:
            return AnGeoString("����Ϊ��");
        case tetNodeMismatch:
            return StringTools::Format("�ڵ�λ�ò�ƥ�� [%s] �߲�: %0.2fm",
                UniqueIdTools::UniqueIdToIdsString(m_ItemIdA).c_str(), m_HeightDiff);
        case tetRoadSampleLack:
            return StringTools::Format("��·�����㲻�� [%s]",
                UniqueIdTools::UniqueIdToIdsString(m_ItemIdA).c_str());
        case tetNodeOverlap:
            return StringTools::Format("�����ڵ��غ� [%s]-[%s]",
                UniqueIdTools::UniqueIdToIdsString(m_ItemIdA).c_str(),
                UniqueIdTools::UniqueIdToIdsString(m_ItemIdB).c_str());
        case tetRoadIdRepeated:
            return StringTools::Format("��· Id �ظ� [%s]",
                UniqueIdTools::UniqueIdToIdsString(m_ItemIdA).c_str());
        case tetRoadSampleOverlap:
            return StringTools::Format("��·�������ص� [%s]",
                UniqueIdTools::UniqueIdToIdsString(m_ItemIdA).c_str());
        default:
            return StringTools::Format("δ֪�������˴��� [%s]",
                UniqueIdTools::UniqueIdToIdsString(m_ItemIdA).c_str());
        }
    }

    void ErrorTopology::SetDataEmpty()
    {
        m_TopologyErrorType = tetDataEmpty;
    }

    void ErrorTopology::SetNodeMismatch(Utility_In Guint64 A_NodeId, Utility_In Gdouble A_HeightDiff)
    {
        m_ItemIdA = A_NodeId; 
        m_HeightDiff = A_HeightDiff; 
        m_TopologyErrorType = tetNodeMismatch;
    }

    Gbool ErrorTopology::GetNodeMismatchDetail(
        Utility_Out Guint64& A_NodeId,
        Utility_Out Gdouble& A_HeightDiff)
    {
        if (m_TopologyErrorType == tetNodeMismatch)
        {
            A_NodeId = m_ItemIdA;
            A_HeightDiff = m_HeightDiff;
            return true;
        }
        return false;
    }

    void ErrorTopology::SetRoadSampleLack(Utility_In Guint64 A_RoadId)
    {
        m_ItemIdA = A_RoadId; 
        m_TopologyErrorType = tetRoadSampleLack;
    }

    Gbool ErrorTopology::GetRoadSampleLackDetail(Utility_Out Guint64& A_RoadId)
    {
        if (m_TopologyErrorType == tetRoadSampleLack)
        {
            A_RoadId = m_ItemIdA;
            return true;
        }
        return false;
    }

    void ErrorTopology::SetNodeOverlap(Utility_In Guint64 A_NodeIdA, Utility_In Guint64 A_NodeIdB)
    {
        m_ItemIdA = A_NodeIdA;
        m_ItemIdB = A_NodeIdB;
        m_TopologyErrorType = tetNodeOverlap;
    }

    Gbool ErrorTopology::GetNodeOverlapDetail(
        Utility_Out Guint64& A_NodeIdA, Utility_Out Guint64& A_NodeIdB)
    {
        if (m_TopologyErrorType == tetNodeOverlap)
        {
            A_NodeIdA = m_ItemIdA;
            A_NodeIdB = m_ItemIdB;
            return true;
        }
        return false;
    }

    void ErrorTopology::SetRoadIdRepeated(Utility_In Guint64 A_RoadId)
    {
        m_ItemIdA = A_RoadId;
        m_TopologyErrorType = tetRoadIdRepeated;
    }

    Gbool ErrorTopology::GetRoadIdRepeatedDetail(Utility_Out Guint64& A_RoadId)
    {
        if (m_TopologyErrorType == tetRoadIdRepeated)
        {
            A_RoadId = m_ItemIdA;
            return true;
        }
        return false;
    }

    void ErrorTopology::SetRoadSampleOverlap(Utility_In Guint64 A_RoadId)
    {
        m_ItemIdA = A_RoadId;
        m_TopologyErrorType = tetRoadSampleOverlap;
    }

    Gbool ErrorTopology::GetRoadSampleOverlapDetail(Utility_Out Guint64& A_RoadId)
    {
        if (m_TopologyErrorType == tetRoadSampleOverlap)
        {
            A_RoadId = m_ItemIdA;
            return true;
        }
        return false;
    }

    Gbool ErrorTopology::Equal(Utility_In ErrorPtr A_Other) const
    {
		ROAD_ASSERT(A_Other);
        if (A_Other == NULL || A_Other->GetErrorType() != GetErrorType())
            return false;

        ErrorTopologyPtr oOtherTopo = DynamicTypeCast<ErrorTopologyPtr>(A_Other);
        return (*this) == (*oOtherTopo);
    }

    bool ErrorTopology::operator == (Utility_In ErrorTopology& A_Other) const
    {
        if (m_TopologyErrorType == tetDataEmpty)
            return true;
        else if (m_TopologyErrorType == tetNodeOverlap)
        {
            return m_ItemIdA == A_Other.m_ItemIdA && m_ItemIdB == A_Other.m_ItemIdB;
        }
        else
        {
            return (m_TopologyErrorType == A_Other.m_TopologyErrorType) &&
                (m_ItemIdA == A_Other.m_ItemIdA);
        }
    }

    /** 
    * @brief ·���ߴ���
    * @author ningning.gn
    * @remark
    **/
    ErrorJunctionInvalid::ErrorJunctionInvalid() : 
        Error(etJunctionInvalid, elWarning), 
        m_JunctionErrorType(jetNULL)
    {}

    void ErrorJunctionInvalid::SetTinyBufferLine(
        Utility_In Guint64& A_RoadId, Utility_In GEO::Vector& A_Pos)
    {
        m_JunctionErrorType = jetTinyBufferLine;
        m_ErrorLevel = elWarning;
        m_RoadId = A_RoadId;
        m_ErrorPos = A_Pos;
    }

    Gbool ErrorJunctionInvalid::Equal(Utility_In ErrorPtr A_Other) const
    {
		ROAD_ASSERT(A_Other);
		if (A_Other == NULL || A_Other->GetErrorType() != GetErrorType())
            return false;

        ErrorJunctionInvalidPtr oOtherConf = DynamicTypeCast<ErrorJunctionInvalidPtr>(A_Other);
        return (oOtherConf->m_RoadId == m_RoadId) && 
            (m_ErrorPos.Equal(oOtherConf->m_ErrorPos, GEO::Constant::Epsilon()));
    }

    AnGeoString ErrorJunctionInvalid::GetDescription() const
    {
        switch (m_JunctionErrorType)
        {
        case jetTinyBufferLine:
            return AnGeoString(StringTools::Format("·�ڻ����߹��� %s",
                UniqueIdTools::UniqueIdToIdsString(m_RoadId).c_str()));
        default:
            return AnGeoString("δ֪����·�ڴ���");
        }
    }

    /**
    * @brief �����߲��Ϸ�
    * @author ningning.gn
    * @remark
    **/
    AnGeoString ErrorCoupleLineNotValid::GetDescription() const
    {
        switch (m_ErrorType)
        {
        case cetTerminalDispart:
            return StringTools::Format("�������յ���� %s %s", m_ErrorDesc.c_str(),
                StringTools::VectorToString(m_ErrorPositoin).c_str());
        case cetCoupleLineDispart:
            return StringTools::Format("�����߷��� %s %s", m_ErrorDesc.c_str(),
                StringTools::VectorToString(m_ErrorPositoin).c_str());
        case cetTinyCoupleCenter:
            return StringTools::Format("�����߹��� %s %s", m_ErrorDesc.c_str(),
                StringTools::VectorToString(m_ErrorPositoin).c_str());
        default:
            return AnGeoString("δ֪�������˴���");
        }
    }

    /**
    * @brief 
    * @author ningning.gn
    * @remark
    **/
    ErrorGroup::ErrorGroup(
        Utility_In ErrorCollectorPtr A_OwnerCollector,
        Utility_In ErrorType A_ErrorType) : 
        m_OwnerCollector(A_OwnerCollector), 
        m_ErrorType(A_ErrorType)
    {
        m_GroupName = Error::ErrorTypeToString(A_ErrorType);
    }

    ErrorGroup::~ErrorGroup()
    {}

    void ErrorGroup::AddError(Utility_In ErrorPtr A_Error)
    {
		ROAD_ASSERT(A_Error);
		if (A_Error == NULL)
			return;

        if (A_Error->GetErrorType() != m_ErrorType)
        {
            delete A_Error;
            return;
        }

		Guint64 nErrorSize = m_ErrorArr.GetSize();
		for (Guint32 i = 0; i < nErrorSize; i++)
        {
            if (m_ErrorArr[i]->Equal(A_Error))
            {
                delete A_Error;
                return;
            }
        }

        A_Error->m_OwnerGroup = this;
        m_ErrorArr.Add(A_Error);
    }

    /**
    * @brief 
    * @author ningning.gn
    * @remark
    **/
    ErrorRoadConflcit::ErrorRoadConflcit(
        Utility_In Guint64& A_UniqueIdRoadA,
        Utility_In Guint64& A_UniqueIdRoadB,
        Utility_In GEO::Vector& A_ConflictPos) : 
        Error(etRoadConflct, elWarning),
        m_UniqueIdRoadA(A_UniqueIdRoadA),
        m_UniqueIdRoadB(A_UniqueIdRoadB),
        m_ConflictPos(A_ConflictPos)
    {}

    AnGeoString ErrorRoadConflcit::GetDescription() const
    {
        return StringTools::Format("��·��ͻ [%s]-[%s]",
            UniqueIdTools::UniqueIdToIdsString(m_UniqueIdRoadA).c_str(),
            UniqueIdTools::UniqueIdToIdsString(m_UniqueIdRoadB).c_str());
    }

    Gbool ErrorRoadConflcit::Equal(Utility_In ErrorPtr A_Other) const
    {
		ROAD_ASSERT(A_Other);
        if (A_Other == NULL || A_Other->GetErrorType() != GetErrorType())
            return false;

        ErrorRoadConflcitPtr oOtherConf = DynamicTypeCast<ErrorRoadConflcitPtr>(A_Other);
        return (*this) == (*oOtherConf);
    }

    bool ErrorRoadConflcit::operator == (Utility_In ErrorRoadConflcit& A_Other) const
    {
        return (m_UniqueIdRoadA == A_Other.m_UniqueIdRoadA &&
            m_UniqueIdRoadB == A_Other.m_UniqueIdRoadB) ||
            (m_UniqueIdRoadA == A_Other.m_UniqueIdRoadB &&
            m_UniqueIdRoadB == A_Other.m_UniqueIdRoadA);
    }

    /**
    * @brief ��·����
    * @author ningning.gn
    * @remark
    **/
    ErrorRoadShinkExcess::ErrorRoadShinkExcess(
        Utility_In Guint64& A_RoadUniqueId, 
        Utility_In ErrorLevel A_ErrorLevel) :
        Error(etRoadShrinkExcess, A_ErrorLevel),
        m_RoadUniqueId(A_RoadUniqueId) 
    {}

    AnGeoString ErrorRoadShinkExcess::GetDescription() const
    {
        return StringTools::Format("����ȹ��� [%s]",
            UniqueIdTools::UniqueIdToIdsString(m_RoadUniqueId).c_str());
    }

    Gbool ErrorRoadShinkExcess::Equal(Utility_In ErrorPtr A_Other) const
    {
		ROAD_ASSERT(A_Other);
        if (A_Other == NULL || A_Other->GetErrorType() != GetErrorType())
            return false;

        ErrorRoadShinkExcessPtr oOtherExce = DynamicTypeCast<ErrorRoadShinkExcessPtr>(A_Other);
        return m_RoadUniqueId == oOtherExce->m_RoadUniqueId;
    }

    /**
    * @brief 
    * @author ningning.gn
    * @remark
    **/
    ErrorCollector::ErrorCollector() : m_QuitErrorLevel(elNormalError)
    {}

    ErrorGroupPtr ErrorCollector::ForceGetErrorGroup(Utility_In ErrorType A_Type)
    {
        AnGeoMap<ErrorType, ErrorGroupPtr>::const_iterator it = m_GroupMap.find(A_Type);
        if (it != m_GroupMap.end())
        {
            return (*it).second;
        }
        else
        {
            ErrorGroupPtr oGroup = new ErrorGroup(this, A_Type);
            m_GroupArr.Add(oGroup);
            m_GroupMap.insert(STL_NAMESPACE::make_pair(A_Type, oGroup));
            return oGroup;
        }
    }

    ErrorGroupPtr ErrorCollector::GetErrorGroup(Utility_In ErrorType A_Type) const
    {
        AnGeoMap<ErrorType, ErrorGroupPtr>::const_iterator it = m_GroupMap.find(A_Type);
        if (it != m_GroupMap.end())
        {
            return (*it).second;
        }
        return NULL;
    }

    void ErrorCollector::Clear()
    {
        m_GroupMap.clear();
        m_GroupArr.Clear();
    }

//     AnGeoString ErrorCollector::GetDescriptions() const
//     {
//         AnGeoString sResult;
//         for (Gint32 i = 0; i < m_GroupArr.GetSize(); i++)
//         {
//             ErrorGroupPtr oErrorGroup = m_GroupArr[i];
//             for (Gint32 j = 0; j < oErrorGroup->GetErrorCount(); j++)
//             {
//                 ErrorPtr oError = oErrorGroup->GetErrorAt(j);
//                 sResult += oError->GetDescription() + "\r\n";
//             }
//         }
//         return sResult;
//     }

    void ErrorCollector::GetAllErrorItems(Utility_Out AnGeoVector<ErrorPtr>& A_ErrorArr) const
    {
        A_ErrorArr.clear();
		Guint64 nGroupSize = m_GroupArr.GetSize();
		for (Guint32 i = 0; i < nGroupSize; i++)
        {
            ErrorGroupPtr oErrorGroup = m_GroupArr[i];
			Guint32 nErrorSize = oErrorGroup->GetErrorCount();
			for (Guint32 j = 0; j < nErrorSize; j++)
            {
                A_ErrorArr.push_back(oErrorGroup->GetErrorAt((Gint32)j));
            }
        }
    }

    Gbool ErrorCollector::IsEmpty() const
    {
		Guint32 nGroupSize = m_GroupArr.GetSize();
		for (Guint32 i = 0; i < nGroupSize; i++)
        {
            ErrorGroupPtr oErrorGroup = m_GroupArr[i];
            if (oErrorGroup->GetErrorCount() > 0)
                return false;
        }
        return true;
    }

    // ��ȡ�������Ĵ�����
    ErrorType ErrorCollector::GetSignificantErrorType() const
    {
        ErrorLevel eSignificantErrLevel = elNULL;
        ErrorType eErrorType = etNULL;

        AnGeoVector<ErrorPtr> oErrorArr;
        GetAllErrorItems(oErrorArr);
		Guint32 nErrorSize = oErrorArr.size();
		for (Guint32 i = 0; i < nErrorSize; i++)
        {
            ErrorLevel eErrorLevel = oErrorArr[i]->GetErrorLevel();
            if (eErrorLevel > eSignificantErrLevel)
            {
                eSignificantErrLevel = eErrorLevel;
                eErrorType = oErrorArr[i]->GetErrorType();
            }
        }

        return eErrorType;
    }

    Gbool ErrorCollector::NeedToQuit() const
    {
        //return false;

        ErrorLevel eSignificantErrLevel = elNULL;

        // ��ͻ�㳬���������ش���
        ErrorGroupPtr oGroup = GetErrorGroup(etRoadConflct);
        if (oGroup != NULL && oGroup->GetErrorCount() > 2)
            return true;

//         oGroup = GetErrorGroup(etRoadShrinkExcess);
//         if (oGroup != NULL && oGroup->GetErrorCount() >= 2)
//             return true;

        AnGeoVector<ErrorPtr> oErrorArr;
        GetAllErrorItems(oErrorArr);
        Gint32 nCount = (Gint32)oErrorArr.size();
        for (Gint32 i = 0; i < nCount; i++)
        {
            ErrorLevel eErrorLevel = oErrorArr[i]->GetErrorLevel();
            if (eErrorLevel > eSignificantErrLevel)
            {
                eSignificantErrLevel = eErrorLevel;
            }
        }

        return eSignificantErrLevel >= m_QuitErrorLevel;
    }

}//end ROADGEN
