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
#ifndef EE_ToolSnapService_H
#define EE_ToolSnapService_H

#include "egmToolServicesLibType.h"
#include "egmToolServicesClassIDs.h"

#include <efd/ISystemService.h>
#include <NiColor.h>
#include <NiMesh.h>

#include "ecr/SceneGraphService.h"
#include <ecr/ecrSystemServiceIDs.h>
#include <ecr/CoreRuntimeMessages.h>

namespace egmToolServices
{

/**
    The ToolSnapService is responsible for maintaining a list of snap points and snapping to those
    points as requested. These snap points can be created in the art package by artists and used
    to assist in positioning entities in tools.

    In order for two entities to snap together, they need to both have at least one snap point.
    The snap point system has a "stickiness" radius that defines how close two entities must be
    before a "snap" operation occurs. When the snap occurs, the two snap points are made to be
    coincident.
*/
class EE_EGMTOOLSERVICES_ENTRY ToolSnapService : public efd::ISystemService
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(ToolSnapService, efd::kCLASSID_ToolSnapService, efd::ISystemService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond
public:

    /// Basic constructor
    ToolSnapService();

    /**
        This handler is invoked whenever the SceneGraphService registers a new scene graph
        object. This service then recurses over the scene graph to determine if any snap points
        exist.

        @param pMessage The notification message containing the scene graph that was added.
        @param targetChannel The target category on which the message arrived.
    */
    virtual void OnSceneGraphAdded(const ecr::SceneGraphAddedMessage* pMessage,
        efd::Category targetChannel);

    /**
        This handler is invoked whenever the SceneGraphService unregisters a scene graph
        object. This service then releases any snap points that were contained.

        @param pMessage The notification message containing the scene graph that was removed.
        @param targetChannel The target category on which the message arrived.
    */
    virtual void OnSceneGraphRemoved(const ecr::SceneGraphRemovedMessage* pMessage,
        efd::Category targetChannel);

    /**
        When beginning a translation event, snapping must be activated by this method. This
        will notify the service that it needs to begin rendering proxies as the objects
        move in space and snap points fall within the visualization bounds.

        @param pEntity The entity that is the focus of the snapping.
    */
    void BeginSnap(egf::Entity* pEntity);

    /**
        When performing a translation event, snapping is computed by this method. It compares the
        current entity with all other entities with snap points. If there is any overlap, it will
        test to see if a snap occurred. If so, the new snap point is returned by the translate
        argument.

        @param pEntity The notification message containing the scene graph that was removed.
        @param [in] startPoint The target category on which the message arrived.
        @param [out] translate The computed translation to achieve "snapping"
        @return Determine whether or not the snap occurred.
    */
    bool SnapToPoints(egf::Entity* pEntity, const efd::Point3& startPoint, efd::Point3& translate);

    /**
        Given a ray, compute the snap point that it comes closest to if it comes within the snap
        radius of any snap point.

        @param pEntity The entity to use the result. Any snap points associated with this entity
            will be ignored
        @param origin The origin of the input ray
        @param direction The direction of the input ray. This should be a unit vector
        @param snapPosition The resulting world position of the closest snap point
        @return Whether or not a snap occurred.
    */
    bool ClosestSnapToRay(
        egf::Entity* pEntity,
        NiPoint3 origin,
        NiPoint3 direction,
        NiPoint3& snapPosition);


    /**
        When completing a translation event, snapping must be deactivated by this method. This
        will hide any snap point proxies.
    */
    void EndSnap();

    /// Get how close two entities must be before a "snap" operation occurs.
    ///
    /// May be called during OnPreInit or OnInit.
    float GetStickinessRadius() const;

    /// Set how close two entities must be before a "snap" operation occurs.
    ///
    /// May be called during OnPreInit or OnInit.
    void SetStickinessRadius(efd::Float32 radius);

    /// Get whether or not we enable the snap points.
    ///
    /// May be called during OnPreInit or OnInit.
    bool GetSnapPointEnabled() const;

    /// Set whether or not we enable the snap points.
    ///
    /// May be called during OnPreInit or OnInit.
    void SetSnapPointEnabled(bool enabled);

protected:
    /// Destructor
    virtual ~ToolSnapService();

    /**
        Get the human-friendly name of this service.
    */
    virtual const char* GetDisplayName() const;

    /**
        Used to cache common services and register for messages.
    */
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);

    /**
        Used to unregister this service from message handling.
    */
    virtual efd::AsyncResult OnShutdown();

    /// Recurse over a scene graph and determine if there are any snap point nodes.
    void RegisterSnapPoints(NiNode* pScene);

    /// Display proxies for the snap points that are children of a given scene graph node.
    void ShowSnapPoints(NiNode* pScene, bool bShow);

    /// Display proxies for all snap point objects in the world
    void ShowAllSnapPoints(bool bShow);

    /// Creates a snap point visualization mesh
    void CreateMasterMesh();

    /// Saved scene graph service pointer for convenient access.
    ecr::SceneGraphService* m_pSceneGraphService;

    /// Saved message service pointer for convenient access.
    efd::MessageService* m_pMessageService;

    typedef efd::map<egf::Entity*, NiNode*> EntityToSnapSceneMap;

    /// Map of enttities to their root snap node in the scene graph
    EntityToSnapSceneMap m_scenes;

    /// The source mesh for snap points as rendered geometry
    NiMeshPtr m_spSnapPointMesh;

    /// How close two entities must be before a "snap" operation occurs.
    float m_stickyDistance;

    /// Determine whether or not snapping is enabled.
    bool m_snapPointEnabled;

    /// Determine whether or not
    bool m_snapping;

    /// The current entity that is being snapped "to".
    egf::Entity* m_activeEntity;

    /// The current snap point node for the active entity
    NiNode* m_activeNode;
};

typedef efd::SmartPointer<ToolSnapService> ToolSnapServicePtr;

} // namespace

#endif // EE_ToolSnapService_H
