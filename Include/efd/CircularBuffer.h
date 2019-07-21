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
#ifndef EE_CIRCULARBUFFER_H
#define EE_CIRCULARBUFFER_H

#include <efd/efdLibType.h>
#include <efd/UniversalTypes.h>

namespace efd
{
/**
    This class is an implementation of a circular or ring buffer.  CircularBuffer always leaves
    1 byte open so that it can distinguish between empty and full.  If CircularBuffer is  used in
    a single reader/single writer case no lock should be necessary.  The reader only ever writes
    to the read position and the writer only ever writes to the write position.  This leaves the
    buffer always in a valid state even if it is being both read and written to at the same time.
    In these cases only valid data is read, but either not all of the data is read/written.  The
    next call to Read/Write will pick up at the appropriate place.
*/
class EE_EFD_ENTRY CircularBuffer
{
public:

    /// @name Construction and Destruction
    //@{
    CircularBuffer(efd::UInt32 maxBytes);
    virtual ~CircularBuffer();
    //@}

    /// Get the number of bytes waiting to be read from the CircularBuffer.
    efd::UInt32 BytesAvailableToRead();
    /// Get the number of bytes free to be written to in the CircularBuffer.
    efd::UInt32 BytesAvailableToWrite();

    /**
        Write buffer into the CircularBuffer.
        @param pBuffer the buffer to write into the CircularBuffer.
        @param size the size in bytes of the buffer to write.
        @return: the number of bytes actually written.  Note: this may be less that the number of
            bytes specified by size or 0 if the CircularBuffer is full.
    */
    efd::UInt32 Write(efd::UInt8* pBuffer, efd::UInt32 size);

    /**
        Read the contents of CircularBuffer into pBuffer.
        @param pBuffer the buffer to read into.
        @param size the size in bytes of the buffer to read.
        @return: the number of bytes actually read.  Note: this may be less that the number of
        bytes specified by size or 0 if the CircularBuffer is empty.
    */
    efd::UInt32 Read(efd::UInt8* pBuffer, efd::UInt32 size);

    /**
        Set the read position of the CircularBuffer.
        @param absoluteByte absolute position to set read position to.
    */
    bool AdvanceReadTo(UInt32 absoluteByte);

    /**
        Set the write position of the CircularBuffer
        @param absoluteByte absolute position to set write position to.
    */
    bool AdvanceWriteTo(UInt32 absoluteByte);

    /**
        Resets the read and write position to 0.
    */
    void Reset();

    /// Returns the current read position.
    efd::UInt32 GetReadPos();

    /// Returns the current read position.
    efd::UInt32 GetWritePos();

    /// Returns maximum number of bytes that can be written into this CircularBuffer.
    efd::UInt32 GetMaxBytes();

    /// Returns the internal buffer used by CircularBuffer.
    efd::UInt8* GetBuffer();

    /// Returns true if Circular buffer is Full.
    bool IsFull();

    /// Returns true if Circular buffer is Empty.
    bool IsEmpty();

protected:

    /// Advance the read position by bytesToAdvance.  Used internally by Read.
    bool AdvanceRead(UInt32 bytesToAdvance);

    /// Advance the write position by bytesToAdvance.  Used internally by Write.
    bool AdvanceWrite(UInt32 bytesToAdvance);

    /// Calculate the bytes available to read from readPos instead of m_readPos.
    efd::UInt32 BytesAvailableToRead(UInt32 readPos);
    /// Calculate the bytes available to write from writePos instead of m_writePos.
    efd::UInt32 BytesAvailableToWrite(UInt32 writePos);

    /// The current read position.
    efd::UInt32 m_readPos;

    /// The current write position.
    efd::UInt32 m_writePos;

    /// The maximum number of bytes this CircularBuffer can hold.  Also the size of m_pBuffer.
    efd::UInt32 m_maxBytes;

    /// The buffer used by CircularBuffer to actually store data.
    efd::UInt8* m_pBuffer;
};
}
#endif //EE_CIRCULARBUFFER_H
