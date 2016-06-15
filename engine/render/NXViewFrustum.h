/*
 *  File:    NXViewFrustum.h
 *  author:  张雄
 *  date:    2016_06_01
 *  purpose: 定义ViewFrustum及相应的一些操作函数
 */

#ifndef __ZX_NXENGINE_VIEWFRUSTUM_H__
#define __ZX_NXENGINE_VIEWFRUSTUM_H__

#include "../math/NXPlane.h"

namespace NX {
    class ViewFrustum{
    public:
        ViewFrustum();
        ViewFrustum(const NX::Plane &Front, const NX::Plane &Back, const NX::Plane &left, const NX::Plane &Right, const NX::Plane &Top, const NX::Plane &Bottom);
        virtual ~ViewFrustum();
        
    public:
        inline NX::Plane GetFrontPlane()  const;
        inline NX::Plane GetBackPlane()   const;
        inline NX::Plane GetLeftPlane()   const;
        inline NX::Plane GetRightPlane()  const;
        inline NX::Plane GetTopPlane()    const;
        inline NX::Plane GetBottomPlane() const;
        
    private:
        NX::Plane     m_FrontPlane;
        NX::Plane     m_BackPlane;
        NX::Plane     m_LeftPlane;
        NX::Plane     m_RightPlane;
        NX::Plane     m_TopPlane;
        NX::Plane     m_BottomPlane;
    };
    
    inline NX::Plane ViewFrustum::GetFrontPlane()  const{
        return m_FrontPlane;
    }
    
    inline NX::Plane ViewFrustum::GetBackPlane()   const{
        return m_BackPlane;
    }
    
    inline NX::Plane ViewFrustum::GetLeftPlane()   const{
        return m_LeftPlane;
    }
    
    inline NX::Plane ViewFrustum::GetRightPlane()  const{
        return m_RightPlane;
    }
    
    inline NX::Plane ViewFrustum::GetTopPlane()    const{
        return m_TopPlane;
    }
    
    inline NX::Plane ViewFrustum::GetBottomPlane() const{
        return m_BottomPlane;
    }
}


#endif  //!__ZX_NXENGINE_VIEWFRUSTUM_H__