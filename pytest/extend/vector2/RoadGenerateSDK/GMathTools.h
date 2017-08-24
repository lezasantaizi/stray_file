/*-----------------------------------------------------------------------------
                                 ��ѧ���ߵ�Ԫ
	���ߣ����� 2016/06/02
	��ע��
	��ˣ�

-----------------------------------------------------------------------------*/
#pragma once

namespace GEO
{
    /**
    * @brief ����
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT Constant
    {
    private:
        Constant() {}

    public:
        inline static Gdouble Pi() { return TMath_d::s_pi; };
		inline static Gdouble TwoPi() { return TMath_d::s_two_pi; }
		inline static Gdouble HalfPi() { return TMath_d::s_half_pi; }
        inline static Gdouble Epsilon() { return TMath_d::s_epsilon; }
        inline static Gdouble EpsilonRatio() { return TMath_d::s_epsilonRatio; }
        inline static Gdouble EpsilonAngle() { return TMath_d::s_epsilonAngle; } // 5��

    };//end Constant

    /**
    * @brief ��ѧ����
    * @author ningning.gn
    * @remark
    **/
    class ROAD_EXPORT MathTools
    {
    private:
        MathTools() {}

    public:
        // �Ƿ����
        inline static Gbool Equal(Utility_In Gdouble A_Value1, Utility_In Gdouble A_Value2);

        // ����ֵ
        inline static Gdouble Abs(Utility_In Gdouble A_Value);

        // ���
        inline static Gdouble Diff(Utility_In Gdouble A_Value1, Utility_In Gdouble A_Value2);
        inline static Gint32 Diff(Utility_In Gint32 A_Value1, Utility_In Gint32 A_Value2);

        // ��С
        inline static Gdouble Min(Utility_In Gdouble A_Value1, Utility_In Gdouble A_Value2);
        inline static Gdouble Min(Utility_In Gdouble A_Value1, Utility_In Gdouble A_Value2, Utility_In Gdouble A_Value3);

        inline static Gint32 Min(Utility_In Gint32 A_Value1, Utility_In Gint32 A_Value2);
        inline static Gint32 Min(Utility_In Gint32 A_Value1, Utility_In Gint32 A_Value2, Utility_In Gint32 A_Value3);

        // ���
        inline static Gdouble Max(Utility_In Gdouble A_Value1, Utility_In Gdouble A_Value2);
        inline static Gdouble Max(Utility_In Gdouble A_Value1, Utility_In Gdouble A_Value2, Utility_In Gdouble A_Value3);

        inline static Gint32 Max(Utility_In Gint32 A_Value1, Utility_In Gint32 A_Value2);
        inline static Gint32 Max(Utility_In Gint32 A_Value1, Utility_In Gint32 A_Value2, Utility_In Gint32 A_Value3);

        // ����
        inline static Gdouble Sin(Utility_In Gdouble A_Value);

        // ����
        inline static Gdouble Cos(Utility_In Gdouble A_Value);

        // ˫������
        inline static Gdouble Sinh(Utility_In Gdouble A_Value);

        // ˫������
        inline static Gdouble Cosh(Utility_In Gdouble A_Value);

        // ����
        inline static Gdouble Tan(Utility_In Gdouble A_Value);

        // ����
        inline static Gdouble Cot(Utility_In Gdouble A_Value);

        // ����eֵ�ĵ� A_Value ����
        inline static Gdouble Exp(Utility_In Gdouble A_Value);

        inline static Gdouble ASin(Utility_In Gdouble A_Value);
        inline static Gdouble ACos(Utility_In Gdouble A_Value);

        // �����У���Բֵ�����������[-PI,PI]
        inline static Gdouble ATan2(Utility_In Gdouble A_X, Utility_In Gdouble A_Y);

        // ��ֱ֪������������ֱ�Ǳ߳��ȣ���б�߳���
        inline static Gdouble Hypot(Utility_In Gdouble A_X, Utility_In Gdouble A_Y);

        // ��eΪ�׵Ķ���
        inline static Gdouble Log(Utility_In Gdouble A_Value);

        // ����x��y����
        inline static Gdouble Pow(Utility_In Gdouble x, Utility_In Gdouble y);

        // ��10Ϊ�׵Ķ���
        inline static Gdouble Log10(Utility_In Gdouble A_Value);

        // �������������������
        inline static Gdouble Mod(Utility_In Gdouble A_Value, Utility_In Gdouble A_Value2);

        // ���η�
        inline static Gdouble Cube(Utility_In Gdouble A_Value);

        // ƽ����
        inline static Gdouble Sqrt(Utility_In Gdouble A_Value);

        // ��������
        inline static Gdouble Round(Utility_In Gdouble A_Value);

        // ȡ���������ز���xС����С����
        inline static Gdouble Ceil(Utility_In Gdouble A_Value);

        // ȡ���������ز���x����������������˹����[x]
        inline static Gdouble Floor(Utility_In Gdouble A_Value);

        // ǯ������
        inline static void ClampSelf(Utility_InOut Gdouble& A_Value, Utility_In Gdouble A_Min, Utility_In Gdouble A_Max);
        inline static Gdouble Clamp(Utility_In Gdouble A_Value, Utility_In Gdouble A_Min, Utility_In Gdouble A_Max);

        inline static void ClampSelf(Utility_InOut Gint32& A_Value, Utility_In Gint32 A_Min, Utility_In Gint32 A_Max);
        inline static Gint32 Clamp(Utility_In Gint32 A_Value, Utility_In Gint32 A_Min, Utility_In Gint32 A_Max);

        // �ж���ֵ�Ƿ��ڷ�Χ֮��
        static Gbool IsInRange(Utility_In Gdouble A_Value, Utility_In Gdouble A_Min, Utility_In Gdouble A_Max,
            Utility_In Gdouble A_ToleranceExpand = Constant::Epsilon());

        // �Ƕ�ת����
        inline static Gdouble DegToRad(Utility_In Gdouble A_Deg);
        inline static void DegToRadSelf(Utility_InOut Gdouble& A_DegToRad);

        // ����ת�Ƕ�
        inline static Gdouble RadToDeg(Utility_In Gdouble A_Rad);
        inline static void RadToDegSelf(Utility_InOut Gdouble& A_RadToDeg);

        // ��������� 0.0 ~ 1.0
        inline static Gdouble Rand();

        // ��������� A_Min ~ A_Max
        inline static Gdouble RandRange(Utility_In Gdouble A_Min, Utility_In Gdouble A_Max);

        inline static Gint32 RandomInteger();

    };//end MathTools

    /**
    * @brief ��ѧ����
    * @author ningning.gn
    * @remark
    **/
    inline void MathTools::ClampSelf(Utility_InOut Gdouble& A_Value, Utility_In Gdouble A_Min, Utility_In Gdouble A_Max)
    {
        ROAD_ASSERT(A_Min <= A_Max);

        if (A_Value < A_Min)
            A_Value = A_Min;
        else if (A_Value > A_Max)
            A_Value = A_Max;
    }

    inline void MathTools::ClampSelf(Utility_InOut Gint32& A_Value, Utility_In Gint32 A_Min, Utility_In Gint32 A_Max)
    {
        ROAD_ASSERT(A_Min <= A_Max);

        if (A_Value < A_Min)
            A_Value = A_Min;
        else if (A_Value > A_Max)
            A_Value = A_Max;
    }

    inline Gdouble MathTools::Clamp(Utility_In Gdouble A_Value, Utility_In Gdouble A_Min, Utility_In Gdouble A_Max)
    {
        ROAD_ASSERT(A_Min <= A_Max);

        return TMath_d::clamp(A_Value , A_Min , A_Max);
    }

    inline Gint32 MathTools::Clamp(Utility_In Gint32 A_Value, Utility_In Gint32 A_Min, Utility_In Gint32 A_Max)
    {
        ROAD_ASSERT(A_Min <= A_Max);

        if (A_Value < A_Min)
            return A_Min;
        if (A_Value > A_Max)
            return A_Max;
        return A_Value;
    }

    inline Gdouble MathTools::Rand()
    {
		return (Gdouble)TMath_d::rand_() / (Gdouble)RAND_MAX;
    }

    inline Gdouble MathTools::RandRange(Utility_In Gdouble A_Min, Utility_In Gdouble A_Max)
    {
		return (Gdouble)TMath_d::rand_() / (Gdouble)RAND_MAX * (A_Max - A_Min) + A_Min;
    }

    inline Gint32 MathTools::RandomInteger()
    {
		return TMath_d::rand_();
    }

    // �Ƿ����
    inline Gbool MathTools::Equal(Utility_In Gdouble A_Value1, Utility_In Gdouble A_Value2)
    {
		return TMath_d::equal(A_Value1, A_Value2);
    }

    // ����ֵ
    inline Gdouble MathTools::Abs(Utility_In Gdouble A_Value)
    {
        return TMath_d::abs_(A_Value);
    }

    // ���
    inline Gdouble MathTools::Diff(Utility_In Gdouble A_Value1, Utility_In Gdouble A_Value2)
    {
        return fabs(A_Value1 - A_Value2);
    }

    inline Gint32 MathTools::Diff(Utility_In Gint32 A_Value1, Utility_In Gint32 A_Value2)
    {
        if (A_Value1 >= A_Value2)
            return A_Value1 - A_Value2;
        else
            return A_Value2 - A_Value1;
    }

    inline Gdouble MathTools::Min(Utility_In Gdouble A_Value1, Utility_In Gdouble A_Value2)
    {
        return TMath_d::min_(A_Value1 , A_Value2);
    }

    inline Gint32 MathTools::Min(Utility_In Gint32 A_Value1, Utility_In Gint32 A_Value2)
    {
		return TMath_d::min_(A_Value1, A_Value2);
    }

    inline Gdouble MathTools::Min(Utility_In Gdouble A_Value1, Utility_In Gdouble A_Value2, Utility_In Gdouble A_Value3)
    {
        if (A_Value1 < A_Value2 && A_Value1 < A_Value3)
        {
                return A_Value1;
        }
        else
        {
            return A_Value2 < A_Value3 ? A_Value2 : A_Value3;
        }
    }

    inline Gint32 MathTools::Min(Utility_In Gint32 A_Value1, Utility_In Gint32 A_Value2, Utility_In Gint32 A_Value3)
    {
        if (A_Value1 < A_Value2 && A_Value1 < A_Value3)
        {
            return A_Value1;
        }
        else
        {
            return A_Value2 < A_Value3 ? A_Value2 : A_Value3;
        }
    }

    inline Gdouble MathTools::Max(Utility_In Gdouble A_Value1, Utility_In Gdouble A_Value2)
    {
		return TMath_d::max_(A_Value1, A_Value2);
    }

    inline Gint32 MathTools::Max(Utility_In Gint32 A_Value1, Utility_In Gint32 A_Value2)
    {
		return TMath_d::max_(A_Value1, A_Value2);
    }

    inline Gdouble MathTools::Max(Utility_In Gdouble A_Value1, Utility_In Gdouble A_Value2, Utility_In Gdouble A_Value3)
    {
        if (A_Value1 > A_Value2 && A_Value1 > A_Value3)
        {
            return A_Value1;
        }
        else
        {
            return A_Value2 > A_Value3 ? A_Value2 : A_Value3;
        }
    }

    inline Gint32 MathTools::Max(Utility_In Gint32 A_Value1, Utility_In Gint32 A_Value2, Utility_In Gint32 A_Value3)
    {
        if (A_Value1 > A_Value2 && A_Value1 > A_Value3)
        {
            return A_Value1;
        }
        else
        {
            return A_Value2 > A_Value3 ? A_Value2 : A_Value3;
        }
    }

    // ����
    inline Gdouble MathTools::Sin(Utility_In Gdouble A_Value)
    {
		return TMath_d::sin_(A_Value);
    }

    // ����
    inline Gdouble MathTools::Cos(Utility_In Gdouble A_Value)
    {
		return TMath_d::cos_(A_Value);
    }

    inline Gdouble MathTools::Sinh(Utility_In Gdouble A_Value)
    {
		return TMath_d::sinh_(A_Value);
    }

    inline Gdouble MathTools::Cosh(Utility_In Gdouble A_Value)
    {
		return TMath_d::cosh_(A_Value);
    }

    inline Gdouble MathTools::Tan(Utility_In Gdouble A_Value)
    {
		return TMath_d::tan_(A_Value);
    }

    inline Gdouble MathTools::Cot(Utility_In Gdouble A_Value)
    {
		return TMath_d::cot_(A_Value);
    }

    inline Gdouble MathTools::Exp(Utility_In Gdouble A_Value)
    {
		return TMath_d::exp_(A_Value);
    }

    inline Gdouble MathTools::ATan2(Utility_In Gdouble A_X, Utility_In Gdouble A_Y)
    {
		return TMath_d::atan2_(A_Y, A_X);
    }

//     inline Gdouble MathTools::Hypot(Utility_In Gdouble A_X, Utility_In Gdouble A_Y)
//     {
//         return ::hypot(A_X, A_Y);
//     }

    inline Gdouble MathTools::ASin(Utility_In Gdouble A_Value)
    {
        return TMath_d::asin_(A_Value);
    }

    inline Gdouble MathTools::ACos(Utility_In Gdouble A_Value)
    {
        return TMath_d::acos_(A_Value);
    }

    inline Gdouble MathTools::Pow(Utility_In Gdouble x, Utility_In Gdouble y)
    {
		return TMath_d::pow_(x, y);
    }

    inline Gdouble MathTools::Log(Utility_In Gdouble A_Value)
    {
		return TMath_d::log_(A_Value);
    }

//     inline Gdouble MathTools::Log10(Utility_In Gdouble A_Value)
//     {
//         return ::log10(A_Value);
//     }
// 
//     inline Gdouble MathTools::Mod(Utility_In Gdouble A_Value, Utility_In Gdouble A_Value2)
//     {
//         return ::fmod(A_Value, A_Value2);
//     }

    inline Gdouble MathTools::Cube(Utility_In Gdouble A_Value)
    {
		return TMath_d::pow_(A_Value, 3.0);
    }

    // ƽ����
    inline Gdouble MathTools::Sqrt(Utility_In Gdouble A_Value)
    {
		return TMath_d::sqrt_(A_Value);
    }

    // ��������
    inline Gdouble MathTools::Round(Utility_In Gdouble A_Value)
    {
		return TMath_d::round_(A_Value);
    }

    inline Gdouble MathTools::Ceil(Utility_In Gdouble A_Value)
    {
        return TMath_d::ceil_(A_Value);
    }

    inline Gdouble MathTools::Floor(Utility_In Gdouble A_Value)
    {
        return TMath_d::floor_(A_Value);
    }

    // �Ƕ�ת����
    inline Gdouble MathTools::DegToRad(Utility_In Gdouble A_Deg)
    {
		return TMath_d::dtor(A_Deg);
    }

    inline void MathTools::DegToRadSelf(Utility_InOut Gdouble& A_DegToRad)
    {
		A_DegToRad *= TMath_d::s_deg_to_rad;
    }

    // ����ת�Ƕ�
    inline Gdouble MathTools::RadToDeg(Utility_In Gdouble A_Rad)
    {
        return TMath_d::rtod(A_Rad);
    }

    inline void MathTools::RadToDegSelf(Utility_InOut Gdouble& A_RadToDeg)
    {
		A_RadToDeg *= TMath_d::s_rad_to_deg;
    }

    inline Gbool MathTools::IsInRange(Utility_In Gdouble A_Value,
        Utility_In Gdouble A_Min, Utility_In Gdouble A_Max, Utility_In Gdouble A_ToleranceExpand/* = 0.0001*/)
    {
        return (A_Value >= A_Min - A_ToleranceExpand) && (A_Value <= A_Max + A_ToleranceExpand);
    }

}//end GEO
