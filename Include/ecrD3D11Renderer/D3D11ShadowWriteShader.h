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
#ifndef EE_D3D11SHADOWWRITESHADER_H
#define EE_D3D11SHADOWWRITESHADER_H

#include <ecrD3D11Renderer/D3D11FragmentShader.h>

namespace ecr
{

/**
    Specialized D3D11-specific shader used by the shadowing system. 
    
    The only difference from this shader and a normal D3D11FragmentShader is that in the 
    PreProcessPipeline function this shader overrides the standard back face rendering state 
    and sets it to back face rendering state the shader has been supplied.
*/
class EE_ECRD3D11RENDERER_ENTRY D3D11ShadowWriteShader : public D3D11FragmentShader
{
    /// @cond EMERGENT_INTERNAL

    NiDeclareRTTI;

    /// @endcond
public:
    /// @name Construction and Destruction
    //@{
    /// Constructor. 
    D3D11ShadowWriteShader(NiMaterialDescriptor* pDesc);
    /// Destructor.
    virtual ~D3D11ShadowWriteShader();
    //@}

    /// Sets the back-facing render state if necessary.
    virtual efd::UInt32 PreProcessPipeline(const NiRenderCallContext& callContext);

    /// Set whether the backfaces of triangles will be rendered when creating the shadow buffer
    /// rather than the front faces.
    static void SetRenderBackfaces(efd::Bool renderBackfaces);

protected:
    static efd::Bool ms_renderBackfaces;
};

/// Define a smart pointer (reference counting, self deleting pointer) for the
/// D3D11ShadowWriteShader class.
typedef efd::SmartPointer<D3D11ShadowWriteShader> D3D11ShadowWriteShaderPtr;

}   // End namespace ecr.

#include <ecrD3D11Renderer/D3D11ShadowWriteShader.inl>

#endif // EE_D3D11SHADOWWRITESHADER_H
