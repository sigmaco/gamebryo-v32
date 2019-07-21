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
#ifndef EE_TOOLLIGHTSERVICE_H
#define EE_TOOLLIGHTSERVICE_H

#include "egmToolServicesLibType.h"
#include "egmToolServicesClassIDs.h"

#include <egf/Entity.h>
#include <ecr/ecrSystemServiceIDs.h>
#include <ecr/ecrLibType.h>
#include <ecr/LightService.h>

namespace egmToolServices
{
/**
    ToolLightService is a Gamebryo service which manages light sources and the lists of entities which
    they affect. LightService uses a simple range based algorithm to determine which renderable
    entities are affected by which lights. LightService also manages shadow generators (optionally
    associated with directional, point, and spot lights), as well as the lists of entities which
    may cast and/or receive shadows.

    When determining which lights are within range, the light service computes the variance of
    light ranges across the three cardinal axes. Using the axis with the largest variance, it
    ignores light to entity pairings which can not affect each other. Each potential pairing
    undergoes a more comprehensive test to determine if a light affects an entity.

    ToolLightService is a tool mode version of the LightService. The only change
    in the ToolLightService is that all Light models are assumed to have the
    "UpdateLightingOnMove" property set to true.

*/
class EE_EGMTOOLSERVICES_ENTRY ToolLightService : public ecr::LightService
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(ToolLightService, efd::kCLASSID_ToolLightService, ecr::LightService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

public:

    /**
        Constructor for the ToolLightService.

        Calls directly to the LightService constructor.
    */
    ToolLightService(bool enableAutomaticRelighting = true);

protected:
    /**
        Destructor for the ToolLightService.
    */
    virtual ~ToolLightService();

    /**
        Returns the display name, ToolLightService.
    */
    virtual const char* GetDisplayName() const;

    /// Registers an alias for the LightService
    virtual void OnServiceRegistered(efd::IAliasRegistrar* pAliasRegistrar);

    /**
        LightEntityChanged records that the light entity changed so that it's affect on the scene
        can be processed at a later time.

        Note: This implementation will always assume that the light's "UpdateLightingOnMove"
        property is set true.

        @param pLightData The light data associated with the entity.
        @param pEntity The entity that was changed.
    */
    virtual void LightEntityChanged(LightData* pLightData, egf::Entity* pEntity);

};

/// A SmartPointer for the ToolLightService class
typedef efd::SmartPointer<ToolLightService> ToolLightServicePtr;

} // End namespace egmToolServices.

#endif  // EE_TOOLLIGHTSERVICE_H
