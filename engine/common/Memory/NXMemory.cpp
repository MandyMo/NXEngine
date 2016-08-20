/*
 *  File:     NXMemory.h
 *  Author:   张雄
 *  Date:     2016_04_27
 *  Purpose:  memory relatived functions
 */

#include "NXMemory.h"


NX::MemoryManager::MemoryManager(){
    //empty here
}

NX::MemoryManager::~MemoryManager(){
    //empty here
}

NX::MemoryManager& NX::MemoryManager::Instance(){
    static MemoryManager SharedObject;
    return SharedObject;
}

void* NX::MemoryManager::FixedAlloc(__in const int iMemSize, __in const int iAlignSize){
    NXAssert(iAlignSize > 1 && !(iAlignSize & (iAlignSize - 1)));
    //expand memory size
    int iFinalSize       = iMemSize + iAlignSize + sizeof(void*);
    ullong  StartAddress = (ullong)malloc(iFinalSize);
    if(StartAddress == 0){
        return NULL;
    }
    ullong  Address           = (StartAddress + sizeof(void*) + iAlignSize) & ~(iAlignSize - 1);
    *(((ullong*)Address) - 1) = StartAddress;
    return (void*)Address;
}

void NX::MemoryManager::FixedDelloc(__in const void * const pFixedAddress){
    NXAssert(pFixedAddress);
    if(!pFixedAddress){
        return;
    }
    ullong *pAddress             = ((ullong*)pFixedAddress) - 1;
    void * pStartAddress         = (void*)*pAddress;
    free(pStartAddress);
}

void* NX::MemoryManager::AllocBuffer(__in const NXUInt64 iMemSize){
    return malloc(iMemSize);
}

void NX::MemoryManager::FreeBuffer(const void * const pAddress){
    free((void*)pAddress);
}