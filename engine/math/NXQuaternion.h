/*
 *  File:    NXQuaternion.h
 *  author:  张雄
 *  date:    2016_05_05
 *  purpose: 四元数操作函数
 */

#ifndef __ZX_NXENGINE_QUATERNION_H__
#define __ZX_NXENGINE_QUATERNION_H__

namespace NX {
    template<typename T, int iScale> class vector;
    template<typename T, int iRow, int iCol> class Matrix;
    
    class Quaternion{
    public:
        friend  Quaternion operator * (const Quaternion &lhs, const Quaternion &rhs);
    public:
        Quaternion();
        Quaternion(const float w,  const float x, const float y, const float z);
        Quaternion(const float *v, int len = 4);
        Quaternion(const float radian, const vector<float, 3> &Axis);
        Quaternion(const vector<float, 4> &rhs);
        Quaternion(const Quaternion &rhs);
        ~Quaternion();
    public:
        Quaternion& SetRotateAboutX(const float radian);
        Quaternion& SetRotateAboutY(const float radian);
        Quaternion& SetRotateAboutZ(const float radian);
        Quaternion& SetRotateAboutAxis(const float radian, const vector<float, 3> &axis);
    public:
        float& operator[] (const int idx);
        const float operator[] (const int idx) const;
        bool operator == (const Quaternion &rhs) const;
        Quaternion& operator *= (const Quaternion &rhs);
        Quaternion& operator *= (const float value);
        Quaternion& operator += (const Quaternion &rhs);
        Quaternion& operator += (const float value);
        Quaternion& operator -= (const Quaternion &rhs);
        Quaternion& operator -= (const float value);
        Quaternion& operator /= (const float value);
        friend  Quaternion operator * (const Quaternion &lhs, const Quaternion &rhs);
        friend  Quaternion operator * (const Quaternion &lhs, const float value);
        friend  Quaternion operator * (const float value, const Quaternion &lhs);
        
        /**
         *  使用四元数对点(向量)进行变换,rhs是三维点或齐次坐标系的点(四个分量)
         */
        friend  Quaternion operator * (const Quaternion &lhs, const vector<float, 3> &rhs);
        friend  Quaternion operator * (const Quaternion &lhs, const vector<float, 4> &rhs);
        
        friend  Quaternion operator - (const Quaternion &lhs, const Quaternion &rhs);
        friend  Quaternion operator - (const Quaternion &lhs, const float value);
        friend  Quaternion operator + (const Quaternion &lhs, const Quaternion &rhs);
        friend  Quaternion operator + (const Quaternion &lhs, const float value);
        friend  Quaternion operator / (const Quaternion &lhs, const float value);
    public:
        float Length();

        Matrix<float, 4, 4> GetRotateMatrix() const;
        Quaternion GetConjugate() const;
        Quaternion GetInverse() const;
        Quaternion GetNormalized() const;
        vector<float, 3> GetRotated(const vector<float, 3> &rhs);
        
        Quaternion& Inverse();
        Quaternion& Conjugate();
        vector<float, 3>& Rotate(vector<float, 3> &rhs);
        Quaternion& Normalize();
        
        /**
         *  使用以下函数之前，请保证四元数是单位四元数(可调用normalize函数将其转化为单位四元数)
         */
        vector<float, 3> GetRotateAxis();
        Quaternion& Pow(float e);
        Quaternion GetPow(float e) const;
        float GetRotateRadian();
        float GetRotateAngle();
        
    private:
         float LengthSquare();
        
    public:
        friend  float Dot(const Quaternion &lhs, const Quaternion &rhs);
        friend  Quaternion Cross(const Quaternion &lhs, const Quaternion &rhs);
        friend  Quaternion Lerp(const Quaternion &lhs, const Quaternion &rhs, const float t);

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
    extern const Quaternion kQuanternionIndentity;
}


#endif