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
#ifndef NISYSTEM_H
#define NISYSTEM_H

#include "NiRTLib.h"
#include "NiOS.h"
#include "NiDebug.h"
#include "NiMemManager.h"
#include "NiMemObject.h"
#include <efd/File.h>
#include "NiPath.h"
#include "NiLog.h"
#include "NiSystemSDM.h"
#include "NiMessageBox.h"
#include "NiSystemDesc.h"
#include <efd/Endian.h>
#include "NiTCreate.h"
#include "NiUniversalTypes.h"
#include "NiStaticDataManager.h"

#ifndef __SPU__
#include "NiCriticalSection.h"
#endif

#include <efd/Utilities.h>
#include <efd/ILogger.h>

// Wrappers for some C Runtime functions
#define NiStrcpy efd::Strcpy
#define NiStrncpy efd::Strncpy
#define NiStrcat efd::Strcat
#define NiStrtok efd::Strtok
#define NiSprintf efd::Sprintf
#define NiVsprintf efd::Vsprintf
#define NiSnprintf efd::Snprintf
#define NiVsnprintf efd::Vsnprintf
#define NiMemcpy efd::Memcpy
#define NiMemmove efd::Memmove

#define NiWStrcpy efd::WStrcpy
#define NiWStrncpy efd::WStrncpy
#define NiWStrcat efd::WStrcat
#define NiWStrtok efd::WStrtok
#define NiWSprintf efd::WSprintf

// Constant for NiStrncpy function
#define NI_TRUNCATE EE_TRUNCATE

// Routines whose implementation depends on system
#define NiGetenv efd::GetEnvironmentVariable
#define NiStricmp efd::Stricmp
#define NiStrnicmp efd::Strnicmp
#define NiStrdup efd::Strdup
#define NiRotr efd::Rotr
#define NiSleep efd::Sleep
#define NiYieldThread efd::YieldThread
#define NiGetCurrentThreadId efd::GetCurrentThreadId

//--------------------------------------------------------------------------------------------------
#define NiSelectGE efd::SelectGE
#define NiSelect efd::Select

//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
// Cache Control Functions
//--------------------------------------------------------------------------------------------------
#define NiPrefetch128 efd::Prefetch128

//--------------------------------------------------------------------------------------------------
// Safe casting routines from 32-bit enum values to unsigned values.
#define NiInt32ToUInt8 efd::Int32ToUInt8
#define NiInt32ToUInt16 efd::Int32ToUInt16
#define NiInt32ToUInt32 efd::Int32ToUInt32
#define NiInt32ToInt8 efd::Int32ToInt8
#define NiInt32ToInt16 efd::Int32ToInt16

//--------------------------------------------------------------------------------------------------

// Routines that query the system
inline float NiGetCurrentTimeInSec() { return (float)efd::GetCurrentTimeInSec(); }

#define NiResetBaseTime efd::SetInitialTimeInSec

#define NiGetPerformanceCounter efd::GetPerformanceCounter

#ifndef __SPU__
#define NiGetFileSize efd::GetFileSize

// Routines that return information to user/programmer
#define NiWriteToStdErr efd::WriteToStdErr

#ifndef NiOutputDebugString
#define NiOutputDebugString EE_OUTPUT_DEBUG_STRING
#endif

// Routines for setting up environment for test apps
// (turn off error dialogs, etc)
#define NiInitTestEnvironment efd::InitTestEnvironment

#endif

#if defined(WIN32)
#include "NiSystem.inl"
#endif

#endif

