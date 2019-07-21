#pragma once
#ifndef EE_INPUTSERVICEMOUSE_H
#define EE_INPUTSERVICEMOUSE_H

#include <ecrInput/InputServiceActionBase.h>
#include <ecrInput/InputService.h>

namespace ecrInput
{

/**
  This class processes a mouse action.

  The returned magnitude is always 0.0. X and Y specify the change in mouse position
  since the last tick, and Z specifies the change in mouse wheel.
*/

class EE_ECRINPUT_ENTRY InputServiceMouse : public ecrInput::InputServiceActionBase
{
public:

    /// @name Construction and Destruction.
    //@{
    /// Default constructor.
    InputServiceMouse();
   
    /**
        Initializing constructor.
        @param flags An ORed combination of ecrInput::InputService::ActionFlags.
        @param appData User-specified data.
        @param deviceID Which device to listen for events on. Typically is 0 for a mouse.
        @param modifiers Device modifiers. These should be an ORed combination of
            modifiers specific to the device type, taken from NiInputMouse::Modifiers.
        @param pFilter A post-process callback for input.
    */
    InputServiceMouse(
        efd::UInt32 flags,
        efd::UInt32 appData = 0,
        efd::UInt32 deviceID = 0,
        efd::UInt32 modifiers = 0,
        ecrInput::InputService::InputFilteringCallback pFilter = NULL);

    /// Virtual Destructor.
    virtual ~InputServiceMouse();
    //@}

    /// @cond EMERGENT_INTERNAL

    /// Determines if action was triggered, also checking modifiers and range if needed.
    /// It returns true if the action was triggered and also fills in the magnitude
    /// and coordinates.
    virtual efd::Bool ProcessInput(
        InputService* pInputService,
        efd::UInt32& appData,
        efd::Float32& magnitude,
        efd::Float32& x,
        efd::Float32& y,
        efd::Float32& z);

    /// Save action data to XML.
    efd::Bool SaveXml(efd::TiXmlElement* pElement);

    /// Load action data from XML.
    efd::Bool LoadXml(efd::TiXmlElement* pElement);

    /// @endcond

protected:

    ecrInput::InputService::InputFilteringCallback m_pFilter;
};

};  // end namespace ecrInput

#endif // EE_INPUTSERVICEMOUSE_H
