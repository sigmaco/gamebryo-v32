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

//////////////////////////////////////////////////////////////////////////////
// The Loki Library
// Copyright (c) 2001 by Andrei Alexandrescu
// This code accompanies the book:
// Alexandrescu, Andrei. "Modern C++ Design: Generic Programming and Design
//     Patterns Applied". Copyright (c) 2001. Addison-Wesley.
// Permission to use, copy, modify, distribute and sell this software for any
//     purpose is hereby granted without fee, provided that the above
//     copyright notice appear in all copies and that both that copyright
//     notice and this permission notice appear in supporting documentation.
// The author or Addison-Welsey Longman make no representations about the
//     suitability of this software for any purpose. It is provided "as is"
//     without express or implied warranty.
//////////////////////////////////////////////////////////////////////////////

// Last update: June 20, 2001

#pragma once
#ifndef NIFIXEDALLOCATOR_H
#define NIFIXEDALLOCATOR_H

#ifndef DEFAULT_CHUNK_SIZE
#define DEFAULT_CHUNK_SIZE 25600
#endif

#include <efd/FixedSizeAllocator.h>

#if !defined(EE_REMOVE_LEGACY_NI)
#define NiFixedAllocator efd::FixedSizeAllocator
#endif // !defined(EE_REMOVE_LEGACY_NI)


#endif // NIFIXEDALLOCATOR_H
