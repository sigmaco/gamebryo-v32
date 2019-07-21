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
#ifndef NIBINARYSTREAM_H
#define NIBINARYSTREAM_H

#include <efd/Endian.h>
#include <efd/BinaryStream.h>

#if !defined(EE_REMOVE_LEGACY_NI)
#define NiBinaryStream efd::BinaryStream

#define NiDeclareDerivedBinaryStream   EE_DeclareDerivedBinaryStream
#define NiImplementDerivedBinaryStream EE_ImplementDerivedBinaryStream

//--------------------------------------------------------------------------------------------------
template <class T>
void NiStreamLoadBinary(efd::BinaryStream& binstream, T& value)
{
    efd::BinaryStreamLoad(binstream, &value, 1);
}

//--------------------------------------------------------------------------------------------------
template <class T>
void NiStreamLoadBinary(efd::BinaryStream& binstream, T* value, unsigned int uiNumEls)
{
    efd::BinaryStreamLoad(binstream, value, uiNumEls);
}

//--------------------------------------------------------------------------------------------------
template <class T>
void NiStreamSaveBinary(efd::BinaryStream& binstream, T& value)
{
    efd::BinaryStreamSave(binstream, &value, 1);
}

//--------------------------------------------------------------------------------------------------
template <class T>
void NiStreamSaveBinary(efd::BinaryStream& binstream, T* value, unsigned int uiNumEls)
{
    efd::BinaryStreamSave(binstream, value, uiNumEls);
}
#endif // !defined(EE_REMOVE_LEGACY_NI)

//--------------------------------------------------------------------------------------------------

#endif // NIBINARYSTREAM_H
