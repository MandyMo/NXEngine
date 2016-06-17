/*
 *  File:    NXViewFrustum.cpp
 *  author:  张雄
 *  date:    2016_06_02
 *  purpose: 定义ViewFrustum及相应的一些操作函数
 */

#include "NXViewFrustum.h"

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