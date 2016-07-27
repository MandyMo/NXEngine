/**
 *   File:     NXEventManager.h
 *
 *   Author:   张雄
 *   Date:     2016_07_27
 *   Purpose:  EventManager implement
 */

#include "NXEventManager.h"

NX::EventManager& NX::EventManager::Instance(){
    static NX::EventManager SharedObject;
    return SharedObject;
}

NX::EventID NX::EventManager::GenEventID(){
    static NX::EventID id = 0;
    return ++id;
}

int NX::EventManager::GetEventCount(){
    return (int)m_eventMap.size();
}

int NX::EventManager::GetEventListenerCount(NX::EventID eventId){
    if(!m_eventMap.count(eventId)){
        return 0;
    }
    return m_eventMap[eventId]->GetListenerCount();
}

NX::Event* NX::EventManager::GetEventById(NX::EventID eventId){
    if(!m_eventMap.count(eventId)){
        return NULL;
    }
    NX::Event * event = m_eventMap[eventId];
    if(event){
        event->AddRef();
    }
    return event;
}

NX::EventManager::EventManager(){
    /*empty*/
}

NX::EventManager::~EventManager(){
    for(auto iter = m_eventMap.begin(); iter != m_eventMap.end(); ++iter){
        NX::Event* pEvent = iter->second;
        if (pEvent){
            pEvent->Release();
            iter->second = NULL;
        }
    }
    m_eventMap.clear();
}

int NX::EventManager::SendEvent(NX::EventID eventId){
    auto result = m_eventMap.find(eventId);
    NX::Event *pEvent = NULL;
    if (result != m_eventMap.end()){
        pEvent = result->second;
    }
    return pEvent ? pEvent->SendEvent() : 0;
}

bool NX::EventManager::SendEventToHandler(NX::EventID eventId, NX::EventHandler& eventHandler){
    auto result = m_eventMap.find(eventId);
    NX::Event *pEvent = NULL;
    if (result != m_eventMap.end()){
        if (result->second){
            pEvent = result->second;
        }
    }
    return pEvent ? pEvent->SendEvent(&eventHandler) : false;
}

int NX::EventManager::RegisterEvent(NX::EventID eventId){
    auto result = m_eventMap.find(eventId);
    if (result == m_eventMap.end()){
        NX::Event* pEvent = new NX::Event(eventId);
        m_eventMap[eventId] = pEvent;
    }
    return (int)m_eventMap.size();
}

int NX::EventManager::RegisterEvent(NX::EventID eventId, Event *event){
    event->AddRef();
    if(m_eventMap.count(eventId)){
        if(m_eventMap[eventId]){
            m_eventMap[eventId]->Release();
        }
    }
    m_eventMap[eventId] = event;
    return (int)m_eventMap.size();
}

int NX::EventManager::AttachEventHandler(NX::EventID eventId, NX::EventHandler& eventHandler){
    auto result = m_eventMap.find(eventId);
    NX::Event *pEvent = NULL;
    if (result != m_eventMap.end()){
        pEvent = result->second;
    }
    return pEvent ? pEvent->AttatchEventHandler(&eventHandler) : 0;
}

int NX::EventManager::DetachEventHandler(NX::EventID eventId, NX::EventHandler& eventHandler){
    auto result = m_eventMap.find(eventId);
    NX::Event *pEvent = NULL;
    assert(result != m_eventMap.end());
    if (result != m_eventMap.end()){
        pEvent = result->second;
    }
    
    int iHandlercount = 0;
    
    /**
     *  no handler exist, then remove event
     */
    if(pEvent && !(iHandlercount = pEvent->DetachEventHandler(&eventHandler))){
        pEvent->Release();
        m_eventMap.erase(eventId);
    }
    
    return iHandlercount;
}