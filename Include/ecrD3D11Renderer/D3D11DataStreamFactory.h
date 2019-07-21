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
#ifndef EE_D3D11DATASTREAMFACTORY_H
#define EE_D3D11DATASTREAMFACTORY_H

#include <ecrD3D11Renderer/ecrD3D11RendererLibType.h>
#include <ecrD3D11Renderer/D3D11Headers.h>
#include <ecrD3D11Renderer/D3D11DataStream.h>

#include <NiDataStreamFactory.h>

namespace ecr
{

/**
    D3D11DataStreamFactory is the NiDataStreamFactory implementation for the D3D11 renderer.
*/

class EE_ECRD3D11RENDERER_ENTRY D3D11DataStreamFactory : public NiDataStreamFactory
{
public:
    /// @cond EMERGENT_INTERNAL

    /// @name Construction and Destruction
    //@{
    /// Constructor
    D3D11DataStreamFactory();
    
    /// Destructor
    virtual ~D3D11DataStreamFactory();
    //@}

    /// @endcond

protected:
    /// Creates a data stream.
    virtual NiDataStream* CreateDataStreamImpl(
        const NiDataStreamElementSet& kElements,
        efd::UInt32 count,
        efd::UInt8 accessMask,
        NiDataStream::Usage usage);

    /// Creates a data stream.
    virtual NiDataStream* CreateDataStreamImpl(
        efd::UInt8 uiAccessMask,
        NiDataStream::Usage usage,
        efd::Bool canOverrideAccessMask);

    friend D3D11DataStream* D3D11DataStream::Create(ID3D11Buffer* pkBuffer);
};

}   // End namespace ecr.

#endif // EE_D3D11DATASTREAMFACTORY_H
