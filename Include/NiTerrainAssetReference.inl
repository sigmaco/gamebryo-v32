// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not
// be copied or disclosed excekPt in accordance with the terms of that
// agreement.
//
//      Copyright (c) 1996-2009 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Calabasas, CA 91302
// http://www.emergent.net

//--------------------------------------------------------------------------------------------------
inline const efd::utf8string& NiTerrainAssetReference::GetResolvedLocation() const
{
    return m_kResolvedLocation;
}

//--------------------------------------------------------------------------------------------------
inline efd::utf8string NiTerrainAssetReference::GetStoredLocation() const
{
    // Calculate the expected location of the asset based on relative path to this file
    efd::utf8string kPath = GetRelativeAssetLocation();
    efd::utf8string kRefferingLocation = 
        efd::PathUtils::PathRemoveFileName(GetReferingAssetLocation());
    if (!kRefferingLocation.empty())
    {
        kPath = efd::PathUtils::PathCombine(kRefferingLocation, kPath);
    }

    // Clean up the path
    kPath = efd::PathUtils::PathRemoveSlashDotSlash(kPath);
    kPath = efd::PathUtils::PathRemoveSlashSlash(kPath);

    // Copy the path into a temp char* and remove the dot dot's (PathRemoveDotDots has a bug)
    // DT #41174 
    efd::Char* pcTempPath = EE_ALLOC(efd::Char, kPath.length() + 1);
    memcpy(pcTempPath, kPath.c_str(), (kPath.length() + 1) * sizeof(efd::Char));
    efd::PathUtils::RemoveDotDots(pcTempPath);
    kPath = pcTempPath;
    EE_FREE(pcTempPath);
    
    return kPath;
}

//--------------------------------------------------------------------------------------------------
inline const efd::utf8string& NiTerrainAssetReference::GetAssetID() const
{
    return m_kAssetID;
}

//--------------------------------------------------------------------------------------------------
inline const efd::utf8string& NiTerrainAssetReference::GetReferingAssetLocation() const
{
    return m_kReferingAssetLocation;
}

//--------------------------------------------------------------------------------------------------
inline const efd::utf8string& NiTerrainAssetReference::GetRelativeAssetLocation() const
{
    return m_kRelativeAssetLocation;
}

//--------------------------------------------------------------------------------------------------
inline bool NiTerrainAssetReference::IsResolved() const
{
    return m_bIsResolved;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainAssetReference::MarkResolved(bool bResolved)
{
    m_bIsResolved = bResolved;
    if (bResolved)
    {
        OnResolved();
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainAssetReference::SetReferringAssetLocation(const efd::utf8string& kLocation)
{
    m_kReferingAssetLocation = kLocation;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainAssetReference::SetRelativeAssetLocation(const efd::utf8string& kLocation)
{
    m_kRelativeAssetLocation = kLocation;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainAssetReference::SetAssetID(const efd::utf8string& kAssetID)
{
    m_kAssetID = kAssetID;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainAssetReference::SetResolvedLocation(const efd::utf8string& kLocation)
{
    m_kResolvedLocation = kLocation;
}

//--------------------------------------------------------------------------------------------------

