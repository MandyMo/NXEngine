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
inline Matrix<T, Row, Col>::Matrix(const T v){
    for(int r = 0; r < Row; ++r){
        for(int c = 0; c < Col; ++c){
            m_Element[r][c] = v;
        }
    }
}

template<typename T, int Row, int Col>
inline Matrix<T, Row, Col>::Matrix(const T *ptr){
    memcpy(m_Element, ptr, sizeof(m_Element));
}

template<typename T, int Row, int Col>
template<typename U>
inline Matrix<T, Row, Col>::Matrix(const NX::vector<U, Col> *v){
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
template<typename U, int RB, int CB>
inline Matrix<T, Row, Col>::Matrix(const U (&ary)[RB][CB]){
    memset(m_Element, 0, sizeof(m_Element));
    int rl = NXMin(Row, RB), cl = NXMin(Col, CB);
    for(int r = 0; r < rl; ++r){
        for(int c = 0; c < cl; ++c){
            m_Element[r][c] = ary[r][c];
        }
    }
}

template<typename T, int Row, int Col>
template<typename U, int RB, int CB>
inline Matrix<T, Row, Col>::Matrix(const Matrix<U, RB, CB> &rhs){
    memset(m_Element, 0, sizeof(m_Element));
    int rl = NXMin(Row, RB), cl = NXMin(Col, CB);
    for(int r = 0; r < rl; ++r){
        for(int c = 0; c < cl; ++c){
            m_Element[r][c] = rhs[r][c];
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
    NXAssert(row >= 0 && col >= 0 && row < Row && col < Col);
    return m_Element[row][col];
}

template<typename T, int Row, int Col>
inline T Matrix<T, Row, Col>::GetElement(int row, int col) const{
    NXAssert(row >= 0 && col >= 0 && row < Row && col < Col);
    return m_Element[row][col];
}

template<typename T, int Row, int Col>
template<typename U, int Scale>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::SetRow(int row, const NX::vector<U, Scale> &rhs){
    NXAssert(row < Row && row >=0);
    for(int i = 0, l = NXMin(Scale, Col); i < l; ++i){
        m_Element[row][i] = rhs.v[i];
    }
    return *this;
}

template<typename T, int Row, int Col>
template<int Scale>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::SetRow(int row, const NX::vector<T, Scale> &rhs){
    std::memcpy(&m_Element[row][0], rhs.v, NXMin(Col, Scale) * sizeof(T));
    return *this;
}

template<typename T, int Row, int Col>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::SetRow(int row, const NX::vector<T, Col> &rhs){
    std::memcpy(&m_Element[row][0], rhs.v, sizeof(T) * Col);
    return *this;
}

template<typename T, int Row, int Col>
template<typename U>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::SetRow(int row, const U *ptr){
    NXAssert(row < Row && row >=0);
    const U *p = ptr;
    for(int i = 0; i < Col; ++i){
        m_Element[row][i] = *p++;
    }
    return *this;
}

template<typename T, int Row, int Col>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::SetRow(int row, const T value){
    NXAssert(row < Row && row >=0);
    for(int i = 0; i < Col; ++i){
        m_Element[row][i] = value;
    }
    return *this;
}

template<typename T, int Row, int Col>
template<typename U, int Scale>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::SetRow(int row, U (&ary)[Scale]){
    NXAssert(row < Row && row >=0);
    for(int i = 0, l = std::min(Scale, Col); i < l; ++i){
        m_Element[row][i] = ary[i];
    }
    return *this;
}

template<typename T, int Row, int Col>
template<int Scale>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::SetRow(int row, T (&ary)[Scale]){
    NXAssert(row < Row && row >= 0);
    std::memcpy(&m_Element[row][0], &ary[0], NXMin(Col, Scale) * sizeof(T));
    return *this;
}


template<typename T, int Row, int Col>
template<typename U, int Scale>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::SetCol(int col, const NX::vector<U, Scale> &rhs){
    NXAssert(col < Col && col >=0);
    for(int i = 0, l = NXMin(Scale, Row); i < l; ++i){
        m_Element[i][col] = rhs.v[i];
    }
    return *this;
}

template<typename T, int Row, int Col>
template<typename U, int Scale>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::SetCol(int col, U (&ary)[Scale]){
    NXAssert(col < Col && col >=0);
    for(int i = 0, l = std::min(Scale, Row); i < l; ++i){
        m_Element[i][col] = ary[i];
    }
    return *this;
}

template<typename T, int Row, int Col>
template<typename U>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::SetCol(int col, const U *ptr){
   const  U *p = ptr;
    NXAssert(col < Col && col >=0);
    for(int i = 0; i < Row; ++i){
        m_Element[i][col] = *p++;
    }
    return *this;
}

template<typename T, int Row, int Col>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::SetCol(int col, const T value){
    NXAssert(col < Col && col >=0);
    for(int i = 0; i < Row; ++i){
        m_Element[i][col] = value;
    }
    return *this;
}

template<typename T, int Row, int Col>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::Transpose(){
    NXAssert(Row == Col);
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

template<typename T, typename U>
inline NX::vector<U, 3> operator * (const NX::Matrix<T, 4, 4> &lhs, const NX::vector<U, 3> &rhs) {
	NX::vector<U, 3>result;
	for (int r = 0; r < 3; ++r) {
		for (int c = 0; c < 3; ++c) {
			result[r] += lhs[r][c] * rhs[c];
		}
		result[r] += lhs[r][3];
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
inline Matrix<RT, M, 1> operator * (const Matrix<U, M, N> &lhs, const NX::vector<T, N> &rhs){
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
    NXAssert(index >= 0 && index < Row);
    return m_Element[index];
}

template<typename T, int Row, int Col>
inline const T (&Matrix<T, Row, Col>::operator [] (int index) const)[Col]{
    NXAssert(index >= 0 && index < Row);
    return m_Element[index];
}

template<typename T, int Row, int Col>
template<typename U>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::MultiRow(int row, const U value){
    NXAssert(row < Row && row >= 0);
    for(int i = 0; i < Col; ++i){
        m_Element[row][i] *= value;
    }
    return *this;
}

template<typename T, int Row, int Col>
template<typename U>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::MultiCol(int col, const U value){
    NXAssert(col < Col && col >= 0);
    for(int i = 0; i < Row; ++i){
        m_Element[i][col] *= value;
    }
    return *this;
}

template<typename T, int Row, int Col>
template<typename U>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::AddRow(int row, const U value){
    NXAssert(row < Row && row >= 0);
    for(int i = 0; i < Col; ++i){
        m_Element[row][i] += value;
    }
    return *this;
}

template<typename T, int Row, int Col>
template<typename U>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::AddCol(int col, const U value){
    NXAssert(col < Col && col >= 0);
    for(int i = 0; i < Row; ++i){
        m_Element[i][col] += value;
    }
    return *this;
}

template<typename T, int Row, int Col>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::AddOneRowToAnother(const int first, const int second){
    NXAssert(first < Row && first >= 0 && second < Row && second >= 0);
    for(int i = 0; i < Col; ++i){
        m_Element[second][i] += m_Element[first][i];
    }
    return *this;
}

//row[second] += row[first] * factor;
template<typename T, int Row, int Col>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::AddOneRowToAnotherByFactor(const int first, const int second, const T factor){
    NXAssert(first < Row && first >= 0 && second < Row && second >= 0);
    for(int i = 0; i < Col; ++i){
        m_Element[second][i] += m_Element[first][i] * factor;
    }
    return *this;
}

template<typename T, int Row, int Col>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::AddOneColToAnotherByFactor(const int first, const int second, const T factor){
    NXAssert(first < Col && first >= 0 && second < Col && second >= 0);
    for(int i = 0; i < Row; ++i){
        m_Element[i][second] += m_Element[i][first] * factor;
    }
    return *this;
}

template<typename T, int Row, int Col>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::AddOneColToAnother(const int first, const int second){
    NXAssert(first < Col && first >= 0 && second < Col && second >= 0);
    for(int i = 0; i < Row; ++i){
        m_Element[i][second] += m_Element[i][first];
    }
    return *this;
}


//row[second] = row[first] && clear(row[first])
template<typename T, int Row, int Col>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::MoveOnRowToAnother(const int first, const int second){
    NXAssert(first < Row && first >= 0 && second < Row && second >= 0);
    for(int i = 0; i < Col; ++i){
        m_Element[second][i] = m_Element[first][i];
        m_Element[first][i]  = 0;
    }
    return *this;
}

//col[second] = col[first] && clear(col[first])
template<typename T, int Row, int Col>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::MoveOneColToAnother(const int first, const int second){
    NXAssert(first < Col && first >= 0 && second < Col && second >= 0);
    for(int i = 0; i < Row; ++i){
        m_Element[i][second] = m_Element[i][first];
        m_Element[i][first]  = 0;
    }
    return *this;
}

//row[second] = row[first] but not clear(row[first])
template<typename T, int Row, int Col>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::SetOneRowWithAnother(const int first, const int second){
    NXAssert(first < Row && first >= 0 && second < Row && second >= 0);
    for(int i = 0; i < Col; ++i){
        m_Element[second][i] = m_Element[first][i];
    }
    return *this;
}

//col[second] = col[first] but not clear(col[first])
template<typename T, int Row, int Col>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::SetOneColWithAnother(const int first, const int second){
    NXAssert(first < Col && first >= 0 && second < Col && second >= 0);
    for(int i = 0; i < Row; ++i){
        m_Element[i][second] = m_Element[i][first];
    }
    return *this;
}

template<typename T, int Row, int Col>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::SwapRow(int first, int second){
    NXAssert(first < Row && first >= 0 && second < Row && second >= 0);
    for(int i = 0; i < Col; ++i){
        std::swap(m_Element[second][i], m_Element[first][i]);
    }
    return *this;
}

template<typename T, int Row, int Col>
inline Matrix<T, Row, Col>& Matrix<T, Row, Col>::SwapCol(int first, int second){
    NXAssert(first < Col && first >= 0 && second < Col && second >= 0);
    for(int i = 0; i < Row; ++i){
        std::swap(m_Element[i][second], m_Element[i][first]);
    }
    return *this;
}


template<typename T, int Row, int Col, typename U, typename RT>
inline NX::Matrix<RT, Row, Col> operator + (const NX::Matrix<T, Row, Col> &lhs, const NX::Matrix<U, Row, Col> &rhs){
    return Matrix<RT, Row, Col>(lhs) += rhs;
}

template<typename T, int Row, int Col, typename U, typename RT>
inline NX::Matrix<RT, Row, Col> operator - (const NX::Matrix<T, Row, Col> &lhs, const NX::Matrix<U, Row, Col> &rhs){
    return Matrix<RT, Row, Col>(lhs) -= rhs;
}

template<typename T, int Row, int Col>
inline bool operator == (const NX::Matrix<T, Row, Col> &lhs, const NX::Matrix<T, Row, Col> &rhs) {
	for (int r = 0; r < Row; ++r) {
		for (int c = 0; c < Col; ++c) {
			if (NX::EqualfloatWithDelta(lhs[r][c], rhs[r][c], .001f)) {
				return false;
			}
		}
	}

	return true;
}

template<typename T, int Row, int Col>
inline bool operator != (const NX::Matrix<T, Row, Col> &lhs, const NX::Matrix<T, Row, Col> &rhs) {
	return !(lhs == rhs);
}

template<typename T, int Row, int Col>
inline NX::vector<T, Col> Matrix<T, Row, Col>::GetRow(int row){
    NXAssert(row >= 0 && row < Row);
    return vector<T, Col>(m_Element[row]);
}

template<typename T, int Row, int Col>
inline NX::vector<T, Row> Matrix<T, Row, Col>::GetCol(int col){
    NXAssert(col >= 0 && col < Col);
    vector<T, Row> result;
    for(int i = 0; i < Row; ++i){
        result[i] = m_Element[i][col];
    }
    return result;
}


#ifndef DECLARE_MATRIX_TYPE_ROW
#define DECLARE_MATRIX_TYPE_ROW(type, row) \
typedef NX::Matrix<type, row, 1> type##row##X##1;\
typedef NX::Matrix<type, row, 2> type##row##X##2;\
typedef NX::Matrix<type, row, 3> type##row##X##3;\
typedef NX::Matrix<type, row, 4> type##row##X##4;\
typedef NX::Matrix<type, row, 1> type##row##x##1;\
typedef NX::Matrix<type, row, 2> type##row##x##2;\
typedef NX::Matrix<type, row, 3> type##row##x##3;\
typedef NX::Matrix<type, row, 4> type##row##x##4;
#endif

#ifndef DECLARE_MATRIX_TYPE
#define DECLARE_MATRIX_TYPE(type) \
DECLARE_MATRIX_TYPE_ROW(type, 1)\
DECLARE_MATRIX_TYPE_ROW(type, 2)\
DECLARE_MATRIX_TYPE_ROW(type, 3)\
DECLARE_MATRIX_TYPE_ROW(type, 4)
#endif

DECLARE_MATRIX_TYPE(NXInt8)
DECLARE_MATRIX_TYPE(NXUInt8)
DECLARE_MATRIX_TYPE(NXInt16)
DECLARE_MATRIX_TYPE(NXUInt16)
DECLARE_MATRIX_TYPE(NXInt32)
DECLARE_MATRIX_TYPE(NXUInt32)
DECLARE_MATRIX_TYPE(NXInt64)
DECLARE_MATRIX_TYPE(NXUInt64)


//float
DECLARE_MATRIX_TYPE(float);    //float

//double
DECLARE_MATRIX_TYPE(double);   //double


#undef DECLARE_MATRIX_TYPE_ROW
#undef DECLARE_MATRIX_TYPE


#endif  //!__ZX_NXENGINE_MATRIX_INL__
