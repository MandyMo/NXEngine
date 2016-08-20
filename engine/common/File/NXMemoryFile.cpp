/*
 *  File:     NXMemoryFile.cpp
 *  Author:   张雄
 *  Date:     2016_08_19
 *  Purpose:  memory file operation
 */

#include "NXMemoryFile.h"
#include "../Memory/NXMemory.h"
#include "../../math/NXMath.h"

void NX::MemoryFile::ClearMember(){
    m_uCurReadPos   = 0;
    m_uCurWritePos  = 0;
    m_uMemIOBufLen  = 0;
    m_pMemIOBuf     = NULL;
    m_strDiskFilePath.clear();
}

NX::MemoryFile::MemoryFile(){
    ClearMember();
}

NX::MemoryFile::MemoryFile(const std::string &strDiskFilePath){
    ClearMember();
}

NX::MemoryFile::MemoryFile(const NXUInt64 MemBufSize){
    ClearMember();
    m_pMemIOBuf = (NXUInt8*)NX::MemoryManager::Instance().AllocBuffer(MemBufSize);
    if(m_pMemIOBuf){
        m_uMemIOBufLen = MemBufSize;
    }
}

NX::MemoryFile::MemoryFile(const void *pStarAddress, const void *pEndAddress){//[start, end)
    ClearMember();
    NXUInt64 start  = (NXUInt64)((void*)pStarAddress);
    NXUInt64 end    = (NXUInt64)((void*)pEndAddress);
    if(start <= end){
        return;
    }
    NXUInt64 BufLen = (int)(end - start);
    m_pMemIOBuf = (NXUInt8*)NX::MemoryManager::Instance().AllocBuffer(BufLen);
    if(!m_pMemIOBuf){
        ClearMember();
        return;
    }
    memcpy(m_pMemIOBuf, pStarAddress, BufLen);
    m_uMemIOBufLen = BufLen;
}

NX::MemoryFile::~MemoryFile(){
    m_strDiskFilePath.clear();
    NX::MemoryManager::Instance().FreeBuffer(m_pMemIOBuf);
    ClearMember();
}

NXUInt64 NX::MemoryFile::GetCurReadPosition(){
    return m_uCurReadPos;
}

NXUInt64 NX::MemoryFile::GetCurWritePosition(){
    return m_uCurWritePos;
}

NXUInt64 NX::MemoryFile::GetMemBufSize(){
    return m_uMemIOBufLen;
}

void NX::MemoryFile::ExpandMemBuf(const NXUInt64 NewMemBufSize){
    if(m_uMemIOBufLen >= NewMemBufSize){
        return;
    }
    
    NXUInt8 * pNewBuf = (NXUInt8*)NX::MemoryManager::Instance().AllocBuffer(NewMemBufSize);
    if(!pNewBuf){
        return;
    }
    
    memcpy(pNewBuf, m_pMemIOBuf, m_uMemIOBufLen);
    m_uMemIOBufLen = NewMemBufSize;
    NX::MemoryManager::Instance().FreeBuffer(m_pMemIOBuf);
    m_pMemIOBuf = pNewBuf;
}

void NX::MemoryFile::SkipReadBytes(const NXUInt64 SkippedByteCount){
    if(!Readable() || m_uMemIOBufLen - m_uCurReadPos <= SkippedByteCount){
        m_uCurReadPos = m_uMemIOBufLen;
    }else{
        m_uCurReadPos += SkippedByteCount;
    }
}

void NX::MemoryFile::SkipWriteBytes(const NXUInt64 SkippedByteCount){
    if(!Writeable() || m_uMemIOBufLen - m_uCurWritePos <= SkippedByteCount){
        m_uCurWritePos = m_uMemIOBufLen;
    }else{
        m_uCurWritePos += SkippedByteCount;
    }
}

bool NX::MemoryFile::Readable(){
    return m_pMemIOBuf && m_uCurReadPos < m_uMemIOBufLen;
}

NXInt8 NX::MemoryFile::ReadInt8(){
    if(!Readable() || m_uMemIOBufLen - m_uCurReadPos < sizeof(NXInt8)){
        return -1;
    }
    NXInt8 v = *(NXInt8*)(m_pMemIOBuf + m_uCurReadPos);
    m_uCurReadPos += sizeof(NXInt8);
    return v;
}

NXUInt8 NX::MemoryFile::ReadUInt8(){
    if(!Readable() || m_uMemIOBufLen - m_uCurReadPos < sizeof(NXUInt8)){
        return -1;
    }
    NXUInt8 v = *(NXUInt8*)(m_pMemIOBuf + m_uCurReadPos);
    m_uCurReadPos += sizeof(NXUInt8);
    return v;
}

NXInt16 NX::MemoryFile::ReadInt16(){
    if(!Readable() || m_uMemIOBufLen - m_uCurReadPos < sizeof(NXInt16)){
        return -1;
    }
    NXInt16 v = *(NXInt16*)(m_pMemIOBuf + m_uCurReadPos);
    m_uCurReadPos += sizeof(NXInt16);
    return v;
}

NXUInt16 NX::MemoryFile::ReadUInt16(){
    if(!Readable() || m_uMemIOBufLen - m_uCurReadPos < sizeof(NXUInt16)){
        return -1;
    }
    NXUInt16 v = *(NXUInt16*)(m_pMemIOBuf + m_uCurReadPos);
    m_uCurReadPos += sizeof(NXUInt16);
    return v;
}

NXInt32 NX::MemoryFile::ReadInt32(){
    if(!Readable() || m_uMemIOBufLen - m_uCurReadPos < sizeof(NXInt32)){
        return -1;
    }
    NXInt32 v = *(NXInt32*)(m_pMemIOBuf + m_uCurReadPos);
    m_uCurReadPos += sizeof(NXInt32);
    return v;
}

NXUInt32 NX::MemoryFile::ReadUInt32(){
    if(!Readable() || m_uMemIOBufLen - m_uCurReadPos < sizeof(NXUInt32)){
        return -1;
    }
    NXUInt32 v = *(NXUInt32*)(m_pMemIOBuf + m_uCurReadPos);
    m_uCurReadPos += sizeof(NXUInt32);
    return v;
}

NXInt64 NX::MemoryFile::ReadInt64(){
    if(!Readable() || m_uMemIOBufLen - m_uCurReadPos < sizeof(NXInt64)){
        return -1;
    }
    NXInt64 v = *(NXInt64*)(m_pMemIOBuf + m_uCurReadPos);
    m_uCurReadPos += sizeof(NXInt64);
    return v;
}

NXUInt64 NX::MemoryFile::ReadUInt64(){
    if(!Readable() || m_uMemIOBufLen - m_uCurReadPos < sizeof(NXUInt64)){
        return -1;
    }
    NXUInt64 v = *(NXUInt64*)(m_pMemIOBuf + m_uCurReadPos);
    m_uCurReadPos += sizeof(NXUInt64);
    return v;
}

std::string NX::MemoryFile::ReadString(const NXUInt32 len, NXUInt32 &ReadLen){
    if(!Readable()){
        ReadLen = 0;
        return std::string();
    }else if(m_uMemIOBufLen - m_uCurReadPos < len){
        ReadLen = (NXUInt32)(m_uMemIOBufLen - m_uCurReadPos);
        NXUInt8 * pb = m_pMemIOBuf + m_uCurReadPos;
        NXUInt8 * pe = m_pMemIOBuf + m_uMemIOBufLen;
        m_uCurReadPos = m_uMemIOBufLen;
        return std::string(pb, pe);
    }else{
        ReadLen = len;
        NXUInt8 * pb = m_pMemIOBuf + m_uCurReadPos;
        NXUInt8 * pe = pb + len;
        m_uCurReadPos  += len;
        return std::string(pb, pe);
    }
}

void NX::MemoryFile::ReadInt8(NXInt8 &rv){
    rv = ReadInt8();
}

void NX::MemoryFile::ReadUInt8(NXUInt8 &rv){
    rv = ReadUInt8();
}

void NX::MemoryFile::ReadInt16(NXInt16 &rv){
    rv = ReadInt16();
}
void NX::MemoryFile::ReadUInt16(NXUInt16 &rv){
    rv = ReadUInt16();
}
void NX::MemoryFile::ReadInt32(NXInt32 &rv){
    rv = ReadInt32();
}

void NX::MemoryFile::ReadUInt32(NXUInt32 &rv){
    rv = ReadUInt32();
}

void NX::MemoryFile::ReadInt64(NXInt64 &rv){
    rv = ReadInt64();
}

void NX::MemoryFile::ReadUInt64(NXUInt64 &rv) {
    rv = ReadUInt64();
}

void NX::MemoryFile::ReadString(std::string &rv, const NXUInt32 len, NXUInt32 &ReadLen){
    rv = ReadString(len, ReadLen);
}

bool NX::MemoryFile::Writeable(){
    return m_pMemIOBuf && m_uCurWritePos < m_uMemIOBufLen;
}

void NX::MemoryFile::WriteInt8(const NXInt8 wv){
    if(!Writeable() || m_uMemIOBufLen - m_uCurWritePos < sizeof(NXInt8)){
        return;
    }
    memcpy(m_pMemIOBuf + m_uCurWritePos, &wv, sizeof(wv));
    m_uCurWritePos += sizeof(wv);
}

void NX::MemoryFile::WriteUInt8(const NXUInt8 wv) {
    if(!Writeable() || m_uMemIOBufLen - m_uCurWritePos < sizeof(NXUInt8)){
        return;
    }
    memcpy(m_pMemIOBuf + m_uCurWritePos, &wv, sizeof(wv));
    m_uCurWritePos += sizeof(wv);
}

void NX::MemoryFile::WriteInt16(const NXInt16 wv){
    if(!Writeable() || m_uMemIOBufLen - m_uCurWritePos < sizeof(NXInt16)){
        return;
    }
    memcpy(m_pMemIOBuf + m_uCurWritePos, &wv, sizeof(wv));
    m_uCurWritePos += sizeof(wv);
}

void NX::MemoryFile::WriteUInt16(const NXUInt16 wv){
    if(!Writeable() || m_uMemIOBufLen - m_uCurWritePos < sizeof(NXUInt16)){
        return;
    }
    memcpy(m_pMemIOBuf + m_uCurWritePos, &wv, sizeof(wv));
    m_uCurWritePos += sizeof(wv);
}

void NX::MemoryFile::WriteInt32(const NXInt32 wv){
    if(!Writeable() || m_uMemIOBufLen - m_uCurWritePos < sizeof(NXInt32)){
        return;
    }
    memcpy(m_pMemIOBuf + m_uCurWritePos, &wv, sizeof(wv));
    m_uCurWritePos += sizeof(wv);
}

void NX::MemoryFile::WriteUInt32(const NXUInt32 wv) {
    if(!Writeable() || m_uMemIOBufLen - m_uCurWritePos < sizeof(NXUInt32)){
        return;
    }
    memcpy(m_pMemIOBuf + m_uCurWritePos, &wv, sizeof(wv));
    m_uCurWritePos += sizeof(wv);
}

void NX::MemoryFile::WriteInt64(const NXInt64 wv){
    if(!Writeable() || m_uMemIOBufLen - m_uCurWritePos < sizeof(NXInt64)){
        return;
    }
    memcpy(m_pMemIOBuf + m_uCurWritePos, &wv, sizeof(wv));
    m_uCurWritePos += sizeof(wv);
}

void NX::MemoryFile::WriteUInt64(const NXUInt64 wv){
    if(!Writeable() || m_uMemIOBufLen - m_uCurWritePos < sizeof(NXUInt64)){
        return;
    }
    memcpy(m_pMemIOBuf + m_uCurWritePos, &wv, sizeof(wv));
    m_uCurWritePos += sizeof(wv);
}

void NX::MemoryFile::WriteString(const std::string &wv){
    if(!Writeable()){
        return;
    }
    NXUInt64 wl = NX::NXMin(m_uMemIOBufLen - m_uCurWritePos, wv.length());
    memcpy(m_pMemIOBuf + m_uCurWritePos, wv.c_str(), wl);
    m_uCurWritePos += wl;
}