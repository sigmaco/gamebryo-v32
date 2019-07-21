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
// AddEntityMessage
//------------------------------------------------------------------------------------------------
inline egmToolServices::AddEntityMessage::OverrideEntry::OverrideEntry()
    : Key(NULL)
{
}

//------------------------------------------------------------------------------------------------
inline egmToolServices::AddEntityMessage::OverrideEntry::~OverrideEntry()
{
    EE_EXTERNAL_DELETE Key;
}

//------------------------------------------------------------------------------------------------
inline egmToolServices::AddEntityMessage::AddEntityMessage()
{
}

//------------------------------------------------------------------------------------------------
inline egmToolServices::AddEntityMessage::~AddEntityMessage()
{
}

//------------------------------------------------------------------------------------------------
inline void egmToolServices::AddEntityMessage::SetEntityId(const efd::ID128& value)
{
    m_entityId = value;
}

//------------------------------------------------------------------------------------------------
inline const efd::ID128& egmToolServices::AddEntityMessage::GetEntityId() const
{
    return m_entityId;
}

//------------------------------------------------------------------------------------------------
inline void egmToolServices::AddEntityMessage::SetModelName(const efd::utf8string& value)
{
    m_modelName = value;
}

//------------------------------------------------------------------------------------------------
inline const efd::utf8string& egmToolServices::AddEntityMessage::GetModelName() const
{
    return m_modelName;
}

//------------------------------------------------------------------------------------------------
inline efd::list<egmToolServices::AddEntityMessage::OverrideEntryPtr>*
egmToolServices::AddEntityMessage::GetOverrides()
{
    return &m_overrides;
}

//------------------------------------------------------------------------------------------------
inline const efd::list<egmToolServices::AddEntityMessage::OverrideEntryPtr>*
egmToolServices::AddEntityMessage::GetOverrides() const
{
    return &m_overrides;
}

//------------------------------------------------------------------------------------------------
inline void egmToolServices::AddEntityMessage::AddOverride(const efd::utf8string& pPropName,
                                                           const efd::utf8string& pPropValue,
                                                           const efd::utf8string* pKey)
{
    OverrideEntryPtr spEntry = EE_EXTERNAL_NEW OverrideEntry();
    spEntry->PropertyName = pPropName;
    spEntry->PropertyValue = pPropValue;

    if (pKey != NULL)
        spEntry->Key = EE_EXTERNAL_NEW efd::utf8string(*pKey);

    m_overrides.push_back(spEntry);
}


//------------------------------------------------------------------------------------------------
// RemoveEntityMessage
//------------------------------------------------------------------------------------------------
inline egmToolServices::RemoveEntityMessage::RemoveEntityMessage()
{
}

//------------------------------------------------------------------------------------------------
inline egmToolServices::RemoveEntityMessage::~RemoveEntityMessage()
{
}

//------------------------------------------------------------------------------------------------
inline void egmToolServices::RemoveEntityMessage::SetEntityId(efd::ID128 value)
{
    m_entityId = value;
}

//------------------------------------------------------------------------------------------------
inline efd::ID128 egmToolServices::RemoveEntityMessage::GetEntityId() const
{
    return m_entityId;
}

//------------------------------------------------------------------------------------------------
// SetEntityPropertyMessage
//------------------------------------------------------------------------------------------------
inline egmToolServices::SetEntityPropertyMessage::SetEntityPropertyMessage()
{
}

//------------------------------------------------------------------------------------------------
inline egmToolServices::SetEntityPropertyMessage::~SetEntityPropertyMessage()
{
}

//------------------------------------------------------------------------------------------------
inline void egmToolServices::SetEntityPropertyMessage::SetEntityId(efd::ID128 value)
{
    m_entityId = value;
}

//------------------------------------------------------------------------------------------------
inline efd::ID128 egmToolServices::SetEntityPropertyMessage::GetEntityId() const
{
    return m_entityId;
}

//------------------------------------------------------------------------------------------------
inline void egmToolServices::SetEntityPropertyMessage::SetPropertyName(efd::utf8string value)
{
    m_propertyName = value;
}

//------------------------------------------------------------------------------------------------
inline efd::utf8string egmToolServices::SetEntityPropertyMessage::GetPropertyName() const
{
    return m_propertyName;
}

//------------------------------------------------------------------------------------------------
inline void egmToolServices::SetEntityPropertyMessage::SetPropertyValue(efd::utf8string value)
{
    m_propertyValue = value;
}

//------------------------------------------------------------------------------------------------
inline efd::utf8string egmToolServices::SetEntityPropertyMessage::GetPropertyValue() const
{
    return m_propertyValue;
}

//------------------------------------------------------------------------------------------------
// SetEntitiesPropertiesMessage
//--------------------------------------------------------------------------------------------------
inline egmToolServices::SetEntitiesPropertiesMessage::OverrideEntry::OverrideEntry()
    : Key(NULL)
{
}
//--------------------------------------------------------------------------------------------------
inline egmToolServices::SetEntitiesPropertiesMessage::OverrideEntry::~OverrideEntry()
{
    if (Key != NULL)
        EE_EXTERNAL_DELETE Key;
}
inline egmToolServices::SetEntitiesPropertiesMessage::SetEntitiesPropertiesMessage()
{
}

//------------------------------------------------------------------------------------------------
inline egmToolServices::SetEntitiesPropertiesMessage::~SetEntitiesPropertiesMessage()
{
    m_overrides.clear();
}
//--------------------------------------------------------------------------------------------------
inline efd::list<egmToolServices::SetEntitiesPropertiesMessage::OverrideEntryPtr>*
egmToolServices::SetEntitiesPropertiesMessage::GetChanges()
{
    return &m_overrides;
}
//--------------------------------------------------------------------------------------------------
inline const efd::list<egmToolServices::SetEntitiesPropertiesMessage::OverrideEntryPtr>*
egmToolServices::SetEntitiesPropertiesMessage::GetChanges() const
{
    return &m_overrides;
}
//--------------------------------------------------------------------------------------------------
inline void egmToolServices::SetEntitiesPropertiesMessage::AddEntry(
    efd::ID128 entityId,
    efd::utf8string propName,
    efd::utf8string propValue,
    const efd::utf8string* pKey)
{
    OverrideEntryPtr spEntry = EE_EXTERNAL_NEW OverrideEntry();
    spEntry->Entityid = entityId;
    spEntry->PropertyName = propName;
    spEntry->PropertyValue = propValue;

    if (pKey != NULL)
        spEntry->Key = EE_EXTERNAL_NEW efd::utf8string(*pKey);

    m_overrides.push_back(spEntry);
}

//------------------------------------------------------------------------------------------------
// SetGizmoBasisMessage
//------------------------------------------------------------------------------------------------
inline egmToolServices::SetGizmoBasisMessage::SetGizmoBasisMessage()
{
}

//------------------------------------------------------------------------------------------------
inline egmToolServices::SetGizmoBasisMessage::~SetGizmoBasisMessage()
{
}

//------------------------------------------------------------------------------------------------
inline void egmToolServices::SetGizmoBasisMessage::SetRelativeSpace(efd::UInt16 value)
{
    m_relativeSpace = value;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt16 egmToolServices::SetGizmoBasisMessage::GetRelativeSpace() const
{
    return m_relativeSpace;
}

//-----------------------------------------------------------------------------------------------
// BeginCloneEntityMessage
//-----------------------------------------------------------------------------------------------
inline egmToolServices::BeginCloneEntityMessage::BeginCloneEntityMessage()
{
}
//----------------------------------------------------------------------------------------------
inline egmToolServices::BeginCloneEntityMessage::~BeginCloneEntityMessage()
{
}

//------------------------------------------------------------------------------------------------
// SettingsUpdateMessage
//------------------------------------------------------------------------------------------------
inline egmToolServices::SettingsUpdateMessage::SettingsUpdateMessage()
{
}

//------------------------------------------------------------------------------------------------
inline egmToolServices::SettingsUpdateMessage::~SettingsUpdateMessage()
{
}

//------------------------------------------------------------------------------------------------
inline void egmToolServices::SettingsUpdateMessage::SetSettingName(efd::utf8string value)
{
    m_settingName = value;
}

//------------------------------------------------------------------------------------------------
inline efd::utf8string egmToolServices::SettingsUpdateMessage::GetSettingName() const
{
    return m_settingName;
}

//------------------------------------------------------------------------------------------------
inline void egmToolServices::SettingsUpdateMessage::SetSettingValue(efd::utf8string value)
{
    m_settingValue = value;
}

//------------------------------------------------------------------------------------------------
inline efd::utf8string egmToolServices::SettingsUpdateMessage::GetSettingValue() const
{
    return m_settingValue;
}

//------------------------------------------------------------------------------------------------
// SetActiveCameraMessage
//------------------------------------------------------------------------------------------------
inline egmToolServices::SetActiveCameraMessage::SetActiveCameraMessage()
{
    m_cameraName = "";
    m_window = 0;
}

//------------------------------------------------------------------------------------------------
inline egmToolServices::SetActiveCameraMessage::~SetActiveCameraMessage()
{
}

//------------------------------------------------------------------------------------------------
inline void egmToolServices::SetActiveCameraMessage::SetWindow(efd::UInt64 value)
{
    m_window = value;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt64 egmToolServices::SetActiveCameraMessage::GetWindow() const
{
    return m_window;
}

//------------------------------------------------------------------------------------------------
inline void egmToolServices::SetActiveCameraMessage::SetCameraName(efd::utf8string value)
{
    m_cameraName = value;
}

//------------------------------------------------------------------------------------------------
inline efd::utf8string egmToolServices::SetActiveCameraMessage::GetCameraName() const
{
    return m_cameraName;
}

//------------------------------------------------------------------------------------------------
// CameraUpdateMessage
//------------------------------------------------------------------------------------------------
inline egmToolServices::CameraUpdateMessage::CameraUpdateMessage()
{
}

//------------------------------------------------------------------------------------------------
inline egmToolServices::CameraUpdateMessage::~CameraUpdateMessage()
{
}

//------------------------------------------------------------------------------------------------
inline void egmToolServices::CameraUpdateMessage::SetWindowHandle(efd::WindowRef windowRef)
{
    m_windowRef = windowRef;
}

//------------------------------------------------------------------------------------------------
inline efd::WindowRef egmToolServices::CameraUpdateMessage::GetWindowHandle() const
{
    return m_windowRef;
}

//------------------------------------------------------------------------------------------------
inline efd::map<efd::utf8string, efd::utf8string>&
    egmToolServices::CameraUpdateMessage::GetChanges()
{
    return m_changes;
}

//------------------------------------------------------------------------------------------------
inline const efd::map<efd::utf8string, efd::utf8string>&
    egmToolServices::CameraUpdateMessage::GetChanges() const
{
    return m_changes;
}

//------------------------------------------------------------------------------------------------
inline void egmToolServices::CameraUpdateMessage::AddChange(efd::utf8string propName,
                                                            efd::utf8string propValue)
{
    m_changes[propName] = propValue;
}

//------------------------------------------------------------------------------------------------
// CreateEntityMessage
//------------------------------------------------------------------------------------------------
inline egmToolServices::CreateEntityMessage::CreateEntityMessage()
{
}

//------------------------------------------------------------------------------------------------
inline egmToolServices::CreateEntityMessage::~CreateEntityMessage()
{
}

//------------------------------------------------------------------------------------------------
inline void egmToolServices::CreateEntityMessage::SetModelName(const efd::utf8string& value)
{
    m_modelName = value;
}

//------------------------------------------------------------------------------------------------
inline const efd::utf8string& egmToolServices::CreateEntityMessage::GetModelName() const
{
    return m_modelName;
}

//------------------------------------------------------------------------------------------------
inline void egmToolServices::CreateEntityMessage::SetPosition(const efd::Point3& value)
{
    m_position = value;
}

//------------------------------------------------------------------------------------------------
inline const efd::Point3& egmToolServices::CreateEntityMessage::GetPosition() const
{
    return m_position;
}

//------------------------------------------------------------------------------------------------
inline void egmToolServices::CreateEntityMessage::SetRotation(const efd::Point3& value)
{
    m_rotation = value;
}

//------------------------------------------------------------------------------------------------
inline const efd::Point3& egmToolServices::CreateEntityMessage::GetRotation() const
{
    return m_rotation;
}

//------------------------------------------------------------------------------------------------
// InputActionMessage
//------------------------------------------------------------------------------------------------
inline egmToolServices::InputActionMessage::InputActionMessage()
{
}

//------------------------------------------------------------------------------------------------
inline egmToolServices::InputActionMessage::~InputActionMessage()
{
}

//------------------------------------------------------------------------------------------------
inline void egmToolServices::InputActionMessage::SetName(const efd::utf8string& value)
{
    m_name = value;
}

//------------------------------------------------------------------------------------------------
inline const efd::utf8string& egmToolServices::InputActionMessage::GetName() const
{
    return m_name;
}

//------------------------------------------------------------------------------------------------
inline void egmToolServices::InputActionMessage::SetActive(efd::Bool value)
{
    m_active = value;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool egmToolServices::InputActionMessage::GetActive() const
{
    return m_active;
}

//------------------------------------------------------------------------------------------------
// SourcePaintDataMessage
//------------------------------------------------------------------------------------------------
inline egmToolServices::SourcePaintDataMessage::SourcePaintDataMessage()
{
    
}
//------------------------------------------------------------------------------------------------
inline efd::UInt32 egmToolServices::SourcePaintDataMessage::GetX() const
{
    return m_x;
}
//------------------------------------------------------------------------------------------------
inline efd::UInt32 egmToolServices::SourcePaintDataMessage::GetY() const
{
    return m_y;
}
//------------------------------------------------------------------------------------------------
inline efd::UInt32 egmToolServices::SourcePaintDataMessage::GetWidthInPixels() const
{
    return m_width;
}
//------------------------------------------------------------------------------------------------
inline efd::UInt32 egmToolServices::SourcePaintDataMessage::GetHeightInPixels() const
{
    return m_height;
}

//------------------------------------------------------------------------------------------------
inline const efd::Point2& egmToolServices::SourcePaintDataMessage::GetCenter() const
{
    return m_center;
}

//------------------------------------------------------------------------------------------------
inline const efd::Point2& egmToolServices::SourcePaintDataMessage::GetDimensions() const
{
    return m_dimensions;
}

//------------------------------------------------------------------------------------------------
// TerrainAssetMigrationRequestMessage
//------------------------------------------------------------------------------------------------
inline egmToolServices::TerrainAssetMigrationRequestMessage::TerrainAssetMigrationRequestMessage():
    m_entityId(0)
{
}

//------------------------------------------------------------------------------------------------
inline egmToolServices::TerrainAssetMigrationRequestMessage::~TerrainAssetMigrationRequestMessage()
{
}

//------------------------------------------------------------------------------------------------
inline efd::ID128 egmToolServices::TerrainAssetMigrationRequestMessage::GetEntityId() const
{
    return m_entityId;
}

//------------------------------------------------------------------------------------------------
inline const efd::utf8string& egmToolServices::TerrainAssetMigrationRequestMessage::GetAssetId() 
    const
{
    return m_assetId;
}

//------------------------------------------------------------------------------------------------
inline const efd::utf8string& egmToolServices::TerrainAssetMigrationRequestMessage::GetAssetPath() 
    const
{
    return m_assetPath;
}

//------------------------------------------------------------------------------------------------
