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
#ifndef EE_EONPCH_H
#define EE_EONPCH_H


/// @file
/// This header file is used as the Precompiled Header for building eon.  It should
/// only include eon headers that are commonly used and not expected to change frequently.
/// In addition it should include various external headers such as OS or CRT headers.

#if !defined(EE_CONFIG_DEBUG) && \
    !defined(EE_CONFIG_RELEASE) && \
    !defined(EE_CONFIG_SHIPPING)
#error One of EE_CONFIG_DEBUG, EE_CONFIG_RELEASE, or EE_CONFIG_SHIPPING must be defined
#endif

#ifdef EE_USE_PCH

#include <efd/efdPCH.h>
#include <egf/egfPCH.h>
#include <efd/Foundation.h>
#include <egf/GameFramework.h>

#include <eon/eonLogIDs.h>

#endif // def EE_USE_PCH

#endif // EE_EONPCH_H
