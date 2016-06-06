/*
 *  File:    NXTriangle.cpp
 *  author:  张雄
 *  date:    2016_06_06
 *  purpose: define triangle
 */


#include "NXTriangle.h"
#include "NXCircle.h"
#include "NXMatrix.h"
#include "NXAlgorithm.h"

namespace NX{
    
    /*
     *  外接圆圆心
     */
    NX::vector<float, 3> Triangle::GetCircumCentre() const{
        const NX::vector<float, 3> e1 = m_vPtC - m_vPtB;
        const NX::vector<float, 3> e2 = m_vPtA - m_vPtC;
        const NX::vector<float, 3> e3 = m_vPtB - m_vPtA;
        const float d1 = -NX::Dot(e2, e3);
        const float d2 = -NX::Dot(e3, e1);
        const float d3 = -NX::Dot(e1, e2);
        const float c1 = d2 * d3;
        const float c2 = d1 * d3;
        const float c3 = d1 * d2;
        const float c  = c1 + c2 + c3;
        const float Mult = 0.5f / c;
        return  Mult * (c2 + c3) * m_vPtA + Mult * (c3 + c1) * m_vPtB + Mult * (c1 + c2) * m_vPtC;
    }
    
    /**
     *  内接圆圆心
     */
    NX::vector<float, 3> Triangle::GetHeart() const{
        const NX::vector<float, 3> e1 = m_vPtC - m_vPtB;
        const NX::vector<float, 3> e2 = m_vPtA - m_vPtC;
        const NX::vector<float, 3> e3 = m_vPtB - m_vPtA;
        const float l1 = NX::Length(e1);
        const float l2 = NX::Length(e2);
        const float l3 = NX::Length(e3);
        const float Mult = 0.5f / (l1 + l2 + l3);
        return l1 * Mult * m_vPtA + l2 * Mult * m_vPtB + l3 * Mult * m_vPtC;
    }
    
    
    /**
     *  外接圆
     */
    Circle Triangle::GetGetCircumCircle() const{
        return Circle(m_vPtA, m_vPtB, m_vPtC);
    }
    
    /**
     *  内接圆
     */
    Circle Triangle::GetInscribedCircle() const{
        const NX::vector<float, 3> e1 = m_vPtC - m_vPtB;
        const NX::vector<float, 3> e2 = m_vPtA - m_vPtC;
        const NX::vector<float, 3> e3 = m_vPtB - m_vPtA;
        const float l1 = NX::Length(e1);
        const float l2 = NX::Length(e2);
        const float l3 = NX::Length(e3);
        const float p  = (l1 + l2 + l3) * 0.5f;
        const float Mult = 1.0f / p;
        const NX::vector<float, 3> ptCenter =  l1 * Mult * m_vPtA + l2 * Mult * m_vPtB + l3 * Mult * m_vPtC;
        const float s = std::sqrt(p * (p - l1) * (p - l2) * (p - l3));/*Heron formula*/
        const float r = s * Mult;
        const NX::vector<float, 3> n = NX::GetNormalized(NX::Cross(e2, e3));
        return Circle(ptCenter, n, r);
    }
    
    NX::vector<float, 3> Triangle::GetPointByBaryCentricCoord(const NX::vector<float, 3> &coord) const{
        return m_vPtA * coord.x + m_vPtB * coord.y + m_vPtC * coord.z;
    }
    
    NX::vector<float, 3> Triangle::GetPointByBaryCentricCoord(const float x, const float y, const float z) const{
        return x * m_vPtA + y * m_vPtB + z * m_vPtC;
    }
    
    NX::vector<float, 3> Triangle::GetBaryCentricCoord(const NX::vector<float, 3> &point) const{
        const NX::vector<float, 3> e1(m_vPtA - m_vPtC);
        const NX::vector<float, 3> e2(m_vPtB - m_vPtC);
        const NX::vector<float, 3> r(point - m_vPtC);
        NX::Matrix<float, 2, 2> m;
        NX::vector<float, 2> result;
        {
            m[0][0] = NX::Dot(e1, e1), m[0][1] = NX::Dot(e1, e2), result[0] = NX::Dot(r, e1);
            m[1][0] = m[0][1],         m[1][1] = NX::Dot(e2, e2), result[1] = NX::Dot(r, e2);
        }
        const std::pair<bool, NX::vector<float, 2> > solv = SolveEquation(m, result);
        return NX::vector<float, 3>(solv.second.x, solv.second.y, 1.0f - solv.second.x - solv.second.y);
    }
    
    NX::vector<float, 3> Triangle::GetBaryCentricCoord(const float x, const float y, const float z) const{
        return GetBaryCentricCoord(NX::vector<float, 3>(x, y, z));
    }
    
    Triangle& Triangle::Transform(const NX::Matrix<float, 3, 3> &matrix){
        NX::TransformPoint(m_vPtA, matrix);
        NX::TransformPoint(m_vPtB, matrix);
        NX::TransformPoint(m_vPtC, matrix);
        NX::TransformNormalVector(m_vNormal, matrix);
        return *this;
    }
    
    Triangle& Triangle::Transform(const NX::Matrix<float, 4, 4> &matrix){
        NX::TransformPoint(m_vPtA, matrix);
        NX::TransformPoint(m_vPtB, matrix);
        NX::TransformPoint(m_vPtC, matrix);
        NX::TransformNormalVector(m_vNormal, matrix);
        return *this;
    }
    
    Triangle  Triangle::GetTransformed(const NX::Matrix<float, 3, 3> &matrix){
        return Triangle(*this).Transform(matrix);
    }
    
    Triangle  Triangle::GetTransformed(const NX::Matrix<float, 4, 4> &matrix){
        return Triangle(*this).Transform(matrix);
    }
}