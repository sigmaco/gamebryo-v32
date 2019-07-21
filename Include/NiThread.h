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
#ifndef NITHREAD_H
#define NITHREAD_H

#include <efd/Thread.h>

// While not technically needed for compilation, these two directives provide backwards
// compatibility with previous versions of Gamebryo where NiThread was not a direct define for
// the efd version.
#include <NiThreadProcedure.h>
#include <NiProcessorAffinity.h>

#define NiThread efd::Thread

#endif  //#ifndef NITHREAD_H
