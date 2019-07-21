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
#ifndef EE_SOCKET_ERRORS_H
#define EE_SOCKET_ERRORS_H

namespace efd
{

enum EE_SOCKET_ERRORS
{
    EE_SOCKET_NO_DATA = 0,
    EE_SOCKET_ERROR_UNKNOWN = -1,
    EE_SOCKET_SHUTDOWN = -2,
    EE_SOCKET_CONNECTION_CLOSED = -3,
    EE_SOCKET_MESSAGE_QUEUED = -4,
    EE_SOCKET_QUEUE_ALMOST_FULL = -5,
    EE_SOCKET_SEND_FAILED = -6,
    EE_SOCKET_MESSAGE_NOT_SENT = -7,
    EE_SOCKET_CONNECTION_IN_PROGRESS = -8,
    EE_SOCKET_CONNECTION_COMPLETE = -9,
    EE_SOCKET_CONNECTION_FAILED = -10,
    EE_SOCKET_CONNECTION_ACCEPTED = -11,
    EE_SOCKET_END_OF_BUFFER = -12,
    EE_SOCKET_CONNECTION_TIMED_OUT = -13,
    EE_SOCKET_CONNECTION_NOT_FOUND = -14,
    EE_SOCKET_CONNECTION_NOT_ACTIVE = -15,
    EE_SOCKET_LISTEN_FAILED = -16,
    EE_SOCKET_INBOUND_CONNECTION_FAILED = -17,
};
} //End namespace efd
#endif //EE_SOCKET_ERRORS_H
