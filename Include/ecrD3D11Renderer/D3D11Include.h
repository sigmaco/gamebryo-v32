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
#ifndef EE_D3D11INCLUDE_H
#define EE_D3D11INCLUDE_H

#include <ecrD3D11Renderer/ecrD3D11RendererLibType.h>
#include <ecrD3D11Renderer/D3D11Headers.h>

namespace ecr
{

/**
    A Gamebryo-specific implementation of ID3DInclude that allows applications to provide search 
    paths for files included by shaders.
*/
class EE_ECRD3D11RENDERER_ENTRY D3D11Include : public ID3DInclude
{
public:
    /// Sets the path that will be searched for an include file.
    void SetBasePath(const efd::Char* pBasePath);

    /// @cond EMERGENT_INTERNAL

    /// Override of ID3DInclude::Open, which searches the provided base path for include files.
    virtual HRESULT STDMETHODCALLTYPE Open(
        D3D_INCLUDE_TYPE IncludeType,
        LPCSTR pFileName, 
        LPCVOID pParentData, 
        LPCVOID *ppData, 
        UINT *pBytes);
    /// Override of ID3DInclude::Close.
    virtual HRESULT STDMETHODCALLTYPE Close(LPCVOID pData);

    /// @endcond

protected:
    efd::Char m_basePath[efd::EE_MAX_PATH];
};

}   // End namespace ecr.

#endif // EE_D3D11INCLUDE_H
