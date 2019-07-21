// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not
// be copied or disclosed except in accordance with the terms of that
// agreement.
//
//      Copyright (c) 2006-2009 Todd Berkebile.
//      Copyright (c) 1996-2009 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Calabasas, CA 91302
// http://www.emergent.net


namespace efd
{

//------------------------------------------------------------------------------------------------
inline bool Archive::IsPacking() const
{
    return m_fPacking;
}

//------------------------------------------------------------------------------------------------
inline bool Archive::IsUnpacking() const
{
    return !m_fPacking;
}

//------------------------------------------------------------------------------------------------
inline bool Archive::GetError() const
{
    return m_fError;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 Archive::GetCurrentPosition() const
{
    return m_CurrentPos;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 Archive::GetUsedSize() const
{
    return GetCurrentPosition();
}

//------------------------------------------------------------------------------------------------
inline SmartBuffer Archive::GetUsedBuffer()
{
    return m_buffer.MakeWindow(0, GetCurrentPosition());
}

//------------------------------------------------------------------------------------------------
inline const SmartBuffer Archive::GetUsedBuffer() const
{
    return m_buffer.MakeWindow(0, GetCurrentPosition());
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 Archive::GetRemainingSize() const
{
    EE_ASSERT(m_buffer.GetSize() >= GetCurrentPosition());
    return m_buffer.GetSize() - GetCurrentPosition();
}

//------------------------------------------------------------------------------------------------
inline SmartBuffer Archive::GetRemainingBuffer()
{
    return m_buffer.MakeWindow(GetCurrentPosition(), GetRemainingSize());
}

//------------------------------------------------------------------------------------------------
inline const SmartBuffer Archive::GetRemainingBuffer() const
{
    return m_buffer.MakeWindow(GetCurrentPosition(), GetRemainingSize());
}

//------------------------------------------------------------------------------------------------
inline const SmartBuffer& Archive::GetEntireBuffer() const
{
    return m_buffer;
}

//------------------------------------------------------------------------------------------------
inline bool Archive::CheckBytes(efd::UInt32 i_cbSize)
{
    return NULL != PeekBytes(GetCurrentPosition(), i_cbSize);
}

//------------------------------------------------------------------------------------------------
inline efd::Endianness Archive::GetEndianness() const
{
    return m_endianness;
}

//------------------------------------------------------------------------------------------------
inline void Archive::SetEndianness(efd::Endianness val)
{
    EE_ASSERT(0 == GetUsedSize());
    m_endianness = val;
}

//------------------------------------------------------------------------------------------------
inline efd::Endianness Archive::GetHardwareEndianness()
{
    static union { int i; char a[4]; } u = {1};
    return u.a[0] ? Endian_Little : Endian_Big;
}

//------------------------------------------------------------------------------------------------
inline bool Archive::NeedsSwap()
{
    return m_endianness != GetHardwareEndianness();
}

//------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127) // constant conditional
#endif

template<typename T>
void Archive::MaybeSwap(const T& i_value, T& o_result)
{
    if (sizeof(T) == 1 || !NeedsSwap())
    {
        // Must use memcpy here to deal with potential alignment problems:
        memcpy(&o_result, &i_value, sizeof(T));
        return;
    }

    const efd::UInt8* pSource = reinterpret_cast<const efd::UInt8*>(&i_value);
    efd::UInt8* pDest = reinterpret_cast<efd::UInt8*>(&o_result);

    switch (sizeof(T))
    {
    case 8:
        pDest[0] = pSource[7];
        pDest[1] = pSource[6];
        pDest[2] = pSource[5];
        pDest[3] = pSource[4];
        pDest[4] = pSource[3];
        pDest[5] = pSource[2];
        pDest[6] = pSource[1];
        pDest[7] = pSource[0];
        break;
    case 4:
        pDest[0] = pSource[3];
        pDest[1] = pSource[2];
        pDest[2] = pSource[1];
        pDest[3] = pSource[0];
        break;
    case 2:
        pDest[0] = pSource[1];
        pDest[1] = pSource[0];
        break;
    default:
        EE_FAIL("Only valid for POD types.");
        break;
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

//------------------------------------------------------------------------------------------------
} // end namespace efd
