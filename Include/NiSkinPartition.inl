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
inline unsigned int NiSkinPartition::GetPartitionCount() const
{
    return m_uiPartitions;
}

//--------------------------------------------------------------------------------------------------
inline NiSkinPartition::Partition* NiSkinPartition::GetPartitions()
{
    return m_pkPartitions;
}

//--------------------------------------------------------------------------------------------------
inline const NiSkinPartition::Partition* NiSkinPartition::GetPartitions() const
{
    return m_pkPartitions;
}

//--------------------------------------------------------------------------------------------------
#endif // #ifndef EE_REMOVE_BACK_COMPAT_STREAMING
