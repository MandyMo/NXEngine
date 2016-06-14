/*
 *  File:    NXSphere.cpp
 *  author:  张雄
 *  date:    2016_05_13
 *  purpose: define Sphere
 */

#include "NXSphere.h"
#include "NXMatrix.h"
#include "NXAlgorithm.h"
#include "NXLine.h"
#include "NXPlane.h"

namespace NX {
    Sphere::Sphere(const float3 &ptA, const float3 &ptB, const float3 &ptC, const float3 &ptD){
        NX::Matrix<float, 3, 3> m;
        m.SetRow(0, 2 * (ptA - ptB));
        m.SetRow(1, 2 * (ptA - ptC));
        m.SetRow(2, 2 * (ptA - ptD));
        float aa = NX::LengthSquare(ptA);
        float bb = NX::LengthSquare(ptB);
        float cc = NX::LengthSquare(ptC);
        float dd = NX::LengthSquare(ptD);
        const NX::Matrix<float, 3, 1> &Result = NX::GetReverse(m) * NX::float3(aa - bb, aa - cc, aa - dd);
        m_vCenter.Set(Result[0][0], Result[1][0], Result[2][0]);
        m_fRadius = NX::Length(ptA - m_vCenter);
    }
    
    Sphere& Sphere::Transform(const Matrix<float, 3, 3> &matrix){
        const NX::Matrix<float, 3, 1> &RV = matrix * m_vCenter;
        m_vCenter.Set(RV[0][0], RV[1][0], RV[2][0]);
        return *this;
    }
    
    Sphere& Sphere::Transform(const Matrix<float, 4, 4> &matrix){
        const NX::Matrix<float, 4, 1> &RV = matrix * NX::vector<float, 4>(m_vCenter.x, m_vCenter.y, m_vCenter.z, 1.0f);
        const float Mult = 1.0f / RV[3][0];
        m_vCenter.Set(RV[0][0] * Mult, RV[1][0] * Mult, RV[2][0] * Mult);
        return *this;
    }
    
    Sphere& Sphere::Transform(const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3>    &T){
        NX::Matrix<float, 4, 4> M = NX::GetRTMatrix(R, T);
        return Transform(M);
    }
    
    Sphere& Sphere::Transform(const NX::vector<float, 3>    &T, const NX::Matrix<float, 3, 3> &R){
        NX::Matrix<float, 4, 4> M = NX::GetTRMatrix(T, R);
        return Transform(M);
    }
    
    Sphere& Sphere::Translate(const float3 &v){
        m_vCenter += v;
        return *this;
    }
    
    bool Sphere::Intersect(const Sphere &rhs) const{
        return NX::LengthSquare(rhs.m_vCenter - m_vCenter) <= m_fRadius + rhs.m_fRadius;
    }
    
    bool Sphere::TangentWithLine(const Line &lne) const{
        return NX::NXAbs(lne.Distance(m_vCenter) - m_fRadius) <= NX::Epsilon<float>::m_Epsilon;
    }
    
    bool Sphere::TangentWithPlane(const Plane &plane) const{
        return NX::NXAbs(plane.Distance(m_vCenter) - m_fRadius) <= NX::Epsilon<float>::m_Epsilon;
    }
    
    bool Sphere::TangentWithSphere(const Sphere &rhs) const{
        return NX::NXAbs(NX::LengthSquare(rhs.m_vCenter - m_vCenter) - (m_fRadius + rhs.m_fRadius) * (m_fRadius + rhs.m_fRadius)) <= NX::Epsilon<float>::m_Epsilon;
    }
}