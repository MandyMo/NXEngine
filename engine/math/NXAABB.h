/*
 *  File:    NXAABB.h
 *  author:  张雄
 *  date:    2016_06_05
 *  purpose: define AABB
 */

#ifndef __ZX_NXENGINE_AABB_H__
#define __ZX_NXENGINE_AABB_H__

#include "NXVector.h"

namespace NX {
    class AABB{
    public:
        inline explicit AABB(const NX::vector<float, 3> &MinPoint, const NX::vector<float, 3> &MaxPoint):m_vMinPoint(MinPoint), m_vMaxPoint(MaxPoint){
            /*empty*/
        }
        
        inline explicit AABB(){
            /*empty*/
        }
        
        inline AABB(const AABB &rhs):m_vMinPoint(rhs.m_vMinPoint), m_vMaxPoint(rhs.m_vMaxPoint){
            /*empty*/
        }
        
        AABB(const std::vector<NX::vector<float, 3> > &PointSet);
        
    public:
        inline NX::vector<float, 3>& GetMinPoint(){
            return m_vMinPoint;
        }
        
        inline NX::vector<float, 3>& GetMaxPoint(){
            return m_vMaxPoint;
        }
        
        NX::vector<float, 3>  GetMinPoint() const{
            return m_vMinPoint;
        }
        
        NX::vector<float, 3>  GetMaxPoint() const{
            return m_vMaxPoint;
        }
        
        NX::vector<float, 3>   GetCenter() const{
            return (m_vMinPoint + m_vMaxPoint) * 0.5f;
        }
        
        AABB& FromPointSet(const std::vector<NX::vector<float, 3> > &PointSet);
        
    public:
        inline bool InAABB(const NX::vector<float, 3> &point){
            return  point.x >= m_vMinPoint.x && point.x <= m_vMaxPoint.x &&
                    point.y >= m_vMinPoint.y && point.y <= m_vMaxPoint.y &&
                    point.z >= m_vMinPoint.z && point.z <= m_vMaxPoint.z;
        }
        
        inline AABB& AddPoint(const NX::vector<float, 3> &point){
            m_vMinPoint.x = NX::NXMin(m_vMinPoint.x, point.x);
            m_vMinPoint.y = NX::NXMin(m_vMinPoint.y, point.y);
            m_vMinPoint.z = NX::NXMin(m_vMinPoint.z, point.z);
            
            m_vMaxPoint.x = NX::NXMax(m_vMaxPoint.x, point.x);
            m_vMaxPoint.y = NX::NXMax(m_vMaxPoint.y, point.y);
            m_vMaxPoint.z = NX::NXMax(m_vMaxPoint.z, point.z);
            
            return *this;
        }
        
    public:
        NX::vector<float, 3>    m_vMinPoint;
        NX::vector<float, 3>    m_vMaxPoint;
    };
}

#endif // !__ZX_NXENGINE_AABB_H__