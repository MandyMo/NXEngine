/*
 *  File:    NXQuaternion.cpp
 *  author:  张雄
 *  date:    2016_05_05
 *  purpose: 四元数操作函数
 */

#include <cstring>
#include <cstdlib>
#include "NXVector.h"
#include "NXMatrix.h"
#include "NXQuaternion.h"
#include "NXAlgorithm.h"

namespace NX{
    Quaternion::Quaternion(){
        w = 1.0f;
        x = y = z = 0.0f;
    }

    Quaternion::Quaternion(const float w,  const float x, const float y, const float z){
        this->w = w, this->x = x, this->y = y, this->z = z;
    }

    Quaternion::Quaternion(const float *v, int len/* = 4*/){
        NXAssert(len == 4);
        std::memcpy(m_V, v, sizeof(m_V));
    }

    Quaternion::Quaternion(const float radian, const NX::vector<float, 3> &Axis){
        //<w, (x, y, z)>  == <cos(theta / 2), Axis * sin(theta / 2)>
        vector<float, 3> axis(Axis);
        NX::Normalize(axis);
        const float theta = radian * 0.5f;
        float CosValue = std::cos(theta);
        float SinValue = std::sin(theta);
        w = CosValue;
        x = SinValue * axis.x;
        y = SinValue * axis.y;
        z = SinValue * axis.z;
    }

    Quaternion::Quaternion(const Quaternion &rhs){
        std::memcpy(m_V, rhs.m_V, sizeof(m_V));
    }

    Quaternion::Quaternion(const NX::vector<float, 4> &rhs){
        std::memcpy(m_V, &rhs.x, sizeof(m_V));
    }

    Quaternion::~Quaternion(){
        //empty here
    }

    float& Quaternion::operator[] (const int idx){
        NXAssert(idx >= 0 && idx < 4);
        return m_V[idx];
    }

    const float Quaternion::operator[] (const int idx) const{
        NXAssert(idx >= 0 && idx < 4);
        return m_V[idx];
    }

    bool Quaternion::operator == (const Quaternion &rhs) const{
    #define FLOAT_EQUAL(x, y) (NXAbs((x) - (y)) <= FLOAT_EPSILON)
        return FLOAT_EQUAL(w, rhs.w)  && FLOAT_EQUAL(x, rhs.x) && FLOAT_EQUAL(y, rhs.y) && FLOAT_EQUAL(z, rhs.z);
    #undef FLOAT_EQUAL
    }

    Quaternion& Quaternion::operator *= (const Quaternion &rhs){
        float w1 = w, w2 = rhs.w;
        float3 v1(x, y, z), v2(rhs.x, rhs.y, rhs.z);
        w = w1 * w2 - Dot(v1, v2);
        float3 v = (v1 * w2) + (v2 * w1) + Cross(v1, v2);
        x = v.x, y= v.y, z = v.z;
        return *this;
    }

    Quaternion& Quaternion::operator *= (const float value){
        w *= value, x *= value, y *= value, z *= value;
        return *this;
    }

    Quaternion& Quaternion::operator += (const Quaternion &rhs){
        w += rhs.w, x += rhs.x, y += rhs.y, z += rhs.z;
        return *this;
    }

    Quaternion& Quaternion::operator += (const float value){
        w += value, x += value, y += value, z += value;
        return *this;
    }

    Quaternion& Quaternion::operator -= (const Quaternion &rhs){
        w -= rhs.w, x -= rhs.x, y -= rhs.y, z -= rhs.z;
        return *this;
    }

    Quaternion& Quaternion::operator -= (const float value){
        w -= value, x -= value, y -= value, z -= value;
        return *this;
    }

    Quaternion operator * (const Quaternion &lhs, const Quaternion &rhs){
        return Quaternion(lhs) *= rhs;
    }

    Quaternion operator * (const NX::Quaternion &lhs, const float value){
        return NX::Quaternion(lhs) *= value;
    }

    Quaternion operator * (const float value, const Quaternion &lhs){
        return Quaternion(lhs) *= value;
    }

    Quaternion operator * (const Quaternion &lhs, const NX::vector<float, 3> &rhs){
        return lhs * Quaternion(0.0f, rhs.x, rhs.y, rhs.z) * lhs.GetInverse();
    }
    
    Quaternion operator * (const Quaternion &lhs, const NX::vector<float, 4> &rhs){
        NXAssert(NXAbs(rhs.w) > Epsilon<float>::m_Epsilon);
        const float Mult = 1.0f / rhs.w;
        return lhs * Quaternion(0.0f, rhs.x * Mult, rhs.y * Mult, rhs.z * Mult) * lhs.GetInverse();
    }
    
    Quaternion operator - (const Quaternion &lhs, const Quaternion &rhs){
        return Quaternion(lhs) -= rhs;
    }

    Quaternion operator - (const Quaternion &lhs, const float value){
        return Quaternion(lhs) -= value;
    }

    Quaternion operator + (const Quaternion &lhs, const Quaternion &rhs){
        return Quaternion(lhs) += rhs;
    }

    Quaternion operator + (const Quaternion &lhs, const float value){
        return Quaternion(lhs) += value;
    }

    NX::float4X4 Quaternion::GetRotateMatrix() const{
        NX::float4X4 result;
        float xx = 2 * x * x, yy = 2 * y * y, zz = 2 * z * z;
        float wx = 2 * w * x, wy = 2 * w * y, wz = 2 * w * z;
        float xy = 2 * x * y, xz = 2 * x * z, yz = 2 * y * z;
        
        result[3][3] = 1.0f;
        result[0][0] = 1 - yy - zz,     result[0][1] = xy - wz;       result[0][2] = xz + wy;
        result[1][0] = xy + wz,         result[1][1] = 1 - xx - zz,   result[1][2] = yz - wx;
        result[2][0] = xz - wy,         result[2][1] = yz + wx,       result[2][2] = 1 - xx - yy;
        return result;
    }

    Quaternion Quaternion::GetConjugate() const{
        return Quaternion(w, -x, -y, -z);
    }
    
   NX:: vector<float, 3> Quaternion::GetRotated(const NX::vector<float, 3> &rhs){
        vector<float, 3> t(rhs);
        return Rotate(t);
    }

    NX::vector<float, 3>& Quaternion::Rotate(NX::vector<float, 3> &rhs){
        const Quaternion &RefObj = (*this) * Quaternion(0, rhs.x, rhs.y, rhs.z) * GetInverse();
        rhs.x = RefObj.x, rhs.y = RefObj.y, rhs.z = RefObj.z;
        return rhs;
    }

    Quaternion& Quaternion::Normalize(){
        const float len = Length();
        w /= len, x /= len, y /= len, z /= len;
        return *this;
    }

    float Quaternion::LengthSquare(){
        return w * w + x * x + y * y + z * z;
    }

    Quaternion& Quaternion::operator /= (const float value){
        w /= value, x /= value, y /= value, z /= value;
        return *this;
    }

    Quaternion operator / (const Quaternion &lhs, const float value){
        return Quaternion(lhs) /= value;
    }

    float Quaternion::Length(){
        return std::sqrt(LengthSquare());
    }

    Quaternion Quaternion::GetInverse() const{
        return Quaternion(*this).Inverse();
    }

    Quaternion Quaternion::GetNormalized() const{
        return Quaternion(*this).Normalize();
    }

    Quaternion Quaternion::GetPow(float e) const{
        return Quaternion(*this).Pow(e);
    }

    Quaternion& Quaternion::Pow(float e){
        float alpha    = std::acos(w);
        float newalpha = alpha * e;
        float mult     = sin(newalpha) / sin(alpha);
        w              = std::cos(newalpha);
        x              *= mult;
        y              *= mult;
        z              *= mult;
        return *this;
    }

    Quaternion& Quaternion::Inverse(){
        return Conjugate() /= LengthSquare();
    }

    Quaternion& Quaternion::Conjugate(){
        x = -x, y = -y, z = -z;
        return *this;
    }

    vector<float, 3> Quaternion::GetRotateAxis(){
        float SinValue = 1.0f - w * w;
        if(SinValue < 0.0f){
            return vector<float, 3>(1.0f, 0, 0);
        }
        float factor = 1.0f / std::sqrt(SinValue);
        return vector<float, 3>(factor * x, factor * y, factor * z);
    }

    float Quaternion::GetRotateRadian(){
        return SafeACos(w) * 2.0f;
    }
    
    float Quaternion::GetRotateAngle(){
        return RD2DG(GetRotateRadian());
    }
    
    float LengthSquare(const Quaternion &lhs){
        return lhs.x * lhs.x + lhs.y * lhs.y + lhs.z * lhs.z + lhs.w * lhs.w;
    }

    float Dot(const Quaternion &lhs, const Quaternion &rhs){
        return lhs.w * rhs.w + lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
    }

    NX::Quaternion Cross(const Quaternion &lhs, const Quaternion &rhs){
        return lhs * rhs ;
    }

    float RadianByTwoQuaternion(const Quaternion &lhs, const Quaternion &rhs){
        float DotValue       = Dot(lhs, rhs);
        float DotSquareValue = DotValue * DotValue;
        float LenSquare      = LengthSquare(lhs) * LengthSquare(rhs);
        float CosValue       = std::sqrt((DotSquareValue / LenSquare));
        return std::acos(CosValue);
    }

    Quaternion Lerp(const Quaternion &lhs, const Quaternion &rhs, const float t){
        if(t <= 0.0f){
            return lhs;
        }else if(t >=  1.0f){
            return rhs;
        }
        float a, b;
        float CosValue, sign;
        CosValue = NX::Dot(lhs, rhs);
        if( CosValue < 0.0f ){
            CosValue = -CosValue;
            sign = -1.0f;
        }else{
            sign = 1.0f;
        }
        
        if (CosValue > 1.0 - FLOAT_EPSILON){
            a = 1.0f - t;
            b = t    * sign;
        }else{
            float theta  = (float)acos(CosValue);
            float sine   = (float)sin(theta);
            a = (float)(sin((1.0f - t) * theta) / sine);
            b = (float)(sin(t * theta) / sine)  * sign;
        }
        return a * lhs + b * rhs;
    }
    
    Quaternion& Quaternion::SetRotateAboutX(const float radian){
        const float theta = radian * 0.5f;
        w = std::cos(theta);
        x = std::sin(theta);
        y = 0.0f;
        z = 0.0f;
        return *this;
    }
    
    Quaternion& Quaternion::SetRotateAboutY(const float radian){
        const float theta = radian * 0.5f;
        w = std::cos(theta);
        x = 0.0f;
        y = std::sin(theta);
        z = 0.0f;
        return *this;
    }
    
    Quaternion& Quaternion::SetRotateAboutZ(const float radian){
        const float theta = radian * 0.5f;
        w = std::cos(theta);
        x = 0.0f;
        y = 0.0f;
        z = std::sin(theta);
        return *this;
    }
    
    Quaternion& Quaternion::SetRotateAboutAxis(const float radian, const NX::vector<float, 3> &axis){
        vector<float, 3> n(NX::GetNormalized(axis));
        const float theta    = radian * 0.5f;
        const float SinValue = std::sin(theta);
        w = std::cos(theta);
        x = SinValue * n.x;
        y = SinValue * n.y;
        z = SinValue * n.z;
        return *this;
    }
    
    const Quaternion kQuanternionIndentity(1.0f, 0.0f, 0.0f, 0.0f);
}