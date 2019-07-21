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
#ifndef EE_SOCKET_WIN32_H
#define EE_SOCKET_WIN32_H

#define EE_SOCKET_ERROR(expression) (expression == SOCKET_ERROR)

#define EE_SOCKET_INVALID(expression) (expression == INVALID_SOCKET)

#define EE_SOCKET_CLOSE(expression) closesocket(expression)

#define EE_SOCKET_LINGER(expression) static_cast<u_short>(expression)

typedef int socklen_t;
#define EAGAIN WSAEWOULDBLOCK
#define EINPROGRESS WSAEWOULDBLOCK
#define EALREADY WSAEALREADY
#define EISCONN WSAEISCONN
#define ECONNRESET WSAECONNRESET

#include <efd/Metrics.h>
#include <efdNetwork/Win32/Socket_Win32.inl>

#endif // EE_SOCKET_WIN32_H