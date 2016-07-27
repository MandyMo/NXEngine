/**
 *   File:     NXEvent.h
 *
 *   Author:   张雄
 *   Date:     2016_07_27
 *   Purpose:  define event interface
 */

#ifndef __ZX_NXENGINE_EVENT_H__
#define __ZX_NXENGINE_EVENT_H__

#include <vector>

#include "NXUtility.h"

namespace NX {
    typedef long long EventID;
    
    class EventHandler;
    
    class Event: public NX::NXRef{
    public:
        explicit Event(const EventID id);
        virtual ~Event();
        
    public:
        EventID  GetEventId();
        int    AttatchEventHandler(EventHandler * handler);
        int    DetachEventHandler(EventHandler * handler);
        int    GetListenerCount();
        bool   SendEvent(EventHandler *handler);
        int    SendEvent();
        
    private:
        EventID                  m_id;
        std::vector<EventHandler*>   m_vEventLisener;
    };
}

#endif