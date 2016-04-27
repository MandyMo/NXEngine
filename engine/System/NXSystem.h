/*
 *  File:    NXSystem.h
 *  author:  张雄
 *  date:    2016_04_27
 *  purpose: define a general interface for some system relative call
 */
#include "../common/NXCore.h"

namespace NX {
    class System{
    public:
        System();
        virtual ~System() = 0;
        static System& Instance();
    public:
        virtual void Sleep(__in const unsigned int iMilliSeconds) = 0;
    };
}