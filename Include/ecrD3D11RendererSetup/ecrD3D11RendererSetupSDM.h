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
#ifndef EE_ECRD3D11RENDERERSETUPSDM_H
#define EE_ECRD3D11RENDERERSETUPSDM_H

/** @file ecrD3D11RendererSetupSDM.h
    This header file manages the static data initialization for the library.
*/

#include <ecrD3D11RendererSetup/ecrD3D11RendererSetupLibType.h>
#include <NiStaticDataManager.h>

namespace ecr
{

EE_DECLARE_SDM(ecrD3D11RendererSetup, EE_ECRD3D11RENDERERSETUP_ENTRY)

}   // End namespace ecr.

#endif // EE_ECRD3D11RENDERERSETUPSDM_H
