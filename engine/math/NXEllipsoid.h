/*
 *  File:    NXEllipsoid.h
 *  author:  张雄
 *  date:    2016_06_013
 *  purpose: define ellipsoid
 */

#ifndef __ZX_NXENGINE_ELLIPSOID_H__
#define __ZX_NXENGINE_ELLIPSOID_H__

#include "NXVector.h"

namespace NX{
    tempalte<typename T, int Row, int Col>
    class Matrix;
    
    class Ellipsoid{
    public:
        inline Ellipsoid(){
            /*empty*/
        }
        
        inline Ellipsoid(const float fSemiAxisX, const float fSemiAxisY, const float fSemiAxisZ):m_vCenter(0.0f, 0.0f, 0.0f), m_vSemiAxisX(1.0f, 0.0f, 0.0f),m_vSemiAxisY(0.0f, 1.0f, 0.0f), m_vSemiAxisZ(0.0f, 0.0f, 1.0f), m_fSemiAxisX(fSemiAxisX), m_fSemiAxisY(fSemiAxisX), m_fSemiAxisZ(fSemiAxisZ){
            /*empty*/
        }
        
        inline Ellipsoid(const NX::vector<float, 3> &vCenter, const NX::vector<float, 3> &vSemiAxisX, const NX::vector<float, 3> &vSemiAxisY, const NX::vector<float, 3> &vSemiAxisZ, const float fSemiAxisX, const float fSemiAxisY, const float fSemiAxisZ):m_vCenter(vCenter), m_vSemiAxisX(vSemiAxisX), m_vSemiAxisY(vSemiAxisY), m_vSemiAxisZ(vSemiAxisZ), m_fSemiAxisX(fSemiAxisX), m_fSemiAxisY(fSemiAxisY), m_fSemiAxisZ(fSemiAxisZ){
            /*empty*/
        }
        
        inline Ellipsoid(const float fSemiAxisX, const float fSemiAxisY, const float fSemiAxisZ, const NX::vector<float, 3> &T,    const NX::Matrix<float, 3, 3> &R);
        
        inline Ellipsoid(const float fSemiAxisX, const float fSemiAxisY, const float fSemiAxisZ, const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3>    &T);
        
        inline Ellipsoid(const float fSemiAxisX, const float fSemiAxisY, const float fSemiAxisZ, const NX::Matrix<float, 3, 3> &R);
        
        inline Ellipsoid(const float fSemiAxisX, const float fSemiAxisY, const float fSemiAxisZ, const NX::Matrix<float, 4, 4> &M);
        
    public:
        NX::vector<float, 3>     m_vCenter;
        NX::vector<float, 3>     m_vSemiAxisX;
        NX::vector<float, 3>     m_vSemiAxisY;
        NX::vector<float, 3>     m_vSemiAxisZ;
        float                    m_fSemiAxisX;
        float                    m_fSemiAxisY;
        float                    m_fSemiAxisZ;
    };
};

#endif //!__ZX_NXENGINE_ELLIPSOID_H__