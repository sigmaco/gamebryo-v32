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
#ifndef EE_TinyXML_h
#define EE_TinyXML_h

#include <efd/UniversalTypes.h>
#include <efd/utf8string.h>
#include <efd/ParseHelper.h>
#include <efd/efdLibType.h>

#include <efdXML/tinyxml.h>


namespace efd
{

namespace XMLUtils
{

    /**
        Parse an xml attribute value as a utf8string.

        @param[in] attrs All the attributes for the current node
        @param[in] name The specific attribute whose name you want to parse
        @param[out] o_result The utf8string for the resulting attribute data
        @return bool True if the given attribute exists and can be parsed as the requested type
    */
    bool EE_EFD_ENTRY GetAttribute(const TiXmlAttributeSet& attrs,
        const EE_TIXML_STRING& name,
        efd::utf8string& o_result);

    /**
        Templated function to parse an xml attribute value as a specific type of data.

        @param[in] attrs All the attributes for the current node
        @param[in] name The specific attribute whose name you want to parse
        @param[out] o_result The templated type for the resulting attribute data
        @return bool True if the given attribute exists and can be parsed as the requested type
    */
    template< typename T >
    bool GetAttribute(const TiXmlAttributeSet& attrs,
        const EE_TIXML_STRING& name,
        T& o_result)
    {
        bool retval = false;

        efd::utf8string strValue;

        if (GetAttribute(attrs, name, strValue))
            retval = efd::ParseHelper< T >::FromString(strValue, o_result);

        return retval;
    }

} // end namespace XMLUtils

} // end namespace efd

#endif // EE_TinyXML_h
