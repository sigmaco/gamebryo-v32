// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not
// be copied or disclosed except in accordance with the terms of that
// agreement.
//
//      Copyright (c) 1996-2008 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Calabasas, CA 91302
// http://www.emergent.net

#pragma once
#ifndef EE_ECRPHYSXBINDINGS_H
#define EE_ECRPHYSXBINDINGS_H

#include "ecrPhysXLibType.h"

#include <egf/Entity.h>

/**
    This namespace contains contains the scripting layer behavior API allowing scripts to hook into
    the Core Services PhysX system.
 */
namespace ecrPhysXBindings
{
    /**
        This method applies a conventional torque (or impulse) defined in the global coordinate
        frame to the all the actors in the specified entity.

        @param eid The prop entity that is receiving the torque
        @param torque The torque being applied.
    */
    EE_ECRPHYSX_ENTRY void ApplyTorque(egf::EntityID eid, efd::Point3 torque);

    /**
        This method applies a conventional force (or impulse) defined in the global coordinate
        frame to the all the actors in the specified entity.

        Note that if the force does not act along the center of mass of the actor, this
        will also add the corresponding torque.

        @param eid The prop entity that is receiving the force
        @param force The force being applied.
    */
    EE_ECRPHYSX_ENTRY void ApplyForce(egf::EntityID eid, efd::Point3 force);

    /**
        This method applies a conventional force (or impulse) defined in the global coordinate
        frame, acting at a particular point in global coordinates, to the all the actors in the
        specified entity.

        Note that if the force does not act along the center of mass of the actor, this
        will also add the corresponding torque.

        @param eid The prop entity that is receiving the force
        @param force The force being applied.
        @param pos The point in global coordinates where the force is applied.
    */
    EE_ECRPHYSX_ENTRY void ApplyForceAtPos(egf::EntityID eid, efd::Point3 force, efd::Point3 pos);

    /**
        Resets the PhysX scene called sceneName to the specified stateID.

        Return true if the scene is found.  Otherwise return false
    */
    EE_ECRPHYSX_ENTRY efd::Bool ResetState(const char* pSceneName, efd::UInt32 stateID);
}

#endif
