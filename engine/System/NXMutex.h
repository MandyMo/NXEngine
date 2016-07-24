/*
 *  File:    NXMutex.h
 *
 *  author:  张雄
 *  date:    2016_04_26
 *  purpose: define a general mutex interface
 */

#ifndef __ZX_NXENGINE_MUTEX_H__
#define __ZX_NXENGINE_MUTEX_H__

#include "../common/NXCore.h"

namespace NX {
    class Mutex{
    public:
        Mutex();
        virtual ~Mutex() = 0;
    public:
        static Mutex* Create();
        static void Destroy(__in Mutex * const pMutex);
    public:
        /**
         *  Fetch lock
         */
        virtual void Enter()    = 0;
        
        /**
         *  Release lock
         */
        virtual void Leave()    = 0;
        
        /**
         *  try fetch lock
         *  <return value>
         *  false:   fetch failed, maybe lock has got by others
         *  true;    fetch succced
         */
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