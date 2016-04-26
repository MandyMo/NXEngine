/*
 *  File:    NXMutex.cpp
 *  author:  张雄
 *  date:    2016_04_26
 *  purpose: implement concrete platform mutex, android, iOS, OSX, Win32
 */

#include "../common/NXCore.h"
#include "NXMutex.h"

NX::Mutex::Mutex(){
    //empty here
}

NX::Mutex::~Mutex(){
    //empty here
}

NX::MutexWraper::MutexWraper(Mutex *pMutex):m_pMutex(pMutex){
    assert(m_pMutex);
    m_pMutex->Enter();
}

NX::MutexWraper::~MutexWraper(){
    assert(m_pMutex);
    m_pMutex->Leave();
}

#ifdef PLATFORM_OSX //compiled for OSX
#include <unistd.h>

namespace NX {
    class OSXMutex: public Mutex{
    public:
        OSXMutex();
        virtual ~OSXMutex();
    public:
        virtual void Enter();
        virtual void Leave();
        virtual bool TryEnter();
    private:
        pthread_mutex_t  m_pMutex;
    };
    
    OSXMutex::~OSXMutex(){
        //do nothing
    }
    
    OSXMutex::OSXMutex(){
        m_pMutex = PTHREAD_MUTEX_INITIALIZER;
    }
    
    void OSXMutex::Enter(){
        pthread_mutex_lock(&m_pMutex);
    }
    
    void OSXMutex::Leave(){
        pthread_mutex_unlock(&m_pMutex);
    }
    
    bool OSXMutex::TryEnter(){
        return pthread_mutex_trylock(&m_pMutex) == 0;
    }
    
    Mutex* Mutex::Create(){
        return new OSXMutex();
    }
}

#endif