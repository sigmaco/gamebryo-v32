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
#ifndef NICUBEMAPDEPTHSTENCILBUFFER_H
#define NICUBEMAPDEPTHSTENCILBUFFER_H

#include "NiD3D10RendererLibType.h"

#include <NiDepthStencilBuffer.h>

class NID3D10RENDERER_ENTRY NiCubeMapDepthStencilBuffer :
    public NiDepthStencilBuffer
{
public:
    NiDeclareRTTI;

public:
    virtual ~NiCubeMapDepthStencilBuffer();

    static NiCubeMapDepthStencilBuffer* Create(unsigned int uiWidth,
        unsigned int uiHeight, NiRenderer* pkRenderer,
        const NiPixelFormat& kFormat,
        MultiSamplePreference eMSAAPref = MULTISAMPLE_NONE);

protected:
    NiCubeMapDepthStencilBuffer();

    virtual bool CreateRendererData(const NiPixelFormat& pkFormat,
        Ni2DBuffer::MultiSamplePreference eMSAAPref =
        Ni2DBuffer::MULTISAMPLE_NONE);

};

NiSmartPointer(NiCubeMapDepthStencilBuffer);

#endif // NICUBEMAPDEPTHSTENCILBUFFER_H
