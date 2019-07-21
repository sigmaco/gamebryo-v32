// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not
// be copied or disclosed except in accordance with the terms of that
// agreement.
//
//      Copyright (c) 1996-2007 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Calabasas, CA 91302
// http://www.emergent.net

#pragma once
#ifndef EE_PHYSXTERRAINSERVICE_H
#define EE_PHYSXTERRAINSERVICE_H

#include "egmPhysXTerrainLibType.h"

#include <egf/EntityID.h>
#include <efd/ISystemService.h>

#include <ecr/SceneGraphService.h>
#include <egmTerrain/TerrainService.h>
#include <NiTerrain.h>
#include "PhysXTerrainDataPolicy.h"

// Forward declarations
namespace egfPhysX
{
    class SceneService;
    class SceneMessage;
}

namespace ecrPhysX
{
    class PropService;
    class NiPhysXSceneAdded;
}

class NxActor;
class NxScene;

namespace egmPhysXTerrain
{

/**
    The PhysXTerrain service extends the Gamebryo Terrain service to support
    PhysX interactions with the terrain.

    It adds the terrain custom data policy and loads physx data when capable
*/
class EE_EGMPHYSXTERRAIN_ENTRY PhysXTerrainService : public egmTerrain::TerrainService
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(
        egmPhysXTerrain::PhysXTerrainService,
        efd::kCLASSID_PhysXTerrainService,
        egmTerrain::TerrainService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

protected:
    /**
        Destructor.
    */
    virtual ~PhysXTerrainService();

public:
    /**
        Constructor.
        
        Initializes members, but otherwise does nothing.
    */
    PhysXTerrainService();

    /**
        This helper function returns a list of all actors created for the terrain associted with
        the given entity ID. The list will be empty if there are no terrains for this entity ID or
        the terrain is not a PhysXTerrain.

        @param entityID The entity ID associated with the terrain we want the actors for
        @return The list of NxActor created for the associated terrain
    */
    virtual efd::list<NxActor*> GetPhysXTerrainActors(egf::EntityID entityID);

    /**
        Called when a PhysXScene is added by the egfPhysX::SceneService.
        Pending data requiring actor creation for this scene will be processed
    */
    void HandleNiPhysXSceneAddedMessage(
        const ecrPhysX::NiPhysXSceneAdded* pMessage,
        efd::Category targetChannel);
    
    /**
        Called when a PhysXScene is about to be removed by the egfPhysX::SceneService.
        
        Any terrain PhysX using this scene has its actors removed.
    */
    void HandlePhysXSceneRemovingMessage(
        const egfPhysX::SceneMessage* pMessage,
        efd::Category targetChannel);

    /**
        This message handler is called when an entity has been updated in the
        EntityManager.
        @param pMessage The entity message.
        @param targetChannel Channel the message was sent on.
     */
    virtual void HandleEntityUpdatedMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

protected:

    /// @name ISystemService overrides
    /// @see efd::ISystemService
    //@{

    /**
        Returns "PhysXTerrainService".
    */
    virtual const char* GetDisplayName() const;

    /**
        Registers a service alias for our egmTerrain::TerrainService base class.
    */
    void OnServiceRegistered(efd::IAliasRegistrar* pAliasRegistrar);

    /**
        Calls egmTerrain::TerrainService::PreInit and then subscribes to messages.
        Return value is that of egmTerrain::TerrainService::PreInit.
    */
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);


    /**
        Performs operations that require the PhysX SDK, and then calls
        egmTerrain::TerrainService::OnTick. Priorities must be set such that this
        method is invoked when PhysX simulation is not active.
    */
    virtual efd::AsyncResult OnTick();

    /**
        Removes any PhysX content, unsubscribes from messages, and then calls
        egmTerrain::TerrainService::OnShutdown.
    */
    virtual efd::AsyncResult OnShutdown();
    //@}

    /**
        Overrides the TerrainService function to initialize PhysXTerrain specific data.
    */
    virtual void InitializeTerrain(NiTerrain* pkTerrain, egf::Entity* pEntity);

    /**
        Overrides the TerrainService function to remove PhysXTerrain specific data.
    */
    virtual void RemoveTerrainEntity(egf::Entity* pEntity, efd::Bool removeEntity = false);

    /// Map connecting physx scene names to the terrain physx data
    typedef efd::map< efd::utf8string, efd::list<PhysXTerrainDataPolicyPtr> > SceneNameToPhysXData;
    SceneNameToPhysXData m_terrainPhysXData;

    /// Map connecting physx scene names to the terrain entities
    typedef efd::map< efd::utf8string, EntityList > SceneNameToEntity;
    SceneNameToEntity m_physXTerrains;
    /// @name Cached service pointers
    //@{
    ecrPhysX::PropService* m_propService;
    //@}

    /// Flag to control whether to display the debug physx data or not
    efd::Bool m_disablePhysXDebugRendering;
};

/// A SmartPointer for the PhysXTerrainService class
typedef efd::SmartPointer<PhysXTerrainService> PhysXTerrainServicePtr;

} // end namespace egmPhysXTerrain

#endif // EE_PHYSXTERRAINSERVICE_H
