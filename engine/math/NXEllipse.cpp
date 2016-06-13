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
    
    
    Ellipse::Ellipse(const float fLongAxis, const float fShortAxis, const NX::vector<float, 3> &T, const NX::Matrix<float, 3, 3> &R):m_vShortSemiAxis(0.0f, 0.0f, 1.0f), m_vNormal(0.0f, 1.0f, 0.0f), m_vCenter(0.0f, 0.0f, 0.0f){
        m_fLongSemiAxis   = fLongAxis;
        m_fShortSemiAxis  = fShortAxis;
        Transform(T, R);
    }
    
    Ellipse::Ellipse(const float fLongAxis, const float fShortAxis, const NX::Matrix<float, 4, 4> &M):m_vLongSemiAxis(1.0f, 0.0f, 0.0f), m_vShortSemiAxis(0.0f, 0.0f, 1.0f), m_vNormal(0.0f, 1.0f, 0.0f), m_vCenter(0.0f, 0.0f, 0.0f){
        m_fLongSemiAxis   = fLongAxis;
        m_fShortSemiAxis  = fShortAxis;
        Transform(M);
    }
    
    Ellipse::Ellipse(const float fLongAxis, const float fShortAxis, const NX::Matrix<float, 3, 3> &M):m_vLongSemiAxis(1.0f, 0.0f, 0.0f), m_vShortSemiAxis(0.0f, 0.0f, 1.0f), m_vNormal(0.0f, 1.0f, 0.0f), m_vCenter(0.0f, 0.0f, 0.0f){
        m_fLongSemiAxis   = fLongAxis;
        m_fShortSemiAxis  = fShortAxis;
        Transform(M);
    }

    Ellipse::Ellipse(const float fLongAxis, const float fShortAxis):m_fLongSemiAxis(fLongAxis), m_fShortSemiAxis(fShortAxis), m_vLongSemiAxis(1.0f, 0.0f, 0.0f), m_vShortSemiAxis(0.0f, 1.0f, 0.0f), m_vCenter(0.0f, 0.0f, 0.0f), m_vNormal(0.0f, 0.0f, 1.0f){
        /*empty*/
    }
    
    Ellipse& Ellipse::Transform(const NX::vector<float, 3> &T, const NX::Matrix<float, 3, 3> &R){
        NX::Matrix<float, 4, 4> M = NX::CreateTransformMatrixByTranslationAndRotate(T, R);
        Transform(M);
        return *this;
    }
    
    Ellipse& Ellipse::Transform(const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3> &T){
        NX::Matrix<float, 4, 4> M = NX::CreateTransformMatrixByRotateAndTranslation(R, T);
        Transform(M);
        return *this;
    }
    
    Ellipse& Ellipse::Transform(const NX::Matrix<float, 3, 3> &R){
        NX::TransformPoint(m_vCenter,         R);
        NX::TransformVector(m_vLongSemiAxis,  R);
        NX::TransformVector(m_vShortSemiAxis, R);
        NX::TransformNormalVector(m_vNormal,  R);
        return *this;
    }
    
    Ellipse& Ellipse::Transform(const NX::Matrix<float, 4, 4> &M){
        NX::TransformPoint(m_vCenter,         M);
        NX::TransformVector(m_vLongSemiAxis,  M);
        NX::TransformVector(m_vShortSemiAxis, M);
        NX::TransformNormalVector(m_vNormal,  M);
        return *this;
    }
    
    Ellipse Ellipse::GetTransformed(const NX::vector<float, 3> &T, const NX::Matrix<float, 3, 3> &R){
        return Ellipse(*this).Transform(T, R);
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
    
    bool Ellipse::InEllipse(const NX::vector<float, 3> &point) const{
        const NX::vector<float, 3> v = point - GetCenter();
        const float lx = NX::Dot(v, GetLongSemiAxis());
        const float ly = NX::Dot(v, GetShortSemiAxis());
        const float dx = lx / GetLongSemiAxisLength();
        const float dy = ly / GetShortSemiAxisLength();
        return dx * dx + dy * dy <= kf1;
    }
    
    bool Ellipse::OnEllipse(const NX::vector<float, 3> &point) const{
        const NX::vector<float, 3> v = point - GetCenter();
        const float lx = NX::Dot(v, GetLongSemiAxis());
        const float ly = NX::Dot(v, GetShortSemiAxis());
        const float dx = lx / GetLongSemiAxisLength();
        const float dy = ly / GetShortSemiAxisLength();
        return NX::Equalfloat(dx * dx + dy * dy , kf1);
    }
}