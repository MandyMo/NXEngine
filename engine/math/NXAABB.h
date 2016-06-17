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
        inline explicit AABB(const NX::vector<float, 3> &MinPoint, const NX::vector<float, 3> &MaxPoint){
            m_vMinPoint.x = NX::NXMin(MinPoint.x, MaxPoint.x);
            m_vMinPoint.y = NX::NXMin(MinPoint.y, MaxPoint.y);
            m_vMinPoint.z = NX::NXMin(MinPoint.z, MaxPoint.z);
            
            m_vMaxPoint.x = NX::NXMax(MinPoint.x, MaxPoint.x);
            m_vMaxPoint.y = NX::NXMax(MinPoint.y, MaxPoint.y);
            m_vMaxPoint.z = NX::NXMax(MinPoint.z, MaxPoint.z);
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
        
        inline NX::vector<float, 3>  GetMinPoint() const{
            return m_vMinPoint;
        }
        
        inline NX::vector<float, 3>  GetMaxPoint() const{
            return m_vMaxPoint;
        }
        
        inline NX::vector<float, 3>   GetCenter() const{
            return (m_vMinPoint + m_vMaxPoint) * 0.5f;
        }
        
        inline NX::vector<float, 3>   GetSize() const{
            return m_vMaxPoint - m_vMaxPoint;
        }
        
        inline float GetXSize() const{
            return m_vMaxPoint.x - m_vMinPoint.x;
        }
        
        inline float GetYSize() const{
            return m_vMaxPoint.y - m_vMinPoint.y;
        }
        
        inline float GetZSize() const{
            return m_vMaxPoint.z - m_vMinPoint.z;
        }
        
        AABB& FromPointSet(const std::vector<NX::vector<float, 3> > &PointSet);
        
    public:
        /**
         *  测试时建议使用一定误差，否则，处于边缘的点会被判定为不在AABB内
         */
        inline bool InAABB(const NX::vector<float, 3> &point, const float Delta = NX::Epsilon<float>::m_Epsilon) const{
            return  point.x >= m_vMinPoint.x - Delta && point.x <= m_vMaxPoint.x + Delta&&
                    point.y >= m_vMinPoint.y - Delta && point.y <= m_vMaxPoint.y + Delta&&
                    point.z >= m_vMinPoint.z - Delta && point.z <= m_vMaxPoint.z + Delta;
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