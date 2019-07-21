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
#ifndef NIMAINPCH_H
#define NIMAINPCH_H

#if defined(NI_USE_PCH)

#if !defined(NIDEBUG)
#pragma message("using fat pch's")
// For full builds, it is faster to include all of the current project's headers.

// For full builds, it is faster to include all of the current project's headers.
#include <NiSystemPCH.h>

#include "NiMain.h"

#else

// Headers that are unlikely to be edited and so are here to speed up incremental builds only.
// The rule of thumb is to avoid including any headers from the current project.
#include <NiSystemPCH.h> // Auto reduces from FAT, includes efd

#include "NiMainLibType.h"

#include "NiAlphaProperty.h"
#include "NiBitfield.h"
#include "NiBool.h"
#include "NiClone.h"
#include "NiColor.h"
#include "NiFlags.h"
#include "NiFixedString.h"
#include "NiLines.h"
#include "NiMainSDM.h"
#include "NiMaterial.h"
#include "NiMath.h"
#include "NiMatrix3.h"
#include "NiNode.h"
#include "NiTNodeTraversal.h"
#include "NiObject.h"
#include "NiPlane.h"
#include "NiPoint2.h"
#include "NiPoint3.h"
#include "NiPrimitiveType.h"
#include "NiQuaternion.h"
#include "NiRect.h"
#include "NiRefObject.h"
#include "NiRTTI.h"
#include "NiGeometricUtils.h"
#include "NiSmartPointer.h"
#include "NiString.h"
#include "NiTArray.h"
#include "NiTList.h"
#include "NiTMap.h"
#include "NiTObjectList.h"
#include "NiTPointerList.h"
#include "NiTPointerMap.h"
#include "NiTPool.h"
#include "NiTPtrSet.h"
#include "NiTransform.h"
#include "NiTQueue.h"
#include "NiTSet.h"
#include "NiTStringMap.h"

#endif

#endif //#if defined(NI_USE_PCH)

#endif // #ifndef NIMAINPCH_H
