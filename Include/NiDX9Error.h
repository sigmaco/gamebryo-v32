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
//--------------------------------------------------------------------------------------------------

#pragma once
#ifndef NIDX9ERROR_H
#define NIDX9ERROR_H

//  The IndexBuffer manager is responsible for giving out and tracking index
//  buffers required by the application.
#include "NiDX9Headers.h"
#include "NiDX9RendererLibType.h"

char* NiDX9ErrorString(unsigned int uiErrorCode);

#endif  //#ifndef NIDX9ERROR_H
