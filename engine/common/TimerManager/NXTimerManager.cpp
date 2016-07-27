/**
 *   File:     NXTimerManager.cpp
 *
 *   Author:   张雄
 *   Date:     2016_07_27
 *   Purpose:  implement TimerManager
 */


#include "NXTimerManager.h"
#include "NXTimerEvent.h"

NX::TimerManager::TimerManager(){
    /*empty*/
}

NX::TimerManager::~TimerManager(){
    /*empty*/
}

NX::TimerManager& NX::TimerManager::Instance(){
    static NX::TimerManager SharedObject;
    return SharedObject;
}


void NX::TimerManager::Tick(const int iDeltaTime){
    for(auto it = m_EventId2Time.begin(); it != m_EventId2Time.end(); ++it){
        NX::EventID eventId = it->first;
        NX::NXTick * ticker = dynamic_cast<NX::NXTick*>(NX::EventManager::Instance().GetEventById(eventId));
        if(ticker){
            ticker->Tick(iDeltaTime);
        }
    }
}

int  NX::TimerManager::RemoveTimer(NX::EventID eventId){
    if(m_EventId2Time.count(eventId)){
        int iTime = m_EventId2Time[eventId];
        m_Time2EventId.erase(iTime);
        m_EventId2Time.erase(eventId);
    }
    return (int)m_EventId2Time.size();
}

int  NX::TimerManager::SendTimerEvent(int iTime){
    if(m_Time2EventId.count(iTime)){
        NX::EventID eventId = m_Time2EventId[iTime];
        return NX::SendEvent(eventId);
    }
    return 0;
}

bool NX::TimerManager::SendTimerEventToHandler(int iTime, EventHandler& eventHandler){
    if(m_Time2EventId.count(iTime)){
        NX::EventID eventId = m_Time2EventId[iTime];
        return NX::SendEventToHandler(eventId, eventHandler);
    }
    return 0;
}

int NX::TimerManager::AttachTimerEventHandler(int iTime, EventHandler& eventHandler){
    if(m_Time2EventId.count(iTime)){
        NX::EventID eventId = m_Time2EventId[iTime];
        return NX::AttachEventHandler(eventId, eventHandler);
    }else{
        NX::EventID eventId = NX::EventManager::GenEventID();
        m_Time2EventId[iTime]   = eventId;
        m_EventId2Time[eventId] = iTime;
        NX::TimerEvent * event = new NX::TimerEvent(iTime, eventId);
        NX::RegisterEvent(eventId, event);
        return NX::AttachEventHandler(eventId, eventHandler);
    }
}

int NX::TimerManager::DetachTimerEventHandler(int iTime, EventHandler& eventHandler){
    if(m_Time2EventId.count(iTime)){
        NX::EventID eventId = m_Time2EventId[iTime];
        return NX::DetachEventHandler(eventId, eventHandler);
    }
    return 0;
}