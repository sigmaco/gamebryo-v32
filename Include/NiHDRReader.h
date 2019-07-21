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
#ifndef NIHDRREADER_H
#define NIHDRREADER_H

#include "NiHDRReaderLibType.h"
#include "NiPixelFormat.h"
#include "NiImageReader.h"
#include <efd/File.h>

class NIHDRREADER_ENTRY NiHDRReader : public NiImageReader
{
public:
    virtual bool CanReadFile(const char* pcFileExtension) const;

    virtual NiPixelData* ReadFile(efd::File& kIst, NiPixelData* pkOptDest);

    virtual bool ReadHeader(efd::File& kIst,
        unsigned int& uiWidth, unsigned int& uiHeight,
        NiPixelFormat& kFormat, bool& bMipmap, unsigned int& uiFaces);

protected:
    // Reads the header of the HDR file.  It is assumed that when this
    // function finishes, the file pointer will be at the beginning of the
    // pixel data.
    bool ReadHeaderInternal(efd::File& kIst, unsigned int& uiWidth,
        unsigned int& uiHeight, bool& bXLeftToRight, bool& bYTopToBottom,
        bool& bRowMajor);

    bool ReadRawFile(efd::File& kIst, unsigned char aucFirstPixel[4],
        unsigned char* pucData, int iRowStride, int iColStride,
        unsigned int uiHeight, unsigned int uiWidth,
        unsigned int uiDPixelSize);

    bool ReadRLEFile(efd::File& kIst, unsigned char aucFirstPixel[4],
        unsigned char* pucData, int iRowStride, int iColStride,
        unsigned int uiHeight, unsigned int uiWidth,
        unsigned int uiDPixelSize);

    static void ConvertRGBEToHalf(unsigned char* pucRGBE,
        unsigned char* pucDest);
    static void ConvertRGBEToFloat(unsigned char* pucRGBE,
        unsigned char* pucDest);
};

#endif // #ifndef NIHDRREADER_H