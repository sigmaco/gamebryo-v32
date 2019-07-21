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
#ifndef NIAVOBJECTPALETTE_H
#define NIAVOBJECTPALETTE_H

#include "NiAVObject.h"

class NIMAIN_ENTRY NiAVObjectPalette : public NiObject
{
    NiDeclareRTTI;
    NiDeclareAbstractClone(NiAVObjectPalette);
    NiDeclareAbstractStream;
    NiDeclareViewerStrings;

public:
    inline NiAVObjectPalette() { /* */ }
    inline ~NiAVObjectPalette() { /* */ }

    virtual NiAVObject* GetAVObject(const char* pcName) = 0;
    virtual void SetAVObject(const char* pcName, NiAVObject* pkObj) = 0;
};

typedef efd::SmartPointer<NiAVObjectPalette> NiAVObjectPalettePtr;

#endif
