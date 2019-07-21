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
#ifndef NIPOINT3_H
#define NIPOINT3_H

#include "NiMainLibType.h"
#include "NiTSet.h"

class NiStream;

#include <efd/Point3.h>

class NIMAIN_ENTRY NiPoint3 : public efd::Point3
{
public:
    inline NiPoint3() : efd::Point3() {}
    inline NiPoint3(float fX, float fY, float fZ) : efd::Point3(fX, fY, fZ) {}
    inline NiPoint3(const efd::Point3& kSrc) : efd::Point3(kSrc) {}

    // *** begin Emergent internal use only ***
#ifndef __SPU__
    // streaming
    void LoadBinary (NiStream& stream);
    void SaveBinary (NiStream& stream) const;

    // Utility methods for streaming arrays of NiPoint3's.
    // Note that the array's must be pre-allocated for Loading,
    // meaning that the external caller is responsible for
    // streaming the size.
    static void LoadBinary (NiStream& stream, NiPoint3* pkValues,
        unsigned int uiNumValues);
    static void SaveBinary (NiStream& stream, NiPoint3* pkValues,
        unsigned int uiNumValues);

    char* GetViewerString (const char* pPrefix) const;
#endif
    // *** end Emergent internal use only ***
};

#ifndef __SPU__
typedef NiTObjectSet<NiPoint3> NiPoint3Set;
#endif

//--------------------------------------------------------------------------------------------------
//  Inline include
#include "NiPoint3.inl"

//--------------------------------------------------------------------------------------------------

#endif


