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
#ifndef EE_SIMDEBUGGERMESSAGES_H
#define EE_SIMDEBUGGERMESSAGES_H

#include <efd/IMessage.h>
#include <egf/egfBaseIDs.h>
#include <egf/egfLibType.h>
#include <egf/egfMessageIDs.h>
#include <egf/EntityID.h>

namespace egf
{

/**
    Base class for notification messages that alert Toolbench to game events.
 */
class EE_EGF_ENTRY DebugNoteBase : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(
        DebugNoteBase,
        efd::kMSGID_DebugNoteBase,
        efd::IMessage);
    /// @endcond

protected:
    /// @name Construction and Destruction
    //@{

    /// Default constructor.
    DebugNoteBase();

    /**
        Constructs a new DebugNoteBase message.

        @param gameID A 64-bit run-time entity ID associated with the event.
    */
    DebugNoteBase(egf::EntityID gameID);

public:
    /// Cleans up any resources.
    virtual ~DebugNoteBase();

    //@}

    /// Converts this class into a stream of atomic types.
    virtual void Serialize(efd::Archive& io_ar);

    /// @name Getters and Setters
    //@{

    /// Gets the timestamp for the sim event.
    efd::Float64 GetTimestamp() const;

    /// Sets the timestamp for the sim event.
    void SetTimestamp(efd::Float64 timestamp);

    /// Gets the run-time entity ID associated with the event.
    egf::EntityID GetGameID() const;

    //@}

private:
    efd::Float64 m_timestamp;
    egf::EntityID m_gameID;
};

/// A SmartPointer for the DebugNoteBase class.
typedef efd::SmartPointer<DebugNoteBase> DebugNoteBasePtr;


/**
    Generic notification message that alerts Toolbench to game events using string-based payloads.
 */
class EE_EGF_ENTRY DebugNoteEvent : public egf::DebugNoteBase
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(
        DebugNoteEvent,
        efd::kMSGID_DebugNoteEvent,
        egf::DebugNoteBase);
    /// @endcond

public:
    /// @name Construction and Destruction
    //@{

    /// Default constructor.
    DebugNoteEvent();

    /**
        Constructs a new DebugNoteEvent message.

        @param gameID A 64-bit run-time entity ID associated with the event.
        @param eventName The name of the event being reported.
        @param params Custom parameters for the particular event type.
    */
    DebugNoteEvent(
        egf::EntityID gameID,
        const efd::utf8string& eventName,
        const efd::utf8string& params);

    /// Cleans up any resources.
    virtual ~DebugNoteEvent();

    //@}

    /// Converts this class into a stream of atomic types.
    virtual void Serialize(efd::Archive& io_ar);

    /// @name Getters and Setters
    //@{

    /// Gets the name of the event being reported.
    const efd::utf8string& GetEventName() const;

    /// Gets the custom parameters for the particular event type.
    const efd::utf8string& GetParams() const;

    //@}

private:
    efd::utf8string m_eventName;
    efd::utf8string m_params;
};

/// A SmartPointer for the DebugNoteEvent class.
typedef efd::SmartPointer<DebugNoteEvent> DebugNoteEventPtr;


/**
    Notification message that kicks off a fresh Toolbench Sim Debugger session.
 */
class EE_EGF_ENTRY DebugNoteSessionStarted : public egf::DebugNoteBase
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(
        DebugNoteSessionStarted,
        efd::kMSGID_DebugNoteSessionStarted,
        egf::DebugNoteBase);
    /// @endcond

public:
    /// @name Construction and Destruction
    //@{

    /// Default constructor.
    DebugNoteSessionStarted();

    /// Cleans up any resources.
    virtual ~DebugNoteSessionStarted();

    //@}
};

/// A SmartPointer for the DebugNoteSessionStarted class.
typedef efd::SmartPointer<DebugNoteSessionStarted> DebugNoteSessionStartedPtr;


/**
    Notification message that defines a flat model for the Toolbench Sim Debugger.
 */
class EE_EGF_ENTRY DebugNoteFlatModelDefined : public egf::DebugNoteBase
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(
        DebugNoteFlatModelDefined,
        efd::kMSGID_DebugNoteFlatModelDefined,
        egf::DebugNoteBase);
    /// @endcond

public:
    /// @name Construction and Destruction
    //@{

    /// Default constructor.
    DebugNoteFlatModelDefined();

    /**
        Constructs a new DebugNoteFlatModelDefined message.

        @param modelName The name of the flat model being defined.
    */
    DebugNoteFlatModelDefined(const efd::utf8string& modelName);

    /// Cleans up any resources.
    virtual ~DebugNoteFlatModelDefined();

    //@}

    /// Converts this class into a stream of atomic types.
    virtual void Serialize(efd::Archive& io_ar);

    /// @name Getters and Setters
    //@{

    /// Gets the name of the flat model being defined.
    const efd::utf8string& GetModelName() const;

    /// Gets a value indicating whether the flat model mixes in Mesh.
    efd::Bool IsMesh() const;

    /// Specifies that the flat model mixes in Mesh.
    void SetIsMesh();

    /// Gets a value indicating whether the flat model mixes in Actor.
    efd::Bool IsActor() const;

    /// Specifies that the flat model mixes in Actor.
    void SetIsActor();

    /// Gets the number of properties in the flat model.
    efd::UInt32 GetPropertyCount() const;

    /// Gets the name of the specified property.
    const efd::utf8string& GetPropertyName(efd::UInt32 index) const;

    /// Gets the value of the specified property as a string.
    const efd::utf8string& GetPropertyValue(efd::UInt32 index) const;

    /// Adds a flat model property, including its value as a string.
    void AddProperty(const efd::utf8string& name, const efd::utf8string& value);

    //@}

private:
    efd::utf8string m_modelName;
    efd::Bool m_isMesh;
    efd::Bool m_isActor;
    efd::vector<EE_STL_NAMESPACE::pair<efd::utf8string, efd::utf8string> > m_properties;
};

/// A SmartPointer for the DebugNoteFlatModelDefined class.
typedef efd::SmartPointer<DebugNoteFlatModelDefined> DebugNoteFlatModelDefinedPtr;


/**
    Notification message that alerts the Toolbench Sim Debugger that an entity has been created.
 */
class EE_EGF_ENTRY DebugNoteEntityCreated : public egf::DebugNoteBase
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(
        DebugNoteEntityCreated,
        efd::kMSGID_DebugNoteEntityCreated,
        egf::DebugNoteBase);
    /// @endcond

public:
    /// @name Construction and Destruction
    //@{

    /// Default constructor.
    DebugNoteEntityCreated();

    /**
        Constructs a new DebugNoteEntityCreated message.

        @param gameID The 64-bit run-time entity ID for the new entity.
        @param toolID The 128-bit tool-time ID, if the entity was generated from a data file.
        @param modelName The name of the entity model used to create the new entity.
        @param position The initial position of the new entity.
        @param facing The initial facing angle of the new entity.
    */
    DebugNoteEntityCreated(
        egf::EntityID gameID,
        const efd::ID128& toolID,
        const efd::utf8string& modelName,
        const efd::Point3& position,
        efd::Float32 facing);

    /// Cleans up any resources.
    virtual ~DebugNoteEntityCreated();

    //@}

    /// Converts this class into a stream of atomic types.
    virtual void Serialize(efd::Archive& io_ar);

    /// @name Getters and Setters
    //@{

    /// Gets the tool-time ID, if the entity was generated from a data file.
    const efd::ID128& GetToolID() const;

    /// Gets the name of the entity model used to create the new entity.
    const efd::utf8string& GetModelName() const;

    /// Gets the initial position of the new entity.
    const efd::Point3& GetPosition() const;

    /// Gets the initial facing angle of the new entity.
    efd::Float32 GetFacingAngle() const;

    /// Gets the number of overridden properties on the entity.
    efd::UInt32 GetPropertyCount() const;

    /// Gets the name of the specified property.
    const efd::utf8string& GetPropertyName(efd::UInt32 index) const;

    /// Gets the value of the specified property as a string.
    const efd::utf8string& GetPropertyValue(efd::UInt32 index) const;

    /// Adds an overridden property on the entity, including its value as a string.
    void AddProperty(const efd::utf8string& name, const efd::utf8string& value);

    //@}

private:
    efd::ID128 m_toolID;
    efd::utf8string m_modelName;
    efd::Point3 m_position;
    efd::Float32 m_facing;
    efd::vector<EE_STL_NAMESPACE::pair<efd::utf8string, efd::utf8string> > m_properties;
};

/// A SmartPointer for the DebugNoteEntityCreated class.
typedef efd::SmartPointer<DebugNoteEntityCreated> DebugNoteEntityCreatedPtr;


/**
    Notification message that alerts the Toolbench Sim Debugger that an entity has been destroyed.
 */
class EE_EGF_ENTRY DebugNoteEntityDestroyed : public egf::DebugNoteBase
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(
        DebugNoteEntityDestroyed,
        efd::kMSGID_DebugNoteEntityDestroyed,
        egf::DebugNoteBase);
    /// @endcond

public:
    /// @name Construction and Destruction
    //@{

    /// Default constructor.
    DebugNoteEntityDestroyed();

    /**
        Constructs a new DebugNoteEntityDestroyed message.

        @param gameID The 64-bit run-time entity ID for the destroyed entity.
    */
    DebugNoteEntityDestroyed(egf::EntityID gameID);

    /// Cleans up any resources.
    virtual ~DebugNoteEntityDestroyed();

    //@}
};

/// A SmartPointer for the DebugNoteEntityDestroyed class.
typedef efd::SmartPointer<DebugNoteEntityDestroyed> DebugNoteEntityDestroyedPtr;


/**
    Notification message that alerts the Toolbench Sim Debugger that an entity property has been
    changed.
 */
class EE_EGF_ENTRY DebugNotePropertyChanged : public egf::DebugNoteBase
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(
        DebugNotePropertyChanged,
        efd::kMSGID_DebugNotePropertyChanged,
        egf::DebugNoteBase);
    /// @endcond

public:
    /// @name Construction and Destruction
    //@{

    /// Default constructor.
    DebugNotePropertyChanged();

    /**
        Constructs a new DebugNotePropertyChanged message.

        @param gameID The 64-bit run-time entity ID for the entity.
        @param propertyName The name of the entity property that has changed.
        @param propertyValue The new value of the entity property as a string.
    */
    DebugNotePropertyChanged(
        egf::EntityID gameID,
        const efd::utf8string& propertyName,
        const efd::utf8string& propertyValue);

    /// Cleans up any resources.
    virtual ~DebugNotePropertyChanged();

    //@}

    /// Converts this class into a stream of atomic types.
    virtual void Serialize(efd::Archive& io_ar);

    /// @name Getters and Setters
    //@{

    /// Gets the name of the entity property that has changed.
    const efd::utf8string& GetPropertyName() const;

    /// Gets the new value of the entity property as a string.
    const efd::utf8string& GetPropertyValue() const;

    //@}

private:
    efd::utf8string m_propertyName;
    efd::utf8string m_propertyValue;
};

/// A SmartPointer for the DebugNotePropertyChanged class.
typedef efd::SmartPointer<DebugNotePropertyChanged> DebugNotePropertyChangedPtr;


/**
    Notification message that alerts the Toolbench Sim Debugger that an entity collection property
    has been changed.
 */
class EE_EGF_ENTRY DebugNoteCollectionPropertyChanged : public egf::DebugNoteBase
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(
        DebugNoteCollectionPropertyChanged,
        efd::kMSGID_DebugNoteCollectionPropertyChanged,
        egf::DebugNoteBase);
    /// @endcond

public:
    /// @name Construction and Destruction
    //@{

    /// Default constructor.
    DebugNoteCollectionPropertyChanged();

    /**
        Constructs a new DebugNoteCollectionPropertyChanged message.

        @param gameID The 64-bit run-time entity ID for the entity.
        @param propertyName The name of the entity property that has changed.
    */
    DebugNoteCollectionPropertyChanged(
        egf::EntityID gameID,
        const efd::utf8string& propertyName);

    /// Cleans up any resources.
    virtual ~DebugNoteCollectionPropertyChanged();

    //@}

    /// Converts this class into a stream of atomic types.
    virtual void Serialize(efd::Archive& io_ar);

    /// @name Getters and Setters
    //@{

    /// Gets the name of the entity property that has changed.
    const efd::utf8string& GetPropertyName() const;

    /// Gets the number of key/value pairs in the collection property.
    efd::UInt32 GetItemCount() const;

    /// Gets the key of the specified collection property item.
    const efd::utf8string& GetItemKey(efd::UInt32 index) const;

    /// Gets the value of the specified collection property item as a string.
    const efd::utf8string& GetItemValue(efd::UInt32 index) const;

    /// Adds a key/value pair collection property item to the change record.
    void AddItem(const efd::utf8string& key, const efd::utf8string& value);

    //@}

private:
    efd::utf8string m_propertyName;
    efd::vector<EE_STL_NAMESPACE::pair<efd::utf8string, efd::utf8string> > m_items;
};

/// A SmartPointer for the DebugNoteCollectionPropertyChanged class.
typedef efd::SmartPointer<DebugNoteCollectionPropertyChanged> DebugNoteCollectionPropertyChangedPtr;

}

#include <egf/SimDebuggerMessages.inl>

#endif
