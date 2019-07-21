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
#ifndef NID3DSHADERFACTORY_H
#define NID3DSHADERFACTORY_H

#include <NiShaderFactory.h>
#include "NiD3DDefines.h"
#include "NiD3DError.h"
#include "NiGlobalConstantEntry.h"
#include "NiTStringMap.h"

#include <efd/ThreadLocal.h>

class NiD3DShaderLibrary;
class NiD3DShaderInterface;
class NiRenderer;

// NiD3DShaderFactory
class NID3D_ENTRY NiD3DShaderFactory : public NiShaderFactory
{
protected:
    NiD3DShaderFactory();

public:
    virtual ~NiD3DShaderFactory();

    virtual NiShader* RetrieveShader(const char* pcName,
        unsigned int uiImplementation, bool bReportNotFound = true);
    virtual NiShader* FindShader(const char* pcName,
        unsigned int uiImplementation);

    virtual bool ReleaseShaderFromLibrary(const char* pcName,
        unsigned int uiImplementation);
    virtual bool ReleaseShaderFromLibrary(NiShader* pkShader);

    // *** begin Emergent internal use only ***
    virtual void SetRenderer(NiD3DRenderer* pkRenderer);

    virtual void InsertShader(NiShader* pkShader,
        unsigned int uiImplementation);
    virtual void RemoveShader(const char* pcName,
        unsigned int uiImplementation);
    virtual void RemoveAllShaders();

    virtual void InsertLibrary(NiShaderLibrary* pkLibrary);
    virtual NiShaderLibrary* FindLibrary(const char* pcName);
    virtual void RemoveLibrary(const char* pcName);
    virtual void RemoveAllLibraries();
    virtual NiShaderLibrary* GetFirstLibrary();
    virtual NiShaderLibrary* GetNextLibrary();

    virtual void PurgeAllShaderRendererData();
    virtual void RestoreAllShaderRendererData();
#if defined(_USRDLL)
    virtual void FreeLibraryDLLs();
    virtual void* GetFirstLibraryDLL(const char*& pcName);
    virtual void* GetNextLibraryDLL(const char*& pcName);
    virtual void ClearLibraryDLLs();
#endif
    virtual bool IsDefaultImplementation(NiShader* pkShader);

    static void _SDMInit();
    static void _SDMShutdown();

    static NiShaderFactory* Create();
    static void Destroy();

    virtual unsigned int GetMajorVertexShaderVersion(
        const unsigned int uiVersion);
    virtual unsigned int GetMinorVertexShaderVersion(
        const unsigned int uiVersion);
    virtual unsigned int CreateVertexShaderVersion(
        const unsigned int uiMajorVersion, const unsigned int uiMinorVersion);
    virtual unsigned int GetMajorGeometryShaderVersion(
        const unsigned int uiVersion);
    virtual unsigned int GetMinorGeometryShaderVersion(
        const unsigned int uiVersion);
    virtual unsigned int CreateGeometryShaderVersion(
        const unsigned int uiMajorVersion, const unsigned int uiMinorVersion);
    virtual unsigned int GetMajorPixelShaderVersion(
        const unsigned int uiVersion);
    virtual unsigned int GetMinorPixelShaderVersion(
        const unsigned int uiVersion);
    virtual unsigned int CreatePixelShaderVersion(
        const unsigned int uiMajorVersion, const unsigned int uiMinorVersion);

    bool SetAsActiveFactory();
    static bool IsActiveFactory();
    static NiD3DShaderFactory* GetD3DShaderFactory();

    virtual const char* GetRendererString() const;

    virtual NISHADERFACTORY_CLASSCREATIONCALLBACK
        GetDefaultClassCreateCallback() const;
    virtual NISHADERFACTORY_RUNPARSERCALLBACK GetDefaultRunParserCallback()
        const;
    virtual NISHADERFACTORY_ERRORCALLBACK GetDefaultErrorCallback() const;
    // *** end Emergent internal use only ***

protected:
    virtual const char* GetFirstProgramDirectory(NiTListIterator& kIter);
    virtual const char* GetNextProgramDirectory(NiTListIterator& kIter);
    virtual void AddProgramDirectory(const char* pacDirectory);
    virtual void RemoveProgramDirectory(const char* pacDirectory);
    virtual void RemoveAllProgramDirectories();

    static const char* GetCompilerName(unsigned int uiVersion);

    NiD3DRenderer* m_pkRenderer;

    NiTStringPointerMap<NiShader*>* m_pkShaderMap;
    efd::ThreadLocal<NiTMapIterator> m_kLibraryIter;
    NiTStringPointerMap<NiShaderLibraryPtr>* m_pkLibraryMap;

    efd::CriticalSection m_kShaderMapLock;

    static unsigned int ms_uiNewShaderValue;

    // Default Class Creation and RunParser functions.
    // For DLL configurations, this will attempt to explicitly load
    // DLLs that have not already been implicitly loaded.
    static bool DefaultCreateClass(const char* pcLibName,
        NiRenderer* pkRenderer, int iDirectoryCount,
        const char* apcDirectories[], bool bRecurseSubFolders,
        NiShaderLibrary** ppkLibrary);
    static unsigned int DefaultRunParser(const char* pcLibName,
        NiRenderer* pkRenderer, const char* pcDirectory,
        bool bRecurseSubFolders);

#if defined(_USRDLL)
    efd::ThreadLocal<NiTMapIterator> m_kLibraryDLLIter;
    NiTStringMap<HMODULE> m_kLoadedShaderLibDLLs;
#endif //#if defined(_USRDLL)

    static NiD3DShaderFactory* ms_pkD3DShaderFactory;
};

typedef efd::SmartPointer<NiD3DShaderFactory> NiD3DShaderFactoryPtr;

#endif  //#ifndef NID3DSHADERFACTORY_H
