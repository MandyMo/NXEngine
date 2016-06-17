/*
 *  File:    NXCone.cpp
 *  author:  张雄
 *  date:    2016_06_14
 *  purpose: define cone
 */

#include "NXCone.h"
#include "NXMatrix.h"
#include "NXAlgorithm.h"

namespace NX{
    Cone::Cone(const float fLongAxis, const float fShortAxis, const float fHeight):m_vCenter(0.0f, 0.0f, 0.0f), m_vNormal(0.0f, 1.0f, 0.0f), m_vLongAxis(1.0f, 0.0f, 0.0f), m_vShortAxis(0.0f, 0.0f, 1.0f){
        m_fLongAxis   = fLongAxis;
        m_fShortAxis  = fShortAxis;
        m_fHeight     = fHeight;
    }

    Cone::Cone(const float fLongAxis, const float fShortAxis, const float fHeight, const NX::Matrix<float, 3, 3> &R):m_vCenter(0.0f, 0.0f, 0.0f), m_vNormal(0.0f, 1.0f, 0.0f), m_vLongAxis(1.0f, 0.0f, 0.0f), m_vShortAxis(0.0f, 0.0f, 1.0f){
        m_fLongAxis   = fLongAxis;
        m_fShortAxis  = fShortAxis;
        m_fHeight     = fHeight;
        Transform(R);
    }


    Cone::Cone(const float fLongAxis, const float fShortAxis, const float fHeight, const NX::Matrix<float, 4, 4> &M):m_vCenter(0.0f, 0.0f, 0.0f), m_vNormal(0.0f, 1.0f, 0.0f), m_vLongAxis(1.0f, 0.0f, 0.0f), m_vShortAxis(0.0f, 0.0f, 1.0f){
        m_fLongAxis   = fLongAxis;
        m_fShortAxis  = fShortAxis;
        m_fHeight     = fHeight;
        Transform(M);
    }

    Cone::Cone(const float fLongAxis, const float fShortAxis, const float fHeight, const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3> &T):m_vCenter(0.0f, 0.0f, 0.0f), m_vNormal(0.0f, 1.0f, 0.0f), m_vLongAxis(1.0f, 0.0f, 0.0f), m_vShortAxis(0.0f, 0.0f, 1.0f){
        m_fLongAxis   = fLongAxis;
        m_fShortAxis  = fShortAxis;
        m_fHeight     = fHeight;
        Transform(R, T);
    }


    Cone::Cone(const float fLongAxis, const float fShortAxis, const float fHeight, const NX::vector<float, 3> &T, const NX::Matrix<float, 3, 3> &R):m_vCenter(0.0f, 0.0f, 0.0f), m_vNormal(0.0f, 1.0f, 0.0f), m_vLongAxis(1.0f, 0.0f, 0.0f), m_vShortAxis(0.0f, 0.0f, 1.0f){
        m_fLongAxis   = fLongAxis;
        m_fShortAxis  = fShortAxis;
        m_fHeight     = fHeight;
        Transform(T, R);
    }
    
    Cone& Cone::Transform(const NX::Matrix<float, 3, 3> &R){
        NX::TransformPoint       (m_vCenter,    R);
        NX::TransformNormalVector(m_vNormal,    R);
        NX::TransformVector      (m_vLongAxis,  R);
        NX::TransformVector      (m_vShortAxis, R);
        return *this;
    }
    
    Cone& Cone::Transform(const NX::Matrix<float, 4, 4> &M){
        NX::TransformPoint       (m_vCenter,    M);
        NX::TransformNormalVector(m_vNormal,    M);
        NX::TransformVector      (m_vLongAxis,  M);
        NX::TransformVector      (m_vShortAxis, M);
        return *this;
    }
    
    Cone& Cone::Transform(const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3>    &T){
        return Transform(NX::GetRTMatrix(R, T));
    }
    
    Cone& Cone::Transform(const NX::vector<float, 3>    &T, const NX::Matrix<float, 3, 3> &R){
        return Transform(NX::GetTRMatrix(T, R));
    }
    
    Cone& Cone::Translate(const NX::vector<float, 3> &T){
        m_vCenter += T;
        return *this;
    }
    
    Cone Cone::GetTransformed(const NX::Matrix<float, 3, 3> &R) const{
        return Cone(*this).Transform(R);
    }
    
    Cone Cone::GetTransformed(const NX::Matrix<float, 4, 4> &M) const{
        return Cone(*this).Transform(M);
    }
    
    Cone Cone::GetTransformed(const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3>    &T) const{
        return Cone(*this).Transform(R, T);
    }
    
    Cone Cone::GetTransformed(const NX::vector<float, 3>    &T, const NX::Matrix<float, 3, 3> &R) const{
        return Cone(*this).Transform(T, R);
    }
    
    Cone Cone::GetTranslated(const NX::vector<float, 3> &T) const{
        return Cone(*this).Translate(T);
    }
    
    bool Cone::InCone(const NX::vector<float, 3> &point) const{
        const NX::vector<float, 3> v = point - GetCenter();
        const float lx = NX::Dot(v, GetLongAxis());
        const float ly = NX::Dot(v, GetNormal());
        const float lz = NX::Dot(v, GetShortAxis());
        if(ly < kf0 || ly > GetHeight()){
            return false;
        }
        
        const float t  = kf1 - ly / GetHeight();
        const float rx = GetLongAxisLength()  * t;
        const float rz = GetShortAxisLength() * t;
        const float dx = lx / rx;
        const float dz = lz / rz;
        return dx * dx + dz * dz <= kf1;
    }
    
    bool Cone::OnCone(const NX::vector<float, 3> &point) const{
        const NX::vector<float, 3> v = point - GetCenter();
        const float lx = NX::Dot(v, GetLongAxis());
        const float ly = NX::Dot(v, GetNormal());
        const float lz = NX::Dot(v, GetShortAxis());
        if(ly < kf0 || ly > GetHeight()){
            return false;
        }
        
        const float t  = kf1 - ly / GetHeight();
        const float rx = GetLongAxisLength()  * t;
        const float rz = GetShortAxisLength() * t;
        const float dx = lx / rx;
        const float dz = lz / rz;
        return NX::Equalfloat(dx * dx + dz * dz, kf1);
    }
}