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
#ifndef EE_D3D11RENDERERSDM_H
#define EE_D3D11RENDERERSDM_H

/** @file ecrD3D11RendererSDM.h
    This header file manages the static data initialization for the library.
*/

#include <NiStaticDataManager.h>
#include <ecrD3D11Renderer/ecrD3D11RendererLibType.h>

namespace ecr
{

    EE_DECLARE_SDM(ecrD3D11Renderer, EE_ECRD3D11RENDERER_ENTRY);

}

#endif // EE_D3D11RENDERERSDM_H
