/*
 *  File:    NXComplex.h
 *  author:  张雄
 *  date:    2016_06_04
 *  purpose: 复数
 */

#ifndef __ZX_NXENGINE_COMPLEX_H__
#define __ZX_NXENGINE_COMPLEX_H__

#include "NXMath.h"

namespace NX{
    class Complex{
    public:
        explicit Complex(const float fReal, const float fImage){
            m_fReal   = fReal;
            m_fImage  = fImage;
        }
        
        explicit Complex(const float fReal){
            m_fReal  = fReal;
            m_fImage = 0.0f;
        }
        
        Complex(){
            m_fReal = m_fImage = 0.0f;
        }
        
        Complex(const Complex &rhs){
            m_fReal   = rhs.m_fReal;
            m_fImage  = rhs.m_fImage;
        }
        
    public:
        Complex& operator = (const Complex &rhs){
            m_fReal   = rhs.m_fReal;
            m_fImage  = rhs.m_fImage;
            return *this;
        }
        
        Complex& operator += (const Complex &rhs){
            m_fReal   += rhs.m_fReal;
            m_fImage  += rhs.m_fImage;
            return *this;
        }
        
        Complex& operator -= (const Complex &rhs){
            m_fReal   -= rhs.m_fReal;
            m_fImage  -= rhs.m_fImage;
            return *this;
        }
        
        Complex& operator *= (const Complex &rhs){
            float real  = m_fReal * rhs.m_fReal  - m_fImage * rhs.m_fImage;
            float image = m_fReal * rhs.m_fImage + m_fImage * rhs.m_fReal;
            m_fReal  = real;
            m_fImage = image;
            return *this;
        }
        
        Complex& operator /= (const Complex &rhs){
            return *this *= rhs.GetReverse();
        }
        
        Complex& operator += (const float v){
            m_fReal  += v;
            return *this;
        }
        
        Complex& operator -= (const float v){
            m_fReal  -= v;
            return *this;
        }
        Complex& operator /= (const float v){
            NXAssert(!Equalfloat(v, 0.0f));
            m_fReal   /= v;
            m_fImage  /= v;
            return *this;
        }
        
        Complex& operator *= (const float v){
            m_fReal   *= v;
            m_fImage  *= v;
            return *this;
        }
        
    public:
        float Length() const{
            return std::sqrt(LengthSquare());
        }
        
        float LengthSquare() const{
            return m_fReal * m_fReal + m_fImage * m_fImage;
        }
        
        Complex& Conjugate(){
            m_fImage = -m_fImage;
            return *this;
        }
        
        Complex GetConjugate() const{
            return Complex(*this).Conjugate();
        }
        
        Complex& Reverse(){
            float ss = LengthSquare();
            Conjugate();
            m_fImage /= ss;
            m_fReal  /= ss;
            return *this;
        }
        
        Complex GetReverse() const{
            return Complex(*this).Reverse();
        }
        
        Complex& Set(const float real, const float image){
            m_fReal   = real;
            m_fImage  = image;
            return *this;
        }
        
        Complex& SetImage(const float image){
            m_fImage = image;
            return *this;
        }
        
        Complex& SetReal(const float real){
            m_fReal  = real;
            return *this;
        }
        
        float GetReal() const{
            return m_fReal;
        }
        
        float GetImage() const{
            return m_fImage;
        }
        
        bool IsRealNumber() const{
            return NX::NXAbs(m_fImage) < Epsilon<float>::m_Epsilon;
        }
        
        bool IsPureImage() const{
            return NX::NXAbs(m_fReal) < Epsilon<float>::m_Epsilon;
        }
    public:
        friend inline bool operator == (const Complex &lhs, const Complex &rhs);
        friend inline bool operator == (const Complex &lhs, const float v);
        friend inline bool operator == (const float v, const Complex &rhs);
        friend inline bool operator != (const Complex &lhs, const Complex &rhs);
        friend inline bool operator != (const Complex &rhs, const float v);
        friend inline bool operator != (const float v, const Complex &rhs);
        
        friend inline Complex operator + (const Complex &lhs, const Complex &rhs);
        friend inline Complex operator - (const Complex &lhs, const Complex &rhs);
        friend inline Complex operator * (const Complex &lhs, const Complex &rhs);
        friend inline Complex operator / (const Complex &lhs, const Complex &rhs);

    
        friend inline Complex operator + (const Complex &lhs, const float v);
        friend inline Complex operator - (const Complex &lhs, const float v);
        friend inline Complex operator * (const Complex &lhs, const float v);
        friend inline Complex operator / (const Complex &lhs, const float v);
        
        friend inline Complex operator + ( const float v, const Complex &rhs);
        friend inline Complex operator - ( const float v, const Complex &rhs);
        friend inline Complex operator * ( const float v, const Complex &rhs);
        friend inline Complex operator / ( const float v, const Complex &rhs);
    public:
        float   m_fReal;
        float   m_fImage;
    };
    
    inline bool operator == (const Complex &lhs, const Complex &rhs){
        return NX::Equalfloat(lhs.m_fReal, rhs.m_fReal) && NX::Equalfloat(lhs.m_fImage, rhs.m_fImage);
    }
    
    inline bool operator == (const Complex &lhs, const float v){
        return NX::Equalfloat(lhs.m_fReal, v) && NX::Equalfloat(lhs.m_fImage, 0.0f);
    }
    
    inline bool operator == (const float v, const Complex &rhs){
        return NX::Equalfloat(rhs.m_fReal, v) && NX::Equalfloat(rhs.m_fImage, 0.0f);
    }
    
    inline bool operator != (const Complex &lhs, const Complex &rhs){
        return !(lhs == rhs);
    }
    
    inline bool operator != (const Complex &rhs, const float v){
        return !NX::Equalfloat(rhs.m_fReal, v) || !NX::Equalfloat(rhs.m_fImage, 0.0f);
    }
    
    inline bool operator != (const float v, const Complex &rhs){
        return !NX::Equalfloat(rhs.m_fReal, v) || !NX::Equalfloat(rhs.m_fImage, 0.0f);
    }
    
    inline Complex operator + (const Complex &lhs, const Complex &rhs){
        return Complex(lhs) += rhs;
    }
    
    inline Complex operator - (const Complex &lhs, const Complex &rhs){
        return Complex(lhs) -= rhs;
    }
    
    inline Complex operator * (const Complex &lhs, const Complex &rhs){
        return Complex(lhs) *= rhs;
    }
    
    inline Complex operator / (const Complex &lhs, const Complex &rhs){
        return Complex(lhs) /= rhs;
    }
    
    
    inline Complex operator + ( const float v, const Complex &rhs){
        return Complex(rhs) += v;
    }
    
    inline Complex operator - ( const float v, const Complex &rhs){
        return Complex(v - rhs.m_fReal, -rhs.m_fImage);
    }
    
    inline Complex operator * ( const float v, const Complex &rhs){
        return Complex(rhs) *= v;
    }
    
    inline Complex operator / (const float v, const Complex &rhs){
        return v * rhs.GetReverse();
    }
    
    inline Complex operator + (const Complex &lhs, const float v){
        return Complex(lhs) += v;
    }
    
    inline Complex operator - (const Complex &lhs, const float v){
        return Complex(lhs) -= v;
    }
    
    inline Complex operator * (const Complex &lhs, const float v){
        return Complex(lhs) *= v;
    }
    
    inline Complex operator / (const Complex &lhs, const float v){
        return Complex(lhs) /= v;
    }
}
#endif  //__ZX_NXENGINE_COMPLEX_H__
