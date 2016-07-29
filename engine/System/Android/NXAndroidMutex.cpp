/*
 *  File:    NXAndroidMutex.cpp
 *
 *  Date:    2016_07_29
 *  Author:  张雄
 *  purpose: Android mutex define
 */

#include "../NXMutex.h"

#ifdef PLATFORM_ANDROID

#include <unistd.h>

namespace NX {
    class AndroidMutex: public Mutex{
    public:
        AndroidMutex();
        virtual ~AndroidMutex();
    public:
        virtual void Enter();
        virtual void Leave();
        virtual bool TryEnter();
    private:
        pthread_mutex_t  m_pMutex;
    };
    
    AndroidMutex::~AndroidMutex(){
        //do nothing
    }
    
    AndroidMutex::AndroidMutex(){
        m_pMutex = PTHREAD_MUTEX_INITIALIZER;
    }
    
    void AndroidMutex::Enter(){
        pthread_mutex_lock(&m_pMutex);
    }
    
    void AndroidMutex::Leave(){
        pthread_mutex_unlock(&m_pMutex);
    }
    
    bool AndroidMutex::TryEnter(){
        return pthread_mutex_trylock(&m_pMutex) == 0;
    }
    
    Mutex* Mutex::Create(){
        return new AndroidMutex();
    }
}

#endif //PLATFORM_ANDROID