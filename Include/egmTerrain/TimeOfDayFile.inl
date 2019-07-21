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
inline TimeOfDayFile::FileVersion TimeOfDayFile::GetFileVersion() const
{
    return m_fileVersion;
}

//--------------------------------------------------------------------------------------------------
inline bool TimeOfDayFile::IsReady() const
{
    return m_ready;
}

//--------------------------------------------------------------------------------------------------
inline bool TimeOfDayFile::IsWritable() const
{
    return m_writeAccess;
}

//--------------------------------------------------------------------------------------------------
inline TimeOfDayFile::FileVersion TimeOfDayFile::GetCurrentVersion()
{
    return ms_fileVersion;
}

//--------------------------------------------------------------------------------------------------
inline void TimeOfDayFile::AddEntity(efd::ID128 entityID, efd::utf8string entityName)
{
    efd::utf8string existingName;
    if (!m_registeredEntities.find(entityID, existingName))
    {
        m_registeredEntities[entityID] = entityName;
    }

    EntityToPropertyMap::iterator it;
    it = m_entityToPropertyMap.find(entityID);
    if (it == m_entityToPropertyMap.end())
    {
        PropertyVector properties;
        m_entityToPropertyMap[entityID] = properties;
    }
    else
    {
        PropertyVector::iterator propIter = m_entityToPropertyMap[entityID].begin();

        while (propIter != m_entityToPropertyMap[entityID].end())
        {
            m_propertyMap[propIter->m_propertyName].clear();
            m_propertyMap.erase(propIter->m_propertyName);
            ++propIter;
        }
        
        m_entityToPropertyMap[entityID].clear();
    }
}

//--------------------------------------------------------------------------------------------------
inline bool TimeOfDayFile::AddProperty(efd::ID128 entityID,
    EnvironmentService::ToDProperty toAdd)
{
    PropertyToKeyframeMap::iterator it;
    it = m_propertyMap.find(toAdd.m_propertyName);
    
    if (it == m_propertyMap.end())
    {
        efd::vector<Keyframe> keyframeSequence;
        m_propertyMap[toAdd.m_propertyName] = keyframeSequence;

        m_entityToPropertyMap[entityID].push_back(toAdd);
    }
    else
    {
        m_propertyMap[toAdd.m_propertyName].clear();
    }

    return true;
}

//--------------------------------------------------------------------------------------------------
inline efd::utf8string TimeOfDayFile::GetFilePath() const
{
    return m_fileName;
}

}
