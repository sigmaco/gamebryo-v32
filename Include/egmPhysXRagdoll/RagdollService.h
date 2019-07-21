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
#ifndef EE_PHYSXRAGDOLLSERVICE_H
#define EE_PHYSXRAGDOLLSERVICE_H

#include "egmPhysXRagdollLibType.h"

#include <egf/EntityID.h>
#include <efd/FixedString.h>
#include <efd/ISystemService.h>
#include <ecrPhysX/PhysXPropMessage.h>

#include <ecr/SceneGraphService.h>

#include <egmAnimation/AnimationService.h>

// Forward declarations
namespace egf
{
    class Scheduler;
}

namespace efd
{
    class MessageService;
}

namespace ecrPhysX
{
    class PropService;
}

#include <NiPhysXSequenceManager.h>

namespace egmPhysXRagdoll
{

/**

*/
class EE_EGMPHYSXRAGDOLL_ENTRY RagdollService : public efd::ISystemService
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(
        egmPhysXRagdoll::RagdollService,
        efd::kCLASSID_PhysXRagdollService,
        efd::ISystemService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond
public:

    /**
    */
    RagdollService();

    /**
    */
    virtual ~RagdollService();

    /// Return the name of the service, in this case "RagdollService".
    virtual const char* GetDisplayName() const;

    /**
        This method does nothing.
    */
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);

    /**
        OnInit caches pointers to other services and subscribes to messages.
    */
    virtual efd::AsyncResult OnInit();

    /**
        OnTick applies any changes that have been buffered since the last tick.

        Most PhysX-related calls cannot be made during simulation, so changes are buffered
        when the service first learns of them, and then applied here, when simulation is
        presumed to be inactive.
    */
    virtual efd::AsyncResult OnTick();

    /**
        Unsubsccribe to messages and delete any pending data.
    */
    virtual efd::AsyncResult OnShutdown();

    /**
        This message handler is called when an entity has been updated in the
        scheduler.

        @param pMessage The entity message.
        @param targetChannel Channel the message was sent on.
    */
    void HandleEntityUpdatedMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    /**
        If the new actor is a physical actor (mixes in PhysXRagdoll), get the list
        of sequences that must be tagged and store them on an NiPhysXSequenceManager.

        Since all needed information is available during ActorAdded events, we don't
        have to do anything during Entity Discovery.
    */
    void HandleActorAddedMessage(
        const egmAnimation::ActorAddedMessage* pMessage,
        efd::Category targetChannel);

    /**
        Remove any data associated with the actor that is being removed.
    */
    void HandleActorRemovedMessage(
        const egmAnimation::ActorRemovedMessage* pMessage,
        efd::Category targetChannel);

    /**
        Process any ragdoll that is waiting on the prop that has been added.
    */
    void HandlePropAddedMessage(
        const ecrPhysX::PhysXPropMessage* pMessage,
        efd::Category targetChannel);

    /**
        Revert the physical sequences of any ragdoll associated with the prop.
    */
    void HandlePropRemovingMessage(
        const ecrPhysX::PhysXPropMessage* pMessage,
        efd::Category targetChannel);

protected:

    enum {
        RAGDOLL_SET_SEQUENCES = 0x01,
        RAGDOLL_REMOVE_SEQUENCES = 0x02,
        RAGDOLL_REPLACE_SEQUENCES = 0x03
    };

    // If we only are keeping track of the NiPhysXSequenceManagerPtr,
    // this struct could probably be done away with, folded back in to
    // a list of SMPtrs and methods on this class.
    struct RagdollData : public efd::MemObject
    {
        RagdollData();
        void RevertAllSequences();

        efd::list<NiPhysXSequenceManagerPtr> m_spSequenceManagers;
        NiActorManagerPtr m_spActorManager;

        /// ID of the entity this ragdoll belongs to
        egf::EntityID m_entityID;

        efd::UInt8 m_sequenceState;
    };

    efd::map<egf::EntityID, RagdollData*> m_ragdolls;

    efd::list<egf::EntityID> m_pendingRagdolls;

    virtual efd::Bool RegisterPhysicalSequences(RagdollData* pRagdollData, egf::Entity* pEntity);
    virtual void MarkSequences(RagdollData* pRagdollData, egf::Entity* pEntity);
    virtual void RemovePhysicalSequences(RagdollData* pRagdollData);

    ecrPhysX::PropService* m_pPropService;
    egmAnimation::AnimationService* m_pAnimationService;
    egf::EntityManager* m_pEntityManager;
};

typedef efd::SmartPointer<RagdollService> RagdollServicePtr;

}; // namespace

#endif
