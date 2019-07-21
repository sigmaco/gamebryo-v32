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

namespace egmSample
{

//--------------------------------------------------------------------------------------------------
inline void WalkableService::SetMaxSlope(efd::Float32 newSlope)
{
    m_maxSlope = newSlope;
}

//--------------------------------------------------------------------------------------------------
inline efd::Float32 WalkableService::GetMaxSlope()
{
    return m_maxSlope;
}

//--------------------------------------------------------------------------------------------------
inline void WalkableService::SetTerrainLODLevel(efd::UInt32 newLOD)
{
    m_terrainLODLevel = newLOD;
}

//--------------------------------------------------------------------------------------------------
inline efd::UInt32 WalkableService::GetTerrainLODLevel()
{
    return m_terrainLODLevel;
}

//--------------------------------------------------------------------------------------------------
inline void WalkableService::SetPickHeight(efd::Float32 newHeight)
{
    m_pickHeight = newHeight;
}

//--------------------------------------------------------------------------------------------------
inline efd::Float32 WalkableService::GetPickHeight()
{
    return m_pickHeight;
}

//--------------------------------------------------------------------------------------------------
inline void WalkableService::SetPickDirection(efd::Point3 newDirection)
{
    m_pickDir = newDirection;
}

//--------------------------------------------------------------------------------------------------
inline efd::Point3 WalkableService::GetPickDirection()
{
    return m_pickDir;
}

//--------------------------------------------------------------------------------------------------
inline void WalkableService::SetTrackMaterial(efd::Bool trackChanges)
{
    m_trackMaterialChanges = trackChanges;
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool WalkableService::GetTrackMaterial()
{
    return m_trackMaterialChanges;
}

//--------------------------------------------------------------------------------------------------
inline void WalkableService::SetWalkAnywhere(efd::Bool walkAnywhere)
{
    m_walkAnywhere = walkAnywhere;
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool WalkableService::GetWalkAnywhere()
{
    return m_walkAnywhere;
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool WalkableService::GetCurrentMaterial(
    egf::Entity* pEntity,
    NiFixedString& materialName)
{
    if (m_trackMaterialChanges)
    {
        efd::map<egf::Entity*, NiFixedString>::iterator iterator = m_MaterialMap.find(pEntity);
        if (iterator != m_MaterialMap.end())
        {
            materialName = iterator->second;
            return true;
        }
    }

    return false;
}

//--------------------------------------------------------------------------------------------------
} // end namespace egmSample
