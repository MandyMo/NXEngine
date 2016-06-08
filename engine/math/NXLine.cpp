/*
 *  File:    NXLine.cpp
 *  author:  张雄
 *  date:    2016_05_13
 *  purpose: define Line
 */

#include "NXLine.h"
#include "NXAlgorithm.h"
#include "NXMath.h"
#include "NXPlane.h"
#include "NXMath.h"

namespace NX{
    float Line::Distance(const Line &rhs) const{//两直线距离
        float V12   = NX::Dot(m_vDirection, rhs.m_vDirection);
        float Delta = V12 * V12 - ::NX::LengthSquare(m_vDirection) * ::NX::LengthSquare(rhs.m_vDirection);
        if(NX::NXAbs(Delta) < Epsilon<float>::m_Epsilon){//line parallel, so it's easy
            return Distance(rhs.m_BeginPosition);
        }else{
            vector<float, 3> v = rhs.m_BeginPosition - m_BeginPosition;
            float a = NX::Dot(v, m_vDirection), b = Dot(v, rhs.m_vDirection);
            float V11 = NX::LengthSquare(m_vDirection);
            float V22 = NX::LengthSquare(rhs.m_vDirection);
            float t1 = (-V22 * a + V12 * b) / Delta;
            float t2 = (-V12 * a + V11 * b) / Delta;
            return ::NX::Length(GetPoint(t1) - rhs.GetPoint(t2));
        }
    }

    std::pair<bool, vector<float, 3> >  Line::Intersect(const Plane &plane) const{//直线与平面交点
        return plane.Intersect(*this);
    }

    std::pair<bool, vector<float, 3> >  Line::Intersect(const Line &rhs) const{ //两直线的交点
        Matrix<float, 2, 2> M;
        vector<float, 2>    V;
        M[0][0] = ::NX::LengthSquare(m_vDirection),  M[0][1] = -::NX::Dot(m_vDirection, rhs.m_vDirection);
        M[1][0] = -M[0][1],                          M[1][1] = LengthSquare(rhs.m_vDirection);
        V[0] = ::NX::Dot(m_vDirection, rhs.m_BeginPosition - m_BeginPosition);
        V[1] = ::NX::Dot(rhs.m_vDirection, m_BeginPosition - rhs.m_BeginPosition);
        const std::pair<bool, vector<float, 2> > &SS = SolveEquation(M, V);
        if(SS.first){
            const float t1 = SS.second[0], t2 = SS.second[1];
            if(NX::Length(GetPoint(t1) - rhs.GetPoint(t2)) <= Epsilon<float>::m_Epsilon){
                return std::make_pair(true, GetPoint(t1));
            }
        }
        return std::make_pair(false, vector<float, 3>());
    }
}
