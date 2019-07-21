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
#ifndef EE_EGFPHYSX_ENTITYACTORDATA_H
#define EE_EGFPHYSX_ENTITYACTORDATA_H

#include "egfPhysXLibType.h"

#include <efd/BitUtils.h>
#include <efd/MemObject.h>
#include <efd/UniversalTypes.h>

#include <egf/Entity.h>

#include <efdPhysX/PhysXSDKManager.h>
#include <NxActor.h>

namespace egfPhysX
{

/**
    The EntityActorData class holds information relating an Entity to its PhysX actor.

    This class is used to manage information about actors that are created from entity
    properties, particularly triggers.
*/
class EE_EGFPHYSX_ENTRY EntityActorData : public efd::MemObject
{
    EE_DECLARE_CONCRETE_REFCOUNT;

public:

    /// Create a data object for the given entity.
    ///
    /// The actor is set to NULL.
    EntityActorData(egf::EntityPtr spEntity);

    /// Destructor.
    virtual ~EntityActorData();

    /// Get the entity for this data.
    inline const egf::EntityPtr GetEntity() const;

    /// Get the actor for this data.
    inline NxActor* GetActor() const;

    /// Set the actor for this data.
    inline void SetActor(NxActor* pActor);

    /// Get the scale of the PhysX scene holding this actor
    inline const efd::Float32& GetSceneScale() const;

    /// Set the scale of the PhysX scene holding this actor
    inline void SetSceneScale(const efd::Float32& scale);

    /// Get the name of the PhysX scene that holds this actor
    inline const efd::utf8string& GetSceneName() const;

    /// Get the earliest time that the next stay event will be sent.
    inline efd::TimeType GetNextStayEventTime() const;

    /// Set the earliest time that the next stay event can be sent.
    inline void SetNextStayEventTime(const efd::TimeType nextTime);

    /// Get the repeat interval for stay events.
    inline efd::Float32 GetStayEventInterval() const;

    /// Set the repeat interval for stay events.
    inline void SetStayEventInterval(const efd::Float32 stayInterval);

    /// Returns whether or not this actor is also a trigger
    inline efd::Bool IsTrigger() const;

    /**
        Perform processing necessary for an entity update message on this entity.

        This function caches updated properties for later application,
        in the OnTick function.

        @return True if relevant PhysX data was changed and the entity must be ticked. False
            if there have been no changes to the PhysX related properties.
    */
    efd::Bool DoEntityUpdated();

    /**
        Apply cached updates.

        This function must be called outside a PhysX simulate/fetchResult block.
    */
    void OnTick();

    /**
        Mark this actor as owned (or not) by the trigger service.
        
        When owned, the Trigger Service will attempt to release the actor when the entity data
        is removed.
    */
    inline void SetTriggerOwnsActor(const bool isOwned);

    /// Get the Trigger Service ownership status.
    inline bool GetTriggerOwnsActor() const;

    /// Mark this data for future actor release.
    inline void MarkForRelease();

    /// Clear any future actor release flag.
    inline void ClearForRelease();

    /// Query whether this data is marked for actor release.
    inline efd::Bool IsMarkedForRelease() const;

    /// Mark this data for future removal.
    inline void MarkForRemoval();

    /// Clear any future removal flag.
    inline void ClearForRemoval();

    /// Query whether this data is marked for removal.
    inline efd::Bool IsMarkedForRemoval() const;
    /// Helper for generating memory leak reports
    static void LeakDump(void* pMem, char* o_buffer, unsigned int i_cchBuffer);

protected:
    void UpdateActorPose();
    void UpdateActorShape();
    void UpdateTriggers();

    enum {
        UPDATE_POSE = 0x01,
        UPDATE_SHAPE = 0x02,
        UPDATE_TRIGGERS = 0x04,
        UPDATE_RELEASE = 0x08,
        UPDATE_REMOVED = 0x10,
        TRIGGER_OWNED = 0x20
    };

    // The entity and actor
    egf::EntityPtr m_spEntity;
    NxActor* m_pActor;

    // The scale of the PhysX scene holding the actor
    efd::Float32 m_sceneScale;

    // The name of the scene that owns the actor
    efd::utf8string m_sceneName;

    // Trigger event time values
    efd::TimeType m_nextStayEventTime;
    efd::Float32 m_repeatInterval;

    // Values that are cached from the time an entities properties are updated until the
    // time they may be safely changed in the simulation.
    NxMat34 m_updatePose;
    NxShapeDesc* m_pUpdateShape;
    efd::UInt32 m_updateTriggerFlags;

    // Flags indicating things that must be updated.
    efd::UInt16 m_updateFlags;

    // Flag indicating whether or not this actor is a trigger
    efd::Bool m_isTrigger;
};

/// A SmartPointer for the EntityActorData class
typedef efd::SmartPointer<EntityActorData> EntityActorDataPtr;

} // end namespace egfPhysX

#include <egfPhysX/EntityActorData.inl>

#endif // EE_EFDPHYSX_ENTITYACTORDATA_H
