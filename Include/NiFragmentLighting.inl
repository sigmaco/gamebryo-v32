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

#include "NiFragmentLighting.h"

//--------------------------------------------------------------------------------------------------
#define NiDeclareBitfieldPlaceholderEntryFunctions(name, val, \
        type) \
    inline type Get##name() const \
    { \
        return type(val); \
    } \
    inline void Set##name(type)  \
    { \
    }
//--------------------------------------------------------------------------------------------------
#define NiDeclareBitfieldAliasEntryFunctions(name, alias, \
        type) \
    inline type Get##name() const \
    { \
        return Get##alias(); \
    } \
    inline void Set##name(type value)  \
    { \
        Set##alias(value); \
    }
//--------------------------------------------------------------------------------------------------
#define NiDeclareDefaultBitfieldPlaceholderEntryFunctions(name, val) \
    NiDeclareBitfieldPlaceholderEntryFunctions(name, val, \
        NiUInt32)
//--------------------------------------------------------------------------------------------------
#define NiDeclareDefaultBitfieldAliasEntryFunctions(name, alias) \
    NiDeclareBitfieldAliasEntryFunctions(name, alias, \
        NiUInt32)
//--------------------------------------------------------------------------------------------------
inline void NiFragmentLighting::SetForcePerPixelLighting(bool bForce)
{
    m_bForcePerPixelLighting = bForce;
}

//--------------------------------------------------------------------------------------------------
inline bool NiFragmentLighting::GetForcePerPixelLighting() const
{
    return m_bForcePerPixelLighting;
}

//--------------------------------------------------------------------------------------------------
inline void NiFragmentLighting::SetSaturateShading(bool bSaturate)
{
    m_bSaturateShading = bSaturate;
}

//--------------------------------------------------------------------------------------------------
inline bool NiFragmentLighting::GetSaturateShading() const
{
    return m_bSaturateShading;
}

//--------------------------------------------------------------------------------------------------
inline void NiFragmentLighting::SetSaturateTextures(bool bSaturate)
{
    m_bSaturateTextures = bSaturate;
}

//--------------------------------------------------------------------------------------------------
inline bool NiFragmentLighting::GetSaturateTextures() const
{
    return m_bSaturateTextures;
}

//--------------------------------------------------------------------------------------------------
template <class Type> void NiFragmentLighting::SetDescriptor(
    Type* pkDescriptor, const Descriptor& kDescriptor)
{
    pkDescriptor->SetSPECULAR(kDescriptor.bSpecularOn);
    pkDescriptor->SetVERTEXCOLORS(kDescriptor.bVertexColors);
    pkDescriptor->SetAMBDIFFEMISSIVE(kDescriptor.eAmbDiffEmissive);
    pkDescriptor->SetLIGHTINGMODE(kDescriptor.eLightingMode);
    pkDescriptor->SetAPPLYMODE(kDescriptor.eApplyMode);
    pkDescriptor->SetPERVERTEXFORLIGHTS(kDescriptor.bPerVertexForLights);
    pkDescriptor->SetPOINTLIGHTCOUNT(kDescriptor.uiNumPointLights);
    pkDescriptor->SetSPOTLIGHTCOUNT(kDescriptor.uiNumSpotLights);
    pkDescriptor->SetDIRLIGHTCOUNT(kDescriptor.uiNumDirectionalLights);
    pkDescriptor->SetSHADOWMAPFORLIGHT(kDescriptor.uiShadowMapBitfield);
    pkDescriptor->SetSHADOWTECHNIQUE(kDescriptor.usShadowTechnique);
    pkDescriptor->SetPSSMSLICETRANSITIONSENABLED(
        kDescriptor.bPSSMSliceTransitionEnabled);
    pkDescriptor->SetPSSMSLICECOUNT(kDescriptor.usPSSMSliceCount);
    pkDescriptor->SetPSSMWHICHLIGHT(kDescriptor.usPSSMWhichLight);
}

//--------------------------------------------------------------------------------------------------
template <class Type> void NiFragmentLighting::GetDescriptor(
    const Type* pkDescriptor, Descriptor& kDescriptor)
{
    kDescriptor.bSpecularOn =
        pkDescriptor->GetSPECULAR() != 0;
    kDescriptor.bVertexColors =
        pkDescriptor->GetVERTEXCOLORS() != 0;
    kDescriptor.eAmbDiffEmissive =
        (AmbDiffEmissiveEnum)pkDescriptor->GetAMBDIFFEMISSIVE();
    kDescriptor.eLightingMode =
        (LightingModeEnum)pkDescriptor->GetLIGHTINGMODE();
    kDescriptor.eApplyMode = (
        ApplyMode)pkDescriptor->GetAPPLYMODE();
    kDescriptor.bPerVertexForLights =
        pkDescriptor->GetPERVERTEXFORLIGHTS() != 0;
    kDescriptor.uiNumPointLights =
        pkDescriptor->GetPOINTLIGHTCOUNT();
    kDescriptor.uiNumSpotLights =
        pkDescriptor->GetSPOTLIGHTCOUNT();
    kDescriptor.uiNumDirectionalLights =
        pkDescriptor->GetDIRLIGHTCOUNT();
    kDescriptor.uiShadowMapBitfield =
        pkDescriptor->GetSHADOWMAPFORLIGHT();
    kDescriptor.usShadowTechnique =
        (NiUInt16)pkDescriptor->GetSHADOWTECHNIQUE();
    kDescriptor.bPSSMSliceTransitionEnabled =
        (pkDescriptor->GetPSSMSLICETRANSITIONSENABLED() != 0);
    kDescriptor.usPSSMSliceCount =
        (NiUInt16)pkDescriptor->GetPSSMSLICECOUNT();
    kDescriptor.usPSSMWhichLight =
        (NiUInt16)pkDescriptor->GetPSSMWHICHLIGHT();
}

//--------------------------------------------------------------------------------------------------
template <class Type> void NiFragmentLighting::SetDescriptor(
    Type* pkVertexDesc, const VertexDescriptor& kVertDesc)
{
    // The following lines are commented out as they are the
    // responsibility of the material, but are here for completeness sake

    //pkVertexDesc->SetOUTPUTWORLDPOS(kVertDesc.bOutputWorldPos);
    //pkVertexDesc->SetOUTPUTWORLDNBT(kVertDesc.bOutputWorldNormal);
    //pkVertexDesc->SetOUTPUTWORLDVIEW(kVertDesc.bOutputWorldView);

    pkVertexDesc->SetSPECULAR(kVertDesc.bSpecularOn);
    pkVertexDesc->SetPOINTLIGHTCOUNT(kVertDesc.uiNumPointLights);
    pkVertexDesc->SetSPOTLIGHTCOUNT(kVertDesc.uiNumSpotLights);
    pkVertexDesc->SetDIRLIGHTCOUNT(kVertDesc.uiNumDirectionalLights);
    pkVertexDesc->SetVERTEXCOLORS(kVertDesc.bVertexColors);
    pkVertexDesc->SetVERTEXLIGHTSONLY(kVertDesc.bVertexOnlyLights);
    pkVertexDesc->SetAMBDIFFEMISSIVE(kVertDesc.eAmbDiffEmissive);
    pkVertexDesc->SetLIGHTINGMODE(kVertDesc.eLightingMode);
    pkVertexDesc->SetAPPLYMODE(kVertDesc.eApplyMode);
}

//--------------------------------------------------------------------------------------------------
template <class Type> void NiFragmentLighting::SetDescriptor(
    Type* pkPixelDesc, const PixelDescriptor& kPixelDesc)
{
    // The following lines are commented out as they are the
    // responsibility of the material, but are here for completeness sake

    //pkPixelDesc->SetWORLDPOSITION(kPixelDesc.bInputWorldPos);
    //pkPixelDesc->SetWORLDNORMAL(kPixelDesc.bInputWorldNormal);
    //pkPixelDesc->SetWORLDVIEW(kPixelDesc.bInputWorldView);

    pkPixelDesc->SetSPECULAR(kPixelDesc.bSpecularOn);
    pkPixelDesc->SetPOINTLIGHTCOUNT(kPixelDesc.uiNumPointLights);
    pkPixelDesc->SetSPOTLIGHTCOUNT(kPixelDesc.uiNumSpotLights);
    pkPixelDesc->SetDIRLIGHTCOUNT(kPixelDesc.uiNumDirectionalLights);
    pkPixelDesc->SetSHADOWMAPFORLIGHT(kPixelDesc.uiShadowMapBitfield);
    pkPixelDesc->SetAMBDIFFEMISSIVE(kPixelDesc.eAmbDiffEmissive);
    pkPixelDesc->SetLIGHTINGMODE(kPixelDesc.eLightingMode);
    pkPixelDesc->SetAPPLYAMBIENT(kPixelDesc.bApplyAmbient);
    pkPixelDesc->SetAPPLYEMISSIVE(kPixelDesc.bApplyEmissive);
    pkPixelDesc->SetSHADOWTECHNIQUE(kPixelDesc.usShadowTechnique);
    pkPixelDesc->SetPSSMSLICETRANSITIONSENABLED(
        kPixelDesc.bPSSMSliceTransitionEnabled);
    pkPixelDesc->SetPSSMSLICECOUNT(kPixelDesc.usPSSMSliceCount);
    pkPixelDesc->SetPSSMWHICHLIGHT(kPixelDesc.usPSSMWhichLight);
    pkPixelDesc->SetAPPLYMODE(kPixelDesc.eApplyMode);
    pkPixelDesc->SetPERVERTEXLIGHTING(kPixelDesc.bPerVertexForLights);
}

//--------------------------------------------------------------------------------------------------
template <class Type> void NiFragmentLighting::GetDescriptor(
    const Type* pkVertexDesc, VertexDescriptor& kVertDesc)
{
    // The following lines are commented out as they are the
    // responsibility of the material, but are here for completeness sake

    //kVertDesc.bOutputWorldPos = pkVertexDesc->GetOUTPUTWORLDPOS();
    //kVertDesc.bOutputWorldNormal = pkVertexDesc->GetOUTPUTWORLDNBT();
    //kVertDesc.bOutputWorldView = pkVertexDesc->GetOUTPUTWORLDVIEW();

    kVertDesc.bSpecularOn =
        pkVertexDesc->GetSPECULAR() != 0;
    kVertDesc.uiNumPointLights =
        pkVertexDesc->GetPOINTLIGHTCOUNT();
    kVertDesc.uiNumSpotLights =
        pkVertexDesc->GetSPOTLIGHTCOUNT();
    kVertDesc.uiNumDirectionalLights =
        pkVertexDesc->GetDIRLIGHTCOUNT();
    kVertDesc.bVertexColors =
        pkVertexDesc->GetVERTEXCOLORS() != 0;
    kVertDesc.bVertexOnlyLights =
        pkVertexDesc->GetVERTEXLIGHTSONLY() != 0;
    kVertDesc.eAmbDiffEmissive =
        (AmbDiffEmissiveEnum)pkVertexDesc->GetAMBDIFFEMISSIVE();
    kVertDesc.eLightingMode =
        (LightingModeEnum)pkVertexDesc->GetLIGHTINGMODE();
    kVertDesc.eApplyMode =
        (ApplyMode)pkVertexDesc->GetAPPLYMODE();
}

//--------------------------------------------------------------------------------------------------
template <class Type> void NiFragmentLighting::GetDescriptor(
    const Type* pkPixelDesc, PixelDescriptor& kPixelDesc)
{
    // The following lines are commented out as they are the
    // responsibility of the material, but are here for completeness sake

    //kPixelDesc.bInputWorldPos = pkPixelDesc->GetWORLDPOSITION();
    //kPixelDesc.bInputWorldNormal = pkPixelDesc->GetWORLDNORMAL();
    //kPixelDesc.bInputWorldView = pkPixelDesc->GetWORLDVIEW();

    kPixelDesc.bSpecularOn = 
        pkPixelDesc->GetSPECULAR() != 0;
    kPixelDesc.uiNumPointLights =
        pkPixelDesc->GetPOINTLIGHTCOUNT();
    kPixelDesc.uiNumSpotLights =
        pkPixelDesc->GetSPOTLIGHTCOUNT();
    kPixelDesc.uiNumDirectionalLights =
        pkPixelDesc->GetDIRLIGHTCOUNT();
    kPixelDesc.uiShadowMapBitfield =
        pkPixelDesc->GetSHADOWMAPFORLIGHT();
    kPixelDesc.eAmbDiffEmissive =
        (AmbDiffEmissiveEnum)pkPixelDesc->GetAMBDIFFEMISSIVE();
    kPixelDesc.eLightingMode =
        (LightingModeEnum)pkPixelDesc->GetLIGHTINGMODE();
    kPixelDesc.bApplyAmbient =
        pkPixelDesc->GetAPPLYAMBIENT() != 0;
    kPixelDesc.bApplyEmissive =
        pkPixelDesc->GetAPPLYEMISSIVE() != 0;
    kPixelDesc.usShadowTechnique =
        (NiUInt16)pkPixelDesc->GetSHADOWTECHNIQUE();
    kPixelDesc.bPSSMSliceTransitionEnabled =
        (pkPixelDesc->GetPSSMSLICETRANSITIONSENABLED() != 0);
    kPixelDesc.usPSSMSliceCount =
        (NiUInt16)pkPixelDesc->GetPSSMSLICECOUNT();
    kPixelDesc.usPSSMWhichLight =
        (NiUInt16)pkPixelDesc->GetPSSMWHICHLIGHT();
    kPixelDesc.eApplyMode =
        (ApplyMode)pkPixelDesc->GetAPPLYMODE();
    kPixelDesc.bPerVertexForLights =
        pkPixelDesc->GetPERVERTEXLIGHTING() != 0;
}

//--------------------------------------------------------------------------------------------------
template <class M, class V, class P>
bool NiFragmentLighting::Fallbacks<M,V,P>::SplitPerPixelLights(
    ReturnCode eFailedRC, NiUInt32 uiFailedPass,
    RenderPassDescriptor* pkRenderPasses,
    NiUInt32 uiMaxCount, NiUInt32& uiCount)
{
    typedef M MaterialDescriptor;
    typedef V MaterialVertexDescriptor;
    typedef P MaterialPixelDescriptor;

    // This function can only deal with failed pixel shader compiles...
    if ((eFailedRC & EnumSource::RC_COMPILE_FAILURE_PIXEL) == 0)
        return false;

    // This function adds an additional pass - make sure there's room
    if (uiCount == uiMaxCount - 1)
        return false;

    NiUInt32 uiOriginalCount = uiCount;
    NiUInt32 uiNewPass = uiFailedPass + 1;

    // Extract the lighting data from the descriptor
    PixelDescriptor kInvalidPixelDesc;
    NiFragmentLighting::GetDescriptor(
        (MaterialPixelDescriptor*)pkRenderPasses[uiFailedPass].m_pkPixelDesc,
        kInvalidPixelDesc);

    bool bPerVertexLighting = kInvalidPixelDesc.bPerVertexForLights;

    // If all lighting is per-vertex, this function won't work
    if (bPerVertexLighting)
        return false;

    NiUInt32 uiDirLightCount = kInvalidPixelDesc.uiNumDirectionalLights;
    NiUInt32 uiSpotLightCount = kInvalidPixelDesc.uiNumSpotLights;
    NiUInt32 uiPointLightCount = kInvalidPixelDesc.uiNumPointLights;
    NiUInt16 usPSSMSliceCount = kInvalidPixelDesc.usPSSMSliceCount;
    NiUInt16 usPSSMWhichLight = kInvalidPixelDesc.usPSSMWhichLight;
    bool bPSSMSliceTransitions = kInvalidPixelDesc.bPSSMSliceTransitionEnabled;
    bool bApplyAmbient = kInvalidPixelDesc.bApplyAmbient;
    bool bApplyEmissive =  kInvalidPixelDesc.bApplyEmissive;

    // Can't do anything if there is only one light in this pass
    NiUInt32 uiTotalLightCount = uiDirLightCount + uiSpotLightCount +
        uiPointLightCount;
    if ((uiTotalLightCount == 0 ||
        uiTotalLightCount == 1 && !bApplyAmbient))
    {
        return false;
    }

    NiOutputDebugString("Trying to distribute per-pixel lights\n");

    // Make room for new pass immediately after failed pass, and
    // duplicate failed pass to new pass
    for (NiUInt32 i = uiOriginalCount; i > uiFailedPass; i--)
    {
        pkRenderPasses[i] = pkRenderPasses[i - 1];
    }

    // Remove any existing offsets from the new pass, since they will be
    // recalculated.
    pkRenderPasses[uiNewPass].m_kObjectOffsets.RemoveAll();
    // Disable lights reset on new pass
    pkRenderPasses[uiNewPass].m_bResetObjectOffsets = false;

    PixelDescriptor kNewPixelDesc;
    NiFragmentLighting::GetDescriptor(
        (MaterialPixelDescriptor*)pkRenderPasses[uiNewPass].m_pkPixelDesc,
        kNewPixelDesc);

    // Calculate the number of lights to go into each pass.
    // NOTE: the lights are split in reverse order (spot,dir,point) to
    // maintain the ordering of the lights when odd numbers of light types
    // are applied

    NiUInt32 uiNewLightCount = uiTotalLightCount - uiTotalLightCount / 2;
    NiUInt32 uiNumNewLightsLeft = uiNewLightCount;

    NiUInt32 uiNewSpotLightCount = uiSpotLightCount -
        uiSpotLightCount / 2;
    if (uiNewSpotLightCount > uiNumNewLightsLeft)
        uiNewSpotLightCount = uiNumNewLightsLeft;
    uiNumNewLightsLeft -= uiNewSpotLightCount;

    NiUInt32 uiNewDirLightCount = uiDirLightCount - uiDirLightCount / 2;
    if (uiNewDirLightCount > uiNumNewLightsLeft)
        uiNewDirLightCount = uiNumNewLightsLeft;
    uiNumNewLightsLeft -= uiNewDirLightCount;

    NiUInt32 uiNewPointLightCount = uiPointLightCount -
        uiPointLightCount / 2;
    if (uiNewPointLightCount > uiNumNewLightsLeft)
        uiNewPointLightCount = uiNumNewLightsLeft;
    uiNumNewLightsLeft -= uiNewPointLightCount;

    EE_ASSERT(uiNumNewLightsLeft == 0);

    NiUInt32 uiPreviousDirLightCount =
        uiDirLightCount - uiNewDirLightCount;
    NiUInt32 uiPreviousPointLightCount =
        uiPointLightCount - uiNewPointLightCount;
    NiUInt32 uiPreviousSpotLightCount =
        uiSpotLightCount - uiNewSpotLightCount;

    EE_ASSERT(uiNewDirLightCount + uiNewPointLightCount +
        uiNewSpotLightCount == uiNewLightCount);
    EE_ASSERT(uiNewLightCount + uiPreviousDirLightCount +
        uiPreviousPointLightCount + uiPreviousSpotLightCount ==
        uiTotalLightCount);

    // Defines how much we need to subtract off the PSSMWhichLight, due to
    // earlier lights being removed.
    NiUInt16 usPSSMOffset = (NiUInt16)
        (uiPreviousDirLightCount + uiPreviousPointLightCount);

    NiUInt16 usNewPSSMWhichLight;
    if (usPSSMOffset > usPSSMWhichLight)
    {
        // Disable PSSM if the PSSM light is no longer active in this pass
        usNewPSSMWhichLight = 0;
        kNewPixelDesc.usPSSMSliceCount =
            (NiUInt16)NiPSSMShadowClickGenerator::EncodeDescriptorSliceCount(1);
    }
    else
    {
        // Shift the PSSM light number to match the reduced number of lights.
        usNewPSSMWhichLight = usPSSMWhichLight - usPSSMOffset;
        kNewPixelDesc.usPSSMSliceCount = usPSSMSliceCount;
    }
    kNewPixelDesc.bPSSMSliceTransitionEnabled = bPSSMSliceTransitions;

    kNewPixelDesc.uiNumDirectionalLights = uiNewDirLightCount;
    kNewPixelDesc.uiNumPointLights = uiNewPointLightCount;
    kNewPixelDesc.uiNumSpotLights = uiNewSpotLightCount;
    kNewPixelDesc.bApplyAmbient = false;
    kNewPixelDesc.bApplyEmissive = false;

    // The following section updates the shadow map bitfields for each pass
    // that is being generated. Whilst doing this, a count of each type of light
    // is maintained so that the appropriate object offsets may be applied to
    // the pass descriptor.
    kNewPixelDesc.uiShadowMapBitfield = 0;

    NiUInt32 uiOriginalShadowBitfield = kInvalidPixelDesc.uiShadowMapBitfield;
    NiUInt32 uiPreviousShadowBitfield = 0;
    NiUInt32 uiNewShadowBitfield = 0;
    NiUInt32 uiOriginalLight = 0;
    NiUInt32 uiPreviousLight = 0;
    NiUInt32 uiNewLight = 0;

    NiUInt32 uiPreviousShadowPointLightCount = 0;
    NiUInt32 uiPreviousShadowDirLightCount = 0;
    NiUInt32 uiPreviousShadowSpotLightCount = 0;
    NiUInt32 uiPreviousNonShadowPointLightCount = 0;
    NiUInt32 uiPreviousNonShadowDirLightCount = 0;
    NiUInt32 uiPreviousNonShadowSpotLightCount = 0;

    for (NiUInt32 ui = 0; ui < uiPointLightCount; ui++)
    {
        NiUInt32 uiMask = NiTGetBitMask<NiUInt32>(uiOriginalLight, 1);
        bool bShadow =
            NiTGetBit<NiUInt32>(uiOriginalShadowBitfield, uiMask);

        if (ui < uiPreviousPointLightCount)
        {
            // Count the number of shadowed and number of non shadowed
            // lights in the previous pass (for object offset purposes)
            if (bShadow)
            {
                uiMask = NiTGetBitMask<NiUInt32>(uiPreviousLight, 1);
                uiPreviousShadowBitfield |= uiMask;

                uiPreviousShadowPointLightCount++;
            }
            else
            {
                uiPreviousNonShadowPointLightCount++;
            }
            uiPreviousLight++;
        }
        else
        {
            if (bShadow)
            {
                // Transfer these bits into the new descriptor
                NiTSetBit<NiUInt32>(uiOriginalShadowBitfield, 0, uiMask);
                uiMask = NiTGetBitMask<NiUInt32>(uiNewLight, 1);
                uiNewShadowBitfield |= uiMask;
            }
            uiNewLight++;
        }
        uiOriginalLight++;
    }

    for (NiUInt32 ui = 0; ui < uiDirLightCount; ui++)
    {
        NiUInt32 uiMask = NiTGetBitMask<NiUInt32>(uiOriginalLight, 1);
        bool bShadow =
            NiTGetBit<NiUInt32>(uiOriginalShadowBitfield, uiMask);

        if (ui < uiPreviousDirLightCount)
        {
            // Count the number of shadowed and number of non shadowed
            // lights in the previous pass (for object offset purposes)
            if (bShadow)
            {
                uiMask = NiTGetBitMask<NiUInt32>(uiPreviousLight, 1);
                uiPreviousShadowBitfield |= uiMask;

                uiPreviousShadowDirLightCount++;
            }
            else
            {
                uiPreviousNonShadowDirLightCount++;
            }
            uiPreviousLight++;
        }
        else
        {
            if (bShadow)
            {
                NiTSetBit<NiUInt32>(uiOriginalShadowBitfield, 0, uiMask);
                uiMask = NiTGetBitMask<NiUInt32>(uiNewLight, 1);
                uiNewShadowBitfield |= uiMask;
            }
            uiNewLight++;
        }
        uiOriginalLight++;
    }

    for (NiUInt32 ui = 0; ui < uiSpotLightCount; ui++)
    {
        NiUInt32 uiMask = NiTGetBitMask<NiUInt32>(uiOriginalLight, 1);
        bool bShadow =
            NiTGetBit<NiUInt32>(uiOriginalShadowBitfield, uiMask);

        if (ui < uiPreviousSpotLightCount)
        {
            // Count the number of shadowed and number of non shadowed
            // lights in the previous pass (for object offset purposes)
            if (bShadow)
            {
                uiMask = NiTGetBitMask<NiUInt32>(uiPreviousLight, 1);
                uiPreviousShadowBitfield |= uiMask;

                uiPreviousShadowSpotLightCount++;
            }
            else
            {
                uiPreviousNonShadowSpotLightCount++;
            }
            uiPreviousLight++;
        }
        else
        {
            if (bShadow)
            {
                NiTSetBit<NiUInt32>(uiOriginalShadowBitfield, 0, uiMask);
                uiMask = NiTGetBitMask<NiUInt32>(uiNewLight, 1);
                uiNewShadowBitfield |= uiMask;
            }
            uiNewLight++;
        }
        uiOriginalLight++;
    }

    EE_ASSERT(uiNewLightCount == uiNewLight);
    EE_ASSERT(uiOriginalLight == uiTotalLightCount);

    EE_ASSERT(uiPreviousShadowPointLightCount +
        uiPreviousNonShadowPointLightCount == uiPreviousPointLightCount);
    EE_ASSERT(uiPreviousShadowDirLightCount +
        uiPreviousNonShadowDirLightCount == uiPreviousDirLightCount);
    EE_ASSERT(uiPreviousShadowSpotLightCount +
        uiPreviousNonShadowSpotLightCount == uiPreviousSpotLightCount);

    kNewPixelDesc.uiShadowMapBitfield = uiNewShadowBitfield;
    kInvalidPixelDesc.uiShadowMapBitfield = uiPreviousShadowBitfield;

    // Apply the appropriate blending for this fallback (Additive)
    pkRenderPasses[uiNewPass].m_bAlphaOverride = true;
    pkRenderPasses[uiNewPass].m_bAlphaBlend = true;
    pkRenderPasses[uiNewPass].m_bUsePreviousSrcBlendMode = true;
    pkRenderPasses[uiNewPass].m_bUsePreviousDestBlendMode = false;
    pkRenderPasses[uiNewPass].m_eSrcBlendMode =
        NiAlphaProperty::ALPHA_ONE;
    pkRenderPasses[uiNewPass].m_eDestBlendMode =
        NiAlphaProperty::ALPHA_ONE;

    // The next section sets the required object offsets in the render pass
    // descriptor.

    if (uiNewDirLightCount != 0)
    {
        ObjectResourceOffset kOffset;

        // Generate the offset for general directional lights
        kOffset.m_eObjectType =
            NiShaderAttributeDesc::OT_EFFECT_DIRECTIONALLIGHT;
        kOffset.m_eProgramType = NiGPUProgram::PROGRAM_PIXEL;
        kOffset.m_uiOffset = NiFragment::GetHighestObjectOffset(
            kOffset.m_eObjectType,
            pkRenderPasses, uiNewPass) +
            uiPreviousNonShadowDirLightCount;
        pkRenderPasses[uiNewPass].m_kObjectOffsets.Add(kOffset);

        // Generate the offset for shadow directional lights
        kOffset.m_eObjectType =
            NiShaderAttributeDesc::OT_EFFECT_SHADOWDIRECTIONALLIGHT;
        kOffset.m_eProgramType = NiGPUProgram::PROGRAM_PIXEL;
        kOffset.m_uiOffset = NiFragment::GetHighestObjectOffset(
            kOffset.m_eObjectType,
            pkRenderPasses, uiNewPass) +
            uiPreviousShadowDirLightCount;
        pkRenderPasses[uiNewPass].m_kObjectOffsets.Add(kOffset);
    }

    if (uiNewSpotLightCount != 0)
    {
        ObjectResourceOffset kOffset;

        // Generate the offset for general spot lights
        kOffset.m_eObjectType =
            NiShaderAttributeDesc::OT_EFFECT_SPOTLIGHT;
        kOffset.m_eProgramType = NiGPUProgram::PROGRAM_PIXEL;
        kOffset.m_uiOffset = NiFragment::GetHighestObjectOffset(
            kOffset.m_eObjectType,
            pkRenderPasses, uiNewPass) +
            uiPreviousNonShadowSpotLightCount;
        pkRenderPasses[uiNewPass].m_kObjectOffsets.Add(kOffset);

        // Generate the offset for shadow casting spot lights
        kOffset.m_eObjectType =
            NiShaderAttributeDesc::OT_EFFECT_SHADOWSPOTLIGHT;
        kOffset.m_eProgramType = NiGPUProgram::PROGRAM_PIXEL;
        kOffset.m_uiOffset = NiFragment::GetHighestObjectOffset(
            kOffset.m_eObjectType,
            pkRenderPasses, uiNewPass) +
            uiPreviousShadowSpotLightCount;
        pkRenderPasses[uiNewPass].m_kObjectOffsets.Add(kOffset);
    }

    if (uiNewPointLightCount != 0)
    {
        ObjectResourceOffset kOffset;

        // Generate the offset for general point lights
        kOffset.m_eObjectType =
            NiShaderAttributeDesc::OT_EFFECT_POINTLIGHT;
        kOffset.m_eProgramType = NiGPUProgram::PROGRAM_PIXEL;
        kOffset.m_uiOffset = NiFragment::GetHighestObjectOffset(
            kOffset.m_eObjectType,
            pkRenderPasses, uiNewPass) +
            uiPreviousNonShadowPointLightCount;
        pkRenderPasses[uiNewPass].m_kObjectOffsets.Add(kOffset);

        // Generate the offset for shadow casting point lights
        kOffset.m_eObjectType =
            NiShaderAttributeDesc::OT_EFFECT_SHADOWPOINTLIGHT;
        kOffset.m_eProgramType = NiGPUProgram::PROGRAM_PIXEL;
        kOffset.m_uiOffset = NiFragment::GetHighestObjectOffset(
            kOffset.m_eObjectType,
            pkRenderPasses, uiNewPass) +
            uiPreviousShadowPointLightCount;
        pkRenderPasses[uiNewPass].m_kObjectOffsets.Add(kOffset);
    }

    kInvalidPixelDesc.uiNumDirectionalLights = uiPreviousDirLightCount;
    kInvalidPixelDesc.uiNumPointLights = uiPreviousPointLightCount;
    kInvalidPixelDesc.uiNumSpotLights = uiPreviousSpotLightCount;
    kInvalidPixelDesc.bApplyAmbient = bApplyAmbient;
    kInvalidPixelDesc.bApplyEmissive = bApplyEmissive;

    NiFragmentLighting::SetDescriptor(
        (MaterialPixelDescriptor*)pkRenderPasses[uiFailedPass].m_pkPixelDesc,
        kInvalidPixelDesc);

    NiFragmentLighting::SetDescriptor(
        (MaterialPixelDescriptor*)pkRenderPasses[uiNewPass].m_pkPixelDesc,
        kNewPixelDesc);

    uiCount++;

    return true;
}

//--------------------------------------------------------------------------------------------------
template <class M, class V, class P>
bool NiFragmentLighting::Fallbacks<M,V,P>::DropPSSMShadowMaps(
    ReturnCode eFailedRC, NiUInt32 uiFailedPass,
    RenderPassDescriptor* pkRenderPasses)
{
    typedef M MaterialDescriptor;
    typedef V MaterialVertexDescriptor;
    typedef P MaterialPixelDescriptor;

    // This function can only deal with failed pixel shader compiles...
    if ((eFailedRC & EnumSource::RC_COMPILE_FAILURE_PIXEL) == 0)
        return false;

    // Extract the failed descriptor
    PixelDescriptor kInvalidPixelDesc;
    NiFragmentLighting::GetDescriptor(
        (MaterialPixelDescriptor*)pkRenderPasses[uiFailedPass].m_pkPixelDesc,
        kInvalidPixelDesc);

    // This function only works for shaders with shadow maps
    if (!kInvalidPixelDesc.uiShadowMapBitfield)
        return false;

    // This function only works if there is a PSSM enabled shadowmap
    if (!kInvalidPixelDesc.usPSSMSliceCount)
        return false;

    NiOutputDebugString("Trying to remove PSSM enabled shadow maps.\n");

    NiUInt32 uiPSSMShadowMapBit = 1 << kInvalidPixelDesc.usPSSMWhichLight;

    // Make sure a shadowmap actually exists
    if ((kInvalidPixelDesc.uiShadowMapBitfield & uiPSSMShadowMapBit) == 0)
        return false;

    kInvalidPixelDesc.uiShadowMapBitfield -= uiPSSMShadowMapBit;
    kInvalidPixelDesc.usPSSMSliceCount = 0;

    // Store the new lighting descriptor info
    NiFragmentLighting::SetDescriptor(
        (MaterialPixelDescriptor*)pkRenderPasses[uiFailedPass].m_pkPixelDesc,
        kInvalidPixelDesc);

    return true;
}

//--------------------------------------------------------------------------------------------------
template <class M, class V, class P>
bool NiFragmentLighting::Fallbacks<M,V,P>::DropShadowMaps(ReturnCode eFailedRC,
    NiUInt32 uiFailedPass, RenderPassDescriptor* pkRenderPasses)
{
    typedef M MaterialDescriptor;
    typedef V MaterialVertexDescriptor;
    typedef P MaterialPixelDescriptor;

    // This function can only deal with failed pixel shader compiles...
    if ((eFailedRC & EnumSource::RC_COMPILE_FAILURE_PIXEL) == 0)
        return false;

    // Extract the failed descriptor
    PixelDescriptor kInvalidPixelDesc;
    NiFragmentLighting::GetDescriptor(
        (MaterialPixelDescriptor*)pkRenderPasses[uiFailedPass].m_pkPixelDesc,
        kInvalidPixelDesc);

    // This function only works for shaders with shadow maps
    if (!kInvalidPixelDesc.uiShadowMapBitfield)
        return false;

    NiOutputDebugString("Trying to remove all shadow maps.\n");

    kInvalidPixelDesc.uiShadowMapBitfield = 0;

    // Store the new lighting descriptor info
    NiFragmentLighting::SetDescriptor(
        (MaterialPixelDescriptor*)pkRenderPasses[uiFailedPass].m_pkPixelDesc,
        kInvalidPixelDesc);

    return true;
}

//--------------------------------------------------------------------------------------------------
template <class M, class V, class P>
bool NiFragmentLighting::Fallbacks<M,V,P>::SplitPerVertexLights(
    ReturnCode eFailedRC, NiUInt32 uiFailedPass,
    RenderPassDescriptor* pkRenderPasses,
    NiUInt32 uiMaxCount, NiUInt32& uiCount)
{
    typedef M MaterialDescriptor;
    typedef V MaterialVertexDescriptor;
    typedef P MaterialPixelDescriptor;

    // This function can only deal with failed pixel shader compiles...
    if ((eFailedRC & EnumSource::RC_COMPILE_FAILURE_VERTEX) == 0)
        return false;

    // This function adds an additional pass - make sure there's room
    if (uiCount == uiMaxCount - 1)
        return false;

    NiUInt32 uiOriginalCount = uiCount;
    NiUInt32 uiNewPass = uiFailedPass + 1;

    // Extract the relevant lighting descriptors from the material's descriptors
    VertexDescriptor kInvalidVertexDesc;
    NiFragmentLighting::GetDescriptor(
        (MaterialVertexDescriptor*)pkRenderPasses[uiFailedPass].m_pkVertexDesc,
        kInvalidVertexDesc);
    PixelDescriptor kInvalidPixelDesc;
    NiFragmentLighting::GetDescriptor(
        (MaterialPixelDescriptor*)pkRenderPasses[uiFailedPass].m_pkPixelDesc,
        kInvalidPixelDesc);

    bool bPerVertexLighting = kInvalidPixelDesc.bPerVertexForLights;

    NiUInt32 uiDirLightCount = kInvalidVertexDesc.uiNumDirectionalLights;
    NiUInt32 uiSpotLightCount = kInvalidVertexDesc.uiNumSpotLights;
    NiUInt32 uiPointLightCount = kInvalidVertexDesc.uiNumPointLights;
    NiUInt32 uiTotalLightCount = uiDirLightCount + uiSpotLightCount +
        uiPointLightCount;

    // If there are no per-vertex lights, this function won't work
    if (bPerVertexLighting == 0 || uiTotalLightCount == 0)
        return false;

    NiOutputDebugString("Trying to distribute per-vertex lights\n");

    // Make room for new pass immediately after failed pass, and
    // duplicate failed pass to new pass
    for (NiUInt32 i = uiOriginalCount; i > uiFailedPass; i--)
    {
        pkRenderPasses[i] = pkRenderPasses[i - 1];
    }

    // Remove any existing offsets from the new pass, since they will be
    // recalculated.
    pkRenderPasses[uiNewPass].m_kObjectOffsets.RemoveAll();
    // Disable lights reset on new pass
    pkRenderPasses[uiNewPass].m_bResetObjectOffsets = false;

    VertexDescriptor kNewVertexDesc;
    NiFragmentLighting::GetDescriptor(
        (MaterialVertexDescriptor*)pkRenderPasses[uiNewPass].m_pkVertexDesc,
        kNewVertexDesc);

    // Calculate the number of lights to go into each pass.
    // NOTE: the lights are split in reverse order (spot,dir,point) to
    // maintain the ordering of the lights when odd numbers of light types
    // are applied

    NiUInt32 uiNewLightCount = uiTotalLightCount - uiTotalLightCount / 2;
    NiUInt32 uiNumNewLightsLeft = uiNewLightCount;

    NiUInt32 uiNewSpotLightCount =
        uiSpotLightCount - uiSpotLightCount / 2;
    if (uiNewSpotLightCount > uiNumNewLightsLeft)
        uiNewSpotLightCount = uiNumNewLightsLeft;
    uiNumNewLightsLeft -= uiNewSpotLightCount;

    NiUInt32 uiNewPointLightCount = uiPointLightCount -
        uiPointLightCount / 2;
    if (uiNewPointLightCount > uiNumNewLightsLeft)
        uiNewPointLightCount = uiNumNewLightsLeft;
    uiNumNewLightsLeft -= uiNewPointLightCount;

    NiUInt32 uiNewDirLightCount = uiDirLightCount - uiDirLightCount / 2;
    if (uiNewDirLightCount > uiNumNewLightsLeft)
        uiNewDirLightCount = uiNumNewLightsLeft;
    uiNumNewLightsLeft -= uiNewDirLightCount;

    EE_ASSERT(uiNumNewLightsLeft == 0);

    NiUInt32 uiPreviousDirLightCount =
        uiDirLightCount - uiNewDirLightCount;
    NiUInt32 uiPreviousPointLightCount =
        uiPointLightCount - uiNewPointLightCount;
    NiUInt32 uiPreviousSpotLightCount =
        uiSpotLightCount - uiNewSpotLightCount;

    EE_ASSERT(uiNewDirLightCount + uiNewPointLightCount +
        uiNewSpotLightCount == uiNewLightCount);
    EE_ASSERT(uiNewLightCount + uiPreviousDirLightCount +
        uiPreviousPointLightCount + uiPreviousSpotLightCount ==
        uiTotalLightCount);

    kNewVertexDesc.uiNumDirectionalLights = uiNewDirLightCount;
    kNewVertexDesc.uiNumPointLights = uiNewPointLightCount;
    kNewVertexDesc.uiNumSpotLights = uiNewSpotLightCount;

    // Apply the appropriate blending for this fallback (Additive)
    pkRenderPasses[uiNewPass].m_bAlphaOverride = true;
    pkRenderPasses[uiNewPass].m_bAlphaBlend = true;
    pkRenderPasses[uiNewPass].m_bUsePreviousSrcBlendMode = true;
    pkRenderPasses[uiNewPass].m_bUsePreviousDestBlendMode = false;
    pkRenderPasses[uiNewPass].m_eSrcBlendMode =
        NiAlphaProperty::ALPHA_ONE;
    pkRenderPasses[uiNewPass].m_eDestBlendMode =
        NiAlphaProperty::ALPHA_ONE;

    // The next section applies the appropriate object offsets for this
    // pass
    if (uiNewDirLightCount != 0)
    {
        ObjectResourceOffset kOffset;
        kOffset.m_eObjectType =
            NiShaderAttributeDesc::OT_EFFECT_DIRECTIONALLIGHT;
        kOffset.m_eProgramType = NiGPUProgram::PROGRAM_VERTEX;
        kOffset.m_uiOffset = NiFragment::GetHighestObjectOffset(
            kOffset.m_eObjectType,
            pkRenderPasses, uiNewPass) + uiPreviousDirLightCount;
        pkRenderPasses[uiNewPass].m_kObjectOffsets.Add(kOffset);
    }

    if (uiNewSpotLightCount != 0)
    {
        ObjectResourceOffset kOffset;
        kOffset.m_eObjectType = NiShaderAttributeDesc::OT_EFFECT_SPOTLIGHT;
        kOffset.m_eProgramType = NiGPUProgram::PROGRAM_VERTEX;
        kOffset.m_uiOffset = NiFragment::GetHighestObjectOffset(
            kOffset.m_eObjectType,
            pkRenderPasses, uiNewPass) + uiPreviousSpotLightCount;
        pkRenderPasses[uiNewPass].m_kObjectOffsets.Add(kOffset);
    }

    if (uiNewPointLightCount != 0)
    {
        ObjectResourceOffset kOffset;
        kOffset.m_eObjectType = NiShaderAttributeDesc::OT_EFFECT_POINTLIGHT;
        kOffset.m_eProgramType = NiGPUProgram::PROGRAM_VERTEX;
        kOffset.m_uiOffset = NiFragment::GetHighestObjectOffset(
            kOffset.m_eObjectType,
            pkRenderPasses, uiNewPass) + uiPreviousPointLightCount;
        pkRenderPasses[uiNewPass].m_kObjectOffsets.Add(kOffset);
    }

    kInvalidVertexDesc.uiNumDirectionalLights = uiPreviousDirLightCount;
    kInvalidVertexDesc.uiNumPointLights = uiPreviousPointLightCount;
    kInvalidVertexDesc.uiNumSpotLights = uiPreviousSpotLightCount;

    NiFragmentLighting::SetDescriptor(
        (MaterialVertexDescriptor*)pkRenderPasses[uiFailedPass].m_pkVertexDesc,
        kInvalidVertexDesc);

    NiFragmentLighting::SetDescriptor(
        (MaterialVertexDescriptor*)pkRenderPasses[uiNewPass].m_pkVertexDesc,
        kNewVertexDesc);

    uiCount++;

    return true;
}
