/*
 *  File:     NXMemoryFile.h
 *  Author:   张雄
 *  Date:     2016_08_19
 *  Purpose:  memory file operation
 */

#pragma once

#include "NXReader.h"
#include "NXWriter.h"
#include "../NXUtility.h"

namespace NX {
    class MemoryFile: public NX::Reader, public NX::Writer, public NX::NXRef{
    public:
        MemoryFile();
        explicit MemoryFile(const std::string &strDiskFilePath);
        explicit MemoryFile(const NXUInt64 MemBufSize);
        explicit MemoryFile(const void *pStarAddress, const void *pEndAddress);//[start, end)
        virtual ~MemoryFile();
        
    public:
        NXUInt64 GetCurReadPosition();
        NXUInt64 GetCurWritePosition();
        NXUInt64 GetMemBufSize();
        void ExpandMemBuf(const NXUInt64 NewMemBufSize);
        void SkipReadBytes(const NXUInt64 SkippedByteCount);
        void SkipWriteBytes(const NXUInt64 SkippedByteCount);
    public:
        virtual bool Readable();
        virtual NXInt8 ReadInt8();
        virtual NXUInt8 ReadUInt8();
        virtual NXInt16 ReadInt16();
        virtual NXUInt16 ReadUInt16();
        virtual NXInt32 ReadInt32();
        virtual NXUInt32 ReadUInt32();
        virtual NXInt64 ReadInt64();
        virtual NXUInt64 ReadUInt64();
        virtual std::string ReadString(const NXUInt32 len, NXUInt32 &ReadLen);
        
        virtual void ReadInt8(NXInt8 &rv);
        virtual void ReadUInt8(NXUInt8 &rv);
        virtual void ReadInt16(NXInt16 &rv);
        virtual void ReadUInt16(NXUInt16 &rv);
        virtual void ReadInt32(NXInt32 &rv);
        virtual void ReadUInt32(NXUInt32 &rv);
        virtual void ReadInt64(NXInt64 &rv);
        virtual void ReadUInt64(NXUInt64 &rv) ;
        virtual void ReadString(std::string &rv, const NXUInt32 len, NXUInt32 &ReadLen);
        
    public:
        virtual bool Writeable();
        virtual void WriteInt8(const NXInt8 wv);
        virtual void WriteUInt8(const NXUInt8 wv) ;
        virtual void WriteInt16(const NXInt16 wv);
        virtual void WriteUInt16(const NXUInt16 wv);
        virtual void WriteInt32(const NXInt32 wv);
        virtual void WriteUInt32(const NXUInt32 wv) ;
        virtual void WriteInt64(const NXInt64 wv);
        virtual void WriteUInt64(const NXUInt64 wv);
        virtual void WriteString(const std::string &wv);
        
    private:
        void ClearMember();
    private:
        NXUInt64   m_uMemIOBufLen;
        NXUInt64   m_uCurReadPos;
        NXUInt64   m_uCurWritePos;
        NXUInt8*   m_pMemIOBuf;
        std::string m_strDiskFilePath;
    };
}