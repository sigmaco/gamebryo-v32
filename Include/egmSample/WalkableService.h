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
#ifndef EE_WALKABLESERVICE_H
#define EE_WALKABLESERVICE_H

#include <ecr/CoreRuntimeMessages.h>
#include <ecr/SceneGraphService.h>
#include <efd/ISystemService.h>
#include <egf/Entity.h>
#include <egmTerrain/TerrainService.h>
#include <egmTerrain/TerrainChangedMessage.h>
#include <NiAVObject.h>
#include <NiPick.h>
#include <NiPoint3.h>
#include <NiTList.h>
#include "egfDemoSystemServiceIDs.h"
#include "egmSampleLibType.h"


namespace egmSample
{
/**
    Helps entities conform to walkable and non-walkable surfaces.

    This service provides the functionality necessary to make an entity to conform to the
    height of walkable surfaces or terrain and be blocked and slide around the edges of
    walkable surfaces, non-walkable surfaces and terrain. It collects references to
    geometry that follows a naming convention identifying it as walkable or non-walkable
    and optionally an NiTerrain object.

    The service can optionally track material metadata from walk requests and associate that
    with the requesting entity such that material change notifications can be sent out when
    the walked-on material changes.

    Walkable and non-walkable surfaces are identified whenever new scenegraphs are created. The
    walkable service will inspect newly created scenegraphs and find any objects within it
    named "Walkable" or "NonWalkable" respectively. These objects are cached and recursively
    picked against to determine success.

    Terrain material can be used to limit walkability. To do so, attach a float metadata to the
    material called "NonWalkable". The value of the metadata will be used to determine the
    walkability threshold for that material on a scale from 0 to 100. Areas where the material
    has a percent of influence above this threshold will be non-walkable.

    To associate a walkable surface with a material name, attach an NiStringExtraData called
    "MaterialName" with a value of whatever material you want change notifications to be sent
    for. Similarly, to associate a material with terrain, add a string metadata to your
    terrain material called "MaterialName" with a value of the material name.
*/
class EE_EGMSAMPLE_ENTRY WalkableService : public efd::ISystemService
{
    /// @cond EMERGENT_INTERNAL

    EE_DECLARE_CLASS1(WalkableService, efd::kCLASSID_WalkableService, efd::ISystemService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

public:
    WalkableService();

    /**
        Initializes maps, creates pick object for Walkable service, subscribes for messages.
    */
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);

    /**
        Unsubscribes for messages, cleans up maps.
    */
    virtual efd::AsyncResult OnShutdown();

    /// Returns "egmSample::WalkableService"
    virtual const char *GetDisplayName() const;

    /**
        Checks the new scene for walkable/nonwalkable elements and adds them to the list
    */
    virtual void HandleSceneAddedMessage(
        const ecr::SceneGraphAddedMessage* pMessage,
        efd::Category targetChannel);

    /**
        Removes walkable/nonwalkable elements for the removed scene
    */
    virtual void HandleSceneRemovedMessage(
        const ecr::SceneGraphRemovedMessage* pMessage,
        efd::Category targetChannel);

    /**
        Deals with updates to the terrain, probably due to rapid iteration
    */
    virtual void HandleTerrainChangedMessage(
        const egmTerrain::TerrainChangedMessage* pMessage,
        efd::Category targetChannel);

    /**
        Determines how the given entity can move relative to the scene's walkable surfaces,
        non-walkable surfaces and terrain.

        @param pEntity The entity that is attempting to move
        @param source The starting position of that entity
        @param goal The destination position the entity is trying to move to
        @param result The actual destination after being blocked or sliding
        @param callDepth Internally used to limit pick count. Should always be zero when called
            externally
        @return If no valid walkable results were found, false is returned
    */
    efd::Bool Walk(
        egf::Entity* pEntity,
        efd::Point3 source,
        efd::Point3 goal,
        efd::Point3& result,
        efd::SInt32 callDepth);

    /**
        Sets the slope threshold beyond which the player will not be able to walk.
        This parameter is only considered when moving on terrain. Walkable meshes can be
        walked on at any slope.

        @param newSlope Slope expressed as a ratio of distance in the pick direction over
               distance perpendicular to the slope direction. In other words, it is rise
               over run.
    */
    inline void SetMaxSlope(efd::Float32 newSlope);

    /// Retrieve the current slope threshold that will limit movement on terrain
    inline efd::Float32 GetMaxSlope();

    /**
        Sets the LOD level that is used for terrain testing. Using a finer LOD level can be
        slightly more expensive and add small jagged edges to the walkable/nonwalkable areas.
        Using a coarser LOD level can prevent or allow entities from moving into unwanted
        areas and adds more error to ground conformance.

        @param newLOD LOD level to use
    */
    inline void SetTerrainLODLevel(efd::UInt32 newLOD);

    /// Retrieve the current LOD level used for terrain testing
    inline efd::UInt32 GetTerrainLODLevel();

    /**
        Sets an offset above the given entity's origin to cast the pick from. The offset is
        always in the exact opposite direction of the pick direction. A positive value is
        necessary if the entity needs to be able to move up an incline.

        @param newHeight the new offset from entity origin to use when performing picks
    */
    inline void SetPickHeight(efd::Float32 newHeight);

    /// Retrieve the current pick height used for all walk testing picks
    inline efd::Float32 GetPickHeight();

    /**
        Sets the direction of all walk testing picks. This should be the opposite of the
        application's up vector. A typical example for pick direction would be <0, 0, -1>.

        @param newDirection The pick direction
    */
    inline void SetPickDirection(efd::Point3 newDirection);

    /// Retrieve the current pick direction
    inline efd::Point3 GetPickDirection();

    /**
        Enable or disable whether the walkable service tracks material changes for each entity
        that requests walking information. When tracking is enabled, the service will pay
        attention to any material metadata on picked surfaces and store it. As soon as a
        different material is detected, a notification will be sent out. The service only
        tracks entities that make calls to the walk function.

        @param trackChanges If true, material changes will be tracked
    */
    inline void SetTrackMaterial(efd::Bool trackChanges);

    /// Retrieve whether material changes are currently being tracked
    inline efd::Bool GetTrackMaterial();

    /**
        Disables the Walk service such that it will always return the indicated goal position
        without actually testing.
    */
    inline void SetWalkAnywhere(efd::Bool walkAnywhere);

    /**
        Returns the state of the "Walk Anywhere" flag, which disables the walk service
    */
    inline efd::Bool GetWalkAnywhere();

    /**
        When material tracking is enabled this function can be used to query what the currently
        known material is for any given entity.

        @param pEntity What Entity to look up the current material for
        @param materialName The material that the given entity was last known to walk on
        @return True if the entity has walked on a material before
    */
    inline efd::Bool GetCurrentMaterial(egf::Entity* pEntity, NiFixedString& materialName);

protected:
    NiTPointerList<NiAVObject*> m_WalkableList;
    NiTPointerList<NiAVObject*> m_NonWalkableList;
    typedef EE_STL_NAMESPACE::pair<egf::Entity*, NiAVObject*> EntityMapEntry;
    typedef EE_STL_NAMESPACE::multimap<
        egf::Entity*,
        NiAVObject*,
        EE_STL_NAMESPACE::less<egf::Entity*>,
        efd::CustomAllocator<EntityMapEntry> > EntityMap;
    EntityMap m_EntityMap;
    NiTerrain* m_pTerrain;
    NiPick m_pick;
    NiFixedString m_walkableName;
    NiFixedString m_nonWalkableName;
    efd::Point3 m_pickDir;
    efd::Float32 m_pickHeight;
    efd::Float32 m_maxSlope;
    efd::UInt32 m_terrainLODLevel;
    efd::Bool m_walkAnywhere;

    efd::Bool m_trackMaterialChanges;
    efd::map<egf::Entity*, NiFixedString> m_MaterialMap;
    NiFixedString m_MaterialKeyName;

    ecr::SceneGraphService* m_pSceneGraphService;
    egmTerrain::TerrainService* m_pTerrainService;
    efd::MessageService* m_pMessageService;

    /**
        Determines how the given entity can move relative to the scene's walkable surfaces,
        non-walkable surfaces and terrain.

        @param pEntity The entity that is attempting to move
        @param source The starting position of that entity
        @param goal The destination position the entity is trying to move to
        @param result The actual destination after being blocked or sliding
        @param fTryNormalized Roughly 0..1 location from goal to source to try picking
        @param bOddTry Is this an even or odd try (affects pick site as well)
        @return If no valid walkable results were found, false is returned
    */
    efd::Bool WalkInternal(
        egf::Entity* pEntity,
        efd::Point3 source,
        efd::Point3 goal,
        efd::Point3& result,
        efd::Float32 fTryNormalized = 0.0f,
        efd::Bool bOddTry = false);

    /// Recursive function to assist in locating walkable and nonwalkable surfaces within a
    /// scenegraph.
    void AddWalkables(egf::Entity* pEntity, NiAVObject* pRoot);
    void RemoveWalkables(egf::Entity* pEntity);
};
typedef efd::SmartPointer<WalkableService> WalkableServicePtr;

} // end namespace egmSample

#include "WalkableService.inl"

#endif // EE_WALKABLESERVICE_H
