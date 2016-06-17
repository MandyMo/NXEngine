/*
 *  File:    NXCircle.cpp
 *  author:  张雄
 *  date:    2016_05_13
 *  purpose: define circle
 */

#include "NXCircle.h"
#include "NXMatrix.h"
#include "NXVector.h"
#include "NXAlgorithm.h"

namespace NX {
    Circle::Circle(const NX::float3 &ptA, const NX::float3 &ptB, const NX::float3 &ptC){
        const NX::vector<float, 3> e1 = ptC - ptB;
        const NX::vector<float, 3> e2 = ptA - ptC;
        const NX::vector<float, 3> e3 = ptB - ptA;
        const float d1 = -NX::Dot(e2, e3);
        const float d2 = -NX::Dot(e3, e1);
        const float d3 = -NX::Dot(e1, e2);
        const float c1 = d2 * d3;
        const float c2 = d1 * d3;
        const float c3 = d1 * d2;
        const float c  = c1 + c2 + c3;
        const float Mult = 0.5f / c;
        m_vCenter =  Mult * (c2 + c3) * ptA + Mult * (c3 + c1) * ptB + Mult * (c1 + c2) * ptC;
        m_fRadius =  NX::Length(m_vCenter - ptA);
        m_vNormal =  NX::GetNormalized(NX::Cross(e2, e3));
    }
    
    Circle& Circle::Transform(const NX::Matrix<float, 3, 3> &matrix){
        {
            const Matrix<float, 3, 1> &RV = NX::GetTransposed(::NX::GetReverse(matrix)) * m_vNormal;
            m_vNormal.Set(RV[0][0], RV[1][0], RV[2][0]);
        }
        {
            const Matrix<float, 3, 1> &RV = matrix * m_vCenter;
            m_vCenter.Set(RV[0][0], RV[1][0], RV[2][0]);
        }
        
        return *this;
    }
    
    Circle& Circle::Transform(const NX::Matrix<float, 4, 4> &matrix){
        {
            const Matrix<float, 4, 1> &RV = NX::GetTransposed(NX::GetReverse(matrix)) * NX::vector<float, 4>(m_vNormal.x, m_vNormal.y, m_vNormal.z, 0.0f);
            m_vNormal.Set(RV[0][0], RV[1][0], RV[2][0]);
        }
        
        {
            const Matrix<float, 4, 1> &RV = matrix * NX::vector<float, 4>(m_vCenter.x, m_vCenter.y, m_vCenter.z, 1.0f);
            const float Mult = 1.0f / RV[3][0];
            m_vCenter.Set(RV[0][0] * Mult, RV[1][0] * Mult, RV[2][0] * Mult);
        }
        return *this;
    }
    
    Circle& Circle::Transform(const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3>    &T){
        NX::Matrix<float, 4, 4> M = NX::GetRTMatrix(R, T);
        return Transform(M);
    }
    
    Circle& Circle::Transform(const NX::vector<float, 3>    &T, const NX::Matrix<float, 3, 3> &R){
        NX::Matrix<float, 4, 4> M = NX::GetTRMatrix(T, R);
        return Transform(M);
    }
}
