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
    inline double QuickCosWithRadius(const double Radius);
    inline double QuickSinWithRadius(const double Radius);
    inline float  QuickCosWithAngle(const float Angle);
    inline float  QuickSinWithAngle(const float Angle);
    inline double QuickCosWithRadius(const float Radius);
    inline double QuickSinWithRadius(const float Radius);
    inline double QuickSinWithAngle(const int Angle);
    inline double QuickCosWithAngle(const int Angle);
    inline int    RandInt();
    inline int    RandIntInRange(int left, int right);
    inline float  RandUnitFloat();//rand float with (0,1)
    inline float  RandFloatInRange(float left, float right);
#include "NXMath.inl"
}

#endif