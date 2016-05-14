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
inline Matrix<T, Row, Col> Transpose(const Matrix<T, Col, Row> &lhs){
    Matrix<T, Row, Col> result;
    for(int i = 0; i < Col; ++i){
        result.template SetCol<T, Row>(i, lhs[i]);
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

template<typename U, typename T>
inline Matrix<T, 4, 4> LookAt(const vector<U, 3> &eye, const vector<U, 3> &look, const vector<U, 3> &up){
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
inline Matrix<T, 4, 4> Translate(const T dx, const T dy, const T dz){
    Matrix<T, 4, 4> result;
    result[0][0] = result[1][1] = result[2][2] = result[3][3] = T(1);
    result[0][3] = dx;
    result[1][3] = dy;
    result[2][3] = dz;
    return result;
}

template<typename T, int Scale>
inline Matrix<T, Scale, Scale> RotateX(const T radian){
    assert(Scale == 3 || Scale == 4);
    Matrix<T, Scale, Scale> result;
    T CosValue(std::cos(radian));
    T SinValue(std::sin(radian));
    result.m_Element[Scale - 1][Scale - 1] = T(1);
    result.m_Element[0][0] = T(1);
    result.m_Element[1][1] = CosValue, result.m_Element[1][2] = -SinValue;
    result.m_Element[2][1] = SinValue, result.m_Element[2][2] = CosValue;
    return result;
}

template<typename T, int Scale>
inline Matrix<T, Scale, Scale> RotateY(const T radian){
    assert(Scale == 3 || Scale == 4);
    Matrix<T, Scale, Scale> result;
    T CosValue(std::cos(radian));
    T SinValue(std::sin(radian));
    result.m_Element[Scale - 1][Scale - 1] = T(1), result.m_Element[1][1] = T(1);
    result.m_Element[0][0] = CosValue, result.m_Element[0][2]  = SinValue;
    result.m_Element[2][0] = -SinValue, result.m_Element[2][2] = CosValue;
    return result;
}

template<typename T, int Scale>
inline Matrix<T, Scale, Scale> RotateZ(const T radian){
    assert(Scale == 3 || Scale == 4);
    Matrix<T, Scale, Scale> result;
    T CosValue(std::cos(radian));
    T SinValue(std::sin(radian));
    result.m_Element[Scale - 1][Scale - 1] = T(1), result.m_Element[2][2] = T(1);
    result.m_Element[0][0] = CosValue, result.m_Element[0][1] = -SinValue;
    result.m_Element[1][0] = SinValue, result.m_Element[1][1] = CosValue;
    return result;
}

template<typename T, int Scale>
inline Matrix<T, Scale, Scale> Scalar(const T sx, const T sy, const T sz){
    Matrix<T, Scale, Scale> result;
    result.m_Element[Scale - 1][Scale - 1] = T(1);
    result.m_Element[0][0] = sx;
    result.m_Element[1][1] = sy;
    result.m_Element[2][2] = sz;
    return result;
}

template<typename T, int Scale, typename U>
inline Matrix<T, Scale, Scale> RotateAix(const vector<U, 3> &Aix, const T radian){
    vector<T, 3> ax(Aix);
    Normalize(ax);
    T nxx = ax.x * ax.x;
    T nyy = ax.y * ax.y;
    T nzz = ax.z * ax.z;
    T nxy = ax.x * ax.y;
    T nyz = ax.y * ax.z;
    T nzx = ax.z * ax.x;
    T CosValue  = std::cos(radian);
    T SinValue  = std::sin(radian);
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
template<typename T, int Scale>
inline Matrix<T, Scale, Scale> Perspective(const T FovAngle, const T aspect, const T near, const T far){
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
template<typename T, int Scale>
inline Matrix<T, Scale, Scale> Orthogonal(const T Width, const T Height, const T near, const T far){
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

template<typename T, typename RT>
inline RT Detaminate(const Matrix<T, 2, 2>& matrix){
    RT result(matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
    return result;
}

template<typename T, typename RT>
inline RT Detaminate(const Matrix<T, 3, 3>& matrix){
    NX::vector<T, 3> a(matrix[0][0], matrix[0][1], matrix[0][2]);
    NX::vector<T, 3> b(matrix[1][0], matrix[1][1], matrix[1][2]);
    NX::vector<T, 3> c(matrix[2][0], matrix[2][1], matrix[2][2]);
    return RT(Dot(c, Cross(a, b)));
}

template<typename T, int Scale, typename RT>
inline RT Detaminate(const Matrix<T, Scale, Scale> &matrix){
    Matrix<RT, Scale, Scale> M(matrix);
    unsigned int iSwapCount = 0;
    {//gauss - jordan method
        int iSelRow = 0;
        for(int c = 0; c < Scale; ++c){
            iSelRow = c;
            for(int i = c + 1; i < Scale; ++i){//select pivot row for numeric stability
                if(NX::NXAbs(M[iSelRow][c]) < NX::NXAbs(M[i][c])){
                    iSelRow = i;
                }
            }
            if(iSelRow != c){
                M.SwapRow(iSelRow, c);
                ++iSwapCount;
            }
            if(NXAbs(M[c][c]) < Epsilon<RT>::m_Epsilon){
                return RT(0);
            }
            for(int i = c+ 1; i < Scale; ++i){
                M.AddOneRowToAnotherByFactor(c, i, -M[i][c] / M[c][c]);
            }
        }
    }
    RT result(1);
    for(int i = 0; i < Scale; ++i){
        result *= M[i][i];
    }
    return iSwapCount & 1 ? -result : result;
}

template<typename T, typename RT>
inline RT Detaminate(const Matrix<T, 4, 4> &matrix){
    RT result(0);
    {//M{0, 0}
        Matrix<T, 3, 3> m;
        m.SetRow(0, &matrix[1][1]);
        m.SetRow(1, &matrix[2][1]);
        m.SetRow(2, &matrix[3][1]);
        result += matrix[0][0] * Detaminate(m);
    }
    
    {//M{1, 0}
        Matrix<T, 3, 3> m;
        m.SetRow(0, &matrix[0][1]);
        m.SetRow(1, &matrix[2][1]);
        m.SetRow(2, &matrix[3][1]);
        result -= matrix[1][0] * Detaminate(m);
    }
    
    {//M{2, 0}
        Matrix<T, 3, 3> m;
        m.SetRow(0, &matrix[0][1]);
        m.SetRow(1, &matrix[1][1]);
        m.SetRow(2, &matrix[3][1]);
        result += matrix[2][0] * Detaminate(m);
    }
    
    {//M{3, 0}
        Matrix<T, 3, 3> m;
        m.SetRow(0, &matrix[0][1]);
        m.SetRow(1, &matrix[1][1]);
        m.SetRow(2, &matrix[2][1]);
        result -= matrix[3][0] * Detaminate(m);
    }
    return result;
}

template<typename T, typename RT>
inline Matrix<RT, 2, 2> Reverse(const Matrix<T, 2, 2>& matrix){
    Matrix<RT, 2, 2> result = matrix;
    RT det = Detaminate<T, RT>(matrix);
    result[0][1] = - result[0][1];
    result[1][0] = - result[1][0];
    result /= det;
    return result;
}

template<typename T, typename RT>
inline Matrix<RT, 3, 3> Reverse(const Matrix<T, 3, 3>& matrix){
    Matrix<RT, 3, 3> result;
    RT det = Detaminate(matrix);
    if(NX::NXAbs(det) < Epsilon<T>::m_Epsilon){//to small
        return result;
    }
    
    {//first row
        result[0][0] = matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1];
        result[0][1] = matrix[1][2] * matrix[2][0] - matrix[1][0] * matrix[2][2];
        result[0][2] = matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0];
    }
    
    {//second row
        result[1][0] = matrix[0][2] * matrix[2][1] - matrix[0][1] * matrix[2][2];
        result[1][1] = matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0];
        result[1][2] = matrix[0][1] * matrix[2][0] - matrix[0][0] * matrix[2][1];
    }
    
    {//third row
        result[2][0] = matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1];
        result[2][1] = matrix[0][2] * matrix[1][0] - matrix[0][0] * matrix[1][2];
        result[2][2] = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }
    result /= det;
    Transpose(result);
    return result;
}


template<typename T, typename RT>
inline Matrix<RT, 4, 4> Reverse(const Matrix<T, 4, 4> &matrix){
    Matrix<RT, 4, 8> m;
    {//init m = {matrix, I};
        m[0][4] = 1, m[1][5] = 1, m[2][6] = 1, m[3][7] = 1;
        m.template SetRow<T, 4>(0, matrix[0]);
        m.template SetRow<T, 4>(1, matrix[1]);
        m.template SetRow<T, 4>(2, matrix[2]);
        m.template SetRow<T, 4>(3, matrix[3]);
    }
    
    if(NX::NXAbs(Detaminate(matrix)) < Epsilon<T>::m_Epsilon){
        return matrix;
    }
    
    {//gauss - jordan method
        int iSelRow = 0;
        for(int c = 0; c < 4; ++c){
            iSelRow = c;
            for(int i = c + 1; i < 4; ++i){//select pivot row
                if(NX::NXAbs(m[iSelRow][c]) < NX::NXAbs(m[i][c])){
                    iSelRow = i;
                }
            }
            if(iSelRow != c){
                m.SwapRow(iSelRow, c);
            }
            for(int i = 0; i < 4; ++i){
                if(i == c){
                    continue;
                }
                m.AddOneRowToAnotherByFactor(c, i, -m[i][c] / m[c][c]);
            }
            m.MultiRow(c, 1 / m[c][c]);
        }
    }
    
    Matrix<RT, 4, 4> result;
    {//copy back
        result.SetRow(0, &m[0][4]);
        result.SetRow(1, &m[1][4]);
        result.SetRow(2, &m[2][4]);
        result.SetRow(3, &m[3][4]);
    }
    return result;
}

template<typename T, int Scale, typename RT>
inline Matrix<RT, Scale, Scale> Reverse(const Matrix<T, Scale, Scale> &matrix){
    Matrix<RT, Scale, (Scale << 1)> M;
    for(int i = 0; i < Scale; ++i){
        M.template SetRow<T, Scale>(i, matrix[i]);
        M[i][i + Scale] = 1;
    }
    {//gauss - jordan method
        int iSelRow = 0;
        for(int c = 0; c < Scale; ++c){
            iSelRow = c;
            for(int i = c + 1; i < Scale; ++i){//select pivot row
                if(NX::NXAbs(M[iSelRow][c]) < NX::NXAbs(M[i][c])){
                    iSelRow = i;
                }
            }
            if(iSelRow != c){
                M.SwapRow(iSelRow, c);
            }
            for(int i = 0; i < Scale; ++i){
                if(i == c){
                    continue;
                }
                M.AddOneRowToAnotherByFactor(c, i, -M[i][c] / M[c][c]);
            }
            M.MultiRow(c, 1 / M[c][c]);
        }
    }
    
    Matrix<RT, Scale, Scale> result;
    {//copy back
        for(int i = 0; i < Scale; ++i){
            result.SetRow(i, &M[i][Scale]);
        }
    }
    return result;
}

template<typename T, int Scale, typename RT>
inline std::pair<bool, Matrix<RT, Scale, Scale> > ReverseSafe(const Matrix<T, Scale, Scale> &matrix){
    Matrix<RT, Scale, (Scale << 1)> M;
    for(int i = 0; i < Scale; ++i){
        M.template SetRow<T, Scale>(i, matrix[i]);
        M[i][i + Scale] = 1;
    }
    {//gauss - jordan method
        int iSelRow = 0;
        for(int c = 0; c < Scale; ++c){
            iSelRow = c;
            for(int i = c + 1; i < Scale; ++i){//select pivot row
                if(NX::NXAbs(M[iSelRow][c]) < NX::NXAbs(M[i][c])){
                    iSelRow = i;
                }
            }
            if(iSelRow != c){
                M.SwapRow(iSelRow, c);
            }
            if(NXAbs(M[c][c]) < Epsilon<RT>::m_Epsilon){
                return std::make_pair(true, Matrix<RT, Scale, Scale>());
            }
            for(int i = 0; i < Scale; ++i){
                if(i == c){
                    continue;
                }
                M.AddOneRowToAnotherByFactor(c, i, -M[i][c] / M[c][c]);
            }
            M.MultiRow(c, 1 / M[c][c]);
        }
    }
    
    std::pair<bool, Matrix<RT, Scale, Scale> >result;
    {//copy back
        result.first = true;
        for(int i = 0; i < Scale; ++i){
            result.second.SetRow(i, &M[i][Scale]);
        }
    }
    return result;
}

/**
 *  zero some small elements such as 0.0000001
 */
template<typename T, int iScale>
inline Matrix<T, iScale, iScale>& SimplifyMatrix(Matrix<T, iScale, iScale> &matrix, const T EpsilonValue){
    for(int r = 0; r < iScale; ++r){
        for(int c = 0; c < iScale; ++c){
            if(NXAbs(matrix[r][c] < EpsilonValue)){
                matrix[r][c] = T(0);
            }
        }
    }
    return matrix;
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
