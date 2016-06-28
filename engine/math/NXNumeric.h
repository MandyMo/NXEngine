/*
 *  File:    NXNumeric.h
 *  author:  张雄
 *  date:    2016_05_13
 *  purpose: 定义一些数值的东西
 */

#ifndef __ZX_NXENGINE_NUMERIC_H__
#define __ZX_NXENGINE_NUMERIC_H__
#include <cmath>

namespace NX{
    //==============================================begin epsilon value=================================================
    template<typename T>
    class Epsilon{
    public:
    };
    #ifndef NX_EPSILON_SPECIALLIZE
    #define NX_EPSILON_SPECIALLIZE(type, value) \
    template<>\
    class Epsilon<type>{\
    public:\
        constexpr const static type m_Epsilon = value;\
    };
    #endif
    
    /**
     *  template speciallize
     */
    NX_EPSILON_SPECIALLIZE(unsigned char,        (0))
    NX_EPSILON_SPECIALLIZE(signed char,          (0))
    NX_EPSILON_SPECIALLIZE(char,                 (0))
    NX_EPSILON_SPECIALLIZE(short,                (0))
    NX_EPSILON_SPECIALLIZE(unsigned short,       (0))
    NX_EPSILON_SPECIALLIZE(int,                  (0))
    NX_EPSILON_SPECIALLIZE(unsigned int,         (0))
    NX_EPSILON_SPECIALLIZE(long,                 (0))
    NX_EPSILON_SPECIALLIZE(unsigned long,        (0))
    NX_EPSILON_SPECIALLIZE(long long,            (0))
    NX_EPSILON_SPECIALLIZE(unsigned long long,   (0))
    NX_EPSILON_SPECIALLIZE(float,                (0.0001f))
    NX_EPSILON_SPECIALLIZE(double,               (0.0000001))
    NX_EPSILON_SPECIALLIZE(long double,          (0.0000001))
    static const float  FLOAT_EPSILON    = Epsilon<float>::m_Epsilon;
    static const double DOUBLE_EPSILON   = Epsilon<double>::m_Epsilon;
    //==============================================end of epsilon value================================================
    
    
    
    //============================================begin of evaluation at compile time===================================
    template<int numerator, int denominator>
    class RationalEvaluationFloat{
    public:
        constexpr static float m_Value = 1.0f * numerator / denominator;
    };
    
    template<int numerator, int denominator>
    class RationalEvaluationDouble{
    public:
        constexpr static double m_Value = 1.0 * numerator / denominator;
    };
    //=============================================end of evaluation at compile time====================================
    
    
    //========================================constant about pi=========================================================
    static const float kfPi            = 3.14159265358979323846264338327950238f;
    static const float kf2Pi           = kfPi * 2.0f;
    static const float kfPiOver2       = kfPi * 0.5f;
    static const float kf1OverPi       = 1.0f / kfPi;
    static const float kf1Over2Pi      = 1.0f / kf2Pi;
    
    static const double klfPi          = 3.14159265358979323846264338327950238;
    static const double klf2Pi         = klfPi * 2.0;
    static const double llfPiOver2     = klfPi * 0.5;
    static const double klf1OverPi     = 1.0 / klfPi;
    static const double klf1Over2Pi    = 1.0 / kf2Pi;
    //==================================================================================================================
    
    //==========================================constant number=========================================================
    static const float kf0             = 0.0f;
    static const float kf1             = 1.0f;
    static const float kf2             = 2.0f;
    static const float kf3             = 3.0f;
    static const float kf1Over2        = kf1 / kf2;
    static const float kf1Over3        = kf1 / kf3;
    static const float kf2Over3        = kf2 / kf3;
    static const float kf3Over2        = kf3 / kf2;
    static const float kfSqrt2         = std::sqrt(kf2);
    static const float kfSqrt3         = std::sqrt(kf3);
    static const float kf1OverSqrt3    = kf1 / kfSqrt3;
    static const float kf1OverSqrt2    = kf1 / kfSqrt2;
    static const float kf2OverSqrt3    = kf2 * kf1Over3;
    
    static const float klf0            = 0.0;
    static const float klf1            = 1.0;
    static const float klf2            = 2.0;
    static const float klf3            = 3.0;
    static const float klf1Over2       = klf1 / klf2;
    static const float klf1Over3       = klf1 / klf3;
    static const float klf2Over3       = klf2 / klf3;
    static const float klf3Over2       = klf3 / klf2;
    static const float klfSqrt2        = std::sqrt(klf2);
    static const float klfSqrt3        = std::sqrt(klf3);
    static const float klf1OverSqrt3   = klf1 / klfSqrt3;
    static const float klf1OverSqrt2   = klf1 / klfSqrt2;
    static const float klf2OverSqrt3   = klf2 * klf1Over3;
    //==================================================================================================================
    
    //==================================================nature constant=================================================
    static const float kfe             = 2.71828182845904523536028747135266249775724709369995f;
    static const float kf1Overe        = kf1 / kfe;
    static const float kf2e            = kf2 * kfe;
    static const float kf2Overe        = kf2 / kfe;
    static const float kfeOver2        = kfe * kf1Over2;
    
    static const double klfe           = 2.71828182845904523536028747135266249775724709369995;
    static const double klf1Overe      = klf1 / klfe;
    static const double klf2e          = klf2 * klfe;
    static const double klf2Overe      = klf2 / klfe;
    static const double klfeOver2      = klfe * klf1Over2;
    //==================================================================================================================
}


#endif //