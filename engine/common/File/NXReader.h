/*
 *  File:     NXReader.h
 *  Author:   张雄
 *  Date:     2016_08_19
 *  Purpose:  file read operation
 */

#pragma once

#include "../NXCore.h"

namespace NX {
    class Reader{
    public:
        Reader() {}
        virtual ~Reader() {}
        
    public:
        virtual bool Readable() = 0;
        virtual NXInt8 ReadInt8() = 0;
        virtual NXUInt8 ReadUInt8() = 0;
        virtual NXInt16 ReadInt16() = 0;
        virtual NXUInt16 ReadUInt16() = 0;
        virtual NXInt32 ReadInt32() = 0;
        virtual NXUInt32 ReadUInt32() = 0;
        virtual NXInt64 ReadInt64() = 0;
        virtual NXUInt64 ReadUInt64() = 0;
        virtual std::string ReadString(const NXUInt32 len, NXUInt32 &ReadLen) = 0;
        
        virtual void ReadInt8(NXInt8 &rv) = 0;
        virtual void ReadUInt8(NXUInt8 &rv) = 0;
        virtual void ReadInt16(NXInt16 &rv) = 0;
        virtual void ReadUInt16(NXUInt16 &rv) = 0;
        virtual void ReadInt32(NXInt32 &rv) = 0;
        virtual void ReadUInt32(NXUInt32 &rv) = 0;
        virtual void ReadInt64(NXInt64 &rv) = 0;
        virtual void ReadUInt64(NXUInt64 &rv) = 0;
        virtual void ReadString(std::string &rv, const NXUInt32 len, NXUInt32 &ReadLen) = 0;
    };
}