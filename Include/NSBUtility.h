// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not
// be copied or disclosed except in accordance with the terms of that
// agreement.
//
//      Copyright (c) 1996-2009 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Calabasas, CA 91302
// http://www.emergent.net

#pragma once
#ifndef NSBUTILITY_H
#define NSBUTILITY_H

#include "NSBShaderLibLibType.h"
#include <NiMemObject.h>
#include <efd/File.h>

class NSBStateGroup;
class NSBConstantMap;
namespace efd
{
    class BinaryStream;
}

//--------------------------------------------------------------------------------------------------

// Make sure these defines match what's in NSFLexer.l
#ifndef NSBSHADER_VERSION_MAJOR
#define NSBSHADER_VERSION_MAJOR(_Version) (((_Version)>>8)&0xFF)
#endif  //#ifndef NSBSHADER_VERSION_MAJOR

#ifndef NSBSHADER_VERSION_MINOR
#define NSBSHADER_VERSION_MINOR(_Version) (((_Version)>>0)&0xFF)
#endif  //#ifndef NSBSHADER_VERSION_MINOR

#ifndef NSBVS_VERSION
#define NSBVS_VERSION(_Major,_Minor) (0xFFFE0000|((_Major)<<8)|(_Minor))
#endif  //#ifndef NSBVS_VERSION

#ifndef NSBGS_VERSION
#define NSBGS_VERSION(_Major,_Minor) (0xFFFD0000|((_Major)<<8)|(_Minor))
#endif  //#ifndef NSBGS_VERSION

#ifndef NSBPS_VERSION
#define NSBPS_VERSION(_Major,_Minor) (0xFFFF0000|((_Major)<<8)|(_Minor))
#endif  //#ifndef NSBPS_VERSION

#ifndef NSBCS_VERSION
#define NSBCS_VERSION(_Major,_Minor) (0xFFFC0000|((_Major)<<8)|(_Minor))
#endif  //#ifndef NSBCS_VERSION

#if defined(NIDEBUG)
#define STATE_CASE_STRING(x)      case x: return #x;
#endif  //#if defined(NIDEBUG)

class NSBSHADERLIB_ENTRY NSBUtility : public NiMemObject
{
public:
    static bool SaveBinaryStateGroup(efd::BinaryStream& kStream,
        NSBStateGroup* pkStateGroup);
    static bool LoadBinaryStateGroup(efd::BinaryStream& kStream,
        NSBStateGroup*& pkStateGroup);

    static bool SaveBinaryConstantMap(efd::BinaryStream& kStream,
        NSBConstantMap* pkMap);
    static bool LoadBinaryConstantMap(efd::BinaryStream& kStream,
        NSBConstantMap*& pkMap);

    // String setting helper function
    static unsigned int SetString(char*& pcDest, unsigned int uiDestSize,
        const char* pcSrc);

    // Write to stream
    static bool WriteData(efd::BinaryStream& kStream, void* pvData,
        unsigned int uiSize, unsigned int uiComponentSize = 1);

    // Read from stream
    static bool ReadData(efd::BinaryStream& kStream, void*& pvData,
        unsigned int& uiSize);
    static bool AllocateAndReadData(efd::BinaryStream& kStream, void*& pvData,
        unsigned int& uiDataSize, unsigned int uiComponentSize = 1);

#if defined(NIDEBUG)
    static unsigned int ms_uiIndent;

    static void IndentInsert();
    static void IndentRemove();
    static void Dump(FILE* pf, bool bIndent, const char* pcFmt, ...);
#endif  //#if defined(NIDEBUG)

};

//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------

#endif  //NSBUTILITY_H
