/**
 *   File:     NXEvent.cpp
 *
 *   Author:   张雄
 *   Date:     2016_07_27
 *   Purpose:  implement even system
 */

#include "NXEvent.h"
#include "NXEventHandler.h"

NX::Event::Event(const NX::EventID id): m_id(id){
    /*empty*/
}

NX::Event::~Event(){
    for(std::vector<EventHandler*>::iterator it = m_vEventLisener.begin(); it != m_vEventLisener.end(); ++it){
        if(*it){
            (*it)->Release();
        }
    }
    m_vEventLisener.clear();
}

NX::EventID NX::Event::GetEventId(){
    return m_id;
}

int NX::Event::AttatchEventHandler(NX::EventHandler *handler){
    if(handler && std::find(m_vEventLisener.begin(), m_vEventLisener.end(), handler) == m_vEventLisener.end()){
        handler->AddRef();
        m_vEventLisener.push_back(handler);
    }
    return (int)m_vEventLisener.size();
}

int NX::Event::DetachEventHandler(NX::EventHandler *handler){
    std::vector<EventHandler*>::iterator it = std::find(m_vEventLisener.begin(), m_vEventLisener.end(), handler);
    if(it != m_vEventLisener.end() && handler){
        handler->Release();
        m_vEventLisener.erase(it);
    }
    return (int)m_vEventLisener.size();
}

int NX::Event::GetListenerCount(){
    return (int)m_vEventLisener.size();
}

bool NX::Event::SendEvent(NX::EventHandler *handler){
    if(handler &&  std::find(m_vEventLisener.begin(), m_vEventLisener.end(), handler) != m_vEventLisener.end()){
        return handler->HandleEvent(this);
    }
    return false;
}

int NX::Event::SendEvent(){
    int iSucced = 0;
    for(int i = 0, l = (int)m_vEventLisener.size(); i < l; ++i){
        if(m_vEventLisener[i] && m_vEventLisener[i]->HandleEvent(this)){
            ++iSucced;
        }
    }
    return iSucced;
}