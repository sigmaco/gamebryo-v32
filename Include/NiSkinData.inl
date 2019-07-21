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

#ifndef EE_REMOVE_BACK_COMPAT_STREAMING

//--------------------------------------------------------------------------------------------------
inline NiSkinData::NiSkinData()
    : m_pkBoneData(0)
{
    // Used for streaming. All members will be initialized by LoadBinary.
}

//--------------------------------------------------------------------------------------------------
inline unsigned int NiSkinData::GetBoneCount() const
{
    return m_uiBones;
}

//--------------------------------------------------------------------------------------------------
inline NiSkinData::BoneData* NiSkinData::GetBoneData() const
{
    return m_pkBoneData;
}

//--------------------------------------------------------------------------------------------------
inline const NiTransform& NiSkinData::GetRootParentToSkin() const
{
    return m_kRootParentToSkin;
}

//--------------------------------------------------------------------------------------------------
inline NiSkinPartition* NiSkinData::GetSkinPartition(bool bDontAssert) const
{
    if (bDontAssert)
        return m_spSkinPartition;
    EE_ASSERT(false);
    return NULL;
}

//--------------------------------------------------------------------------------------------------
inline void NiSkinData::SetSkinPartition(NiSkinPartition* pkSkinPartition,
    bool bDontAssert)
{
    if (bDontAssert)
        m_spSkinPartition = pkSkinPartition;
    else
        EE_ASSERT(false);
}

//--------------------------------------------------------------------------------------------------
#endif // #ifndef EE_REMOVE_BACK_COMPAT_STREAMING
