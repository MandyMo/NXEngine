/*
 *  File:    NXWinMutex.cpp
 *
 *  Date:    2016_07_29
 *  Author:  张雄
 *  purpose: Win mutex define
 */

#include "../NXMutex.h"

#ifdef PLATFORM_WINDOWS

#include <windows.h>

namespace NX {
    class WinMutex: public Mutex{
    public:
        WinMutex();
        virtual ~WinMutex();
    public:
        virtual void Enter();
        virtual void Leave();
        virtual bool TryEnter();
    private:
        CRITICAL_SECTION  m_CriticalSection;
    };
    
    WinMutex::~WinMutex(){
        ::DeleteCriticalSection(&m_CriticalSection);
    }
    
    WinMutex::WinMutex(){
        ::InitializeCriticalSection(&m_CriticalSection);
    }
    
    void WinMutex::Enter(){
        ::EnterCriticalSection(&m_CriticalSection);
    }
    
    void WinMutex::Leave(){
        ::LeaveCriticalSection(&m_CriticalSection);
    }
    
    bool WinMutex::TryEnter(){
        return ::TryEnterCriticalSection(&m_CriticalSection);
    }
    
    Mutex* Mutex::Create(){
        return new WinMutex();
    }
}

#endif