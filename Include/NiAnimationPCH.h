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
#ifndef NIANIMATIONPCH_H
#define NIANIMATIONPCH_H

#if defined(NI_USE_PCH)

#include <NiMainPCH.h>

#if !defined(NIDEBUG)
#pragma message("using fat pch's")
// For full builds, it is faster to include all of the current project's headers.

#include "NiAnimation.h"

#else

// Minimize incremental NiAnimation rebuilds
#include "NiAnimState.h"
#include "NiBSplineBasis.h"
#include "NiBSplineFit.h"
#include "NiInterpScalar.h"
#include "NiPrimeNumber.h"
#include "NiQuatTransform.h"
#include "NiStringPalette.h"
#include "NiAnimationKey.h"
#include "NiTransformController.h"
#include "NiVisController.h"
#include "NiBlendInterpolator.h"
#include "NiBlendTransformInterpolator.h"
#include "NiBoolInterpolator.h"
#include "NiFloatInterpolator.h"
#include "NiPoint3Interpolator.h"
#include "NiQuaternionInterpController.h"

#endif

#endif //#if defined(NI_USE_PCH)

#endif // #ifndef NIANIMATIONPCH_H
