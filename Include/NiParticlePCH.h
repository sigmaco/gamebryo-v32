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
#ifndef NIPARTICLEPCH_H
#define NIPARTICLEPCH_H

#ifdef NI_USE_PCH

#include <NiAnimationPCH.h>

#if !defined(NIDEBUG)
#pragma message("using fat pch's")
// For full builds, it is faster to include all of the current project's headers.
#include "NiParticle.h"
#else

#include "NiParticleLibType.h"
#include "NiPSCommonSemantics.h"
#include "NiPSCollider.h"
#include "NiPSColliderDefinitions.h"
#include "NiPSColliderHelpers.h"
#include "NiPSPlanarCollider.h"
#include "NiPSSphericalCollider.h"
#include "NiPSForce.h"
#include "NiPSForceHelpers.h"


#endif

#endif  // #ifdef NI_USE_PCH

#endif  // #ifndef NIPARTICLEPCH_H
