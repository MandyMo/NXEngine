/*
 *  File:     core.h
 *  Author:   张雄
 *  Date:     2016_02_22
 *  Purpose:  引擎中需要使用的一些共公东西
 */


#ifndef __ZX_NXENGINE_CORE_H__
#define __ZX_NXENGINE_CORE_H__

#include "NXType.h"
#include "NXPlatform.h"

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
#include <cstring>
#include <typeinfo>
#include <cstdarg>
#include <cstdio>
#if !PLATFORM_WINDOWS
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#endif



#if !defined(_MSC_VER)
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

#endif

namespace NX{
    extern void NXAssertFailed(const char *szFileName, const char *szFuncName, const int iLine, const char * expr);
}

#ifndef NXAssert
#if DEBUG_MODE
#define NXAssert(expr) \
    if((expr)){\
    }else{/*NXAssert failed*/\
        NX::NXAssertFailed(__FILE__, __func__, __LINE__, #expr);\
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
    
    template<typename T>
    inline void NXZeroMemory(T * ptr){
        std::memset(ptr, 0, sizeof(T));
    }
    
    inline void NXZeroMemory(void * ptr, int _n){
        std::memset(ptr, 0, _n);
    }

	template<typename T, int N>
	inline void NXZeroArray(T (&AryRef)[N] ) {
		NX::NXZeroMemory(AryRef, sizeof(AryRef));
	}

	template<typename T>
	inline void NXSafeRelease(T*& objPtr) {
		if (objPtr) {
			objPtr->Release();
		}
		objPtr = NULL;
	}
}

#endif //!__ZX_NXENGINE_CORE_H__