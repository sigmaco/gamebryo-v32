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
#ifndef EE_WALKABLEBUILTINS_H
#define EE_WALKABLEBUILTINS_H

#include <efd/Point3.h>
#include <egf/Entity.h>

#include "WalkableService.h"
#include "egmSampleLibType.h"

namespace egmSample
{
/**
    Makes an entity conform to walkable and non-walkable areas.

    This built-in enables an entity to conform to the height of walkables or terrain and be
    blocked and slide around non-walkables and terrain. It depends on the WalkableService to
    collect references to geometry that follows a naming convention marking it as walkable or
    non-walkable and optionally an NiTerrain object.

    @param entity ID of the entity that is trying to move
    @param goal the desired new position of the entity
    @param result return value indicating where the entity should end up after being blocked by
        non-walkables, sliding, and conforming to the height of the walkable surface
    @return whether or not any valid potential results were found
*/
EE_EGMSAMPLE_ENTRY efd::Bool ComputeWalk(
    egf::EntityID entity,
    efd::Point3 goal,
    efd::Point3& result);

} // end namespace egmSample

#endif // EE_WALKABLEBUILTINS_H
