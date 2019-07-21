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

//--------------------------------------------------------------------------------------------------
inline void NiSurface::SetTexturingProperty(NiTexturingProperty* pkTexProp)
{
    m_spTexProp = pkTexProp;
    m_bCompiled = pkTexProp != NULL;
}

//--------------------------------------------------------------------------------------------------
inline NiTexturingProperty* NiSurface::GetTexturingProperty() const
{
    return m_spTexProp;
}

//--------------------------------------------------------------------------------------------------
inline void NiSurface::SetPackage(NiSurfacePackage* pkPackage)
{
    if (pkPackage)
    {
        pkPackage->ClaimSurface(this);
    }
    else if (m_pkPackage)
    {
        NiSurfacePackage* pkOldPackage = m_pkPackage;
        m_pkPackage = 0;
        pkOldPackage->UnloadSurface(GetName());
    }

    m_pkPackage = pkPackage;
}

//--------------------------------------------------------------------------------------------------
inline NiSurfacePackage* NiSurface::GetPackage() const
{
    return m_pkPackage;
}

//--------------------------------------------------------------------------------------------------
inline void NiSurface::SetName(const NiString& kName)
{
    // This is recursion safe.
    if (m_pkPackage)
        m_pkPackage->RenameSurface(this, kName);

    m_kName = kName;
}

//--------------------------------------------------------------------------------------------------
inline const NiString& NiSurface::GetName() const
{
    return m_kName;
}

//--------------------------------------------------------------------------------------------------
inline void NiSurface::SetTextureSlotEntry(NiSurface::SurfaceMapID eMapID, 
    NiSurface::TextureSlotEntry* pkTexSlot)
{
    EE_ASSERT(eMapID < NUM_SURFACE_MAPS);

    if (m_apkTextureSlots[eMapID])
        EE_DELETE m_apkTextureSlots[eMapID];

    m_apkTextureSlots[eMapID] = pkTexSlot;
}

//--------------------------------------------------------------------------------------------------
inline NiSurface::TextureSlotEntry* NiSurface::GetTextureSlotEntry(SurfaceMapID eMapID) const
{
    return m_apkTextureSlots[eMapID];
}

//--------------------------------------------------------------------------------------------------
inline float NiSurface::GetTextureTiling() const
{
    return m_fTextureTiling;
}

//--------------------------------------------------------------------------------------------------
inline void NiSurface::SetTextureTiling(float fValue)
{
    m_fTextureTiling = fValue;
}

//--------------------------------------------------------------------------------------------------
inline float NiSurface::GetDetailTextureTiling() const
{
    return m_fDetailTextureTiling;
}

//--------------------------------------------------------------------------------------------------
inline void NiSurface::SetDetailTextureTiling(float fValue)
{
    m_fDetailTextureTiling = fValue;
}

//--------------------------------------------------------------------------------------------------
inline float NiSurface::GetRotation() const
{
    return m_fRotation;
}

//--------------------------------------------------------------------------------------------------
inline void NiSurface::SetRotation(float fValue)
{
    m_fRotation = fValue;
}

//--------------------------------------------------------------------------------------------------
inline float NiSurface::GetParallaxStrength() const
{
    return m_fParallaxStrength;
}

//--------------------------------------------------------------------------------------------------
inline void NiSurface::SetParallaxStrength(float fValue)
{
    m_fParallaxStrength = fValue;
}

//--------------------------------------------------------------------------------------------------
inline float NiSurface::GetDistributionMaskStrength() const
{
    return m_fDistributionMaskStrength;
}

//--------------------------------------------------------------------------------------------------
inline void NiSurface::SetDistributionMaskStrength(float fValue)
{
    m_fDistributionMaskStrength = fValue;
}

//--------------------------------------------------------------------------------------------------
inline float NiSurface::GetSpecularPower() const
{
    return m_fSpecularPower;
}

//--------------------------------------------------------------------------------------------------
inline void NiSurface::SetSpecularPower(float fValue)
{
    m_fSpecularPower = fValue;
}

//--------------------------------------------------------------------------------------------------
inline float NiSurface::GetSpecularIntensity() const
{
    return m_fSpecularIntensity;
}

//--------------------------------------------------------------------------------------------------
inline void NiSurface::SetSpecularIntensity(float fValue)
{
    m_fSpecularIntensity = fValue;
}

//--------------------------------------------------------------------------------------------------
inline bool NiSurface::HasValidTextureSlots() const
{
    for (efd::SInt32 i = 0; i < NUM_SURFACE_MAPS; i++)
    {
        if (m_apkTextureSlots[i])
            return true;
    }

    return false;
}

//--------------------------------------------------------------------------------------------------
inline NiMetaData& NiSurface::GetMetaData()
{
    return m_kMetaData;
}

//--------------------------------------------------------------------------------------------------
inline const NiMetaData& NiSurface::GetMetaData() const
{
    return m_kMetaData;
}

//--------------------------------------------------------------------------------------------------
inline bool NiSurface::IsCompiled() const
{
    return m_bCompiled;
}

//--------------------------------------------------------------------------------------------------
inline void NiSurface::MarkResolved(bool bResolved)
{
    m_bIsResolved = bResolved;
}

//--------------------------------------------------------------------------------------------------
inline bool NiSurface::IsResolved() const
{
    return m_bIsResolved;
}

//--------------------------------------------------------------------------------------------------
