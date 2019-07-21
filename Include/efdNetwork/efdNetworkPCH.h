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
#ifndef EE_EFDNETWORKPCH_H
#define EE_EFDNETWORKPCH_H

#include <efd/efdPCH.h>
#include <efd/OS.h>
#include <efd/UniversalTypes.h>
#include <efd/Asserts.h>
#include <efd/efdLogIDs.h>

#include <efdNetwork/efdNetworkLibType.h>
#include <efdNetwork/IConnection.h>
#include <efdNetwork/INetTransport.h>

/** @file efdNetworkPCH.h
    This header file is used as the Precompiled Header for building efdnetwork.  It should
    only include efd headers that are commonly used and not expected to change frequently.
    In addition it should include various external headers such as OS or CRT headers.
*/

#endif //EE_EFDNETWORKPCH_H

