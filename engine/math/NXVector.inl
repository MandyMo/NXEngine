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

template<typename T, typename U, int Scale>
inline vector<T, Scale> operator % (const vector<T, Scale> &lhs, const U &ModeValue) {
	vector<T, Scale> result(lhs);
	for (int i = 0; i < Scale; ++i) {
		result[i] -= ModeValue * floor(result[i] / ModeValue);
	}
	return result;
}

#ifndef DECLARE_VECTOR_TYPE
#define DECLARE_VECTOR_TYPE(type) \
    typedef NX::vector<type, 1> type##1;\
    typedef NX::vector<type, 2> type##2;\
    typedef NX::vector<type, 3> type##3;\
    typedef NX::vector<type, 4> type##4;
#endif

//char(byte)
DECLARE_VECTOR_TYPE(NXInt8)
DECLARE_VECTOR_TYPE(NXUInt8)
DECLARE_VECTOR_TYPE(NXInt16)
DECLARE_VECTOR_TYPE(NXUInt16)
DECLARE_VECTOR_TYPE(NXInt32)
DECLARE_VECTOR_TYPE(NXUInt32)
DECLARE_VECTOR_TYPE(NXInt64)
DECLARE_VECTOR_TYPE(NXUInt64)

//float
DECLARE_VECTOR_TYPE(float);    //float

//double
DECLARE_VECTOR_TYPE(double);   //double

#undef DECLARE_VECTOR_TYPE

typedef float3 Point3D;
typedef float2 Point2D;
typedef float2 Size2D;
typedef float3 Size3D;

#endif //!__ZX_NXENGINE_VECTOR_INL__