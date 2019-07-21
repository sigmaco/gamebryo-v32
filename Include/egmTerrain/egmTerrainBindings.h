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
#ifndef EE_EGMTERRAINBINDINGS_H
#define EE_EGMTERRAINBINDINGS_H

#include "egmTerrainLibType.h"

#include <egf/EntityID.h>
#include <efd/Point3.h>

#include <NiTerrainLib.h>

/**
    This namespace contains contains the scripting layer behavior API allowing scripts to hook into
    the Gamebryo Terrain System.
 */
namespace egmTerrainBindings
{
    /// Picks against the terrain in the -Z direction from the given point.
    /// If it hits the terrain, it returns true and sets height and normal to the pick result.
    EE_EGMTERRAIN_ENTRY efd::Bool FindTerrainIntersection(
        const efd::Point3& i_pt,
        efd::Float32* o_height,
        efd::Point3* o_normal);
}

#endif
