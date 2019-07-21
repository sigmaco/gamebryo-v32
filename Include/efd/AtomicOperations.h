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
#ifndef EE_ATOMICOPERATIONS_H
#define EE_ATOMICOPERATIONS_H

#include <efd/OS.h>
#include <efd/UniversalTypes.h>
#include <efd/Asserts.h>

namespace efd
{
/// atomically increment a variable
inline efd::SInt32 AtomicIncrement(efd::SInt32 &value);

/// atomically decrement a variable
inline efd::SInt32 AtomicDecrement(efd::SInt32 &value);

/// atomically increment a variable
inline efd::UInt32 AtomicIncrement(efd::UInt32 &value);

/// atomically decrement a variable
inline efd::UInt32 AtomicDecrement(efd::UInt32 &value);

/// atomically increment a variable
inline efd::SInt32 AtomicIncrement(volatile efd::SInt32 &value);

/// atomically decrement a variable
inline efd::SInt32 AtomicDecrement(volatile efd::SInt32 &value);

/// atomically increment a variable
inline efd::UInt32 AtomicIncrement(volatile efd::UInt32 &value);

/// atomically decrement a variable
inline efd::UInt32 AtomicDecrement(volatile efd::UInt32 &value);


#if defined(__SPU__)
    /// atomically increment a variable
    inline size_t AtomicIncrement(size_t &value);

    /// atomically decrement a variable
    inline size_t AtomicDecrement(size_t &value);

    /// atomically increment a variable
    inline size_t AtomicIncrement(volatile size_t &value);

    /// atomically decrement a variable
    inline size_t AtomicDecrement(volatile size_t &value);
#endif

#if defined(EE_ARCH_64) || defined(EE_PLATFORM_PS3)
    /// atomically increment a variable
    inline efd::SInt64 AtomicIncrement(efd::SInt64 &value);

    /// atomically decrement a variable
    inline efd::SInt64 AtomicDecrement(efd::SInt64 &value);

    /// atomically increment a variable
    inline efd::UInt64 AtomicIncrement(efd::UInt64 &value);

    /// atomically decrement a variable
    inline efd::UInt64 AtomicDecrement(efd::UInt64 &value);

    /// atomically increment a variable
    inline efd::SInt64 AtomicIncrement(volatile efd::SInt64 &value);

    /// atomically decrement a variable
    inline efd::SInt64 AtomicDecrement(volatile efd::SInt64 &value);

    /// atomically increment a variable
    inline efd::UInt64 AtomicIncrement(volatile efd::UInt64 &value);

    /// atomically decrement a variable
    inline efd::UInt64 AtomicDecrement(volatile efd::UInt64 &value);
#endif

    /// @name Atomic compare-and-swap operations
    //@{

    /**
        Performs an atomic compare-and-swap (CAS) operation on the specified pointer values.

        In pseudocode, this function performs the following operation:
        @code
           atomic
           {
               void* pOldValue = *ppDestination;
               if (pOldValue == pComparand)
                   *ppDestination = pExchange;
               return pOldValue;
           }
        @endcode

        This operation includes a memory barrier.

        @param ppDestination The memory location tested and potentially modified
        @param pComparand The value to test against *ppDestination
        @param pExchange The new value written to *ppDestination if the comparison passed
        @return void* The initial value of *ppDestination
    */
    inline void* AtomicCompareAndSwap(
        void* volatile* ppDestination,
        void* pComparand,
        void* pExchange);

    /**
        Performs an atomic compare-and-swap (CAS) operation on the specified 32-bit values.

        In pseudocode, this function performs the following operation:
        @code
           atomic
           {
               UInt32 oldValue = *pDestination;
               if (oldValue == comparand)
                   *pDestination = exchange;
               return oldValue;
           }
        @endcode

        This operation includes a memory barrier.

        @param pDestination The memory location tested and potentially modified
        @param comparand The value to test against *pDestination
        @param exchange The new value written to *pDestination if the comparison passed
        @return UInt32 The initial value of *pDestination
    */
    inline efd::UInt32 AtomicCompareAndSwap(
        efd::UInt32 volatile* pDestination,
        efd::UInt32 comparand,
        efd::UInt32 exchange);

#if defined(EE_PLATFORM_PS3) || defined(EE_PLATFORM_XBOX360) || \
    defined(EE_ARCH_64)

    /**
        Performs an atomic compare-and-swap (CAS) operation on the specified 64-bit values.

        In pseudocode, this function performs the following operation:
        @code
           atomic
           {
               UInt64 oldValue = *pDestination;
               if (oldValue == comparand)
                   *pDestination = exchange;
               return oldValue;
           }
        @endcode

        This operation includes a memory barrier.

        @param pDestination The memory location tested and potentially modified
        @param comparand The value to test against *pDestination
        @param exchange The new value written to *pDestination if the comparison passed
        @return UInt64 The initial value of *pDestination
    */
    inline efd::UInt64 AtomicCompareAndSwap(
        efd::UInt64 volatile* pDestination,
        efd::UInt64 comparand,
        efd::UInt64 exchange);
#endif


    //@}

/**
    This class contains various atomic helper template methods that ease the use of the atomic
    operations.
  */
class Atomic
{
public:
    /**
        Performs an atomic compare-and-swap (CAS) operation on the specified values.

        In pseudocode, this function performs the following operation:
        @code
           atomic
           {
               UInt32 oldValue = *pDestination;
               if (oldValue == comparand)
                   *pDestination = exchange;
               return oldValue;
           }
        @endcode

        This operation includes a memory barrier.

        @param pDestination The memory location tested and potentially modified
        @param comparand The value to test against *pDestination
        @param exchange The new value written to *pDestination if the comparison passed
        @return T The initial value of *pDestination
    */
    template <typename T>
    static inline T CompareAndSwapReturnInit(volatile T* pDestination, T comparand, T exchange);

    /**
        Performs an atomic compare-and-swap (CAS) operation on the specified values.

        In pseudocode, this function performs the following operation:
        @code
           atomic
           {
               UInt32 oldValue = *pDestination;
               if (oldValue == comparand)
               {
                   *pDestination = exchange;
                   return true;
               }
               else
               {
                   return false;
               }
           }
        @endcode

        This operation includes a memory barrier.

        @param pDestination The memory location tested and potentially modified
        @param comparand The value to test against *pDestination
        @param exchange The new value written to *pDestination if the comparison passed
        @return bool True if the exchange took place
    */
    template <typename T>
    static inline bool CompareAndSwap(volatile T* pDestination, T comparand, T exchange);

    /// Sets a memory location to a value atomically (with a memory barrier)
    template <typename T>
    static inline void SetValue(volatile T* pLocation, T newValue);
private:
    template <int Size, typename T>
    struct SelectMatchingUIntBySize;

#if defined(EE_PLATFORM_PS3) || defined(EE_PLATFORM_XBOX360) || (_WIN32_WINNT >= 0x0502) || \
    defined(EE_ARCH_64)

    template <typename T>
    struct SelectMatchingUIntBySize<8, T>
    {
        typedef UInt64 Result;
    };
#endif

    template <typename T>
    struct SelectMatchingUIntBySize<4, T>
    {
        typedef UInt32 Result;
    };
};

} // end namespace efd

// Include the platform specific inline functions
#include EE_PLATFORM_SPECIFIC_INCLUDE(efd,AtomicOperations,inl)

// Include the cross-platform inline functions
#include <efd/AtomicOperations.inl>

#endif // EE_ATOMICOPERATIONS_H

