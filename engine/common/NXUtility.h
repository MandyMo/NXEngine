/*
 *  File:     NXUtility.h
 *  Author:   张雄
 *  Date:     2016_06_14
 *  Purpose:  四元组，三元组，二元组等以及一些辅助函数
 */

#ifndef __ZX_NXENGINE_UTILITY_H__
#define __ZX_NXENGINE_UTILITY_H__

#include "NXCore.h"

namespace NX {
    //===============================================begin pair=========================================================
    template<typename A, typename B>
    class NXPair{
    public:
        template<typename RA, typename RB>
        NXPair(const RA &_first, const RB& _second): first(_first), second(_second){/*empty*/}
        
        template<typename RA, typename RB>
        NXPair(const NXPair<RA, RB> &other): first(other.first), second(other.second){/*empty*/}
        
        NXPair(){/*empty*/}
    
    public:
        template<typename RA, typename RB>
        NXPair& operator = (const NXPair<RA, RB> &other){
            first  = other.first;
            second = other.second;
            return *this;
        }
        
    public:
        A& First(){
            return first;
        }
        
        A First() const{
            return first;
        }
        
        B& Second(){
            return second;
        }
        
        B Second() const{
            return second;
        }
        
    public:
        A              first;
        B              second;
    };
    
    template<typename A, typename B, typename RA, typename RB>
    bool operator == (const NXPair<A, B> &a, const NXPair<RA, RB> &b){
        return a.first == b.first && a.second == b.second;
    }
    
    template<typename A, typename B>
    NXPair<A, B> MakePair(const A &_first, const B &_second){
        return NXPair<A, B>(_first, _second);
    }
    //=================================================end pair=========================================================
    
    //===============================================begin triple=======================================================
    template<typename A, typename B, typename C>
    class NXTriple{
    public:
        template<typename RA, typename RB, typename RC>
        NXTriple(const RA &_first, const RB& _second, const RC &_third): first(_first), second(_second), third(_third){/*empty*/}
        
        template<typename RA, typename RB, typename RC>
        NXTriple(const NXTriple<RA, RB, RC> &other): first(other.first), second(other.second), third(other.third){/*empty*/}
        
        NXTriple(){/*empty*/}
        
    public:
        template<typename RA, typename RB, typename RC>
        NXTriple& operator = (const NXTriple<RA, RB, RC> &other){
            first  = other.first;
            second = other.second;
            third  = other.third;
            return *this;
        }
        
    public:
        A& First(){
            return first;
        }
        
        A First() const{
            return first;
        }
        
        B& Second(){
            return second;
        }
        
        B Second() const{
            return second;
        }
        
        C& Third(){
            return third;
        }
        
        C Third() const{
            return third;
        }
    public:
        A              first;
        B              second;
        C              third;
    };
    
    template<typename A, typename B, typename C, typename RA, typename RB, typename RC>
    bool operator == (const NXTriple<A, B, C> &a, const NXTriple<RA, RB, RC> &b){
        return a.first == b.first && a.second == b.second && a.third == b.third;
    }
    
    template<typename A, typename B, typename C>
    NXTriple<A, B, C> MakePair(const A &_first, const B &_second, const C &_third){
        return NXTriple<A, B, C>(_first, _second, _third);
    }
    //=================================================end triple=======================================================
    
    
    //===============================================begin quadruples===================================================
    template<typename A, typename B, typename C, typename D>
    class NXQuadruples{
    public:
        template<typename RA, typename RB, typename RC, typename RD>
        NXQuadruples(const RA &_first, const RB& _second, const RC &_third, const RD &_fourth): first(_first), second(_second), third(_third), fourth(_fourth){/*empty*/}
        
        template<typename RA, typename RB, typename RC, typename RD>
        NXQuadruples(const NXQuadruples<RA, RB, RC, RD> &other): first(other.first), second(other.second), third(other.third), fourth(other.fourth){/*empty*/}
        
        NXQuadruples(){/*empty*/}
        
    public:
        template<typename RA, typename RB, typename RC, typename RD>
        NXQuadruples& operator = (const NXQuadruples<RA, RB, RC, RD> &other){
            first  = other.first;
            second = other.second;
            third  = other.third;
            fourth = other.fourth;
            return *this;
        }
        
    public:
        A& First(){
            return first;
        }
        
        A First() const{
            return first;
        }
        
        B& Second(){
            return second;
        }
        
        B Second() const{
            return second;
        }
        
        C& Third(){
            return third;
        }
        
        C Third() const{
            return third;
        }
        
        D& Fourth(){
            return fourth;
        }
        
        D Fourth() const{
            return fourth;
        }
        
    public:
        A              first;
        B              second;
        C              third;
        D              fourth;
    };
    
    template<typename A, typename B, typename C, typename D, typename RA, typename RB, typename RC, typename RD>
    bool operator == (const NXQuadruples<A, B, C, D> &a, const NXQuadruples<RA, RB, RC, RD> &b){
        return a.first == b.first && a.second == b.second && a.third == b.third && a.fourth == b.fourth;
    }
    
    template<typename A, typename B, typename C, typename D>
    NXQuadruples<A, B, C, D> MakePair(const A &_first, const B &_second, const C &_third, const D & _fourth){
        return NXQuadruples<A, B, C, D>(_first, _second, _third, _fourth);
    }
    //=================================================end quadruples===================================================
    
    class NXIUnknow{
    public:
        NXIUnknow() {}
        virtual ~NXIUnknow() {}
        
    public:
        virtual int GetRefCount() = 0;
        virtual int AddRef()      = 0;
        virtual int Release()     = 0;
    };
    
    class NXRef: public NXIUnknow{
    public:
        NXRef(){
            m_iRefCount = 1;
        }
        
        virtual ~NXRef() {}
        
    public:
        virtual int GetRefCount(){
            return m_iRefCount;
        }
        
        virtual int AddRef(){
            return ++m_iRefCount;
        }
        
        virtual int Release(){
            if(--m_iRefCount == 0){
                delete this;
            }
            return m_iRefCount;
        }
        
    private:
        int   m_iRefCount;
    };
    
    class NXCounter{
    public:
        explicit NXCounter(const int iTickDelta): m_iTickDelta(iTickDelta), m_iTimeSinceLastTick(0){}
        ~NXCounter() {}
    public:
        bool Tick(const int DeltaTime){
            m_iTimeSinceLastTick += DeltaTime;
            if(m_iTickDelta && m_iTimeSinceLastTick >= m_iTickDelta){
                m_iTimeSinceLastTick -= m_iTickDelta;
                return true;
            }
            return false;
        }
    private:
        int  m_iTickDelta;
        int  m_iTimeSinceLastTick;
    };
    
    class NXTick{
    public:
        explicit NXTick(const int iTickDelta): m_iTickDelta(iTickDelta), m_iTimeSinceLastTick(0){}
        virtual ~NXTick() {}
    public:
        virtual bool Tick(const int DeltaTime){
            m_iTimeSinceLastTick += DeltaTime;
            if(m_iTickDelta && m_iTimeSinceLastTick >= m_iTickDelta){
                m_iTimeSinceLastTick -= m_iTickDelta;
                return true;
            }
            return false;
        }
    private:
        int  m_iTickDelta;
        int  m_iTimeSinceLastTick;
    };
    
    NXUInt64 NXEncodePermutation(int * pPos, int len);
    std::vector<int> NXDecodePermutation(int iRanked, int len);
    
    //random shuffle range [begin, end)
    template<typename RandomAccessIterator>
    void NXRandomShuffle(RandomAccessIterator begin, RandomAccessIterator end){
        int len = end - begin;
        while(len){
            std::swap(*begin, *(begin + std::rand() % len--));
        }
    }
    
    
    std::string  EncodeBase64(const std::string &src);
    std::string  DecodeBase64(const std::string &src);
    std::string  Encrpt(const std::string &src);
    std::string  Decrpt(const std::string &src);
    std::string  DecrptFromFile(const std::string &strSrcFile, const std::string &strDstFile);
    std::string  EncrptFromFile(const std::string &strSrcFile, const std::string &strDstFile);
}


#endif
