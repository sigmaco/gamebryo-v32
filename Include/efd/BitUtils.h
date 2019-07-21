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
#ifndef EE_BITUTILS_H
#define EE_BITUTILS_H

#include <efd/Asserts.h>
#include <efd/UniversalTypes.h>

namespace efd
{
    /**
        Helper functions to perform common bitwise operations.  These mainly exist to improve the
        readability of code using bitwise operations.
    */
    namespace BitUtils
    {
        //////////////////////////////////////////////
        // Mask based methods

        template< typename T >
        inline T SetBits(T i_bitfield, T i_maskBitsToSet)
        {
            return i_bitfield | i_maskBitsToSet;
        }

        template< typename T >
        inline T ClearBits(T i_bitfield, T i_maskBitsToClear)
        {
            return i_bitfield & (~i_maskBitsToClear);
        }

        template< typename T >
        inline T SetBitsOnOrOff(T i_bitfield, T i_maskBitsToChange, bool i_on)
        {
            if (i_on)
            {
                return i_bitfield | i_maskBitsToChange;
            }
            else
            {
                return i_bitfield & (~i_maskBitsToChange);
            }
        }

        template< typename T >
        bool AllBitsAreSet(T i_bitfield, T i_maskBitsToCheck)
        {
            return (i_bitfield & i_maskBitsToCheck) == i_maskBitsToCheck;
        }

        template< typename T >
        bool AnyBitsAreSet(T i_bitfield, T i_maskBitsToCheck)
        {
            return (i_bitfield & i_maskBitsToCheck) != 0;
        }

        template< typename T >
        bool NoBitsAreSet(T i_bitfield, T i_maskBitsToCheck)
        {
            return (i_bitfield & i_maskBitsToCheck) == 0;
        }


        //////////////////////////////////////////////
        // Index based methods

        template< typename T >
        T SetBitByIndex(T i_bitfield, efd::UInt32 i_index)
        {
            EE_ASSERT(i_index < sizeof(i_bitfield)*8);
            // Note: double static_cast is required on VC8.  The static_cast<T>(1) will upcast
            // to T in the case where T is larger than 32bits.  The second static cast will
            // downcast to T in the case where T is less than 32 bits.  This is needed to prevent
            // compile warnings because in VC8 (UInt8 << UInt32) yields a 32bit result.
            return (i_bitfield | static_cast<T>(static_cast<T>(1) << i_index));
        }

        template< typename T >
        T ClearBitByIndex(T i_bitfield, efd::UInt32 i_index)
        {
            EE_ASSERT(i_index < sizeof(i_bitfield)*8);
            // See note in SetBitByIndex concerning the double static_cast
            return (i_bitfield & ~static_cast<T>(static_cast<T>(1) << i_index));
        }

        template< typename T >
        T SetBitOnOrOffByIndex(T i_bitfield, efd::UInt32 i_index, bool i_on)
        {
            EE_ASSERT(i_index < sizeof(i_bitfield)*8);
            // See note in SetBitByIndex concerning the double static_cast
            return SetBitsOnOrOff(i_bitfield, static_cast<T>(static_cast<T>(1) << i_index), i_on);
        }

        template< typename T >
        bool TestBitByIndex(T i_bitfield, efd::UInt32 i_index)
        {
            EE_ASSERT(i_index < sizeof(i_bitfield)*8);
            // See note in SetBitByIndex concerning the double static_cast
            return (i_bitfield & static_cast<T>(static_cast<T>(1) << i_index)) != 0;
        }

        //////////////////////////////////////////////
        // Bit-related helpers

        /**
            Returns the number of bits in the given type.  Useful in templated functions that
            deal with various sizes of plain-old-data fundamental integral types.
            Usage: UInt32 result = GetBitCount< sometype >();
        */
        template< typename T >
        inline efd::UInt32 GetBitCount()
        {
            return sizeof(T) * 8;
        }

        /**
            Given a number of bits within the given word size that you want to preserver this
            determines the maximum bit-shift possible without overflowing those bits.  This
            can be useful in templated functions that deal with various sizes of integral plain-
            old-data types.
            Usage: UInt32 result = MaximumShiftWithoutOverflow< sometype >(countOfBitsToKeep);
        */
        template< typename T >
        inline efd::UInt32 MaximumShiftWithoutOverflow(efd::UInt32 i_NumBits)
        {
            EE_ASSERT(i_NumBits <= sizeof(T) * 8);
            return (GetBitCount<T>() - i_NumBits);
        }

        /**
            Given a number of bits and the position of the least significant bit's index, generate
            a bit mask of the given type.  T should be an integral plain-old-data type.  This is
            useful for generating bit masks at run-time.
            NOTE: As coded this only works for Unsigned types!!!
        */
        template< typename T >
        inline T ComputeBitMask(efd::UInt32 i_NumBits, efd::UInt32 i_LSBPos)
        {
            EE_ASSERT(GetBitCount<T>() >= i_NumBits + i_LSBPos);
            return ((T)-1 >> MaximumShiftWithoutOverflow<T>(i_NumBits) << i_LSBPos);
        }

        /**
            This is much like ComputeBitMask only the mask is generated completely at compile
            time.  As a result it can only be used with constant values, but there is no runtime
            cost as the compiler should replace this entire function with a single constant when
            you generate an optimized build (possibly even in debug builds depending on compiler).
            NOTE: As coded this only works for Unsigned types!!!
        */
        template< typename T, efd::UInt32 i_NumBits, efd::UInt32 i_LSBPos >
        inline T MakeBitMask()
        {
            EE_COMPILETIME_ASSERT(i_NumBits + i_LSBPos <= (sizeof(T) * 8));
            return ((T)-1 >> ((sizeof(T) * 8) - i_NumBits) << i_LSBPos);
        }

    } // end namespace BitUtils

} // end namespace efd

#endif // EE_BITUTILS_H
