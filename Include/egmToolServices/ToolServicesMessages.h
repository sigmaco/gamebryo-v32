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

#pragma once
#ifndef EE_EGMTOOLSERVICESMESSAGES_H
#define EE_EGMTOOLSERVICESMESSAGES_H

#include "egmToolServicesLibType.h"
#include "egmToolServicesMessageIDs.h"

#include <efd/IDs.h>
#include <efd/IMessage.h>
#include <efd/StreamMessage.h>
#include <egf/IProperty.h>
#include <egf/Entity.h>

#include <NiTerrainDeformationBuffer.h>

namespace egmToolServices
{

/// @name MessageWrappers from ToolServicesMessages.h
//@{
typedef efd::MessageWrapper
    <efd::StreamMessage, egmToolServices::kMSGID_ToolVisibilityChanged>
    ToolVisibilityRequest;

typedef efd::MessageWrapper
    <efd::StreamMessage, egmToolServices::kMSGID_ToolSelectabilityChanged>
    ToolSelectabilityRequest;

typedef efd::MessageWrapper
    <efd::IMessage, egmToolServices::kMSGID_TerrainPaintingBeginMessage>
    TerrainPaintingBeginMessageType;

typedef efd::MessageWrapper
    <efd::IMessage, egmToolServices::kMSGID_TerrainPaintingEndMessage>
    TerrainPaintingEndMessageType;
//@}

class EE_EGMTOOLSERVICES_ENTRY ToolMessagesConstants
{
public:
    static const efd::Category ms_fromFrameworkCategory;
    static const efd::Category ms_fromExternalFrameworkCategory;
};

class EE_EGMTOOLSERVICES_ENTRY SelectEntitiesMessage : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(SelectEntitiesMessage, kMSGID_SelectEntitiesMessage, efd::IMessage);
    /// @endcond

public:
    static efd::IMessagePtr FactoryMethod();

    SelectEntitiesMessage() { }
    virtual ~SelectEntitiesMessage() { }

    efd::list< efd::ID128 >* GetAddedEntities()
    {
        return &m_addedEntities;
    }

    const efd::list< efd::ID128 >* GetAddedEntities() const
    {
        return &m_addedEntities;
    }

    efd::list< efd::ID128 >* GetRemovedEntities()
    {
        return &m_removedEntities;
    }

    const efd::list< efd::ID128 >* GetRemovedEntities() const
    {
        return &m_removedEntities;
    }

    const bool GetSelectionCleared()  const
    {
        return m_selectionCleared;
    }

    void SetSelectionCleared(bool cleared)
    {
        m_selectionCleared = cleared;
    }

protected:
    efd::list< efd::ID128 > m_addedEntities;
    efd::list< efd::ID128 > m_removedEntities;
    bool m_selectionCleared;
};
typedef efd::SmartPointer<SelectEntitiesMessage> SelectEntitiesMessagePtr;



/**
    This message is used when the World Builder tool creates a new entity in the
    world.
*/
class EE_EGMTOOLSERVICES_ENTRY AddEntityMessage : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(AddEntityMessage, kMSGID_AddEntityMessage, efd::IMessage);
    /// @endcond

public:
    static efd::IMessagePtr FactoryMethod();

public:
    AddEntityMessage();
    virtual ~AddEntityMessage();

    class OverrideEntry
    {
        EE_DECLARE_CONCRETE_REFCOUNT;

    public:
        OverrideEntry();
        ~OverrideEntry();
        void Serialize(efd::Archive& ar);

        efd::utf8string PropertyName;
        efd::utf8string PropertyValue;
        efd::utf8string* Key;
    };
    typedef efd::SmartPointer<OverrideEntry> OverrideEntryPtr;

    virtual void Serialize(efd::Archive& ar);

    void SetEntityId(const efd::ID128& value);

    const efd::ID128& GetEntityId() const;

    void SetModelName(const efd::utf8string& value);
    const efd::utf8string& GetModelName() const;

    inline efd::list<OverrideEntryPtr>* GetOverrides();
    inline const efd::list<OverrideEntryPtr>* GetOverrides() const;

    inline void AddOverride(
        const efd::utf8string& pPropName,
        const efd::utf8string& pPropValue,
        const efd::utf8string* key);

protected:
    efd::ID128 m_entityId;
    efd::utf8string m_modelName;

    efd::list<OverrideEntryPtr> m_overrides;
};
typedef efd::SmartPointer<AddEntityMessage> AddEntityMessagePtr;

/**
    This message is used by the World Builder tool when an entity is removed from the world.
*/
class EE_EGMTOOLSERVICES_ENTRY RemoveEntityMessage : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(RemoveEntityMessage, kMSGID_RemoveEntityMessage, efd::IMessage);
    /// @endcond

public:
    static efd::IMessagePtr FactoryMethod();

public:
    RemoveEntityMessage();
    virtual ~RemoveEntityMessage();

    virtual void Serialize(efd::Archive& ar);

    void SetEntityId(efd::ID128 value);

    efd::ID128 GetEntityId() const;

protected:
    efd::ID128 m_entityId;
};
typedef efd::SmartPointer<RemoveEntityMessage> RemoveEntityMessagePtr;


/**
    This message is used by the World Builder tool when a property has changed on an entity.
    The C++ run-time entity property is then updated to reflect the change.
*/
class EE_EGMTOOLSERVICES_ENTRY SetEntityPropertyMessage : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(
        SetEntityPropertyMessage,
        kMSGID_SetEntityPropertyMessage,
        efd::IMessage);
    /// @endcond

public:
    static efd::IMessagePtr FactoryMethod();

public:
    inline SetEntityPropertyMessage();
    inline virtual ~SetEntityPropertyMessage();

    virtual void Serialize(efd::Archive& ar);

    inline void SetEntityId(efd::ID128 value);

    inline efd::ID128 GetEntityId() const;

    inline void SetPropertyName(efd::utf8string value);

    inline efd::utf8string GetPropertyName() const;

    inline void SetPropertyValue(efd::utf8string value);

    inline efd::utf8string GetPropertyValue() const;

protected:
    efd::ID128 m_entityId;
    efd::utf8string m_propertyName;
    efd::utf8string m_propertyValue;
};

typedef efd::SmartPointer<SetEntityPropertyMessage> SetEntityPropertyMessagePtr;


/**
    This message is used when several properties on several entities need updating. By
    packing multiple property change messages together, the message bandwidth and
    general number of messages are dramatically reduced resulting in better performance.
*/
class EE_EGMTOOLSERVICES_ENTRY SetEntitiesPropertiesMessage : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(
        SetEntitiesPropertiesMessage,
        kMSGID_SetEntitiesPropertiesMessage,
        efd::IMessage);
    /// @endcond

public:
    static efd::IMessagePtr FactoryMethod();

public:
    class OverrideEntry
    {
        EE_DECLARE_CONCRETE_REFCOUNT;

    public:
        OverrideEntry();
        virtual ~OverrideEntry();

        void Serialize(efd::Archive& ar);

        efd::ID128 Entityid;
        efd::utf8string PropertyName;
        efd::utf8string PropertyValue;
        efd::utf8string* Key;
    };
    typedef efd::SmartPointer<OverrideEntry> OverrideEntryPtr;

    inline SetEntitiesPropertiesMessage();
    inline virtual ~SetEntitiesPropertiesMessage();

    virtual void Serialize(efd::Archive& ar);

    inline efd::list<OverrideEntryPtr>* GetChanges();
    inline const efd::list<OverrideEntryPtr>* GetChanges() const;

    inline void AddEntry(
        efd::ID128 entityId,
        efd::utf8string propName,
        efd::utf8string propValue,
        const efd::utf8string* pKey = NULL);

protected:
    efd::list<OverrideEntryPtr> m_overrides;
};
typedef efd::SmartPointer<SetEntitiesPropertiesMessage> SetEntitiesPropertiesMessagePtr;


/**
    This message is used when the transformation mode changes in World Builder. The transformation
    mode is either in world space or local space to the entity being transformed.
*/
class EE_EGMTOOLSERVICES_ENTRY SetGizmoBasisMessage : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(SetGizmoBasisMessage, kMSGID_SetGizmoBasisMessage, efd::IMessage);
    /// @endcond

public:
    static efd::IMessagePtr FactoryMethod();

public:
    inline SetGizmoBasisMessage();
    inline virtual ~SetGizmoBasisMessage();

    virtual void Serialize(efd::Archive& ar);

    inline void SetRelativeSpace(efd::UInt16 value);

    inline efd::UInt16 GetRelativeSpace() const;

protected:
    efd::UInt16 m_relativeSpace;
};

typedef efd::SmartPointer<SetGizmoBasisMessage> SetGizmoBasisMessagePtr;

/**
    This message is sent when a clone transaction is about to occur.
*/
class EE_EGMTOOLSERVICES_ENTRY BeginCloneEntityMessage : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(BeginCloneEntityMessage, kMSGID_BeginCloneEntityMessage, efd::IMessage);
    /// @endcond

public:
    static efd::IMessagePtr FactoryMethod();

public:
    inline BeginCloneEntityMessage();
    inline virtual ~BeginCloneEntityMessage();
};

typedef efd::SmartPointer<BeginCloneEntityMessage> BeginCloneEntityMessagePtr;

/**
    This method is called when application settings are changed in the World Builder tool.
*/
class EE_EGMTOOLSERVICES_ENTRY SettingsUpdateMessage : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(SettingsUpdateMessage, kMSGID_SettingsUpdateMessage, efd::IMessage);
    /// @endcond

public:
    static efd::IMessagePtr FactoryMethod();

public:
    inline SettingsUpdateMessage();
    inline virtual ~SettingsUpdateMessage();

    virtual void Serialize(efd::Archive& ar);

    inline void SetSettingName(efd::utf8string value);

    inline efd::utf8string GetSettingName() const;

    inline void SetSettingValue(efd::utf8string value);

    inline efd::utf8string GetSettingValue() const;

protected:
    efd::utf8string m_settingName;
    efd::utf8string m_settingValue;
};

typedef efd::SmartPointer<SettingsUpdateMessage> SettingsUpdateMessagePtr;


/**
    This method is called when the active camera is changed on a given viewport. The active
    camera may be one of several orthographic cameras, scene cameras, or the generic
    perspective camera.
*/
class EE_EGMTOOLSERVICES_ENTRY SetActiveCameraMessage : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(SetActiveCameraMessage, kMSGID_CameraChanged, efd::IMessage);
    /// @endcond

public:
    static efd::IMessagePtr FactoryMethod();

    inline SetActiveCameraMessage();
    inline virtual ~SetActiveCameraMessage();

    virtual void Serialize(efd::Archive& ar);

    inline void SetWindow(efd::UInt64 value);

    inline efd::UInt64 GetWindow() const;

    inline void SetCameraName(efd::utf8string value);

    inline efd::utf8string GetCameraName() const;

protected:
    efd::UInt64 m_window;
    efd::utf8string m_cameraName;
};

typedef efd::SmartPointer<SetActiveCameraMessage> SetActiveCameraMessagePtr;


/**
    This message is sent when the current active camera location or orientation changes.
*/
class EE_EGMTOOLSERVICES_ENTRY CameraUpdateMessage : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(CameraUpdateMessage, kMSGID_CameraUpdateMessage, efd::IMessage);
    /// @endcond

public:
    static efd::IMessagePtr FactoryMethod();

public:
    inline CameraUpdateMessage();
    inline virtual ~CameraUpdateMessage();

    virtual void Serialize(efd::Archive& ar);

    void SetWindowHandle(efd::WindowRef windowRef);
    efd::WindowRef GetWindowHandle() const;

    inline efd::map<efd::utf8string, efd::utf8string>& GetChanges();
    inline const efd::map<efd::utf8string, efd::utf8string>& GetChanges() const;

    inline void AddChange(efd::utf8string propName, efd::utf8string propValue);

protected:
    efd::WindowRef m_windowRef;
    efd::map<efd::utf8string, efd::utf8string> m_changes;
};

typedef efd::SmartPointer<CameraUpdateMessage> CameraUpdateMessagePtr;


/**
    This message is called when a new entity is created in World Builder.
*/
class EE_EGMTOOLSERVICES_ENTRY CreateEntityMessage : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(CreateEntityMessage, kMSGID_CreateEntityMessage, efd::IMessage);
    /// @endcond

public:
    static efd::IMessagePtr FactoryMethod();

public:
    inline CreateEntityMessage();
    inline virtual ~CreateEntityMessage();

    inline void SetModelName(const efd::utf8string& value);
    inline const efd::utf8string& GetModelName() const;

    inline void SetPosition(const efd::Point3& value);
    inline const efd::Point3& GetPosition() const;

    inline void SetRotation(const efd::Point3& value);
    inline const efd::Point3& GetRotation() const;

    virtual void Serialize(efd::Archive& ar);

protected:
    efd::utf8string m_modelName;
    efd::Point3 m_position;
    efd::Point3 m_rotation;
};

typedef efd::SmartPointer<CreateEntityMessage> CreateEntityMessagePtr;


/**
    This message is used when World Builder performs various actions based on user input.
    For example, when the user presses a certain key, the action "MoveForward" would be sent using
    this message.
*/
class EE_EGMTOOLSERVICES_ENTRY InputActionMessage : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(InputActionMessage, kMSGID_InputActionMessage, efd::IMessage);
    /// @endcond

public:
    static efd::IMessagePtr FactoryMethod();

public:
    inline InputActionMessage();
    inline virtual ~InputActionMessage();

    virtual void Serialize(efd::Archive& ar);

    inline void SetName(const efd::utf8string& value);
    inline const efd::utf8string& GetName() const;

    inline void SetActive(efd::Bool value);
    inline efd::Bool GetActive() const;

protected:
    efd::utf8string m_name;
    efd::Bool m_active;
};

typedef efd::SmartPointer<InputActionMessage> InputActionMessagePtr;

/**
    This message is used when worldbuilder performs an action that should modify a terrain. 
    For example any time a user paints on the terrain.
*/
class EE_EGMTOOLSERVICES_ENTRY SourcePaintDataMessage : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(SourcePaintDataMessage, kMSGID_SourcePaintDataMessage, efd::IMessage);
    /// @endcond

public:

    /// @name Construction and Destruction
    // @{

    /**
        Default Constructor
    */
    inline SourcePaintDataMessage();
    
    /**
        Initialization constructor.

        @param x Sets the paint stroke's center point's x coordinate for the painting action.
        @param y Sets the paint stroke's center point's x coordinate for the painting action.
        @param width Sets the extent the paint stroke's is affecting following the x axis.
        @param height Sets the extent the paint stroke's is affecting following the y axis.
        @param center The center of the paint stroke in terrain space coordinates.
        @param dimensions The dimensions of the paint stroke in terrain space coordinates.
    */
    SourcePaintDataMessage(efd::UInt32 x, efd::UInt32 y, 
        efd::UInt32 width, efd::UInt32 height, efd::Point2 center, efd::Point2 dimensions);

    /**
        Virtual destructor.
    */
    virtual ~SourcePaintDataMessage();
    //@}

    /**
        Helper function to create a SourcePaintDataMessage object.
    */
    static efd::IBasePtr FactoryMethod();
    
    virtual void Serialize(efd::Archive& ar);

    /*
        Returns the center of the paint stroke in terrain space coordinates.
    */
    inline const efd::Point2& GetCenter() const;

    /*
        Returns the dimensions of the paint stroke in terrain space coordinates.
    */
    inline const efd::Point2& GetDimensions() const;

    /**
        Returns the paint stroke's center point's x coordinate.
    */
    inline efd::UInt32 GetX() const;

    /**
        Returns the paint stroke's center point's y coordinate.
    */
    inline efd::UInt32 GetY() const;

    /**
        Returns the extent the paint stroke's is affecting following the x axis.
    */
    inline efd::UInt32 GetWidthInPixels() const;

    /**
        Returns the extent the paint stroke's is affecting following the y axis.
    */
    inline efd::UInt32 GetHeightInPixels() const;

protected:
    efd::Point2 m_center;
    efd::Point2 m_dimensions;

    efd::UInt32 m_x;
    efd::UInt32 m_y;
    efd::UInt32 m_width;
    efd::UInt32 m_height;
};

/// Defines a smart pointer (reference counted) for the SourcePaintDataMessage class
typedef efd::SmartPointer<SourcePaintDataMessage> SourcePaintDataMessagePtr;

/**
    This message type is used for triggering a migration of a terrain asset in the UI
*/
class EE_EGMTOOLSERVICES_ENTRY TerrainAssetMigrationRequestMessage : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(TerrainAssetMigrationRequestMessage, 
        kMSGID_TerrainAssetMigrationRequest, efd::IMessage);
    /// @endcond

public:

    /// @name Construction and Destruction
    //@{
    /// Default Constructor.
    inline TerrainAssetMigrationRequestMessage();
    TerrainAssetMigrationRequestMessage(const efd::ID128& entityId, const efd::utf8string& assetId, 
        const efd::utf8string& assetPath);

    /// Virtual Destructor.
    virtual ~TerrainAssetMigrationRequestMessage();
    //@}

    /// @name Fetch the properties
    // @{
    /**
        Returns the ID of the entity to migrate.
    */
    inline efd::ID128 GetEntityId() const;

    /**
        Returns the ID of the asset to use for migration.
    */
    inline const efd::utf8string& GetAssetId() const;

    /**
        Returns the ID of the asset's path
    */
    inline const efd::utf8string& GetAssetPath() const;
    // @}

    /// Factory method to create this message.
    static efd::IMessagePtr FactoryMethod();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::ClassID GetClassID() const;
    virtual void Serialize(efd::Archive& ar);

private:
    efd::ID128 m_entityId;
    efd::utf8string m_assetId;
    efd::utf8string m_assetPath;
};

/// Defines a smart pointer (reference counted) for the TerrainAssetMigrationRequestMessage class
typedef efd::SmartPointer<TerrainAssetMigrationRequestMessage> 
    TerrainAssetMigrationRequestMessagePtr;

}; // namespace

#include "ToolServicesMessages.inl"

#endif //EE_EGMTOOLSERVICESMESSAGES_H
