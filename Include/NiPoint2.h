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
#ifndef NIPOINT2_H
#define NIPOINT2_H

#include <NiMainLibType.h>
#include <efd/Point2.h>
#include <NiTSet.h>

class NiStream;

class NIMAIN_ENTRY NiPoint2 : public efd::Point2
{
public:
    inline NiPoint2() : efd::Point2() {}
    inline NiPoint2(float fX, float fY) : efd::Point2(fX, fY) {}
    inline NiPoint2(const efd::Point2& kSrc) : efd::Point2(kSrc) {}

    // *** begin Emergent internal use only ***
#ifndef __SPU__
    // streaming
    void LoadBinary (NiStream& stream);
    void SaveBinary (NiStream& stream) const;

    // Utility methods for streaming arrays of NiPoint2's.
    // Note that the array's must be pre-allocated for Loading,
    // meaning that the external caller is responsible for
    // streaming the size.
    static void LoadBinary(
        NiStream& stream,
        NiPoint2* pkValues,
        unsigned int uiNumValues);
    static void SaveBinary(
        NiStream& stream,
        NiPoint2* pkValues,
        unsigned int uiNumValues);

    char* GetViewerString (const char* pPrefix) const;
#endif
    // *** end Emergent internal use only ***
};

#ifndef __SPU__
typedef NiTObjectSet<NiPoint2> NiPoint2Set;
#endif

//--------------------------------------------------------------------------------------------------
//  Inline include
#include "NiPoint2.inl"

//--------------------------------------------------------------------------------------------------

#endif

