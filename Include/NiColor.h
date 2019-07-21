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
#ifndef NICOLOR_H
#define NICOLOR_H

#include "NiMainLibType.h"
//#include "NiStream.h"
#include "NiUniversalTypes.h"

#include <efd/Color.h>

class NiStream;
class NiColorA;
class NiRGBA;

//------------------------------------------------------------------------------------------------

class NIMAIN_ENTRY NiColor : public efd::Color
{
public:
    inline NiColor() : efd::Color() {}
    inline NiColor(float fR, float fG, float fB) : efd::Color(fR, fG, fB) {}
    inline NiColor(const efd::Color& kSrc) : efd::Color(kSrc) {}

    // *** begin Emergent internal use only ***
#ifndef __SPU__
    // streaming
    void LoadBinary(NiStream& stream);
    void SaveBinary(NiStream& stream);

    // Utility methods for streaming arrays of NiColor's.
    // Note that the array's must be pre-allocated for Loading,
    // meaning that the external caller is responsible for
    // streaming the size.
    static void LoadBinary(NiStream& stream, NiColor* pkValues,
        unsigned int uiNumValues);
    static void SaveBinary(NiStream& stream, NiColor* pkValues,
        unsigned int uiNumValues);

    char* GetViewerString (const char* pPrefix) const;
#endif
    // *** end Emergent internal use only ***
};

//------------------------------------------------------------------------------------------------

class NIMAIN_ENTRY NiColorA : public efd::ColorA
{
public:
    inline NiColorA() : efd::ColorA() {}
    inline NiColorA(float fR, float fG, float fB, float fA) :
        efd::ColorA(fR, fG, fB, fA) {}
    inline NiColorA(const efd::ColorA& kSrc) : efd::ColorA(kSrc) {}

    // *** begin Emergent internal use only ***
#ifndef __SPU__
    // streaming
    void LoadBinary(NiStream& stream);
    void SaveBinary(NiStream& stream);

    // Utility methods for streaming arrays of NiColorA's.
    // Note that the array's must be pre-allocated for Loading,
    // meaning that the external caller is responsible for
    // streaming the size.
    static void LoadBinary(NiStream& stream, NiColorA* pkValues,
        unsigned int uiNumValues);
    static void SaveBinary(NiStream& stream, NiColorA* pkValues,
        unsigned int uiNumValues);

    char* GetViewerString (const char* pPrefix) const;
#endif

    // *** end Emergent internal use only ***
};

//------------------------------------------------------------------------------------------------

class NIMAIN_ENTRY NiRGBA : public efd::ColorA_UInt8
{
public:
    inline NiRGBA() : efd::ColorA_UInt8() {}
    inline NiRGBA(NiUInt8 uiR, NiUInt8 uiG, NiUInt8 uiB, NiUInt8 uiA) :
        efd::ColorA_UInt8(uiR, uiG, uiB, uiA) {}
    inline NiRGBA(const efd::ColorA_UInt8& kSrc) : efd::ColorA_UInt8(kSrc) {}

    // *** begin Emergent internal use only ***
#ifndef __SPU__
    // streaming
    void LoadBinary(NiStream& kStream);
    void SaveBinary(NiStream& kStream);

    // Utility methods for streaming arrays of NiRGBA objects.
    // Note that the arrays must be pre-allocated for Loading,
    // meaning that the external caller is responsible for
    // streaming the size.
    static void LoadBinary(NiStream& stream, NiRGBA* pkValues,
        unsigned int uiNumValues);
    static void SaveBinary(NiStream& stream, NiRGBA* pkValues,
        unsigned int uiNumValues);

    char* GetViewerString(const char* pcPrefix) const;
#endif
    // *** end Emergent internal use only ***
};

//------------------------------------------------------------------------------------------------

#endif
