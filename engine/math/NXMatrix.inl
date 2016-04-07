template<typename T, int Row, int Col>
template<typename U>
Matrix<T, Row, Col>::Matrix(const Matrix<U, Row, Col> &rhs){
    for(int r = 0; r < Row; ++r){
        for(int c = 0; c < Col; ++c){
            m_Element[r][c] = rhs.m_Element[r][c];
        }
    }
}

template<typename T, int Row, int Col>
Matrix<T, Row, Col>::Matrix(const Matrix &rhs){
    std::memcpy(m_Element, rhs.m_Element, sizeof(m_Element));
}

template<typename T, int Row, int Col>
Matrix<T, Row, Col>::Matrix(){
    std::memset(m_Element, 0, sizeof(m_Element));
}

template<typename T, int Row, int Col>
Matrix<T, Row, Col>::Matrix(const T *ptr){
    memcpy(m_Element, ptr, sizeof(m_Element));
}

template<typename T, int Row, int Col>
template<typename U>
Matrix<T, Row, Col>::Matrix(const vector<U, Col> *v){
    for(int r = 0; r < Row; ++r){
        for(int c = 0; c < Col; ++c){
            m_Element[r][c] = v[r][c];
        }
    }
}

template<typename T, int Row, int Col>
template<typename U>
Matrix<T, Row, Col>::Matrix(const U (&ary)[Row][Col]){
    for(int r = 0; r < Row; ++r){
        for(int c = 0; c < Col; ++c){
            m_Element[r][c] = ary[r][c];
        }
    }
}

template<typename T, int Row, int Col>
template<typename U>
Matrix<T, Row, Col>& Matrix<T, Row, Col>::operator += (const Matrix<U, Row, Col> &rhs){
    for(int r = 0; r < Row; ++r){
        for(int c = 0; c < Col; ++c){
            m_Element[r][c] += rhs.m_Element[r][c];
        }
    }
    return *this;
}

template<typename T, int Row, int Col>
template<typename U>
Matrix<T, Row, Col>& Matrix<T, Row, Col>::operator -= (const Matrix<U, Row, Col> &rhs){
    for(int r = 0; r < Row; ++r){
        for(int c = 0; c < Col; ++c){
            m_Element[r][c] -= rhs.m_Element[r][c];
        }
    }
    return *this;
}

template<typename T, int Row, int Col>
Matrix<T, Row, Col>& Matrix<T, Row, Col>::operator += (const T &value){
    for(int r = 0; r < Row; ++r){
        for(int c = 0; c < Col; ++c){
            m_Element[r][c] += value;
        }
    }
    return *this;
}

template<typename T, int Row, int Col>
Matrix<T, Row, Col>& Matrix<T, Row, Col>::operator -= (const T &value){
    for(int r = 0; r < Row; ++r){
        for(int c = 0; c < Col; ++c){
            m_Element[r][c] -= value;
        }
    }
    return *this;
}

template<typename T, int Row, int Col>
Matrix<T, Row, Col>& Matrix<T, Row, Col>::operator *= (const T &value){
    for(int r = 0; r < Row; ++r){
        for(int c = 0; c < Col; ++c){
            m_Element[r][c] *= value;
        }
    }
    return *this;
}

template<typename T, int Row, int Col>
Matrix<T, Row, Col>& Matrix<T, Row, Col>::operator /= (const T &value){
    for(int r = 0; r < Row; ++r){
        for(int c = 0; c < Col; ++c){
            m_Element[r][c] /= value;
        }
    }
    return *this;
}

template<typename T, int Row, int Col>
T& Matrix<T, Row, Col>::GetElement(int row, int col){
    assert(row >= 0 && col >= 0 && row < Row && col < Col);
    return m_Element[row][col];
}

template<typename T, int Row, int Col>
template<typename U, int Scale>
void Matrix<T, Row, Col>::SetRow(int row, const vector<U, Scale> &rhs){
    assert(row < Row && row >=0);
    for(int i = 0, l = std::min(Scale, Col); i < l; ++i){
        m_Element[row][i] = rhs.v[i];
    }
}

template<typename T, int Row, int Col>
template<typename U, int Scale>
void Matrix<T, Row, Col>::SetCol(int col, const vector<U, Scale> &rhs){
    assert(col < Col && col >=0);
    for(int i = 0, l = std::min(Scale, Row); i < l; ++i){
        m_Element[i][col] = rhs.v[i];
    }
}

template<typename T, int M, int N, typename U, int K, typename RT = T>
Matrix<RT, M, K> operator * (const Matrix<T, M, N> &lhs, const Matrix<U, N, K> &rhs){
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

template<typename T, int M, int N, typename U, typename RT = T>
vector<RT, N> operator * (const vector<T, M> &lhs, const Matrix<U, M, N> &rhs){
    vector<RT, N> result;
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < M; ++j){
            result.v[i] += lhs.v[j] * rhs.m_Element[j][i];
        }
    }
    return result;
}

template<typename T, int M, int N, typename U, typename RT = T>
Matrix<RT, M, 1> operator * (const Matrix<U, M, N> &lhs, const vector<T, N> &rhs){
    Matrix<RT, M, 1> result;
    for(int i = 0; i < M; ++i){
        for(int j = 0; j < N; ++j){
            result.m_Element[i][0] += lhs.m_Element[i][j] * rhs.v[j];
        }
    }
    return result;
}

template<typename T, int M>
void Transpose(Matrix<T, M, M> &lhs){
    for(int r = 0; r < M; ++r){
        for(int c = 0; c < r; ++c){
            std::swap(lhs.m_Element[r][c], lhs.m_Element[c][r]);
        }
    }
}

template<typename T, int Row, int Col>
T (&Matrix<T, Row, Col>::operator [] (int index))[Col]{
    assert(index >= 0 && index < Row);
    return m_Element[index];
}

template<typename U, typename T = float>
Matrix<T, 4, 4> LookAt(const vector<U, 3> &eye, const vector<U, 3> &look, const vector<U, 3> &up){
    vector<T, 3> oz = look - eye;
    Normalize(oz);
    vector<T, 3> ox = Cross(up, oz);
    Normalize(ox);
    vector<T, 3> oy = Cross(oz, ox);
    Normalize(oy);
    vector<T, 3> oo = eye;
    
    Matrix<T, 4, 4> result;
    result.SetRow(0, ox);
    result.SetRow(1, oy);
    result.SetRow(2, oz);
    result[0][3] = -Dot(oo, ox);
    result[1][3] = -Dot(oo, oy);
    result[2][3] = -Dot(oo, oz);
    result[3][3] = T(1);
    return result;
}

template<typename T>
Matrix<T, 4, 4> Translate(const T dx, const T dy, const T dz){
    Matrix<T, 4, 4> result;
    result[0][0] = result[1][1] = result[2][2] = result[3][3] = T(1);
    result[0][3] = dx;
    result[1][3] = dy;
    result[2][3] = dz;
    return result;
}

template<typename T, int Scale = 4>
Matrix<T, Scale, Scale> RotateX(const T radius){
    assert(Scale == 3 || Scale == 4);
    Matrix<T, Scale, Scale> result;
    T CosValue(std::cos(radius));
    T SinValue(std::sin(radius));
    result.m_Element[Scale - 1][Scale - 1] = T(1);
    result.m_Element[0][0] = T(1);
    result.m_Element[1][1] = CosValue, result.m_Element[1][2] = -SinValue;
    result.m_Element[2][1] = SinValue, result.m_Element[2][2] = CosValue;
    return result;
}

template<typename T, int Scale = 4>
Matrix<T, Scale, Scale> RotateY(const T radius){
    assert(Scale == 3 || Scale == 4);
    Matrix<T, Scale, Scale> result;
    T CosValue(std::cos(radius));
    T SinValue(std::sin(radius));
    result.m_Element[Scale - 1][Scale - 1] = T(1), result.m_Element[1][1] = T(1);
    result.m_Element[0][0] = CosValue, result.m_Element[0][2] = SinValue;
    result.m_Element[2][0] = -SinValue, result.m_Element[2][2] = CosValue;
    return result;
}

template<typename T, int Scale = 4>
Matrix<T, Scale, Scale> RotateZ(const T radius){
    assert(Scale == 3 || Scale == 4);
    Matrix<T, Scale, Scale> result;
    T CosValue(std::cos(radius));
    T SinValue(std::sin(radius));
    result.m_Element[Scale - 1][Scale - 1] = T(1), result.m_Element[2][2] = T(1);
    result.m_Element[0][0] = CosValue, result.m_Element[0][1] = SinValue;
    result.m_Element[1][0] = -SinValue, result.m_Element[1][1] = CosValue;
    return result;
}

template<typename T, int Scale = 4>
Matrix<T, Scale, Scale> Scalar(const T sx, const T sy, const T sz){
    Matrix<T, Scale, Scale> result;
    result.m_Element[Scale - 1][Scale - 1] = T(1);
    result.m_Element[0][0] = sx;
    result.m_Element[1][1] = sy;
    result.m_Element[2][2] = sz;
    return result;
}

template<typename T, int Scale = 4, typename U>
Matrix<T, Scale, Scale> RotateAix(const vector<U, 3> &Aix, const T radius){
    vector<T, 3> ax(Aix);
    Normalize(ax);
    T nxx = ax.x * ax.x;
    T nyy = ax.y * ax.y;
    T nzz = ax.z * ax.z;
    T nxy = ax.x * ax.y;
    T nyz = ax.y * ax.z;
    T nzx = ax.z * ax.x;
    T CosValue  = std::cos(radius);
    T SinValue  = std::sin(radius);
    T OneMinCos = T(1) - CosValue;
    Matrix<T, Scale, Scale> result;
    result.m_Element[Scale -1 ][Scale - 1] = T(1);
    result.m_Element[0][0] = nxx * OneMinCos + CosValue;
    result.m_Element[1][0] = nxy * OneMinCos + ax.z * SinValue;
    result.m_Element[2][0] = nzx * OneMinCos - ax.y * SinValue;
    result.m_Element[0][1] = nxy * OneMinCos - ax.z * SinValue;
    result.m_Element[1][1] = nyy * OneMinCos + CosValue;
    result.m_Element[2][1] = nyz * OneMinCos + ax.x * SinValue;
    result.m_Element[0][2] = nzx * OneMinCos + ax.y * SinValue;
    result.m_Element[1][2] = nyz * OneMinCos - ax.x * SinValue;
    result.m_Element[2][2] = nzz * OneMinCos + CosValue;
    return result;
}

//x/w: [-1, 1]
//y/w: [-1, 1]
//z/w: [0, 1]
//w: z
template<typename T, int Scale = 4>
Matrix<T, Scale, Scale> Perspective(const T FovAngle, const T aspect, const T near, const T far){
    assert(Scale == 4);
    Matrix<T, Scale, Scale> result;
    T CotValue = 1 / std::tan(DG2RD(FovAngle) / 2);
    T dif = near - far;
    T a = -far / dif;
    T b = near * far / dif;
    result.m_Element[0][0] = 1 / aspect * CotValue;
    result.m_Element[1][1] = CotValue;
    result.m_Element[2][2] = a;
    result.m_Element[2][3] = b;
    result.m_Element[3][2] = T(1);
    return result;
}

//x: [-1, 1]
//y: [-1, 1]
//z: [0, 1]
//w: 1
template<typename T, int Scale = 4>
Matrix<T, Scale, Scale> Orthogonal(const T Width, const T Height, const T near, const T far){
    assert(Scale == 4);
    Matrix<T, Scale, Scale> result;
    result.m_Element[Scale - 1][Scale - 1] = T(1);
    result.m_Element[0][0] = 2 / Width;
    result.m_Element[1][1] = 2 / Height;
    const T dif = far - near;
    const T a   = 1 / dif;
    const T b   = -near / dif;
    result.m_Element[2][2] = a;
    result.m_Element[2][3] = b;
    return result;
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
