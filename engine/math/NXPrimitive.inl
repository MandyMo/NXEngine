/*
 *  File:    NXPrimitive.inl
 *  author:  张雄
 *  date:    2016_05_13
 *  purpose: 基本的3D图元
 */

#ifndef __ZX_NXENGINE_PRIMITIVE_INL__
#define __ZX_NXENGINE_PRIMITIVE_INL__
//======================================begin line nomember function====================================================
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

inline float Distance(const Line &lhs, const Line &rhs){
    return lhs.Distance(rhs);
}

inline std::pair<bool, vector<float, 3> >  Intersect(const Line &lhs, const Line &rhs){
    return lhs.Intersect(rhs);
}
//========================================end line nomember function====================================================



//=====================================begin plane nomember function====================================================

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

template<typename T>
inline Plane Transform(const Matrix<T, 4, 4> &matrix, const Plane &plane){
    return Plane(plane).Transform(matrix);
}
//==========================================end plane nomember function=================================================
#endif