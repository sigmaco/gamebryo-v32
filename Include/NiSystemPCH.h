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
#ifndef NISYSTEMPCH_H
#define NISYSTEMPCH_H

#if defined(NI_USE_PCH)

#if !defined(NIDEBUG)
#pragma message("using fat pch's")
// For full builds, it is faster to include all of the current project's headers.
#include <efd/efdPCH.h>
#include "NiBinaryLoadSave.h"
#include <efd/File.h>
#include "NiBinaryStream.h"
#include "NiFileName.h"
#include "NiLog.h"
#include "NiLogBehavior.h"
#include <efd/LoopedThread.h>
#include <efd/LoopedThreadProcedure.h>
#include "NiMemManager.h"
#include "NiMemStream.h"
#include "NiMessageBox.h"
#include "NiOS.h"
#include "NiPath.h"
#include "NiProcessorAffinity.h"
#include "NiRTLib.h"
#include "NiRWLock.h"
#include "NiSDMMacros.h"
#include "NiSearchPath.h"
#include "NiSemaphore.h"
#include "NiStaticDataManager.h"
#include "NiSystem.h"
#include "NiSystemSDM.h"
#include "NiThread.h"
#include "NiThreadProcedure.h"
#include "NiUniversalTypes.h"
#include "NiVersion.h"

#else

// Headers that are unlikely to be edited and so are here to speed up incremental builds only.
// The rule of thumb is to avoid including any headers from the current project.

#include <efd/efdPCH.h> // Automatically reduces to likely stable headers.
#include "NiLog.h"
#include "NiMemManager.h"
#include "NiOS.h"
#include "NiSDMMacros.h"
#include "NiStaticDataManager.h"
#include "NiSystemSDM.h"
#include "NiUniversalTypes.h"

#endif

#endif //#if defined(NI_USE_PCH)

#endif // #ifndef NISYSTEMPCH_H
