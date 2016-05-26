/*
 *  File:    NXVector.inl
 *  author:  张雄
 *  date:    2016_02_22
 *  purpose: 实现3d数学的vector，注意，此vector只适合于存储简单的内置基本类型，若存放class和struct类型，请不要使用。
 */

#ifndef __ZX_NXENGINE_VECTOR_INL__
#define __ZX_NXENGINE_VECTOR_INL__

template<typename T, int Scale>
inline bool operator == (const vector<T, Scale> &lhs, const vector<T, Scale> &rhs){
    for(int i = 0; i < Scale; ++i){
        if(lhs.v[i] != rhs.v[i]){
            return false;
        }
    }
    return true;
}

template<typename T, typename U, int Scale, typename RT>
inline vector<RT, Scale> operator + (const vector<T, Scale> &lhs, const vector<U, Scale> &rhs){
    return (vector<RT, Scale>(lhs) += rhs);
}

template<typename T, typename U, int Scale, typename RT>
inline vector<RT, Scale> operator + (const vector<T, Scale> &lhs, const U value){
    return (vector<RT, Scale>(lhs) += value);
}

template<typename T, typename U, int Scale, typename RT>
inline vector<RT, Scale> operator + (const U value, const vector<T, Scale> &rhs){
    return (vector<RT, Scale>(rhs) += value);
}

template<typename T, typename U, int Scale, typename RT>
inline vector<RT, Scale> operator - (const vector<T, Scale> &lhs, const U value){
    return (vector<RT, Scale>(lhs) -= value);
}

template<typename T, typename U, int Scale, typename RT>
inline vector<RT, Scale> operator - (const U value, const vector<T, Scale> &rhs){
    return (vector<RT, Scale>(value) -= rhs);
}

template<typename T, typename U, int Scale, typename RT>
inline vector<RT, Scale> operator - (const vector<T, Scale> &lhs, const vector<U, Scale> &rhs){
    return (vector<RT, Scale>(lhs) -= rhs);
}

template<typename T, typename U, int Scale, typename RT>
inline vector<RT, Scale> operator * (const vector<T, Scale> &lhs, const vector<U, Scale> &rhs){
    return (vector<RT, Scale>(lhs) *= rhs);
}

template<typename T, typename U, int Scale, typename RT>
inline vector<RT, Scale> operator * (const vector<T, Scale> &lhs, const U value){
    return (vector<RT, Scale>(lhs) *= value);
}

template<typename T, typename U, int Scale, typename RT>
inline vector<RT, Scale> operator * (const U value, const vector<T, Scale> &lhs){
    return (vector<RT, Scale>(lhs) *= value);
}

template<typename T, typename U, int Scale, typename RT>
inline vector<RT, Scale> operator / (const vector<T, Scale> &lhs, const vector<U, Scale> &rhs){
    return (vector<RT, Scale>(lhs) /= rhs);
}

template<typename T, typename U, int Scale, typename RT>
inline vector<RT, Scale> operator / (const vector<T, Scale> &lhs, const U value){
    return (vector<RT, Scale>(lhs) /= value);
}

template<typename T, typename U, int Scale, typename RT>
inline vector<RT, Scale> operator / (const U value, const vector<T, Scale> &lhs){
    return (vector<RT, Scale>(value) -= lhs);
}

template<typename T, int Scale>
inline bool operator != (const vector<T, Scale> &lhs, const vector<T, Scale> &rhs){
    return !(lhs == rhs);
}

template<typename T, typename U, int Scale, typename RT>
inline RT Dot (const vector<T, Scale> &lhs, const vector<U, Scale> &rhs){
    RT sum = 0;
    for(int i = 0; i < Scale; ++i){
        sum += lhs.v[i] * rhs.v[i];
    }
    return sum;
}

template<typename T, typename U, typename RT>
inline vector<RT, 3> Cross(const vector<T, 3> &lhs, const vector<U, 3> &rhs){
    return vector<RT, 3>(lhs.v[1] * rhs.v[2] - lhs.v[2] * rhs.v[1],
                         lhs.v[2] * rhs.v[0] - lhs.v[0] * rhs.v[2],
                         lhs.v[0] * rhs.v[1] - rhs.v[0] * lhs.v[1]);
}


template<typename T, int Scale, typename RT>
inline RT Length(const vector<T, Scale> &lhs){
    return std::sqrt(LengthSquare(lhs));
}

template<typename T, int Scale, typename RT>
inline RT LengthSquare(const vector<T, Scale> &lhs){
    RT Sum = 0.0;
    for(int i = 0; i < Scale; ++i){
        Sum += (lhs.v[i] * lhs.v[i]);
    }
    return Sum;
}

template<typename T, int Scale>
void Normalize(vector<T, Scale> &lhs){
    T v = Length(lhs);
    for(int i = 0; i < Scale; ++i){
        lhs.v[i] /= v;
    }
}

template<typename T, int Scale>
inline bool operator < (const vector<T, Scale> &lhs, const vector<T, Scale> &rhs){
    for(int i = 0; i < Scale; ++i){
        if(lhs.v[i] >= rhs.v[i]){
            return false;
        }
    }
    return true;
}

template<typename T, int Scale>
inline bool operator <= (const vector<T, Scale> &lhs, const vector<T, Scale> &rhs){
    for(int i = 0; i < Scale; ++i){
        if(lhs.v[i] > rhs.v[i]){
            return false;
        }
    }
    return true;
}

template<typename T, int Scale>
inline bool operator > (const vector<T, Scale> &lhs, const vector<T, Scale> &rhs){
    return !(lhs <= rhs);
}

template<typename T, int Scale>
inline bool operator >= (const vector<T, Scale> &lhs, const vector<T, Scale> &rhs){
    return !(lhs < rhs);
}


template<typename TA, typename TB, int Scale, typename RT>
inline vector<RT, Scale> Lerp(const vector<TA, Scale> &lhs, const vector<TB, Scale> &rhs, const float t){
    vector<RT, Scale> result;
    RT a = 1 - t, b = t;
    for(int i = 0; i < Scale; ++i){
        result[i] = lhs[i] * a + rhs[i] * b;
    }
    return result;
}

template<int Scale>
inline bool operator == (const vector<float, Scale> &lhs, const vector<float, Scale> &rhs){
    for(int i = 0; i < Scale; ++i){
        if(NXAbs(lhs.v[i] - rhs.v[i]) >= FLOAT_EPSILON){
            return false;
        }
    }
    return true;
}

template<int Scale>
inline bool operator == (const vector<double, Scale> &lhs, const vector<double, Scale> &rhs){
    for(int i = 0; i < Scale; ++i){
        if(NXAbs(lhs.v[i] - rhs.v[i]) >= DOUBLE_EPSILON){
            return false;
        }
    }
    return true;
}


template<typename T, int Scale>
inline vector<T, Scale> GetNegative(const vector<T, Scale> &lhs){
    return Negative(vector<T, Scale>(lhs));
}

template<typename T, int Scale>
inline vector<T, Scale>& Negative(vector<T, Scale> &lhs){
    return -lhs;
}

/**
 *  求点位于直接(2维)或平面(三维)上的投影(其中normal是法线，且默认直线或平面过原点)
 */
template<typename T, typename U>
inline vector<T, 2>& Project(vector<T, 2> &lhs, const vector<U, 2> &normal){
    vector<T, 2> n(normal);
    Normalize(n);
    T nxx = 1 - n.x * n.x, nyy = 1 - n.y * n.y, nxy = -n.x * n.y;
    return lhs = vector<T, 2>(
                              nxx * lhs[0] + nxy * lhs[1],
                              nxy * lhs[0] + nyy * lhs[1]);
}

template<typename T, typename U>
inline vector<T, 3>& Project(vector<T, 3> &lhs, const vector<U, 3> &normal){
    vector<T, 3> n(normal);
    Normalize(n);
    T nxx = 1 - n.x * n.x, nyy = 1 - n.y * n.y, nzz = 1 - n.z * n.z, nxy = -n.x * n.y, nyz = -n.y * n.z, nzx = -n.z * n.x;
    return lhs = vector<T, 3>(
                               nxx * lhs[0] + nxy * lhs[1] + nzx * lhs[2],
                               nxy * lhs[0] + nyy * lhs[1] + nyz * lhs[2],
                               nzx * lhs[0] + nyz * lhs[1] + nzz * lhs[2]
                               );
}

template<typename  T, typename U, typename RT>
inline vector<RT, 2> GetProject(const vector<T, 2> &lhs, const vector<U, 2> &normal){
    return Project(vector<RT, 2>(lhs), normal);
}

template<typename  T, typename U, typename RT>
inline vector<RT, 3> GetProject(const vector<T, 3> &lhs, const vector<U, 3> &normal){
    return Project(vector<RT, 3>(lhs), normal);
}

#ifndef DECLARE_VECTOR_TYPE
#define DECLARE_VECTOR_TYPE(type) \
    typedef NX::vector<type, 1> type##1;\
    typedef NX::vector<type, 2> type##2;\
    typedef NX::vector<type, 3> type##3;\
    typedef NX::vector<type, 4> type##4;
#endif

//char(byte)
DECLARE_VECTOR_TYPE(char)       //char1,
DECLARE_VECTOR_TYPE(byte);      //byte1
DECLARE_VECTOR_TYPE(sbyte);     //sbyte
DECLARE_VECTOR_TYPE(ubyte);     //ubyte
DECLARE_VECTOR_TYPE(schar);     //signed char
DECLARE_VECTOR_TYPE(uchar);     //unsigned char

//wchar_t
DECLARE_VECTOR_TYPE(wchar_t);
DECLARE_VECTOR_TYPE(swchar_t);
DECLARE_VECTOR_TYPE(uwchar_t);
DECLARE_VECTOR_TYPE(wchar);
DECLARE_VECTOR_TYPE(swchar);
DECLARE_VECTOR_TYPE(uwchar);

//short
DECLARE_VECTOR_TYPE(short);     //short
DECLARE_VECTOR_TYPE(sshort);    //signed short
DECLARE_VECTOR_TYPE(ushort);    //unsigned short

//int
DECLARE_VECTOR_TYPE(int);      //int
DECLARE_VECTOR_TYPE(sint);     //sgined int
DECLARE_VECTOR_TYPE(uint);     //unsigned int

//long
DECLARE_VECTOR_TYPE(long);     //long
DECLARE_VECTOR_TYPE(slong);    //signed long
DECLARE_VECTOR_TYPE(ulong);    //unsigned long

//long long
DECLARE_VECTOR_TYPE(llong);    //long long
DECLARE_VECTOR_TYPE(sllong);   //signed long long
DECLARE_VECTOR_TYPE(ullong);   //unsigned long long

//float
DECLARE_VECTOR_TYPE(float);    //float

//double
DECLARE_VECTOR_TYPE(double);   //double

#undef DECLARE_VECTOR_TYPE

#endif //!__ZX_NXENGINE_VECTOR_INL__