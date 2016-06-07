/*
 *  File:    NXCircle.h
 *  author:  张雄
 *  date:    2016_05_13
 *  purpose: define Circle
 */

#ifndef __ZX_NXENGINE_CIRCLE_H__
#define __ZX_NXENGINE_CIRCLE_H__

#include "NXVector.h"
#include "NXAlgorithm.h"

namespace NX {
    template<typename T, int Row, int Col>
    class Matrix;
    
    class Circle{
    public:
        inline explicit Circle(){
            /*empty*/
        }
        
        inline Circle(const Circle &rhs):m_vCenter(rhs.m_vCenter), m_vNormal(rhs.m_vNormal), m_fRadius(rhs.m_fRadius){
            /*empty*/
        }
        
        inline explicit Circle(const NX::float3 &ptCenter, const NX::float3 &normal, const float radius):m_vCenter(ptCenter), m_vNormal(normal), m_fRadius(radius){
            /*empty*/
        }
        
        explicit Circle(const NX::float3 &ptA, const NX::float3 &ptB, const NX::float3 &ptC);
        
        inline ~Circle(){
            /*empty*/
        }
        
    public:
        inline NX::float3 GetCenter() const{
            return m_vCenter;
        }
        
        inline float3 GetNormal() const{
            return m_vNormal;
        }
        
        inline float  GetRadius() const{
            return m_fRadius;
        }
        
        inline float  GetArea() const{
            return kfPi * m_fRadius * m_fRadius;
        }
        
        inline float  GetCircumference() const{
            return kf2Pi * m_fRadius;
        }
    
    public:
        inline bool InCircle(const NX::vector<float, 3> &point) const{
            return NX::LengthSquare(point - m_vCenter) <= m_fRadius * m_fRadius;
        }
        
        inline bool OnCircle(const NX::vector<float, 3> &point, const float Delta = NX::Epsilon<float>::m_Epsilon) const{
            return NX::Equalfloat(NX::Length(point - m_vCenter), Delta);
        }
        
    public:
        inline Circle  GetTransformed(const NX::Matrix<float, 3, 3> &matrix) const{
            return Circle(*this).Transform(matrix);
        }
        
        inline Circle  GetTransformed(const NX::Matrix<float, 4, 4> &matrix) const{
            return Circle(*this).Transform(matrix);
        }
        
        inline Circle  GetTranslated(const NX::float3 &v) const{
            return Circle(*this).Translate(v);
        }
        
        Circle& Transform(const NX::Matrix<float, 3, 3> &matrix);
        Circle& Transform(const NX::Matrix<float, 4, 4> &matrix);
        
        Circle& Translate(const NX::float3 &v){
            m_vCenter += v;
            return *this;
        }
        
    public:
        NX::float3   m_vCenter;
        NX::float3   m_vNormal;
        float        m_fRadius;
    };

}

#endif // !__ZX_NXENGINE_CIRCLE_H__