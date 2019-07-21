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

//------------------------------------------------------------------------------------------------
inline efd::UInt8* efd::GrowableBuffer::GetBuffer()
{
    return m_pData;
}

//------------------------------------------------------------------------------------------------
inline const efd::UInt8* efd::GrowableBuffer::GetBuffer() const
{
    return m_pData;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 efd::GrowableBuffer::GetSize() const
{
    return m_cbData;
}

//------------------------------------------------------------------------------------------------
inline bool efd::GrowableBuffer::CanGrow() const
{
    return m_fCanGrow;
}

//------------------------------------------------------------------------------------------------
inline bool efd::GrowableBuffer::OwnsBuffer() const
{
    return m_fOwnsBuffer;
}

//------------------------------------------------------------------------------------------------
inline bool efd::GrowableBuffer::IsExclusive() const
{
    return GetRefCount() == 1;
}

//------------------------------------------------------------------------------------------------
