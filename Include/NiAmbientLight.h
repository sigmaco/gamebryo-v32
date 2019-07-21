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
#ifndef NIAMBIENTLIGHT_H
#define NIAMBIENTLIGHT_H

#include "NiLight.h"

class NIMAIN_ENTRY NiAmbientLight : public NiLight
{
    NiDeclareRTTI;
    NiDeclareClone(NiAmbientLight);
    NiDeclareStream;
    NiDeclareViewerStrings;

public:
    NiAmbientLight();

};

typedef efd::SmartPointer<NiAmbientLight> NiAmbientLightPtr;

#include "NiAmbientLight.inl"

#endif
