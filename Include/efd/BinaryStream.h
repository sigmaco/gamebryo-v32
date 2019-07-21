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
#ifndef EE_BINARYSTREAM_H
#define EE_BINARYSTREAM_H

#include <efd/MemObject.h>
#include <efd/BinaryStreamMacro.h>

namespace efd
{

/**
    This abstract base class for all binary streams, such as memory streams or files, is designed
    to wrap platform-dependent implementations of streaming systems.

    Derived classes need to implement some particular behavior to support endian swapping.  Such
    details are described in the documentation about how to derive from BinaryStream.  By default,
    all files will be written in the endianness of the current platform.
*/
class EE_EFD_ENTRY BinaryStream : public MemObject
{
public:
    /// This abstract base class has no useful constructors.
    BinaryStream();

    /// Virtual destructor.
    virtual ~BinaryStream();

    /**
        For streams that may or may not always be ready to use, such as files, this operator
        returns true if the stream is ready to be written to or read from, or false if the stream
        is not ready to use.

        Streams that have no such limitations always return true.
    */
    virtual operator bool() const = 0;

    /**
        Advances the current read/write position of the stream by the number of bytes given by
        iNumBytes.

        Passing a negative value into iNumBytes will move the current position back towards the
        beginning of the file, while a positive value will advance the position towards the end of
        the file.

        @param iNumBytes Number of bytes to move (forward or backward) the current read/write
            position of the stream.
        @return true if successful, false otherwise.
    */
    virtual bool Seek(int iNumBytes) = 0;

    /**
        Returns the current read or write position in the stream.

        @return Current read/write position in the stream.
    */
    virtual unsigned int GetPosition() const;

    /**
        Endian-aware struct reading.

        This method reads uiTotalBytes from the stream and stores them into pvBuffer, which must
        be allocated before this call.  If endian-swapping needs to occur, then it will use the
        array puiComponentSizes of size uiNumComponents for information about how the data is
        structured.  It will then do the endian-swapping based on those component sizes.  If there
        are fewer than uiTotalBytes available in the stream to be read, this function will only
        read as many bytes as are available.

        @param pvBuffer Data read from the stream is stored into this buffer.
        @param uiTotalBytes Number of bytes of data to be read from the stream.
        @param puiComponentSizes Array of component size information of size uiNumComponents.
        @param uiNumComponents Number of components in the puiComponentSizes array.
        @return Number of bytes successfully read into pvBuffer.
    */
    inline unsigned int BinaryRead(
        void* pvBuffer,
        unsigned int uiTotalBytes,
        unsigned int* puiComponentSizes,
        unsigned int uiNumComponents = 1);

    /**
        Endian-aware struct writing.

        This method writes uiTotalBytes from pvBuffer.  If endian-swapping needs to occur, then it
        will use the array puiComponentSizes of size uiNumComponents for information about how
        pvBuffer is structured.  It will do the endian-swapping based on those component sizes.
        Because endian-swapping will occur and pvBuffer will be modified, pvBuffer should not
        point to the original data.

        @param pvBuffer Data written to the stream originates from this buffer.
        @param uiTotalBytes Number of bytes of data to be written to the stream.
        @param puiComponentSizes Array of component size information of size uiNumComponents.
        @param uiNumComponents Number of components in the puiComponentSizes array.
        @return Number of bytes that were successfully written to the stream.
    */
    inline unsigned int BinaryWrite(
        const void* pvBuffer,
        unsigned int uiTotalBytes,
        unsigned int* puiComponentSizes,
        unsigned int uiNumComponents = 1);

    /**
        Read uiBytes of raw bytes from the stream and put them into pvBuffer, without considering
        endianness.

        If there are fewer than uiBytes available in the stream to be read, this function will
        only read as many bytes as are available.

        @note Memory for pvBuffer must have been allocated before this call.

        @param pvBuffer Data read from the stream is stored into this buffer.
        @param uiBytes Number of bytes of data to be read from the stream.
        @return Number of bytes successfully read into pvBuffer.
    */
    virtual unsigned int Read(
        void *pvBuffer,
        unsigned int uiBytes);

    /**
        Write uiBytes raw bytes to the stream from pvBuffer.

        @param pvBuffer Data written to the stream originates from this buffer.
        @param uiBytes Number of bytes of data to be written to the stream.
        @return Number of bytes successfully written to the stream.
    */
    virtual unsigned int Write(
        const void *pvBuffer,
        unsigned int uiBytes);

    /**
        Read bytes from the stream into pcBuffer until a newline character is reached, the end
        of the stream is reached, or (uiMaxBytes - 1) bytes have been read.

        The final newline character, if it exists, is not copied into pcBuffer, but pcBuffer is
        terminated with a "\0".

        @note Memory for pcBuffer must have been allocated before this call.

        @param pvBuffer Data read from the stream is stored into this buffer.
        @param uiMaxBytes Maximum number of bytes of data to be read from the stream.
        @return Number of bytes successfully read from the file (including any newline or return
            characters, even though they are not placed in pcBuffer).  If the return value is 0,
            then the end of the file was reached.
    */
    unsigned int GetLine(
        char* pvBuffer,
        unsigned int uiMaxBytes);

    /**
        Writes pcBuffer, a NULL-terminated string, to the stream.

        @note The final "\0" is not written to the stream.

        @param pvBuffer Data written to the stream originates from this buffer.
        @return Number of bytes successfully written.
    */
    unsigned int PutS(const char* pvBuffer);

    /**
        Set whether endian swapping is needed.

        The base class has two function pointers that point to the current read and write
        functions for a given binary stream.  Derived functions should set those function pointers
        to either raw I/O functions or to functions that endian swap, based on the value bDoSwap.

        @param bDoSwap Whether endian swapping is needed.
    */
    virtual void SetEndianSwap(bool bDoSwap) = 0;

    //@{
    /**
        Access the endian match hint, a static setting.

        The endian match hint gives a hint to derived classes whether or not they should load
        files that do not match the current platform's endianness.  By default, it is false.  If
        set to true, then streaming systems which respect this hint (such as Gamebryo's
        NiActorManager and NiStream) will fail to load files that are not in the native endian
        format.
    */
    static bool GetEndianMatchHint();
    static void SetEndianMatchHint(bool bForceMatch);
    //@}

    /**
        Writes a null-terminated (C-style) string to the stream.

        A C-style string consists of a 4-byte length, followed by length characters from the
        stream.  No null-terminator is written to the stream.

        If the input string is NULL or the empty string "\0", then no characters are written (only
        a 4-byte zero).  When such as string is read with ReadCString, it will return NULL.

        @param pcString Null-terminated (C-style) string.
    */
    void WriteCString(const char* pcString);

    /**
        Reads a 4-byte length from the stream, allocates a string of (length + 1) bytes, reads
        length bytes from the stream, and then null-terminates the string.

        @return The allocated string.  The caller is responsible for ultimately freeing the
            memory.  If the string read in was of length zero, the function will return NULL.
    */
    char* ReadCString();

protected:
    // Define function pointers.  (Mimic "function pointer to a member function" by passing along
    // the "this" pointer.)
    typedef unsigned int (*BINARYSTREAM_READFN)(
        BinaryStream* pkThis,
        void* pvBuffer,
        unsigned int uiBytes,
        unsigned int* puiComponentSizes,
        unsigned int uiNumComponents);
    typedef unsigned int (*BINARYSTREAM_WRITEFN)(
        BinaryStream* pkThis,
        const void* pvBuffer,
        unsigned int uiBytes,
        unsigned int* puiComponentSizes,
        unsigned int uiNumComponents);

    // Convenience function for derived classes.
    static void DoByteSwap(
        void* pvData,
        unsigned int uiBytes,
        unsigned int* puiComponentSizes,
        unsigned int uiNumComponents);

    static bool ms_bEndianMatchHint;
    unsigned int m_uiAbsoluteCurrentPos;

    BINARYSTREAM_READFN m_pfnRead;
    BINARYSTREAM_WRITEFN m_pfnWrite;
};

//--------------------------------------------------------------------------------------------------
/// @name Inline load/save routines for native data from BinaryStream.h
//@{
///
template <class T>
inline void StreamLoadBinary(BinaryStream& binstream, T& value);

template <class T>
inline void StreamLoadBinary(BinaryStream& binstream, T* value, unsigned int uiNumEls);

template <class T>
inline void StreamSaveBinary(BinaryStream& binstream, T& value);

template <class T>
inline void StreamSaveBinary(BinaryStream& binstream, T* value, unsigned int uiNumEls);
//@}
//--------------------------------------------------------------------------------------------------

} // end namespace efd

#include <efd/BinaryStream.inl>

#endif // EE_BINARYSTREAM_H
