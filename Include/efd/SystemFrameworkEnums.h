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
#ifndef EE_SYSTEMFRAMEWORKENUMS_H
#define EE_SYSTEMFRAMEWORKENUMS_H

#include <efd/ClassInfo.h>

namespace efd
{
/// @name Constants and definitions from SystemFrameworkEnums.h

//@{

/** A Synchronous Result is simply a boolean success/fail value. It is used by the ISystemService
    OnPreInit method for consistency with other ISystemService methods which return tri-state
    AsyncResult values.
*/
enum SyncResult
{
    SyncResult_Failure,
    SyncResult_Success,
};

/** An Asynchronous Result is a tri-state value which can be used for methods that can either
    immediately fail, immediately finish or run asynchronously. This is used by the ISystemService
    methods OnInit, OnTick, and OnShutdown.
*/
enum AsyncResult
{
    AsyncResult_Failure,
    AsyncResult_Pending,
    AsyncResult_Complete,
};


/** System Service IDentification (SSID) number are used to identify and locate various system
    services at run-time.  System Service IDs are just normal ClassIDs expect they must use a
    value less than EE_INTERNAL_SERVICE_MAX (0x07ffffff).
*/
typedef efd::UInt32 SSID;
const SSID INVALID_SSID = 0;

/// This sentinel value is used to tell whether the net ID has been set yet.
const efd::UInt32 kNetID_Unassigned = 0;

/// All clients are initialized with the same fixed NetID since they start out offline.  If they
/// connect to a ChannelManager or Gateway they will be assigned a valid net id.
const efd::UInt32 kNetID_Client = 4096;

/// An invalid netid used by categories to indicate a broadcast channel
const efd::UInt32 kNetID_Any = 4095;

/// An invalid netid used by ISystemService categories to indicate a broadcast channel
const efd::UInt32 kNetID_ISystemService = 4094;

//@}

} // end namespace efd

#endif // EE_SYSTEMFRAMEWORKENUMS_H
