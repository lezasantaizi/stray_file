/*-----------------------------------------------------------------------------
                                 ���λ�����Ԫ
    ���ߣ����� 2016/05/11
    ��ע��
    ��ˣ�

-----------------------------------------------------------------------------*/
#pragma once

#include "Common.h"

namespace GEO
{
    /**
    * @brief �������ع��߼�
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT PolylineTools
    {
    private:
        PolylineTools() {}

    public:
        // �������ߵĴ��λ��
        static GEO::Vector CalcPolyLineBreakPoint(
            Utility_In RoadBreakPoint& A_BreakPoint, Utility_In GEO::VectorArray& A_Samples);
        static GEO::Vector3 CalcPolyLineBreakPoint(
            Utility_In RoadBreakPoint& A_BreakPoint, Utility_In GEO::VectorArray3& A_Samples);

        // ��ȡ�������ʼ����, ���Ϊ��λ����,    Start->-------------------End
        // ����߶γ���Ϊ 0, ��û�з���, ���� (0, 0, 0)
        static GEO::Vector GetStartDirection(Utility_In GEO::VectorArray& A_VectorArr);
        static GEO::Vector3 GetStartDirection(Utility_In GEO::VectorArray3& A_VectorArr);

        // ��ȡ�������ֹ����, ���Ϊ��λ����,    Start-------------------<-End
        // ����߶γ���Ϊ 0, ��û�з���, ���� (0, 0, 0)
        static GEO::Vector GetEndDirection(Utility_In GEO::VectorArray& A_VectorArr);
        static GEO::Vector3 GetEndDirection(Utility_In GEO::VectorArray3& A_VectorArr);

        // ��ȡ��ϵ�λ�õķ��� Start-------->------------End
        static GEO::Vector GetBreakPointDirection(Utility_In RoadBreakPoint& A_BreakPt,
            Utility_In GEO::VectorArray& A_VectorArr);

        static GEO::Vector3 GetBreakPointDirection(Utility_In RoadBreakPoint& A_BreakPt,
            Utility_In GEO::VectorArray3& A_VectorArr);

        // ��ȡ����߳���
        static Gdouble CalcPolylineLength(Utility_In GEO::VectorArray& A_VectorArr);
        static Gdouble CalcPolylineLength(Utility_In GEO::VectorArray3& A_VectorArr);

        static void Inverse2D(Utility_InOut GEO::VectorArray& A_VectorArr);
        static void Inverse3D(Utility_InOut GEO::VectorArray3& A_VectorArr);

        // ���㶥�����������, ���ض���߳���(��ά)
        static Gdouble CalcPolylineIntrinsicLength(Utility_In GEO::VectorArray& A_VectorArr,
            Utility_Out AnGeoVector<Gdouble>& A_VertexIntrinsicLength);

        // ���㶥�����������, ���ض���߳���(��ά)
        static Gdouble CalcPolylineIntrinsicLength(Utility_In GEO::VectorArray3& A_VectorArr,
            Utility_Out AnGeoVector<Gdouble>& A_VertexIntrinsicLength);

        // �е���ʼ��һ��
        static Gbool CutHead(Utility_InOut GEO::VectorArray3& A_VectorArr, Utility_In Gdouble A_Length);
        static Gbool CutTail(Utility_InOut GEO::VectorArray3& A_VectorArr, Utility_In Gdouble A_Length);

        static void ExtendHead(Utility_InOut GEO::VectorArray3& A_VectorArr, Utility_In Gdouble A_Length);
        static void ExtendTail(Utility_InOut GEO::VectorArray3& A_VectorArr, Utility_In Gdouble A_Length);

        static void ExtendHead(Utility_InOut GEO::VectorArray& A_VectorArr, Utility_In Gdouble A_Length);
        static void ExtendTail(Utility_InOut GEO::VectorArray& A_VectorArr, Utility_In Gdouble A_Length);
        
        // ��ȡ��ά������е�һ����
        static void CalcRangeSamples(Utility_In RoadItemRange& A_Range,
            Utility_In GEO::VectorArray& A_Samples, Utility_Out GEO::VectorArray& A_Result);
        static void CalcRangeSamples(Utility_In RoadBreakPoint& A_Start, Utility_In RoadBreakPoint& A_End,
            Utility_In GEO::VectorArray& A_Samples, Utility_Out GEO::VectorArray& A_Result);

        // ��ȡ��ά������е�һ����
        static void CalcRangeSamples(Utility_In RoadItemRange& A_Range,
            Utility_In GEO::VectorArray3& A_Samples, Utility_Out GEO::VectorArray3& A_Result);
        static void CalcRangeSamples(Utility_In RoadBreakPoint& A_Start, Utility_In RoadBreakPoint& A_End,
            Utility_In GEO::VectorArray3& A_Samples, Utility_Out GEO::VectorArray3& A_Result);

        // ��ά����, ���ҿ�Ⱦ�Ϊ��ֵ
        static void ExpandLine(Utility_In GEO::VectorArray& A_Samples,
            Utility_In Gdouble A_WidthLeft, Utility_In Gdouble A_WidthRight,
            Utility_Out GEO::VectorArray& A_LeftLine, Utility_Out GEO::VectorArray& A_RightLine);

        // ��ά������ˮƽ������, ���ҿ�Ⱦ�Ϊ��ֵ
        static void ExpandLine(Utility_In GEO::VectorArray3& A_Samples,
            Utility_In Gdouble A_WidthLeft, Utility_In Gdouble A_WidthRight,
            Utility_Out GEO::VectorArray3& A_LeftLine, Utility_Out GEO::VectorArray3& A_RightLine);

        // ����ƫ��
        static void OffsetSelf(Utility_InOut GEO::VectorArray3& A_Samples, Utility_In Gdouble A_RightOffSetDis);
        static void OffsetSelf(Utility_InOut GEO::VectorArray& A_Samples, Utility_In Gdouble A_RightOffSetDis);

        // ����ˮƽ����
        static void CalcHorizontalNormals(
            Utility_In GEO::VectorArray& A_Samples, Utility_Out GEO::VectorArray& A_HorNormals);
        static void CalcHorizontalNormals(
            Utility_In GEO::VectorArray3& A_Samples, Utility_Out GEO::VectorArray& A_HorNormals);

        // �����е�
        static GEO::Vector CalcMidWayPoint(Utility_In GEO::VectorArray& A_Samples);
        static GEO::Vector3 CalcMidWayPoint(Utility_In GEO::VectorArray3& A_Samples);

        // ��������ĳ��Χ�ĳ���
        static Gdouble CalcPolyLineRangeLength(Utility_In RoadItemRange& A_Range, Utility_In GEO::VectorArray3& A_Samples);

        // �����ϵ���ߵĶ���߳���
        static Gdouble CalcPolyLineLeftLength(Utility_In RoadBreakPoint& A_BreakPoint, Utility_In GEO::VectorArray& A_Samples);
        static Gdouble CalcPolyLineLeftLength(Utility_In RoadBreakPoint& A_BreakPoint, Utility_In GEO::VectorArray3& A_Samples);

        // �����ϵ��ұߵĶ���߳���
        static Gdouble CalcPolyLineRightLength(Utility_In RoadBreakPoint& A_BreakPoint, Utility_In GEO::VectorArray& A_Samples);
        static Gdouble CalcPolyLineRightLength(Utility_In RoadBreakPoint& A_BreakPoint, Utility_In GEO::VectorArray3& A_Samples);

    };//end PolylineTools

    /**
    * @brief �����ĸ�ʽת��
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT VectorTools
    {
    private:
        VectorTools() {}

    public:
        // ��ά��ά����ת��
        static GEO::Vector3 TVector2dTo3d(Utility_In GEO::Vector& A_Point, Utility_In Gdouble A_Z = 0.0);
        static GEO::Vector Vector3dTo2d(Utility_In GEO::Vector3& A_Point);

        // ���������ά��άת��
        static void VectorArray2dTo3d(Utility_In GEO::VectorArray& A_Samples, Utility_Out GEO::VectorArray3& A_Sample3, Utility_In Gdouble A_Height = 0.0);
        static void VectorArray3dTo2d(Utility_In GEO::VectorArray3& A_Samples, Utility_Out GEO::VectorArray& A_Sample2);

        // ׷������
        static void AppendArray(Utility_InOut GEO::VectorArray& A_Samples, Utility_In GEO::VectorArray3& A_Append);
        static void AppendArray(Utility_InOut GEO::VectorArray& A_Samples, Utility_In GEO::VectorArray& A_Append);
        
        static void AppendArrayInv(Utility_InOut GEO::VectorArray& A_Samples, Utility_In GEO::VectorArray3& A_Append);
        static void AppendArrayInv(Utility_InOut GEO::VectorArray& A_Samples, Utility_In GEO::VectorArray& A_Append);

        static void AppendArrayWithoutFirst(Utility_InOut GEO::VectorArray& A_Samples, Utility_In GEO::VectorArray3& A_Append);
        static void AppendArrayWithoutFirst(Utility_InOut GEO::VectorArray& A_Samples, Utility_In GEO::VectorArray& A_Append);
        
        static void AppendArrayInvWithoutFirst(Utility_InOut GEO::VectorArray& A_Samples, Utility_In GEO::VectorArray3& A_Append);
        static void AppendArrayInvWithoutFirst(Utility_InOut GEO::VectorArray& A_Samples, Utility_In GEO::VectorArray& A_Append);
        
        static void AppendArray3(Utility_InOut GEO::VectorArray3& A_Samples, Utility_In GEO::VectorArray3& A_Append);

        // ��������, ��Ϊ����ֵ
        static inline GEO::Vector3 GetErrorVector3() { return GEO::Vector3(1e50, 1e50, 1e50); }
        static inline Gbool IsErrorVector(Utility_In GEO::Vector3& A_Vec) { return A_Vec.x > 1e30; }

        // ��ת�� (����)
        static GEO::Vector RotatePoint(
            Utility_In GEO::Vector& A_SrcPt,    // ����ת�ĵ�
            Utility_In GEO::Vector& A_OriPt,    // ��׼��
            Utility_In Gdouble A_Angle);          // ��ת����

        // ��ת���� (����)
        static GEO::Vector RotateVector(
            Utility_In GEO::Vector& A_SrcVector, Utility_In Gdouble A_Angle);

        // ͨ����γ�������ķ���
        static GEO::Vector3 SphereDirection(Utility_In Gdouble A_HorAngle, Utility_In Gdouble A_VerAngle);

        // �ж��Ƿ�ͬ��
        static Gbool IsSameDirection(
            Utility_In GEO::Vector& A_DirA, Utility_In GEO::Vector& A_DirB, 
            Utility_In Gdouble A_AngleEpsilon = TMath_d::s_epsilonAngle);

        // �ж��Ƿ�ͬ�� �ȹ�һ
        static Gbool IsSameDirectionN(
            Utility_In GEO::Vector& A_DirA, Utility_In GEO::Vector& A_DirB,
			Utility_In Gdouble A_AngleEpsilon = TMath_d::s_epsilonAngle);

        // �ж��Ƿ���
        static Gbool IsOppositeDirection(
            Utility_In GEO::Vector& A_DirA, Utility_In GEO::Vector& A_DirB, 
			Utility_In Gdouble A_AngleEpsilon = TMath_d::s_epsilonAngle);

        // �ж��Ƿ��� �ȹ�һ
        static Gbool IsOppositeDirectionN(
            Utility_In GEO::Vector& A_DirA, Utility_In GEO::Vector& A_DirB,
			Utility_In Gdouble A_AngleEpsilon = TMath_d::s_epsilonAngle);

    };//end VectorConvertTools

    enum PtLineRelationship
    {
        plrInner, plrOuterStart, plrOuterEnd
    };

    /**
    * @brief ��ά�߶�
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT Segment
    {
    private:
        GEO::Vector m_StartPt;
        GEO::Vector m_EndPt;

    public:
        Segment() {}
        Segment(Utility_In GEO::Vector& A_StartPt, Utility_In GEO::Vector& A_EndPt) : m_StartPt(A_StartPt), m_EndPt(A_EndPt) {}

        inline void SetValue(Utility_In GEO::Vector& A_StartPt, Utility_In GEO::Vector& A_EndPt);
        inline void SetStartPt(Utility_In GEO::Vector& A_StartPt) { m_StartPt = A_StartPt; }
        inline void SetEndPt(Utility_In GEO::Vector& A_EndPt) { m_EndPt = A_EndPt; }

        inline const GEO::Vector& GetStartPt() const;
        inline const GEO::Vector& GetEndPt() const;

        // ��������߶ε������, ������������߶εı���λ��, �� �㵽�����ľ���
        GEO::Vector CalcPointSegNearPtEx(
            Utility_In GEO::Vector& A_TestPt, Utility_Out Gdouble& A_Ratio, Utility_Out Gdouble& A_Distance);

    };//end Segment

    /**
    * @brief ��ά�߶�
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT Segment3
    {
    private:
        GEO::Vector3 m_StartPt;
        GEO::Vector3 m_EndPt;

    public:
        Segment3() {}
        Segment3(Utility_In GEO::Vector3& A_StartPt, Utility_In GEO::Vector3& A_EndPt) : m_StartPt(A_StartPt), m_EndPt(A_EndPt) {}

        inline void SetValue(Utility_In GEO::Vector3& A_StartPt, Utility_In GEO::Vector3& A_EndPt);
        inline void SetStartPt(Utility_In GEO::Vector3& A_StartPt) { m_StartPt = A_StartPt; }
        inline void SetEndPt(Utility_In GEO::Vector3& A_EndPt) { m_EndPt = A_EndPt; }

        inline const GEO::Vector3& GetStartPt() const;
        inline const GEO::Vector3& GetEndPt() const;

        // ���������ָ���յ������
        GEO::Vector3 GetDirection() const;

        // ��������߶ε������, ������������߶εı���λ��, �� �㵽�����ľ���
        GEO::Vector3 CalcPointSegNearPtEx(
            Utility_In GEO::Vector3& A_TestPt, Utility_Out Gdouble& A_Ratio, Utility_Out Gdouble& A_Distance);

        PtLineRelationship CalcPointSegNearPt(
            Utility_In GEO::Vector3& A_TestPt, 
            Utility_Out Gdouble& A_Ratio, 
            Utility_Out Gdouble& A_Distance, 
            Utility_Out GEO::Vector3& A_NearPt);

    };//end Segment3

    /**
    * @brief ��άֱ��
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT StraightLine
    {
    private:
        Vector m_Base;
        Vector m_Direction;

    public:
        StraightLine() {}
        inline StraightLine(Utility_In Vector& A_AnchorA, Utility_In Vector& A_AnchorB);

        inline void SetByTwoAnchor(Utility_In Vector& A_AnchorA, Utility_In Vector& A_AnchorB);
        inline void SetByBaseDir(Utility_In Vector& A_Base, Utility_In Vector& A_Direction);

        inline const Vector& GetBase() const;
        inline void GetBase(Utility_Out Gdouble& A_X, Utility_Out Gdouble& A_Y) const;

        inline const Vector& GetDirection() const;
        inline void GetDirection(Utility_Out Gdouble& A_X, Utility_Out Gdouble& A_Y) const;

        inline Vector GetParamPosition(Utility_In Gdouble A_Lambda) const;

        // ����ӳ�䵽ֱ����
        Vector Project(Utility_In Vector& A_Point) const;

    };//end StraightLine

    /**
    * @brief ��άֱ��
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT StraightLine3
    {
    private:
        Vector3 m_Base;
        Vector3 m_Direction;

    public:
        StraightLine3() : m_Direction(0.0, 0.0, 1.0) {}
        inline StraightLine3(Utility_In Vector3& A_AnchorA, Utility_In Vector3& A_AnchorB);

        inline void SetByTwoAnchor(Utility_In Vector3& A_AnchorA, Utility_In Vector3& A_AnchorB);
        inline void SetByBaseDir(Utility_In Vector3& A_Base, Utility_In Vector3& A_Direction);

        inline const Vector3& GetBase() const;
        inline void GetBase(Utility_Out Gdouble& A_X, Utility_Out Gdouble& A_Y, Gdouble& A_Z) const;

        inline const Vector3& GetDirection() const;
        inline void GetDirection(Utility_Out Gdouble& A_X, Utility_Out Gdouble& A_Y, Gdouble& A_Z) const;

        inline Vector3 GetParamPosition(Utility_In Gdouble A_Lambda) const;

        // ����ӳ�䵽ֱ����
        Vector3 Project(Utility_In Vector3& A_Point) const;

    };//end StraightLine3

    /**
    * @brief ƽ��
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT Plane
    {
    private:
        Vector3 m_Base;
        Vector3 m_Normal;

    public:
        Plane() : m_Normal(0.0, 0.0, 1.0) {}
        Plane(Utility_In Vector3& A_Base, Utility_In Vector3& A_Normal) : m_Base(A_Base), m_Normal(A_Normal) {}

        void SetValue(Utility_In Vector3& A_Base, Utility_In Vector3& A_Normal);

        // ���㴹ֱӳ�䵽ƽ��
        Vector3 Project(Utility_In Vector3& A_Point) const;

    };//end Plane

    /**
    * @brief �ֲ��ѿ������
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT LocalCoord
    {
    private:
        Vector3 m_Origin;
        Vector3 m_AxisX;
        Vector3 m_AxisY;
        Vector3 m_AxisZ;

    public:
        inline LocalCoord();
        inline LocalCoord(Utility_In Vector3& A_Origin, Utility_In Vector3& A_AxisX, Utility_In Vector3& A_AxisY, Utility_In Vector3& A_AxisZ);

        // ��������
        inline void SetOirgin(Utility_In Vector3& A_Origin);
        inline void SetAxes(Utility_In Vector3& A_AxisX, Utility_In Vector3& A_AxisY, Utility_In Vector3& A_AxisZ);

        // ������ȡ
        inline const Vector3& GetOrigin() const;
        inline void GetAxes(Utility_Out Vector3& A_AxisX, Utility_Out Vector3& A_AxisY, Utility_Out Vector3& A_AxisZ) const;

        // �Ϸ�����֤
        Gbool CheckSelf() const;

        // ȫ����ֲ������ת��
        inline Vector3 GlobalToLocal(Utility_In Vector3& A_Point) const;
        inline Vector3 LocalToGlobal(Utility_In Vector3& A_Point) const;

        // ȫ����ֲ������ת��
        void GlobalToLocal(Utility_InOut VectorArray3& A_PointArr) const;
        void LocalToGlobal(Utility_InOut VectorArray3& A_PointArr) const;

    };//end LocalCoord

    /**
    * @brief ��ά�����
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT Polyline
    {
    private:
        GEO::VectorArray m_Samples;

    public:
        Polyline(){}
        Polyline(Utility_In GEO::VectorArray A_Samples) : m_Samples(A_Samples) {}

        inline void Add(Utility_In GEO::Vector& A_Sample) { m_Samples.push_back(A_Sample); }
        inline void Clear() { m_Samples.clear(); }

        GEO::VectorArray& GetSamples() { return m_Samples; }

        inline void SetValue(Utility_In GEO::VectorArray& A_Samples) { m_Samples = A_Samples; }

        inline Gint32 GetSize() const { return Gint32(m_Samples.size()); }
        inline void SetAt(Utility_In Gint32 A_Index, Utility_In GEO::Vector& A_Sample) { m_Samples[A_Index] = A_Sample; }

        const GEO::Vector& operator [] (Utility_In Gint32 A_Index) const { return m_Samples[A_Index]; }
        GEO::Vector& operator [] (Utility_In Gint32 A_Index) { return m_Samples[A_Index]; }

        // ��ȡ�������ʼ����, ���Ϊ��λ����,    Start->-------------------End
        // ����߶γ���Ϊ 0, ��û�з���, ���� (0, 0, 0)
        GEO::Vector GetStartDirection() const;

        // ��ȡ�������ֹ����, ���Ϊ��λ����,    Start-------------------<-End
        // ����߶γ���Ϊ 0, ��û�з���, ���� (0, 0, 0)
        GEO::Vector GetEndDirection() const;

        // ��ȡ����߳���
        Gdouble CalcLength() const;

        // ����
        void ExpandLine(Utility_In Gdouble A_WidthLeft, Utility_In Gdouble A_WidthRight,
            Utility_Out Polyline& A_LeftLine, Utility_Out Polyline& A_RightLine);

    };//end Polyline

    /**
    * @brief ��ά�����
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT Polyline3
    {
    private:
        GEO::VectorArray3 m_Samples;

    public:
        Polyline3(){}
        Polyline3(Utility_In GEO::VectorArray3& A_Samples) : m_Samples(A_Samples) {}

        inline void AddSample(Utility_In GEO::Vector3& A_Sample) { m_Samples.push_back(A_Sample); }
        void AddDistinctSample(Utility_In GEO::Vector3& A_Sample);

        inline void SetValue(Utility_In GEO::VectorArray3& A_Samples) { m_Samples = A_Samples; }

        // ׷��
        void Append(Utility_In Polyline3& A_OtherLine, Utility_In Gbool A_IgnorFirstSample = false);
        void AppendInv(Utility_In Polyline3& A_OtherLine, Utility_In Gbool A_IgnorFirstSample = false);

        // ����
        void InverseSelf();

        inline void Clear() { m_Samples.clear(); }

        // ���ò�������Ŀ
        inline void Resize(Utility_In Gint32 A_Size) { m_Samples.resize(A_Size); }

        inline GEO::VectorArray3& GetSamples() { return m_Samples; }
        inline const GEO::VectorArray3& GetSamples() const { return m_Samples; }

        inline Gint32 GetSampleCount() const { return Gint32(m_Samples.size()); }
        inline void SeSampletAt(Utility_In Gint32 A_Index, Utility_In GEO::Vector3& A_Sample) { m_Samples[A_Index] = A_Sample; }

        const GEO::Vector3& operator [] (Utility_In Gint32 A_Index) const { return m_Samples[A_Index]; }
        GEO::Vector3& operator [] (Utility_In Gint32 A_Index) { return m_Samples[A_Index]; }

        GEO::Vector GetSample2D(Utility_In Gint32 A_Index) const { return GEO::VectorTools::Vector3dTo2d(m_Samples[A_Index]); }

        Gint32 GetSegmentCount() const;
        Segment3 GetSegmentAt(Utility_In Gint32 A_Index) const;
        Gbool GetSegmentAt(Utility_In Gint32 A_Index, 
            Utility_Out GEO::Vector3& A_Start, Utility_Out GEO::Vector3& A_End) const;

        // ��ȡ�������ʼ����, ���Ϊ��λ����,    Start->-------------------End
        // ����߶γ���Ϊ 0, ��û�з���, ���� (0, 0, 0)
        GEO::Vector3 GetStartDirection() const;

        // ��ȡ�������ֹ����, ���Ϊ��λ����,    Start-------------------<-End
        // ����߶γ���Ϊ 0, ��û�з���, ���� (0, 0, 0)
        GEO::Vector3 GetEndDirection() const;

        Gbool CalcSampleDirection(Utility_In Gint32 A_Index,
            Utility_Out GEO::Vector3& A_DirPrev, Utility_Out GEO::Vector3& A_DirNext) const;

        GEO::Vector3 CalcSegmentDirection(Utility_In Gint32 A_SegIndex) const;

        GEO::Vector3 GetFirstSample() const;
        GEO::Vector3 GetLastSample() const;

        void MoveFirstSample(Utility_In GEO::Vector3& A_NewPos);
        void MoveLastSample(Utility_In GEO::Vector3& A_NewPos);

        GEO::Box CalcBox() const;
        GEO::Vector3 CalcHalfWayPt() const;

        // ��ȡ����߳���
        Gdouble CalcLength() const;

        void CalcRangeSamples(Utility_In RoadBreakPoint& A_Start, Utility_In RoadBreakPoint& A_End,
            Utility_Out GEO::VectorArray3& A_Result) const;

        // ������������
        void ExpandLine(Utility_In Gdouble A_WidthLeft, Utility_In Gdouble A_WidthRight,
            Utility_Out GEO::Polyline3& A_LeftLine, Utility_Out GEO::Polyline3& A_RightLine) const;

        // �������ߵĴ��λ��
        GEO::Vector3 CalcBreakPoint(Utility_In RoadBreakPoint& A_BreakPoint) const;

        // ���㶥�����������, ���ض���߳���(��ά)
        Gdouble CalcPolylineIntrinsicLength(Utility_Out AnGeoVector<Gdouble>& A_VertexIntrinsicLength) const;

        // ����㵽����ߵľ���
        PtLineRelationship CalcNearPtToTestPoint(
            Utility_In GEO::Vector3& A_TestPt,
            Utility_Out RoadBreakPoint& A_BreakPt,
            Utility_Out Gdouble& A_Distance,
            Utility_Out GEO::Vector3& A_NearPt) const;

        // �����ϵ�λ��
        RoadBreakPoint GetFirstBreakPoint() const { return RoadBreakPoint(0, 0.0); }
        RoadBreakPoint GetLastBreakPoint() const;
        
    };//end Polyline3

    /**
    * @brief ��������
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT TriangleMesh
    {
    private:
        GEO::VectorArray3 m_Triangles;
        GEO::VectorArray3 m_Normals;
        GEO::VectorArray m_TexCoords;

        GEO::Vector3 CalcNormal(
            Utility_In GEO::Vector3& a, Utility_In GEO::Vector3& b, Utility_In GEO::Vector3& c);

    public:
        TriangleMesh() {}

        void AddTriangle(
            Utility_In GEO::Vector3& a, Utility_In GEO::Vector3& b, Utility_In GEO::Vector3& c,
            Utility_In GEO::Vector& ta, Utility_In GEO::Vector& tb, Utility_In GEO::Vector& tc);

        void AddQuad(
            Utility_In GEO::Vector3& a, Utility_In GEO::Vector3& b, Utility_In GEO::Vector3& c, Utility_In GEO::Vector3& d,
            Utility_In GEO::Vector& ta, Utility_In GEO::Vector& tb, Utility_In GEO::Vector& tc, Utility_In GEO::Vector& td);

        void SmoothNormals();

        inline Gint32 GetTriangleCount() const { return m_Triangles.size() / 3; }

        void GetTriangleAt(Utility_In Gint32 A_Index,
            Utility_Out GEO::Vector3& a, Utility_Out GEO::Vector3& b, Utility_Out GEO::Vector3& c,
            Utility_Out GEO::Vector& ta, Utility_Out GEO::Vector& tb, Utility_Out GEO::Vector& tc) const;

        void GetTriangleAt(Utility_In Gint32 A_Index,
            Utility_Out GEO::Vector3& a, Utility_Out GEO::Vector3& b, Utility_Out GEO::Vector3& c,
            Utility_Out GEO::Vector3& na, Utility_Out GEO::Vector3& nb, Utility_Out GEO::Vector3& nc,
            Utility_Out GEO::Vector& ta, Utility_Out GEO::Vector& tb, Utility_Out GEO::Vector& tc) const;

    };//end TriangleMesh

    /**
    * @brief ����
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT Loft
    {
    private:
        VectorArray m_Section;
        GEO::Vector m_Bias;
        GEO::Vector m_Scale;
        GEO::Vector m_TextureScale;
        GEO::TriangleMesh& m_Mesh;

    public:
        Loft(Utility_Out GEO::TriangleMesh& A_Mesh) :
            m_Scale(1.0, 1.0), m_TextureScale(1.0, 1.0), m_Mesh(A_Mesh) {}

        inline void SetBias(Utility_In GEO::Vector& A_Bias) { m_Bias = A_Bias; }
        inline void SetScale(Utility_In GEO::Vector& A_Scale) { m_Scale = A_Scale; }

        inline void SetTextureScale(Utility_In GEO::Vector& A_Scale) { m_TextureScale = A_Scale; }

        inline void SetSection(Utility_In VectorArray& A_Section) { m_Section = A_Section; }
        void Process(Utility_In VectorArray3& A_LoftLine);

    };//end Loft

}//end GEO

// ��������ֱ�ߵĹ�����
Gbool CalcPerpendicularLine(
    Utility_In GEO::StraightLine3& A_Line1, Utility_In GEO::StraightLine3& A_Line2,
    Utility_Out GEO::StraightLine3& A_Result);

// ��������ֱ�ߵĹ�����, ������������
Gbool CalcPerpendicularLine(
    Utility_In GEO::StraightLine3& A_Line1, Utility_In GEO::StraightLine3& A_Line2,
    Utility_Out GEO::StraightLine3& A_Result,
    Utility_Out GEO::Vector3& A_Foot1, Utility_Out GEO::Vector3& A_Foot2);

namespace GEO
{
    /**
    * @brief ��ϡ�㷨
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT DilutingTool
    {
    public:
        // oVertexArr: ��Ҫ��ϡ�����ߵ�, nStart/nEnd ��ʼ/��ֹ���� A_DelFlag ɾ������
        static void DouglasPeukcer2D(Utility_In GEO::VectorArray& oVertexArr, Utility_In Gint32 nStart,
            Utility_In Gint32 nEnd, Utility_Out AnGeoVector<Gbool>& A_DelFlag, Utility_In Gdouble A_SparseDis);

        // ��ά��ϡ
        static void DouglasPeukcer3D(Utility_In GEO::VectorArray3& oVertexArr, Utility_In Gint32 nStart,
            Utility_In Gint32 nEnd, Utility_Out AnGeoVector<Gbool>& A_DelFlag, Utility_In Gdouble A_SparseDis);

        static void MakeSparce(Utility_InOut GEO::VectorArray3& A_VectorArr, Utility_In Gdouble A_SparseDis);
        static void MakeSparce(
            Utility_In GEO::VectorArray3& A_VectorArr,
            Utility_Out GEO::VectorArray3& A_Result,
            Utility_In Gdouble A_SparseDis);

    };//end DilutingTool

    /**
    * @brief
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT SimplePolygon
    {
    private:
        GEO::Box m_BoundingBox;
        GEO::VectorArray m_VertexArr;

    public:
        void AddVertex(Utility_In GEO::Vector& A_Vertex);
        void Initialize();

        Gbool IsPointInPolygon(Utility_In GEO::Vector& A_Point) const;
        inline const GEO::Box& GetBoundingBox() const { return m_BoundingBox; }

        // �������
        Gdouble CalcArea() const;

        void CalcVertexNormal(Utility_Out GEO::VectorArray& A_Normals) const;
        void SimpleOffset(Utility_In Gdouble A_Distance);

        Gint32 GetVertexCount() const { return m_VertexArr.size(); }
        const Vector& operator [] (Utility_In Gint32 A_Index) const { return m_VertexArr[A_Index]; }
        const Vector& GetVertexAt(Utility_In Gint32 A_Index) const { return m_VertexArr[A_Index]; }

    };//end SimplePolygon

    /**
    * @brief ��ά�����
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT SimplePolygon3
    {
    private:
        GEO::Box m_BoundingBox;
        GEO::VectorArray3 m_VertexArr;

    public:
        void AddVertex(Utility_In GEO::Vector3& A_Vertex);
        void AppendArray( GEO::VectorArray3& vPoints,  Gbool bOrder = true);
        void Initialize();

        inline const GEO::Box& GetBoundingBox() const { return m_BoundingBox; }

        const Vector3& operator [] (Utility_In Gint32 A_Index) const { return m_VertexArr[A_Index]; }
        const Vector3& GetVertexAt(Utility_In Gint32 A_Index) const { return m_VertexArr[A_Index]; }

        const GEO::VectorArray3& GetSamples() const { return m_VertexArr; }
		Gint32 GetSamplesCount() const { return m_VertexArr.size(); }

        Gbool CalcPolylineIntersect(Utility_In Polyline3& A_Polyline, 
            Utility_Out GEO::VectorArray3& A_InterPtPolygon,
            Utility_Out GEO::VectorArray3& A_InterPtPolyline);

        //========================= Extent =========================//

        // ��ƫ��
        void SimpleHorizonalOffset(Utility_In Gdouble A_Distance);

        void    Clear();

    };//end SimplePolygon3

    /**
    * @brief 
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT LinearAlgebra
    {
    private:
        LinearAlgebra() {}

    public:
        // ���Ԫһ�η�����, �޽�������ʱ���� false
        // a1*x + b1*y + c1 = 0
        // a2*x + b2*y + c2 = 0
        static Gbool BinaryEquation(
            Utility_In Gdouble a1, Utility_In Gdouble a2,
            Utility_In Gdouble b1, Utility_In Gdouble b2,
            Utility_In Gdouble c1, Utility_In Gdouble c2,
            Utility_Out Gdouble& x, Utility_Out Gdouble& y);

        // ��������ʽ
        static Gdouble Determinant3x3(
            Utility_In Gdouble A1, Utility_In Gdouble A2, Utility_In Gdouble A3,
            Utility_In Gdouble B1, Utility_In Gdouble B2, Utility_In Gdouble B3,
            Utility_In Gdouble C1, Utility_In Gdouble C2, Utility_In Gdouble C3);

    };//end LinearAlgebra

    /**
    * @brief ��ֵ
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT InterpolateTool
    {
    private:
        InterpolateTool() {}

    public:
        // һά���Բ�ֵ
        inline static Gdouble Interpolate(Utility_In Gdouble A_Start, Utility_In Gdouble A_End, Utility_In Gdouble A_Ratio);

        // ��ά���Բ�ֵ
        inline static GEO::Vector Interpolate(Utility_In GEO::Vector& A_PtA, Utility_In GEO::Vector& A_PtB, Utility_In Gdouble A_Ratio);
        
        // ��ά���Բ�ֵ
        inline static GEO::Vector3 Interpolate(Utility_In GEO::Vector3& A_PtA, Utility_In GEO::Vector3& A_PtB, Utility_In Gdouble A_Ratio);
        
        // ���� A_Value �� A_Min �� A_Max ֮��ı���λ��
        inline static Gdouble CalcRangeRatio(Utility_In Gdouble A_Value, Utility_In Gdouble A_Min, Utility_In Gdouble A_Max);

        // B ������ kΪ���ƴ���,���Կ������ߵĹ⻬��
        static void B_Spline(GEO::VectorArray& p, Gint32 k, GEO::VectorArray& A_Samples);

    };//end InterpolateTool

    /**
    * @brief �����ʷ��㷨, �������Ч�ʵ�, �����ڵ�·��������һ�㲻���Ǻܸ��ӵĶ����
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT Triangulate
    {
    public:
        // triangulate a contour/polygon, places results in STL vector
        // as series of triangles.
        // ���������ʷ�֮��Ľ��, ������һ��ķ�ʽ����������ηŵ� result ֮��
        static Gbool Process(Utility_In VectorArray &contour,
            VectorArray& result);

        // ���������ʷ�֮��Ľ��, �ʷ�ʱ��������µĶ���, �ʷֽ��ȫ��ʹ��ԭʼ����εĶ���
        // ���ص������ν�� A_IndexResult Ϊ�ʷֵ������ζ�����ԭʼ����εĶ�������λ��
        static Gbool Process(Utility_In VectorArray &contour,
            AnGeoVector<Gint32>& A_IndexResult);

    private:
        Triangulate() {}

        // compute area of a contour/polygon
        static Gdouble Area(Utility_In VectorArray &contour);

        // decide if point Px/Py is inside triangle defined by
        // (Ax,Ay) (Bx,By) (Cx,Cy)
        static Gbool InsideTriangle(
            Gdouble Ax, Gdouble Ay,
            Gdouble Bx, Gdouble By,
            Gdouble Cx, Gdouble Cy,
            Gdouble Px, Gdouble Py);

        static Gbool Snip(Utility_In VectorArray &contour, 
            Gint32 u, Gint32 v, Gint32 w, Gint32 n, Gint32 *V);

    };//end Triangulate

    /**
    * @brief 
    * @author ningning.gn
    * @remark
    **/
    enum JunctionResult
    {
        jrNone,
        jrInner,
        jrExtendMaxMax,
        jrExtendMaxMin,
        jrExtendMinMax,
        jrExtendMinMin,
        jrExtendInnerMax,
        jrExtendInnerMin,
        jrExtendMinInner,
        jrExtendMaxInner,
        jrOverlap1Jun,
        jrOverlap2Jun,
        jrOverlapBothJun
    };

    /**
    * @brief ����ߵ��ཻ���, ����ѡ���ԵĻ�ȡ��Ҫ�Ľ��
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT PolyLineIntersectionsResults
    {
        friend class Common;

    private:
        BreakPointArraryPtr m_Breaks1;
        BreakPointArraryPtr m_Breaks2;
        GEO::VectorArrayPtr m_Junctions;
        AnGeoVector<Gdouble>* m_IntsectCos;
        AnGeoVector<Gdouble>* m_IntsectSin;

    public:
        PolyLineIntersectionsResults() : m_Breaks1(NULL), m_Breaks2(NULL), m_Junctions(NULL), m_IntsectCos(NULL), m_IntsectSin(NULL) {}
        inline void SetBreaks1(Utility_In BreakPointArraryPtr A_Breaks1) { m_Breaks1 = A_Breaks1; }
        inline void SetBreaks2(Utility_In BreakPointArraryPtr A_Breaks2) { m_Breaks2 = A_Breaks2; }
        inline void SetJunctons(GEO::VectorArrayPtr A_Junctoins) { m_Junctions = A_Junctoins; }
        inline void SetIntersectCos(AnGeoVector<Gdouble>* A_IntersectCos) { m_IntsectCos = A_IntersectCos; }
        inline void SetIntersectSin(AnGeoVector<Gdouble>* A_IntersectSin) { m_IntsectSin = A_IntersectSin; }

    };//end PolyLineIntersectionsResults

    /**
    * @brief �������ߺ���
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT Common
    {
    private:
        Common() {}

    public:
        // �����߶���ײ����
        static Gbool SegmentPointHitTest(Utility_In GEO::Vector& A_StartPt, Utility_In GEO::Vector& A_EndPt,
            Utility_In GEO::Vector& A_TestPt, Gdouble A_Tolerance);

        // ����㵽�߶ε��������
        static GEO::Vector CalcPointSegNearPt(Utility_In GEO::Vector& A_StartPt, Utility_In GEO::Vector& A_EndPt,
            Utility_In GEO::Vector& A_TestPt, Utility_Out Gdouble& A_Ratio, Utility_Out Gdouble& A_Distance);

        static GEO::Vector3 CalcPointSegNearPt(Utility_In GEO::Vector3& A_StartPt, Utility_In GEO::Vector3& A_EndPt,
            Utility_In GEO::Vector3& A_TestPt, Utility_Out Gdouble& A_Ratio, Utility_Out Gdouble& A_Distance);

        // ����㵽����ߵ������
        static GEO::Vector CalcPolylineNearPoint(
            Utility_In GEO::Vector& A_Pt, Utility_In GEO::VectorArray& A_Polyline,
            Utility_Out RoadBreakPoint& A_RoadPosPoint, Utility_Out Gdouble& A_MinDistance);

        static GEO::Vector3 CalcPolylineNearPoint(
            Utility_In GEO::Vector3& A_Pt, Utility_In GEO::VectorArray3& A_Polyline,
            Utility_Out RoadBreakPoint& A_RoadPosPoint, Utility_Out Gdouble& A_MinDistance);

        // ��ȡ�ϵ���е�λ��
        static RoadBreakPoint CalcBreakPointMiddle(Utility_In RoadBreakPoint& A_Start,
            Utility_In RoadBreakPoint& A_End, Utility_In GEO::VectorArray& A_Samples);

        // ������������ߵĽ���, ���ؽ������������ϵ�λ����Ϣ, û�н��㷵�� false
        static Gbool CalcPolyLineIntersections(
            Utility_In GEO::VectorArray& A_Samples1, Utility_In GEO::VectorArray& A_Samples2,
            Utility_Out BreakPointArrary& A_Breaks1, Utility_Out BreakPointArrary& A_Breaks2,
            Utility_In Gdouble A_Tolerance = 0.00001);

        // ������������ߵĽ���, ���ؽ������������ϵ�λ����Ϣ, û�н��㷵�� false
        static Gbool CalcPolyLineIntersections(
            Utility_In GEO::VectorArray& A_Samples1, Utility_In GEO::VectorArray& A_Samples2,
            Utility_Out PolyLineIntersectionsResults& A_Results,
            Utility_In Gdouble A_Tolerance = 0.00001);

        // �����߶������ߵĽ���
        static Gbool CalcSegPolyLineIntersections(
            Utility_In GEO::Segment& A_Segment, Utility_In GEO::VectorArray& A_Samples,
            Utility_Out PolyLineIntersectionsResults& A_Results,
            Utility_In Gdouble A_Tolerance = 0.00001);

        static Gbool CalcSegPolyLineIntersections(
            Utility_In GEO::Segment& A_Segment, Utility_In GEO::VectorArray& A_Samples,
            Utility_Out BreakPointArrary& A_Breaks,
            Utility_In Gdouble A_Tolerance = 0.00001);

        // ��������ĳ��Χ�ϵĲ�����
        static void CalcPolyLineSamples(Utility_In RoadItemRange& A_Range,
            Utility_In GEO::VectorArray3& A_Samples, Utility_Out GEO::VectorArray3& A_RangeSamples);
        static void CalcPolyLineSamples(Utility_In RoadItemRange& A_Range,
            Utility_In GEO::VectorArray& A_Samples, Utility_Out GEO::VectorArray& A_RangeSamples);

        // ����������, �����Ƿ��ཻ
        static Gbool RayIntersection(
            Utility_In GEO::Vector& A_Start1,
            Utility_In GEO::Vector& A_Dir1,
            Utility_In GEO::Vector& A_Start2,
            Utility_In GEO::Vector& A_Dir2,
            Utility_Out GEO::Vector& jun,
            Utility_In Gdouble fTolerance = 0.00001);

        // ���߶��ཻ����
        static JunctionResult CalcJunction(
            Utility_In GEO::Vector& A_Start1,
            Utility_In GEO::Vector& A_End1,
            Utility_In GEO::Vector& A_Start2,
            Utility_In GEO::Vector& A_End2,
            Utility_Out GEO::Vector& jun,
            Utility_In Gdouble fTolerance = 0.00001);

        // ���߶��ཻ����
        static JunctionResult CalcJunction(
            Utility_In GEO::Vector& A_Start1,
            Utility_In GEO::Vector& A_End1,
            Utility_In GEO::Vector& A_Start2,
            Utility_In GEO::Vector& A_End2,
            Utility_Out GEO::Vector& jun,
            Utility_Out Gdouble& A_Ratio1,
            Utility_Out Gdouble& A_Ratio2,
            Utility_In Gdouble fTolerance = 0.00001);

        // ���߶��ཻ����
        static JunctionResult CalcJunctionEx(
            Utility_In GEO::Vector& A_Start1,
            Utility_In GEO::Vector& A_End1,
            Utility_In GEO::Vector& A_Start2,
            Utility_In GEO::Vector& A_End2,
            Utility_Out GEO::Vector &A_Junction1,
            Utility_Out GEO::Vector &A_Junction2,
            Utility_In Gdouble fTolerance = 0.00001);

        static JunctionResult CalcJunction2d(
            Utility_In GEO::Vector3& A_Start1,
            Utility_In GEO::Vector3& A_End1,
            Utility_In GEO::Vector3& A_Start2,
            Utility_In GEO::Vector3& A_End2,
            Utility_Out GEO::Vector3& A_Jun1,
            Utility_Out GEO::Vector3& A_Jun2,
            Utility_In Gdouble fTolerance = 0.00001);

        static Gbool BoxSegmentIntersect(
            Utility_In GEO::Box& A_Box, 
            Utility_In GEO::Vector& A_Start, 
            Utility_In GEO::Vector& A_End);

        // �㵽�߶ξ���
        static Gdouble Distance(Utility_In GEO::Vector& A_Point,
            Utility_In GEO::Vector& A_LineStart, Utility_In GEO::Vector& A_LineEnd);

        // ��ͶӰ���߶��ϵı���λ��, ��Ϊ<0ֵ��>1��ֵ
        static Gdouble ProjectToSegment(Utility_In GEO::Vector& A_Point,
            Utility_In GEO::Vector& A_LineStart, Utility_In GEO::Vector& A_LineEnd);

    };//end CCommon

}//end GEO

#include "Geometry.inl"
