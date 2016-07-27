/**
 *   File:     NXTimerEvent.cpp
 *
 *   Author:   张雄
 *   Date:     2016_07_27
 *   Purpose:  implement timerevent
 */

#include "NXTimerEvent.h"
#include "NXTimerManager.h"

NX::TimerEvent::TimerEvent(const int iTickDelta, const NX::EventID eventId): NX::NXTick(iTickDelta), NX::Event(eventId){
    /*empty*/
}

NX::TimerEvent::~TimerEvent(){
    /*empty*/
}

int NX::TimerEvent::Release(){
    int iRefCount = GetRefCount();
    /**
     *  will be deleted
     */
    if(iRefCount == 1){
        NX::TimerManager::Instance().RemoveTimer(GetEventId());
    }
    return NX::Event::Release();
}

bool NX::TimerEvent::Tick(const int iDeltaTime){
    bool bTicked = NX::NXTick::Tick(iDeltaTime);
    if(bTicked){
        NX::SendEvent(GetEventId());
    }
    return bTicked;
}