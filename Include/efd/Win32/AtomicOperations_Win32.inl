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

#include <direct.h>
#include <process.h>
#include <efd/Asserts.h>

namespace efd
{

//-------------------------------------------------------------------------------------------------
inline efd::SInt32 AtomicIncrement(efd::SInt32& value)
{
    return InterlockedIncrement((LONG*)&value);
}
//-------------------------------------------------------------------------------------------------
inline efd::SInt32 AtomicDecrement(efd::SInt32& value)
{
    return InterlockedDecrement((LONG*)&value);
}
//-------------------------------------------------------------------------------------------------
inline efd::SInt32 AtomicIncrement(volatile efd::SInt32& value)
{
    return InterlockedIncrement((volatile LONG*)&value);
}
//-------------------------------------------------------------------------------------------------
inline efd::SInt32 AtomicDecrement(volatile efd::SInt32& value)
{
    return InterlockedDecrement((volatile LONG*)&value);
}
//-------------------------------------------------------------------------------------------------
inline efd::UInt32 AtomicIncrement(efd::UInt32& value)
{
    return InterlockedIncrement((LONG*)&value);
}
//-------------------------------------------------------------------------------------------------
inline efd::UInt32 AtomicDecrement(efd::UInt32& value)
{
    EE_ASSERT(value > 0);
    return InterlockedDecrement((LONG*)&value);
}
//-------------------------------------------------------------------------------------------------
inline efd::UInt32 AtomicIncrement(volatile efd::UInt32& value)
{
    return InterlockedIncrement((volatile LONG*)&value);
}
//-------------------------------------------------------------------------------------------------
inline efd::UInt32 AtomicDecrement(volatile efd::UInt32& value)
{
    EE_ASSERT(value > 0);
    return InterlockedDecrement((volatile LONG*)&value);
}
//-------------------------------------------------------------------------------------------------
inline void* AtomicCompareAndSwap(
    void* volatile* ppDestination,
    void* pComparand,
    void* pExchange)
{
    return InterlockedCompareExchangePointer(ppDestination, pExchange, pComparand);
}
//-------------------------------------------------------------------------------------------------
inline efd::UInt32 AtomicCompareAndSwap(
    efd::UInt32 volatile* pDestination,
    efd::UInt32 comparand,
    efd::UInt32 exchange)
{
    return InterlockedCompareExchange(
        reinterpret_cast<LONG volatile*>(pDestination),
        static_cast<LONG>(exchange),
        static_cast<LONG>(comparand));
}
//-------------------------------------------------------------------------------------------------
#if 0 // (_WIN32_WINNT >= 0x0502)
inline efd::UInt64 AtomicCompareAndSwap(
    efd::UInt64 volatile* pDestination,
    efd::UInt64 comparand,
    efd::UInt64 exchange)
{
    return InterlockedCompareExchange64(
        reinterpret_cast<LONGLONG volatile*>(pDestination),
        static_cast<LONGLONG>(exchange),
        static_cast<LONGLONG>(comparand));
}
#endif
//-------------------------------------------------------------------------------------------------

} // end namespace efd
