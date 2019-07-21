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
#ifndef NIINPUT_H
#define NIINPUT_H

// This must be first
#if defined(_XENON)
    #include "NiInput_Xbox360.h"
#elif defined(WIN32)
    #include <NiSystem.h>
    #include "NiInput_DI8.h"
#elif defined(_PS3)
    #include "NiInput_PS3.h"
#else
    #error Unknown platform
#endif

#include <NiSystem.h>
#include <NiSmartPointer.h>

#include "NiInputLibType.h"
#include "NiInputDevice.h"
#include "NiInputGamePad.h"
#include "NiInputKeyboard.h"
#include "NiInputMouse.h"
#include "NiInputErr.h"
#include "NiInputSystem.h"

#include "NiAction.h"
#include "NiActionData.h"
#include "NiActionMap.h"

#endif  //#ifndef NIINPUT_H
