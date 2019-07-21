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
#ifndef EE_BINARYLOADSAVE_H
#define EE_BINARYLOADSAVE_H

#include <efd/BinaryStream.h>
#include <efd/Asserts.h>

namespace efd
{

/// @name Inline load/save routines for endian-aware streams from BinaryLoadSave.h

//@{

//--------------------------------------------------------------------------------------------------
template <class T>
void BinaryStreamLoad (BinaryStream& is, T* pValue,
    unsigned int uiNumEls = 1)
{
    EE_ASSERT(uiNumEls > 0);
    unsigned int uiSize = sizeof(T);
    unsigned int uiBytesToRead = sizeof(T) * uiNumEls;
    EE_VERIFYEQUALS(
        is.BinaryRead(pValue, uiBytesToRead, &uiSize, 1),
        uiBytesToRead);
}

//--------------------------------------------------------------------------------------------------
inline void BinaryStreamLoad (BinaryStream& is, void* pvValue,
    unsigned int uiNumEls, unsigned int* puiComponentSizes,
    unsigned int uiNumComponents = 1)
{
    EE_ASSERT(uiNumEls > 0);
    EE_ASSERT(puiComponentSizes != NULL);
    EE_ASSERT(uiNumComponents > 0);

    unsigned int uiBytesToRead = 0;
    {
        for (unsigned int uiComp = 0; uiComp < uiNumComponents; uiComp++)
        {
            unsigned int uiElSize = puiComponentSizes[uiComp];
            uiBytesToRead += uiElSize;
            EE_ASSERT(uiElSize == 1 || uiElSize == 2 ||
                uiElSize == 4 || uiElSize == 8);
        }
    }
    uiBytesToRead *= uiNumEls;
    EE_ASSERT(uiBytesToRead != 0);

    EE_VERIFYEQUALS(
        is.BinaryRead(
            pvValue, uiBytesToRead, puiComponentSizes, uiNumComponents),
        uiBytesToRead);
}

//--------------------------------------------------------------------------------------------------
template <class T>
void BinaryStreamLoadEnum (BinaryStream& is, T* pValue)
{
    int iDummy;
    unsigned int uiBytesToRead = sizeof(int);
    EE_VERIFYEQUALS(
        is.BinaryRead(&iDummy, uiBytesToRead, &uiBytesToRead, 1),
        uiBytesToRead);

    *pValue = (T)iDummy;
}

//--------------------------------------------------------------------------------------------------
template <class T>
void BinaryStreamSave (BinaryStream& os, const T* pValue,
    unsigned int uiNumEls = 1)
{
    EE_ASSERT(uiNumEls > 0);
    unsigned int uiSize = sizeof(T);
    unsigned int uiBytesToWrite = uiSize * uiNumEls;
    EE_VERIFYEQUALS(
        os.BinaryWrite(pValue, uiBytesToWrite, &uiSize, 1),
        uiBytesToWrite);
}

//--------------------------------------------------------------------------------------------------
inline void BinaryStreamSave (BinaryStream& os, const void* pvValue,
    unsigned int uiNumEls, unsigned int* puiComponentSizes,
    unsigned int uiNumComponents)
{
    EE_ASSERT(uiNumEls != 0);
    EE_ASSERT(puiComponentSizes != NULL);
    EE_ASSERT(uiNumComponents > 0);

    unsigned int uiBytesToWrite = 0;
    for (unsigned int uiComp = 0; uiComp < uiNumComponents; uiComp++)
    {
        unsigned int uiElSize = puiComponentSizes[uiComp];
        uiBytesToWrite += uiElSize;
        EE_ASSERT(uiElSize == 1 || uiElSize == 2 ||
            uiElSize == 4 || uiElSize == 8);
    }
    uiBytesToWrite *= uiNumEls;

    EE_VERIFYEQUALS(
        os.BinaryWrite(
            pvValue, uiBytesToWrite, puiComponentSizes, uiNumComponents),
        uiBytesToWrite);
}

//--------------------------------------------------------------------------------------------------
template <class T>
void BinaryStreamSaveEnum (BinaryStream& os, const T& value)
{
    unsigned int uiBytesToWrite = sizeof(int);
    EE_VERIFYEQUALS(
        os.BinaryWrite(&value, uiBytesToWrite, &uiBytesToWrite, 1),
        uiBytesToWrite);
}

//@}

} // end namespace efd

#endif // EE_BINARYLOADSAVE_H
