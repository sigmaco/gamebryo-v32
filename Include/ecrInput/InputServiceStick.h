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
#ifndef EE_INPUTSERVICESTICK_H
#define EE_INPUTSERVICESTICK_H

#include "InputServiceActionBase.h"
#include "InputService.h"


namespace ecrInput
{

/**
    This class processes a game pad stick action.

    This action can be assigned to game pad stick or formed from any 3 axes, specified by custom
    semantics. Range and modifiers are checked if requested by flags.

    There are 2 variants for return value, depending on SPHERIC_COORDS flag:
      - Square coordinates. Magnitude equals 1.0f. X, Y and Z coordinates specify physical position
        of stick and can be each in range [-1..1]. Range treated as minimum and maximum values for
        each axis.
      - Spheric coordinates. Magnitude is sqrt(x^2 + y^2 + z^2) and represents distance from stick
        center to current stick position. Coordinates specify point on unit sphere (circle) and
        show direction. Range is specified by minimum and maximum radius (XMin and XMax), and 2
        ranges for spheric coordinate system angles: YMin and YMax are min and max values for phi
        and ZMin and ZMax are min and max values for theta.  This gives an ability to define
        reaction sector or ring.  If min value for angles equal max value, angle is not checked and
        2 radius define inner and outer radius of reaction ring.  For example, action can trigger
        if stick moved more than 1/4 from center (XMin = 0.25, XMax = 1.0, YMin = 0.0, YMax = 0.0);
        more than 1/2 from center and in up position (XMin = 0.5, XMax = 1.0, YMin = -sqrt(2)/2,
        YMax = sqrt(2)/2), etc.

    The Z coordinate s used only for custom sticks, where the Z axis semantic is set.
*/
class EE_ECRINPUT_ENTRY InputServiceStick : public InputServiceActionBase
{
public:
    /// @name Construction and Destruction.
    //@{
    /// Default constructor.
    inline InputServiceStick();

    /**
        Initializing constructor.
        @param stickType See InputService::StickType.
        @param flags An ORed combination of ecrInput::InputService::ActionFlags.
        @param appData User-specified data.
        @param deviceID Which device to listen for events on. Typically, deviceID is
            always 0 for keyboard and mouse, and may be 0 to NiInputSystem::MAX_GAMEPADS for
            GamePads.
        @param modifiers Device modifiers. These should be an ORed combination of
            modifiers specific to the device type, taken from one of NiInputKeyboard::Modifiers or
            NiInputMouse::Modifiers (there are no modifiers for GamePad input).
        @param minRangeX Minimum range on X axis for this action.
        @param maxRangeX Maximum range on X axis for this action.
        @param minRangeY Minimum range on Y axis for this action.
        @param maxRangeY Maximum range on Y axis for this action.
        @param minRangeZ Minimum range on Z axis for this action.
        @param maxRangeZ Maximum range on Z axis for this action.
        @param pFilter A post-process callback for input.
        @param axisSemanticX Semantic of the X axis for custom stick.
        @param axisSemanticY Semantic of the Y axis for custom stick.
        @param axisSemanticZ Semantic of the Z axis for custom stick.
    */
    inline InputServiceStick(
        InputService::StickType stickType,
        efd::UInt32 flags,
        efd::UInt32 appData = 0,
        efd::UInt32 deviceID = 0,
        efd::UInt32 modifiers = 0,
        efd::Float32 minRangeX = -1.0f,
        efd::Float32 maxRangeX = 1.0f,
        efd::Float32 minRangeY = -1.0f,
        efd::Float32 maxRangeY = 1.0f,
        efd::Float32 minRangeZ = -1.0f,
        efd::Float32 maxRangeZ = 1.0f,
        InputService::InputFilteringCallback pFilter = NULL,
        efd::UInt32 axisSemanticX = 0,
        efd::UInt32 axisSemanticY = 0,
        efd::UInt32 axisSemanticZ = 0);

    /// Virtual Destructor.
    virtual ~InputServiceStick();
    //@}

    /// @cond EMERGENT_INTERNAL

    /// Determines if action was triggered, also checking modifiers and range if needed.
    /// It returns true if the action was triggered and also fills in the magnitude
    /// and coordinates.
    virtual efd::Bool ProcessInput(
        InputService* pInput,
        efd::UInt32& appData,
        efd::Float32& magnitude,
        efd::Float32& x,
        efd::Float32& y,
        efd::Float32& z);

    /// Returns a unique hash for this action.
    virtual efd::UInt32 GetHash() const;

    /// Save action data to XML.
    efd::Bool SaveXml(efd::TiXmlElement* pElement);

    /// Load action data from XML.
    efd::Bool LoadXml(efd::TiXmlElement* pElement);

    /// @endcond

    /// @name Action data getters and setters.
    //@{
    /// Gets the stick type.
    inline InputService::StickType GetType() const;

    /// Sets the stick type.
    inline void SetType(InputService::StickType stickType);

    /// Gets custom semantics for each axis.
    inline void GetCustomSemantic(
        efd::UInt32& axisSemanticX,
        efd::UInt32& axisSemanticY,
        efd::UInt32& axisSemanticZ) const;

    /// Sets custom semantics for each axis
    inline void SetCustomSemantic(
        efd::UInt32 axisSemanticX,
        efd::UInt32 axisSemanticY,
        efd::UInt32 axisSemanticZ);

    /// Get stick range.
    inline void GetRange(
        efd::Float32& xMin,
        efd::Float32& xMax,
        efd::Float32& yMin,
        efd::Float32& yMax,
        efd::Float32& zMin,
        efd::Float32& zMax) const;

    /// Set stick range.
    inline void SetRange(
        efd::Float32 xMin,
        efd::Float32 xMax,
        efd::Float32 yMin,
        efd::Float32 yMax,
        efd::Float32 zMin,
        efd::Float32 zMax);

    /// Return true if provided value is in range of this action.
    efd::Bool IsInRange(
        efd::Float32 magnitude,
        efd::Float32 x,
        efd::Float32 y,
        efd::Float32 z) const;
    //@}

    /// Load translation maps.
    static void LoadTranslationMap();

    /// Unload translation maps.
    static void UnloadTranslationMap();

protected:
    // Data of a stick
    InputService::StickType m_stickType;
    efd::UInt32 m_axisSemanticX;
    efd::UInt32 m_axisSemanticY;
    efd::UInt32 m_axisSemanticZ;
    efd::UInt32 m_axisControlX;
    efd::UInt32 m_axisControlY;
    efd::UInt32 m_axisControlZ;
    efd::Float32 m_minRangeX;
    efd::Float32 m_maxRangeX;
    efd::Float32 m_minRangeY;
    efd::Float32 m_maxRangeY;
    efd::Float32 m_minRangeZ;
    efd::Float32 m_maxRangeZ;
    InputService::InputFilteringCallback m_pFilter;

    static FlagMap ms_stickTypeMap;
};

} // end namespace ecrInput

#include "InputServiceStick.inl"

#endif // EE_INPUTSERVICESTICK_H
