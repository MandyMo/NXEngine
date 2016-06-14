/*
 *  File:    NXCylinder.cpp
 *  author:  张雄
 *  date:    2016_06_14
 *  purpose: define Cylinder
 */

#include "NXCylinder.h"
#include "NXMatrix.h"
#include "NXAlgorithm.h"

namespace NX{
    Cylinder::Cylinder(const float fLongAxis, const float fShortAxis, const float fHeight):m_vCenter(0.0f, 0.0f, 0.0f), m_vNormal(0.0f, 1.0f, 0.0f), m_vLongAxis(1.0f, 0.0f, 0.0f), m_vShortAxis(0.0f, 0.0f, 1.0f){
        m_fLongAxis   = fLongAxis;
        m_fShortAxis  = fShortAxis;
        m_fHeight     = fHeight;
    }
    
    Cylinder::Cylinder(const float fLongAxis, const float fShortAxis, const float fHeight, const NX::Matrix<float, 3, 3> &R):m_vCenter(0.0f, 0.0f, 0.0f), m_vNormal(0.0f, 1.0f, 0.0f), m_vLongAxis(1.0f, 0.0f, 0.0f), m_vShortAxis(0.0f, 0.0f, 1.0f){
        m_fLongAxis   = fLongAxis;
        m_fShortAxis  = fShortAxis;
        m_fHeight     = fHeight;
        Transform(R);
    }
    
    Cylinder::Cylinder(const float fLongAxis, const float fShortAxis, const float fHeight, const NX::Matrix<float, 4, 4> &M):m_vCenter(0.0f, 0.0f, 0.0f), m_vNormal(0.0f, 1.0f, 0.0f), m_vLongAxis(1.0f, 0.0f, 0.0f), m_vShortAxis(0.0f, 0.0f, 1.0f){
        m_fLongAxis   = fLongAxis;
        m_fShortAxis  = fShortAxis;
        m_fHeight     = fHeight;
        Transform(M);
    }
    
    Cylinder::Cylinder(const float fLongAxis, const float fShortAxis, const float fHeight, const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3> &T):m_vCenter(0.0f, 0.0f, 0.0f), m_vNormal(0.0f, 1.0f, 0.0f), m_vLongAxis(1.0f, 0.0f, 0.0f), m_vShortAxis(0.0f, 0.0f, 1.0f){
        m_fLongAxis   = fLongAxis;
        m_fShortAxis  = fShortAxis;
        m_fHeight     = fHeight;
        Transform(R, T);
    }
    
    
    Cylinder::Cylinder(const float fLongAxis, const float fShortAxis, const float fHeight, const NX::vector<float, 3> &T, const NX::Matrix<float, 3, 3> &R):m_vCenter(0.0f, 0.0f, 0.0f), m_vNormal(0.0f, 1.0f, 0.0f), m_vLongAxis(1.0f, 0.0f, 0.0f), m_vShortAxis(0.0f, 0.0f, 1.0f){
        m_fLongAxis   = fLongAxis;
        m_fShortAxis  = fShortAxis;
        m_fHeight     = fHeight;
        Transform(T, R);
    }
    
    Cylinder& Cylinder::Transform(const NX::Matrix<float, 3, 3> &R){
        NX::TransformPoint       (m_vCenter,    R);
        NX::TransformNormalVector(m_vNormal,    R);
        NX::TransformVector      (m_vLongAxis,  R);
        NX::TransformVector      (m_vShortAxis, R);
        return *this;
    }
    
    Cylinder& Cylinder::Transform(const NX::Matrix<float, 4, 4> &M){
        NX::TransformPoint       (m_vCenter,    M);
        NX::TransformNormalVector(m_vNormal,    M);
        NX::TransformVector      (m_vLongAxis,  M);
        NX::TransformVector      (m_vShortAxis, M);
        return *this;
    }
    
    Cylinder& Cylinder::Transform(const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3>    &T){
        return Transform(NX::GetRTMatrix(R, T));
    }
    
    Cylinder& Cylinder::Transform(const NX::vector<float, 3>    &T, const NX::Matrix<float, 3, 3> &R){
        return Transform(NX::GetTRMatrix(T, R));
    }
    
    Cylinder& Cylinder::Translate(const NX::vector<float, 3> &T){
        m_vCenter += T;
        return *this;
    }
    
    Cylinder Cylinder::GetTransformed(const NX::Matrix<float, 3, 3> &R) const{
        return Cylinder(*this).Transform(R);
    }
    
    Cylinder Cylinder::GetTransformed(const NX::Matrix<float, 4, 4> &M) const{
        return Cylinder(*this).Transform(M);
    }
    
    Cylinder Cylinder::GetTransformed(const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3>    &T) const{
        return Cylinder(*this).Transform(R, T);
    }
    
    Cylinder Cylinder::GetTransformed(const NX::vector<float, 3>    &T, const NX::Matrix<float, 3, 3> &R) const{
        return Cylinder(*this).Transform(T, R);
    }
    
    Cylinder Cylinder::GetTranslated(const NX::vector<float, 3> &T) const{
        return Cylinder(*this).Translate(T);
    }
    
    bool Cylinder::InCylinder(const NX::vector<float, 3> &point) const{
        const NX::vector<float, 3> v = point - GetCenter();
        const float lx = NX::Dot(v, GetLongAxis());
        const float ly = NX::Dot(v, GetNormal());
        const float lz = NX::Dot(v, GetShortAxis());
        if(ly < kf0 || ly > GetHeight()){
            return false;
        }
        
        const float dx = lx / GetLongAxisLength();
        const float dz = lz / GetShortAxisLength();
        return dx * dx + dz * dz <= kf1;
    }
    
    bool Cylinder::OnCylinder(const NX::vector<float, 3> &point) const{
        const NX::vector<float, 3> v = point - GetCenter();
        const float lx = NX::Dot(v, GetLongAxis());
        const float ly = NX::Dot(v, GetNormal());
        const float lz = NX::Dot(v, GetShortAxis());
        if(ly < kf0 || ly > GetHeight()){
            return false;
        }
        const float dx = lx / GetLongAxisLength();
        const float dz = lz / GetShortAxisLength();
        return NX::Equalfloat(dx * dx + dz * dz, kf1);
    }
}