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
        float aa = NX::LengthSquare(ptB - ptC);
        float bb = NX::LengthSquare(ptA - ptC);
        float cc = NX::LengthSquare(ptA - ptB);
        float a = std::sqrt(aa);
        float b = std::sqrt(bb);
        float c = std::sqrt(cc);
        float p = (a + b + c) * 0.5f;
        float s = std::sqrt(p * (p - a) * (p - b) * (p - c));
        float Mult = 1 / (4.0 * s);
        float CotA = (bb + cc - aa) * Mult;
        float CotB = (aa + cc - bb) * Mult;
        float CotC = (aa + bb - cc) * Mult;
        
        m_vCenter = (1 - CotB * CotC) * ptA + (1 - CotA * CotC) * ptB + (1 - CotA * CotB) * ptC;
        m_vCenter *= 0.5;
        m_vNormal = ::NX::Cross(ptB - ptA, ptC - ptA);
        m_fRadius = 0.25 * a * b * c / s;
    }
    
    Circle& Circle::Transform(const NX::Matrix<float, 3, 3> &matrix){
        {
            const Matrix<float, 3, 1> &RV = ::NX::GetTranspose(::NX::GetReverse(matrix)) * m_vNormal;
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
            const Matrix<float, 4, 1> &RV = ::NX::GetTranspose(::NX::GetReverse(matrix)) * NX::vector<float, 4>(m_vNormal.x, m_vNormal.y, m_vNormal.z, 0.0f);
            m_vNormal.Set(RV[0][0], RV[1][0], RV[2][0]);
        }
        
        {
            const Matrix<float, 4, 1> &RV = matrix * NX::vector<float, 4>(m_vCenter.x, m_vCenter.y, m_vCenter.z, 1.0f);
            const float Mult = 1.0f / RV[3][0];
            m_vCenter.Set(RV[0][0] * Mult, RV[1][0] * Mult, RV[2][0] * Mult);
        }
        return *this;
    }
}
