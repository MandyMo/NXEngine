/*
 *  File:     NXWriter.h
 *  Author:   张雄
 *  Date:     2016_08_19
 *  Purpose:  file write operation
 */

#pragma once

#include "NXCore.h"

namespace NX {
    class Writer{
    public:
        Writer() {}
        virtual ~Writer() {}
    
    public:
        virtual bool Writeable() = 0;
        virtual void WriteInt8(const NXInt8 wv) = 0;
        virtual void WriteUInt8(const NXUInt8 wv) = 0;
        virtual void WriteInt16(const NXInt16 wv) = 0;
        virtual void WriteUInt16(const NXUInt16 wv) = 0;
        virtual void WriteInt32(const NXInt32 wv) = 0;
        virtual void WriteUInt32(const NXUInt32 wv) = 0;
        virtual void WriteInt64(const NXInt64 wv) = 0;
        virtual void WriteUInt64(const NXUInt64 wv) = 0;
        virtual void WriteString(const std::string &wv) = 0;
    };
}