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
        const std::pair<bool, Matrix<float, 3, 3> > &SS = ReverseSafe(M);
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

#endif