/*
 *  File:    NXTriangle.h
 *  author:  张雄
 *  date:    2016_06_06
 *  purpose: define triangle
 */

#ifndef __ZX_NXENGINE_TRIANGLE_H__
#define __ZX_NXENGINE_TRIANGLE_H__

#include "NXVector.h"
#include "NXAlgorithm.h"

namespace NX {
    class Circle;
    
    class Triangle{
    public:
        inline explicit Triangle(const NX::vector<float, 3> &ptA, const NX::vector<float, 3> &ptB, const NX::vector<float, 3> &ptC):
        m_vPtA(ptA), m_vPtB(ptB), m_vPtC(ptC), m_vNormal(NX::GetNormalized(NX::Cross(ptB- ptA, ptC - ptA))){
            /*empty*/
        }
        
        inline Triangle(const Triangle &rhs):m_vPtA(rhs.m_vPtA), m_vPtB(rhs.m_vPtB), m_vPtC(rhs.m_vPtC), m_vNormal(rhs.m_vNormal){
            /*empty*/
        }
        
        inline Triangle(){
            /*empty*/
        }
        
        ~Triangle(){
            /*empty*/
        }
        
    public:
        inline NX::vector<float, 3> GetPointA() const{
            return m_vPtA;
        }
        
        inline NX::vector<float, 3> GetPointB() const{
            return m_vPtB;
        }
        
        inline NX::vector<float, 3> GetPointC() const{
            return m_vPtC;
        }
        
        inline NX::vector<float, 3> GetNormal() const{
            return m_vNormal;
        }
        
    public:
        /*
         *  外接圆圆心
         */
        NX::vector<float, 3> GetCircumCentre() const;
        
        /**
         *  内接圆圆心
         */
        NX::vector<float, 3> GetHeart() const;
        
        
        /**
         *  外接圆
         */
        Circle GetGetCircumCircle() const;
        
        /**
         *  内接圆圆心
         */
        Circle GetInscribedCircle() const;
    
    public:
        NX::vector<float, 3> GetPointByBaryCentricCoord(const NX::vector<float, 3> &coord) const;
        
        NX::vector<float, 3> GetPointByBaryCentricCoord(const float x, const float y, const float z) const;
        
        NX::vector<float, 3> GetBaryCentricCoord(const NX::vector<float, 3> &point) const;
        
        NX::vector<float, 3> GetBaryCentricCoord(const float x, const float y, const float z) const;
        
    public:
        Triangle& Transform(const NX::Matrix<float, 3, 3> &matrix);
        Triangle& Transform(const NX::Matrix<float, 4, 4> &matrix);
        Triangle& Transform(const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3>    &T);
        Triangle& Transform(const NX::vector<float, 3>    &T, const NX::Matrix<float, 3, 3> &R);
        Triangle& Translate(const NX::vector<float, 3> &T);
        
        Triangle  GetTransformed(const NX::Matrix<float, 3, 3> &matrix) const;
        Triangle  GetTransformed(const NX::Matrix<float, 4, 4> &matrix) const;
        Triangle  GetTransformed(const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3>    &T) const;
        Triangle  GetTransformed(const NX::vector<float, 3>    &T, const NX::Matrix<float, 3, 3> &R) const;
        Triangle  GetTranslated(const NX::vector<float, 3> &T) const;
    private:
        NX::vector<float, 3>   m_vPtA;
        NX::vector<float, 3>   m_vPtB;
        NX::vector<float, 3>   m_vPtC;
        NX::vector<float, 3>   m_vNormal;
    };
}

#endif