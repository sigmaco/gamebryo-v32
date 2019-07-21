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
#ifndef EE_ENTITYLOADERMESSAGE_H
#define EE_ENTITYLOADERMESSAGE_H


#include <egf/egfLibType.h>
#include <efd/IMessage.h>
#include <efdNetwork/NetCategory.h>
#include <egf/egfMessageIDs.h>
#include <efd/AssetID.h>
#include <egf/EntityTypes.h>
#include <egf/Entity.h>
#include <egf/EntityID.h>
#include <egf/BlockIdentification.h>
#include <egf/BlockLoadParameters.h>


namespace egf
{

/// An arbitrary user provided value that is simply passed back to the user later.
// DT32393 Context needs to be 64bit on 64bit platforms.
typedef efd::UInt32 Context;


/**
    Message implementation for managing a block file. This message is sent to the
    EntityLoaderService to either load, unload, or reload a specific block. This can be used to
    load or unload a block in any process, to load a block in the current process a message send
    can be bypassed by directly calling EntityLoaderService::RequestEntitySetLoad.
*/
class EE_EGF_ENTRY EntityLoadRequest : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(EntityLoadRequest, efd::kMSGID_EntityLoadRequest, efd::IMessage);
    /// @endcond

public:

    /// Operation state enum. This describes the type of operation requested.
    enum Operation
    {
        /// An invalid operation type
        elo_Invalid,
        /// A request to load a block file
        elo_Load,
        /// A request to unload an already loaded block file
        elo_Unload,
        /// A request to cancel an in-progress load request
        elo_CancelLoad,
        /// A request to reload an already loaded block in response to a rapid iteration change
        elo_Reload
    };

    /// @name Construction and Destruction
    //@{
    /// default constructor
    EntityLoadRequest();

    /**
        Constructor for load requests. Creates an EntityLoadResult message with either the elo_Load
        or elo_Reload operation depending on the value of i_isReload. The BlockLoadParameters, if
        provided, are copied into the message.

        @param[in] i_blockID The AssetID to load.
        @param[in] i_pParameters The complete load parameters
        @param[in] i_isReload If true, perform an elo_Reload operation, otherwise use elo_load.
    */
    EntityLoadRequest(
        const BlockIdentification& i_blockID,
        const BlockLoadParameters* i_pParameters = NULL,
        bool i_isReload = false);

    /**
        Constructor for message based callbacks.  Results in a EntityLoadResult message based
        callback when this message is sent to the EntityLoaderService.

        @param[in] i_op Operation enum value.
        @param[in] i_blockID The AssetID to load.
        @param[in] i_cb The callback Category.
        @param[in] i_ctx The message context.
        @param[in] i_autoEnterWorld True if you want the entities to automatically enter the world.
            This will cause the entity set complete message to not be sent until after all of the
            OnEnterWorld behaviors have run.
    */
    EntityLoadRequest(
        Operation i_op,
        const BlockIdentification& i_blockID,
        efd::Category i_cb,
        Context i_ctx,
        bool i_autoEnterWorld = BlockLoadParameters::GetDefaultAutoEnterWorld());

    /**
        Constructor for behavior based callbacks.  Results in an entity behavior based callback
        when this message is sent to the EntityLoaderService.

        @param[in] i_op Operation enum value.
        @param[in] i_blockID The AssetID to load.
        @param[in] i_cbEntity The callback entity.
        @param[in] i_cbBehavior The callback behavior.
        @param[in] i_ctx The message context.
        @param[in] i_autoEnterWorld True if you want the entities to automatically enter the world.
            This will cause the entity set complete message to not be sent until after all of the
            OnEnterWorld behaviors have run.
    */
    EntityLoadRequest(
        Operation i_op,
        const BlockIdentification& i_blockID,
        efd::Category i_cbEntity,
        egf::BehaviorID i_cbBehavior,
        Context i_ctx,
        bool i_autoEnterWorld = BlockLoadParameters::GetDefaultAutoEnterWorld());

    /// default destructor
    virtual ~EntityLoadRequest();
    //@}

    /// convert this class into a stream of atomic types.
    virtual void Serialize(efd::Archive& ar);

    /// storage for Operation enum value
    Operation m_op;
    /// storage for block AssetID and instance
    BlockIdentification m_blockID;
    /// storage for other parameters
    BlockLoadParameters m_settings;
};

/// A smart pointer for the EntityLoadRequest class
typedef efd::SmartPointer<EntityLoadRequest> EntityLoadRequestPtr;


/**
    Message implementation for the return results from loading an Entity
*/
class EE_EGF_ENTRY EntityLoadResult : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(EntityLoadResult, efd::kMSGID_EntityLoadResult, efd::IMessage);
    /// @endcond

public:

    /// Enumeration of possible result values for egf::EntityLoaderService block loading and
    /// unloading methods.
    enum Result
    {
        /// An invalid value
        elr_Unknown = 0,

        /// Success values. All success values are greater than zero.
        //@{
        /// The entity set is currently being parsed and only a portion of the entities have
        /// finished being loaded.  Once all entities have been parsed, we will send a
        /// elr_Loaded message.
        elr_Loading,

        /// Entity set was loaded and parsed successfully. Creation of entities is in progress.
        /// This should eventually be followed by a elr_EntityCreationCompleted message.
        elr_Loaded,

        /// The requested block was already loaded so no further action was taken.
        elr_AlreadyLoaded,

        /// All entities in a loaded block have completed their entity creation life cycles
        elr_EntityCreationCompleted,

        /// A request to cancel the loading of a block has successfully prevented a pending or in
        /// progress block load.
        elr_LoadCancelSuccess,

        /// An unload request was valid and the destruction of entities from the block has begun.
        /// This message is normally followed by a elr_EntityDestructionCompleted message; however
        /// if no entities in the block have shutdown behaviors such as OnDestroy or OnExitWorld
        /// then this message can arrive after the elr_EntityDestructionCompleted message.
        elr_Unloaded,

        /// All entities in an unloaded block have completed their entity destruction life cycles.
        /// This is normally the last message sent for a block unload but can sometimes be sent
        /// prior to the elr_Unloaded message (but on the same tick) if no entities in the block
        /// have any destruction behaviors.
        elr_EntityDestructionCompleted,
        //@}

        /// Error values. All errors are negative values.
        //@{
        /// Generic non-specific failure
        elr_Failed = -1000,

        /// Failed to queue the request. Message contained invalid callback data.
        elr_RequestFailure,

        /// Asset id didn't specify a block file.
        elr_EntitySetNotFound,

        /// No asset with the given assetID was found. On unload this only means the block was not
        /// currently loaded.
        elr_AssetIDNotFound,

        /// A block asset was found but that block was corrupt and returned an error status when
        /// parsed.
        elr_ParseFailed,
        //@}
    };

    /// @name Construction and Destruction
    //@{

    /// default constructor
    EntityLoadResult();
    /**
        Constructor which initializes parameters

        @param[in] i_blockID The asset ID of the Entity that was loaded.
        @param[in] i_ctx The context for the loaded Entity.
        @param[in] i_result The result to report.
    */
    EntityLoadResult(const BlockIdentification& i_blockID, efd::UInt32 i_ctx, Result i_result);

    /// default destructor
    virtual ~EntityLoadResult();
    //@}

    /// convert this class into a stream of atomic types.
    virtual void Serialize(efd::Archive& ar);

    /// Test for success result
    bool Succeeded() const
    {
        return (int)m_result > 0;
    }
    /// Test for failure result
    bool Failed() const
    {
        return !Succeeded();
    }

    /// Storage for block AssetID and instance
    BlockIdentification m_assetID;
    /// Storage for context
    efd::UInt32 m_context;
    /// Storage for result
    Result m_result;
};

/// A smart pointer for the EntityLoadResult class
typedef efd::SmartPointer<EntityLoadResult> EntityLoadResultPtr;



/**
    Message implementation for preloading an entity.

    The EntityPreloadRequest is sent by EntityManager on the category returned by
    EntityManager::GetEntityPreloadCategory(). All registered preload services must handle this
    message and perform any desired preloading. Each service must send an EntityPreloadResponse to
    the category it registered with when complete.

    If the entity is not of a type normally managed by a preload service, the service must still
    send an EntityPreloadResponse.
*/
class EE_EGF_ENTRY EntityPreloadRequest: public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(EntityPreloadRequest, efd::kMSGID_EntityPreloadRequest, efd::IMessage);
    /// @endcond

public:
    EntityPreloadRequest();
    virtual ~EntityPreloadRequest();

    /// Convert this class into a stream of atomic types
    virtual void Serialize(efd::Archive& ar);

    /// Returns the associated entity
    egf::Entity* GetEntity() const;

    /// Returns the associated entity ID
    egf::EntityID GetEntityID() const;

    /// Storage for Entity
    egf::EntityPtr m_pEntity;
};

/// A smart pointer for the EntityPreloadRequest class
typedef efd::SmartPointer<EntityPreloadRequest> EntityPreloadRequestPtr;

/**
    Message implementation for indicating a service has completed preloading an entity.

    The EntityPreloadResponse is sent by each preloading service to the individual category
    it registered with. The OnAssetsLoaded behavior and regular entity lifecycle are not
    triggered by EntityManager until all registered preloading services have sent their
    EntityPreloadResponses.

    If the entity is not of a type normally managed by a preload service,
    the service must still send an EntityPreloadResponse.
*/
class EE_EGF_ENTRY EntityPreloadResponse: public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(EntityPreloadResponse, efd::kMSGID_EntityPreloadResponse, efd::IMessage);
    /// @endcond

public:
    /// Constructor
    EntityPreloadResponse();

    /// Destructor
    virtual ~EntityPreloadResponse();

    /// Convert this class into a stream of atomic types
    virtual void Serialize(efd::Archive& ar);

    /// Returns the associated entity
    egf::Entity* GetEntity() const;

    /// Returns the associated entity ID
    egf::EntityID GetEntityID() const;

    /// Storage for Entity
    egf::EntityPtr m_pEntity;
};

/// A smart pointer for the EntityPreloadResponse class
typedef efd::SmartPointer<EntityPreloadResponse> EntityPreloadResponsePtr;

} // end namespace egf

// Determine how various enumerations serialize into Archive or ParameterList instances:
EE_SPECIALIZE_ENUM(egf::EntityLoadRequest::Operation, efd::UInt8);
EE_SPECIALIZE_ENUM(egf::EntityLoadResult::Result, efd::SInt16);

#endif // EE_ENTITYLOADERMESSAGE_H

