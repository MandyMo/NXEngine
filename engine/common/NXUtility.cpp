/*
 *  File:     NXUtility.h
 *  Author:   张雄
 *  Date:     2016_06_14
 *  Purpose:  四元组，三元组，二元组等以及一些辅助函数
 */
#include "NXUtility.h"

static NXUInt64 Factorial[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600, 6227020800, 87178291200, 1307674368000,20922789888000,355687428096000,6402373705728000,121645100408832000,2432902008176640000};

NXUInt64 NX::NXEncodePermutation(int * iPlacement, int len){
    std::vector<int> iExist;
    for(int i = 0; i < len; ++i){
        iExist.push_back(i);
    }
    NXUInt64 result = 0;
    for(int i = 0; i < len; ++i){
        result += (std::lower_bound(iExist.begin(), iExist.end(), iPlacement[i]) - iExist.begin()) * Factorial[len - i - 1];
        iExist.erase(std::find(iExist.begin(), iExist.end(), iPlacement[i]));
    }
    return result;
}

std::vector<int> NX::NXDecodePermutation(int iRanked, int len){
    std::vector<int> iExist, vResult;
    for(int i = 0; i < len; ++i){
        iExist.push_back(i);
    }
    for(int i = 0; i < len; ++i){
        int idx = iRanked / Factorial[len - i - 1];
        vResult.push_back(iExist[idx]);
        iExist.erase(iExist.begin() + idx);
        iRanked -= idx * Factorial[len - i - 1];
    }
    return vResult;
}