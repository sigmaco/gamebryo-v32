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
#ifndef EE_WhiteboxService_H
#define EE_WhiteboxService_H

#include <egf/Entity.h>
#include <egf/EntityID.h>
#include <efd/MessageHandlerBase.h>
#include <efd/ISystemService.h>
#include <efd/StreamMessage.h>
#include <egf/EntityChangeMessage.h>
#include <egf/FlatModelManager.h>
#include <ecr/ecrSystemServiceIDs.h>
#include <NiMesh.h>

#include "egmWhiteboxLibType.h"
#include <ecr/SceneGraphService.h>

namespace egmWhitebox
{

/**
    The Whitebox Service generates geometry that matches the properties of any discovered
    entities that mix in the Whitebox model. The geometry, how it is diplayed, and how the scene
    is structured is determined by the following properties: ShapeDimensions,
    Diffuse, RuntimeRender, Walkable, and SnapPoints.

    The service is used simply by registering it; there is no relevant public interface.
    Any control over whiteboxes during the simulation is done through property changes on
    whitebox entities.
*/
class EE_EGMWHITEBOX_ENTRY WhiteboxService : public efd::ISystemService
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(
        WhiteboxService,
        efd::kCLASSID_WhiteboxService,
        efd::ISystemService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond
public:

    /// @name Construction and Destruction
    //@{
    /// Default constructor.
    WhiteboxService();

    /// Virtual destructor.
    virtual ~WhiteboxService();
    //@}

    /**
        This message handler is called when a new entity is discovered. If the entity inherits
        from Whitebox, the service creates geometry for it
    */
    void HandleEntityDiscoverMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    /**
        This message handler is called when an entity has been removed from the EntityManager. So
        the service knows to un-register its geometry.
    */
    void HandleEntityRemovedMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    /**
        This message handler is called when properties of an entity change. So the service can
        modify the geometry.
    */
    void HandleEntityUpdatedMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    /// Tell the service whether it is being run within World Builder or in game
    void SetInToolMode(bool inToolMode);

protected:
    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);
    virtual efd::AsyncResult OnShutdown();
    virtual const char* GetDisplayName() const;

    // Subscribe to entity discovery, removal, update, etc messages
    void RegisterForEntityMessages();
    // Create a box and register it with the scene graph service
    virtual void CreateAndRegisterSceneGraph(egf::Entity* pEntity);
    // Update the entire scenegraph to match current entity properties
    virtual void UpdateWhiteboxes(egf::Entity* pEntity, NiAVObject* pObject, bool init = false);
    // Given the entity property values, push them onto all meshes
    void UpdateMeshesRecursive(const efd::Point3& dimensions, NiAVObject* pObject);
    // Set each meshes material properties to match the given diffuse color
    void UpdateMaterialsRecursive(const efd::ColorA& diffuse, NiAVObject* pObject);
    // Initialize the given mesh's data streams
    void SetupWhiteboxDatastreams(NiMesh* pMesh);
    // Initialize the given mesh's materials
    void SetupWhiteboxMaterial(NiMesh* pMesh);
    // Add or remove snap point nodes to the scenegraph
    void SetupSnapPoints(NiAVObject* pRoot, bool add = true);
    // Send the messages neccessary to make other services recognize structural changes
    void SendUpdateMessages(egf::Entity* pEntity);

    // Helper data to describe the geometry layout of the box
    static const NiUInt16 ALIGNOFFSET_POS_X = 0;
    static const NiUInt16 ALIGNOFFSET_POS_Y = 12;
    static const NiUInt16 ALIGNOFFSET_POS_Z = 24;
    static const NiUInt16 ALIGNOFFSET_NEG_X = 36;
    static const NiUInt16 ALIGNOFFSET_NEG_Y = 48;
    static const NiUInt16 ALIGNOFFSET_NEG_Z = 60;
    static const NiUInt16 ALIGNOFFSET_SIZE = 72;
    // vertices we need to modify to commit dimension changes along each axis
    NiUInt16 m_indexAlignment[ALIGNOFFSET_SIZE];
    // stores a multiplier for each corner of the box for easily committing dimension changes
    efd::Point3 m_snapMultipliers[8];
    // reminds us if we are running in toolbench or in game
    bool m_toolMode;
    // caching this string so we can do quick comparisons
    NiFixedString m_strSnapPoints;

    // cache references to commonly used services
    ecr::SceneGraphServicePtr m_spSceneGraphService;
    efd::MessageService* m_pMessageService;
    egf::FlatModelManager* m_pFlatModelManager;
    egf::EntityManager* m_pEntityManager;
};

typedef efd::SmartPointer<WhiteboxService> WhiteboxServicePtr;

} // namespace

#endif
