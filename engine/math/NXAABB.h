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
        explicit AABB(const NX::vector<float, 3> &MinPoint, const NX::vector<float, 3> &MaxPoint):m_vMinPoint(MinPoint), m_vMaxPoint(MaxPoint){
            /*empty*/
        }
        
        explicit AABB(){
            /*empty*/
        }
        
        AABB(const AABB &rhs):m_vMinPoint(rhs.m_vMinPoint), m_vMaxPoint(rhs.m_vMaxPoint){
            /*empty*/
        }
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
        
    public:
        NX::vector<float, 3>    m_vMinPoint;
        NX::vector<float, 3>    m_vMaxPoint;
    };
}

#endif // !__ZX_NXENGINE_AABB_H__