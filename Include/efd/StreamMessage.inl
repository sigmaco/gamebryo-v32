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

namespace efd
{

//------------------------------------------------------------------------------------------------
inline void StreamMessage::SetBuffer(const efd::SmartBuffer& i_buffer)
{
    m_archive = Archive(Archive::Unpacking, i_buffer);
}

//------------------------------------------------------------------------------------------------
inline efd::Archive& StreamMessage::GetArchive()
{
    return m_archive;
}

//------------------------------------------------------------------------------------------------
inline efd::Archive& StreamMessage::GetArchive() const
{
    EE_ASSERT(m_archive.IsUnpacking());
    return m_archive;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 StreamMessage::GetBufferSize() const
{
    return m_archive.GetUsedSize();
}

//------------------------------------------------------------------------------------------------
} // end namespace efd
