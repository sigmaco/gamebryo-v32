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

//------------------------------------------------------------------------------------------------
inline efd::UInt32 egf::EntityLoaderService::GetMaxEntityLoadThrottle() const
{
    return m_maxEntityLoadThrottle;
}

//------------------------------------------------------------------------------------------------
inline void egf::EntityLoaderService::SetMaxEntityLoadThrottle(efd::UInt32 entities)
{
    EE_ASSERT(entities > 0);
    m_maxEntityLoadThrottle = entities;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 egf::EntityLoaderService::GetMaxEntityUnloadThrottle() const
{
    return m_maxEntityUnloadThrottle;
}

//------------------------------------------------------------------------------------------------
inline void egf::EntityLoaderService::SetMaxEntityUnloadThrottle(efd::UInt32 entities)
{
    m_maxEntityUnloadThrottle = entities;
}

//------------------------------------------------------------------------------------------------
inline efd::Category egf::EntityLoaderService::GetPrivateChannel()
{
    return m_myPrivateChannel;
}

//------------------------------------------------------------------------------------------------
inline egf::EntityLoaderService::WorldLoadedInfo::WorldLoadedInfo()
    : m_createdCount(0)
    , m_enteredWorldCount(0)
{
}
