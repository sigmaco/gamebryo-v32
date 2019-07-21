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
#ifndef EE_BASIC_STRING_H
#define EE_BASIC_STRING_H

#include <stlport/string>
#include <efd/RTLib.h>

namespace efd
{

// We need to import basic_string into the efd namespace.  Otherwise latter on our efd::string
// from Utilities will not be compatible with the internal string used in utf8string.
using EE_STL_NAMESPACE::basic_string;
using EE_STL_NAMESPACE::char_traits;

} // namespace efd


#endif  // EE_BASIC_STRING_H
