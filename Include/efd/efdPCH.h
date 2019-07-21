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
#ifndef EE_EFDPCH_H
#define EE_EFDPCH_H

/** @file efdPCH.h
    This header file is used as the Precompiled Header for building efd.  It should
    only include efd headers that are commonly used and not expected to change frequently.
    In addition it should include various external headers such as OS or CRT headers.
*/

#ifdef EE_USE_PCH

#if !defined(EE_EFD_CONFIG_DEBUG)

// For full builds, it is faster to include all of the current project's headers.
#include "efd/Foundation.h"

#else

// Headers that are unlikely to be edited and so are here to speed up incremental builds only.
// The rule of thumb is to avoid including any headers from the current project.
#include <efd/efdLibType.h>
#include <efd/OS.h>

#include <efd/Asserts.h>
#include <efd/BinaryStream.h>
#include <efd/Category.h>
#include <efd/ClassInfo.h>
#include <efd/DataStream.h>
#include <efd/IBase.h>
#include <efd/IConfigManager.h>
#include <efd/ID128.h>
#include <efd/IUtilities.h>
#include <efd/MemObject.h>
#include <efd/MessageFactory.h>
#include <efd/RefCount.h>
#include <efd/SequenceNumber.h>
#include <efd/StandardAllocator.h>
#include <efd/StdContainers.h>
#include <efd/String.h>
#include <efd/StringUtilities.h>
#include <efd/TimeType.h>
#include <efd/UniversalID.h>
#include <efd/UniversalTypes.h>
#include <efd/utf8string.h> // Should be in UniversalTypes.h?
#include <efd/Utilities.h>
#include <efd/Serialize.h>

#endif // EE_FULL_BUILD

#endif // EE_USE_PCH

#endif //EE_EFDPCH_H

