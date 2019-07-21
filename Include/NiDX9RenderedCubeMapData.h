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
#ifndef NIDX9RENDEREDCUBEMAPDATA_H
#define NIDX9RENDEREDCUBEMAPDATA_H

#include "NiDX9RenderedTextureData.h"
#include <NiRenderedCubeMap.h>

class NiDX9Renderer;
class NiDX9TextureRenderTarget;

class NIDX9RENDERER_ENTRY NiDX9RenderedCubeMapData :
    public NiDX9RenderedTextureData
{
public:
    static NiDX9RenderedCubeMapData* Create(NiRenderedCubeMap* pkTexture,
        NiDX9Renderer* pkRenderer);
    virtual ~NiDX9RenderedCubeMapData();

protected:
    NiDX9RenderedCubeMapData(NiRenderedCubeMap* pkTexture,
        NiDX9Renderer* pkRenderer);
    const NiPixelFormat* CreateSurf(const NiRenderedCubeMap* pkTexture);
};

#endif  //#ifndef NIDX9RENDEREDEXTUREDATA_H
