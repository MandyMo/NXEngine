/*
 *  File:    NXSphere.h
 *  author:  张雄
 *  date:    2016_05_13
 *  purpose: define sphere
 */

#ifndef __ZX_NXENGINE_SPHERE_H__
#define __ZX_NXENGINE_SPHERE_H__

#include "NXVector.h"
#include "NXAlgorithm.h"

namespace NX {
    template<typename T, int Row, int Col>
    class Matrix;
    
    class Line;
    class Plane;
    
    class Sphere{
    public:
        Sphere(){
            /*empty*/
        }
        
        inline explicit Sphere(const float3 &ptCenter, const float3 &ptOnSphere):m_vCenter(ptCenter), m_fRadius(NX::Length(ptOnSphere - ptCenter)){
            /*empty*/
        }
        
        inline explicit Sphere(const float3 &ptCenter, const float fRadius):m_vCenter(ptCenter), m_fRadius(fRadius){
            /*empty*/
        }
        
        explicit Sphere(const float3 &ptA, const float3 &ptB, const float3 &ptC, const float3 &ptD);
        
        inline Sphere(const Sphere &rhs):m_vCenter(rhs.m_vCenter), m_fRadius(rhs.m_fRadius){
            /*empty*/
        }
        
        inline  ~Sphere(){
            /*empty*/
        }
        
    public:
        inline float  GetVolume() const{
            return 4.0f / 3.0f * kfPi * m_fRadius * m_fRadius * m_fRadius;
        }
        
        inline float  GetArea()   const{
            return 4.0f * kfPi * m_fRadius * m_fRadius;
        }
        
        inline float  GetRadius() const{
            return m_fRadius;
        }
        
        inline float3 GetCenter() const{
            return m_vCenter;
        }
        
    public:
        inline Sphere  GetTransformed(const Matrix<float, 3, 3> &matrix) const{
            return Sphere(*this).Transform(matrix);
        }
        
        inline Sphere  GetTransformed(const Matrix<float, 4, 4> &matrix) const{
            return Sphere(*this).Transform(matrix);
        }
        
        inline Sphere  GetTranslated(const float3 &v) const{
            return Sphere(*this).Translate(v);
        }
        
        Sphere& Transform(const Matrix<float, 3, 3> &matrix);
        Sphere& Transform(const Matrix<float, 4, 4> &matrix);
        Sphere& Translate(const float3 &v);
        
    public:
        bool Intersect(const Sphere &rhs) const;
        bool TangentWithLine(const Line &lne) const;
        bool TangentWithPlane(const Plane &plane) const;
        bool TangentWithSphere(const Sphere &rhs) const;
        
    public:
        float   m_fRadius;
        float3  m_vCenter;
    };
}

#endif