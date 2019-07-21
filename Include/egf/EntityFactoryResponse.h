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
#ifndef EE_ENTITYFACTORYRESPONSE_H
#define EE_ENTITYFACTORYRESPONSE_H

#include <egf/Entity.h>
#include <egf/egfMessageIDs.h>
#include <egf/egfLibType.h>
#include <egf/FlatModelFactoryResponse.h>

namespace egf
{
// forward declaration
class EntityFactoryRequest;

/**
    EntityFactoryResponse objects are created by the EntityFactory in reply to EntityFactoryRequest
    objects. Each EnityFactoryRequest processed by the loader will result in an
    EntityFactoryResponse.
 */
class EE_EGF_ENTRY EntityFactoryResponse : public egf::FlatModelFactoryResponse
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(
        EntityFactoryResponse,
        efd::kMSGID_EntityFactoryResponse,
        egf::FlatModelFactoryResponse);
    /// @endcond

public:
    /// @name Construction and Destruction
    //{

    /// Default constructor
    EntityFactoryResponse();

    /**
        Construct a new EntityFactoryResponse. Each response contains information about the
        original request, the result of the load, the new entity, the entity FlatModel,
        and FlatModel objects for any mix in model not already loaded.

        @param urn original request URN.
        @param responseCategory category expecting a response message.
        @param result result of the load.
        @param entityID the EntityID provided in the request.
        @param assetPath the asset path.
        @param isReload hint to the factory indicating if this is a reload.
        @param entity the new entity, or 0 if the load failed.
        @param flatModelName Name of the entity objects flat model.
        @param flatModelMap Set of FlatModel instances for dependent flat models.
        @param scriptFactoryResponseSet Set of ScriptFactoryResponse message containing
            dependent scripts.
    */
    EntityFactoryResponse(
        const efd::utf8string& urn,
        const efd::Category& responseCategory,
        efd::AssetLoadResponse::AssetLoadResult result,
        const egf::EntityID& entityID,
        const efd::utf8string& assetPath = "",
        bool isReload = false,
        egf::Entity* entity = 0,
        const efd::utf8string& flatModelName = "",
        FlatModelFactoryResponse::FlatModelMap flatModelMap =
            FlatModelFactoryResponse::FlatModelMap(),
        FlatModelFactoryResponse::DependentScriptSet scriptFactoryResponseSet =
            FlatModelFactoryResponse::DependentScriptSet());

    //@}

    /// @name Getters and Setters
    //@{

    /**
        Get the provided EntityID.
        @return EntityID given in the request.
    */
    const egf::EntityID& GetEntityID() const;

    /**
        Get the resulting entity.
        @return Created Entity or 0 if the Entity failed to factory.
    */
    egf::EntityPtr GetEntity() const;

    /**
        Set the entity.
        @param pEntity A pointer to the entity for this response.
    */
    void SetEntity(egf::Entity* pEntity) const;

    //@}

protected:
    // let the FlatModelFactory and EntityFactory have direct access to our member variables to
    // avoid having to make our variables public or creating accessor for them.
    friend class EntityFactory;
    friend class FlatModelFactory;

    /// EntityID from the original request.
    egf::EntityID m_entityID;

    /// Constructed Entity, or 0 if the entity failed to factory.
    mutable egf::EntityPtr m_entityPtr;
};

/// A SmartPointer for the EntityFactoryResponse class
typedef efd::SmartPointer<EntityFactoryResponse> EntityFactoryResponsePtr;

} // end namespace egf

#endif // EE_ENTITYFACTORYRESPONSE_H
