/*-----------------------------------------------------------------------------

	���ߣ����� 2016/06/02
	��ע��
	��ˣ�

-----------------------------------------------------------------------------*/
#pragma once

#include "GVector.h"

namespace GEO
{
    /**
    * @brief 
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT ResamplePolyline
    {
    private:
        const GEO::VectorArray3& m_Samples3;
        GEO::VectorArray3 m_ResultSamples3;
        Gdouble m_StepLength;

    public:
        ResamplePolyline(Utility_In GEO::VectorArray3& A_Samples3) : m_Samples3(A_Samples3), m_StepLength(1.0) {}

        void SetStepLength(Utility_In Gdouble A_Length);
        Gdouble GetStepLength() const { return m_StepLength; }

        Gbool DoCalculate();

        const GEO::VectorArray3& GetResults() const { return m_ResultSamples3; }

    };//end ResamplePolyline

    /**
    * @brief ��˹ƽ��
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT GaussianSmooth
    {
    private:
        GEO::VectorArray3 m_Samples3;
        GEO::VectorArray3 m_SmoothResult;
        AnGeoVector<Gdouble> m_Kernel;
        Gint32 m_KernelSize;
        Gint32 m_KernelHalfSize;
        Gdouble m_SmoothRange;
        AnGeoVector<Gint32> m_AnchorIndexArr;

        void ReorderAnchor();

    public:
        GaussianSmooth();

        // ƽ��ǿ��, ���Ҷ��ٸ�������, ����Ϊ����, ����Ϊ������
        void SetSmoothIntensity(Utility_In Gdouble A_Intensity);

        // ���ò�����, �����ǵȾ������
        void SetLineData(Utility_In GEO::VectorArray3& A_Samples3);

        // ��Ӳ���ê��
        void AddAnchorPos(Utility_In Gint32 A_Index);

        // ��ƽ������
        Gbool DoSmooth();

        // ��ȡ������
        inline const GEO::VectorArray3& GetSmoothResult() const { return m_SmoothResult; }

#if ROAD_CANVAS
        // ��ͼ(���Ժ���)
        void Draw(Utility_In GRAPHIC::CanvasPtr A_Canvas);
#endif
    };//end GaussianSmooth

    /**
    * @brief ����������
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT GSpline3
    {
    public:
        class SegmentParam
        {
            friend class GSpline3;
        private:
            Gdouble m_a3, m_a1, m_b3, m_b1;
            GEO::Vector  m_Start;
            GEO::Vector  m_End;


            SegmentParam(Gdouble a3, Gdouble a1, Gdouble b3, Gdouble b1, Utility_In GEO::Vector& A_Start, Utility_In GEO::Vector& A_End)
                : m_a3(a3), m_a1(a1), m_b3(b3), m_b1(b1), m_Start(A_Start), m_End(A_End) {}

        public:
            // �����ֵ��
            Gdouble CalcValue(Utility_In Gdouble A_Value) const;
            GEO::Vector CalcPoint(Utility_In Gdouble A_Value) const;

        };//end SegmentParam

    private:
        Gdouble m_BeginK;
        Gdouble m_EndK;
        GEO::VectorArray m_AnchorArr;
        AnGeoVector<SegmentParam> m_SegmentParamArr;

    public:
        GSpline3();

        inline void SetBeginSlope(Utility_In Gdouble A_Value) { m_BeginK = A_Value; }
        inline void SetEndSlope(Utility_In Gdouble A_Value) { m_EndK = A_Value; }

        // ���ê��
        void AddAnchor(Utility_In GEO::Vector& A_Anchor);

        // ����ֶβ�ֵϵ��
        Gbool DoCalculateParams();

        // ��ȡ�ֶ�ϵ��
        inline Gint32 GetSegmentCount() const { return (Gint32)m_SegmentParamArr.size(); }
        inline const SegmentParam& GetSegmentParamAt(Utility_In Gint32 A_Index) const { return m_SegmentParamArr[A_Index]; }

    };//end GSpline3

}//end GEO
