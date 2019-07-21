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
#ifndef NSBTEXTURESTAGE_H
#define NSBTEXTURESTAGE_H

#include "NSBShaderLibLibType.h"
#include "NSBUtility.h"

#include <NiTextureStage.h>
#include <NiShaderAttributeDesc.h>

class NSBSHADERLIB_ENTRY NSBTextureStage : public NiMemObject
{
public:
    NSBTextureStage();
    ~NSBTextureStage();

    // Name
    inline const char* GetName();
    void SetName(const char* pcName);

    inline unsigned int GetStage();
    inline void SetStage(unsigned int uiStage);

    //
    NSBStateGroup* GetTextureStageGroup();
    NSBStateGroup* GetSamplerStageGroup();

    inline unsigned int GetTextureFlags();
    inline unsigned short GetObjTextureFlags();

    inline void SetNDLMap(unsigned int uiNDLMap);
    inline void SetDecalMap(unsigned int uiDecal);
    inline void SetShaderMap(unsigned int uiShaderMap);
    inline void SetUseIndexFromMap(bool bUse);
    inline void SetObjTextureSettings(
        NiShaderAttributeDesc::ObjectType eObjectType,
        unsigned int uiObjectIndex);

    inline bool GetUseTextureTransformation();
    inline float* GetTextureTransformation();

    inline void SetUseTextureTransformation(bool bUse);
    inline void SetTextureTransformation(float afTextureTransform[16]);

    inline unsigned int GetTextureTransformFlags();
    inline void SetTextureTransformFlags(unsigned int uiFlags);

    inline const char* GetGlobalName();
    inline void SetGlobalName(const char* pcGlobalName);

    // *** begin Emergent internal use only
    bool SaveBinary(efd::BinaryStream& kStream);
    bool LoadBinary(efd::BinaryStream& kStream);

#if defined(NIDEBUG)
    void Dump(FILE* pf);
#endif  //#if defined(NIDEBUG)
    // *** end Emergent internal use only

protected:
    bool SaveBinaryTextureTransform(efd::BinaryStream& kStream);
    bool LoadBinaryTextureTransform(efd::BinaryStream& kStream);

    char* m_pcName;

    unsigned int m_uiStage;
    unsigned int m_uiTextureFlags;
    NSBStateGroup* m_pkTextureStageGroup;
    NSBStateGroup* m_pkSamplerStageGroup;
    unsigned short m_usObjTextureFlags;
    bool m_bTextureTransform;
    float m_afTextureTransform[16];
    unsigned int m_uiTextureTransformFlags;
    char* m_pcGlobalEntry;
};

#include "NSBTextureStage.inl"

#endif  //NSBTEXTURESTAGE_H
