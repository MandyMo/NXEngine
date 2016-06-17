/*
 *  File:    NXViewFrustum.cpp
 *  author:  张雄
 *  date:    2016_06_02
 *  purpose: 定义ViewFrustum及相应的一些操作函数
 */

#include "NXViewFrustum.h"
#include "../math/NXSphere.h"
#include "../math/NXEllipsoid.h"


NX::ViewFrustum::ViewFrustum(){
    /*empty*/
}

NX::ViewFrustum::ViewFrustum(const Plane &Front, const Plane &Back, const Plane &left, const Plane &Right, const Plane &Top, const Plane &Bottom):
m_FrontPlane(Front), m_BackPlane(Back), m_LeftPlane(left), m_RightPlane(Right), m_TopPlane(Top), m_BottomPlane(Bottom){
    /*empty*/
}

NX::ViewFrustum::~ViewFrustum(){
    /*empty*/
}

bool NX::ViewFrustum::Visible(const NX::Sphere &sphere, const NX::FRUSTUM_VISIBLE_TEST_BIT_MASK mask){
    const NX::vector<float, 3> center = sphere.GetCenter();
    const float r = sphere.GetRadius();
    if(mask & NX::VF_VT_LEFT){
        if(NX::Dot(GetLeftPlane().GetNormal(), center)   + GetLeftPlane().GetDistFromOriginal()   < -r){
            return false;
        }
    }
    if(mask & NX::VF_VT_RIGHT){
        if(NX::Dot(GetRightPlane().GetNormal(), center)  + GetRightPlane().GetDistFromOriginal()  < -r){
            return false;
        }
    }
    if(mask & NX::VF_VT_TOP){
        if(NX::Dot(GetTopPlane().GetNormal(), center)    + GetTopPlane().GetDistFromOriginal()    < -r){
            return false;
        }
    }
    if(mask & NX::VF_VT_BOTTOM){
        if(NX::Dot(GetBottomPlane().GetNormal(), center) + GetBottomPlane().GetDistFromOriginal() < -r){
            return false;
        }
    }
    if(mask & NX::VF_VT_FRONT){
        if(NX::Dot(GetFrontPlane().GetNormal(), center)  + GetFrontPlane().GetDistFromOriginal()  < -r){
            return false;
        }
    }
    if(mask & NX::VF_VT_BACK){
        if(NX::Dot(GetBackPlane().GetNormal(), center)   + GetBackPlane().GetDistFromOriginal()   < -r){
            return false;
        }
    }
    return true;
}

bool NX::ViewFrustum::Visible(const NX::Ellipsoid &ellipsoid,        const NX::FRUSTUM_VISIBLE_TEST_BIT_MASK mask){
    NXAssert(0);
    return false;
}
