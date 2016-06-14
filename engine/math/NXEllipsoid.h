/*
 *  File:    NXEllipsoid.h
 *  author:  张雄
 *  date:    2016_06_013
 *  purpose: define ellipsoid
 */

#ifndef __ZX_NXENGINE_ELLIPSOID_H__
#define __ZX_NXENGINE_ELLIPSOID_H__

#include "NXVector.h"

namespace NX{
    template<typename T, int Row, int Col>
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
        
        Ellipsoid(const float fSemiAxisX, const float fSemiAxisY, const float fSemiAxisZ, const NX::vector<float, 3> &T,    const NX::Matrix<float, 3, 3> &R);
        
        Ellipsoid(const float fSemiAxisX, const float fSemiAxisY, const float fSemiAxisZ, const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3>    &T);
        
        Ellipsoid(const float fSemiAxisX, const float fSemiAxisY, const float fSemiAxisZ, const NX::Matrix<float, 3, 3> &R);
        
        Ellipsoid(const float fSemiAxisX, const float fSemiAxisY, const float fSemiAxisZ, const NX::Matrix<float, 4, 4> &M);
        
    public:
        Ellipsoid& Transform(const NX::Matrix<float, 3, 3> &R);
        Ellipsoid& Transform(const NX::Matrix<float, 4, 4> &M);
        Ellipsoid& Transform(const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3>    &T);
        Ellipsoid& Transform(const NX::vector<float, 3>    &T, const NX::Matrix<float, 3, 3> &R);
        Ellipsoid& Translate(const NX::vector<float, 3> &T);
        
        Ellipsoid GetTransformed(const NX::Matrix<float, 3, 3> &R) const;
        Ellipsoid GetTransformed(const NX::Matrix<float, 4, 4> &M) const;
        Ellipsoid GetTransformed(const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3>    &T) const;
        Ellipsoid GetTransformed(const NX::vector<float, 3>    &T, const NX::Matrix<float, 3, 3> &R) const;
        Ellipsoid GetTranslated(const NX::vector<float, 3> &T) const;
    public:
        inline NX::vector<float, 3> GetCenter() const{
            return m_vCenter;
        }
        
        inline NX::vector<float, 3> GetAxisX() const{
            return m_vSemiAxisX;
        }
        
        inline NX::vector<float, 3> GetAxisY() const{
            return m_vSemiAxisY;
        }
        
        inline NX::vector<float, 3> GetAxisZ() const{
            return m_vSemiAxisZ;
        }
        
        inline float GetAxisXLength() const{
            return m_fSemiAxisX;
        }
        
        inline float GetAxisYLength() const{
            return m_fSemiAxisY;
        }
        
        inline float GetAxisZLength() const{
            return m_fSemiAxisZ;
        }
        
    public:
        bool InEllipsoid(const NX::vector<float, 3> &point) const;
        bool OnEllipsoid(const NX::vector<float, 3> &point) const;
        
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