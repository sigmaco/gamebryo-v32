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
#ifndef EE_D3D11SHADERPROGRAM_H
#define EE_D3D11SHADERPROGRAM_H

#include <ecrD3D11Renderer/ecrD3D11RendererLibType.h>
#include <ecrD3D11Renderer/D3D11Headers.h>

#include <efd/FixedString.h>
#include <NiGPUProgram.h>

namespace ecr
{

class D3D11ShaderProgramCreator;

/**
    Base class for managing D3D11 vertex, hull, domain, geometry, pixel, or compute shader programs.
*/
class EE_ECRD3D11RENDERER_ENTRY D3D11ShaderProgram : public NiGPUProgram
{
    /// @cond EMERGENT_INTERNAL

    NiDeclareRTTI;

    /// @endcond

public:
    /// @name Construction and Destruction
    //@{
    /// Constructor, which takes a shader type and the compiled shader byte code as an ID3DBlob.
    D3D11ShaderProgram(NiGPUProgram::ProgramType shaderType, ID3DBlob* pkShaderByteCode);
    /// Destructor
    virtual ~D3D11ShaderProgram();
    //@}

    /// Return the name of the shader program.
    inline const efd::FixedString& GetName() const;
    /// Set the name of the shader program.
    inline void SetName(const efd::FixedString& shaderName);

    /// Return the compiled shader byte code for the shader program.
    inline ID3DBlob* GetShaderByteCode() const;
    /// Set the compiled shader byte code for the shader program.
    void SetShaderByteCode(ID3DBlob* pShaderByteCode);

    /// Return the D3D11ShaderProgramCreator used to create the shader program.
    inline D3D11ShaderProgramCreator* GetCreator() const;
    /// Set the D3D11ShaderProgramCreator used to create the shader program - this should not be
    /// called by an application.
    inline void SetCreator(D3D11ShaderProgramCreator* pCreator);

    /// Release any devices-specific data for the shader program.
    virtual void DestroyRendererData() = 0;
    /// Recreate any devices-specific data for the shader program.
    virtual void RecreateRendererData() = 0;

    /// Set the shader reflection for a shader program.
    void SetShaderReflection(ID3D11ShaderReflection* pkReflection);
    /// Return the shader reflection for a shader program.
    inline ID3D11ShaderReflection* GetShaderReflection() const;
    /// Release the shader reflection for a shader program.
    inline void ClearShaderReflection();

protected:
    efd::FixedString m_name;

    ID3DBlob* m_pShaderByteCode;
    D3D11ShaderProgramCreator* m_pCreator;

    ID3D11ShaderReflection* m_pReflection;
};

/// Define a smart pointer (reference counting, self deleting pointer) for the D3D11ShaderProgram
/// class.
typedef efd::SmartPointer<D3D11ShaderProgram> D3D11ShaderProgramPtr;

}   // End namespace ecr.

#include <ecrD3D11Renderer/D3D11ShaderProgram.inl>

#endif // EE_D3D11SHADERPROGRAM_H
