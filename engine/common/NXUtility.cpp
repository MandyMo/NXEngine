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

static inline NXUInt64 NXQuickModPow(NXUInt64 x, NXUInt64 n, NXUInt64 mod); //return x^n % mod
static inline NXUInt64 NXPow2Mod(NXUInt64 x, NXUInt64 n, NXUInt64 mod);//return x << n % mod

static NXUInt64 p    = 2147483647;
static NXUInt64 q    = 2305843009213693951ull;
static NXUInt64 rq   = NXQuickModPow(p, q - 2, q);


static inline std::string ReadFile(const std::string &strFilePath);
static inline void        WriteFile(const std::string &strDstFilePath, const std::string &strContent);
static std::string        EncodeBase64Chunk(const char *start, const char *end);
static std::string        DecodeBase64Chunk(const char *start, const char *end);
static std::string        EncrpytChunk(const char * start, const char * end);
static std::string        DecrpytChunk(const char * start, const char * end);

std::string  NX::EncodeBase64(const std::string &src){
    int len = (int)src.length();
    assert(len >= 1);
    std::string result;
    if(src.length() == 0){
        return std::string("");
    }
    for(int i = 0; i + 3 < len; i += 3){
        result.append(EncodeBase64Chunk(&src[i], &src[i + 3]));
    }
    result.append(EncodeBase64Chunk(&src[len % 3 == 0 ? len - 3 : len - (len % 3)], &src[len]));
    return result;
}

std::string  NX::DecodeBase64(const std::string &src){
    std::string result;
    int len = (int)src.length();
    assert(len % 4  == 0);
    if(len % 4 != 0){
        return result;
    }
    for(int i = 0; i < len; i += 4){
        result.append(DecodeBase64Chunk(&src[i], &src[i + 4]));
    }
    return result;
}

std::string  NX::Encrpt(const std::string &src){
    std::string str(src);
    int pad = (4 - str.length() % 4) % 4;
    while(pad--){
        str.push_back('\n');
    }
    std::string result;
    for(int i = 0; i < str.length(); i += 4){
        result.append(EncrpytChunk(&str[i], &str[i + 4]));
    }
    return EncodeBase64(result);
}

std::string  NX::Decrpt(const std::string &src){
    std::string str = DecodeBase64(src);
    assert(str.length() % 8 == 0);
    std::string result;
    for(int i = 0; i < str.length(); i += 8){
        result.append(DecrpytChunk(&str[i], &str[i + 8]));
    }
    return result;
}

std::string  NX::DecrptFromFile(const std::string &strSrcFile, const std::string &strDstFile){
    std::string strSrcContent = ReadFile(strSrcFile);
    std::string strDstContent = Decrpt(strSrcContent);
    WriteFile(strDstFile, strDstContent);
    return strDstContent;
}

std::string  NX::EncrptFromFile(const std::string &strSrcFile, const std::string &strDstFile){
    std::string strSrcContent = ReadFile(strSrcFile);
    std::string strDstContent = Encrpt(strSrcContent);
    WriteFile(strDstFile, strDstContent);
    return strDstContent;
}

static std::string EncodeBase64Chunk(const char *start, const char *end){
    unsigned int code = 0;
    int c;
    std::string result;
    int len = (int)(end - start);
    assert(len <= 3);
    for(const char *p = start; p != end; ++p){
        code = (code << 8) | ((unsigned char)*p);
    }
    if(len == 1){
        code <<= 4;
    }else if(len == 2){
        code <<= 2;
    }
    
    for(int i = 0; i < (len * 8 + 5) / 6; ++i){
        c = code & 0x3F;
        if(c < 26){//[0, 26) => ['A', 'Z']
            result.push_back(c + 'A');
        }else if(c < 52){//[26, 52) => ['a', 'z']
            result.push_back(c - 26 + 'a');
        }else if(c < 62){//[52, 62) => ['0', '9']
            result.push_back(c - 52 + '0');
        }else if(c == 62){//62 => '+'
            result.push_back('+');
        }else{//63 => '-'
            result.push_back('-');
        }
        code >>= 6;
    }
    std::reverse(result.begin(), result.end());
    //append tail =
    while(len < 3){
        result.push_back('=');
        ++len;
    }
    return result;
}

static std::string DecodeBase64Chunk(const char *start, const char *end){
    std::string result;
    assert(end - start == 4);
    unsigned int code = 0;
    const char * p;
    unsigned int c;
    for(p = start; p != end && *p != '='; ++p){
        if(*p >= 'A' && *p <= 'Z'){
            c = *p - 'A' + 0;
        }else if(*p >= 'a' && *p <= 'z'){
            c = *p - 'a' + 26;
        }else if(*p >= '0' && *p <= '9'){
            c = *p - '0' + 52;
        }else if(*p == '+'){
            c = 62;
        }else{
            c = 63;
        }
        code = (code << 6) | c;
    }
    int pad = (int)(end - p);
    code >>= (pad << 1);
    for(int i = 0; i < 3 - pad; ++i){
        result.push_back(code & 0xFF);
        code >>= 8;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

static std::string EncrpytChunk(const char * start, const char * end){
    assert(end - start == 4);
    NXUInt64 src = 0;
    for(const char * p = start; p != end; ++p){
        src = (src << 8) | ((unsigned char)*p);
    }
    src = (src * p) % q;
    std::string result;
    for(int i = 0; i < 8; ++i){
        result.push_back(src & 0xFF);
        src >>= 8;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

static std::string DecrpytChunk(const char * start, const char * end){
    assert(end - start == 8);
    NXUInt64 a = 0;
    for(const char * p = start; p != end; ++p){
        a = a << 8 | ((unsigned char)*p);
    }
    NXUInt64 b = rq;
    NXUInt64 ah = a >> 32, al = a & 0xFFFFFFFF;
    NXUInt64 bh = b >> 32, bl = b & 0xFFFFFFFF;
    NXUInt64 ab = (NXPow2Mod((ah * bh) % q, 64, q) + NXPow2Mod((bh * al + ah * bl) % q, 32, q) + (al * bl) % q) % q;
    std::string result;
    for(int i = 0; i < 4; ++i){
        result.push_back(ab & 0xFF);
        ab >>= 8;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

static inline NXUInt64 NXQuickModPow(NXUInt64 x, NXUInt64 n, NXUInt64 mod){
    if(n == 1){
        return x;
    }else if(n == 0){
        return 1;
    }
    NXUInt64 dx = NXQuickModPow(x, n >> 1, mod);
    NXUInt64 dxh = dx >> 32, dxl = dx & 0xFFFFFFFF;
    NXUInt64 xh  = x  >> 32,  xl = x  & 0xFFFFFFFF;
    NXUInt64 ddx = (NXPow2Mod((dxh * dxh % mod), 64, mod) + NXPow2Mod((dxh * dxl) % mod, 33, mod) + (dxl * dxl) % mod) % mod;
    NXUInt64 ah  = ddx >> 32, al = ddx & 0xFFFFFFFF;
    return n & 1 ? (NXPow2Mod((ah * xh % mod), 64, mod) + NXPow2Mod(((ah * xl) % mod + (al * xh) % mod) % mod, 32, mod) + (al * xl) % mod) % mod: ddx;
}

static inline NXUInt64 NXPow2Mod(NXUInt64 x, NXUInt64 n, NXUInt64 mod){
    for(int i = 0; i < n; ++i){
        x <<= 1;
        x %= mod;
    }
    return x;
}

static inline std::string ReadFile(const std::string &strFilePath){
    FILE *reader = fopen(strFilePath.c_str(), "rb");
    if(!reader){
        return std::string("");
    }
    fseek(reader, 0, SEEK_END);
    unsigned len = (unsigned)ftell(reader);
    fseek(reader, 0, SEEK_SET);
    std::string strContent(len, '\0');
    fread(&strContent[0], sizeof(strContent[0]), len, reader);
    fclose(reader);
    return strContent;
}

static inline void WriteFile(const std::string &strDstFilePath, const std::string &strContent){
    FILE *writer = fopen(strDstFilePath.c_str(), "wb");
    if(!writer){
        return;
    }
    fwrite(strContent.c_str(), sizeof(strContent[0]), strContent.length(), writer);
    fclose(writer);
}