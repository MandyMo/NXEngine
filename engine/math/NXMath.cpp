
/*
 *  File:    NXMath.cpp
 *  author:  张雄
 *  date:    2016_02_26
 *  purpose: 基本的数学库函数的实现
 */

#include <utility>
#include "NXMath.h"
#include "NXComplex.h"
#include "NXVector.h"
#include "NXMatrix.h"
#include <vector>
#include <functional>

void NX::InitNXMath(){
    std::srand((unsigned int)std::time(NULL));
}

float NX::SafeACos(const float value){
    if(value >= 1.0f){
        return 0;
    }else if(value <= -1.0){
        return kfPi;
    }else{
        return std::acos(value);
    }
}

float NX::SafeASin(const float value){
    if(value >= 1.0f){
        return kfPiOver2;
    }else if(value <= -1.0f){
        return -kfPiOver2;
    }else{
        return std::asin(value);
    }
}

std::pair<float, float> NX::GetSinAndCos(const float radian){
    return std::make_pair<float, float>(std::sin(radian), std::cos(radian));
}

void NX::GetSinAndCos(const float radian, float * const pSinvalue, float * const pCosValue){
    NXAssert(pSinvalue != NULL && pCosValue != NULL);
    *pSinvalue = std::sin(radian);
    *pCosValue = std::cos(radian);
}

double NX::NXQuickKSquare(const double base, const int k, const double Delta){
    double l, r, m;
    if(base >= 0){
        if(base >= 1.0){
            l = 1.0,  r = base;
        }else{
            l = base, r = 1.0;
        }
    }else{
        if((k & 1) == 0){
            return NAN;
        }
        if(base < -1.0){
            l = base;
            r = -1.0;
        }else{
            l = -1.0;
            r = 0.0;
        }
    }
    m = (l + r) * 0.5;
    while(NX::NXAbs(r - l) > Delta){
        m = (l + r) * 0.5;
        if(NX::NXQuickPow(m, k) > base){
            r = m;
        }else{
            l = m;
        }
    }
    return m;
}

double  NXKSquare(const double base, const int k){
    NXAssert((k & 1) || ((k & 1) == 0 && base >= 0.0));
    return std::pow(NX::NXAbs(base), 1.0 / k) * NX::NXSign(base);
}

/**
 *  ax + b = 0
 */
std::vector<NX::Complex> NX::SolveEquation(const float a, const float b){
    NXAssert(!NX::Equalfloat(a, 0.0f));
    std::vector<NX::Complex> result;
    result.push_back(NX::Complex(-b / a));
    return result;
}

std::vector<float> NX::SolveEquationWithOnlyRealResult(const float a, const float b){
    NXAssert(!NX::EqualZero(a));
    std::vector<float> result;
    result.push_back(-b / a);
    return result;
}

/**
 * axx + bx + c = 0
 */
std::vector<NX::Complex> NX::SolveEquation(const float a, const float b, const float c){
    NXAssert(!NX::Equalfloat(a, 0.0f));
    const float delta = b * b - 4 * a * c;
    std::vector<NX::Complex> result;
    const float Mult = 0.5f / a;
    if(NX::Equalfloat(delta, 0.0f)){
        result.push_back(NX::Complex(-b * Mult));
        result.push_back(NX::Complex(-b * Mult));
    }else if(delta > 0){
        float d = std::sqrt(delta);
        result.push_back(NX::Complex((-b + d) * Mult));
        result.push_back(NX::Complex((-b - d) * Mult));
    }else{//unreal solution
        float d = std::sqrt(-delta);
        result.push_back(NX::Complex(-b,  d) * Mult);
        result.push_back(NX::Complex(-b, -d) * Mult);
    }
    return result;
}

std::vector<float> NX::SolveEquationWithOnlyRealResult(const float a, const float b, const float c){
    NXAssert(!NX::Equalfloat(a, 0.0f));
    const float delta = b * b - 4 * a * c;
    std::vector<float> result;
    const float Mult = 0.5f / a;
    if(NX::Equalfloat(delta, 0.0f)){
        result.push_back(-b * Mult);
    }else if(delta > 0){
        float d = std::sqrt(delta);
        result.push_back((-b + d) * Mult);
        result.push_back((-b - d) * Mult);
    }else{//unreal solution
        /*not real solution, we don't need it*/
    }
    return result;
}

/**
 *  axxx + bxx + cx + d = 0
 */
std::vector<NX::Complex> NX::SolveEquation(const float a, const float b, const float c, const float d){
    NXAssert(!NX::Equalfloat(a, 0.0f));
    const float Mult = 1.0f / a;
    const float x = b * Mult;
    const float y = c * Mult;
    const float z = d * Mult;
    const float p = -x * x / 9.0f + y / 3.0f;
    const float q =  x * x * x / 27.0f - x * y / 6.0f + 0.5f * z;
    const float D = -(p * p * p + q * q);
    const float Exp = 1.0f / 3.0f;
    std::vector<NX::Complex> result;
    if(NX::Equalfloat(D, 0.0f)){
        const float r = std::pow(NX::NXAbs(-q), Exp) * NX::NXSign(-q);
        result.push_back(NX::Complex(2 * r));
        result.push_back(NX::Complex(-r));
        result.push_back(NX::Complex(-r));
    }else if(D < 0.0f){
        const float w = std::sqrt(-D);
        const float r = std::pow(NX::NXAbs(-q + w), Exp) * NX::NXSign(-q + w);
        const float s = std::pow(NX::NXAbs(-q - w), Exp) * NX::NXSign(-q - w);
        const float t = std::sqrt(3.0f) * 0.5f;
        const NX::Complex u(-0.5f, t), v(-0.5f, -t);
        result.push_back(NX::Complex(r + s));
        result.push_back(r * u + s * v);
        result.push_back(r * v + s * u);
    }else{
        const float w = std::sqrt(-p);
        float Theta = std::acos(q / (w * p)) * Exp;
        result.push_back(NX::Complex(2 * w * std::cos(Theta)));
        result.push_back(NX::Complex(2 * w * std::cos(Theta + 2.0f * Exp * kfPi)));
        result.push_back(NX::Complex(2 * w * std::cos(Theta - 2.0f * Exp * kfPi)));
    }
    const float w = x / 3.0f;
    for(int i = 0; i < 3; ++i){
        result[i] -= w;
    }
    return result;
}

std::vector<float> NX::SolveEquationWithOnlyRealResult(const float a, const float b, const float c, const float d){
    NXAssert(!NX::Equalfloat(a, 0.0f));
    const float Mult = 1.0f / a;
    const float x = b * Mult;
    const float y = c * Mult;
    const float z = d * Mult;
    const float p = -x * x / 9.0f + y / 3.0f;
    const float q =  x * x * x / 27.0f - x * y / 6.0f + 0.5f * z;
    const float D = -(p * p * p + q * q);
    const float Exp = 1.0f / 3.0f;
    std::vector<float> result;
    if(NX::Equalfloat(D, 0.0f)){//two real solution
        const float r = std::pow(NX::NXAbs(-q), Exp) * NX::NXSign(-q);
        result.push_back(2 * r);
        result.push_back(-r);
    }else if(D < 0.0f){//only one real solution
        const float w = std::sqrt(-D);
        const float r = std::pow(NX::NXAbs(-q + w), Exp) * NX::NXSign(-q + w);
        const float s = std::pow(NX::NXAbs(-q - w), Exp) * NX::NXSign(-q - w);
        result.push_back(r + s);
    }else{//three real solution
        const float w = std::sqrt(-p);
        float Theta = std::acos(q / (w * p)) * Exp;
        result.push_back(2 * w * std::cos(Theta));
        result.push_back(2 * w * std::cos(Theta + 2.0f * Exp * kfPi));
        result.push_back(2 * w * std::cos(Theta - 2.0f * Exp * kfPi));
    }
    const float w = x / 3.0f;
    for(int i = 0; i < result.size(); ++i){
        result[i] -= w;
    }
    return result;
}

/**
 *  axxxx + bxxx + cxx + dx + e = 0
 */
std::vector<NX::Complex> NX::SolveEquation(const float a, const float b, const float c, const float d, const float e){
    NXAssert(!NX::Equalfloat(a, 0.0f));
    const float Mult = 1.0f / a;
    const float x = b * Mult;
    const float y = c * Mult;
    const float z = d * Mult;
    const float w = e * Mult;
    const float p = -3.0f / 8.0f * x * x + y;
    const float q = 1.0f / 8 * x * x * x - 0.5f * x * y + z;
    const float r = -3.0f / 256.f * x * x * x * x + x * x * y / 16.f - 0.25f * x * z + w;
    const std::vector<NX::Complex> &TS = NX::SolveEquation(1.0f, -p * 0.5f, -r, (4.0f * r * p - q * q) / 8.0f);
    float solv = 0.0f;
    for(int i = 0, l = (int)TS.size(); i < l; ++i){
        if(TS[i].IsRealNumber()){
            solv = TS[i].GetReal();
            break;
        }
    }
    std::vector<NX::Complex> result;
    float CofA, CofB, CofC, CofD;
    if(q >= 0.0f){
        CofA = std::sqrt(2.0 * solv - p);
        CofB = -std::sqrt(solv * solv - r);
        CofC = -CofA;
        CofD = -CofB;
        CofB += solv;
        CofD += solv;
    }else{
        CofA = std::sqrt(2.0 * solv - p);
        CofB = std::sqrt(solv * solv - r);
        CofC = -CofA;
        CofD = -CofB;
        CofB += solv;
        CofD += solv;
    }
    const std::vector<NX::Complex> &SA = NX::SolveEquation(1.0f, CofA, CofB);
    const std::vector<NX::Complex> &SB = NX::SolveEquation(1.0f, CofC, CofD);
    result.push_back(SA[0]), result.push_back(SA[1]);
    result.push_back(SB[0]), result.push_back(SB[1]);
    const float delta = x / 4.0f;
    for(int i = 0; i < 4; ++i){
        result[i] -= delta;
    }
    return result;
}

std::vector<float> NX::SolveEquationWithOnlyRealResult(const float a, const float b, const float c, const float d, const float e){
    NXAssert(!NX::Equalfloat(a, 0.0f));
    const float Mult = 1.0f / a;
    const float x = b * Mult;
    const float y = c * Mult;
    const float z = d * Mult;
    const float w = e * Mult;
    const float p = -3.0f / 8.0f * x * x + y;
    const float q = 1.0f / 8 * x * x * x - 0.5f * x * y + z;
    const float r = -3.0f / 256.f * x * x * x * x + x * x * y / 16.f - 0.25f * x * z + w;
    const std::vector<float> &TS = NX::SolveEquationWithOnlyRealResult(1.0f, -p * 0.5f, -r, (4.0f * r * p - q * q) / 8.0f);
    const float solv = TS[0];
    std::vector<float> result;
    float CofA, CofB, CofC, CofD;
    if(q >= 0.0f){
        CofA = std::sqrt(2.0 * solv - p);
        CofB = -std::sqrt(solv * solv - r);
        CofC = -CofA;
        CofD = -CofB;
        CofB += solv;
        CofD += solv;
    }else{
        CofA = std::sqrt(2.0 * solv - p);
        CofB = std::sqrt(solv * solv - r);
        CofC = -CofA;
        CofD = -CofB;
        CofB += solv;
        CofD += solv;
    }
    const std::vector<float> &SA = NX::SolveEquationWithOnlyRealResult(1.0f, CofA, CofB);
    const std::vector<float> &SB = NX::SolveEquationWithOnlyRealResult(1.0f, CofC, CofD);
    for(int i = 0; i < SA.size(); ++i){
        result.push_back(SA[i]);
    }
    for(int i = 0; i < SB.size(); ++i){
        result.push_back(SB[i]);
    }
    const float delta = x / 4.0f;
    for(int i = 0; i < result.size(); ++i){
        result[i] -= delta;
    }
    return result;
}

std::pair<bool, NX::vector<float, 2> > NX::SolveEquation(const NX::Matrix<float, 2, 2> &M, const NX::vector<float, 2> &V){
    std::pair<bool, NX::vector<float, 2> > result;
    float Delta = M[0][0] * M[1][1] - M[0][1] * M[1][0];
    if(NXAbs(Delta) < Epsilon<float>::m_Epsilon){
        result.first = false;
        return result;
    }
    result.first = true;
    result.second[0] = M[1][1] * V[0] - M[0][1] * V[1];
    result.second[1] = M[0][0] * V[1] - M[1][0] * V[0];
    result.second /= Delta;
    return result;
}

std::vector<float> NX::GetEigenValueOfSymmetricMatrix(const NX::Matrix<float, 3, 3> &M){
    const float a = M[0][0];
    const float b = M[0][1];
    const float c = M[0][2];
    const float d = M[1][1];
    const float e = M[1][2];
    const float f = M[2][2];
    const float x = -kf1;
    const float y = (a + d + f);
    const float z = (-a * (d + f) - d * f + b * b + c * c + e * e);
    const float w = (a * d * f + kf2 * b * c * e - a * e * e - f * b * b - d * c * c);
    /**
     *  have three real solution, which can be proved
     */
    std::vector<float> vEigenValue = NX::SolveEquationWithOnlyRealResult(x, y, z, w);
    std::sort(vEigenValue.begin(), vEigenValue.end(), std::greater<float>());
    return vEigenValue;
}

std::vector<NX::vector<float, 3> > NX::GetEigenVectorOfSymmetricMatrix(const NX::Matrix<float, 3, 3> &M){
    //to be continue
    return std::vector<NX::vector<float, 3> > ();
}