/*
 *  File:    NXEllipse.h
 *  author:  张雄
 *  date:    2016_06_08
 *  purpose: define ellipse
 */


#ifndef __ZX_NXENGINE_ELLIPSE_H__
#define __ZX_NXENGINE_ELLIPSE_H__

#include "NXVector.h"
#include "NXAlgorithm.h"

namespace NX {
    template<typename T, int Row, int Col>
    class Matrix;
    
    class Ellipse{
    public:
        inline Ellipse(){
            /*empty*/
        }
        
        /**
         *  becareful that m_vNormal, m_vShortAxis, m_vLongAxis must be unit vector(length is 1)
         */
        inline Ellipse(const NX::vector<float, 3> &center, const NX::vector<float, 3> &normal, const NX::vector<float, 3> &vShortAxis,
                       const NX::vector<float, 3> &vLongAxis, const float fLongAxis, const float fShortAxis):
        m_vCenter(center), m_vNormal(normal),m_vLongAxis(vLongAxis), m_vShortAxis(vShortAxis),m_fLongAxis(fLongAxis),m_fShortAxis(fShortAxis){
            NXAssert(NX::Equalfloat(NX::Length(m_vNormal),    kf1));
            NXAssert(NX::Equalfloat(NX::Length(m_vShortAxis), kf1));
            NXAssert(NX::Equalfloat(NX::Length(m_vLongAxis),  kf1));
            /*empty*/
        }
        
        Ellipse(const float fLongAxis, const float fShortAxis, const NX::vector<float, 3> &T,    const NX::Matrix<float, 3, 3> &R);
        Ellipse(const float fLongAxis, const float fShortAxis, const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3>    &T);
        Ellipse(const float fLongAxis, const float fShortAxis, const NX::Matrix<float, 3, 3> &M);
        Ellipse(const float fLongAxis, const float fShortAxis, const NX::Matrix<float, 4, 4> &M);
        Ellipse(const float fLongAxis, const float fShortAxis);
        
    public:
        NX::vector<float, 3> GetCenter() const{
            return m_vCenter;
        }
        
        NX::vector<float, 3> GetNormal() const{
            return m_vNormal;
        }
        
        NX::vector<float, 3> GetLongAxis() const{
            return m_vLongAxis;
        }
        
        NX::vector<float, 3> GetShortAxis() const{
            return m_vShortAxis;
        }
        
        float GetLongAxisLength() const{
            return m_fLongAxis;
        }
        
        float GetShortAxisLength() const{
            return m_fShortAxis;
        }
    
    public:
        bool InEllipse(const NX::vector<float, 3> &point) const;
        bool OnEllipse(const NX::vector<float, 3> &point) const;
        
    public:
        Ellipse& Transform(const NX::vector<float, 3>    &T, const NX::Matrix<float, 3, 3> &R);
        Ellipse& Transform(const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3> &T);
        Ellipse& Transform(const NX::Matrix<float, 3, 3> &R);
        Ellipse& Transform(const NX::Matrix<float, 4, 4> &M);
        Ellipse& Translate(const NX::vector<float, 3> &T);
        
        Ellipse GetTransformed(const NX::vector<float, 3>    &T, const NX::Matrix<float, 3, 3> &R) const;
        Ellipse GetTransformed(const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3> &T) const;
        Ellipse GetTransformed(const NX::Matrix<float, 3, 3> &R) const;
        Ellipse GetTransformed(const NX::Matrix<float, 4, 4> &M) const;
        Ellipse GetTranslated(const NX::vector<float, 3> &T) const;
        
    public:
        NX::vector<float, 3> m_vCenter;
        NX::vector<float, 3> m_vNormal;
        NX::vector<float, 3> m_vLongAxis;
        NX::vector<float, 3> m_vShortAxis;
        float                m_fLongAxis;
        float                m_fShortAxis;
    };
}


#endif // !__ZX_NXENGINE_ELLIPSE_H__
