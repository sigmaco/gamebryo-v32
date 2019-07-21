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
#ifndef NIDX9ERRORSHADER_H
#define NIDX9ERRORSHADER_H

#include "NiD3DShader.h"

class NID3D_ENTRY NiDX9ErrorShader : public NiD3DShader
{
    NiDeclareRTTI;
public:
    NiDX9ErrorShader();
    virtual ~NiDX9ErrorShader();

    virtual bool Initialize();

    // Override these functions to implement a custom pipeline...
    virtual unsigned int UpdatePipeline(const NiRenderCallContext& kRCC);
    virtual unsigned int SetupTransformations(const NiRenderCallContext& kRCC);
    virtual void Do_RenderMeshes(NiVisibleArray* pkVisibleArray);

protected:
    bool CreateStagesAndPasses();
    bool CreateShaderDeclaration();

    NiD3DPass* m_pkPass;
};

typedef efd::SmartPointer<NiDX9ErrorShader> NiDX9ErrorShaderPtr;

#endif  //#ifndef NIDX9ERRORSHADER_H
