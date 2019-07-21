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
#ifndef NIMATERIALNODELIBRARYREADER_H
#define NIMATERIALNODELIBRARYREADER_H

#include "NiMaterialNodeLibrary.h"

class NIMAIN_ENTRY NiMaterialNodeLibraryReader : public NiRefObject
{
public:
    virtual NiMaterialNodeLibrary* Load(const char* pcFilename) = 0;
};

typedef efd::SmartPointer<NiMaterialNodeLibraryReader> NiMaterialNodeLibraryReaderPtr;

#endif  //#ifndef NIMATERIALNODELIBRARYREADER_H
