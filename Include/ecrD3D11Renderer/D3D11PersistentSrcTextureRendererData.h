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
#ifndef EE_D3D11PERSISTENTSRCTEXTURERENDERERDATA_H
#define EE_D3D11PERSISTENTSRCTEXTURERENDERERDATA_H

#include <ecrD3D11Renderer/D3D11TextureData.h>

#include <NiPersistentSrcTextureRendererData.h>

namespace ecr
{
/**
    D3D11-specific implementation of NiPersistentSrcTextureRendererData.
*/
class EE_ECRD3D11RENDERER_ENTRY D3D11PersistentSrcTextureRendererData :
    public NiPersistentSrcTextureRendererData
{
    /// @cond EMERGENT_INTERNAL

    NiDeclareStream;
    NiDeclareRTTI;
    NiDeclareViewerStrings;

    /// @endcond

public:
    /// @name Construction and Destruction
    //@{
    /// Destructor
    virtual ~D3D11PersistentSrcTextureRendererData();
    //@}

    /// @cond EMERGENT_INTERNAL

    /// Override Streamable RTTI name
    virtual bool GetStreamableRTTIName(efd::Char* rttiName, efd::UInt32 maxSize) const;

    /// @endcond

protected:
    /// Hidden constuctor
    D3D11PersistentSrcTextureRendererData();
};

/// Define a smart pointer (reference counting, self deleting pointer) for the
/// D3D11DynamicTextureData class.
typedef efd::SmartPointer<D3D11DynamicTextureData> D3D11DynamicTextureDataPtr;

}   // End namespace ecr.

#endif // EE_D3D11PERSISTENTSRCTEXTURERENDERERDATA_H
