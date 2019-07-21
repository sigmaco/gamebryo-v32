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
#ifndef EE_ENTITYFACTORYREQUEST_H
#define EE_ENTITYFACTORYREQUEST_H

#include <egf/egfMessageIDs.h>
#include <egf/egfLibType.h>
#include <egf/EntityID.h>
#include <egf/FlatModelFactoryRequest.h>

// forward declarations
namespace efd
{
    class utf8string;
    class Category;
}

namespace egf
{
/**
    The EntityFactoryRequest is used to request an asynchronous Entity load. These
    requests are passed to the AssetFactoryManager for processing. The resulting
    Entity is returned to the caller in an EnityFactoryResponse.

    The requester only needs to provide the urn and EntityID. The AssetFactoryManager
    is responsible for providing the fully qualified path to the asset.
 */
class EE_EGF_ENTRY EntityFactoryRequest : public FlatModelFactoryRequest
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(
        EntityFactoryRequest,
        efd::kMSGID_EntityFactoryRequest,
        egf::FlatModelFactoryRequest);
    /// @endcond

public:
    /// @name Construction and Destruction
    //@{

    /// Default constructor
    EntityFactoryRequest() {}

    /**
        Construct a new EntityFactoryRequest.

        @param urn : URN for the model required by the Entity.
        @param responseCategory : Category to send the response.
        @param entityID : The entityID to use for the entity returned by this request.
        @param assetPath: fully qualified path to the Flat Model for the new entity.
        @param isMasterEntity : True if this is a master, owned entity. False if constructing a
            reflected entity owned by another simulator.
        @param isBackground if true, load is attempted in the background thread.
        @param isPreemptive if true, load is done as soon as possible.
        @param isReload indicates this is a reload request.
    */
    EntityFactoryRequest(
        const efd::utf8string& urn,
        const efd::Category& responseCategory,
        const egf::EntityID& entityID,
        const efd::utf8string& assetPath = "",
        bool isMasterEntity = true,
        bool isBackground = true,
        bool isPreemptive = false,
        bool isReload = false);

    //}

    /// @name Getters and Setters
    //@{

    /**
        Get the entityID used for this request.
        @return EntityID request entityID.
    */
    const egf::EntityID GetEntityID() const;

    /**
        See if this is a master, owned entity.
        @return true if this request is for a master, owned entity. False otherwise.
    */
    bool IsMasterEntity() const;

    //@}

protected:
    /// The EntityID for the created entity.
    egf::EntityID m_entityID;

    /// True if this is a master (owned) entity. False if it is a replicated entity.
    bool m_bIsMaster;
};

} // end namespace egf

/// A SmartPointer for the egf::EntityFactoryRequest class
typedef efd::SmartPointer<egf::EntityFactoryRequest> EntityFactoryRequestPtr;

#endif // EE_ENTITYFACTORYREQUEST_H
