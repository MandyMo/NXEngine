/*
 *  File:    NXNumeric.h
 *  author:  张雄
 *  date:    2016_05_13
 *  purpose: 定义一些数值的东西
 */

#ifndef __ZX_NXENGINE_NUMERIC_H__
#define __ZX_NXENGINE_NUMERIC_H__

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
}


#endif //