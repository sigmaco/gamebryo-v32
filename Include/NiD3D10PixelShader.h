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
#ifndef NID3D10PIXELSHADER_H
#define NID3D10PIXELSHADER_H

#include "NiD3D10ShaderProgram.h"
#include "NiD3D10Headers.h"

class NID3D10RENDERER_ENTRY NiD3D10PixelShader : public NiD3D10ShaderProgram
{
    NiDeclareRTTI;

public:
    NiD3D10PixelShader();
    NiD3D10PixelShader(ID3D10PixelShader* pkPixelShader,
        ID3D10Blob* pkShaderByteCode);
    virtual ~NiD3D10PixelShader();

    inline ID3D10PixelShader* GetPixelShader() const;
    void SetPixelShader(ID3D10PixelShader* pkPixelShader);

    virtual void DestroyRendererData();
    virtual void RecreateRendererData();

protected:
    ID3D10PixelShader* m_pkPixelShader;
};

NiSmartPointer(NiD3D10PixelShader);

#include "NiD3D10PixelShader.inl"

#endif // NID3D10PIXELSHADER_H