/*
 *  File:    NXiOSMutex.cpp
 *
 *  Date:    2016_07_29
 *  Author:  张雄
 *  purpose: iOS mutex define
 */

#include "../NXMutex.h"

#ifdef PLATFORM_IOS

#include <unistd.h>

namespace NX {
    class IOSMutex: public Mutex{
    public:
        IOSMutex();
        virtual ~IOSMutex();
    public:
        virtual void Enter();
        virtual void Leave();
        virtual bool TryEnter();
    private:
        pthread_mutex_t  m_pMutex;
    };
    
    IOSMutex::~IOSMutex(){
        //do nothing
    }
    
    IOSMutex::IOSMutex(){
        m_pMutex = PTHREAD_MUTEX_INITIALIZER;
    }
    
    void IOSMutex::Enter(){
        pthread_mutex_lock(&m_pMutex);
    }
    
    void IOSMutex::Leave(){
        pthread_mutex_unlock(&m_pMutex);
    }
    
    bool IOSMutex::TryEnter(){
        return pthread_mutex_trylock(&m_pMutex) == 0;
    }
    
    Mutex* Mutex::Create(){
        return new IOSMutex();
    }
}

#endif