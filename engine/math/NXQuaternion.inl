/*
 *  File:    NXQuaternion.inl
 *  author:  张雄
 *  date:    2016_05_05
 *  purpose: 四元数操作函数
 */

#ifndef __ZX_NXENGINE_QUATERNION_INL__
#define __ZX_NXENGINE_QUATERNION_INL__

inline Quaternion::Quaternion(){
    w = 1.0f;
    x = y = z = 0.0f;
}

inline Quaternion::Quaternion(const float w,  const float x, const float y, const float z){
    this->w = w, this->x = x, this->y = y, this->z = z;
}

inline Quaternion::Quaternion(const float *v, int len/* = 4*/){
    std::memcpy(m_V, v, sizeof(m_V));
}

inline Quaternion::Quaternion(const float radian, const vector<float, 3> &Axis){
    //<w, (x, y, z)>  == <cos(theta / 2), Axis * sin(theta / 2)>
    vector<float, 3> axis = Axis;
    Normalize(axis);
    float CosValue = std::cos(radian / 2);
    float SinValue = std::sin(radian / 2);
    w = CosValue;
    x = SinValue * axis.x;
    y = SinValue * axis.y;
    z = SinValue * axis.z;
}

inline Quaternion::Quaternion(const Quaternion &rhs){
    std::memcpy(m_V, rhs.m_V, sizeof(m_V));
}

inline Quaternion::Quaternion(const vector<float, 4> &rhs){
    std::memcpy(m_V, &rhs.x, sizeof(m_V));
}

inline Quaternion::~Quaternion(){
    //empty here
}

inline float& Quaternion::operator[] (const int idx){
    assert(idx >= 0 && idx < 4);
    return m_V[idx];
}

inline const float Quaternion::operator[] (const int idx) const{
    assert(idx >= 0 && idx < 4);
    return m_V[idx];
}

inline bool Quaternion::operator == (const Quaternion &rhs){
#define FLOAT_EQUAL(x, y) (NXAbs((x) - (y)) <= FLOAT_EPSILON)
    return FLOAT_EQUAL(w, rhs.w)  && FLOAT_EQUAL(x, rhs.x) && FLOAT_EQUAL(y, rhs.y) && FLOAT_EQUAL(z, rhs.z);
#undef FLOAT_EQUAL
}

inline Quaternion& Quaternion::operator *= (const Quaternion &rhs){
    float w1 = w, w2 = rhs.w;
    float3 v1(x, y, z), v2(rhs.x, rhs.y, rhs.z);
    w = w1 * w2 - Dot(v1, v2);
    float3 v = (v1 * w2) + (v2 * w1) + Cross(v1, v2);
    x = v.x, y= v.y, z = v.z;
    return *this;
}

inline Quaternion& Quaternion::operator *= (const float value){
    w *= value, x *= value, y *= value, z *= value;
    return *this;
}

inline Quaternion& Quaternion::operator += (const Quaternion &rhs){
    w += rhs.w, x += rhs.x, y += rhs.y, z += rhs.z;
    return *this;
}

inline Quaternion& Quaternion::operator += (const float value){
    w += value, x += value, y += value, z += value;
    return *this;
}

inline Quaternion& Quaternion::operator -= (const Quaternion &rhs){
    w -= rhs.w, x -= rhs.x, y -= rhs.y, z -= rhs.z;
    return *this;
}

inline Quaternion& Quaternion::operator -= (const float value){
    w -= value, x -= value, y -= value, z -= value;
    return *this;
}

inline Quaternion operator * (const Quaternion &lhs, const Quaternion &rhs){
    return Quaternion(lhs) *= rhs;
 }

inline Quaternion operator * (const Quaternion &lhs, const float value){
    return Quaternion(lhs) *= value;
}

inline Quaternion operator * (const float value, const Quaternion &lhs){
    return Quaternion(lhs) *= value;
}

inline Quaternion operator - (const Quaternion &lhs, const Quaternion &rhs){
    return Quaternion(lhs) -= rhs;
}

inline Quaternion operator - (const Quaternion &lhs, const float value){
    return Quaternion(lhs) -= value;
}

inline Quaternion operator + (const Quaternion &lhs, const Quaternion &rhs){
    return Quaternion(lhs) += rhs;
}

inline Quaternion operator + (const Quaternion &lhs, const float value){
    return Quaternion(lhs) += value;
}

inline float4X4 Quaternion::GetRotateMatrix(){
    float4X4 result;
    float xx = 2 * x * x, yy = 2 * y * y, zz = 2 * z * z;
    float wx = 2 * w * x, wy = 2 * w * y, wz = 2 * x * w;
    float xy = 2 * x * y, xz = 2 * x * z, yz = 2 * y * z;
    
    result[3][3] = 1.0f;
    result[0][0] = 1 - yy - zz,     result[0][1] = xy - wz;       result[0][2] = xz + wy;
    result[1][0] = xy + wz,         result[1][1] = 1 - xx - zz,   result[1][2] = yz - wx;
    result[2][0] = xz - wy,         result[2][1] = yz + wx,       result[2][2] = 1 - xx - yy;
    return result;
}

inline Quaternion Quaternion::GetConjugate(){
    return Quaternion(w, -x, -y, -z);
}

inline  vector<float, 3> Quaternion::Rotate(const vector<float, 3> &rhs){
    const Quaternion &RefObj = (*this) * Quaternion(0, rhs.x, rhs.y, rhs.z) * GetInverse();
    return float3(RefObj.x, RefObj.y, RefObj.z);
}

inline Quaternion& Quaternion::Normalized(){
    const float len = Length();
    w /= len, x /= len, y /= len, z /= len;
    return *this;
}

inline float Quaternion::LengthSquare(){
    return w * w + x * x + y * y + z * z;
}

inline Quaternion& Quaternion::operator /= (const float value){
    w /= value, x /= value, y /= value, z /= value;
    return *this;
}

inline Quaternion operator / (const Quaternion &lhs, const float value){
    return Quaternion(lhs) /= value;
}

inline float Quaternion::Length(){
    return sqrt(LengthSquare());
}

inline Quaternion Quaternion::GetInverse(){
    return Quaternion(*this).Inverse();
}

inline Quaternion Quaternion::GetNormalized(){
    return Quaternion(*this).Normalized();
}

inline Quaternion Quaternion::GetPow(float e){
    return Quaternion(*this).Pow(e);
}

inline Quaternion& Quaternion::Pow(float e){
    float alpha    = std::acos(w);
    float newalpha = alpha * e;
    float mult     = sin(newalpha) / sin(alpha);
    w              = std::cos(newalpha);
    x              *= mult;
    y              *= mult;
    z              *= mult;
    return *this;
}

inline Quaternion& Quaternion::Inverse(){
    return (*this) /= LengthSquare();
}

inline Quaternion& Quaternion::Conjugate(){
    x = -x, y = -y, z = -z;
    return *this;
}


inline float LengthSquare(const Quaternion &lhs){
    return lhs.x * lhs.x + lhs.y * lhs.y + lhs.z * lhs.z + lhs.w * lhs.w;
}

inline float Dot(const Quaternion &lhs, const Quaternion &rhs){
    return lhs.w * rhs.w + lhs.x * rhs.x + rhs.y * rhs.y + lhs.z * rhs.z;
}

inline Quaternion Cross(const Quaternion &lhs, const Quaternion &rhs){
    return lhs * rhs ;
}

inline float RadianByTwoQuaternion(const Quaternion &lhs, const Quaternion &rhs){
    float DotValue       = Dot(lhs, rhs);
    float DotSquareValue = DotValue * DotValue;
    float LenSquare      = LengthSquare(lhs) * LengthSquare(rhs);
    float CosValue       = NXAbs(DotSquareValue / LenSquare);
    return std::acos(CosValue);
}

inline Quaternion Lerp(const Quaternion &lhs, const Quaternion &rhs, const float t){
    float a, b;
    float CosValue, sign;
    CosValue = Dot(lhs, rhs);
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

#endif