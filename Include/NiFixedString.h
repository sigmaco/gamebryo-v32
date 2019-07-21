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
#ifndef NIFIXEDSTRINGTABLE_H
#define NIFIXEDSTRINGTABLE_H

#include "NiMainLibType.h"
#include "NiGlobalStringTable.h"
#include "NiPath.h"
#include "NiBinaryStream.h"
#include <efd/FixedString.h>


class NIMAIN_ENTRY NiFixedString : public efd::FixedString
{
public:
    inline NiFixedString() : efd::FixedString() {};
    inline NiFixedString(const char* pcString) : efd::FixedString(pcString) {};
    inline NiFixedString(const NiFixedString& kString) : efd::FixedString(kString) {};

    inline NiFixedString& operator=(const char* pkString);

    friend bool operator==(const NiFixedString& s1, const NiFixedString& s2);
    friend bool operator!=(const NiFixedString& s1, const NiFixedString& s2);

    friend bool operator==(const NiFixedString& s1, const char* s2);
    friend bool operator!=(const NiFixedString& s1, const char* s2);

    friend bool operator==(const char* s1, const NiFixedString& s2);
    friend bool operator!=(const char* s1, const NiFixedString& s2);


    // *** begin Emergent internal use only ***
    static void LoadCStringAsFixedString(efd::BinaryStream& kStream,
        NiFixedString& kString);
    static void SaveFixedStringAsCString(efd::BinaryStream& kStream,
        const NiFixedString& kString);
    // *** end Emergent internal use only ***
};

NIMAIN_ENTRY void NiStandardizeFilePath(NiFixedString& kString);

#include "NiFixedString.inl"

#endif
