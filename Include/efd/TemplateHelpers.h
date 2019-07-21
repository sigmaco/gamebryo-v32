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
#ifndef EE_TEMPLATEHELPERS_INCLUDE
#define EE_TEMPLATEHELPERS_INCLUDE

#include <efd/UniversalTypes.h>

namespace efd
{
    /**
        SelectStorageForBytes is for use in templated methods that need to devine the correct
        signed or unsigned efd integral type to hold a certain byte size worth of data.  This
        can be helpful if, for example, you need to cast templated parameters to equivalent
        signed or unsigned types in order to perform certain mathematical operations.  An example
        usage might look something like:

        template< typename T = efd::UInt32 >
        class Example
        {
            typedef SelectStorageForBytes<sizeof(T)>::signedType MySignedType;
            typedef SelectStorageForBytes<sizeof(T)>::unsignedType MyUnsignedType;

            MySignedType m_storage;
        };
    */
    //@{
    template< int cbWordSize >
    struct SelectStorageForBytes
    {
    };

    template<>
    struct SelectStorageForBytes<1>
    {
        typedef efd::SInt8 signedType;
        typedef efd::UInt8 unsignedType;
    };
    template<>
    struct SelectStorageForBytes<2>
    {
        typedef efd::SInt16 signedType;
        typedef efd::UInt16 unsignedType;
    };
    template<>
    struct SelectStorageForBytes<4>
    {
        typedef efd::SInt32 signedType;
        typedef efd::UInt32 unsignedType;
    };
    template<>
    struct SelectStorageForBytes<8>
    {
        typedef efd::SInt64 signedType;
        typedef efd::UInt64 unsignedType;
    };
    //@}


    /**
        AreTypesEquivalent is a template structure used to determine if two types are
        exactly equivalent.

        An example usage might look like:
            if (AreTypesEquivalent<T1, T2>::answer)
            {
                // Code that depends on T1 == T2
            }
            else
            {
                // Code that depends on T1 != T2
            }
    */
    //@{
    template <typename T1, typename T2>
    struct AreTypesEquivalent
    {
        enum { answer = false };
    };

    template <typename T1>
    struct AreTypesEquivalent<T1, T1>
    {
        enum { answer = true };
    };
    //@}

} // end namespace efd


#endif
