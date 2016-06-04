/*
 *  File:    NXRotateAlgorithm.h
 *  author:  张雄
 *  date:    2016_05_27
 *  purpose: 一些与matrix，vector，quaternion相关的算法
 */

#ifndef __ZX_NXENGINE_ALGORITHM_H__
#define __ZX_NXENGINE_ALGORITHM_H__

#include "NXMatrix.h"
#include "NXVector.h"
#include "NXQuaternion.h"
#include "NXEulerAngle.h"

namespace NX {
    //===============================begin some vector function=========================================================
    template<typename T, typename U, int Scale, typename RT = T>
    inline RT Dot (const vector<T, Scale> &lhs, const vector<U, Scale> &rhs);
    
    template<typename T, typename U, typename RT = T>
    inline vector<RT, 3> Cross(const vector<T, 3> &lhs, const vector<U, 3> &rhs);
    
    template<typename T, int Scale, typename RT = float>
    inline RT Length(const vector<T, Scale> &lhs);
    
    template<typename T, int Scale, typename RT = float>
    inline RT LengthSquare(const vector<T, Scale> &lhs);
    
    template<typename T, int Scale>
    inline vector<T, Scale> GetNormalize(const vector<T, Scale> &lhs);
    
    template<typename T, int Scale>
    inline vector<T, Scale>& Normalize(vector<T, Scale> &lhs);
    
    template<typename TA, typename TB, int Scale, typename RT = TA>
    inline vector<RT, Scale> Lerp(const vector<TA, Scale> &lhs, const vector<TB, Scale> &rhs, const float t);
    
    template<typename T, int Scale>
    inline vector<T, Scale> GetNegative(const vector<T, Scale> &lhs);
    
    template<typename T, int Scale>
    inline vector<T, Scale>& Negative(vector<T, Scale> &lhs);
    
    /**
     *  求点位于直接(2维)或平面(三维)上的投影(其中normal是法线，且默认直线或平面过原点)
     */
    template<typename T, typename U>
    inline vector<T, 2>& Project(vector<T, 2> &lhs, const vector<U, 2> &normal);
    
    template<typename T, typename U>
    inline vector<T, 3>& Project(vector<T, 3> &lhs, const vector<U, 3> &normal);
    
    template<typename  T, typename U, typename RT = T>
    inline vector<RT, 2> GetProject(const vector<T, 2> &lhs, const vector<U, 2> &normal);
    
    template<typename  T, typename U, typename RT = T>
    inline vector<RT, 3> GetProject(const vector<T, 3> &lhs, const vector<U, 3> &normal);
    
    /**
     *   求点位于沿直线方向上的缩放(其中direction是方向向量，且默认直线或平面过原点）
     */
    template<typename T, typename U>
    inline vector<T, 2>& Scale(vector<T, 2> &lhs, const vector<U, 2> &direction, const float s);
    
    template<typename T, typename U>
    inline vector<T, 3>& Scale(vector<T, 3> &lhs, const vector<U, 3> &direction, const float s);
    
    template<typename T, typename U, typename RT = T>
    inline vector<RT, 2> GetScale(const vector<T, 2> &lhs, const vector<U, 2> &direction, const float s);
    
    template<typename T, typename U, typename RT = T>
    inline vector<RT, 3> GetScale(const vector<T, 3> &lhs, const vector<U, 3> &direction, const float s);
    
    //=================================end some vector function=========================================================
    
    
    
    
    //================================begin some matrix function========================================================
    template<typename U, typename T = float>
    inline Matrix<T, 4, 4> LookAt(const vector<U, 3> &eye, const vector<U, 3> &look, const vector<U, 3> &up);
    
    template<typename T, int M>
    inline Matrix<T, M, M>& Transpose(Matrix<T, M, M> &lhs);
    
    template<typename T, int Row, int Col>
    inline Matrix<T, Col, Row> GetTranspose(const Matrix<T, Row, Col> &lhs);
    
    template<typename T>
    inline Matrix<T, 4, 4> Translate(const T dx, const T dy, const T dz);
    
    template<typename T, int Scale = 4>
    inline Matrix<T, Scale, Scale> RotateX(const T radian);
    
    template<typename T, int Scale = 4>
    inline Matrix<T, Scale, Scale> RotateY(const T radian);
    
    template<typename T, int Scale = 4>
    inline Matrix<T, Scale, Scale> RotateZ(const T radian);
    
    template<typename T, int Scale = 4>
    inline Matrix<T, Scale, Scale> Scalar(const T sx, const T sy, const T sz);
    
    template<typename T, int Scale = 4, typename U>
    inline Matrix<T, Scale, Scale> RotateAix(const vector<U, 3> &Aix, const T radian);
    
    //x/w: [-1, 1]
    //y/w: [-1, 1]
    //z/w: [0, 1]
    //w: z
    template<typename T, int Scale = 4>
    inline Matrix<T, Scale, Scale> Perspective(const T FovAngle, const T aspect, const T near, const T far);
    
    //x: [-1, 1]
    //y: [-1, 1]
    //z: [0, 1]
    //w: 1
    template<typename T, int Scale = 4>
    inline Matrix<T, Scale, Scale> Orthogonal(const T Width, const T Height, const T near, const T far);
    
    //x: [-1, 1]
    //y: [-1, 1]
    //z: [0, 1]
    //w: 1
    template<typename T, int Scale = 4>
    inline Matrix<T, Scale, Scale> Orthogonal(const T Left, const T Right, const T Top, const T Bottom, const T near, const T far);
    
    template<typename T, typename RT = T>
    inline RT Detaminate(const Matrix<T, 2, 2>& matrix);
    
    template<typename T, typename RT = T>
    inline RT Detaminate(const Matrix<T, 3, 3>& matrix);
    
    template<typename T, typename RT = T>
    inline RT Detaminate(const Matrix<T, 4, 4> &matrix);
    
    template<typename T, int Scale, typename RT = T>
    inline RT Detaminate(const Matrix<T, Scale, Scale> &matrix);
    
    template<typename T, typename RT = float>
    inline Matrix<RT, 2, 2> GetReverse(const Matrix<T, 2, 2>& matrix);
    
    template<typename T, typename RT = float>
    inline Matrix<RT, 3, 3> GetReverse(const Matrix<T, 3, 3>& matrix);
    
    template<typename T, typename RT = float>
    inline Matrix<RT, 4, 4> GetReverse(const Matrix<T, 4, 4> &matrix);
    
    template<typename T, int Scale, typename RT = float>
    inline Matrix<RT, Scale, Scale> GetReverse(const Matrix<T, Scale, Scale> &matrix);
    
    template<typename T, typename RT = float>
    inline Matrix<RT, 2, 2>& Reverse(Matrix<T, 2, 2>& matrix);
    
    template<typename T, typename RT = float>
    inline Matrix<RT, 3, 3>& Reverse(Matrix<T, 3, 3>& matrix);
    
    template<typename T, typename RT = float>
    inline Matrix<RT, 4, 4>& Reverse(Matrix<T, 4, 4> &matrix);
    
    template<typename T, int Scale, typename RT = float>
    inline Matrix<RT, Scale, Scale>& Reverse(Matrix<T, Scale, Scale> &matrix);
    
    template<typename T, int Scale, typename RT = float>
    inline std::pair<bool, Matrix<RT, Scale, Scale> > GetReverseSafe(const Matrix<T, Scale, Scale> &matrix);
    
    template<typename T, int iScale>
    inline Matrix<T, iScale, iScale>& SimplifyMatrix(Matrix<T, iScale, iScale> &matrix, const T EpsilonValue = Epsilon<T>::m_Epsilon);
    
    template<typename T, int iScale>
    inline Matrix<T, iScale, iScale>& GetSimplifiedMatrix(const Matrix<T, iScale, iScale> &matrix, const T EpsilonValue = Epsilon<T>::m_Epsilon);
    /**
     *  返回点投影到直线(2维)或平面(3维)上的投影方程（其中normal是法线，且默认直线或平面过原点)
     */
    template<typename  T, typename U, typename RT = float>
    inline Matrix<RT, 2, 2> GetTransformMatrix(const vector<T, 2> &lhs, const vector<U, 2> &normal);
    
    template<typename  T, typename U, typename RT = float>
    inline Matrix<RT, 3, 3> GetTransformMatrix(const vector<T, 3> &lhs, const vector<U, 3> &normal);
    
    /**
     *  返回点沿给定方向的缩放变换矩阵
     */
    template<typename T, typename U, typename RT = float>
    inline Matrix<RT, 2, 2> GetScaleMatrix(const vector<T, 2> &lhs, const vector<U, 2> &direction, const float s);
    
    template<typename T, typename U, typename RT = float>
    inline Matrix<RT, 3, 3> GetScaleMatrix(const vector<T, 3> &lhs, const vector<U, 3> &direction, const float s);
    //==================================end some matrix function========================================================
    
    
    //================================================几种旋转模型转换函数=====================================================
    EulerAngle MatrixToEulerAngle(const Matrix<float, 3, 3> &rhs, const EulerAngleMode mode);
    EulerAngle MatrixToEulerAngle(const Matrix<float, 4, 4> &rhs, const EulerAngleMode mode);
    Matrix<float, 4, 4> EulerAngleToMatrix(const EulerAngle &lhs, const EulerAngleMode mode);
    Matrix<float, 4, 4> QuaternionToMatrix(const Quaternion &lhs);
    Quaternion MatrixToQuaternion(const Matrix<float, 4, 4> &lhs);
    Quaternion MatrixToQuaternion(const Matrix<float, 3, 3> &lhs);
    EulerAngle QuaternionToEulerAngle(const Quaternion &lhs, const EulerAngleMode mode);
    Quaternion EulerAngleToQuaternion(const EulerAngle &lhs, const EulerAngleMode mode);
    //==================================================================================================================
#include "NXAlgorithm.inl"
}


#endif //__ZX_NXENGINE_ALGORITHM_H__