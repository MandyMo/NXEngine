/*
 *  File:    NXEllipse.h
 *  author:  张雄
 *  date:    2016_06_08
 *  purpose: define ellipse
 */


#ifndef __ZX_NXENGINE_ELLIPSE_H__
#define __ZX_NXENGINE_ELLIPSE_H__

#include "NXVector.h"

namespace NX {
    template<typename T, int Row, int Col>
    class Matrix;
    
    class Ellipse{
    public:
        inline Ellipse(){
                /*empty*/
        }
        
        inline Ellipse(const NX::vector<float, 3> &center, const NX::vector<float, 3> &normal, const NX::vector<float, 3> &vShortAxis,
                       const NX::vector<float, 3> &vLongAxis, const float fLongAxis, const float fShortAxis):
        m_vCenter(center), m_vNormal(normal),m_vLongSemiAxis(vLongAxis), m_vShortSemiAxis(vShortAxis),m_fLongSemiAxis(fLongAxis),m_fShortSemiAxis(fShortAxis){
            /*empty*/
        }
        
        Ellipse(const float fLongAxis, const float fShortAxis, const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3> &T);
        Ellipse(const float fLongAxis, const float fShortAxis, const NX::Matrix<float, 4, 4> &M);
        
    public:
        NX::vector<float, 3> GetCenter() const{
            return m_vCenter;
        }
        
        NX::vector<float, 3> GetNormal() const{
            return m_vNormal;
        }
        
        NX::vector<float, 3> GetLongSemiAxis() const{
            return m_vLongSemiAxis;
        }
        
        NX::vector<float, 3> GetShortSemiAxis() const{
            return m_vShortSemiAxis;
        }
        
        float GetLongSemiAxisLength() const{
            return m_fLongSemiAxis;
        }
        
        float GetShortSemiAxisLength() const{
            return m_fShortSemiAxis;
        }
    
    public:
        bool InEllipse(const NX::vector<float, 3> &point) const;
        bool OnEllipse(const NX::vector<float, 3> &point) const;
        
    public:
        Ellipse& Transform(const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3> &T);
        Ellipse& Transform(const NX::Matrix<float, 3, 3> &R);
        Ellipse& Transform(const NX::Matrix<float, 4, 4> &M);
        
        Ellipse GetTransformed(const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3> &T);
        Ellipse GetTransformed(const NX::Matrix<float, 3, 3> &R);
        Ellipse GetTransformed(const NX::Matrix<float, 4, 4> &M);
        
    public:
        NX::vector<float, 3> m_vCenter;
        NX::vector<float, 3> m_vNormal;
        NX::vector<float, 3> m_vLongSemiAxis;
        NX::vector<float, 3> m_vShortSemiAxis;
        float                m_fLongSemiAxis;
        float                m_fShortSemiAxis;
    };
}


#endif // !__ZX_NXENGINE_ELLIPSE_H__
