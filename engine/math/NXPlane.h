/*
 *  File:    NXPlane.h
 *  author:  张雄
 *  date:    2016_05_13
 *  purpose: define plane
 */

#ifndef __ZX_NXENGINE_PLANE_H__
#define __ZX_NXENGINE_PLANE_H__

#include "NXVector.h"
#include "NXMatrix.h"
#include "NXAlgorithm.h"
#include <utility>

namespace NX {
    class Line;
    class Plane{
    public:
        inline explicit Plane(){ /*empty*/ }
        inline explicit Plane(const float nx, const float ny, const float nz, const float distance):m_vPlaneNormal(nx, ny, nz), m_fDistFromOriginal(distance){
            NX::Normalize(m_vPlaneNormal);
        }

        template<typename T>
        inline explicit Plane(const NX::vector<T, 4> &L):m_vPlaneNormal(L.x, L.y, L.z),m_fDistFromOriginal(L.w){
            Normalize();
        }

        inline explicit Plane(const NX::vector<float, 3> &a, const NX::vector<float, 3> &b, const NX::vector<float, 3> &c){
            NX::vector<float, 3> v1 = a - b;
            NX::vector<float, 3> v2 = a - c;
            m_vPlaneNormal      = NX::Cross(v1, v2);
            m_fDistFromOriginal = -::NX::Dot(m_vPlaneNormal, a);
            Normalize();
        }

        Plane(const Plane &rhs):m_vPlaneNormal(rhs.m_vPlaneNormal), m_fDistFromOriginal(rhs.m_fDistFromOriginal){}
        
        explicit Plane(const vector<float, 3> &Normal, const vector<float, 3> &PointInPlane):m_vPlaneNormal(Normal), m_fDistFromOriginal(-NX::Dot(PointInPlane, Normal)){
            Normalize();
        }

        explicit Plane(const vector<float, 3> &Normal, const float fDistFromOriginal):m_vPlaneNormal(NX::GetNormalized(Normal)), m_fDistFromOriginal(fDistFromOriginal){
        }

    public:
        template<typename T, typename U>
        inline Plane& Transform(const NX::Matrix<T, 3, 3> &matrix, const NX::vector<U, 3> &translation){
            Matrix<T, 4, 4> M;
            {
                M.template SetRow<T, 3>(0, matrix[0]);
                M.template SetRow<T, 3>(1, matrix[1]);
                M.template SetRow<T, 3>(2, matrix[2]);
                M.template SetCol<U, 3>(3, translation);
                M[3][3] = T(1);
            }
            return Transform(M);
        }

        template<typename T>
        inline Plane& Transform(const NX::Matrix<T, 4, 4> &matrix){
            const Matrix<T, 4, 1> &M = Transpose(Reverse(matrix)) * float4(m_vPlaneNormal.x, m_vPlaneNormal.y, m_vPlaneNormal.z, m_fDistFromOriginal);
            m_vPlaneNormal.Set(M[0][0], M[1][0], M[2][0]);
            m_fDistFromOriginal = M[3][0];
            return *this;
        }

        template<typename T, typename U>
        inline Plane GetTransformed(const NX::Matrix<T, 3, 3> &matrix, const NX::vector<U, 3> &translation){
            return Plane(*this).Transform(matrix, translation);
        }

        template<typename T>
        inline Plane GetTransformed(const NX::Matrix<T, 4, 4> &matrix){
            return Plane(*this).Transform(matrix);
        }
        
        inline Plane& Normalize(){
            float len = ::NX::Length(m_vPlaneNormal);
            float Mult = 1.0f / len;
            m_vPlaneNormal.x *= Mult;
            m_vPlaneNormal.y *= Mult;
            m_vPlaneNormal.z *= Mult;
            m_fDistFromOriginal *= Mult;
            return *this;
        }

    public:
        std::pair<bool, Line>   Intersect(const Plane &rhs) const;  //平面交线
        std::pair<bool, float3> Intersect(const Line  &rhs) const;  //直线与平面交点
        float  Distance(const vector<float, 3> &rhs) const;         //点到平面距离
    public:
        vector<float, 3> m_vPlaneNormal;
        float            m_fDistFromOriginal;
    };
}

#endif  //!__ZX_NXENGINE_PLANE_H__