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
#ifndef EE_D3D11ERRORSHADER_H
#define EE_D3D11ERRORSHADER_H

#include <ecrD3D11Renderer/D3D11ShaderCore.h>

namespace ecr
{

/**
    ecr::D3D11ErrorShader is a special error shader meant to clearly identify when a shader 
    otherwise fails to be applied to an object. 
    
    The D3D11ErrorShader will oscillate 10% of the radius of the geometry's bounding volume, 
    and will randomly change colors every frame. This behavior is very irritating to look at, 
    and should immediately visually identify when there a problem.
*/
class EE_ECRD3D11RENDERER_ENTRY D3D11ErrorShader : public D3D11ShaderCore
{
    /// @cond EMERGENT_INTERNAL

    NiDeclareRTTI;

    /// @endcond
public:
    /// @cond EMERGENT_INTERNAL

    /// @name Construction and Destruction
    //@{
    /// Constructor - only the Gamebryo D3D11 renderer should create instances of this class.
    D3D11ErrorShader();

    /// Destructor
    virtual ~D3D11ErrorShader();
    //@}

    /// Initialize the shader by creating the shader programs and input layout.
    virtual efd::Bool Initialize();

    /// Randomly select the offset position and color for this frame.
    virtual unsigned int SetupTransformations(const NiRenderCallContext& callContext);
    /// Perform rendering
    virtual void Do_RenderMeshes(NiVisibleArray* pVisibleArray);

    /// @endcond

protected:
    /// Create the D3D11Pass object.
    efd::Bool CreateStagesAndPasses();
    /// Create the input layout.
    efd::Bool CreateShaderDeclaration();
    /// Create the vertex and pixel shader.
    efd::Bool CreateShaders();

    XMFLOAT4 m_materialColor;

    D3D11Pass* m_pPass;
};

/// Define a smart pointer (reference counting, self deleting pointer) for the D3D11ErrorShader
/// class.
typedef efd::SmartPointer<D3D11ErrorShader> D3D11ErrorShaderPtr;

}   // End namespace ecr.

#endif // EE_D3D11ERRORSHADER_H
