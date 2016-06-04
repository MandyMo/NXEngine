/*
 *  File:    NXPrimitive.inl
 *  author:  张雄
 *  date:    2016_05_13
 *  purpose: 基本的3D图元
 */

#ifndef __ZX_NXENGINE_PRIMITIVE_INL__
#define __ZX_NXENGINE_PRIMITIVE_INL__

inline Line::Line(){/*empty*/}

inline Line::Line(const vector<float, 3> &begin, const vector<float, 3> &end):m_BeginPosition(begin), m_vDirection(end - begin){/*empty*/}

template<typename T>
inline Line& Line::Transform(const Matrix<T, 3, 3> &rhs){
    {//transform begin point
        const Matrix<T, 3, 1> &RefObj = rhs * m_BeginPosition;
        m_BeginPosition.Set(RefObj.m_Element[0][0], RefObj.m_Element[1][0], RefObj.m_Element[2][0]);
    }
    
    {//transform direction vector
        const Matrix<T, 3, 1> &RefObj = rhs * m_vDirection;
        m_vDirection.Set(RefObj.m_Element[0][0], RefObj.m_Element[1][0], RefObj.m_Element[2][0]);
    }
    
    return *this;
}

template<typename T>
inline Line& Line::Transform(const Matrix<T, 4, 4> &rhs){
    {//transfrom begin point
        const Matrix<T, 4, 1> &RefObj = rhs * NX::float4(m_BeginPosition.x, m_BeginPosition.y, m_BeginPosition.z, T(1));
        m_BeginPosition.Set(RefObj[0][0] / RefObj[3][0], RefObj[1][0] / RefObj[3][0], RefObj[2][0] / RefObj[3][0]);
    }
    
    {//transform direction vector
        const Matrix<T, 4, 1> &RefObj = rhs * NX::float4(m_vDirection.x, m_vDirection.y, m_vDirection.z, T(0));
        m_vDirection.Set(RefObj[0][0], RefObj[1][0], RefObj[2][0] );
    }
    return *this;
}

template<typename T>
inline Line Line::GetTransformed(const Matrix<T, 3, 3> &rhs){
    return Line(*this).Transform(rhs);
}

template<typename T>
inline Line Line::GetTransformed(const Matrix<T, 4, 4> &rhs){
    return Line(*this).Transform(rhs);
}

inline vector<float, 3> Line::GetBeginPosition() const{
    return m_BeginPosition;
}

inline vector<float, 3> Line::GetDirection() const{
    return m_vDirection;
}

inline vector<float, 3> Line::GetPoint(const float t) const{
    return m_BeginPosition + t * m_vDirection;
}

template<typename T>
inline float Line::Distance(const vector<T, 3> &Point) const{
    const vector<T, 3> v = Point - m_BeginPosition;
    float t = ::NX::Dot(m_vDirection, v) / Dot(m_vDirection, m_vDirection);
    return Length(t * m_vDirection - v);
}

inline float Line::Distance(const Line &rhs) const{//两直线距离
    float V12   = ::NX::Dot(m_vDirection, rhs.m_vDirection);
    float Delta = V12 * V12 - ::NX::LengthSquare(m_vDirection) * ::NX::LengthSquare(rhs.m_vDirection);
    if(NX::NXAbs(Delta) < Epsilon<float>::m_Epsilon){//line parallel, so it's easy
        return Distance(rhs.m_BeginPosition);
    }else{
        vector<float, 3> v = rhs.m_BeginPosition - m_BeginPosition;
        float a = ::NX::Dot(v, m_vDirection), b = Dot(v, rhs.m_vDirection);
        float V11 = ::NX::LengthSquare(m_vDirection);
        float V22 = ::NX::LengthSquare(rhs.m_vDirection);
        float t1 = (-V22 * a + V12 * b) / Delta;
        float t2 = (-V12 * a + V11 * b) / Delta;
        return ::NX::Length(GetPoint(t1) - rhs.GetPoint(t2));
    }
}

static std::pair<bool, vector<float, 2> > SolveEquation(const Matrix<float, 2, 2> &M, const vector<float, 2> &V){
    std::pair<bool, vector<float, 2> > result;
    float Delta = M[0][0] * M[1][1] - M[0][1] * M[1][0];
    if(NXAbs(Delta) < Epsilon<float>::m_Epsilon){
        result.first = false;
        return result;
    }
    result.first = true;
    result.second[0] = M[1][1] * V[0] - M[0][1] * V[1];
    result.second[1] = M[0][0] * V[1] - M[1][0] * V[0];
    result.second /= Delta;
    return result;
}

inline std::pair<bool, vector<float, 3> >  Line::Intersect(const Plane &plane) const{//直线与平面交点
    return plane.Intersect(*this);
}

inline std::pair<bool, vector<float, 3> >  Line::Intersect(const Line &rhs) const{ //两直线的交点
    Matrix<float, 2, 2> M;
    vector<float, 2>    V;
    M[0][0] = ::NX::LengthSquare(m_vDirection),  M[0][1] = -::NX::Dot(m_vDirection, rhs.m_vDirection);
    M[1][0] = -M[0][1],                    M[1][1] = LengthSquare(rhs.m_vDirection);
    V[0] = ::NX::Dot(m_vDirection, rhs.m_BeginPosition - m_BeginPosition);
    V[1] = ::NX::Dot(rhs.m_vDirection, m_BeginPosition - rhs.m_BeginPosition);
    const std::pair<bool, vector<float, 2> > &SS = SolveEquation(M, V);
    if(SS.first){
        return std::make_pair(true, GetPoint(SS.second[0]));
    }
    return std::make_pair(false, vector<float, 2>());
}

template<typename T>
inline Line Transform(const Line &lhs, const Matrix<T, 3, 3> &rhs){
    return Line(lhs).Transform(rhs);
}

template<typename T>
inline Line Transform(const Matrix<T, 3, 3> &lhs, const Line &rhs){
    return Line(rhs).Transform(lhs);
}

template<typename T>
inline Line Transform(const Line &lhs, const Matrix<T, 4, 4> &rhs){
    return Line(lhs).Transform(rhs);
}

template<typename T>
inline Line Transform(const Matrix<T, 4, 4> &lhs, const Line &rhs){
    return Line(rhs).Transform(lhs);
}




inline Plane::Plane(){ /*empty*/}

inline Plane::Plane(const float nx, const float ny, const float nz, const float distance):m_vPlaneNormal(nx, ny, nz), m_fDistFromOriginal(distance){
    ::NX::Normalize(m_vPlaneNormal);
}

template<typename T>
inline Plane::Plane(const vector<T, 4> &L):m_vPlaneNormal(L.x, L.y, L.z),m_fDistFromOriginal(L.w){
    Normalize();
}

inline Plane::Plane(const vector<float, 3> &a, const vector<float, 3> &b, const vector<float, 3> &c){
    vector<float, 3> v1 = a - b;
    vector<float, 3> v2 = a - c;
    m_vPlaneNormal      = ::NX::Cross(v1, v2);
    m_fDistFromOriginal = -::NX::Dot(m_vPlaneNormal, a);
    Normalize();
}

inline Plane::Plane(const Plane &rhs):m_vPlaneNormal(rhs.m_vPlaneNormal), m_fDistFromOriginal(rhs.m_fDistFromOriginal){/*empty*/}

inline Plane::Plane(const vector<float, 3> &Normal, const vector<float, 3> &PointInPlane):m_vPlaneNormal(Normal), m_fDistFromOriginal(-Dot(PointInPlane, Normal)){
    Normalize();
}

inline Plane::Plane(const vector<float, 3> &Normal, const float fDistFromOriginal):m_vPlaneNormal(GetNormalize(Normal)), m_fDistFromOriginal(fDistFromOriginal){
}

template<typename T, typename U>
inline Plane& Plane::Transform(const Matrix<T, 3, 3> &matrix, const vector<U, 3> &translation){
    Matrix<T, 4, 4> M;
    {
        M.template SetRow<T, 3>(0, matrix[0]);
        M.template SetRow<T, 3>(1, matrix[1]);
        M.template SetRow<T, 3>(2, matrix[2]);
        M.template SetCol<U, 3>(3, translation);
        M[3][3] = T(1);
    }
    return Transform(M);
}

template<typename T>
inline Plane& Plane::Transform(const Matrix<T, 4, 4> &matrix){
    const Matrix<T, 4, 1> &M = Transpose(Reverse(matrix)) * float4(m_vPlaneNormal.x, m_vPlaneNormal.y, m_vPlaneNormal.z, m_fDistFromOriginal);
    m_vPlaneNormal.Set(M[0][0], M[1][0], M[2][0]);
    m_fDistFromOriginal = M[3][0];
    return *this;
}


template<typename T, typename U>
inline Plane Plane::GetTransformed(const Matrix<T, 3, 3> &matrix, const vector<U, 3> &translation){
    return Plane(*this).Transform(matrix, translation);
}

template<typename T>
inline Plane Plane::GetTransformed(const Matrix<T, 4, 4> &matrix){
    return Plane(*this).Transform(matrix);
}


inline std::pair<bool, Line> Plane::Intersect(const Plane &rhs) const{  //平面交线
    Matrix<float, 2, 2> M;
    vector<float, 2>    V;
    M[0][0] = m_vPlaneNormal[0],     M[0][1] = m_vPlaneNormal[1];
    M[1][0] = rhs.m_vPlaneNormal[0], M[1][1] = rhs.m_vPlaneNormal[1];
    
    {
        V[0] = -m_fDistFromOriginal;
        V[1] = -rhs.m_fDistFromOriginal;
        const std::pair<bool, vector<float, 2> > &SS = SolveEquation(M, V);
        if(SS.first){
            vector<float, 3>  begin(SS.second[0], SS.second[1], 0);
            return std::make_pair<bool, Line>(true, Line(begin, begin + Cross(m_vPlaneNormal, rhs.m_vPlaneNormal)));
        }
    }
    
    {
        V[0] = -m_fDistFromOriginal - m_vPlaneNormal[2];
        V[1] = rhs.m_fDistFromOriginal - rhs.m_vPlaneNormal[2];
        const std::pair<bool, vector<float, 2> > &SS = SolveEquation(M, V);
        if(SS.first){
            vector<float, 3>  begin(SS.second[0], SS.second[1], 1);
            return std::make_pair<bool, Line>(true, Line(begin, begin + Cross(m_vPlaneNormal, rhs.m_vPlaneNormal)));
        }
    }
    return std::make_pair(false, Line());
}

inline float  Plane::Distance(const vector<float, 3> &rhs) const{      //点到平面距离
    return (Dot(m_vPlaneNormal, rhs) + m_fDistFromOriginal) / Length(m_vPlaneNormal);
}

template<typename T, typename U>
inline Plane Transform(const Plane &plane, const Matrix<T, 3, 3> &matrix, const vector<U, 3> &translation){
    return Plane(plane).Transform(matrix, translation);
}

template<typename T>
inline Plane Transform(const Plane &plane, const Matrix<T, 4, 4> &matrix){
    return Plane(plane).Transform(matrix);
}

template<typename T>
inline Plane Transform(const Matrix<T, 4, 4> &matrix, const Plane &plane){
    return Plane(plane).Transform(matrix);
}

inline float Distance(const Line &lhs, const Line &rhs){
    return lhs.Distance(rhs);
}

inline std::pair<bool, vector<float, 3> >  Intersect(const Line &lhs, const Line &rhs){
    return lhs.Intersect(rhs);
}

inline std::pair<bool, float3> Plane::Intersect(const Line  &rhs) const{
    float Delta = Dot(rhs.m_vDirection, m_vPlaneNormal);
    if(NXAbs(Delta) < Epsilon<float>::m_Epsilon){
        return std::make_pair(false, float3());
    }
    float t = -(Dot(m_vPlaneNormal, rhs.m_BeginPosition) + m_fDistFromOriginal) / Delta;
    return std::make_pair(true, rhs.GetPoint(t));
}

inline std::pair<bool, Line> Intersect(const Plane &lhs, const Plane &rhs){
    return lhs.Intersect(rhs);
}

inline float  Distance(const Plane &plane, const vector<float, 3> &rhs){
    return plane.Distance(rhs);
}

inline float  Distance(const vector<float, 3> &rhs, const Plane &plane){
    return plane.Distance(rhs);
}

inline std::pair<bool, float3> Intersect(const Line  &line,  const Plane &plane){
    return plane.Intersect(line);
}

inline std::pair<bool, float3> Intersect(const Plane &plane, const Line  &line){
    return plane.Intersect(line);
}

inline std::pair<bool, vector<float, 3> > Intersect(const Plane &PlaneA, const Plane &PlaneB, const Plane &PlaneC){
    Matrix<float, 3, 3> M;
    Matrix<float, 3, 1> Result;
    {
        M.SetRow(0, PlaneA.m_vPlaneNormal);
        M.SetRow(1, PlaneB.m_vPlaneNormal);
        M.SetRow(2, PlaneC.m_vPlaneNormal);
        const std::pair<bool, Matrix<float, 3, 3> > &SS = GetReverseSafe(M);
        if(!SS.first){
            return std::make_pair(false, vector<float, 3>());
        }
        Result = SS.second * float3(PlaneA.m_fDistFromOriginal, PlaneB.m_fDistFromOriginal, PlaneC.m_fDistFromOriginal);
    }
    return std::make_pair(true, vector<float, 3>(-Result[0][0], -Result[1][0], -Result[2][0]));
}

inline Plane& Plane::Normalize(){
    float len = ::NX::Length(m_vPlaneNormal);
    float Mult = 1.0f / len;
    m_vPlaneNormal.x *= Mult;
    m_vPlaneNormal.y *= Mult;
    m_vPlaneNormal.z *= Mult;
    m_fDistFromOriginal *= Mult;
    return *this;
}

//================================================begin circle==========================================================
inline Circle::Circle(){
    /*empty*/
}

inline Circle::Circle(const Circle &rhs):m_vCenter(rhs.m_vCenter), m_vNormal(rhs.m_vNormal), m_fRadius(rhs.m_fRadius){
    /*empty*/
}
inline Circle::Circle(const float3 &ptCenter, const float3 &normal, const float radius):m_vCenter(ptCenter), m_vNormal(normal), m_fRadius(radius){
    /*empty*/
}

inline Circle::Circle(const float3 &ptA, const float3 &ptB, const float3 &ptC){
    float aa = ::NX::LengthSquare(ptB - ptC);
    float bb = ::NX::LengthSquare(ptA - ptC);
    float cc = ::NX::LengthSquare(ptA - ptB);
    float a = std::sqrt(aa);
    float b = std::sqrt(bb);
    float c = std::sqrt(cc);
    float p = (a + b + c) * 0.5f;
    float s = std::sqrt(p * (p - a) * (p - b) * (p - c));
    float Mult = 1 / (4.0 * s);
    float CotA = (bb + cc - aa) * Mult;
    float CotB = (aa + cc - bb) * Mult;
    float CotC = (aa + bb - cc) * Mult;
    
    m_vCenter = (1 - CotB * CotC) * ptA + (1 - CotA * CotC) * ptB + (1 - CotA * CotB) * ptC;
    m_vCenter *= 0.5;
    
    m_vNormal = ::NX::Cross(ptB - ptA, ptC - ptA);
    m_fRadius = 0.25 * a * b * c / s;
}

inline Circle::~Circle(){
    /*empty*/
}

float3 Circle::GetCenter() const{
    return m_vCenter;
}

float3 Circle::GetNormal() const{
    return m_vNormal;
}

float Circle::GetRadius() const{
    return m_fRadius;
}

float  Circle::GetArea() const{
    return kfPi * m_fRadius * m_fRadius;
}

inline float Circle::GetCircumference() const{
    return kf2Pi * m_fRadius;
}

Circle  Circle::GetTransformed(const Matrix<float, 3, 3> &matrix) const{
    return Circle(*this).Transform(matrix);
}

Circle  Circle::GetTransformed(const Matrix<float, 4, 4> &matrix) const{
    return Circle(*this).Transform(matrix);
}

Circle  Circle::GetTranslated(const float3 &v) const{
    return Circle(*this).Translate(v);
}

Circle& Circle::Transform(const Matrix<float, 3, 3> &matrix){
    {
        const Matrix<float, 3, 1> &RV = ::NX::GetTranspose(::NX::GetReverse(matrix)) * m_vNormal;
        m_vNormal.Set(RV[0][0], RV[1][0], RV[2][0]);
    }
    {
        const Matrix<float, 3, 1> &RV = matrix * m_vCenter;
        m_vCenter.Set(RV[0][0], RV[1][0], RV[2][0]);
    }
    
    return *this;
}

Circle& Circle::Transform(const Matrix<float, 4, 4> &matrix){
    {
        const Matrix<float, 4, 1> &RV = ::NX::GetTranspose(::NX::GetReverse(matrix)) * NX::vector<float, 4>(m_vNormal.x, m_vNormal.y, m_vNormal.z, 0.0f);
        m_vNormal.Set(RV[0][0], RV[1][0], RV[2][0]);
    }
    
    {
        const Matrix<float, 4, 1> &RV = matrix * NX::vector<float, 4>(m_vCenter.x, m_vCenter.y, m_vCenter.z, 1.0f);
        const float Mult = 1.0f / RV[3][0];
        m_vCenter.Set(RV[0][0] * Mult, RV[1][0] * Mult, RV[2][0] * Mult);
    }
    return *this;
}

Circle& Circle::Translate(const float3 &v){
    m_vCenter += v;
    return *this;
}
//==================================================end of circle=======================================================



//==================================================begin Sphere circle=================================================
inline Sphere::Sphere(){
    
}

inline Sphere::Sphere(const float3 &ptCenter, const float3 &ptOnSphere):m_vCenter(ptCenter), m_fRadius(NX::Length(ptOnSphere - ptCenter)){
    /*empty*/
}

inline Sphere::Sphere(const float3 &ptCenter, const float fRadius):m_vCenter(ptCenter), m_fRadius(fRadius){
    /*empty*/
}

inline Sphere::Sphere(const float3 &ptA, const float3 &ptB, const float3 &ptC, const float3 &ptD){
    NX::Matrix<float, 3, 3> m;
    m.SetRow(0, 2 * (ptA - ptB));
    m.SetRow(1, 2 * (ptA - ptC));
    m.SetRow(2, 2 * (ptA - ptD));
    float aa = NX::LengthSquare(ptA);
    float bb = NX::LengthSquare(ptB);
    float cc = NX::LengthSquare(ptC);
    float dd = NX::LengthSquare(ptD);
    const NX::Matrix<float, 3, 1> &Result = NX::GetReverse(m) * NX::float3(aa - bb, aa - cc, aa - dd);
    m_vCenter.Set(Result[0][0], Result[1][0], Result[2][0]);
    m_fRadius = NX::Length(ptA - m_vCenter);
}

inline Sphere::Sphere(const Sphere &rhs):m_vCenter(rhs.m_vCenter), m_fRadius(rhs.m_fRadius){
    /*empty*/
}

inline Sphere::~Sphere(){
    /*empty*/
}

inline float Sphere::GetVolume() const{
    return 4.0f / 3.0f * kfPi * m_fRadius * m_fRadius * m_fRadius;
}

inline float Sphere::GetArea()   const{
    return 4.0f * kfPi * m_fRadius * m_fRadius;
}

inline float Sphere::GetRadius() const{
    return m_fRadius;
}

inline float3 Sphere::GetCenter() const{
    return m_vCenter;
}

inline Sphere  Sphere::GetTransformed(const Matrix<float, 3, 3> &matrix) const{
    return Sphere(*this).Transform(matrix);
}

inline Sphere  Sphere::GetTransformed(const Matrix<float, 4, 4> &matrix) const{
    return Sphere(*this).Transform(matrix);
}

inline Sphere  Sphere::GetTranslated(const float3 &v) const{
    return Sphere(*this).Translate(v);
}

inline Sphere& Sphere::Transform(const Matrix<float, 3, 3> &matrix){
    const NX::Matrix<float, 3, 1> &RV = matrix * m_vCenter;
    m_vCenter.Set(RV[0][0], RV[1][0], RV[2][0]);
    return *this;
}

inline Sphere& Sphere::Transform(const Matrix<float, 4, 4> &matrix){
    const NX::Matrix<float, 4, 1> &RV = matrix * NX::vector<float, 4>(m_vCenter.x, m_vCenter.y, m_vCenter.z, 1.0f);
    const float Mult = 1.0f / RV[3][0];
    m_vCenter.Set(RV[0][0] * Mult, RV[1][0] * Mult, RV[2][0] * Mult);
    return *this;
}

inline Sphere& Sphere::Translate(const float3 &v){
    m_vCenter += v;
    return *this;
}

inline bool Sphere::Intersect(const Sphere &rhs) const{
    return NX::LengthSquare(rhs.m_vCenter - m_vCenter) <= m_fRadius + rhs.m_fRadius;
}

inline bool Sphere::TangentWithLine(const Line &lne) const{
    return NX::NXAbs(lne.Distance(m_vCenter) - m_fRadius) <= NX::Epsilon<float>::m_Epsilon;
}

inline bool Sphere::TangentWithPlane(const Plane &plane) const{
    return NX::NXAbs(plane.Distance(m_vCenter) - m_fRadius) <= NX::Epsilon<float>::m_Epsilon;
}

inline bool Sphere::TangentWithSphere(const Sphere &rhs) const{
    return NX::NXAbs(NX::LengthSquare(rhs.m_vCenter - m_vCenter) - (m_fRadius + rhs.m_fRadius) * (m_fRadius + rhs.m_fRadius)) <= NX::Epsilon<float>::m_Epsilon;
}

//==================================================begin Sphere circle=================================================

#endif