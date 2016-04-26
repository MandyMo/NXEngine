/*
 *  File:    NXMutex.h
 *  author:  张雄
 *  date:    2016_04_26
 *  purpose: define a general mutex interface
 */

#ifndef __ZX_NXENGINE_MUTEX_H__
#define __ZX_NXENGINE_MUTEX_H__

namespace NX {
    class Mutex{
    public:
        Mutex();
        virtual ~Mutex() = 0;
    public:
        static Mutex* Create();
    public:
        virtual void Enter()    = 0;
        virtual void Leave()    = 0;
        virtual bool TryEnter() = 0;
    };
    
    class MutexWraper{
    public:
        MutexWraper(Mutex *pMutex);
        ~MutexWraper();
    private:
        Mutex *m_pMutex;
    };
}



#endif  //!__ZX_NXENGINE_MUTEX_H__