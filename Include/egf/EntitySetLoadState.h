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
#ifndef EE_ENTITYSETLOADSTATE_H
#define EE_ENTITYSETLOADSTATE_H

#include <efd/IBase.h>
#include <egf/EntityLoaderMessages.h>
#include <egf/egfClassIDs.h>
#include <egf/WorldFactoryResponse.h>

namespace efd
{
    class ServiceManager;
    class AssetLoadResponse;
    class AssetLocatorResponse;
}

namespace egf
{
/// @cond EMERGENT_INTERNAL

/**
    A class to keep track of a request to load an Entity Set. Multiple people might
    all request the same load so this class keeps track of all callers. Used internally by the
    EntityLoaderService class.
*/
class EntitySetLoadState : public efd::IBase
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(EntitySetLoadState, efd::kCLASSID_EntitySetLoadState, efd::IBase);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

public:
    /// Enum of status
    enum AssetLoadStatus
    {
        LOAD_FAILED,
        LOAD_NOT_STARTED,
        LOAD_STARTED,
        LOAD_COMPLETE,
    };

    /**
        Constructs and EntitySetLoadState.

        @param pMsg Load request message containing details of the block.
        @param pServiceManager Store a local pointer to the Service Manager.
    */
    EntitySetLoadState(const egf::EntityLoadRequest* pMsg, efd::ServiceManager* pServiceManager);

    /// Destructor
    virtual ~EntitySetLoadState();

    /**
        Add someone to the callback list. Will fail if they are already in the list.

        @note The BlockLoadParameters from the original request we be used and any different
            settings in this request are ignored. Only the additional callback data is used.

        @param settings A BlockLoadParameters instance from which to read the callback data.
        @return True if a new callback was added or false if this callback would be a duplicate.
    */
    bool AddCallback(const BlockLoadParameters& settings);

    /// Helper to check if the operation for the request is elo_Reload.
    bool IsReload() const;

    /// Returns the category used for block loading callbacks.
    static efd::Category GetCategory();

    /// The entity set being loaded.
    BlockIdentification m_requestID;

    /// The details of how the block should be loaded
    BlockLoadParameters m_settings;

    /// The name of the XML file containing the entity data.
    efd::utf8string m_entity_file;

    /// The contents of the XML file containing the entity data.
    efd::utf8string m_entity_buffer;

    /// The flag to hold the state of asset loading.
    AssetLoadStatus m_asset_status;

    /// Category used for my asset load responses
    efd::Category m_asset_load_callback;

    /// Type of operation.
    egf::EntityLoadRequest::Operation m_op;

    /// The category and behavior id combined uniquely identify a callback. If these are the same
    /// then it is an identical callback request.
    typedef EE_STL_NAMESPACE::pair<efd::Category, egf::BehaviorID> CallbackIdentity;
    /// The Context and the BlockLoadCallback flags are needed to apply the callback.
    typedef EE_STL_NAMESPACE::pair<egf::Context, efd::UInt32> CallbackData;
    /// Storage type for callback data
    typedef efd::map<CallbackIdentity, CallbackData> CallbackMap;
    /// Storage for callback data
    CallbackMap m_callbacks;

    /// Pointer to the world factory's response message to provide additional load data
    egf::WorldFactoryResponsePtr m_spWorldFactoryResponse;

    /**
        Method used to begin loading data using the Asset ID
    */
    void BeginAssetLoad();

    /**
        A handler for generic asset load responses.

        @param pMessage Pointer to the arriving message.
        @param targetChannel The channel the message was sent to.
    */
    void HandleAssetLoadMsg(const efd::AssetLoadResponse* pMessage, efd::Category targetChannel);

protected:

    /// Local pointer to the Service Manager
    efd::ServiceManager* m_pServiceManager;
};

/// A SmartPointer for the EntitySetLoadState class
typedef efd::SmartPointer<EntitySetLoadState> EntitySetLoadStatePtr;

/// @endcond

} // end namespace egf

#endif // EE_ENTITYSETLOADSTATE_H
