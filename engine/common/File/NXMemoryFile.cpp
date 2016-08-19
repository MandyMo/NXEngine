/*
 *  File:     NXMemoryFile.cpp
 *  Author:   张雄
 *  Date:     2016_08_19
 *  Purpose:  memory file operation
 */

#include "NXMemoryFile.h"
#include "../Memory/NXMemory.h"

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
}

NX::MemoryFile::MemoryFile(const void *pStarAddress, const void *pEndAddress){//[start, end)
    ClearMember();
    NXUInt64 start = (NXUInt64)(pStarAddress);
    NXUInt64 end   = (NXUInt64)(pEndAddress);
    int BufLen = (int)(end - start);
    m_pMemIOBuf = (NXUInt8*)NX::MemoryManager::Instance().AllocateBuffer(BufLen);
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
    
}

void NX::MemoryFile::SkipReadBytes(const NXUInt64 SkippedByteCount){
    
}

void NX::MemoryFile::SkipWriteBytes(const NXUInt64 SkippedByteCount){
    
}

bool NX::MemoryFile::Readable(){
    
}

NXInt8 NX::MemoryFile::ReadInt8(){
    
}

NXUInt8 NX::MemoryFile::ReadUInt8(){
    
}

NXInt16 NX::MemoryFile::ReadInt16(){
    
}

NXUInt16 NX::MemoryFile::ReadUInt16(){
    
}

NXInt32 NX::MemoryFile::ReadInt32(){
    
}

NXUInt32 NX::MemoryFile::ReadUInt32(){
    
}

NXInt64 NX::MemoryFile::ReadInt64(){
    
}

NXUInt64 NX::MemoryFile::ReadUInt64(){
    
}

std::string NX::MemoryFile::ReadString(const NXUInt32 len, NXUInt32 &ReadLen){
    
}

void NX::MemoryFile::ReadInt8(NXInt8 &rv){
    
}

void NX::MemoryFile::ReadUInt8(NXUInt8 &rv){
    
}

void NX::MemoryFile::ReadInt16(NXInt16 &rv){
    
}
void NX::MemoryFile::ReadUInt16(NXUInt16 &rv){
    
}
void NX::MemoryFile::ReadInt32(NXInt32 &rv){
    
}

void NX::MemoryFile::ReadUInt32(NXUInt32 &rv){
    
}

void NX::MemoryFile::ReadInt64(NXInt64 &rv){
    
}

void NX::MemoryFile::ReadUInt64(NXUInt64 &rv) {
    
}

void NX::MemoryFile::ReadString(std::string &rv, const NXUInt32 len, NXUInt32 &ReadLen){
    
}

bool NX::MemoryFile::Writeable(){
    
}

void NX::MemoryFile::WriteInt8(const NXInt8 wv){
    
}

void NX::MemoryFile::WriteUInt8(const NXUInt8 wv) {
    
}

void NX::MemoryFile::WriteInt16(const NXInt16 wv){
    
}

void NX::MemoryFile::WriteUInt16(const NXUInt16 wv){
    
}

void NX::MemoryFile::WriteInt32(const NXInt32 wv){
    
}

void NX::MemoryFile::WriteUInt32(const NXUInt32 wv) {
    
}

void NX::MemoryFile::WriteInt64(const NXInt64 wv){
    
}

void NX::MemoryFile::WriteUInt64(const NXUInt64 wv){
    
}

void NX::MemoryFile::WriteString(const std::string &wv){
    
}