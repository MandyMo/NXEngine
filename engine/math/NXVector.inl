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

template<typename T, int Scale, typename RT>
inline vector<RT, Scale> operator + (const vector<T, Scale> &lhs, const T value){
    return (vector<RT, Scale>(lhs) += value);
}

template<typename T, int Scale, typename RT>
inline vector<RT, Scale> operator - (const vector<T, Scale> &lhs, const T value){
    return (vector<RT, Scale>(lhs) -= value);
}

template<typename T, typename U, int Scale, typename RT>
inline vector<RT, Scale> operator - (const vector<T, Scale> &lhs, const vector<U, Scale> &rhs){
    return (vector<RT, Scale>(lhs) -= rhs);
}

template<typename T, typename U, int Scale, typename RT>
inline vector<RT, Scale> operator * (const vector<T, Scale> &lhs, const vector<U, Scale> &rhs){
    return (vector<RT, Scale>(lhs) *= rhs);
}

template<typename T, int Scale, typename RT>
inline vector<RT, Scale> operator * (const vector<T, Scale> &lhs, const T value){
    return (vector<RT, Scale>(lhs) *= value);
}

template<typename T, int Scale, typename RT>
inline vector<RT, Scale> operator * (const T value, const vector<T, Scale> &lhs){
    return (vector<RT, Scale>(lhs) *= value);
}

template<typename T, typename U, int Scale, typename RT>
inline vector<RT, Scale> operator / (const vector<T, Scale> &lhs, const vector<U, Scale> &rhs){
    return (vector<RT, Scale>(lhs) /= rhs);
}

template<typename T, int Scale, typename RT>
inline vector<RT, Scale> operator / (const vector<T, Scale> &lhs, const T value){
    return (vector<RT, Scale>(lhs) /= value);
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
