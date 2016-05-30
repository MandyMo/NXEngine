/*
 *  File:    math.h
 *  author:  张雄
 *  date:    2016_02_26
 *  purpose: 基本的数学库函数
 */

//写一些sin,cos之类的快速计算函数
#ifndef __ZX_NXENGINE_MATH_H__
#define __ZX_NXENGINE_MATH_H__

#include "NXNumeric.h"
#include "../common/NXCore.h"



namespace NX {
    void InitNXMath();
    template<typename T>
    inline float DG2RD(const T angle);
    
    inline double DG2RD(const double angle);
    
    template<typename T>
    inline float RD2DG(const T angle);
    
    inline double RD2DG(const double angle);
    /**
     *  返回acos和asin值，若value超出[-1, 1]，则返回边界上的最大值
     */
    float SafeACos(const float value);
    float SafeASin(const float value);
    
    std::pair<float, float> GetSinAndCos(const float radian);
    void GetSinAndCos(const float radian, float * const pSinvalue, float * const pCosValue);
    
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
    
    //以mode为单位，将value变换到[-mode, mode]之间，返回变换之前的value
    template<typename T, typename U>
    T Wrap(T &value, const U mode);
    
    //以mode为单位，将value变换到[0, mode)之间，返回变换之前的value
    template<typename T, typename U>
    T Mode(T &value, const U mode);
    template<typename T>
    T NXAbs(const T value);
    
    template<typename T, typename U>
    T NXMin(const T l, const U r);
    
    template<typename T, typename U>
    T NXMax(const T l, const U r);
#include "NXMath.inl"
}

#endif