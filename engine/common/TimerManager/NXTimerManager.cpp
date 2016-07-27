/**
 *   File:     NXTimerManager.cpp
 *
 *   Author:   张雄
 *   Date:     2016_07_27
 *   Purpose:  implement TimerManager
 */


#include "NXTimerManager.h"
#include "NXTimerEvent.h"
#include "../../System/NXSystem.h"

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


int NX::TimerManager::Tick(const int iDeltaTime){
	int cTicked = 0;
    for(auto it = m_EventId2Time.begin(); it != m_EventId2Time.end(); ++it){
        NX::EventID eventId = it->first;
        NX::NXTick * ticker = dynamic_cast<NX::NXTick*>(NX::EventManager::Instance().GetEventById(eventId));
        if(ticker && ticker->Tick(iDeltaTime)){
            ++cTicked;
        }
    }
    return cTicked;
}

int NX::TimerManager::Tick(){
	static NXInt64 LastTimeTicked = NX::System::Instance().GetMillSecondsFromSystemStart();
	NXInt64 Now = NX::System::Instance().GetMillSecondsFromSystemStart();
	int iDeltaTime = Now - LastTimeTicked;
	LastTimeTicked = Now;
	return Tick(iDeltaTime);
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
        event->Release();
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
