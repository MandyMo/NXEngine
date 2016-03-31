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

#ifndef PI
#define PI 3.1415926
#endif

#ifndef DG2RD
#define DG2RD(angel)\
    (angel * PI / 180.0)
#endif


#ifndef RD2DG
#define RD2DG(radius)\
    (radius * 180.0 / PI)
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
    static const float  FLOAT_EPISION   = 0.0001f;
    static const double DOUBLE_EPISION  = 0.0000001;
}

#endif