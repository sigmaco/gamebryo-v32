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
#ifndef EE_D3D11SHADERLIBRARY_H
#define EE_D3D11SHADERLIBRARY_H

#include <ecrD3D11Renderer/ecrD3D11RendererLibType.h>

#include <NiShaderLibrary.h>
#include <NiShaderLibraryDesc.h>

namespace ecr
{

/**
    D3D11 implementation of NiShaderLibrary.

    The class introduces a directory member, ms_pDirectory, which is intended to provide 
    derived libraries with a common place to look for shaders. The platforms the library is 
    valid on are also identified in the static member ms_platform. 

    The description of the library is held in the m_spShaderLibraryDesc member, which is an 
    instance of an NiShaderLibraryDesc class.
*/

class EE_ECRD3D11RENDERER_ENTRY D3D11ShaderLibrary : public NiShaderLibrary
{
public:
    /// @name Construction and Destruction
    //@{
    /// Constructor - takes the name of the shader library to create
    D3D11ShaderLibrary(const efd::Char* pName);
    /// Destructor
    virtual ~D3D11ShaderLibrary();
    //@}

    /// Returns the RendererID that this shader library was created for.
    virtual efd::SystemDesc::RendererID GetRendererID() const;

    /// Set the static directory string to the given directory.
    static void SetDirectoryInfo(const efd::Char* pDirectory);
    /// Return the static directory string.
    static const efd::Char* GetDirectory();
    /// Set the static platform flags.
    static void SetPlatform(efd::UInt32 platform);
    /// Return the static directory string.
    static efd::UInt32 GetPlatform();

    /// Return a description of the shader library.
    virtual NiShaderLibraryDesc* GetShaderLibraryDesc();

    /// @cond EMERGENT_INTERNAL

    /// Set a description of the shader library.
    virtual void SetShaderLibraryDesc(NiShaderLibraryDesc* pLibDesc);

    /// @endcond

protected:
    static efd::CriticalSection ms_criticalSection;
    static efd::Char* ms_pDirectory;
    static efd::UInt32 ms_platform;

    NiShaderLibraryDescPtr m_spShaderLibraryDesc;
};

/// Define a smart pointer (reference counting, self deleting pointer) for the D3D11ShaderLibrary
/// class.
typedef efd::SmartPointer<D3D11ShaderLibrary> D3D11ShaderLibraryPtr;

}   // End namespace ecr.

#endif // EE_D3D11SHADERLIBRARY_H
