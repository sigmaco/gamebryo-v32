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
#ifndef NSBCONSTANTMAP_H
#define NSBCONSTANTMAP_H

#include <efd/BinaryStream.h>
#include <NiTPointerList.h>

#include <NiShader.h>
#include <NiShaderConstantMapEntry.h>

#include "NSBShaderLibLibType.h"
#include "NSBUtility.h"

class NiShaderConstantMap;
class NiShaderDesc;

class NSBSHADERLIB_ENTRY NSBConstantMap : public NiRefObject
{
public:
    NSBConstantMap();
    virtual ~NSBConstantMap();

    // Name
    inline const char* GetName() const;
    void SetName(const char* pcName);

    // Usage
    inline unsigned int GetProgramType();
    inline void SetProgramType(unsigned int uiUsage);

    // Entry
    class NSBCM_Entry : public NiShaderConstantMapEntry
    {
    public:
        NSBCM_Entry();
        ~NSBCM_Entry();

        // *** begin Emergent internal use only
        bool SaveBinary(efd::BinaryStream& kStream);
        bool LoadBinary(efd::BinaryStream& kStream);

        unsigned int GetComponentSize() const;
        // *** end Emergent internal use only
    };

    unsigned int GetGlobalEntryCount();
    unsigned int GetPlatformEntryCount(NiShader::Platform ePlatform);
    unsigned int GetTotalEntryCount();

    virtual bool AddEntry(const char* pcKey, unsigned int uiFlags,
        unsigned int uiExtra, unsigned int uiReg, unsigned int uiCount,
        const char* pcVariableName, unsigned int uiSize = 0,
        unsigned int uiStride = 0, void* pvSource = 0,
        bool bCopyData = false);
    virtual bool AddPlatformSpecificEntry(unsigned int uiPlatformFlags,
        const char* pcKey, unsigned int uiFlags, unsigned int uiExtra,
        unsigned int uiReg, unsigned int uiCount, const char* pcVariableName,
        unsigned int uiSize = 0, unsigned int uiStride = 0,
        void* pvSource = 0, bool bCopyData = false);

    NSBCM_Entry* GetFirstEntry(NiTListIterator& kter);
    NSBCM_Entry* GetNextEntry(NiTListIterator& kter);

    NSBCM_Entry* GetFirstPlatformEntry(NiShader::Platform ePlatform, NiTListIterator& kter);
    NSBCM_Entry* GetNextPlatformEntry(NiShader::Platform ePlatform, NiTListIterator& kter);

    NSBCM_Entry* GetEntryByKey(const char* pcKey);
    NSBCM_Entry* GetEntryByIndex(unsigned int uiIndex);
    unsigned int GetEntryIndexByKey(const char* pcKey);

    NSBCM_Entry* GetPlatformEntryByKey(NiShader::Platform ePlatform,
        const char* pcKey);
    unsigned int GetPlatformEntryIndexByKey(NiShader::Platform ePlatform,
        const char* pcKey);

    // *** begin Emergent internal use only
    virtual bool SaveBinary(efd::BinaryStream& kStream);
    virtual bool LoadBinary(efd::BinaryStream& kStream);

#if defined(NIDEBUG)
    virtual void Dump(FILE* pf);
#endif  //#if defined(NIDEBUG)

    // Explicitly defining this array to size 6 so future changes to 
    // NiGPUProgram::ProgramType won't break NSB streaming.
    enum
    {
        NSB_SHADER_TYPE_COUNT = 6
    };

    // *** end Emergent internal use only

protected:
    NSBCM_Entry* CreateEntry(const char* pcKey,
        unsigned int uiFlags, unsigned int uiExtra, unsigned int uiReg,
        unsigned int uiCount, const char* pcVariableName, unsigned int uiSize,
        unsigned int uiStride, void* pvSource, bool bCopyData);
    bool AddPlatformSpecificEntry_DX9(const char* pcKey, unsigned int uiFlags,
        unsigned int uiExtra, unsigned int uiReg, unsigned int uiCount,
        const char* pcVariableName, unsigned int uiSize, unsigned int uiStride,
        void* pvSource, bool bCopyData);
    bool AddPlatformSpecificEntry_Xenon(const char* pcKey,
        unsigned int uiFlags, unsigned int uiExtra, unsigned int uiReg,
        unsigned int uiCount, const char* pcVariableName, unsigned int uiSize,
        unsigned int uiStride, void* pvSource, bool bCopyData);
    bool AddPlatformSpecificEntry_PS3(const char* pcKey, unsigned int uiFlags,
        unsigned int uiExtra, unsigned int uiReg, unsigned int uiCount,
        const char* pcVariableName, unsigned int uiSize,
        unsigned int uiStride, void* pvSource, bool bCopyData);
    bool AddPlatformSpecificEntry_D3D10(const char* pcKey,
        unsigned int uiFlags, unsigned int uiExtra, unsigned int uiReg,
        unsigned int uiCount, const char* pcVariableName, unsigned int uiSize,
        unsigned int uiStride, void* pvSource, bool bCopyData);
    bool AddPlatformSpecificEntry_D3D11(const char* pcKey,
        unsigned int uiFlags, unsigned int uiExtra, unsigned int uiReg,
        unsigned int uiCount, const char* pcVariableName, unsigned int uiSize,
        unsigned int uiStride, void* pvSource, bool bCopyData);

    bool GetPlatformListPointers(NiShader::Platform ePlatform,
        NiTPointerList<NSBCM_Entry*>*& pkEntryList);

    virtual bool SaveBinaryEntries(efd::BinaryStream& kStream);
    virtual bool LoadBinaryEntries(efd::BinaryStream& kStream);

    char* m_pcName;

    unsigned int m_uiProgramType;

    NiTPointerList<NSBCM_Entry*> m_kEntryList;
    NiTPointerList<NSBCM_Entry*> m_kEntryList_DX9;
    NiTPointerList<NSBCM_Entry*> m_kEntryList_Xenon;
    NiTPointerList<NSBCM_Entry*> m_kEntryList_PS3;
    NiTPointerList<NSBCM_Entry*> m_kEntryList_D3D10;
    NiTPointerList<NSBCM_Entry*> m_kEntryList_D3D11;
};

NiSmartPointer(NSBConstantMap);

#include "NSBConstantMap.inl"

#endif  //NSBCONSTANTMAP_H
