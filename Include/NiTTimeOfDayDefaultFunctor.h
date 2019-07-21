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

#ifndef NITTIMEOFDAYDEFAULTFUNCTOR_H
#define NITTIMEOFDAYDEFAULTFUNCTOR_H

/**
    This default templated class allows for custom classes to bind certain properties
    with a TimeOfDayController. To use this default temple, the target class MUST define
    a Set function for the property to be binded that follows the following format:
    void (Target::*SetFunction)(Value)
*/
template<class Target, class Value>
class NIENVIRONMENT_ENTRY NiTTimeOfDayDefaultFunctor : public NiMemObject
{
public:
    /// The type of the target
    typedef Target TargetType;

    /// The type of the value that is being set on the target
    typedef Value ValueType;

    /// The type of the function that is used to set the value on the target
    typedef void (Target::*SetFunctionType)(Value);

    /**
        NiTTimeOfDayDefaultFunctor Constructor.
        This creates a default functor that is bound to a particular
        variable on a target through a simple "set" function.

        @param pkTarget the object that will have a setting controlled
        @param kSetFunction the function to call on the object to set the value
    */
    inline NiTTimeOfDayDefaultFunctor(Target* pkTarget, SetFunctionType kSetFunction);

    /**
        Destructor.
    */
    inline ~NiTTimeOfDayDefaultFunctor();
    
    /**
        This is the function that will be called by the controller.
    */
    inline void SetValue(Value kToSet);

private:

    /// A pointer to the set function in the target
    SetFunctionType m_kSetFunction;

    /// A pointer to the target object that has its variable animated
    Target* m_pkFunctorTarget;
};

#include "NiTTimeOfDayDefaultFunctor.inl"

#endif