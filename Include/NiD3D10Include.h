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

#ifndef NID3D10INCLUDE_H
#define NID3D10INCLUDE_H

#include <NiD3D10RendererLibType.h>
#include <NiSystem.h>
#include <NiFilename.h>

#include <NiSystem.h>
#include <NiFilename.h>
#include <NiD3D10Headers.h>



class NID3D10RENDERER_ENTRY NiD3D10Include : public ID3D10Include
{
public:
    void SetBasePath(const char* pcBasePath);

    virtual HRESULT STDMETHODCALLTYPE Open(D3D10_INCLUDE_TYPE IncludeType,
        LPCSTR pFileName, LPCVOID pParentData, LPCVOID *ppData, UINT *pBytes);
    virtual HRESULT STDMETHODCALLTYPE Close(LPCVOID pData);

protected:
    char m_acBasePath[NI_MAX_PATH];
};

#endif  // #ifndef NID3D10INCLUDE_H
