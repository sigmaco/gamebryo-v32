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
#ifndef EE_BLOCKLOADPARAMETERS_H
#define EE_BLOCKLOADPARAMETERS_H

#include <egf/egfLibType.h>
#include <egf/egfClassIDs.h>
#include <efd/AssetID.h>
#include <efd/Category.h>
#include <efd/Point3.h>
#include <egf/EntityTypes.h>

namespace egf
{

/**
    Configuration parameters for the loading of a block.
*/
class EE_EGF_ENTRY BlockLoadParameters : public efd::MemObject
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS(BlockLoadParameters, efd::kCLASSID_BlockLoadParameters);
    /// @endcond

public:
    /// Default constructor. Default settings are no callback, using GetDefaultAutoEnterWorld() to
    /// set auto enter and default throttle limits.
    BlockLoadParameters();

    /// Convenience constructor for the common case of loading a block with just a message-based
    /// callback and otherwise default parameters.
    BlockLoadParameters(const efd::Category& cat);

    /// Virtual destructor
    virtual ~BlockLoadParameters();

    /**
        Control whether entities created from loading this block should automatically enter the
        world once created. If not set, the value of GetDefaultAutoEnterWorld() at the time this
        class was created will be used.
    */
    inline void SetAutoEnterWorld(bool autoEnter);

    /**
        Request status callbacks via messages. Multiple egf::EntityLoadResult messages will be sent
        to the given category to inform the callback of the loading and eventual unloading progress
        of the block.

        @note Setting a message callback overrides any behavior callback.

        @param cat The category to which the messages are delivered.
        @param context An optional context that will be passed back to the callback in the
            EntityLoadResult message.
    */
    void SetMessageCallback(const efd::Category& cat, efd::UInt32 context = 0);

    /**
        Request status callbacks via a behavior invocation. Multiple behavior invocations will be
        sent to inform the callback of the loading and eventual unloading progress of the block.

        @note Setting a behavior callback overrides any message callback.

        @param cat The EntityID of a single entity or a Category to which one or more entities are
            subscribed for events.
        @param behavior The BehaviorID of the behavior to invoke on the target entity or entities.
        @param context An optional context that will be passed back to the behavior as a parameter
            named "Context".
    */
    void SetBehaviorCallback(efd::Category cat, egf::BehaviorID behavior, efd::UInt32 context = 0);

    /// Bitwise values which can be combined and passed to SetCallbackStyle.
    enum BlockLoadCallback
    {
        /// Send the elr_Loading callback to indicate partial progress.
        /// @note: This callback is not yet implemented.
        blc_Loading = 1<<0,
        /// Send the elr_Loaded callback when block parsing completes.
        blc_Loaded = 1<<1,
        /// Send the elr_AlreadyLoaded callback when requesting to load an already loaded block.
        blc_AlreadyLoaded = 1<<2,
        /// Send the elr_EntityCreationCompleted callback when block load is totally complete.
        blc_EntityCreationCompleted = 1<<3,
        /// Send the elr_LoadCancelSuccess callback when a block load is canceled before completion.
        blc_LoadCancelSuccess = 1<<4,
        /// Send the elr_Unloaded callback when the block is hidden due to an unload request.
        blc_Unloaded = 1<<5,
        /// Send the elr_EntityDestructionCompleted callback when all entities in an unloaded block
        /// complete their destruction.
        blc_EntityDestructionCompleted = 1<<6,

        /// Send the elr_Failed callback indicating an unknown failure.
        blc_Failed = 1<<31,
        /// Send the elr_RequestFailure callback. This status is never sent.
        blc_RequestFailure = 1<<30,
        /// Send the elr_EntitySetNotFound callback if internal data structures for this block can
        /// not be found at a time when they are expected to be available.
        blc_EntitySetNotFound = 1<<29,
        /// Send the elr_AssetIDNotFound callback if the block asset is not found.
        blc_AssetIDNotFound = 1<<28,
        /// Send the elr_ParseFailed callback if block parsing failure due to corrupt data.
        blc_ParseFailed = 1<<27,

        /// All possible success values from a load attempt.
        blc_AnyLoadSuccess = blc_Loading | blc_Loaded | blc_AlreadyLoaded |
            blc_EntityCreationCompleted,

        /// All possible success values from an unload attempt.
        blc_AnyUnloadSuccess = blc_LoadCancelSuccess | blc_Unloaded |
            blc_EntityDestructionCompleted,

        /// All of the failure values. It is recommended that these always be included.
        blc_AnyFailure = blc_Failed | blc_RequestFailure | blc_EntitySetNotFound |
            blc_AssetIDNotFound | blc_ParseFailed,

        /// If you want to receive exactly one callback this set of flags is your best bet. Any
        /// failure will be sent, otherwise you will get either an already loaded or final
        /// completion notification only.
        blc_AnyFinalLoad = blc_AnyFailure | blc_AlreadyLoaded | blc_EntityCreationCompleted,

        /// Default flags. By default all status values are sent to the callback.
        blc_Default = blc_AnyLoadSuccess | blc_AnyUnloadSuccess | blc_AnyFailure,
    };

    /**
        Control which types of callback notifications are sent to any provided callback. Pass in
        one or more BlockLoadCallback flags combined together.
    */
    void SetActiveCallbacks(efd::UInt32 style);

    /**
        Apply a rotation about the origin that will adjust the "Position" and "Rotation" properties
        of all "Positionable" entities created when the block is loaded. Only those specific
        properties for entities that mix-in that specific model are effected. This change will be
        applied to each entity after initial allocation but before the OnCreate lifecycle. This is
        the same point in time at which block file property overrides are applied. If both a
        rotation and offset are applied, the block will first be rotated and then the offset will
        be applied to the result. The members of the rotation Point3 are degrees of rotation about
        each axis, which is the same form used by the "Rotation" property.

        @note The entire block is rotated about the origin. If you wish to apply rotations to a
            block it is recommended you implement the block such that the origin is at the center
            of the block.

        @param rotation The rotations about each axis in degrees.
    */
    void SetBlockRotation(const efd::Point3& rotation);

    /// Remove a previously set block rotation. By default no rotation is set and there is no need
    /// to call this, but it is useful when reusing the same BlockLoadParameter instance.
    void ClearBlockRotation();

    /**
        Apply a translation that will adjust the "Position" property of all "Positionable" entities
        created when the block is loaded. Only that specific property for entities that mix-in that
        specific model are effected. This change will be applied to each entity after initial
        allocation but before the OnCreate lifecycle. This is the same point in time at which block
        file property overrides are applied. If both a rotation and offset are applied, the block
        will first be rotated and then the offset will be applied to the result.

        @param offset The translation to apply to all entities in the block.
    */
    void SetBlockOffset(const efd::Point3& offset);

    /// Remove a previously set block offset. By default no offset is set and there is no need
    /// to call this, but it is useful when reusing the same BlockLoadParameter instance.
    void ClearBlockOffset();

    /// Special value for use with SetLoadThresholdOverride or SetUnloadThresholdOverride to
    /// indicate the default threshold limit.
    static const efd::UInt32 k_UseDefaultLimit = 0;
    /// Special value for use with SetLoadThresholdOverride or SetUnloadThresholdOverride to
    /// indicate no threshold limit.
    static const efd::UInt32 k_Unlimited = 0xFFFFFFFF;

    /**
        Set an override for the load throttle when loading this block. This can allow an important
        block to be loaded more quickly regardless of frame rate hitches or an unimportant block to
        be loaded more slowly.

        @note Interaction between this setting and the default setting in the EntityLoaderService
            is if fairly complicated:
        - If this setting is higher then the default EntityLoaderService value:
            When loading of this block begins the ELS will switch to using the higher value. Once
            this block finishes the ELS value will return to the default. If a previous block was
            loaded before your block the number of entities already loaded are counted against the
            new threshold. If additional block loads are queued they can proceed this tick only if
            the entities loaded this tick are below the resulting threshold.
        - If this setting is lower than the default EntityLoaderService value:
            When this block begins to load the lower limit will be considered. If a previous block
            has already loaded this tick the reduced limit could already be exceeded in which case
            loading of this block will be delayed until the next tick. After considering this block
            the normal limit will be restored and the next queued block load will be considered.
            Even if this block was skipped due to the limit the next block may still be loaded if
            it is under the restored limit.

        @param override The maximum number of entities to create each tick when loading this block.
            The special value k_Unlimited can be used to ensure the entire block is loaded in a
            single tick. The special value k_UseDefaultLimit will ensure that the default value
            specified by the EntityLoaderService is used.
    */
    void SetLoadThresholdOverride(efd::UInt32 override);

    /**
        Set an override for the unload throttle when unloading this block. This can allow a block
        to be unloaded more quickly. For example, if you know all entities in a block have no exit
        world or destruction behaviors you may wish to free up the memory consumed by the block
        more quickly than normal since it shouldn't generate much work.

        @note Interaction between this setting and the default setting in the EntityLoaderService
            is similar to that described in SetLoadThresholdOverride.

        @param override The maximum number of entities to destroy each tick when unloading this
            block. The special value k_Unlimited can be used to ensure the entire block is
            destroyed in a single tick. The special value k_UseDefaultLimit will ensure that the
            default value specified by the EntityLoaderService is used.
    */
    void SetUnloadThresholdOverride(efd::UInt32 override);

    /**
        Get the global default for whether entities should automatically enter the world when a
        block is loaded. By default the default is true to assist with migrations from previous
        versions of LightSpeed but it is recommended that the default be set to false.
    */
    inline static bool GetDefaultAutoEnterWorld();
    /**
        Set the global default for whether entities should automatically enter the world when a
        block is loaded. By default the default is true to assist with migrations from previous
        versions of LightSpeed but it is recommended that the default be set to false.
    */
    static void SetDefaultAutoEnterWorld(bool autoEnter);

    inline bool GetAutoEnterWorld() const;
    inline const efd::Category& GetNotificationCategory() const;
    inline efd::UInt32 GetNotificationContext() const;
    inline egf::BehaviorID GetNotificationBehavior() const;
    inline egf::BehaviorID GetActiveCallbacks() const;

    inline bool UseRotation() const;
    inline const efd::Point3& GetRotation() const;

    inline bool UseOffset() const;
    inline const efd::Point3& GetOffset() const;

    inline efd::UInt32 GetLoadThresholdOverride() const;
    inline efd::UInt32 GetUnloadThresholdOverride() const;

    /// Serialization method for this class
    virtual void Serialize(efd::Archive& io_ar);

protected:
    /// Default value for the auto-enter-world setting
    static bool ms_defaultAutoEnterWorld;

    /// @name Notification settings
    //@{
    /// Destination for sending either message or behavior callbacks
    efd::Category m_notificationCategory;
    /// User specified context value passed back to callbacks
    efd::UInt32 m_notificationContext;
    /// If a behavior callback is requested, this is the behavior ID. Otherwise this is zero and a
    /// message callback will be send instead.
    egf::BehaviorID m_notificationBehavior;

    /// Various BlockLoadCallback values indicating which notifications to send
    efd::UInt32 m_callbacks;
    //@}

    struct Flags
    {
        bool autoEnterWorld : 1;
        bool rotationSet : 1;
        bool offsetSet : 1;
    };

    union
    {
        efd::UInt8 m_flags;
        Flags m_bits;
    };

    efd::Point3 m_rotation;
    efd::Point3 m_offset;

    efd::UInt32 m_loadThrottleOverride;
    efd::UInt32 m_unloadThrottleOverride;
};

} // end namespace egf

#include <egf/BlockLoadParameters.inl>

#endif // EE_BLOCKLOADPARAMETERS_H
