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
#include <efd/StringUtilities.h>

namespace efd
{

//-------------------------------------------------------------------------------------------------
inline void efd::Sleep(efd::UInt32 milliseconds)
{
    ::Sleep(milliseconds);
}
//-------------------------------------------------------------------------------------------------
inline void efd::YieldThread()
{
    // Preferably, we could call SwitchToThread here, but that requires
    // knowing that your target platform is at least WinNT.
    ::Sleep(0);
}
//---------------------------------------------------------------------------
inline void Prefetch128(void*)
{
    // Intentionally blank at this time.
}
//-------------------------------------------------------------------------------------------------
inline efd::Float32 SelectGE(efd::Float32 condition, efd::Float32 resultIfGreaterThanEqualZero,
    efd::Float32 resultIfLessThanZero)
{
    return condition >= 0 ?
        resultIfGreaterThanEqualZero : resultIfLessThanZero;
}
//-------------------------------------------------------------------------------------------------
inline efd::Float32 SelectGE(efd::SInt32 condition, efd::Float32 resultIfGreaterThanEqualZero,
    efd::Float32 resultIfLessThanZero)
{
    return condition >= 0 ? resultIfGreaterThanEqualZero : resultIfLessThanZero;
}
//-------------------------------------------------------------------------------------------------
inline efd::SInt32 Select(bool condition, efd::SInt32 resultIfTrue, efd::SInt32 resultIfFalse)
{
    return condition ? resultIfTrue : resultIfFalse;
}
//-------------------------------------------------------------------------------------------------
inline efd::Float32 Select(bool condition, efd::Float32 resultIfTrue,
    efd::Float32 resultIfFalse)
{
    return condition ? resultIfTrue : resultIfFalse;
}
//-------------------------------------------------------------------------------------------------
inline efd::UInt8 Int32ToUInt8(efd::SInt32 value)
{
    EE_ASSERT(value >= 0);
    EE_ASSERT(value <= UCHAR_MAX);
    return (efd::UInt8)(value & 0xFF);
}
//-------------------------------------------------------------------------------------------------
inline efd::UInt16 Int32ToUInt16(efd::SInt32 value)
{
    EE_ASSERT(value >= 0);
    EE_ASSERT(value <= USHRT_MAX);
    return (efd::UInt16)(value & 0xFFFF);
}
//-------------------------------------------------------------------------------------------------
inline efd::UInt32 Int32ToUInt32(efd::SInt32 value)
{
    return (efd::UInt32)value;
}
//-------------------------------------------------------------------------------------------------
inline efd::SInt8 Int32ToInt8(efd::SInt32 value)
{
    EE_ASSERT(value >= SCHAR_MIN);
    EE_ASSERT(value <= SCHAR_MAX);

    // Twos complement numbers fully extend the sign bit. If we pass the
    // assertions above, we are within range and a mask is sufficient.
    return (efd::SInt8)(value & 0xFF);
}
//-------------------------------------------------------------------------------------------------
inline efd::SInt16 Int32ToInt16(efd::SInt32 value)
{
    EE_ASSERT(value >= SHRT_MIN);
    EE_ASSERT(value <= SHRT_MAX);

    // Twos complement numbers fully extend the sign bit. If we pass the
    // assertions above, we are within range and a mask is sufficient.
    return (efd::SInt16)(value & 0xFFFF);
}
//-------------------------------------------------------------------------------------------------
inline unsigned long GetCurrentThreadId()
{
    return (unsigned long) ::GetCurrentThreadId();
}
//-------------------------------------------------------------------------------------------------
inline efd::Char* Getcwd(efd::Char* buffer, size_t maxlen)
{
    return _getcwd(buffer, (int)maxlen);
}
//-------------------------------------------------------------------------------------------------
#if defined(EE_EFD_CONFIG_DEBUG)
inline void WriteToStdErr(const efd::Char* pText)
{
    fputs(pText, stderr);
}
#endif // EE_EFD_CONFIG_DEBUG
//-------------------------------------------------------------------------------------------------
inline efd::UInt64 GetPid()
{
    return _getpid();
}
//-------------------------------------------------------------------------------------------------
} // end namespace efd
