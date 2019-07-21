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
#ifndef EE_STDHASHMAP_H
#define EE_STDHASHMAP_H

#include <efd/StdContainers.h>
#include <efd/utf8string.h>

/// @cond EMERGENT_INTERNAL

namespace _STLP_STD_NAME
{

    /// A Hash Function to support using efd::utf8string as a key in a @ref efd::hash_map.
    template<>
    struct hash<efd::utf8string>
    {
        /// Functor to generate a hash value from a utf8string for use in @ref efd::hash_map.
        /// @param s The utf8string to be hashed
        /// @return A hash value generated from the given string
        size_t operator()(efd::utf8string s) const;
    };

} // end namespace _STLP_STD_NAME

/// @endcond

#endif
