/*
 *  File:    NXMath.inl
 *  author:  张雄
 *  date:    2016_02_26
 *  purpose: 基本的数学库函数
 */

inline int    RandInt(){
    return std::rand();
}

template<typename T>
inline float DG2RD(const T angle){
    return angle * kfPi / 180.0f;
}

template<typename T>
inline float RD2DG(const T radian){
    return radian * 180.0f * kf1OverPi;
}

inline int RandIntInRange(int left, int right){
    NXAssert(left <= right);
    return left + RandInt() % (right - left + 1);
}

//如果不懂这代码，请先看明白IEEE754浮点数标准
inline float  RandUnitFloat(){
    static unsigned int seed = std::rand();
    float Result;
    unsigned int tmp;
    seed *= 16807;
    tmp = seed ^ (seed >> 4) ^ (seed << 15);
    *((unsigned int *) &Result) = (tmp >> 9) | 0x3F800000;
    return (Result - 1.0f);
}

inline float  RandFloatInRange(float left, float right){
    NXAssert(NXAbs(right - left) > FLOAT_EPSILON);
    return RandUnitFloat() * (right - left) + left;
}

//after clamp, we have ComparedValue >= NewValue
template<typename T, typename U>
inline T ClampFloor(T& ComparedValue, const U NewValue){
    T OldValue(ComparedValue);
    if(ComparedValue < NewValue){
        ComparedValue = NewValue;
    }
    return OldValue;
}

//after clamp, we have ComparedValue <= NewValue
template<typename T, typename U>
inline T ClampCeil(T& ComparedValue, const U NewValue){
    T OldValue(ComparedValue);
    if(ComparedValue > NewValue){
        ComparedValue = NewValue;
    }
    return OldValue;
}

//after clamp, we have FloorValue <= CompraedValue <= CeilValue
template<typename T, typename U, typename X>
inline T Clamp(T& ComparedValue, const U FloorValue, const X CeilValue){
    T OldValue(ComparedValue);
    if(OldValue > CeilValue){
        ComparedValue = CeilValue;
    }
    if(OldValue < FloorValue){
        ComparedValue = FloorValue;
    }
    return OldValue;
}

template<typename T>
T NXAbs(const T value){
    return value < 0 ? -value : value;
}

template<typename T, typename U>
T NXMin(const T l, const U r){
    return l < r ? l : r;
}

template<typename T, typename U>
T NXMax(const T l, const U r){
    return l > r ? l : r;
}

template<typename T>
T NXSign(const T v){
    if(v > Epsilon<T>::m_Epsilon){
        return T(1);
    }else if(v < -Epsilon<T>::m_Epsilon){
        return T(-1);
    }else{
        return T(0);
    }
}


template<typename T, typename U>
T Wrap(T &value, const U mode){
    T OldValue = value;
    value += mode;
    Mode(value, mode * 2);
    value -= mode;
    return OldValue;
}

template<typename T, typename U>
T Mode(T &value, const U mode){
    T OldValue = value;
    int v      = value / mode;
    value     -= v * mode;
    if(value < 0){
        value += mode;
    }
    return OldValue;
}

inline double DG2RD(const double angle){
    return angle * klfPi / 180.0f;
}

inline double RD2DG(const double angle){
    return angle * 180.0 / klfPi;
}

template<typename T>
T NXQuickPow(const T base, const int exp){
    if(exp == 0){
        return T(1);
    }else if(exp == 1){
        return base;
    }else{
        const T v = NXQuickPow(base, exp >> 1);
        return exp & 1 ? v * v * base : v * v;
    }
}
