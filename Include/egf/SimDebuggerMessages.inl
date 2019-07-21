// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or nondisclosure agreement
// with Emergent Game Technologies and may not be copied or disclosed except in accordance with
// the terms of that agreement.
//
//      Copyright (c) 1996-2009 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Calabasas, CA 91302
// http://www.emergent.net

namespace egf
{

//------------------------------------------------------------------------------------------------
inline DebugNoteBase::DebugNoteBase()
    : m_timestamp(0.0f)
    , m_gameID(kENTITY_INVALID)
{
}

//------------------------------------------------------------------------------------------------
inline DebugNoteBase::DebugNoteBase(egf::EntityID gameID)
    : m_gameID(gameID)
{
}

//------------------------------------------------------------------------------------------------
inline DebugNoteBase::~DebugNoteBase()
{
}

//------------------------------------------------------------------------------------------------
inline efd::Float64 DebugNoteBase::GetTimestamp() const
{
    return m_timestamp;
}

//------------------------------------------------------------------------------------------------
inline void DebugNoteBase::SetTimestamp(efd::Float64 timestamp)
{
    m_timestamp = timestamp;
}

//------------------------------------------------------------------------------------------------
inline egf::EntityID DebugNoteBase::GetGameID() const
{
    return m_gameID;
}


//------------------------------------------------------------------------------------------------
inline DebugNoteEvent::DebugNoteEvent()
{
}

//------------------------------------------------------------------------------------------------
inline DebugNoteEvent::DebugNoteEvent(
    egf::EntityID gameID,
    const efd::utf8string& eventName,
    const efd::utf8string& params)
    : DebugNoteBase(gameID)
    , m_eventName(eventName)
    , m_params(params)
{
}

//------------------------------------------------------------------------------------------------
inline DebugNoteEvent::~DebugNoteEvent()
{
}

//------------------------------------------------------------------------------------------------
inline const efd::utf8string& DebugNoteEvent::GetEventName() const
{
    return m_eventName;
}

//------------------------------------------------------------------------------------------------
inline const efd::utf8string& DebugNoteEvent::GetParams() const
{
    return m_params;
}


//------------------------------------------------------------------------------------------------
inline DebugNoteSessionStarted::DebugNoteSessionStarted()
{
}

//------------------------------------------------------------------------------------------------
inline DebugNoteSessionStarted::~DebugNoteSessionStarted()
{
}


//------------------------------------------------------------------------------------------------
inline DebugNoteFlatModelDefined::DebugNoteFlatModelDefined()
{
}

//------------------------------------------------------------------------------------------------
inline DebugNoteFlatModelDefined::DebugNoteFlatModelDefined(const efd::utf8string& modelName)
    : m_modelName(modelName)
    , m_isMesh(false)
    , m_isActor(false)
{
}

//------------------------------------------------------------------------------------------------
inline DebugNoteFlatModelDefined::~DebugNoteFlatModelDefined()
{
}

//------------------------------------------------------------------------------------------------
inline const efd::utf8string& DebugNoteFlatModelDefined::GetModelName() const
{
    return m_modelName;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool DebugNoteFlatModelDefined::IsMesh() const
{
    return m_isMesh;
}

//------------------------------------------------------------------------------------------------
inline void DebugNoteFlatModelDefined::SetIsMesh()
{
    m_isMesh = true;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool DebugNoteFlatModelDefined::IsActor() const
{
    return m_isActor;
}

//------------------------------------------------------------------------------------------------
inline void DebugNoteFlatModelDefined::SetIsActor()
{
    m_isActor = true;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 DebugNoteFlatModelDefined::GetPropertyCount() const
{
    return m_properties.size();
}

//------------------------------------------------------------------------------------------------
inline const efd::utf8string& DebugNoteFlatModelDefined::GetPropertyName(efd::UInt32 index) const
{
    return m_properties[index].first;
}

//------------------------------------------------------------------------------------------------
inline const efd::utf8string& DebugNoteFlatModelDefined::GetPropertyValue(efd::UInt32 index) const
{
    return m_properties[index].second;
}

//------------------------------------------------------------------------------------------------
inline void DebugNoteFlatModelDefined::AddProperty(const efd::utf8string& name,
                                                   const efd::utf8string& value)
{
    efd::UInt32 index = m_properties.size();
    m_properties.resize(index + 1);
    m_properties[index].first = name;
    m_properties[index].second = value;
}


//------------------------------------------------------------------------------------------------
inline DebugNoteEntityCreated::DebugNoteEntityCreated()
{
}

//------------------------------------------------------------------------------------------------
inline DebugNoteEntityCreated::DebugNoteEntityCreated(
    egf::EntityID gameID,
    const efd::ID128& toolID,
    const efd::utf8string& modelName,
    const efd::Point3& position,
    efd::Float32 facing)
    : DebugNoteBase(gameID)
    , m_toolID(toolID)
    , m_modelName(modelName)
    , m_position(position)
    , m_facing(facing)
{
}

//------------------------------------------------------------------------------------------------
inline DebugNoteEntityCreated::~DebugNoteEntityCreated()
{
}

//------------------------------------------------------------------------------------------------
inline const efd::ID128& DebugNoteEntityCreated::GetToolID() const
{
    return m_toolID;
}

//------------------------------------------------------------------------------------------------
inline const efd::utf8string& DebugNoteEntityCreated::GetModelName() const
{
    return m_modelName;
}

//------------------------------------------------------------------------------------------------
inline const efd::Point3& DebugNoteEntityCreated::GetPosition() const
{
    return m_position;
}

//------------------------------------------------------------------------------------------------
inline efd::Float32 DebugNoteEntityCreated::GetFacingAngle() const
{
    return m_facing;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 DebugNoteEntityCreated::GetPropertyCount() const
{
    return m_properties.size();
}

//------------------------------------------------------------------------------------------------
inline const efd::utf8string& DebugNoteEntityCreated::GetPropertyName(efd::UInt32 index) const
{
    return m_properties[index].first;
}

//------------------------------------------------------------------------------------------------
inline const efd::utf8string& DebugNoteEntityCreated::GetPropertyValue(efd::UInt32 index) const
{
    return m_properties[index].second;
}

//------------------------------------------------------------------------------------------------
inline void DebugNoteEntityCreated::AddProperty(const efd::utf8string& name,
                                                const efd::utf8string& value)
{
    efd::UInt32 index = m_properties.size();
    m_properties.resize(index + 1);
    m_properties[index].first = name;
    m_properties[index].second = value;
}


//------------------------------------------------------------------------------------------------
inline DebugNoteEntityDestroyed::DebugNoteEntityDestroyed()
{
}

//------------------------------------------------------------------------------------------------
inline DebugNoteEntityDestroyed::DebugNoteEntityDestroyed(egf::EntityID gameID)
    : DebugNoteBase(gameID)
{
}

//------------------------------------------------------------------------------------------------
inline DebugNoteEntityDestroyed::~DebugNoteEntityDestroyed()
{
}


//------------------------------------------------------------------------------------------------
inline DebugNotePropertyChanged::DebugNotePropertyChanged()
{
}

//------------------------------------------------------------------------------------------------
inline DebugNotePropertyChanged::DebugNotePropertyChanged(
    egf::EntityID gameID,
    const efd::utf8string& propertyName,
    const efd::utf8string& propertyValue)
    : DebugNoteBase(gameID)
    , m_propertyName(propertyName)
    , m_propertyValue(propertyValue)
{
}

//------------------------------------------------------------------------------------------------
inline DebugNotePropertyChanged::~DebugNotePropertyChanged()
{
}

//------------------------------------------------------------------------------------------------
inline const efd::utf8string& DebugNotePropertyChanged::GetPropertyName() const
{
    return m_propertyName;
}

//------------------------------------------------------------------------------------------------
inline const efd::utf8string& DebugNotePropertyChanged::GetPropertyValue() const
{
    return m_propertyValue;
}


//------------------------------------------------------------------------------------------------
inline DebugNoteCollectionPropertyChanged::DebugNoteCollectionPropertyChanged()
{
}

//------------------------------------------------------------------------------------------------
inline DebugNoteCollectionPropertyChanged::DebugNoteCollectionPropertyChanged(
    egf::EntityID gameID,
    const efd::utf8string& propertyName)
    : DebugNoteBase(gameID)
    , m_propertyName(propertyName)
{
}

//------------------------------------------------------------------------------------------------
inline DebugNoteCollectionPropertyChanged::~DebugNoteCollectionPropertyChanged()
{
}

//------------------------------------------------------------------------------------------------
inline const efd::utf8string& DebugNoteCollectionPropertyChanged::GetPropertyName() const
{
    return m_propertyName;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 DebugNoteCollectionPropertyChanged::GetItemCount() const
{
    return m_items.size();
}

//------------------------------------------------------------------------------------------------
inline const efd::utf8string& DebugNoteCollectionPropertyChanged::GetItemKey(efd::UInt32 index)
    const
{
    return m_items[index].first;
}

//------------------------------------------------------------------------------------------------
inline const efd::utf8string& DebugNoteCollectionPropertyChanged::GetItemValue(efd::UInt32 index)
    const
{
    return m_items[index].second;
}

//------------------------------------------------------------------------------------------------
inline void DebugNoteCollectionPropertyChanged::AddItem(
    const efd::utf8string& key,
    const efd::utf8string& value)
{
    efd::UInt32 index = m_items.size();
    m_items.resize(index + 1);
    m_items[index].first = key;
    m_items[index].second = value;
}

}
