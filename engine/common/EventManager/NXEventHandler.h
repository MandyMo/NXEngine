/**
 *   File:     NXEventHandler.h
 *
 *   Author:   张雄
 *   Date:     2016_07_27
 *   Purpose:  define eventhandler interface for event system used
 */


#ifndef __ZX_NXENGINE_EVENTHANDLER_H__
#define __ZX_NXENGINE_EVENTHANDLER_H__

#include "../NXCore.h"
#include "../NXUtility.h"

namespace NX {
    class Event;
    
    class EventHandler: public NX::NXRef{
    public:
        virtual ~EventHandler(){}
    public:
        virtual bool HandleEvent(Event *pEvent) = 0;
    };
}

#endif