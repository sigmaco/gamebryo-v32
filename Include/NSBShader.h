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
#ifndef NSBSHADER_H
#define NSBSHADER_H

#include "NSBShaderLibLibType.h"
#include "NSBAttributeTable.h"
#include "NSBObjectTable.h"
#include "NSBPackingDef.h"
#include "NSBImplementation.h"
#include "NSBUserDefinedDataSet.h"
#include <NiOutputStreamDescriptor.h>

#include <NiRefObject.h>
#include <NiSmartPointer.h>

class NiBinaryShader;
NiSmartPointer(NiShaderDesc);

class NSBSHADERLIB_ENTRY NSBShader : public NiRefObject
{
protected:
    enum
    {
        MAGIC_NUMBER = 0x0062736E,  // NSB0
        // MMDDYY - version number change information
        // ------   -----------------------------------------------------------
        // 041003 - Bumped version number to 1.1 to reflect addition of
        //          UsesNiLightState requirement. (Shipped in 1.0.1)
        // 101403 - Bumped version to 1.2 to add shader targets, shader
        //          entry points, and variable names
        // 102303 - Bumped version to 1.3 to add software vertex processing
        // 033004 - Bumped version to 1.4 to add streaming of
        //          platform-specific constant map entries
        // 033104 - Bumped version to 1.5 to add streaming of a
        //          user-defined class name for implementations.
        // 010404 - Bumped version to 1.6 to add UserDefinedDataBlocks
        // 020404 - Bumped version to 1.7 to improve software vertex processing
        // 031505 - Bumped version to 1.8 to remove DX8 support
        // 031605 - Bumped version to 1.9 to add obj texture flags
        // 032805 - Bumped version to 1.10 to make NSB files endian-aware
        // 020806 - Bumped version to 1.11 to allow for NBT uv source spec.
        // 050106 - Bumped version to 1.12 to add PS3 support
        // 120106 - Bumped version to 1.13 to add D3D10 and geometry shader
        //          support.
        // 011607 - Bumped version to 1.14 to add separate NSBTexture objects.
        // 031907 - Bumped version to 1.15 to add shadow light object effect
        //          types.
        // 010208 - Bumped version to 2.00 to add semantic adapter table
        //          entries.
        // 033108 - Bumped version to 2.1 to add platform-specific shader
        //          program entries.
        // 061608 - Bumped version to 2.2 to add stream out capabilities
        // 061709 - Bumped version to 3.0 to add D3D11 support
        // 090909 - Bumped version to 3.1 to add D3D11 feature level support
        NSB_VERSION     = 0x00030001    // 3.1
    };

public:
    NSBShader();
    ~NSBShader();

    // Name
    inline const char* GetName();
    inline const char* GetDescription();

    // Shader Versions
    inline unsigned int GetMinVertexShaderVersion();
    inline unsigned int GetMaxVertexShaderVersion();
    inline unsigned int GetMinGeometryShaderVersion();
    inline unsigned int GetMaxGeometryShaderVersion();
    inline unsigned int GetMinPixelShaderVersion();
    inline unsigned int GetMaxPixelShaderVersion();
    inline unsigned int GetMinComputeShaderVersion();
    inline unsigned int GetMaxComputeShaderVersion();
    inline unsigned int GetMinUserVersion();
    inline unsigned int GetMaxUserVersion();
    inline unsigned int GetMinFeatureLevel();
    inline unsigned int GetMaxFeatureLevel();
    inline unsigned int GetPlatform();

    // Access to the attribute table
    inline NSBAttributeTable* GetGlobalAttributeTable();
    inline NSBAttributeTable* GetAttributeTable();

    // Access to the object table
    inline NSBObjectTable* GetObjectTable();

    // The packing definitions
    unsigned int GetPackingDefCount();
    NSBPackingDef* GetPackingDef(const char* pcName, bool bCreate = false);

    // The StreamOutputDescriptors
    inline void AddOutputStreamDescriptor(
        const NiOutputStreamDescriptor& kDescriptor);
    inline void ClearOutputStreamDescriptors();
    inline const NiOutputStreamDescriptorArray& GetOutputStreamDescriptors();

    // The implementations
    unsigned int GetImplementationCount();
    NSBImplementation* GetImplementation(const char* pcName,
        bool bCreate = false, unsigned int uiNextIndex = 0);
    NSBImplementation* GetImplementationByName(const char* pcName);
    NSBImplementation* GetImplementationByIndex(unsigned int uiIndex);

    inline void SetMinVertexShaderVersionRequest(unsigned int uiVersion);
    inline void SetMaxVertexShaderVersionRequest(unsigned int uiVersion);
    inline void SetMinGeometryShaderVersionRequest(unsigned int uiVersion);
    inline void SetMaxGeometryShaderVersionRequest(unsigned int uiVersion);
    inline void SetMinPixelShaderVersionRequest(unsigned int uiVersion);
    inline void SetMaxPixelShaderVersionRequest(unsigned int uiVersion);
    inline void SetMinComputeShaderVersionRequest(unsigned int uiVersion);
    inline void SetMaxComputeShaderVersionRequest(unsigned int uiVersion);
    inline void SetMinUserVersionRequest(unsigned int uiVersion);
    inline void SetMaxUserVersionRequest(unsigned int uiVersion);
    inline void SetMinFeatureLevelRequest(unsigned int uiVersion);
    inline void SetMaxFeatureLevelRequest(unsigned int uiVersion);
    inline void SetPlatformRequest(unsigned int uiPlatform);

    // *** begin Emergent internal use only
    // User defined data set
    inline NSBUserDefinedDataSet* GetUserDefinedDataSet();
    inline void SetUserDefinedDataSet(NSBUserDefinedDataSet* pkUDDSet);

    // Get the shader declaration used by tools
    const NiShaderAttributeDesc* GetTextureAttribute(unsigned int uiIndex,
        const char* pcMap) const;
    bool AddTextureAttributeDesc(const unsigned int uiTextureFlags) const;
    NiShaderDesc* GetShaderDesc();

    // These functions are used during the creation
    void SetName(const char* pcName);
    void SetDescription(const char* pcDescription);

    inline void AddVertexShaderVersion(unsigned int uiVersion);
    inline void AddGeometryShaderVersion(unsigned int uiVersion);
    inline void AddPixelShaderVersion(unsigned int uiVersion);
    inline void AddComputeShaderVersion(unsigned int uiVersion);
    inline void AddUserVersion(unsigned int uiVersion);
    inline void AddFeatureLevel(unsigned int uiVersion);
    inline void AddPlatform(unsigned int uiPlatformFlag);

    // By default, NSB shaders are saved to match the endianness of the
    // platform they are written out on (and can be loaded in on any
    // platform.)
    bool Save(const char* pcFilename, bool bSwapEndian = false);
    bool SaveBinary(efd::BinaryStream& kStream, bool bSwapEndian = false);
    bool Load(const char* pcFilename);
    bool LoadBinary(efd::BinaryStream& kStream);

    static unsigned int GetReadVersion();

#if defined(NIDEBUG)
    void Dump();
#endif  //#if defined(NIDEBUG)
    // *** end Emergent internal use only

protected:
    bool SaveBinaryPackingDefs(efd::BinaryStream& kStream);
    bool LoadBinaryPackingDefs(efd::BinaryStream& kStream);
    bool SaveBinaryImplementations(efd::BinaryStream& kStream);
    bool LoadBinaryImplementations(efd::BinaryStream& kStream);
    bool SaveBinaryOutputStreamDescriptors(efd::BinaryStream& kStream);
    bool LoadBinaryOutputStreamDescriptors(efd::BinaryStream& kStream);

    char* m_pcName;
    char* m_pcDescription;

    unsigned int m_uiMinVertexShaderVersionRequest;
    unsigned int m_uiMaxVertexShaderVersionRequest;
    unsigned int m_uiMinGeometryShaderVersionRequest;
    unsigned int m_uiMaxGeometryShaderVersionRequest;
    unsigned int m_uiMinPixelShaderVersionRequest;
    unsigned int m_uiMaxPixelShaderVersionRequest;
    unsigned int m_uiMinComputeShaderVersionRequest;
    unsigned int m_uiMaxComputeShaderVersionRequest;
    unsigned int m_uiMinUserVersionRequest;
    unsigned int m_uiMaxUserVersionRequest;
    unsigned int m_uiMinFeatureLevelRequest;
    unsigned int m_uiMaxFeatureLevelRequest;
    unsigned int m_uiPlatformRequest;

    unsigned int m_uiMinVertexShaderVersion;
    unsigned int m_uiMaxVertexShaderVersion;
    unsigned int m_uiMinGeometryShaderVersion;
    unsigned int m_uiMaxGeometryShaderVersion;
    unsigned int m_uiMinPixelShaderVersion;
    unsigned int m_uiMaxPixelShaderVersion;
    unsigned int m_uiMinComputeShaderVersion;
    unsigned int m_uiMaxComputeShaderVersion;
    unsigned int m_uiMinUserVersion;
    unsigned int m_uiMaxUserVersion;
    unsigned int m_uiMinFeatureLevel;
    unsigned int m_uiMaxFeatureLevel;
    unsigned int m_uiPlatform;

    // User defined data set
    NSBUserDefinedDataSetPtr m_spUserDefinedDataSet;

    NSBAttributeTable m_kGlobalAttribTable;
    NSBAttributeTable m_kAttribTable;
    NSBObjectTable m_kObjectTable;
    NiTStringPointerMap<NSBPackingDef*> m_kPackingDefMap;
    NiTPrimitiveArray<NSBImplementation*> m_kImplementationArray;
    NiOutputStreamDescriptorArray m_kOutputStreamDescriptors;

    NiShaderDescPtr m_spShaderDesc;

    static unsigned int ms_uiReadVersion;
};

typedef efd::SmartPointer<NSBShader> NSBShaderPtr;

#include "NSBShader.inl"

#endif  //NSBSHADER_H
