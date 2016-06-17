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
    return (vector<RT, Scale>(value) /= lhs);
}

template<typename T, int Scale>
inline bool operator != (const vector<T, Scale> &lhs, const vector<T, Scale> &rhs){
    return !(lhs == rhs);
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

#endif //!__ZX_NXENGINE_VECTOR_INL__