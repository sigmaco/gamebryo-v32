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
#ifndef EE_BAPICONFIG_H
#define EE_BAPICONFIG_H

#include <efd/UniversalTypes.h>
#include <egf/egfLibType.h>


// NOTE: This is a SWIG parsed file.  All methods listed in this file will have script wrappers
// generated.
//
// A note on argument types:
//
// Given any type the SWIG generated bindings will make certain assumptions about whether the
// parameter is an input argument, and output argument, or an input-output argument.  Given
// a type T, it will be treated as follows:
//
//    |---------------|---------------|------------------------------------------------------
//    | typename:     | treated as:   | notes:
//    |---------------|---------------|------------------------------------------------------
//    | T             | Input         |
//    | const T&      | Input         |
//    | const T*      | Input         | Pointer must NOT be NULL
//    | T*            | Output        | Pointer must NOT be NULL
//    | T&            | Input-Output  |
//    |---------------|---------------|------------------------------------------------------
//
// The one exception to the argument type rules above is efd::ParameterList.  efd::ParameterList*
// is treated as a basic type for the purpose of these rules, not efd::ParameterList itself.  For
// example, this means that "efd::ParameterList*" is treated as a plain ParameterList Input argument
// and "efd::ParameterList*&" is treated as an in-out efd::ParameterList parameter.  One additional
// special case, for convenance "efd::ParameterList&" is also treated as an in-out parameter.

namespace BehaviorAPI
{

/**
    Used by the scripting engines to obtain a configuration value for the given parameter.
    You can request values from section using the dotted form of the name.  For example, if
    you have the following in your config file:

    @code
    Config.ini:
        [TopSection.SubSection]
        Value = Whatever
    @endcode

    You could read the value using the following script code:

    @code
    python:
        from BehaviorAPI import GetConfigValue
        value = GetConfigValue("TopSection.SubSection.Value")

    lua:
        -- Note: BehaviorAPI is automatically imported, do not use "require 'BehaviorAPI'"
        local value = BehaviorAPI.GetConfigValue("TopSection.SubSection.Value")
    @endcode

    @param paramName Parameter name for which the configuration value to obtain.
    @return The configuration value or NullString if the given parameter does not exist in the
        configuration.
*/
EE_EGF_ENTRY efd::utf8string GetConfigValue(const efd::utf8string& paramName);

/**
    Return a string describing the current platform, such as "Win32" or "Xbox360".
*/
EE_EGF_ENTRY const char* GetPlatformName();

/**
    Return a string describing the current build mode, one of "Debug", "Release", or "Shipping".
    Technically this is the build configuration used to compile the "egf" library an may differ
    from the configuration used to build the executable or other libraries.
*/
EE_EGF_ENTRY const char* GetBuildConfiguration();

} // end namespace BehaviorAPI

#endif // #ifndef EE_BAPICONFIG_H

