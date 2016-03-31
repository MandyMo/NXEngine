#ifndef __ZX_NXENGINE_H__
#define __ZX_NXENGINE_H__

/*
 *  File:    Matrix.h
 *  author:  张雄
 *  date:    2016_02_23
 *  purpose: 用于定义3d数学的matrix，注意，此matrix只适合于存储简单的内置基本类型，存放class和struct类型，请不要使用
 */

#include "NXVector.h"

namespace NX {
    template<typename T, int Row, int Col>
    class Matrix{
    public:
        template<typename U>
        Matrix(const Matrix<U, Row, Col> &rhs);
        Matrix(const Matrix &rhs);
        Matrix();
        Matrix(const T *ptr);
        template<typename U>
        Matrix(const vector<U, Col> *v);
        template<typename U>
        Matrix(const U (&ary)[Row][Col]);
    public:
        template<typename U>
        Matrix<T, Row, Col>& operator += (const Matrix<U, Row, Col> &rhs);
        
        template<typename U>
        Matrix<T, Row, Col>& operator -= (const Matrix<U, Row, Col> &rhs);
        
        Matrix<T, Row, Col>& operator += (const T &value);
        
        Matrix<T, Row, Col>& operator -= (const T &value);
        
        Matrix<T, Row, Col>& operator *= (const T &value);
        
        Matrix<T, Row, Col>& operator /= (const T &value);
        
        T (&operator [] (int index))[Col];
    public:
        T& GetElement(int row, int col);
        
        template<typename U, int Scale>
        void SetRow(int row, const vector<U, Scale> &rhs);
        
        template<typename U, int Scale>
        void SetCol(int col, const vector<U, Scale> &rhs);
        
        int GetRowCount(){
            return Row;
        }
        
        int GetColCount(){
            return Col;
        }
    public:
        T m_Element[Row][Col];
    };
    
#include "NXMatrix.inl"
    
}

#endif