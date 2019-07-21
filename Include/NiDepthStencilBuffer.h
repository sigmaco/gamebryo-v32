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
#ifndef NIDEPTHSTENCILBUFFER_H
#define NIDEPTHSTENCILBUFFER_H

#include "Ni2DBuffer.h"

class NIMAIN_ENTRY NiDepthStencilBuffer : public Ni2DBuffer
{
public:
    NiDeclareRTTI;

public:
    virtual ~NiDepthStencilBuffer();

    static NiDepthStencilBuffer* Create(unsigned int uiWidth,
        unsigned int uiHeight, NiRenderer* pkRenderer,
        const NiPixelFormat& kFormat,
        Ni2DBuffer::MultiSamplePreference eMSAAPref =
        Ni2DBuffer::MULTISAMPLE_NONE);
    static NiDepthStencilBuffer* CreateCompatible(Ni2DBuffer* pkBuffer,
        NiRenderer* pkRenderer);

    /*** begin Emergent internal use only ***/
    static NiDepthStencilBuffer* Create(unsigned int uiWidth,
        unsigned int uiHeight, Ni2DBuffer::RendererData* pkData);
    /*** end Emergent internal use only ***/

protected:
    NiDepthStencilBuffer();

    virtual bool CreateRendererData(const NiPixelFormat& pkFormat,
        Ni2DBuffer::MultiSamplePreference eMSAAPref =
        Ni2DBuffer::MULTISAMPLE_NONE);
};

typedef efd::SmartPointer<NiDepthStencilBuffer> NiDepthStencilBufferPtr;

#endif
