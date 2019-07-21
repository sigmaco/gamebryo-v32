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
#ifndef EE_PhysXWhiteboxService_H
#define EE_PhysXWhiteboxService_H

#include <egmWhitebox\WhiteboxService.h>
#include <egfPhysX\SceneService.h>
#include <ecrPhysX\PropService.h>
#include <NiPhysXProp.h>

#include "egmPhysXWhiteboxLibType.h"

namespace egmPhysXWhitebox
{

/**
    The PhysX Whitebox Service generates geometry that matches the properties of any discovered
    entities that mix in the Whitebox model. In the case where the entity also mixes in
    PhysXWhitebox model, the service creates the necessary PhysX data
    for these entities so that the box geometry can also act as static or dynamic rigid bodies.

    The service is used simply by registering it; there is no relevant public interface.
    Any control over whiteboxes during the simulation is done through property changes on
    whitebox entities.
*/
class EE_EGMPHYSXWHITEBOX_ENTRY PhysXWhiteboxService : public egmWhitebox::WhiteboxService
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(
        PhysXWhiteboxService,
        efd::kCLASSID_PhysXWhiteboxService,
        egmWhitebox::WhiteboxService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond
public:

    /// @name Construction and Destruction
    //@{
    /// Default constructor.
    PhysXWhiteboxService();
    //@}

    /**
        Since the service stores entity pointers in a list, it must handle when those entities are
         removed before it got a chance to use them.
    */
    void HandleEntityRemovedMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

protected:
    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void OnServiceRegistered(efd::IAliasRegistrar* pAliasRegistrar);
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);
    virtual efd::AsyncResult OnTick();
    virtual efd::AsyncResult OnShutdown();
    virtual const char* GetDisplayName() const;

    // this structure lets us keep track of what entity properties need update
    struct EntityCreationState
    {
        bool usesPhysX;
        bool uninitialized;
        bool shapeChanged;
        bool densityChanged;
        bool frictionChanged;
        bool dynamicChanged;
        bool transformChanged;
        bool whiteboxChanged;
        efd::utf8string physXScene;
    };

    // Determine if it is time to create the geometry and actor for the given entity
    virtual void CreateAndRegisterSceneGraph(egf::Entity* pEntity);
    // Utility function that does the heavy lifting for entity creation
    void ActuallyCreateSceneGraph(egf::Entity* pEntity);
    // Update the entire scenegraph to match current entity properties
    virtual void UpdateWhiteboxes(egf::Entity* pEntity, NiAVObject* pObject, bool init = false);
    // Add physX shape data to our scenegraph
    NiPhysXProp* CreatePhysXData(egf::Entity* pEntity, NiAVObject* pRoot);
    // Collect whether the properties we care about are dirty
    void GetCreationState(egf::Entity* pEntity, EntityCreationState& state);
    // Determine if its ok to modify PhysX objects
    bool CanUseScene(const efd::utf8string& sceneName);

    egfPhysX::SceneService* m_pSceneService;
    ecrPhysX::PropService* m_pPropService;

    // each box has a unique friction value, so we must request unique material indexes from
    // the PhysX SDK starting from this value
    NiUInt16 m_materialStartIndex;

    // track entities that we have yet to create scenegraphs for
    efd::map<egf::Entity*, EntityCreationState> m_pendingCreateList;
    // track entities that have pending updates
    efd::map<egf::Entity*, EntityCreationState> m_pendingChangeList;
};

typedef efd::SmartPointer<PhysXWhiteboxService> PhysXWhiteboxServicePtr;

} // namespace

#endif
