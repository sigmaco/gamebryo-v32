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
#ifndef EE_WIN32FILE_H
#define EE_WIN32FILE_H

#include <efd/FileCommon.h>
#include <efd/BinaryStreamMacro.h>

namespace efd
{

class EE_EFD_ENTRY Win32File : public efd::FileCommon
{
    /// @cond EMERGENT_INTERNAL

     EE_DeclareDerivedBinaryStream();

    /// @endcond

public:
    /**
        Constructor.

        Opens the file pcName in mode eMode.

        The size of the internal buffer used to cache data from the file is uiBufferSize.  This
        value should generally be left at the default value unless memory is tight.

        @param pcName Filename.
        @param eMode Open mode (read versus write versus append).
        @param uiBufferSize Buffer size (defaults to 32768).
        @param flushOnWrite if false buffer writes until we fill the buffer. If true, flush after
               every write call.
    */
    Win32File(
        const char* pcName,
        OpenMode eMode,
        unsigned int uiBufferSize = 32768,
        bool flushOnWrite = false);

    /// Virtual destructor.
    virtual ~Win32File();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual bool Seek(int offset, SeekOrigin seekFrom);
    virtual bool Flush();
    virtual unsigned int GetFileSize() const;
    virtual void SetEndianSwap(bool bDoSwap);

protected:

    /*
        These two methods are passed to the BinaryStreamMacro code to perform
        the raw reads and writes between the file and a buffer.
    */
    virtual unsigned int FileRead(void* pvBuffer, unsigned int uiBytes);
    virtual unsigned int FileWrite(const void* pvBuffer, unsigned int uiBytes);

    /*
        Read a specified number of bytes of data from a File to a buffer.
          pvBuffer : Buffer into which to stream data from the File.
          uiBytes : Number of bytes of data to be read.
          return : Number of bytes actually read (may be less than uiBytes).
    */
    unsigned int DiskRead(void* pvBuffer, unsigned int uiBytes);

    /*
        Write a specified number of bytes of data from a buffer to a File.
          pvBuffer : Buffer of data to be written.
          uiBytes : Number of bytes of data to be written.
          return : Number of bytes actually written (may be less than uiBytes).
    */
    unsigned int DiskWrite(const void* pvBuffer, unsigned int uiBytes);


    // Buffer allocation size.
    unsigned int m_uiBufferAllocSize;

    // Size of how many bytes have been read.
    unsigned int m_uiBufferReadSize;

    // Position in the File.
    unsigned int m_uiPos;

    // Pointer to buffer to hold data streamed in from a File (or streamed out to a File).
    char* m_pBuffer;

    // Pointer to File instance.
    FILE* m_pFile;

    bool m_bFlushOnWrite;
};

}   // End namespace efd.

#endif  // EE_WIN32FILE_H
