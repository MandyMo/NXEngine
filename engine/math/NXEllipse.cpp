/*
 *  File:    NXEllipse.cpp
 *  author:  张雄
 *  date:    2016_06_08
 *  purpose: define ellipse
 */

#include "NXEllipse.h"
#include "NXAlgorithm.h"
#include "NXMatrix.h"
#include "NXMath.h"

namespace NX {
    Ellipse::Ellipse(const float fLongAxis, const float fShortAxis, const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3> &T):m_vLongSemiAxis(1.0f, 0.0f, 0.0f), m_vShortSemiAxis(0.0f, 0.0f, 1.0f), m_vNormal(0.0f, 1.0f, 0.0f), m_vCenter(0.0f, 0.0f, 0.0f){
        m_fLongSemiAxis   = fLongAxis;
        m_fShortSemiAxis  = fShortAxis;
        Transform(R, T);
    }
    
    Ellipse::Ellipse(const float fLongAxis, const float fShortAxis, const NX::Matrix<float, 4, 4> &M):m_vLongSemiAxis(1.0f, 0.0f, 0.0f), m_vShortSemiAxis(0.0f, 0.0f, 1.0f), m_vNormal(0.0f, 1.0f, 0.0f), m_vCenter(0.0f, 0.0f, 0.0f){
        m_fLongSemiAxis   = fLongAxis;
        m_fShortSemiAxis  = fShortAxis;
        Transform(M);
    }
    
    Ellipse& Ellipse::Transform(const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3> &T){
        NX::Matrix<float, 4, 4> M = NX::CreateTransformMatrixByRotateAndTranslation(R, T);
        Transform(M);
        return *this;
    }
    
    Ellipse& Ellipse::Transform(const NX::Matrix<float, 3, 3> &R){
        //to be continue;
        return *this;
    }
    
    Ellipse& Ellipse::Transform(const NX::Matrix<float, 4, 4> &M){
        return *this;
    }
    
    Ellipse Ellipse::GetTransformed(const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3> &T){
        return Ellipse(*this).Transform(R, T);
    }
    
    Ellipse Ellipse::GetTransformed(const NX::Matrix<float, 3, 3> &R){
        return Ellipse(*this).Transform(R);
    }
    
    Ellipse Ellipse::GetTransformed(const NX::Matrix<float, 4, 4> &M){
        return Ellipse(*this).Transform(M);
    }
}