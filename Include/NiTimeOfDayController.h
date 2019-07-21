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

#ifndef NiENVIRONMENTCONTROLLER_H
#define NiENVIRONMENTCONTROLLER_H

#include <NiInterpController.h>
#include <NiFloatInterpController.h>
#include <NiColorInterpController.h>

/**
    This interface is used in the NiTimeOfDay system to allow time of day 
    animations to be applied to various values throughout the scene. 
*/
class NiTimeOfDayController : public NiRefObject
{
public:

    /**
        Virtual destructor for this base interface.
    */
    virtual ~NiTimeOfDayController(){}

    /**
        Update function called once per frame if an interpolator has been 
        attached to animate this controller's value. This function should only
        be called by the NiTimeOfDay class.

        @param fScaledTime the current point in time of the animation. 
    */
    virtual void Update(float fScaledTime) = 0;

    /**
        Sets the interpolation object that will control the animation of
        the variable this controller is tied to.
    */
    virtual void SetInterpolator(NiInterpolator* pkInterpolator) = 0;
};

NiSmartPointer(NiTimeOfDayController);

/**
    This class is a templated TimeOfDay controller class that allows 
    any variable on any object to be controlled by the TimeOfDay system
    through an exposed "Set" function on the target.
*/
template <class Functor, typename Value>    
class NiTTimeOfDayController : public NiTimeOfDayController
{
public:
    /// The type of the target
    typedef Functor TargetFunctor;

    /// The type of the value that is being set on the target
    typedef Value ValueType;

    /**
        NiTTimeOfDayController Constructor.
        This creates a time of day controller that is bound to a particular
        variable on a target through a simple "set" function.

        @param kFunctor the functor used to set the property's value. This functor MUST implement
            a templated void SetValue(Value toSet) function. See NiTTimeOfDayDefaultFunctor for 
            more information.
    */
    NiTTimeOfDayController(Functor kFunctor);

    /**
        Update function called once per frame if an interpolator has been 
        attached to animate this controller's value. This function should only
        be called by the NiTimeOfDay class.

        @param fScaledTime the current point in time of the animation. 
    */
    virtual void Update(float fScaledTime);

    /**
        Sets the interpolation object that will control the animation of
        the variable this controller is tied to.

        @param pkInterpolator the Interpolator to use with this controller
    */
    virtual void SetInterpolator(NiInterpolator* pkInterpolator);

protected:

    /// The target functor that allows for the setting of the property
    Functor m_kTargetFunctor;

    /// A pointer to the interpolator with the animation information
    NiInterpolatorPtr m_spInterpolator;
};

#include "NiTimeOfDayController.inl"

#endif