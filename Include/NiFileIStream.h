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
#ifndef NIFILEISTREAM_H
#define NIFILEISTREAM_H

// define NOMINMAX to avoid all the errors and warnings
// from template <class T> struct limits
#define NOMINMAX

#include <NiSystem.h>
#include <efd/File.h>

#if defined(WIN32) || defined(_XENON)
#pragma warning(push)
#pragma warning(disable: 4244)
#pragma warning(disable: 4996)
#endif

#include <ImfRgba.h>
#include <ImfArray.h>
#include <ImathBox.h>

#include <ImfRgbaFile.h>
#include <ImfTiledRgbaFile.h>
#include <ImfInputFile.h>
#include <ImfTiledInputFile.h>
#include <ImfPreviewImage.h>
#include <ImfChannelList.h>
#include <ImfInt64.h>
#include <ImfHeader.h>
#include <ImfIO.h>

#if defined(WIN32) || defined(_XENON)
#pragma warning(pop)
#endif

class NiFileIStream : public Imf::IStream
{
public:
    NiFileIStream(efd::File *pkFile);
    ~NiFileIStream() {;};

    virtual bool read (char c[], int n);
    virtual Imf::Int64 tellg();
    virtual void seekg(Imf::Int64 pos);
    virtual void clear();

private:
    efd::File* m_pkNiFile;
};

#endif