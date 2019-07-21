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
#ifndef NSBPACKINGDEF_H
#define NSBPACKINGDEF_H

#include "NSBShaderLibLibType.h"

#include <NiShaderDeclaration.h>
#include <NiShader.h>

#if defined(_PS3)
class NiPS3CgShaderProgram;
#endif

class NSBSHADERLIB_ENTRY NSBPackingDef : public NiMemObject
{
public:
    NSBPackingDef();
    ~NSBPackingDef();

    enum NSBPackingDefEnum
    {
        NSB_PD_FLOAT1     = 0,
        NSB_PD_FLOAT2,
        NSB_PD_FLOAT3,
        NSB_PD_FLOAT4,
        NSB_PD_UBYTECOLOR,
        NSB_PD_UBYTE4,
        NSB_PD_SHORT1,
        NSB_PD_SHORT2,
        NSB_PD_SHORT3,
        NSB_PD_SHORT4,
        NSB_PD_NORMSHORT1,
        NSB_PD_NORMSHORT2,
        NSB_PD_NORMSHORT3,
        NSB_PD_NORMSHORT4,
        NSB_PD_NORMPACKED3,
        NSB_PD_PBYTE1,
        NSB_PD_PBYTE2,
        NSB_PD_PBYTE3,
        NSB_PD_PBYTE4,
        NSB_PD_FLOAT2H,
        //
        NSB_PD_NORMUBYTE4,  // 4D normalized unsigned byte (val,val,val,val)
        NSB_PD_NORMUSHORT2, // 2D normalized unsigned short (val,val,0,1)
        NSB_PD_NORMUSHORT4, // 4D normalized unigned short (val,val,val,val)
        NSB_PD_UDEC3,       // 3D unsigned 10 10 10 (val,val,val,1)
        NSB_PD_NORMDEC3,    // 3D normalized signed 10 10 10 (val,val,val,1)
        NSB_PD_FLOAT16_2,   // 2D signed 16-bit float (val,val,0,1)
        NSB_PD_FLOAT16_4,   // 4D signed 16-bit float (val,val,val,val)
        //
        NSB_PD_COUNT,
        NSB_PD_INVALID    = 0x7fffffff
    };

    // Name
    const char* GetName();
    void SetName(const char* pcName);

    bool GetFixedFunction();
    void SetFixedFunction(bool bFixedFunction);

    bool AddPackingEntry(unsigned int uiStream, unsigned int uiRegister,
        unsigned int uiInput, NSBPackingDefEnum eType,
        NiShaderDeclaration::ShaderParameterTesselator eTesselator,
        NiShaderDeclaration::ShaderParameterUsage eUsage,
        unsigned int uiUsageIndex);

    static const char* GetTypeName(NSBPackingDefEnum eType);
    static const char* GetParameterName(
        NiShaderDeclaration::ShaderParameter eParam);

    // *** begin Emergent internal use only
#if defined(_PS3)
    void GenerateDeclarationFromVertexShader(
        NiPS3CgShaderProgram* pkVertexProgram);
#endif

    inline bool GetGenerated() const;
    inline void SetGenerated(bool bGenerated);

    class NSBPDEntry : public NiMemObject
    {
    public:
        NSBPDEntry();
        ~NSBPDEntry();

        unsigned int GetStream();
        unsigned int GetRegister();
        unsigned int GetInput();
        NSBPackingDefEnum GetType();
        NiShaderDeclaration::ShaderParameterTesselator GetTesselator();
        NiShaderDeclaration::ShaderParameterUsage GetUsage();
        unsigned int GetUsageIndex();

        void SetStream(unsigned int uiStream);
        void SetRegister(unsigned int uiRegister);
        void SetInput(unsigned int uiInput);
        void SetType(NSBPackingDefEnum eType);
        void SetTesselator(
            NiShaderDeclaration::ShaderParameterTesselator eTesselator);
        void SetUsage(
            NiShaderDeclaration::ShaderParameterUsage eUsage);
        void SetUsageIndex(unsigned int uiUsageIndex);

        bool SaveBinary(efd::BinaryStream& kStream);
        bool LoadBinary(efd::BinaryStream& kStream);

    protected:
        unsigned int m_uiStream;
        unsigned int m_uiRegister;
        unsigned int m_uiInput;
        NSBPackingDefEnum m_eType;
        NiShaderDeclaration::ShaderParameterTesselator m_eTesselator;
        NiShaderDeclaration::ShaderParameterUsage m_eUsage;
        unsigned int m_uiUsageIndex;
    };

    NSBPDEntry* GetFirstEntry(NiTListIterator& kIter);
    NSBPDEntry* GetNextEntry(NiTListIterator& kIter);

    void GetStreamInfo(unsigned int& uiStreamCount,
        unsigned int& uiMaxStreamEntryCount);

    bool SaveBinary(efd::BinaryStream& kStream);
    bool LoadBinary(efd::BinaryStream& kStream);
    // *** end Emergent internal use only

protected:
    char* m_pcName;
    bool m_bFixedFunction;
    NiTPointerList<NSBPDEntry*> m_kEntryList;
    bool m_bGenerated; // Was generated from VS
};

#include "NSBPackingDef.inl"

#endif  //NSBPACKINGDEF_H
