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
#ifndef NIDRAWSCENEUTILITY_H
#define NIDRAWSCENEUTILITY_H

#include "NiCullingProcess.h"

NIMAIN_ENTRY unsigned int NiDrawScene(NiCamera* pkCamera, NiAVObject* pkScene,
    NiCullingProcess& kCuller, NiVisibleArray* pkVisibleSet = 0);

NIMAIN_ENTRY unsigned int NiCullScene(NiCamera* pkCamera, NiAVObject* pkScene,
    NiCullingProcess& kCuller, NiVisibleArray& pkVisibleSet,
    bool bResetArray = true);

NIMAIN_ENTRY unsigned int NiDrawVisibleArray(NiCamera* pkCamera,
    NiVisibleArray& kVisibleSet);

NIMAIN_ENTRY unsigned int NiDrawVisibleArrayAppend(
    NiVisibleArray& kVisibleSet);

#endif
