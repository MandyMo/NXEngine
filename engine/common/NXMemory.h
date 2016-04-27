/*
 *  File:     NXMemory.h
 *  Author:   张雄
 *  Date:     2016_04_27
 *  Purpose:  memory relatived functions
 */


#include "NXCore.h"

namespace NX {
    class MemoryManager{
    public:
        MemoryManager();
        virtual ~MemoryManager();
        static MemoryManager& Instance();
    public:
        void* FixedAlloc(__in const int iMemSize, __in const int iAlignSize);
        void  FixedDelloc(__in const void * const pFixedAddress);
    };
}
