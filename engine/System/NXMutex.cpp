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

void NX::Mutex::Destroy(__in Mutex * const pMutex){
    delete pMutex;
}

NX::MutexWraper::MutexWraper(Mutex *pMutex):m_pMutex(pMutex){
    assert(m_pMutex);
    m_pMutex->Enter();
}

NX::MutexWraper::~MutexWraper(){
    assert(m_pMutex);
    m_pMutex->Leave();
}

/**
 *  compiled for MAC OSX only
 */
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

#endif

/**
 *  compiled for iOS only
 */
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


/**
 *  compiled for Android only
 */
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

#endif

/**
 *  compiled for windows only
 */
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
        //do nothing
    }
    
    WinMutex::WinMutex(){
        ::InitializeCriticalSection(&m_CriticalSection);
    }
    
    void WinMutex::Enter(){
        EnterCriticalSection(&m_CriticalSection);
    }
    
    void WinMutex::Leave(){
        LeaveCriticalSection(&m_CriticalSection);
    }
    
    bool WinMutex::TryEnter(){
        return ::TryEnterCriticalSection(&m_CriticalSection);
    }
    
    Mutex* Mutex::Create(){
        return new WinMutex();
    }
}

#endif