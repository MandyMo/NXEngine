
inline int    RandInt(){
    return std::rand();
}

inline int RandIntInRange(int left, int right){
    assert(left <= right);
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
    assert(NXAbs(right - left) > FLOAT_EPSILON);
    return RandUnitFloat() * (right - left) + left;
}

double QuickSinWithAngle(const int Angle){
    return std::sin(DG2RD(Angle));
}

double QuickCosWithAngle(const int Angle){
    return std::cos(DG2RD(Angle));
}

//ComparedValue >= NewValue
template<typename T, typename U>
inline T ClampFloor(T& ComparedValue, const U NewValue){
    T OldValue(ComparedValue);
    if(ComparedValue < NewValue){
        ComparedValue = NewValue;
    }
    return OldValue;
}

//ComparedValue <= NewValue
template<typename T, typename U>
inline T ClampCeil(T& ComparedValue, const U NewValue){
    T OldValue(ComparedValue);
    if(ComparedValue > NewValue){
        ComparedValue = NewValue;
    }
    return OldValue;
}

//FloorValue <= CompraedValue <= CeilValue
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