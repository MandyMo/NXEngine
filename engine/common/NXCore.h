/*
 *  File:     core.h
 *  Author:   张雄
 *  Date:     2016_02_22
 *  Purpose:  引擎中需要使用的一些共公东西
 */


#ifndef __ZX_NXENGINE_CORE_H__
#define __ZX_NXENGINE_CORE_H__

#ifndef __in
#define __in
#endif

#ifndef __out
#define __out
#endif

#ifndef __in_opt
#define __in_opt
#endif

#ifndef _T
#ifndef UNICODE
    #define _T(queto) queto
#else
    #define _T(queto) L##queto
#endif
#endif

#ifndef TEXT
#define TEXT(queto) _T(queto)
#endif

#if defined(_MSC_VER)
#if defined(WINRT)
#define PLATFORM_WINRT 1
#else
#define PLATFORM_WINDOWS 1
#endif

#if defined(_WIN64)
#define PLATFORM_64 1
#elif defined(_WIN32)
#define PLATFORM_32 1
#endif
#elif defined(__ANDROID__)
#define PLATFORM_ANDROID 1
#if defined(__x86_64__) || defined(__aarch64__)
#define PLATFORM_64 1
#else
#define PLATFORM_32 1
#endif
#elif defined(__linux__)
#define PLATFORM_LINUX 1
#if defined(__x86_64__)
#define PLATFORM_64 1
#else
#define PLATFORM_32 1
#endif
#elif defined(__APPLE__)
#if defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_IPHONE)
#define PLATFORM_IOS 1
#else
#define PLATFORM_OSX 1
#endif

#if defined(__x86_64__) || defined(__arm64__)
#define PLATFORM_64 1
#else
#define PLATFORM_32 1
#endif
#endif

/**
 *  注意，在debug模式下，XCode下，默认不会定义DEBUG宏，在VS上默认会定义
 */
#if defined(DEBUG) || defined(_DEBUG)
    #define DEBUG_MODE 1
#endif


#ifndef CLS_MEM_OFFSET
#define CLS_MEM_OFFSET(ClsName, MemName) \
    (void*)(&((ClsName*)0)->MemName)
#endif

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(Addr) \
    ((void*)((Addr)))
#endif

#ifndef ARRAY_LENGTH
#define ARRAY_LENGTH(Addr) \
    (sizeof(Addr) / sizeof(Addr[0]))
#endif

#ifndef ARRAY_ELEMENT_NAME
#define ARRAY_ELEMENT_NAME(Ary) \
    (typeid(Ary[0]).name())
#endif

#ifndef NX_STR_PASTE
    #define NX_STR_PASTE(x, y)  x##y
#endif

#ifndef NX_TO_STR
#define NX_TO_STR(expr) #expr
#endif

#include <cassert>
#include <cmath>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


//char
typedef char            byte;
typedef signed   char   sbyte;
typedef unsigned char   ubyte;
typedef signed   char   schar;
typedef unsigned char   uchar;

//wchar_t
typedef signed wchar_t   swchar_t;
typedef unsigned wchar_t uwchar_t;
typedef wchar_t          wchar;
typedef signed wchar_t   swchar;
typedef unsigned wchar_t uwchar;

//short
typedef signed   short   sshort;
typedef unsigned short   ushort;

//int
typedef signed   int     sint;
typedef unsigned int     uint;


//long
typedef signed   long     slong;
typedef unsigned long     ulong;

//long long
typedef signed long long    sllong;
typedef unsigned long long  ullong;
typedef long long           llong;

template<GLenum Type>
class NXEnable{
public:
    NXEnable(){
        glEnable(Type);
    }
    ~NXEnable(){
        glDisable(Type);
    }
};

namespace NX{
    extern void NXAssertFailed(const char *szFileName, const int iLine);
}

#ifndef NXAssert
#if DEBUG_MODE
#define NXAssert(expr) \
    if((expr)){\
    }else{/*NXAssert failed*/\
        NX::NXAssertFailed(__FILE__, __LINE__);\
    }
#else
#define NXAssert(expr)
#endif
#endif


namespace NX {
    template<typename T, int len>
    int ArrayLength(const T (&)[len]){
        return len;
    }
    
    template<typename T, int len>
    std::string ArrayElementName(const T (&)[len]){
        return typeid(T).name();
    }
    
}


#endif //!__ZX_NXENGINE_CORE_H__