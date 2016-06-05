/*
 *  File:    NXPrimitive.h
 *  author:  张雄
 *  date:    2016_05_13
 *  purpose: 基本的3D图元相关算法
 */

#ifndef __ZX_NXENGINE_PRIMITIVE_H__
#define __ZX_NXENGINE_PRIMITIVE_H__

#include "NXPlane.h"
#include "NXCircle.h"
#include "NXLine.h"
#include "NXSphere.h"
#include "NXAABB.h"

namespace NX{
    //==================================begin line nomember function====================================================
    template<typename T>
    inline Line Transform(const Line &lhs, const Matrix<T, 3, 3> &rhs);
    
    template<typename T>
    inline Line Transform(const Matrix<T, 3, 3> &lhs, const Line &rhs);
    
    template<typename T>
    inline Line Transform(const Line &lhs, const Matrix<T, 4, 4> &rhs);
    
    template<typename T>
    inline Line Transform(const Matrix<T, 4, 4> &lhs, const Line &rhs);
    
    inline float Distance(const Line &lhs, const Line &rhs);
    
    inline std::pair<bool, vector<float, 3> >  Intersect(const Line &lhs, const Line &rhs);
    //==================================end line nomember function======================================================

    
    
    //=================================begin plane nomember function====================================================
    template<typename T, typename U>
    inline Plane Transform(const Plane &plane, const Matrix<T, 3, 3> &matrix, const vector<U, 3> &translation);
    
    template<typename T>
    inline Plane Transform(const Plane &plane, const Matrix<T, 4, 4> &matrix);
    
    template<typename T>
    inline Plane Transform(const Matrix<T, 4, 4> &matrix, const Plane &plane);
    
    inline std::pair<bool, Line>   Intersect(const Plane &lhs, const Plane &rhs);
    
    inline std::pair<bool, float3> Intersect(const Line  &line,  const Plane &plane);
    
    inline std::pair<bool, float3> Intersect(const Plane &plane, const Line  &line);
    
    inline float  Distance(const Plane &plane, const vector<float, 3> &rhs);
    
    inline float  Distance(const vector<float, 3> &rhs, const Plane &plane);
    
    inline std::pair<bool, vector<float, 3> > Intersect(const Plane &PlaneA, const Plane &PlaneB, const Plane &PlaneC);
    //==================================end plane nomember function=====================================================

#include "NXPrimitive.inl"
}

#endif