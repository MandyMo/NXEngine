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
        const static T m_Epsilon = 0;
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
}


#endif //