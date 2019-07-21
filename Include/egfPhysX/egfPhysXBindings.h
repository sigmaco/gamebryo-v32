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
#ifndef EE_EGFPHYSXBINDINGS_H
#define EE_EGFPHYSXBINDINGS_H

#include "egfPhysXLibType.h"

#include <egf/EntityManager.h>
#include <egfPhysX/SceneService.h>

/**
    This namespace contains contains the scripting layer behavior API allowing scripts to hook
    into the PhysX Scene System.
 */
namespace egfPhysXBindings
{
    /**
        This method will start simulation on the scene with the specified start time.

        If time is less than 0, use the last fetch time. If there is no last fetch time, use the
        scheduler's current time.

        NOTE:  no simulation will occur before this method is called.

        Return true if the scene with the specified name is found. Otherwise, return false.
    */
    EE_EGFPHYSX_ENTRY efd::Bool StartSimulating(
        const char* sceneName,
        const efd::TimeType& time = egfPhysX::SceneService::ms_kInvalidSimulationTime);

    /**
        This method will start simulation on the scene with the specified start time.

        If time is less than 0, use the last fetch time. If there is no last fetch time, use the
        scheduler's current time. If a scene with the specified entity ID does not exist and
        the entity mixes in the PhysXScene model,  a scene will be created.

        NOTE: no simulation will occur before this method is called.

        Return true if the scene with the specified ID is found or can be created.  Otherwise,
        return false.
    */
    EE_EGFPHYSX_ENTRY efd::Bool StartSimulating(
        const egf::EntityID& sceneEntityId,
        const efd::TimeType& time = egfPhysX::SceneService::ms_kInvalidSimulationTime);

    /**
        Stop simulation on the specified scene.

        Simulation will only run again when StartSimulating is called.

        Return true if the scene is found.  Otherwise, return false.
    */
    EE_EGFPHYSX_ENTRY efd::Bool StopSimulating(const char* sceneName);

    /**
        Stop simulation on the specified scene.

        Simulation will only run again when StartSimulating is called.

        Return true if the scene is found.  Otherwise, return false.
    */
    EE_EGFPHYSX_ENTRY efd::Bool StopSimulating(const egf::EntityID& sceneEntityId);

    /**
        Returns the last time used in simulation.

        If the scene is not found, return SceneService::ms_kInvalidSimulationTime (-1)
    */
    EE_EGFPHYSX_ENTRY efd::TimeType GetCurrentPhysXTime(const char* sceneName);

    /**
        Returns the last time used in simulation.

        If the scene is not found, return SceneService::ms_kInvalidSimulationTime (-1)
    */
    EE_EGFPHYSX_ENTRY efd::TimeType GetCurrentPhysXTime(const egf::EntityID& sceneEntityId);

    /**
        Sets the value of isEnabled to the value of the collision flag for the specified
        groups.

        Return true if the scene is found and the groups are valid.  Otherwise, return false.
    */
    EE_EGFPHYSX_ENTRY efd::Bool GetGroupCollisionFlag(
        const char* sceneName,
        efd::UInt16 group1,
        efd::UInt16 group2,
        efd::Bool& isEnabled);

    /**
        Sets the value of isEnabled to the value of the collision flag for the specified
        groups.

        Return true if the scene is found and the groups are valid.  Otherwise,
        return false.
    */
    EE_EGFPHYSX_ENTRY efd::Bool GetGroupCollisionFlag(
        const egf::EntityID& sceneEntityId,
        efd::UInt16 group1,
        efd::UInt16 group2,
        efd::Bool& isEnabled);

    /**
        Method to set the collision flag between two collision groups in a scene.

        Return true if the scene is found and the groups are valid.  Otherwise, return false.
    */
    EE_EGFPHYSX_ENTRY efd::Bool SetGroupCollisionFlag(
        const char* sceneName,
        efd::UInt16 group1,
        efd::UInt16 group2,
        efd::Bool isEnabled);

    /**
        Method to set the collision flag between two collision groups in a scene.  If a scene
        with the specified entity ID does not exist and the entity mixes in the PhysXScene model,
        a scene will be created.

        Return true if the scene is found or created and the groups are valid.  Otherwise,
        return false.
    */
    EE_EGFPHYSX_ENTRY efd::Bool SetGroupCollisionFlag(
        const egf::EntityID& sceneEntityId,
        efd::UInt16 group1,
        efd::UInt16 group2,
        efd::Bool isEnabled);
}

#endif
