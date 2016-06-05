/*
 *  File:    NXPlane.cpp
 *  author:  张雄
 *  date:    2016_05_13
 *  purpose: define plane
 */

#include "NXPlane.h"
#include "NXLine.h"
#include "NXAlgorithm.h"
#include "NXMath.h"

namespace NX {
    std::pair<bool, Line> Plane::Intersect(const Plane &rhs) const{  //平面交线
        Matrix<float, 2, 2> M;
        vector<float, 2>    V;
        M[0][0] = m_vPlaneNormal[0],     M[0][1] = m_vPlaneNormal[1];
        M[1][0] = rhs.m_vPlaneNormal[0], M[1][1] = rhs.m_vPlaneNormal[1];
        
        {
            V[0] = -m_fDistFromOriginal;
            V[1] = -rhs.m_fDistFromOriginal;
            const std::pair<bool, vector<float, 2> > &SS = SolveEquation(M, V);
            if(SS.first){
                vector<float, 3>  begin(SS.second[0], SS.second[1], 0);
                return std::make_pair<bool, Line>(true, Line(begin, begin + Cross(m_vPlaneNormal, rhs.m_vPlaneNormal)));
            }
        }
        
        {
            V[0] = -m_fDistFromOriginal - m_vPlaneNormal[2];
            V[1] = rhs.m_fDistFromOriginal - rhs.m_vPlaneNormal[2];
            const std::pair<bool, vector<float, 2> > &SS = SolveEquation(M, V);
            if(SS.first){
                vector<float, 3>  begin(SS.second[0], SS.second[1], 1);
                return std::make_pair<bool, Line>(true, Line(begin, begin + Cross(m_vPlaneNormal, rhs.m_vPlaneNormal)));
            }
        }
        return std::make_pair(false, Line());
    }

    float  Plane::Distance(const vector<float, 3> &rhs) const{      //点到平面距离
        return (Dot(m_vPlaneNormal, rhs) + m_fDistFromOriginal) / Length(m_vPlaneNormal);
    }

    std::pair<bool, float3> Plane::Intersect(const Line  &rhs) const{
        float Delta = Dot(rhs.m_vDirection, m_vPlaneNormal);
        if(NXAbs(Delta) < Epsilon<float>::m_Epsilon){
            return std::make_pair(false, float3());
        }
        float t = -(Dot(m_vPlaneNormal, rhs.m_BeginPosition) + m_fDistFromOriginal) / Delta;
        return std::make_pair(true, rhs.GetPoint(t));
    }
}