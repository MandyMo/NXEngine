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
        Line(const vector<float, 3> &begin, const vector<float, 3> &end):m_BeginPosition(begin), m_vDirection(end - begin){
            /*empty*/
        }

    public:
        template<typename T>
        inline Line& Transform(const Matrix<T, 3, 3> &rhs){
            {
                {//transform begin point
                    const Matrix<T, 3, 1> &RefObj = rhs * m_BeginPosition;
                    m_BeginPosition.Set(RefObj.m_Element[0][0], RefObj.m_Element[1][0], RefObj.m_Element[2][0]);
                }
                
                {//transform direction vector
                    const Matrix<T, 3, 1> &RefObj = rhs * m_vDirection;
                    m_vDirection.Set(RefObj.m_Element[0][0], RefObj.m_Element[1][0], RefObj.m_Element[2][0]);
                }
                
                return *this;
            }
        }
        
        template<typename T>
        inline Line& Transform(const Matrix<T, 4, 4> &rhs){
            {//transfrom begin point
                const Matrix<T, 4, 1> &RefObj = rhs * NX::float4(m_BeginPosition.x, m_BeginPosition.y, m_BeginPosition.z, T(1));
                m_BeginPosition.Set(RefObj[0][0] / RefObj[3][0], RefObj[1][0] / RefObj[3][0], RefObj[2][0] / RefObj[3][0]);
            }
            
            {//transform direction vector
                const Matrix<T, 4, 1> &RefObj = rhs * NX::float4(m_vDirection.x, m_vDirection.y, m_vDirection.z, T(0));
                m_vDirection.Set(RefObj[0][0], RefObj[1][0], RefObj[2][0] );
            }
            return *this;
        }

        template<typename T>
        inline Line GetTransformed(const Matrix<T, 3, 3> &rhs){
            return Line(*this).Transform(rhs);
        }
        
        template<typename T>
        inline Line GetTransformed(const Matrix<T, 4, 4> &rhs){
            return Line(*this).Transform(rhs);
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
        
        std::pair<bool, vector<float, 3> >  Intersect(const Line &rhs) const;   //两直线的交点
        std::pair<bool, vector<float, 3> >  Intersect(const Plane &plane) const;//直线与平面交点
        
    public:
        vector<float, 3> m_BeginPosition;
        vector<float, 3> m_vDirection;
    };
}

#endif //!__ZX_NXENGINE_LINE_H__