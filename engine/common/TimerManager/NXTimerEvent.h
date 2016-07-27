/**
 *   File:     NXTimerEvent.h
 *
 *   Author:   张雄
 *   Date:     2016_07_27
 *   Purpose:  define timerevent interface
 */


#ifndef __NX_NXENGINE_TIMER_EVENT_H__
#define __NX_NXENGINE_TIMER_EVENT_H__

#include "../NXUtility.h"
#include "../EventManager/NXEvent.h"

namespace NX {
    class TimerEvent : public NX::Event, public NX::NXTick{
    public:
        TimerEvent(const int iTickDelta, const NX::EventID eventId);
        virtual ~TimerEvent();
    public:
        virtual int Release();
        virtual bool Tick(const int iDeltaTime);
    };
}

#endif