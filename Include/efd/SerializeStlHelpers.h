// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not
// be copied or disclosed except in accordance with the terms of that
// agreement.
//
//      Copyright (c) 2006-2008 Todd Berkebile.
//      Copyright (c) 1996-2008 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Calabasas, CA 91302
// http://www.emergent.net

#pragma once
#ifndef EE_SERIALIZESTLHELPERS_H
#define EE_SERIALIZESTLHELPERS_H


#include <efd/Serialize.h>
#include <efd/EEBasicString.h>


namespace efd
{

// Some specializations of SerializeObject for common STL types
// Note: For serializing container types see efd/SerializeRoutines.h
namespace Serializer
{
    template< typename CHAR_TYPE >
    inline void SerializeStringHelperObject(
        efd::basic_string<CHAR_TYPE>& io_str,
        efd::Archive& io_archive)
    {
        size_t length = io_str.length();
        SR_As32Bit_Compressed::Serialize(length, io_archive);
        efd::UInt8* pData = io_archive.GetBytes(length*sizeof(CHAR_TYPE));
        if (pData)
        {
            if (io_archive.IsUnpacking())
            {
                io_str.assign((CHAR_TYPE*)pData, length);
            }
            else
            {
                memcpy(pData, io_str.data(), length*sizeof(CHAR_TYPE));
            }
        }
    }

    template<>
    inline void SerializeObject<efd::string>(efd::string& io_str, efd::Archive& io_archive)
    {
        SerializeStringHelperObject<char>(io_str, io_archive);
    }

    template<>
    inline void SerializeObject<efd::wstring>(efd::wstring& io_str, efd::Archive& io_archive)
    {
        SerializeStringHelperObject<wchar>(io_str, io_archive);
    }

    // add std::pair?

} // end namespace Serializer
} // end namespace efd

#endif // EE_SERIALIZESTLHELPERS_H
