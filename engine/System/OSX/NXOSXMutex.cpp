/*
 *  File:    NXOSXMutex.cpp
 *
 *  Date:    2016_07_29
 *  Author:  张雄
 *  purpose: OSX mutex define
 */

#include "../NXMutex.h"

#ifdef PLATFORM_OSX

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
        pthread_mutex_destroy(&m_pMutex);
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

#endif //PLATFORM_OSX