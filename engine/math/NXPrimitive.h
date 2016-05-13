/*
 *  File:    NXPrimitive.h
 *  author:  张雄
 *  date:    2016_05_13
 *  purpose: 基本的3D图元
 */

#include <utility>
#include "NXVector.h"
#include "NXMatrix.h"
namespace NX{
    class Line{
    public:
        explicit Line();
        explicit Line(const vector<float, 3> &begin, const vector<float, 3> &end);
    public:
        template<typename T>
        Line& Transform(const Matrix<T, 3, 3> &rhs);
        template<typename T>
        Line& Transform(const Matrix<T, 4, 4> &rhs);
    public:
        vector<float, 3> GetBeginPosition();
        vector<float, 3> GetEndPosition();
        vector<float, 3> GetDirection();
        vector<float, 3> GetPoint(const float t);
        float Distance(const Line &rhs);                                //两直线距离
        std::pair<bool, vector<float, 3> >  Intersect(const Line &rhs); //两直线的交点
    public:
        vector<float, 3> m_BeginPosition;
        vector<float, 3> m_vDirection;
    };
    
    class Plane{
    public:
        explicit Plane();
        template<typename T>
        explicit Plane(const vector<T, 4> &L);
        explicit Plane(const vector<float, 3> &a, const vector<float, 3> &b, const vector<float, 3> &c);
        explicit Plane(const Plane &rhs);
        explicit Plane(const vector<float, 3> &Normal, const vector<float, 3> &PointInPlane);
        explicit Plane(const vector<float, 3> &Normal, const float fDistFromOriginal);
    public:
        template<typename T, typename U>
        Plane& Transform(const Matrix<T, 3, 3> &matrix, const vector<U, 3> &translation);
        template<typename T>
        Plane& Transform(const Matrix<T, 4, 4> &matrix);
    public:
        std::pair<bool, Line> Intersect(const Plane &rhs);//平面交线
        float  Distance(const vector<float, 3> &rhs);     //点到平面距离
    public:
        vector<float, 3> m_vPlaneNormal;
        float            m_fDistFromOriginal;
    };
    
    //==================================begin line nomember function====================================================
    template<typename T>
    Line Transform(const Line &lhs, const Matrix<T, 3, 3> &rhs);
    
    template<typename T>
    Line Transform(const Matrix<T, 3, 3> &rhs, const Line &lhs);
    
    template<typename T>
    Line Transform(const Line &lhs, const Matrix<T, 4, 4> &rhs);
    
    template<typename T>
    Line Transform(const Matrix<T, 4, 4> &rhs, const Line &lhs);
    
    //==================================end line nomember function======================================================
    
    
    //=================================begin plane nomember function====================================================
    template<typename T, typename U>
    Plane Transform(const Plane &plane, const Matrix<T, 3, 3> &matrix, const vector<U, 3> &translation);
    
    template<typename T>
    Plane Transform(const Plane &plane, const Matrix<T, 4, 4> &matrix);
    
    template<typename T>
    Plane Transform(const Matrix<T, 4, 4> &matrix, const Plane &plane);
    
    float Distance(const Line &lhs, const Line &rhs);
    
    std::pair<bool, vector<float, 3> >  Intersect(const Line &lhs, const Line &rhs);
    
    std::pair<bool, Line> Intersect(const Plane &lhs, const Plane &rhs);
    
    float  Distance(const Plane &plane, const vector<float, 3> &rhs);
    
    float  Distance(const vector<float, 3> &rhs, const Plane &plane);
    
    std::pair<bool, vector<float, 3> > Intersect(const Plane &PlaneA, const Plane &PlaneB, const Plane &PlaneC);
    //==================================end plane nomember function=====================================================
#include "NXPrimitive.inl"
}