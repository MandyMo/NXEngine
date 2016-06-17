/*
 *  File:    NXCylinder.h
 *  author:  张雄
 *  date:    2016_06_14
 *  purpose: define Cylinder
 */

#ifndef __ZX_NXENGINE_CYLINDER_H__
#define __ZX_NXENGINE_CYLINDER_H__

#include "NXVector.h"

namespace NX {
    template<typename T, int Row, int Col>
    class Matrix;
    
    class Cylinder{
    public:
        inline Cylinder(){
            /*empty*/
        }
        
        Cylinder(const float fLongAxis, const float fShortAxis, const float fHeight);
        
        Cylinder(const float fLongAxis, const float fShortAxis, const float fHeight, const NX::Matrix<float, 3, 3> &R);
        
        Cylinder(const float fLongAxis, const float fShortAxis, const float fHeight, const NX::Matrix<float, 4, 4> &M);
        
        Cylinder(const float fLongAxis, const float fShortAxis, const float fHeight, const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3> &T);
        
        Cylinder(const float fLongAxis, const float fShortAxis, const float fHeight, const NX::vector<float, 3> &T, const NX::Matrix<float, 3, 3> &R);
        
        inline Cylinder(const NX::vector<float, 3> &vCenter, const NX::vector<float, 3> &vNormal, const NX::vector<float, 3> &vLongAxis, const NX::vector<float, 3> &vShortAxis, const float fLongAxis, const float fShortAxis, const float fHeight):m_vCenter(vCenter), m_vNormal(vNormal), m_vLongAxis(vLongAxis), m_vShortAxis(vShortAxis), m_fLongAxis(fLongAxis), m_fShortAxis(fShortAxis), m_fHeight(fHeight){
            /*empty*/
        }
        
    public:
        Cylinder& Transform(const NX::Matrix<float, 3, 3> &R);
        Cylinder& Transform(const NX::Matrix<float, 4, 4> &M);
        Cylinder& Transform(const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3>    &T);
        Cylinder& Transform(const NX::vector<float, 3>    &T, const NX::Matrix<float, 3, 3> &R);
        Cylinder& Translate(const NX::vector<float, 3> &T);
        
        Cylinder GetTransformed(const NX::Matrix<float, 3, 3> &R) const;
        Cylinder GetTransformed(const NX::Matrix<float, 4, 4> &M) const;
        Cylinder GetTransformed(const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3>    &T) const;
        Cylinder GetTransformed(const NX::vector<float, 3>    &T, const NX::Matrix<float, 3, 3> &R) const;
        Cylinder GetTranslated(const NX::vector<float, 3> &T) const;
        
    public:
        bool InCylinder(const NX::vector<float, 3> &point) const;
        bool OnCylinder(const NX::vector<float, 3> &point) const;
        
    public:
        NX::vector<float, 3>  GetCenter() const{
            return m_vCenter;
        }
        
        NX::vector<float, 3>  GetNormal() const{
            return m_vNormal;
        }
        
        NX::vector<float, 3>  GetLongAxis() const{
            return m_vLongAxis;
        }
        
        NX::vector<float, 3>  GetShortAxis() const{
            return m_vShortAxis;
        }
        
        float GetLongAxisLength() const{
            return m_fLongAxis;
        }
        
        float GetShortAxisLength() const{
            return m_fShortAxis;
        }
        
        float GetHeight() const{
            return m_fHeight;
        }

    public:
        NX::vector<float, 3>           m_vCenter;
        NX::vector<float, 3>           m_vNormal;
        NX::vector<float, 3>           m_vLongAxis;
        NX::vector<float, 3>           m_vShortAxis;
        float                          m_fLongAxis;
        float                          m_fShortAxis;
        float                          m_fHeight;
    };
}


#endif // !__ZX_NXENGINE_CYLINDER_H__