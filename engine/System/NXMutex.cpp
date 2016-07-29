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
    NXAssert(m_pMutex);
    m_pMutex->Enter();
}

NX::MutexWraper::~MutexWraper(){
    NXAssert(m_pMutex);
    m_pMutex->Leave();
}