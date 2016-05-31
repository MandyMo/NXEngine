/*
 *  File:    NXViewFrustum.h
 *  author:  张雄
 *  date:    2016_06_01
 *  purpose: 定义ViewFrustum及相应的一些操作函数
 */

#ifndef __ZX_NXENGINE_VIEWFRUSTUM_H__
#define __ZX_NXENGINE_VIEWFRUSTUM_H__

#include "../math/NXPrimitive.h"

namespace NX {
    class ViewFrustum{
    public:
        ViewFrustum();
        ~ViewFrustum();
    private:
        Plane     m_FrontPlane;
        Plane     m_BackPlane;
        Plane     m_LeftPlane;
        Plane     m_RightPlane;
        Plane     m_TopPlane;
        Plane     m_BottomPlane;
    };
}


#endif  //__ZX_NXENGINE_VIEWFRUSTUM_H__