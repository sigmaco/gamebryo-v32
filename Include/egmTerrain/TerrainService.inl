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


namespace egmTerrain
{
//--------------------------------------------------------------------------------------------------
#define LOG_TERRAIN_LOAD_ERROR(module, level, args, displayError) \
    {EE_LOG(module, level, args); SkipPreloadingAssets(displayError);}
//--------------------------------------------------------------------------------------------------
inline NiTerrain* TerrainService::GetNiTerrain()
{
    EE_ASSERT(m_terrainEntities.size() <= 1);

    if (m_terrainEntities.size() == 1)
        return GetTerrainForEntity(m_terrainEntities.front());
    else
        return NULL;
}

//--------------------------------------------------------------------------------------------------
inline egf::Entity* TerrainService::GetTerrainEntity()
{
    EE_ASSERT(m_terrainEntities.size() <= 1);
    
    if (m_terrainEntities.size() == 1)
        return m_terrainEntities.front();
    else
        return NULL;
}

//--------------------------------------------------------------------------------------------------

// DT32966
// The following method uses SendImmediate to send messages. However, this method can
// be invoked in the context of another message handler. This ordering violates best practices 
// and should be investigated for refactoring as it can cause problems with the order that
// handlers are invoked in other services.
inline void TerrainService::RaiseTerrainChanged()
{
    TerrainChangedMessagePtr spMessage = EE_NEW TerrainChangedMessage();
    m_pMessageService->SendImmediate(spMessage);
}

//--------------------------------------------------------------------------------------------------
} // namespace
