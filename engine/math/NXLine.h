/*
 *  File:    NXLine.h
 *  author:  张雄
 *  date:    2016_05_13
 *  purpose: define Line
 */

#ifndef __ZX_NXENGINE_LINE_H__
#define __ZX_NXENGINE_LINE_H__

#include <utility>
#include "NXVector.h"
#include "NXMatrix.h"
#include "NXAlgorithm.h"

namespace NX{
    class Plane;
    
    class Line{
    public:
        inline explicit Line(){/*empty*/}
        Line(const NX::vector<float, 3> &begin, const NX::vector<float, 3> &end):m_BeginPosition(begin), m_vDirection(end - begin){
            /*empty*/
        }

    public:
        Line& Transform(const NX::Matrix<float, 3, 3> &rhs);
        Line& Transform(const NX::Matrix<float, 4, 4> &rhs);
        Line& Transform(const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3>    &T);
        Line& Transform(const NX::vector<float, 3>    &T, const NX::Matrix<float, 3, 3> &R);
        Line& Translate(const NX::vector<float, 3> &T);
        
        inline Line GetTransformed(const NX::Matrix<float, 3, 3> &rhs) const{
            return Line(*this).Transform(rhs);
        }
        
        inline Line GetTransformed(const NX::Matrix<float, 4, 4> &rhs) const{
            return Line(*this).Transform(rhs);
        }

        inline Line GetTransformed(const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3>    &T) const{
            return Line(*this).Transform(R, T);
        }
        
        inline Line GetTransformed(const NX::vector<float, 3>    &T, const NX::Matrix<float, 3, 3> &R) const{
            return Line(*this).Transform(T, R);
        }
        
        inline Line GetTranslated(const NX::vector<float, 3> &T) const{
            return Line(*this).Translate(T);
        }
        
    public:
        inline vector<float, 3> GetBeginPosition() const{
            return m_BeginPosition;
        }
        
        inline vector<float, 3> GetDirection() const{
            return m_vDirection;
        }
        
        inline vector<float, 3> GetPoint(const float t) const{
            return m_BeginPosition + t * m_vDirection;
        }

        float Distance(const Line &rhs) const;//两直线距离
        
        template<typename T>
        inline float Distance(const vector<T, 3> &Point) const{
            const vector<T, 3> v = Point - m_BeginPosition;
            float t = NX::Dot(m_vDirection, v) / Dot(m_vDirection, m_vDirection);
            return Length(t * m_vDirection - v);
        }

        inline bool OnLine(const NX::vector<float, 3> &point){
            return NX::EqualZero(Distance(point));
        }
        
        std::pair<bool, NX::vector<float, 3> >  Intersect(const Line &rhs) const;   //两直线的交点
        std::pair<bool, NX::vector<float, 3> >  Intersect(const Plane &plane) const;//直线与平面交点
        
    public:
        NX::vector<float, 3> m_BeginPosition;
        NX::vector<float, 3> m_vDirection;
    };
}

#endif //!__ZX_NXENGINE_LINE_H__