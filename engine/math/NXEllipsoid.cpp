/*
 *  File:    NXEllipsoid.h
 *  author:  张雄
 *  date:    2016_06_013
 *  purpose: define ellipsoid
 */


#include "NXEllipsoid.h"
#include "NXAlgorithm.h"
#include "NXMatrix.h"

namespace NX {
    Ellipsoid::Ellipsoid(const float fSemiAxisX, const float fSemiAxisY, const float fSemiAxisZ, const NX::vector<float, 3> &T,    const NX::Matrix<float, 3, 3> &R):m_vCenter(0.0f, 0.0f, 0.0f), m_vSemiAxisX(1.0f, 0.0f, 0.0f), m_vSemiAxisY(0.0f, 1.0f, 0.0f), m_vSemiAxisZ(0.0f, 0.0f, 1.0f){
        m_fSemiAxisX = fSemiAxisX;
        m_fSemiAxisY = fSemiAxisY;
        m_fSemiAxisZ = fSemiAxisZ;
        Transform(T, R);
    }

    Ellipsoid::Ellipsoid(const float fSemiAxisX, const float fSemiAxisY, const float fSemiAxisZ, const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3>    &T):m_vCenter(0.0f, 0.0f, 0.0f), m_vSemiAxisX(1.0f, 0.0f, 0.0f), m_vSemiAxisY(0.0f, 1.0f, 0.0f), m_vSemiAxisZ(0.0f, 0.0f, 1.0f){
        m_fSemiAxisX = fSemiAxisX;
        m_fSemiAxisY = fSemiAxisY;
        m_fSemiAxisZ = fSemiAxisZ;
        Transform(R, T);
    }

    Ellipsoid::Ellipsoid(const float fSemiAxisX, const float fSemiAxisY, const float fSemiAxisZ, const NX::Matrix<float, 3, 3> &R):m_vCenter(0.0f, 0.0f, 0.0f), m_vSemiAxisX(1.0f, 0.0f, 0.0f), m_vSemiAxisY(0.0f, 1.0f, 0.0f), m_vSemiAxisZ(0.0f, 0.0f, 1.0f){
        m_fSemiAxisX = fSemiAxisX;
        m_fSemiAxisY = fSemiAxisY;
        m_fSemiAxisZ = fSemiAxisZ;
        Transform(R);
    }

    Ellipsoid::Ellipsoid(const float fSemiAxisX, const float fSemiAxisY, const float fSemiAxisZ, const NX::Matrix<float, 4, 4> &M):m_vCenter(0.0f, 0.0f, 0.0f), m_vSemiAxisX(1.0f, 0.0f, 0.0f), m_vSemiAxisY(0.0f, 1.0f, 0.0f), m_vSemiAxisZ(0.0f, 0.0f, 1.0f){
        m_fSemiAxisX = fSemiAxisX;
        m_fSemiAxisY = fSemiAxisY;
        m_fSemiAxisZ = fSemiAxisZ;
        Transform(M);
    }

    Ellipsoid& Ellipsoid::Transform(const NX::Matrix<float, 3, 3> &R){
        TransformPoint (m_vCenter,    R);
        TransformVector(m_vSemiAxisX, R);
        TransformVector(m_vSemiAxisY, R);
        TransformVector(m_vSemiAxisZ, R);
        return *this;
    }
    
    Ellipsoid& Ellipsoid::Transform(const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3>    &T){
        return Transform(NX::CreateTransformMatrixByRotateAndTranslation(R, T));
    }
    
    Ellipsoid& Ellipsoid::Transform(const NX::vector<float, 3>    &T, const NX::Matrix<float, 3, 3> &R){
        return Transform(NX::CreateTransformMatrixByTranslationAndRotate(T, R));
    }
    
    Ellipsoid& Ellipsoid::Transform(const NX::Matrix<float, 4, 4> &M){
        TransformPoint (m_vCenter,    M);
        TransformVector(m_vSemiAxisX, M);
        TransformVector(m_vSemiAxisY, M);
        TransformVector(m_vSemiAxisZ, M);
        return *this;
    }

    Ellipsoid Ellipsoid::GetTransformed(const NX::Matrix<float, 3, 3> &R) const{
        return Ellipsoid(*this).Transform(R);
    }
    
    Ellipsoid Ellipsoid::GetTransformed(const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3>    &T) const{
        return Ellipsoid(*this).Transform(R, T);
    }
    
    Ellipsoid Ellipsoid::GetTransformed(const NX::vector<float, 3>    &T, const NX::Matrix<float, 3, 3> &R) const{
        return Ellipsoid(*this).Transform(T, R);
    }
    
    Ellipsoid Ellipsoid::GetTransformed(const NX::Matrix<float, 4, 4> &M) const{
        return Ellipsoid(*this).Transform(M);
    }
    
    bool Ellipsoid::InEllipsoid(const NX::vector<float, 3> &point) const{
        const NX::vector<float, 3> v = point - GetCenter();
        const float lx = NX::Dot(v, GetAxisX());
        const float ly = NX::Dot(v, GetAxisY());
        const float lz = NX::Dot(v, GetAxisZ());
        const float dx = lx / m_fSemiAxisX;
        const float dy = ly / m_fSemiAxisY;
        const float dz = lz / m_fSemiAxisZ;
        return dx * dx + dy * dy + dz * dz <= kf1;
    }
    
    bool Ellipsoid::OnEllipsoid(const NX::vector<float, 3> &point) const{
        const NX::vector<float, 3> v = point - GetCenter();
        const float lx = NX::Dot(v, GetAxisX());
        const float ly = NX::Dot(v, GetAxisY());
        const float lz = NX::Dot(v, GetAxisZ());
        const float dx = lx / m_fSemiAxisX;
        const float dy = ly / m_fSemiAxisY;
        const float dz = lz / m_fSemiAxisZ;
        return NX::Equalfloat(dx * dx + dy * dy + dz * dz, kf1);
    }
}
