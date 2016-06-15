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
    Ellipse::Ellipse(const float fLongAxis, const float fShortAxis, const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3> &T):m_vLongAxis(1.0f, 0.0f, 0.0f), m_vShortAxis(0.0f, 0.0f, 1.0f), m_vNormal(0.0f, 1.0f, 0.0f), m_vCenter(0.0f, 0.0f, 0.0f){
        m_fLongAxis   = fLongAxis;
        m_fShortAxis  = fShortAxis;
        Transform(R, T);
    }
    
    
    Ellipse::Ellipse(const float fLongAxis, const float fShortAxis, const NX::vector<float, 3> &T, const NX::Matrix<float, 3, 3> &R):m_vLongAxis(1.0f, 0.0f, 0.0f), m_vShortAxis(0.0f, 0.0f, 1.0f), m_vNormal(0.0f, 1.0f, 0.0f), m_vCenter(0.0f, 0.0f, 0.0f){
        m_fLongAxis   = fLongAxis;
        m_fShortAxis  = fShortAxis;
        Transform(T, R);
    }
    
    Ellipse::Ellipse(const float fLongAxis, const float fShortAxis, const NX::Matrix<float, 4, 4> &M):m_vLongAxis(1.0f, 0.0f, 0.0f), m_vShortAxis(0.0f, 0.0f, 1.0f), m_vNormal(0.0f, 1.0f, 0.0f), m_vCenter(0.0f, 0.0f, 0.0f){
        m_fLongAxis   = fLongAxis;
        m_fShortAxis  = fShortAxis;
        Transform(M);
    }
    
    Ellipse::Ellipse(const float fLongAxis, const float fShortAxis, const NX::Matrix<float, 3, 3> &M):m_vLongAxis(1.0f, 0.0f, 0.0f), m_vShortAxis(0.0f, 0.0f, 1.0f), m_vNormal(0.0f, 1.0f, 0.0f), m_vCenter(0.0f, 0.0f, 0.0f){
        m_fLongAxis   = fLongAxis;
        m_fShortAxis  = fShortAxis;
        Transform(M);
    }

    Ellipse::Ellipse(const float fLongAxis, const float fShortAxis):m_fLongAxis(fLongAxis), m_fShortAxis(fShortAxis), m_vLongAxis(1.0f, 0.0f, 0.0f), m_vShortAxis(0.0f, 0.0f, 1.0f), m_vCenter(0.0f, 0.0f, 0.0f), m_vNormal(0.0f, 1.0f, 0.0f){
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
        NX::TransformPoint       (m_vCenter,         R);
        NX::TransformVector      (m_vLongAxis,       R);
        NX::TransformVector      (m_vShortAxis,      R);
        NX::TransformNormalVector(m_vNormal,         R);
        return *this;
    }
    
    Ellipse& Ellipse::Transform(const NX::Matrix<float, 4, 4> &M){
        NX::TransformPoint       (m_vCenter,         M);
        NX::TransformVector      (m_vLongAxis,       M);
        NX::TransformVector      (m_vShortAxis,      M);
        NX::TransformNormalVector(m_vNormal,         M);
        return *this;
    }
    
    Ellipse& Ellipse::Translate(const NX::vector<float, 3> &T){
        m_vCenter += T;
        return *this;
    }
    
    Ellipse Ellipse::GetTransformed(const NX::vector<float, 3> &T, const NX::Matrix<float, 3, 3> &R) const{
        return Ellipse(*this).Transform(T, R);
    }
    
    Ellipse Ellipse::GetTransformed(const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3> &T) const{
        return Ellipse(*this).Transform(R, T);
    }
    
    Ellipse Ellipse::GetTransformed(const NX::Matrix<float, 3, 3> &R) const{
        return Ellipse(*this).Transform(R);
    }
    
    Ellipse Ellipse::GetTransformed(const NX::Matrix<float, 4, 4> &M) const{
        return Ellipse(*this).Transform(M);
    }
    
    Ellipse Ellipse::GetTranslated(const NX::vector<float, 3> &T) const{
        return Ellipse(*this).Translate(T);
    }
    
    bool Ellipse::InEllipse(const NX::vector<float, 3> &point) const{
        const NX::vector<float, 3> v = point - GetCenter();
        const float lx = NX::Dot(v, GetLongAxis());
        const float ly = NX::Dot(v, GetShortAxis());
        const float dx = lx / GetLongAxisLength();
        const float dy = ly / GetShortAxisLength();
        return NX::EqualZero(NX::Dot(v, GetNormal())) && dx * dx + dy * dy <= kf1;
    }
    
    bool Ellipse::OnEllipse(const NX::vector<float, 3> &point) const{
        const NX::vector<float, 3> v = point - GetCenter();
        const float lx = NX::Dot(v, GetLongAxis());
        const float ly = NX::Dot(v, GetShortAxis());
        const float dx = lx / GetLongAxisLength();
        const float dy = ly / GetShortAxisLength();
        return NX::EqualZero(NX::Dot(v, GetNormal())) && NX::Equalfloat(dx * dx + dy * dy , kf1);
    }
}