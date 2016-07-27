/**
 *   File:     NXEventManager.h
 *
 *   Author:   张雄
 *   Date:     2016_07_27
 *   Purpose:  EventManager define
 */

#ifndef __ZX_NXENGINE_EVENT_MANAGER_H__
#define __ZX_NXENGINE_EVENT_MANAGER_H__

#include <unordered_map>
#include "NXEvent.h"

namespace NX {
    class EventManager{
        friend int  SendEvent(EventID eventId);
        friend bool SendEventToHandler(EventID eventId, EventHandler& eventHandler);
        friend int  RegisterEvent(EventID eventId);
        friend int  RegisterEvent(EventID eventId, Event* event);
        friend int  AttachEventHandler(EventID eventId, EventHandler& eventHandler);
        friend int  DetachEventHandler(EventID eventId, EventHandler& eventHandler);
        
    public:
        EventManager();
        virtual ~EventManager();
    
    public:
        static EventManager& Instance();
        static EventID GenEventID();
        
    public:
        int GetEventCount();
        int GetEventListenerCount(EventID eventId);
        Event* GetEventById(EventID eventId);
        
    public:
        int SendEvent(EventID eventId);
        bool SendEventToHandler(EventID eventId, EventHandler& eventHandler);
        int RegisterEvent(EventID eventId);
        int RegisterEvent(EventID eventId, Event* event);
        int AttachEventHandler(EventID eventId, EventHandler& eventHandler);
        int DetachEventHandler(EventID eventId, EventHandler& eventHandler);

    private:
        std::unordered_map<EventID, Event*>	 m_eventMap;
    };
    
    inline int SendEvent(EventID eventId){
        EventManager &manager = EventManager::Instance();
        return manager.SendEvent(eventId);
    }
    
    inline bool SendEventToHandler(EventID eventId, EventHandler& eventHandler){
        EventManager &manager = EventManager::Instance();
        return manager.SendEventToHandler(eventId, eventHandler);
    }
    
    inline int RegisterEvent(EventID eventId){
        EventManager &manager = EventManager::Instance();
        return manager.RegisterEvent(eventId);
    }
    
    inline int  RegisterEvent(EventID eventId, Event* event){
        EventManager &manager = EventManager::Instance();
        return manager.RegisterEvent(eventId, event);
    }
    
    inline int AttachEventHandler(EventID eventId, EventHandler& eventHandler){
        EventManager &manager = EventManager::Instance();
        return manager.AttachEventHandler(eventId, eventHandler);
    }
    
    inline int DetachEventHandler(EventID eventId, EventHandler& eventHandler){
        EventManager &manager = EventManager::Instance();
        return manager.DetachEventHandler(eventId, eventHandler);
    }
}

#endif