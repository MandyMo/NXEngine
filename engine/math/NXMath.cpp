
/*
 *  File:    NXMath.cpp
 *  author:  张雄
 *  date:    2016_02_26
 *  purpose: 基本的数学库函数的实现
 */

#include <utility>
#include "NXMath.h"

void NX::InitNXMath(){
    std::srand((unsigned int)std::time(NULL));
}

float NX::SafeACos(const float value){
    if(value > 1.0f){
        return 0;
    }else if(value < -1.0){
        return kfPi;
    }else{
        return std::acos(value);
    }
}

float NX::SafeASin(const float value){
    if(value > 1.0f){
        return kfPiOver2;
    }else if(value < -1.0f){
        return -kfPiOver2;
    }else{
        return std::sin(value);
    }
}

std::pair<float, float> NX::GetSinAndCos(const float radian){
    return std::make_pair<float, float>(std::sin(radian), std::cos(radian));
}

void NX::GetSinAndCos(const float radian, float * const pSinvalue, float * const pCosValue){
    assert(pSinvalue != NULL && pCosValue != NULL);
    *pSinvalue = std::sin(radian);
    *pCosValue = std::cos(radian);
}

template<typename T, typename U, typename R>
T NX::Wrap(T &value, const U mode){
    T OldValue = value;
    R v        = value / mode;
    value     -= v * mode;
    return OldValue;
}