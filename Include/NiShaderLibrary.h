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
#ifndef NISHADERLIBRARY_H
#define NISHADERLIBRARY_H

#include "NiRefObject.h"
#include "NiSmartPointer.h"

NiSmartPointer(NiShader);

class NiRenderer;
class NiShaderLibraryDesc;

// NiShaderLibrary
class NIMAIN_ENTRY NiShaderLibrary : public NiRefObject
{
public:
    NiShaderLibrary(const char* pcName);
    virtual ~NiShaderLibrary();

    const char* GetName();
    void SetName(const char* pcName);

    virtual efd::SystemDesc::RendererID GetRendererID() const = 0;

    virtual NiShader* GetShader(NiRenderer* pkRenderer, const char* pcName,
        unsigned int uiImplementation);

    virtual bool ReleaseShader(const char* pcName,
        unsigned int uiImplementation);
    virtual bool ReleaseShader(NiShader* pkShader);

    virtual NiShaderLibraryDesc* GetShaderLibraryDesc() = 0;

    virtual unsigned int GetNumSupportedMimeTypes() const;
    virtual const char* GetSupportedMimeType(unsigned int uiIdx) const;

    virtual bool LoadShader(const char* pcFile) = 0;

    // *** begin Emergent internal use only ***
    virtual void SetShaderLibraryDesc(NiShaderLibraryDesc* pkLibDesc) = 0;
    // *** end Emergent internal use only ***

protected:
    char* m_pcName;
};

typedef efd::SmartPointer<NiShaderLibrary> NiShaderLibraryPtr;

#endif  //#ifndef NISHADERLIBRARY_H
