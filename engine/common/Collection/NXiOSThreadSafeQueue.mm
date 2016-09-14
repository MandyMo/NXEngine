/*
 *  File:    NXiOSThreadSafeQueue.mm
 *
 *  author:  张雄(zhang xiong)
 *  date:    2016_08_27
 *  purpose: define a thread safe queue for iOS
 */

#include "../../System/NXMutex.h"
#include "NXThreadSafeQueue.h"

#if defined(__APPLE__)

#import <Foundation/Foundation.h>
#include "NXKVFile.h"

namespace NX{
    class IOSThreadSafeQueue: public NX::ThreadSafeQueue, public NX::Serializable{
    public:
        IOSThreadSafeQueue();
        virtual ~IOSThreadSafeQueue();
        
    public:
        virtual int  Capacity();
        virtual int  Count();
        virtual bool Init();
        virtual bool Empty();
        virtual bool Full();
        virtual bool Enque(const std::string &strMsg, const bool bForceInsert);
        virtual std::pair<bool, std::string> Deque();
        virtual bool Serialize();
        virtual bool UnSerialize();
        
    private:
        void IncIdx(int &idx);
        void DecIdx(int &idx);
        
    private:
        NX::Mutex       *m_pMutex;
        int             m_iEnqueIdx;
        int             m_iDequeIdx;
        int             m_iSlotCount;
    };
}


static std::string      strEnqueIdxKey     = "D213AF94_FD3B_0A31_5D92_57EA2AF0AAF2";
static std::string      strDequeIdxKey     = "6C1B82D2_ED85_8CA5_24B5_EC319A875B2D";
static std::string      strSlotCountKey    = "2D2518D7_A0AA_51BE_DFBD_333D394C0166";
static std::string      strMsgIdxPrefix    = "A2C0DEF7_797D_8C3E_5653_3DDAD7AB1D5A";

static std::string EnCodeKey(const int n);
//static int DeCodeKey(const std::string &str);
static std::string Int2String(const int n);
static int String2Int(const std::string &str);

NX::IOSThreadSafeQueue::IOSThreadSafeQueue(){
    m_pMutex     = NX::Mutex::Create();
    m_iEnqueIdx  = 0;
    m_iDequeIdx  = 0;
    m_iSlotCount = 0;
}

NX::IOSThreadSafeQueue::~IOSThreadSafeQueue(){
    Serialize();
    NX::Mutex::Destroy(m_pMutex);
}

int NX::IOSThreadSafeQueue::Capacity(){
    return m_iSlotCount;
}

int  NX::IOSThreadSafeQueue::Count(){
    if(m_iSlotCount == 0){
        return 0;
    }
    return (m_iEnqueIdx - m_iDequeIdx + m_iSlotCount) % m_iSlotCount;
}

bool NX::IOSThreadSafeQueue::Init(){
    static bool bInited = false;
    if(bInited){
        return true;
    }
    if(UnSerialize()){//read from disk failed
        return bInited = true;
    }
    /**
     *  it's the first time use it, so create it
     */
    m_iSlotCount = 1024;
    m_iDequeIdx  = 0;
    m_iEnqueIdx  = 0;
    bInited = true;
    return Serialize();
}

bool NX::IOSThreadSafeQueue::Empty(){
    return m_iDequeIdx == m_iEnqueIdx;
}

bool NX::IOSThreadSafeQueue::Full(){
    return (m_iEnqueIdx + 1 - m_iDequeIdx + m_iSlotCount) % m_iSlotCount == 0;
}

bool NX::IOSThreadSafeQueue::Enque(const std::string &strMsg, const bool bForceInsert){
    NX::MutexWraper wraper(m_pMutex);
    NX::KVFile &seriazer = NX::KVFile::Instance();
    if(Full() && !bForceInsert){
        return false;
    }
    //pop the head element
    if(Full()){
        std::string skey = EnCodeKey(m_iDequeIdx);
        seriazer.DeleteValue(skey);
        IncIdx(m_iDequeIdx);
        seriazer.SetValue(strDequeIdxKey, Int2String(m_iDequeIdx));
    }
    
    //now que is not full, just do enque
    std::string skey = EnCodeKey(m_iEnqueIdx);
    IncIdx(m_iEnqueIdx);
    seriazer.SetValue(skey, strMsg);
    seriazer.SetValue(strEnqueIdxKey, Int2String(m_iEnqueIdx));
    return true;
}

std::pair<bool, std::string> NX::IOSThreadSafeQueue::Deque(){
    NX::MutexWraper wraper(m_pMutex);
    if(Empty()){
        return std::make_pair(false, "");
    }
    NX::KVFile &seriazer = NX::KVFile::Instance();
    std::string skey = EnCodeKey(m_iDequeIdx);
    auto result = std::make_pair(true, seriazer.DeleteValue(skey));
    IncIdx(m_iDequeIdx);
    seriazer.SetValue(strDequeIdxKey, Int2String(m_iDequeIdx));
    return result;
}

bool NX::IOSThreadSafeQueue::Serialize(){
    if(m_iEnqueIdx < 0 || m_iDequeIdx < 0 || m_iSlotCount <= 0){
        return false;
    }
    
    NX::MutexWraper wraper(m_pMutex);
    NX::KVFile &seriazer = NX::KVFile::Instance();
    seriazer.SetValue(strEnqueIdxKey,  Int2String(m_iEnqueIdx));
    seriazer.SetValue(strDequeIdxKey,  Int2String(m_iDequeIdx));
    seriazer.SetValue(strSlotCountKey, Int2String(m_iSlotCount));
    
    return true;
}

bool NX::IOSThreadSafeQueue::UnSerialize(){
    NX::MutexWraper wraper(m_pMutex);
    NX::KVFile &seriazer = NX::KVFile::Instance();
    if(!seriazer.HasKey(strEnqueIdxKey) || !seriazer.HasKey(strDequeIdxKey) || !seriazer.HasKey(strSlotCountKey)){
        return false;
    }
    
    m_iEnqueIdx   = String2Int(seriazer.GetValue(strEnqueIdxKey));
    m_iSlotCount  = String2Int(seriazer.GetValue(strSlotCountKey));
    m_iDequeIdx   = String2Int(seriazer.GetValue(strDequeIdxKey));
    
    if(m_iEnqueIdx < 0 || m_iDequeIdx < 0 || m_iSlotCount <= 0){
        return false;
    }
    return true;
}

void NX::IOSThreadSafeQueue::IncIdx(int &idx){
    if(m_iSlotCount <= 0){
        return;
    }
    (++idx) %= m_iSlotCount;
}

void NX::IOSThreadSafeQueue::DecIdx(int &idx){
    if(m_iSlotCount <= 0){
        return;
    }
    idx = (idx - 1 + m_iSlotCount) % m_iSlotCount;
}

NX::ThreadSafeQueue* NX::ThreadSafeQueue::Create(){
    return new NX::IOSThreadSafeQueue();
}

static std::string EnCodeKey(const int key){
    char buf[100];
    sprintf(buf, "%s%d", strMsgIdxPrefix.c_str(), key);
    return buf;
}

//static int DeCodeKey(const std::string &key){
//    if(key.length() <= strMsgIdxPrefix.length()){
//        return -1;
//    }
//    int n;
//    sscanf(key.c_str() + strMsgIdxPrefix.length(), "%d", &n);
//    return n;
//}
static std::string Int2String(const int n){
    char buf[10];
    sprintf(buf, "%d", n);
    return buf;
}

static int String2Int(const std::string &str){
    int n = -1;
    sscanf(str.c_str(), "%d", &n);
    return n;
}

#endif