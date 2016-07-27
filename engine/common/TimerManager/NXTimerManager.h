/**
 *   File:     NXTimerManager.h
 *
 *   Author:   张雄
 *   Date:     2016_07_27
 *   Purpose:  define TimerManager interface
 */

#include <unordered_set>
#include <unordered_map>

#include "../EventManager/NXEvent.h"
#include "../NXUtility.h"
#include "../EventManager/NXEventManager.h"

namespace NX {
    class TimerManager{
        friend inline int  SendTimerEvent(int iTime);
        friend inline bool SendTimerEventToHandler(int iTime, EventHandler& eventHandler);
        friend inline int AttachTimerEventHandler(int iTime, EventHandler& eventHandler);
        friend inline int DetachTimerEventHandler(int iTime, EventHandler& eventHandler);
        friend inline int TickTimerManager(const int iDeltaTime);
        friend inline int TickTimerManager();
    public:
        TimerManager();
        virtual ~TimerManager();
        static TimerManager& Instance();
        
    public:
        int Tick();
        int Tick(const int iDeltaTime);
        int  RemoveTimer(NX::EventID eventId);
        int  SendTimerEvent(int iTime);
        bool SendTimerEventToHandler(int iTime, EventHandler& eventHandler);
        int AttachTimerEventHandler(int iTime, EventHandler& eventHandler);
        int DetachTimerEventHandler(int iTime, EventHandler& eventHandler);

    private:
        std::unordered_map<int, NX::EventID>           m_Time2EventId;
        std::unordered_map<NX::EventID, int>           m_EventId2Time;
    };
    inline int TickTimerManager(const int iDeltaTime){
    	return NX::TimerManager::Instance().Tick(iDeltaTime);
    }

    inline int TickTimerManager(){
    	return NX::TimerManager::Instance().Tick();
    }

    inline int  SendTimerEvent(int iTime){
        return NX::TimerManager::Instance().SendTimerEvent(iTime);
    }
    
    inline bool SendTimerEventToHandler(int iTime, EventHandler& eventHandler){
        return NX::TimerManager::Instance().SendTimerEventToHandler(iTime, eventHandler);
    }
    
    inline int AttachTimerEventHandler(int iTime, EventHandler& eventHandler){
        return NX::TimerManager::Instance().AttachTimerEventHandler(iTime, eventHandler);
    }
    
    inline int DetachTimerEventHandler(int iTime, EventHandler& eventHandler){
        return NX::TimerManager::Instance().DetachTimerEventHandler(iTime, eventHandler);
    }
}
