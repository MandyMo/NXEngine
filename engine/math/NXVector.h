/*
 *  File:    NXVector.h
 *  author:  张雄
 *  date:    2016_02_22
 *  purpose: 定义3d数学的vector，注意，此vector只适合于存储简单的内置基本类型，若存放class和struct类型，请不要使用。
 */

#ifndef __ZX_NXENGINE_VECTOR_H__
#define __ZX_NXENGINE_VECTOR_H__

#include "NXCore.h"
#include "NXNumeric.h"
#include "NXMath.h"

namespace NX {
    template<typename T, int Scale>
    class vector{
    public:
        vector(){
            std::memset(v, 0, sizeof(v));
        }
        
        vector(const T* ptr){
            Set(ptr);
        }
        
        vector(const vector<T, Scale> &rhs){
            std::memcpy(v, rhs.v, sizeof(v));
        }
        
        template<typename U>
        vector(const vector<U, Scale> &rhs){
            for(int i = 0; i < Scale; ++i){
                v[i] = rhs.v[i];
            }
        }
        
        vector(const T value){
            for(int i = 0; i < Scale; ++i){
                v[i] = value[i];
            }
        }
    public:
        vector<T, Scale>& operator - (){
            for(int i = 0; i < Scale; ++i){
                v[i] = -v[i];
            }
            return *this;
        }
        T& operator[] (const int index){
            NXAssert(index >= 0 && index < Scale);
            return v[index];
        }
        
        const T operator[] (const int index) const{
            NXAssert(index >= 0 && index < Scale);
            return v[index];
        }
        
        void Set(const T* ptr){
            std::memcpy(v, ptr, sizeof(v));
        }
        
        vector<T, Scale>& operator = (const vector<T, Scale> &rhs){
            std::memcpy(v, rhs.v, sizeof(v));
            return *this;
        }
        
        template<typename U>
        vector<T, Scale>& operator = (const vector<U, Scale> &rhs){
            for(int i = 0; i < Scale; ++i){
                v[i] = rhs.v[i];
            }
            return *this;
        }
        
        template<typename U, int CC>
        vector<T, Scale>& operator = (const vector<U, CC> &rhs){
            for(int i = 0, l = NXMin(CC, Scale); i < l; ++i){
                v[i] = rhs.v[i];
            }
            return *this;
        }
        
        template<typename U>
        vector<T, Scale>& operator *= (const vector<U, Scale> &rhs){
            for(int i = 0; i < Scale; ++i){
                v[i] *= rhs.v[i];
            }
            return *this;
        }
        
        template<typename U>
        vector<T, Scale>& operator /= (const vector<U, Scale> &rhs){
            for(int i = 0; i < Scale; ++i){
                v[i] /= rhs.v[i];
            }
            return *this;
        }
        
        template<typename U>
        vector<T, Scale>& operator += (const vector<U, Scale> &rhs){
            for(int i = 0; i < Scale; ++i){
                v[i] += rhs.v[i];
            }
            return *this;
        }
        
        vector<T, Scale>& operator += (const T value){
            for(int i = 0; i < Scale; ++i){
                v[i] += value;
            }
            return *this;
        }
        
        
        template<typename U>
        vector<T, Scale>& operator -= (const vector<U, Scale> &rhs){
            for(int i = 0; i < Scale; ++i){
                v[i] -= rhs.v[i];
            }
            return *this;
        }
        
        vector<T, Scale>& operator -= (const T value){
            for(int i = 0; i < Scale; ++i){
                v[i] -= value;
            }
            return *this;
        }
        
        vector<T, Scale>& operator = (const T value){
            for(int i = 0; i < Scale; ++i){
                v[i] = value;
            }
            return *this;
        }
        
        vector<T, Scale>& operator *= (const T value){
            for(int i = 0; i < Scale; ++i){
                v[i] *= value;
            }
            return *this;
        }
        
        vector<T, Scale>& operator /= (const T value){
            for(int i = 0; i < Scale; ++i){
                v[i] /= value;
            }
            return *this;
        }
    public:
        T v[Scale];
    };
    
    template<typename T>
    class vector<T, 0>{
#pragma error "invalid parameter for tempate with 0 to be the size"
    };
    
    template<typename T>
    class vector<T, 1>{
    public:
        vector():x(T()){}
        vector(const T* ptr){
            Set(ptr);
        }
        vector(const T value):x(value)                 {  }
        
        vector(const vector<T, 1> &rhs):x(rhs.x)        {  }
        
        template<typename U>
        vector(const vector<U, 1> &rhs):x(rhs.x)        {  }
        
        template<typename U, int CC>
        vector(const vector<U, CC> & rhs):x(rhs.v[0])   {  }
    public:
        vector<T, 1>& operator - (){
            x = -x;
            return *this;
        }
        T& operator[] (const int index){
            NXAssert(index < 1 && index >= 0);
            return v[index];
        }
        
        const T operator[] (const int index) const{
            NXAssert(index >= 0 && index < 1);
            return v[index];
        }
        
        void Set(const T value){
            x = value;
        }
        
        void Set(const T* ptr){
            v[0] = ptr[0];
        }
        
        vector<T, 1>& operator = (const vector<T, 1> &rhs){
            v[0] = rhs.v[0];
            return *this;
        }
        
        template<typename U>
        vector<T, 1>& operator = (const vector<U, 1> &rhs){
            v[0] = rhs.v[0];
            return *this;
        }
        
        template<typename U, int CC>
        vector<T, 1>& operator = (const vector<U, CC> &rhs){
            NXAssert(CC >= 1);
            v[0] = rhs.v[0];
            return *this;
        }
        
        vector<T, 1>& operator = (const T value){
            x = value;
            return *this;
        }
        
        template<typename U>
        vector<T, 1>& operator += (const vector<U, 1> &rhs){
            x += rhs.x;
            return *this;
        }
        
        vector<T, 1>& operator += (const T value){
            x += value;
            return *this;
        }
        
        template<typename U>
        vector<T, 1>& operator -= (const vector<U, 1> &rhs){
            x -= rhs.x;
            return *this;
        }
        
        vector<T, 1>& operator -= (const T value){
            x -= value;
            return *this;
        }
        
        template<typename U>
        vector<T, 1>& operator *= (const vector<U, 1> &rhs){
            x *= rhs.x;
            return *this;
        }
        
        vector<T, 1>& operator *= (const T value){
            x *= value;
            return *this;
        }
        
        template<typename U>
        vector<T, 1>& operator /= (const vector<U, 1> &rhs){
            x /= rhs.x;
            return *this;
        }
        
        vector<T, 1>& operator /= (const T value){
            x /= value;
            return *this;
        }
    public:
#pragma pack(1)
        union{
            T x;
            T r;
            T v[1];
        };
#ifdef _MSC_VER
#pragma pop()
#endif
    };
    
    template<typename T>
    class vector<T, 2>{
    public:
        vector():x(T()),y(T()){}
        vector(const T* ptr){
            Set(ptr);
        }
        vector(const T v1, const T v2):x(v1), y(v2){}
        
        vector(const vector<T, 2> &rhs):x(rhs.x), y(rhs.y){}
        
        template<typename U>
        vector(const vector<U, 2> &rhs):x(rhs.x), y(rhs.y){}
        
        vector(const T value):x(value), y(value){}
        
        template<typename U, int CC>
        vector(const vector<U, CC> &rhs){
            *this = rhs;
        }
    public:
        vector<T, 2>& operator - (){
            x = -x; y = -y;
            return *this;
        }
        T& operator[] (const int index){
            NXAssert(index < 2 && index >= 0);
            return v[index];
        }
        
        const T operator[] (const int index) const{
            NXAssert(index >= 0 && index < 2);
            return v[index];
        }
        
        void Set(const T v1, const T v2){
            x = v1;
            y = v2;
        }
        void Set(const T* ptr){
            v[0] = ptr[0], v[1] = ptr[1];
        }
    public:
        template<typename U>
        vector<T, 2>& operator = (const vector<U, 2> & rhs){
            v[0] = rhs.v[0];
            v[1] = rhs.v[1];
            return *this;
        }
        template<typename U, int CC>
        vector<T, 2>& operator = (const vector<U, CC> &rhs){
            for(int i = 0, l = NXMin(CC, 2); i < l; ++i){
                v[i] = rhs.v[i];
            }
            return *this;
        }
        vector<T, 2>& operator = (const T value){
            x = y = value;
            return *this;
        }
        
        template<typename U>
        vector<T, 2>& operator += (const vector<U, 2> &rhs){
            x += rhs.x;
            y += rhs.y;
            return *this;
        }
        
        vector<T, 2>& operator += (const T value){
            x += value;
            y += value;
            return *this;
        }
        
        template<typename U>
        vector<T, 2>& operator -= (const vector<U, 2> &rhs){
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }
        
        vector<T, 2>& operator -= (const T value){
            x -= value;
            y -= value;
            return *this;
        }
        
        template<typename U>
        vector<T, 2>& operator *= (const vector<U, 2> &rhs){
            x *= rhs.x;
            y *= rhs.y;
            return *this;
        }
        
        vector<T, 2>& operator *= (const T value){
            x *= value;
            y *= value;
            return *this;
        }
        
        template<typename U>
        vector<T, 2>& operator /= (const vector<U, 2> &rhs){
            x /= rhs.x;
            y /= rhs.y;
            return *this;
        }
        
        vector<T, 2>& operator /= (const T value){
            x /= value;
            y /= value;
            return *this;
        }
    public:
#pragma pack(1)
        union{
            struct{
                T x;
                T y;
            };
            struct{
                T r;
                T g;
            };
            struct{
                T v[2];
            };
        };
#ifdef _MSC_VER
#pragma pop()
#endif
    };

    template<typename T>
    class vector<T, 3>{
    public:
        vector():x(T()), y(T()), z(T()){}
        vector(const T* ptr){
            Set(ptr);
        }
        vector(const T v1, const T v2, const T v3):x(v1), y(v2), z(v3){}
        
        template<typename U>
        vector(const vector<U, 3> &rhs):x(rhs.x), y(rhs.y), z(rhs.z){}
        vector(const T v):x(v), y(v), z(v){}
        template<typename U, int CC>
        vector(const vector<U, CC> & rhs){
            *this = rhs;
        }
    public:
        vector<T, 3>& operator - (){
            x = -x; y = -y; z= -z;
            return *this;
        }
        T& operator[] (const int index){
            NXAssert(index < 3 && index >= 0);
            return v[index];
        }
        
        const T operator[] (const int index) const{
            NXAssert(index >= 0 && index < 3);
            return v[index];
        }
        
        void Set(const T v1, const T v2, const T v3){
            x = v1;
            y = v2;
            z = v3;
        }
        void Set(const T* ptr){
            v[0] = ptr[0], v[1] = ptr[1], v[2] = ptr[2];
        }
    public:
        template<typename U>
        vector<T, 3>& operator = (const vector<U, 3> & rhs){
            v[0] = rhs.v[0];
            v[1] = rhs.v[1];
            v[2] = rhs.v[2];
            return *this;
        }
        template<typename U, int CC>
        vector<T, 3>& operator = (const vector<U, CC> &rhs){
            for(int i = 0, l = NXMin(CC, 3); i < l; ++i){
                v[i] = rhs.v[i];
            }
            return *this;
        }
        
        vector<T, 3>& operator = (const T value){
            x = y = z = value;
            return *this;
        }
        
        template<typename U>
        vector<T, 3>& operator += (const vector<U, 3> &rhs){
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }
        
        vector<T, 3>& operator += (const T value){
            x += value;
            y += value;
            z += value;
            return *this;
        }
        
        template<typename U>
        vector<T, 3>& operator -= (const vector<U, 3> &rhs){
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            return *this;
        }
        
        vector<T, 3>& operator -= (const T value){
            x -= value;
            y -= value;
            z -= value;
            return *this;
        }
        
        template<typename U>
        vector<T, 3>& operator *= (const vector<U, 3> &rhs){
            x *= rhs.x;
            y *= rhs.y;
            z *= rhs.z;
            return *this;
        }
        
        vector<T, 3>& operator *= (const T value){
            x *= value;
            y *= value;
            z *= value;
            return *this;
        }
        
        template<typename U>
        vector<T, 3>& operator /= (const vector<U, 3> &rhs){
            x /= rhs.x;
            y /= rhs.y;
            z /= rhs.z;
            return *this;
        }
        
        vector<T, 3>& operator /= (const T value){
            x /= value;
            y /= value;
            z /= value;
            return *this;
        }
    public:
#pragma pack(1)
        union{
            struct{
                T x;
                T y;
                T z;
            };
            struct{
                T r;
                T g;
                T b;
            };
            struct{
                T v[3];
            };
        };
#ifdef _MSC_VER
#pragma pop()
#endif
    };
    
    template<typename T>
    class vector<T, 4>{
    public:
        vector():x(T()), y(T()), z(T()), w(T()){}
        vector(const T* ptr){
            Set(ptr);
        }
        vector(const T v):x(v), y(v), z(v), w(v){}
        vector(const T v1, const T v2, const T v3, const T v4):x(v1), y(v2), z(v3), w(v4){}
        
        template<typename U>
        vector(const vector<U, 4> &rhs):x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w){}
        
        template<typename U, int CC>
        vector(const vector<U, CC> & rhs){
            *this = rhs;
        }
    public:
        vector<T, 4>& operator - (){
            x = -x, y = -y, z = -z, w = -w;
            return *this;
        }
        T& operator[] (const int index){
            NXAssert(index < 4 && index >= 0);
            return v[index];
        }
        
        const T operator[] (const int index) const{
            NXAssert(index >= 0 && index < 4);
            return v[index];
        }
        
        void Set(const T v1, const T v2, const T v3, const T v4){
            x = v1;
            y = v2;
            z = v3;
            w = v4;
        }
        void Set(const T* ptr){
            v[0] = ptr[0], v[1] = ptr[1], v[2] = ptr[2], v[3] = ptr[3];
        }
    public:
        template<typename U>
        vector<T, 4>& operator = (const vector<U, 4> & rhs){
            v[0] = rhs.v[0], v[1] = rhs.v[1];
            v[2] = rhs.v[2], v[3] = rhs.v[3];
            return *this;
        }
        
        template<typename U, int CC>
        vector<T, 4>& operator = (const vector<U, CC> &rhs){
            for(int i = 0, l = NXMin(CC, 4); i < l; ++i){
                v[i] = rhs.v[i];
            }
            return *this;
        }
        
        vector<T, 4>& operator = (const T value){
            x = y = z = w = value;
            return *this;
        }
        
        template<typename U>
        vector<T, 4>& operator += (const vector<U, 4> &rhs){
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            w += rhs.w;
            return *this;
        }
        
        vector<T, 4>& operator += (const T value){
            x += value;
            y += value;
            z += value;
            w += value;
            return *this;
        }
        
        template<typename U>
        vector<T, 4>& operator -= (const vector<U, 4> &rhs){
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            w -= rhs.w;
            return *this;
        }
        
        vector<T, 4>& operator -= (const T value){
            x -= value;
            y -= value;
            z -= value;
            w -= value;
            return *this;
        }
        
        template<typename U>
        vector<T, 4>& operator *= (const vector<U, 4> &rhs){
            x *= rhs.x;
            y *= rhs.y;
            z *= rhs.z;
            w *= rhs.w;
            return *this;
        }
        
        vector<T, 4>& operator *= (const T value){
            x *= value;
            y *= value;
            z *= value;
            w *= value;
            return *this;
        }
        
        template<typename U>
        vector<T, 4>& operator /= (const vector<U, 4> &rhs){
            x /= rhs.x;
            y /= rhs.y;
            z /= rhs.z;
            w /= rhs.w;
            return *this;
        }
        
        vector<T, 4>& operator /= (const T value){
            x /= value;
            y /= value;
            z /= value;
            w /= value;
            return *this;
        }
    public:
#pragma pack(1)
        union{
            struct{
                T x;
                T y;
                T z;
                T w;
            };
            struct{
                T r;
                T g;
                T b;
                T a;
            };
            struct{
                T v[4];
            };
        };
#ifdef _MSC_VER
#pragma pop()
#endif
    };
    
    //==============================================begin nomember function=============================================
    template<typename T, int Scale>
    inline bool operator == (const vector<T, Scale> &lhs, const vector<T, Scale> &rhs);
    
    template<typename T, typename U, int Scale, typename RT = T>
    inline vector<RT, Scale> operator + (const vector<T, Scale> &lhs, const vector<U, Scale> &rhs);
    
    template<typename T, typename U, int Scale, typename RT = T>
    inline vector<RT, Scale> operator + (const vector<T, Scale> &lhs, const U value);
    
    template<typename T, typename U, int Scale, typename RT>
    inline vector<RT, Scale> operator + (const U value, const vector<T, Scale> &rhs);
    
    template<typename T, typename U, int Scale, typename RT = T>
    inline vector<RT, Scale> operator - (const vector<T, Scale> &lhs, const U value);
    
    template<typename T, typename U, int Scale, typename RT = T>
    inline vector<RT, Scale> operator - (const vector<T, Scale> &lhs, const vector<U, Scale> &rhs);
    
    template<typename T, typename U, int Scale, typename RT = T>
    inline vector<RT, Scale> operator - (const U value, const vector<T, Scale> &lhs);
    
    template<typename T, typename U, int Scale, typename RT = T>
    inline vector<RT, Scale> operator * (const vector<T, Scale> &lhs, const vector<U, Scale> &rhs);
    
    template<typename T, typename U, int Scale, typename RT = T>
    inline vector<RT, Scale> operator * (const vector<T, Scale> &lhs, const U value);
    
    template<typename T, typename U, int Scale, typename RT = T>
    inline vector<RT, Scale> operator * (const U value, const vector<T, Scale> &lhs);
    
    template<typename T, typename U, int Scale, typename RT = T>
    inline vector<RT, Scale> operator / (const vector<T, Scale> &lhs, const vector<U, Scale> &rhs);
    
    template<typename T, typename U, int Scale, typename RT = T>
    inline vector<RT, Scale> operator / (const vector<T, Scale> &lhs, const U value);
    
    template<typename T, typename U, int Scale, typename RT = T>
    inline vector<RT, Scale> operator / (const U value, const vector<T, Scale> &lhs);
    
    template<typename T, int Scale>
    inline bool operator != (const vector<T, Scale> &lhs, const vector<T, Scale> &rhs);
    
    template<typename T, int Scale>
    inline bool operator < (const vector<T, Scale> &lhs, const vector<T, Scale> &rhs);
    
    template<typename T, int Scale>
    inline bool operator <= (const vector<T, Scale> &lhs, const vector<T, Scale> &rhs);
    
    template<typename T, int Scale>
    inline bool operator > (const vector<T, Scale> &lhs, const vector<T, Scale> &rhs);
    
    template<typename T, int Scale>
    inline bool operator >= (const vector<T, Scale> &lhs, const vector<T, Scale> &rhs);
    
    template<int Scale>
    inline bool operator == (const vector<float, Scale> &lhs, const vector<float, Scale> &rhs);
    
    template<int Scale>
    inline bool operator == (const vector<double, Scale> &lhs, const vector<double, Scale> &rhs);
    //==============================================end of nomember function============================================
#include "NXVector.inl"
}

#endif