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
#ifndef NSBLOADER_H
#define NSBLOADER_H

#include <NiMain.h>
#include <NiMemObject.h>
#include <NSBShader.h>

class NSBSHADERLIB_ENTRY NSBLoader : public NiMemObject
{
protected:
    NSBLoader();

public:
    ~NSBLoader();

    static NSBLoader* GetInstance();
    static void Release();

    // Returns true if any shaders are loaded.
    bool LoadAllNSBFiles(const char* pcDirectory, bool bRecurseDirectories);
    // Returns true if a shader was loaded, false if failed or already loaded.
    bool LoadNSBFile(const char* pcFile);

    unsigned int GetBinaryFileCount();
    const char* GetFirstBinaryFile(NiTListIterator& kIter);
    const char* GetNextBinaryFile(NiTListIterator& kIter);

    NSBShader* GetNSBShader(const char* pcName);

    unsigned int GetNSBShaderCount();
    NSBShader* GetFirstNSBShader(NiTListIterator& kIter);
    NSBShader* GetNextNSBShader(NiTListIterator& kIter);

protected:
    void FindAllNSBFiles(const char* pcDirectory,
        bool bRecurseDirectories);
    unsigned int LoadAllNSBFilesInDirectory(const char* pcDirectory,
        const char* pcExt, bool bRecurseDirectories,
        NiTPointerList<char*>* pkFileList);

    bool ProcessNSBFile(const char* pcFilename, const char* pcExt,
        NiTPointerList<char*>* pkFileList);

    bool LoadAllNSBFiles();

    bool InsertNSBShaderIntoList(NSBShader* pkNSBShader);

    static efd::CriticalSection m_kCriticalSection;
    static NSBLoader* ms_pkLoader;

    unsigned int m_uiRefCount;

    NiTPointerList<char*> m_kBinaryList;
    NiTPointerList<NSBShaderPtr> m_kNSBShaderList;
};

#endif  //NSBLOADER_H
