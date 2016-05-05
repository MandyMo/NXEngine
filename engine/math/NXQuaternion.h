/*
 *  File:    NXQuaternion.h
 *  author:  张雄
 *  date:    2016_05_05
 *  purpose: 四元数操作函数
 */

#ifndef __ZX_NXENGINE_QUATERNION_H__
#define __ZX_NXENGINE_QUATERNION_H__
#include <cstdlib>
#include <cstring>
#include "NXQuaternion.h"
#include "../math/NXVector.h"
#include "../math/NXMatrix.h"

namespace NX {
    template<typename T, int iScale> class vector;
    template<typename T, int iRow, int iCol> class Matrix;
    
    class Quaternion{
    public:
        friend inline Quaternion operator * (const Quaternion &lhs, const Quaternion &rhs);
    public:
        inline Quaternion();
        inline Quaternion(const float w,  const float x, const float y, const float z);
        inline Quaternion(const float *v, int len = 4);
        inline Quaternion(const float radian, const vector<float, 3> &Axis);
        inline Quaternion(const vector<float, 4> &rhs);
        inline Quaternion(const Quaternion &rhs);
        ~Quaternion();
        
    public:
        inline float& operator[] (const int idx);
        inline const float operator[] (const int idx) const;
        inline bool operator == (const Quaternion &rhs);
        inline Quaternion& operator *= (const Quaternion &rhs);
        inline Quaternion& operator *= (const float value);
        inline Quaternion& operator += (const Quaternion &rhs);
        inline Quaternion& operator += (const float value);
        inline Quaternion& operator -= (const Quaternion &rhs);
        inline Quaternion& operator -= (const float value);
        inline Quaternion& operator /= (const float value);
        friend inline Quaternion operator * (const Quaternion &lhs, const Quaternion &rhs);
        friend inline Quaternion operator * (const Quaternion &lhs, const float value);
        friend inline Quaternion operator * (const float value, const Quaternion &lhs);
        friend inline Quaternion operator - (const Quaternion &lhs, const Quaternion &rhs);
        friend inline Quaternion operator - (const Quaternion &lhs, const float value);
        friend inline Quaternion operator + (const Quaternion &lhs, const Quaternion &rhs);
        friend inline Quaternion operator + (const Quaternion &lhs, const float value);
        friend inline Quaternion operator / (const Quaternion &lhs, const float value);
    public:
        inline float Length();

        inline Matrix<float, 4, 4> GetRotateMatrix();
        inline Quaternion GetConjugate();
        inline Quaternion GetInverse();
        inline Quaternion GetNormalized();
        inline Quaternion GetPow(float e);
        
        inline Quaternion& Pow(float e);
        inline Quaternion& Inverse();
        inline Quaternion& Conjugate();
        inline vector<float, 3> Rotate(const vector<float, 3> &rhs);
        inline Quaternion& Normalized();
        
    private:
        inline float LengthSquare();
        
    public:
        friend inline float Dot(const Quaternion &lhs, const Quaternion &rhs);
        friend inline Quaternion Cross(const Quaternion &lhs, const Quaternion &rhs);
        friend inline Quaternion Lerp(const Quaternion &lhs, const Quaternion &rhs, const float t);

    public:
        union{
            struct{
                float w;
                union{
                    struct{
                        float x;
                        float y;
                        float z;
                    };
                    float v[3];
                };
            };
            float m_V[4];
            float m_Ele[4];
        };
    };
#include "NXQuaternion.inl"
}


#endif