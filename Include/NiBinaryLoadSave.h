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
#ifndef NIBINARYLOADSAVE_H
#define NIBINARYLOADSAVE_H

#include <efd/BinaryLoadSave.h>

#if !defined(EE_REMOVE_LEGACY_NI)
#define NiBinaryStreamLoad     efd::BinaryStreamLoad
#define NiBinaryStreamLoadEnum efd::BinaryStreamLoadEnum
#define NiBinaryStreamSave     efd::BinaryStreamSave
#define NiBinaryStreamSaveEnum efd::BinaryStreamSaveEnum
#endif // !defined(EE_REMOVE_LEGACY_NI)


#endif // NIBINARYLOADSAVE_H
