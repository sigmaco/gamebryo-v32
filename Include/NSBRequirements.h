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
#ifndef NSBREQUIREMENTS_H
#define NSBREQUIREMENTS_H

#include "NSBShaderLibLibType.h"
#include <NiMain.h>

class NSBSHADERLIB_ENTRY NSBRequirements : public NiMemObject
{
public:
    NSBRequirements();
    ~NSBRequirements();

    enum NSBFeatureLevel
    {
        NSB_FEATURE_LEVEL_INVALID,
        NSB_FEATURE_LEVEL_9_1,
        NSB_FEATURE_LEVEL_9_2,
        NSB_FEATURE_LEVEL_9_3,
        NSB_FEATURE_LEVEL_10_0,
        NSB_FEATURE_LEVEL_10_1,
        NSB_FEATURE_LEVEL_11_0
    };

    NSBFeatureLevel GetFeatureLevel() const;
    void SetFeatureLevel(NSBFeatureLevel eFeatureLevel);
    unsigned int GetVSVersion() const;
    void SetVSVersion(unsigned int uiVersion);
    unsigned int GetGSVersion() const;
    void SetGSVersion(unsigned int uiVersion);
    unsigned int GetPSVersion() const;
    void SetPSVersion(unsigned int uiVersion);
    unsigned int GetCSVersion() const;
    void SetCSVersion(unsigned int uiVersion);
    unsigned int GetUserVersion() const;
    void SetUserVersion(unsigned int uiVersion);
    unsigned int GetPlatformFlags() const;
    void SetPlatformFlags(unsigned int uiFlags);

    bool UsesNiRenderState() const;
    void SetUsesNiRenderState(bool bUses);

    bool UsesNiLightState() const;
    void SetUsesNiLightState(bool bUses);

    NiShaderRequirementDesc::NBTFlags GetBinormalTangentMethod() const;
    void SetBinormalTangentMethod(
        NiShaderRequirementDesc::NBTFlags eNBTMethod);

    unsigned int GetBinormalTangentUVSource() const;
    void SetBinormalTangentUVSource(unsigned int uiSource);

    bool GetSoftwareVPAcceptable() const;
    void SetSoftwareVPAcceptable(bool bSoftwareVP);

    bool GetSoftwareVPRequired() const;
    void SetSoftwareVPRequired(bool bSoftwareVP);

    // For skinning shaders
    unsigned int GetBonesPerPartition() const;
    void SetBonesPerPartition(unsigned int uiBones);
    unsigned int GetBoneMatrixRegisters() const;
    void SetBoneMatrixRegisters(unsigned int uiRegisters);

    // For skinning shaders
    // This enumeration must match the one from NiBinaryShader
    enum BoneMatrixCalcMethod
    {
        BONECALC_SKIN       = 0x00000000,
        BONECALC_NO_SKIN    = 0x00000001
    };

    BoneMatrixCalcMethod GetBoneCalcMethod() const;
    void SetBoneCalcMethod(BoneMatrixCalcMethod eMethod);

    // *** begin Emergent internal use only
    bool SaveBinary(efd::BinaryStream& kStream);
    bool LoadBinary(efd::BinaryStream& kStream);

#if defined(NIDEBUG)
    void Dump(FILE* pf);
#endif  //#if defined(NIDEBUG)
    // *** end Emergent internal use only

protected:
    NSBFeatureLevel m_eFeatureLevel;
    unsigned int m_uiVSVersion;
    unsigned int m_uiGSVersion;
    unsigned int m_uiPSVersion;
    unsigned int m_uiCSVersion;
    unsigned int m_uiUserVersion;
    unsigned int m_uiPlatformFlags;
    bool m_bUsesNiRenderState;
    bool m_bUsesNiLightState;
    unsigned int m_uiBonesPerPartition;
    unsigned int m_uiBoneMatrixRegisters;
    BoneMatrixCalcMethod m_eBoneCalcMethod;
    NiShaderRequirementDesc::NBTFlags m_eBinormalTangentMethod;
    unsigned int m_uiBinormalTangentUVSource;

    bool m_bSoftwareVPAcceptable;
    bool m_bSoftwareVPRequired;
};

#endif  //NSBREQUIREMENTS_H
