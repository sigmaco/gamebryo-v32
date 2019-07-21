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
#ifndef EE_D3D11EFFECTSHADERLIBSDM_H
#define EE_D3D11EFFECTSHADERLIBSDM_H

/** @file ecrD3D11EffectShaderLibSDM.h
    This header file manages the static data initialization for the library.
*/

#include <NiStaticDataManager.h>
#include <ecrD3D11EffectShaderLib/ecrD3D11EffectShaderLibType.h>

namespace ecr
{

EE_DECLARE_SDM(ecrD3D11EffectShaderLib, EE_ECRD3D11EFFECTSHADER_ENTRY)

}   // End namespace ecr.

#endif // EE_D3D11EFFECTSHADERLIBSDM_H
