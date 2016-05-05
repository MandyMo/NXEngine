/*
 *  File:    math.h
 *  author:  张雄
 *  date:    2016_02_26
 *  purpose: 基本的数学库函数
 */

//写一些sin,cos之类的快速计算函数
#ifndef __ZX_NXENGINE_MATH_H__
#define __ZX_NXENGINE_MATH_H__

#include "../common/NXCore.h"

namespace NX {
    void InitNXMath();
    inline double QuickCosWithAngle(const double Angle);
    inline double QuickSinWithAngle(const double Angle);
    inline double QuickCosWithRadian(const double Radian);
    inline double QuickSinWithRadian(const double Radian);
    inline float  QuickCosWithAngle(const float Angle);
    inline float  QuickSinWithAngle(const float Angle);
    inline double QuickCosWithRadian(const float Radian);
    inline double QuickSinWithRadian(const float Radian);
    inline double QuickSinWithAngle(const int Angle);
    inline double QuickCosWithAngle(const int Angle);
    inline int    RandInt();
    inline int    RandIntInRange(int left, int right);
    inline float  RandUnitFloat();//rand float with (0,1)
    inline float  RandFloatInRange(float left, float right);
    
    //ComparedValue >= NewValue
    template<typename T, typename U>
    T ClampFloor(T& ComparedValue, const U NewValue);
    //ComparedValue <= NewValue
    template<typename T, typename U>
    T ClampCeil(T& ComparedValue, const U NewValue);
    //FloorValue <= CompraedValue <= CeilValue
    template<typename T, typename U, typename X>
    T Clamp(T& ComparedValue, const U FloorValue, const X CeilValue);
    
#include "NXMath.inl"
}

#endif