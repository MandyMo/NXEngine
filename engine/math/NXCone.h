/*
 *  File:    NXCone.h
 *  author:  张雄
 *  date:    2016_06_14
 *  purpose: define cone
 */

#ifndef __ZX_NXENGINE_CONE_H__
#define __ZX_NXENGINE_CONE_H__

#include "NXVector.h"

namespace NX {
    template<typename T, int Row, int Col>
    class Matrix;
    
    
    class Cone{
    public:
        inline Cone(){
            /*empty*/
        }
        
        Cone(const float fLongAxis, const float fShortAxis, const float fHeight);
        
        Cone(const float fLongAxis, const float fShortAxis, const float fHeight, const NX::Matrix<float, 3, 3> &R);
        
        Cone(const float fLongAxis, const float fShortAxis, const float fHeight, const NX::Matrix<float, 4, 4> &M);
        
        Cone(const float fLongAxis, const float fShortAxis, const float fHeight, const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3> &T);
        
        Cone(const float fLongAxis, const float fShortAxis, const float fHeight, const NX::vector<float, 3> &T, const NX::Matrix<float, 3, 3> &R);
        
        inline Cone(const NX::vector<float, 3> &vCenter, const NX::vector<float, 3> &vNormal, const NX::vector<float, 3> &vLongAxis, const NX::vector<float, 3> &vShortAxis, const float fLongAxis, const float fShortAxis, const float fHeight):m_vCenter(vCenter), m_vNormal(vNormal), m_vLongAxis(vLongAxis), m_vShortAxis(vShortAxis), m_fLongAxis(fLongAxis), m_fShortAxis(fShortAxis), m_fHeight(fHeight){
            /*empty*/
        }
        
    public:
        Cone& Transform(const NX::Matrix<float, 3, 3> &R);
        Cone& Transform(const NX::Matrix<float, 4, 4> &M);
        Cone& Transform(const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3>    &T);
        Cone& Transform(const NX::vector<float, 3>    &T, const NX::Matrix<float, 3, 3> &R);
        Cone& Translate(const NX::vector<float, 3> &T);
        
        Cone GetTransformed(const NX::Matrix<float, 3, 3> &R) const;
        Cone GetTransformed(const NX::Matrix<float, 4, 4> &M) const;
        Cone GetTransformed(const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3>    &T) const;
        Cone GetTransformed(const NX::vector<float, 3>    &T, const NX::Matrix<float, 3, 3> &R) const;
        Cone GetTranslated(const NX::vector<float, 3> &T) const;
    
    public:
        bool InCone(const NX::vector<float, 3> &point) const;
        bool OnCone(const NX::vector<float, 3> &point) const;
        
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


#endif //!__ZX_NXENGINE_CONE_H__