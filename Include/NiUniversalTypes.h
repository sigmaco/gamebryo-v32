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
#ifndef NIUNIVERSALTYPES_H
#define NIUNIVERSALTYPES_H

#include <efd/UniversalTypes.h>

#ifdef __SPU__

#include <inttypes.h>
typedef int8_t NiInt8;
typedef uint8_t NiUInt8;
typedef int16_t NiInt16;
typedef uint16_t NiUInt16;
typedef int32_t NiInt32;
typedef uint32_t NiUInt32;
typedef int64_t NiInt64;
typedef uint64_t NiUInt64;

#else

#include <NiOS.h>

typedef efd::WChar NiWChar;

typedef efd::SInt8 NiInt8;
typedef efd::UInt8 NiUInt8;

typedef efd::SInt16 NiInt16;
typedef efd::UInt16 NiUInt16;

typedef efd::SInt32 NiInt32;
typedef efd::UInt32 NiUInt32;

typedef efd::SInt64 NiInt64;
typedef efd::UInt64 NiUInt64;

typedef efd::WindowRef NiWindowRef;
typedef efd::StatusWindowRef NiStatusWindowRef;
typedef efd::ContextRef NiContextRef;
typedef efd::OglRenderContextRef NiOglRenderContextRef;
typedef efd::InstanceRef NiInstanceRef;
typedef efd::AcceleratorRef NiAcceleratorRef;
typedef efd::ModuleRef NiModuleRef;

typedef efd::EventRecord NiEventRecord;
typedef efd::EventRecordPtr NiEventRef;

typedef efd::CreateStructRef NiCreateStructRef;
typedef efd::MenuRef NiMenuRef;

#define NI_RESTRICT EE_RESTRICT

#endif // __SPU__

#include "NiFloat16.h"

#endif // NIUNIVERSALTYPES_H
