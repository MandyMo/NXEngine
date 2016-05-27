/*
 *  File:    NXMatrix.inl
 *  author:  张雄
 *  date:    2016_02_23
 *  purpose: 实现3d数学的matrix，注意，此matrix只适合于存储简单的内置基本类型，存放class和struct类型，请不要使用
 */

#ifndef __ZX_NXENGINE_MATRIX_INL__
#define __ZX_NXENGINE_MATRIX_INL__

template<typename T, int Row, int Col>
template<typename U>
inline Matrix<T, Row, Col>::Matrix(const Matrix<U, Row, Col> &rhs){
    for(int r = 0; r < Row; ++r){
        for(int c = 0; c < Col; ++c){
            m_Element[r][c] = rhs.m_Element[r][c];
        }
    }
}

template<typename T, int Row, int Col>
inline Matrix<T, Row, Col>::Matrix(const Matrix &rhs){
    std::memcpy(m_Element, rhs.m_Element, sizeof(m_Element));
}

template<typename T, int Row, int Col>
inline Matrix<T, Row, Col>::Matrix(){
    std::memset(m_Element, 0, sizeof(m_Element));
}

template<typename T, int Row, int Col>
inline Matrix<T, Row, Col>::Matrix(const T *ptr){
    memcpy(m_Element, ptr, sizeof(m_Element));
}

template<typename T, int Row, int Col>
template<typename U>
inline Matrix<T, Row, Col>::Matrix(const vector<U, Col> *v){
    for(int r = 0; r < Row; ++r){
        for(int c = 0; c < Col; ++c){
            m_Element[r][c] = v[r][c];
        }
    }
}

template<typename T, int Row, int Col>
template<typename U>
inline Matrix<T, Row, Col>::Matrix(const U (&ary)[Row][Col]){
    for(int r = 0; r < Row; ++r){
        for(int c = 0; c < Col; ++c){
            m_Element[r][c] = ary[r][c];
        }
    }
}

template<typename T, int Row, int Col>
template<typename U>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::operator += (const Matrix<U, Row, Col> &rhs){
    for(int r = 0; r < Row; ++r){
        for(int c = 0; c < Col; ++c){
            m_Element[r][c] += rhs.m_Element[r][c];
        }
    }
    return *this;
}

template<typename T, int Row, int Col>
template<typename U>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::operator -= (const Matrix<U, Row, Col> &rhs){
    for(int r = 0; r < Row; ++r){
        for(int c = 0; c < Col; ++c){
            m_Element[r][c] -= rhs.m_Element[r][c];
        }
    }
    return *this;
}

template<typename T, int Row, int Col>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::operator += (const T &value){
    for(int r = 0; r < Row; ++r){
        for(int c = 0; c < Col; ++c){
            m_Element[r][c] += value;
        }
    }
    return *this;
}

template<typename T, int Row, int Col>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::operator -= (const T &value){
    for(int r = 0; r < Row; ++r){
        for(int c = 0; c < Col; ++c){
            m_Element[r][c] -= value;
        }
    }
    return *this;
}

template<typename T, int Row, int Col>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::operator *= (const T &value){
    for(int r = 0; r < Row; ++r){
        for(int c = 0; c < Col; ++c){
            m_Element[r][c] *= value;
        }
    }
    return *this;
}

template<typename T, int Row, int Col>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::operator /= (const T &value){
    for(int r = 0; r < Row; ++r){
        for(int c = 0; c < Col; ++c){
            m_Element[r][c] /= value;
        }
    }
    return *this;
}

template<typename T, int Row, int Col>
inline T& Matrix<T, Row, Col>::GetElement(int row, int col){
    assert(row >= 0 && col >= 0 && row < Row && col < Col);
    return m_Element[row][col];
}

template<typename T, int Row, int Col>
template<typename U, int Scale>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::SetRow(int row, const vector<U, Scale> &rhs){
    assert(row < Row && row >=0);
    for(int i = 0, l = std::min(Scale, Col); i < l; ++i){
        m_Element[row][i] = rhs.v[i];
    }
    return *this;
}

template<typename T, int Row, int Col>
template<typename U>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::SetRow(int row, const U *ptr){
    assert(row < Row && row >=0);
    const U *p = ptr;
    for(int i = 0; i < Col; ++i){
        m_Element[row][i] = *p++;
    }
    return *this;
}

template<typename T, int Row, int Col>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::SetRow(int row, const T value){
    assert(row < Row && row >=0);
    for(int i = 0; i < Col; ++i){
        m_Element[row][i] = value;
    }
    return *this;
}

template<typename T, int Row, int Col>
template<typename U, int Scale>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::SetRow(int row, U (&ary)[Scale]){
    assert(row < Row && row >=0);
    for(int i = 0, l = std::min(Scale, Col); i < l; ++i){
        m_Element[row][i] = ary[i];
    }
    return *this;
}

template<typename T, int Row, int Col>
template<typename U, int Scale>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::SetCol(int col, const vector<U, Scale> &rhs){
    assert(col < Col && col >=0);
    for(int i = 0, l = std::min(Scale, Row); i < l; ++i){
        m_Element[i][col] = rhs.v[i];
    }
    return *this;
}

template<typename T, int Row, int Col>
template<typename U, int Scale>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::SetCol(int col, U (&ary)[Scale]){
    assert(col < Col && col >=0);
    for(int i = 0, l = std::min(Scale, Row); i < l; ++i){
        m_Element[i][col] = ary[i];
    }
    return *this;
}

template<typename T, int Row, int Col>
template<typename U>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::SetCol(int col, const U *ptr){
   const  U *p = ptr;
    assert(col < Col && col >=0);
    for(int i = 0; i < Row; ++i){
        m_Element[i][col] = *p++;
    }
    return *this;
}

template<typename T, int Row, int Col>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::SetCol(int col, const T value){
    assert(col < Col && col >=0);
    for(int i = 0; i < Row; ++i){
        m_Element[i][col] = value;
    }
    return *this;
}

template<typename T, int Row, int Col>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::Transpose(){
    assert(Row == Col);
    for(int r = 0; r < Row; ++r){
        for(int c = 0; c < r; ++c){
            std::swap(m_Element[r][c], m_Element[c][r]);
        }
    }
    return *this;
}

template<typename T, int M, int N, typename U, int K, typename RT>
inline Matrix<RT, M, K> operator * (const Matrix<T, M, N> &lhs, const Matrix<U, N, K> &rhs){
    Matrix<RT, M, K> result;
    for(int r = 0; r < M; ++r){
        for(int c = 0; c < K; ++c){
            for(int i = 0; i < N; ++i){
                result.m_Element[r][c] += lhs.m_Element[r][i] * rhs.m_Element[i][c];
            }
        }
    }
    return result;
}

template<typename T, int M, int N, typename U, typename RT>
inline vector<RT, N> operator * (const vector<T, M> &lhs, const Matrix<U, M, N> &rhs){
    vector<RT, N> result;
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < M; ++j){
            result.v[i] += lhs.v[j] * rhs.m_Element[j][i];
        }
    }
    return result;
}

template<typename T, int M, int N, typename U, typename RT>
inline Matrix<RT, M, 1> operator * (const Matrix<U, M, N> &lhs, const vector<T, N> &rhs){
    Matrix<RT, M, 1> result;
    for(int i = 0; i < M; ++i){
        for(int j = 0; j < N; ++j){
            result.m_Element[i][0] += lhs.m_Element[i][j] * rhs.v[j];
        }
    }
    return result;
}

template<typename T, int Row, int Col>
inline T (&Matrix<T, Row, Col>::operator [] (int index))[Col]{
    assert(index >= 0 && index < Row);
    return m_Element[index];
}

template<typename T, int Row, int Col>
inline const T (&Matrix<T, Row, Col>::operator [] (int index) const)[Col]{
    assert(index >= 0 && index < Row);
    return m_Element[index];
}

template<typename T, int Row, int Col>
template<typename U>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::MultiRow(int row, const U value){
    assert(row < Row && row >= 0);
    for(int i = 0; i < Col; ++i){
        m_Element[row][i] *= value;
    }
    return *this;
}

template<typename T, int Row, int Col>
template<typename U>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::MultiCol(int col, const U value){
    assert(col < Col && col >= 0);
    for(int i = 0; i < Row; ++i){
        m_Element[i][col] *= value;
    }
    return *this;
}

template<typename T, int Row, int Col>
template<typename U>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::AddRow(int row, const U value){
    assert(row < Row && row >= 0);
    for(int i = 0; i < Col; ++i){
        m_Element[row][i] += value;
    }
    return *this;
}

template<typename T, int Row, int Col>
template<typename U>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::AddCol(int col, const U value){
    assert(col < Col && col >= 0);
    for(int i = 0; i < Row; ++i){
        m_Element[i][col] += value;
    }
    return *this;
}

template<typename T, int Row, int Col>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::AddOneRowToAnother(const int first, const int second){
    assert(first < Row && first >= 0 && second < Row && second >= 0);
    for(int i = 0; i < Col; ++i){
        m_Element[second][i] += m_Element[first][i];
    }
    return *this;
}

//row[second] += row[first] * factor;
template<typename T, int Row, int Col>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::AddOneRowToAnotherByFactor(const int first, const int second, const T factor){
    assert(first < Row && first >= 0 && second < Row && second >= 0);
    for(int i = 0; i < Col; ++i){
        m_Element[second][i] += m_Element[first][i] * factor;
    }
    return *this;
}

template<typename T, int Row, int Col>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::AddOneColToAnotherByFactor(const int first, const int second, const T factor){
    assert(first < Col && first >= 0 && second < Col && second >= 0);
    for(int i = 0; i < Row; ++i){
        m_Element[i][second] += m_Element[i][first] * factor;
    }
    return *this;
}

template<typename T, int Row, int Col>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::AddOneColToAnother(const int first, const int second){
    assert(first < Col && first >= 0 && second < Col && second >= 0);
    for(int i = 0; i < Row; ++i){
        m_Element[i][second] += m_Element[i][first];
    }
    return *this;
}


//row[second] = row[first] && clear(row[first])
template<typename T, int Row, int Col>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::MoveOnRowToAnother(const int first, const int second){
    assert(first < Row && first >= 0 && second < Row && second >= 0);
    for(int i = 0; i < Col; ++i){
        m_Element[second][i] = m_Element[first][i];
        m_Element[first][i]  = 0;
    }
    return *this;
}

//col[second] = col[first] && clear(col[first])
template<typename T, int Row, int Col>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::MoveOneColToAnother(const int first, const int second){
    assert(first < Col && first >= 0 && second < Col && second >= 0);
    for(int i = 0; i < Row; ++i){
        m_Element[i][second] = m_Element[i][first];
        m_Element[i][first]  = 0;
    }
    return *this;
}

//row[second] = row[first] but not clear(row[first])
template<typename T, int Row, int Col>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::SetOneRowWithAnother(const int first, const int second){
    assert(first < Row && first >= 0 && second < Row && second >= 0);
    for(int i = 0; i < Col; ++i){
        m_Element[second][i] = m_Element[first][i];
    }
    return *this;
}

//col[second] = col[first] but not clear(col[first])
template<typename T, int Row, int Col>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::SetOneColWithAnother(const int first, const int second){
    assert(first < Col && first >= 0 && second < Col && second >= 0);
    for(int i = 0; i < Row; ++i){
        m_Element[i][second] = m_Element[i][first];
    }
    return *this;
}

template<typename T, int Row, int Col>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::SwapRow(int first, int second){
    assert(first < Row && first >= 0 && second < Row && second >= 0);
    for(int i = 0; i < Col; ++i){
        std::swap(m_Element[second][i], m_Element[first][i]);
    }
    return *this;
}

template<typename T, int Row, int Col>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::SwapCol(int first, int second){
    assert(first < Col && first >= 0 && second < Col && second >= 0);
    for(int i = 0; i < Row; ++i){
        std::swap(m_Element[i][second], m_Element[i][first]);
    }
    return *this;
}



#ifndef DECLARE_MATRIX_TYPE_ROW
#define DECLARE_MATRIX_TYPE_ROW(type, row) \
typedef Matrix<type, row, 1> type##row##X##1;\
typedef Matrix<type, row, 2> type##row##X##2;\
typedef Matrix<type, row, 3> type##row##X##3;\
typedef Matrix<type, row, 4> type##row##X##4;\
typedef Matrix<type, row, 1> type##row##x##1;\
typedef Matrix<type, row, 2> type##row##x##2;\
typedef Matrix<type, row, 3> type##row##x##3;\
typedef Matrix<type, row, 4> type##row##x##4;
#endif

#ifndef DECLARE_MATRIX_TYPE
#define DECLARE_MATRIX_TYPE(type) \
DECLARE_MATRIX_TYPE_ROW(type, 1)\
DECLARE_MATRIX_TYPE_ROW(type, 2)\
DECLARE_MATRIX_TYPE_ROW(type, 3)\
DECLARE_MATRIX_TYPE_ROW(type, 4)
#endif


//char(byte)
DECLARE_MATRIX_TYPE(char)       //char1,
DECLARE_MATRIX_TYPE(byte);      //byte1
DECLARE_MATRIX_TYPE(sbyte);     //sbyte
DECLARE_MATRIX_TYPE(ubyte);     //ubyte
DECLARE_MATRIX_TYPE(schar);     //signed char
DECLARE_MATRIX_TYPE(uchar);     //unsigned char

//wchar_t
DECLARE_MATRIX_TYPE(wchar_t);
DECLARE_MATRIX_TYPE(swchar_t);
DECLARE_MATRIX_TYPE(uwchar_t);
DECLARE_MATRIX_TYPE(wchar);
DECLARE_MATRIX_TYPE(swchar);
DECLARE_MATRIX_TYPE(uwchar);

//short
DECLARE_MATRIX_TYPE(short);     //short
DECLARE_MATRIX_TYPE(sshort);    //signed short
DECLARE_MATRIX_TYPE(ushort);    //unsigned short

//int
DECLARE_MATRIX_TYPE(int);      //int
DECLARE_MATRIX_TYPE(sint);     //sgined int
DECLARE_MATRIX_TYPE(uint);     //unsigned int

//long
DECLARE_MATRIX_TYPE(long);     //long
DECLARE_MATRIX_TYPE(slong);    //signed long
DECLARE_MATRIX_TYPE(ulong);    //unsigned long

//long long
DECLARE_MATRIX_TYPE(llong);    //long long
DECLARE_MATRIX_TYPE(sllong);   //signed long long
DECLARE_MATRIX_TYPE(ullong);   //unsigned long long

//float
DECLARE_MATRIX_TYPE(float);    //float

//double
DECLARE_MATRIX_TYPE(double);   //double


#undef DECLARE_MATRIX_TYPE_ROW
#undef DECLARE_MATRIX_TYPE


#endif  //!__ZX_NXENGINE_MATRIX_INL__
