/*
 *  File:    NXAABB.cpp
 *  author:  张雄
 *  date:    2016_06_05
 *  purpose: define AABB
 */


#include "NXAABB.h"

namespace NX {
    AABB::AABB(const std::vector<NX::vector<float, 3> > &PointSet){
        FromPointSet(PointSet);
    }
    
    AABB& AABB::FromPointSet(const std::vector<NX::vector<float, 3> > &PointSet){
        const int len = (int)PointSet.size();
        NXAssert(len >= 0);
        if(len == 0){
            return *this;
        }
        m_vMinPoint = m_vMaxPoint = PointSet[0];
        for(int i = 1; i < len; ++i){
            m_vMinPoint.x = NX::NXMin(m_vMinPoint.x, PointSet[i].x);
            m_vMinPoint.y = NX::NXMin(m_vMinPoint.y, PointSet[i].y);
            m_vMinPoint.z = NX::NXMin(m_vMinPoint.z, PointSet[i].z);
            
            m_vMaxPoint.x = NX::NXMax(m_vMaxPoint.x, PointSet[i].x);
            m_vMaxPoint.y = NX::NXMax(m_vMaxPoint.y, PointSet[i].y);
            m_vMaxPoint.z = NX::NXMax(m_vMaxPoint.z, PointSet[i].z);
        }
        return *this;
    }
}