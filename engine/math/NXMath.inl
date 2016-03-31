
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
    assert(std::abs(right - left) > FLOAT_EPISION);
    return RandUnitFloat() * (right - left) + left;
}