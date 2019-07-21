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
#ifndef EE_EGFPCH_H
#define EE_EGFPCH_H

/// @file
/// This header file is used as the Precompiled Header for building efd.  It should
/// only include efd headers that are commonly used and not expected to change frequently.
/// In addition it should include various external headers such as OS or CRT headers.

#if !defined(EE_CONFIG_DEBUG) && \
    !defined(EE_CONFIG_RELEASE) && \
    !defined(EE_CONFIG_SHIPPING)
#error One of EE_CONFIG_DEBUG, EE_CONFIG_RELEASE, or EE_CONFIG_SHIPPING must be defined
#endif

#ifdef EE_USE_PCH

#if !defined(EE_CONFIG_DEBUG)

// For full builds, it is faster to include all of the current project's headers.

#include <efd/efdPCH.h>
#include <efd/Foundation.h>
#include <egf/GameFramework.h>

#else

// Headers that are unlikely to be edited and so are here to speed up incremental builds only.
// The rule of thumb is to avoid including any headers from the current project.

#include <efd/efdPCH.h>
#include <egf/egfLibType.h>

// Heavily used by egf, but not in the efd pch. Don't want to be compile dependent on
// *all* of Foundation.h
#include <efd/ILogger.h>
#include <efd/MessageService.h> // That is a big dependency to add, but it is used a lot.
#include <efd/ParseHelper.h>
#include <efd/PathUtils.h>
#include <efd/StreamMessage.h>
#include <efd/ServiceManager.h>
#include <efd/TinyXML.h>

#include <efd/efdMessageIDs.h>
#include <efd/efdLogIDs.h>

#include <egf/BehaviorDescriptor.h>
#include <egf/EntityID.h>
#include <egf/EventID.h>
#include <egf/IBuiltinModel.h>
#include <egf/PropertyDescriptor.h>
#include <egf/EntityFactoryResponse.h>
#include <egf/ScheduledTask.h>
#include <egf/SchedulerQueue.h>
#include <egf/TProperty.h>

#endif // EE_FULL_BUILD

#endif // EE_USE_PCH

// don't care about C4505 - unreferenced local function has been removed
#if defined(EE_PLATFORM_WIN32) || defined (EE_PLATFORM_XBOX360)
#pragma warning(disable:4505)
#endif

#endif //EE_EGFPCH_H

