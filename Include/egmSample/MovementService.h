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
#ifndef EE_MOVEMENTSERVICE_H
#define EE_MOVEMENTSERVICE_H

#include <efd/ISystemService.h>
#include "egfDemoSystemServiceIDs.h"

#include "MovementHandler.h"

namespace egmAnimation
{
    class ActorAddedMessage;
    class ActorRemovedMessage;
}

namespace egmSample
{
/**
    The MovementService keeps track of the MovementHandlers.

    MovementHandlers are built-in models that register with the MovementService when they are
    created and unregister when they are removed.

    The MovementService calls the update method on each MovementHandler on every OnTick call
    of the service.  It also registers for actor added and removed messages sent by the
    AnimationService.  When actors are added or removed, the MovementHandler for that actor, if
    there is one, is updated.
*/
class EE_EGMSAMPLE_ENTRY MovementService : public efd::ISystemService
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(
        egmSample::MovementService,
        efd::kCLASSID_MovementService,
        efd::ISystemService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

public:

    /// Constructor
    MovementService();

    /// Destructor
    virtual ~MovementService();

    // Overridden virtual functions inherit base documentation and are not documented here.
    virtual const char* GetDisplayName() const;
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);
    virtual efd::AsyncResult OnInit();
    virtual efd::AsyncResult OnTick();
    virtual efd::AsyncResult OnShutdown();


    /**
        Checks to see if the entity has been registered with the service.  If it has, then
        call InitializeAnimationData on that entity's MovementHandler.
    */
    void HandleActorAddedMessage(const egmAnimation::ActorAddedMessage* pMessage,
        efd::Category targetChannel);

    /**
        Checks to see if the entity has been registered with the service.  If it has, then
        call ResetAnimationData on that entity's MovementHandler.
    */
    void HandleActorRemovedMessage(const egmAnimation::ActorRemovedMessage* pMessage,
        efd::Category targetChannel);

    /**
        Registers the MovementHandler with an owning entity with the specified ID with
        the MovementService.

        @param entityID the entityID of the MovementHandler's owning entity
        @param pHandler the MovementHandler being registered
    */
    void RegisterHandler(const egf::EntityID& entityID, MovementHandler* pHandler);

    /**
        Unregisters the MovementHandler with an owning entity with the specified ID from
        the MovementService.

        @param entityID the entityID of the MovementHandler's owning entity
    */
    void UnregisterHandler(const egf::EntityID& entityID);

protected:

    // Map of all movement handlers.
    efd::map<egf::EntityID, MovementHandlerPtr> m_handlerMap;

    /// The game time at the last OnTick call.
    efd::TimeType m_lastUpdate;
};

typedef efd::SmartPointer<MovementService> MovementServicePtr;

} // end namespace egmSample

#endif // EE_MOVEMENTSERVICE_H
