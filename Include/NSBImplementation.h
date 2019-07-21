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
#ifndef NSBIMPLEMENTATION_H
#define NSBIMPLEMENTATION_H

#include "NSBShaderLibLibType.h"
#include "NSBRequirements.h"
#include "NSBRenderStates.h"
#include "NSBStateGroup.h"
#include "NSBConstantMap.h"
#include "NSBUserDefinedDataSet.h"

class NSBPass;
class NSBShader;

class NSBSHADERLIB_ENTRY NSBImplementation : public NiMemObject
{
public:
    NSBImplementation();
    ~NSBImplementation();

    // Name
    inline const char* GetName();
    void SetName(const char* pcName);
    inline const char* GetDesc();
    void SetDesc(const char* pcDesc);

    // User-defined class name
    inline const char* GetClassName();
    void SetClassName(const char* pcClassName);

    // Requirements
    NSBRequirements* GetRequirements();

    // PackingDef
    inline const char* GetPackingDef();
    void SetPackingDef(const char* pcPackingDef);

    // RenderStateGroup
    NSBStateGroup* GetRenderStateGroup();

    // Constant Maps
    inline unsigned int GetVertexConstantMapCount();
    inline unsigned int GetGeometryConstantMapCount();
    inline unsigned int GetPixelConstantMapCount();
    NSBConstantMap* GetVertexConstantMap(unsigned int uiIndex);
    NSBConstantMap* GetGeometryConstantMap(unsigned int uiIndex);
    NSBConstantMap* GetPixelConstantMap(unsigned int uiIndex);

    inline unsigned int GetConstantMapCount(NiGPUProgram::ProgramType eType);
    NSBConstantMap* GetConstantMap(NiGPUProgram::ProgramType eType, unsigned int uiIndex);
    unsigned int AddConstantMap(NiGPUProgram::ProgramType eType);

    // Passes
    unsigned int GetPassCount();
    NSBPass* GetPass(unsigned int uiIndex, bool bCreate = true);

    // User defined data set
    inline NSBUserDefinedDataSet* GetUserDefinedDataSet();
    inline void SetUserDefinedDataSet(NSBUserDefinedDataSet* pkUDDSet);

    // Semantic adapter table
    inline const NiSemanticAdapterTable& GetSemanticAdapterTable() const;
    inline NiSemanticAdapterTable& GetSemanticAdapterTable();

    // *** begin Emergent internal use only
    // Index
    inline unsigned int GetIndex();
    inline void SetIndex(unsigned int uiIndex);

    inline void SetSoftwareVP(bool bSoftwareVP);
    inline bool GetSoftwareVP() const;

    // Serialization
    bool SaveBinary(efd::BinaryStream& kStream);
    bool LoadBinary(efd::BinaryStream& kStream);

#if defined(NIDEBUG)
    void Dump(FILE* pf);
#endif  //#if defined(NIDEBUG)
    // *** end Emergent internal use only

protected:
    bool SaveBinaryRequirements(efd::BinaryStream& kStream);
    bool SaveBinaryPackingDef(efd::BinaryStream& kStream);
    bool SaveBinaryPasses(efd::BinaryStream& kStream);

    bool LoadBinaryRequirements(efd::BinaryStream& kStream);
    bool LoadBinaryPackingDef(efd::BinaryStream& kStream);
    bool LoadBinaryPasses(efd::BinaryStream& kStream);

    char* m_pcName;
    char* m_pcDesc;
    char* m_pcClassName;

    unsigned int m_uiIndex;

    NSBRequirements* m_pkRequirements;

    // User defined data set
    NSBUserDefinedDataSetPtr m_spUserDefinedDataSet;

    // Packing definition name
    char* m_pcPackingDef;

    // 'Global' render state settings for the shader
    NSBStateGroup* m_pkRenderStateGroup;

    // 'Global' shader constant maps
    NiTPrimitiveSet<NSBConstantMap*> m_akShaderConstantMaps[NSBConstantMap::NSB_SHADER_TYPE_COUNT];
    
    NiTPrimitiveArray<NSBPass*> m_kPasses;

    // Semantic adapter table
    NiSemanticAdapterTable m_kAdapterTable;

    bool m_bSoftwareVP;
};

#include "NSBImplementation.inl"

#endif  //NSBIMPLEMENTATION_H
