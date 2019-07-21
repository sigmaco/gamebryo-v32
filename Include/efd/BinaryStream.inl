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

#include <efd/BinaryLoadSave.h>

namespace efd
{

//--------------------------------------------------------------------------------------------------
// Inline load/save routines for native data.
//--------------------------------------------------------------------------------------------------
template <class T>
inline void StreamLoadBinary(BinaryStream& binstream, T& value)
{
    BinaryStreamLoad(binstream, &value, 1);
}

//--------------------------------------------------------------------------------------------------
template <class T>
inline void StreamLoadBinary(BinaryStream& binstream, T* value, unsigned int uiNumEls)
{
    BinaryStreamLoad(binstream, value, uiNumEls);
}

//--------------------------------------------------------------------------------------------------
template <class T>
inline void StreamSaveBinary(BinaryStream& binstream, T& value)
{
    BinaryStreamSave(binstream, &value, 1);
}

//--------------------------------------------------------------------------------------------------
template <class T>
inline void StreamSaveBinary(BinaryStream& binstream, T* value, unsigned int uiNumEls)
{
    BinaryStreamSave(binstream, value, uiNumEls);
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
inline unsigned int BinaryStream::BinaryRead(void* pvBuffer,
    unsigned int uiTotalBytes, unsigned int* puiComponentSizes,
    unsigned int uiNumComponents)
{
    unsigned int uiBytesRead = m_pfnRead(this, pvBuffer, uiTotalBytes,
        puiComponentSizes, uiNumComponents);
    m_uiAbsoluteCurrentPos += uiBytesRead;
    return uiBytesRead;
}

//--------------------------------------------------------------------------------------------------
inline unsigned int BinaryStream::BinaryWrite(const void* pvBuffer,
    unsigned int uiTotalBytes, unsigned int* puiComponentSizes,
    unsigned int uiNumComponents)
{
    unsigned int uiBytesWritten = m_pfnWrite(this, pvBuffer, uiTotalBytes,
        puiComponentSizes, uiNumComponents);
    m_uiAbsoluteCurrentPos += uiBytesWritten;
    return uiBytesWritten;
}

//--------------------------------------------------------------------------------------------------

} // end namespace efd
