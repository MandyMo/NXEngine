/*
 *  File:     NXType.h
 *  Author:   张雄
 *  Date:     2016_08_19
 *  Purpose:  定义基本类型
 */

#pragma once

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

typedef sbyte NXInt8;
typedef ubyte NXUInt8;
typedef sshort NXInt16;
typedef ushort NXUInt16;
typedef sint NXInt32;
typedef uint NXUInt32;
typedef sllong NXInt64;
typedef ullong NXUInt64;