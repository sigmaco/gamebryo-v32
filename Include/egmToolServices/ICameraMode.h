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
#ifndef EE_ICAMERAMODE_H
#define EE_ICAMERAMODE_H

#include "egmToolServicesLibType.h"
#include "egmToolServicesClassIDs.h"

#include "ToolCamera.h"

#include <ecrInput/MouseMessages.h>

namespace egmToolServices
{

/**
    An interface for driving camera data with user input.
*/
class EE_EGMTOOLSERVICES_ENTRY ICameraMode : public efd::MemObject
{
    EE_DECLARE_CONCRETE_REFCOUNT;

public:
    virtual ~ICameraMode() {}

    /// Tick the camera movement for a given time delta.
    virtual efd::Bool OnTick(efd::TimeType timeElapsed, ToolCamera* pCamera) = 0;

    /**
        Called when the mouse scroll wheel is used.
        @param x Absolute x position.
        @param y Absolute y position.
        @param dScroll Amount of scrolling.
        @param pCamera Camera to drive.
    */
    virtual efd::Bool OnMouseScroll(
        efd::SInt32 x,
        efd::SInt32 y,
        efd::SInt32 dScroll,
        ToolCamera* pCamera) = 0;

    /**
        Called when the mouse moves on screen.
        @param x Absolute x position.
        @param y Absolute y position
        @param dx Delta x position.
        @param dy Delta y position.
        @param pCamera Camera to drive.
    */
    virtual efd::Bool OnMouseMove(
        efd::SInt32 x,
        efd::SInt32 y,
        efd::SInt32 dx,
        efd::SInt32 dy,
        ToolCamera* pCamera) = 0;

    /**
        Called when a mouse button is pressed.
        @param button The pressed button.
        @param x Absolute x position.
        @param y Absolute y position.
        @param pCamera Camera to drive.
    */
    virtual efd::Bool OnMouseDown(
        ecrInput::MouseMessage::MouseButton button,
        efd::SInt32 x,
        efd::SInt32 y,
        ToolCamera* pCamera) = 0;

    /**
        Called when a mouse button is released.
        @param button The released button.
        @param x Absolute x position.
        @param y Absolute y position.
        @param pCamera Camera to drive.
    */
    virtual efd::Bool OnMouseUp(
        ecrInput::MouseMessage::MouseButton button,
        efd::SInt32 x,
        efd::SInt32 y,
        ToolCamera* pCamera) = 0;

    /// Reset to default camera values.
    virtual void Reset(ToolCamera* pCamera) = 0;
};

typedef efd::SmartPointer<ICameraMode> ICameraModePtr;

} // namespace

#endif // EE_ICAMERAMODE_H
