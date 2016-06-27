/*
 *  File:    NXOOBB.h
 *  author:  张雄
 *  date:    2016_06_24
 *  purpose: define OOBB
 */

#ifndef __ZX_NXENGINE_OOBB_H__
#define __ZX_NXENGINE_OOBB_H__

#include "NXVector.h"

namespace NX {
    enum OOBB_EXTEND_AXIS_MASK{
        OOBB_EXTEND_AXIS_X    = 1 << 0,
        OOBB_EXTEND_AXIS_Y    = 1 << 1,
        OOBB_EXTEND_AXIS_Z    = 1 << 2,
        OOBB_EXTEND_AXIS_ALL  = OOBB_EXTEND_AXIS_X | OOBB_EXTEND_AXIS_Y | OOBB_EXTEND_AXIS_Z,
    };
    
    class OOBB{
    public:
        
    public:
        OOBB& Transform(const NX::vector<float, 3>    &T, const NX::Matrix<float, 3, 3> &R);
        OOBB& Transform(const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3> &T);
        OOBB& Transform(const NX::Matrix<float, 3, 3> &R);
        OOBB& Transform(const NX::Matrix<float, 4, 4> &M);
        OOBB& Translate(const NX::vector<float, 3> &T);
        
        inline OOBB GetTransformed(const NX::vector<float, 3>    &T, const NX::Matrix<float, 3, 3> &R) const;
        inline OOBB GetTransformed(const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3> &T) const;
        inline OOBB GetTransformed(const NX::Matrix<float, 3, 3> &R) const;
        inline OOBB GetTransformed(const NX::Matrix<float, 4, 4> &M) const;
        inline OOBB GetTranslated (const NX::vector<float, 3> &T) const;
    
    public:
        inline NX::vector<float, 3>   GetAixsX() const;
        inline NX::vector<float, 3>   GetAxisY() const;
        inline NX::vector<float, 3>   GetAxisZ() const;
        inline NX::vector<float, 3>   GetLeftBottomPoint() const;
        inline NX::vector<float, 3>   GetRightTopPoint() const;
        inline NX::vector<float, 3>   GetCornerPoint(const unsigned int mask) const;
        inline float   GetAxisXLength() const;
        inline float   GetAxisYLenght() const;
        inline float   GetAxisZLength() const;
        
    public:
        NX::vector<float, 3>                    m_vAxisX;
        NX::vector<float, 3>                    m_vAxisY;
        NX::vector<float, 3>                    m_vAxisZ;
        NX::vector<float, 3>                    m_ptLeftCornerPoint;
        float                                   m_fAxisXLength;
        float                                   m_fAxisYLength;
        float                                   m_fAxisZLength;
    };
    
    inline OOBB OOBB::GetTransformed(const NX::vector<float, 3>    &T, const NX::Matrix<float, 3, 3> &R) const{
        return OOBB(*this).Transform(T, R);
    }
    
    inline OOBB OOBB::GetTransformed(const NX::Matrix<float, 3, 3> &R, const NX::vector<float, 3> &T) const{
        return OOBB(*this).Transform(R, T);
    }
    
    inline OOBB OOBB::GetTransformed(const NX::Matrix<float, 3, 3> &R) const{
        return OOBB(*this).Transform(R);
    }
    
    inline OOBB OOBB::GetTransformed(const NX::Matrix<float, 4, 4> &M) const{
        return OOBB(*this).Transform(M);
    }
    
    inline OOBB OOBB::GetTranslated (const NX::vector<float, 3> &T) const{
        return OOBB(*this).Translate(T);
    }
    
    inline NX::vector<float, 3>   OOBB::GetAixsX() const{
        return m_vAxisX;
    }
    
    inline NX::vector<float, 3>   OOBB::GetAxisY() const{
        return m_vAxisY;
    }
    
    inline NX::vector<float, 3>   OOBB::GetAxisZ() const{
        return m_vAxisZ;
    }
    
    inline NX::vector<float, 3>   OOBB::GetLeftBottomPoint() const{
        return m_ptLeftCornerPoint;
    }
    
    inline NX::vector<float, 3>   OOBB::GetRightTopPoint() const{
        return m_ptLeftCornerPoint + m_vAxisX * m_fAxisXLength + m_vAxisY * m_fAxisYLength + m_vAxisZ * m_fAxisZLength;
    }
    
    inline NX::vector<float, 3>   OOBB::GetCornerPoint(const unsigned int mask) const{
        NX::vector<float, 3> result = m_ptLeftCornerPoint;
        if(mask & NX::OOBB_EXTEND_AXIS_X){
            result += m_fAxisXLength * m_vAxisX;
        }
        if(mask & NX::OOBB_EXTEND_AXIS_Y){
            result += m_fAxisYLength * m_vAxisY;
        }
        if(mask & NX::OOBB_EXTEND_AXIS_Z){
            result += m_fAxisZLength * m_vAxisZ;
        }
        return result;
    }
    
    inline float   OOBB::GetAxisXLength() const{
        return m_fAxisXLength;
    }
    
    inline float   OOBB::GetAxisYLenght() const{
        return m_fAxisYLength;
    }
    
    inline float   OOBB::GetAxisZLength() const{
        return m_fAxisZLength;
    }
}

#endif