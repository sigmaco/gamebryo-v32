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


namespace egf
{

//------------------------------------------------------------------------------------------------
template<typename T>
PropertyResult Entity::GetPropertyValue(
    PropertyID propID,
    T& data) const
{
    return GetPropertyValueUnsafe(propID, &data, efd::GetClassIDFromType<T>());
}

//------------------------------------------------------------------------------------------------
template<typename T>
PropertyResult Entity::GetPropertyValue(
    const efd::utf8string& propName,
    T& data) const
{
    EE_ASSERT(this != NULL);
    egf::PropertyID propID = EE_NAME2ID(propName);
    if (propID == 0)
    {
        return PropertyResult_PropertyNotFound;
    }
    return GetPropertyValueUnsafe(propID, &data, efd::GetClassIDFromType<T>());
}

//------------------------------------------------------------------------------------------------
template<typename T>
PropertyResult Entity::GetPropertyValue(
    PropertyID propID,
    const efd::utf8string& key,
    T& data) const
{
    return GetPropertyValueUnsafe(propID, key, &data, efd::GetClassIDFromType<T>());
}

//------------------------------------------------------------------------------------------------
template<typename T>
PropertyResult Entity::GetPropertyValue(
    const efd::utf8string& propName,
    const efd::utf8string& key,
    T& data) const
{
    egf::PropertyID propID = EE_NAME2ID(propName);
    if (propID == 0)
    {
        return PropertyResult_PropertyNotFound;
    }
    return GetPropertyValueUnsafe(propID, key, &data, efd::GetClassIDFromType<T>());
}

//------------------------------------------------------------------------------------------------
inline PropertyID Entity::GetPropertyID(const efd::utf8string& propName) const
{
    const PropertyDescriptor* ppd = m_pFlatModel->GetPropertyDescriptor(propName);
    if (ppd)
    {
        return ppd->GetPropertyID();
    }

    return 0;
}

//------------------------------------------------------------------------------------------------
template<typename T>
PropertyResult Entity::GetDefaultPropertyValue(
    PropertyID propID,
    T& data) const
{
    return GetDefaultPropertyValueUnsafe(propID, &data, efd::GetClassIDFromType<T>());
}

//------------------------------------------------------------------------------------------------
template<typename T>
PropertyResult Entity::GetDefaultPropertyValue(
    const efd::utf8string& propName,
    T& data) const
{
    egf::PropertyID propID = EE_NAME2ID(propName);
    if (propID == 0)
    {
        return PropertyResult_PropertyNotFound;
    }
    return GetDefaultPropertyValueUnsafe(propID, &data, efd::GetClassIDFromType<T>());
}

//------------------------------------------------------------------------------------------------
template<typename T>
PropertyResult Entity::GetDefaultPropertyValue(
    PropertyID propID,
    const efd::utf8string& key,
    T& data) const
{
    return GetDefaultPropertyValueUnsafe(propID, key, &data, efd::GetClassIDFromType<T>());
}

//------------------------------------------------------------------------------------------------
template<typename T>
PropertyResult Entity::GetDefaultPropertyValue(
    const efd::utf8string& propName,
    const efd::utf8string& key,
    T& data) const
{
    egf::PropertyID propID = EE_NAME2ID(propName);
    if (propID == 0)
    {
        return PropertyResult_PropertyNotFound;
    }
    return GetDefaultPropertyValueUnsafe(propID, key, &data, efd::GetClassIDFromType<T>());
}

//------------------------------------------------------------------------------------------------
template<typename T>
PropertyResult Entity::SetPropertyValue(
    PropertyID propID,
    const T& data)
{
    return SetPropertyValueUnsafe(propID, &data, efd::GetClassIDFromType<T>());
}

//------------------------------------------------------------------------------------------------
template<typename T>
PropertyResult Entity::SetPropertyValue(
    const efd::utf8string& propName,
    const T& data)
{
    egf::PropertyID propID = EE_NAME2ID(propName);
    if (propID == 0)
    {
        return PropertyResult_PropertyNotFound;
    }
    return SetPropertyValueUnsafe(propID, &data, efd::GetClassIDFromType<T>());
}

//------------------------------------------------------------------------------------------------
template<typename T>
PropertyResult Entity::SetPropertyValue(
    PropertyID propID,
    const efd::utf8string& key,
    const T& data)
{
    return SetPropertyValueUnsafe(propID, key, &data, efd::GetClassIDFromType<T>());
}

//------------------------------------------------------------------------------------------------
template<typename T>
PropertyResult Entity::SetPropertyValue(
    const efd::utf8string& propName,
    const efd::utf8string& key,
    const T& data)
{
    egf::PropertyID propID = EE_NAME2ID(propName);
    if (propID == 0)
    {
        return PropertyResult_PropertyNotFound;
    }
    return SetPropertyValueUnsafe(propID, key, &data, efd::GetClassIDFromType<T>());
}


//------------------------------------------------------------------------------------------------
inline PropertyResult Entity::SetPropertyValueByString(
    const efd::utf8string& i_strPropName,
    const efd::utf8string& i_strValue)
{
    egf::PropertyID propID = EE_NAME2ID(i_strPropName);
    if (propID == 0)
    {
        return PropertyResult_PropertyNotFound;
    }
    return SetPropertyValueByString(propID, i_strValue);
}

//------------------------------------------------------------------------------------------------
inline PropertyResult Entity::SetPropertyValueByString(
    const efd::utf8string& i_strPropName,
    const efd::utf8string& i_strKey,
    const efd::utf8string& i_strValue)
{
    egf::PropertyID propID = EE_NAME2ID(i_strPropName);
    if (propID == 0)
    {
        return PropertyResult_PropertyNotFound;
    }
    return SetPropertyValueByString(propID, i_strKey, i_strValue);
}

//------------------------------------------------------------------------------------------------
template<typename T>
PropertyResult Entity::IncrementPropertyValue(
    PropertyID propID,
    T& data,
    T increment_value)
{
    //A failure here may indicate a type mismatch, check the result code.
    PropertyResult result = GetPropertyValueUnsafe(propID, &data, efd::GetClassIDFromType<T>());
    if (result == PropertyResult_OK)
    {
        data = data + increment_value;
        return SetPropertyValueUnsafe(propID, &data, efd::GetClassIDFromType<T>());
    }
    else
        return result;
}

//------------------------------------------------------------------------------------------------
template<typename T>
PropertyResult Entity::IncrementPropertyValue(
    const efd::utf8string& propName,
    T& data,
    T increment_value)
{
    egf::PropertyID propID = EE_NAME2ID(propName);
    if (propID == 0)
    {
        return PropertyResult_PropertyNotFound;
    }

    return IncrementPropertyValue(propID, data, increment_value);
}

//------------------------------------------------------------------------------------------------
template<typename T>
PropertyResult Entity::DecrementPropertyValue(
    PropertyID propID,
    T& data,
    T decrement_value)
{
    //A failure here may indicate a type mismatch, check the result code.
    PropertyResult result = GetPropertyValueUnsafe(propID, &data, efd::GetClassIDFromType<T>());
    if (result == PropertyResult_OK)
    {
        data = data - decrement_value;
        return SetPropertyValueUnsafe(propID, &data, efd::GetClassIDFromType<T>());
    }

    return result;
}

//------------------------------------------------------------------------------------------------
template<typename T>
PropertyResult Entity::DecrementPropertyValue(
    const efd::utf8string& propName,
    T& data,
    T decrement_value)
{
    egf::PropertyID propID = EE_NAME2ID(propName);
    if (propID == 0)
    {
        return PropertyResult_PropertyNotFound;
    }

    return DecrementPropertyValue(propID, data, decrement_value);
}

//------------------------------------------------------------------------------------------------
inline PropertyResult Entity::HasPropertyValue(PropertyID propID) const
{
    const PropertyDescriptor* pDesc = NULL;
    return _GetPropDesc(propID, pDesc);
}

//------------------------------------------------------------------------------------------------
inline PropertyResult Entity::HasPropertyValue(
    const efd::utf8string& propName,
    const efd::utf8string& key) const
{
    egf::PropertyID propID = EE_NAME2ID(propName);
    if (propID == 0)
    {
        return PropertyResult_PropertyNotFound;
    }
    return HasPropertyValue(propID, key);
}

//------------------------------------------------------------------------------------------------
inline PropertyResult Entity::HasPropertyValue(const efd::utf8string& propName) const
{
    const PropertyDescriptor* pDesc = NULL;
    return _GetPropDesc(propName, pDesc);
}

//------------------------------------------------------------------------------------------------
inline PropertyResult Entity::RemovePropertyValue(
    const efd::utf8string& propName,
    const efd::utf8string& key)
{
    egf::PropertyID propID = EE_NAME2ID(propName);
    if (propID == 0)
    {
        return PropertyResult_PropertyNotFound;
    }
    return RemovePropertyValue(propID, key);
}

//------------------------------------------------------------------------------------------------
inline bool Entity::IsDirty(PropertyID propID) const
{
    return m_dirtyPropertySet.count(propID) > 0;
}

//------------------------------------------------------------------------------------------------
inline bool Entity::IsDirty(const efd::utf8string& propName) const
{
    egf::PropertyID propID = EE_NAME2ID(propName);
    if (propID == 0)
    {
        return false;
    }
    return m_dirtyPropertySet.count(propID) > 0;
}

//------------------------------------------------------------------------------------------------
inline void Entity::ClearDirty()
{
    m_dirtyPropertySet.clear();
}

//------------------------------------------------------------------------------------------------
inline egf::EntityManager* Entity::GetEntityManager() const
{
    return m_pEntityManager;
}

//------------------------------------------------------------------------------------------------
inline void Entity::SetEntityManager(EntityManager* pMgr)
{
    m_pEntityManager = pMgr;
}

//------------------------------------------------------------------------------------------------
inline egf::Scheduler* Entity::GetScheduler() const
{
    return m_pScheduler;
}

//------------------------------------------------------------------------------------------------
inline const FlatModel* Entity::GetModel() const
{
    return m_pFlatModel;    // return ID class pointer
}

//------------------------------------------------------------------------------------------------
inline FlatModelID Entity::GetModelID() const
{
    if (m_pFlatModel)
        return m_pFlatModel->GetID();
    return 0;
}

//------------------------------------------------------------------------------------------------
inline const efd::utf8string& Entity::GetModelName() const
{
    if (m_pFlatModel)
        return m_pFlatModel->GetName();
    return efd::utf8string::NullString();
}

//------------------------------------------------------------------------------------------------
inline void Entity::SetModel(const FlatModel* flatModel)
{
    m_pFlatModel = flatModel;
}

//------------------------------------------------------------------------------------------------
inline const EntityID& Entity::GetEntityID() const
{
    return m_entityID;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt64 Entity::GetEntityIDValue() const
{
    return m_entityID.GetValue();
}

//------------------------------------------------------------------------------------------------
inline void Entity::SetID(const EntityID& entityID)
{
    m_entityID = entityID;
}

//------------------------------------------------------------------------------------------------
inline const efd::ID128& Entity::GetDataFileID() const
{
    return m_dataFileID;
}

//------------------------------------------------------------------------------------------------
inline void Entity::SetDataFileID(const efd::ID128& id)
{
    m_dataFileID = id;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 Entity::GetBlockInstance() const
{
    return m_blockInstance;
}

//------------------------------------------------------------------------------------------------
inline void Entity::SetBlockInstance(efd::UInt32 id)
{
    m_blockInstance = id;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 Entity::GetIterationCount() const
{
    return m_iterationCount;
}

//------------------------------------------------------------------------------------------------
inline void Entity::SetIterationCount(const efd::UInt32 iteration)
{
    m_iterationCount = iteration;
}

//------------------------------------------------------------------------------------------------
inline Scheduler* Entity::GetExecutor() const
{
    // return ptr to scheduler who currently owns us
    return m_pScheduler;
}

//------------------------------------------------------------------------------------------------
inline IBuiltinModel* Entity::FindBuiltinModel(FlatModelID i_componentId) const
{
    IBuiltinModelPtr pComp;
    m_BuiltinModels.find(i_componentId, pComp);
    return pComp;
}

//------------------------------------------------------------------------------------------------
inline bool Entity::IsPropertyOverridden(PropertyID i_pid) const
{
    return m_propertyMap.find(i_pid) != m_propertyMap.end();
}

//------------------------------------------------------------------------------------------------
} // end namespace egf

