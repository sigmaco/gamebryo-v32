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
#ifndef EE_DATASTREAM_H
#define EE_DATASTREAM_H

#include <efd/StreamInfo.h>
#include <efd/IStreamable.h>

namespace efd
{

class Matrix3;
class Point2;
class Point3;
class Point4;
class Quaternion;
class ID128;
class AssetID;

/**
    Interface used to stream information from one place to another.

    An DataStream knows how to read and write Emergent data types to marshal / demarshal this
    data over the wire.
*/
class EE_EFD_ENTRY DataStream : public MemObject
{
    /// @cond EMERGENT_INTERNAL

    EE_DECLARE_CONCRETE_REFCOUNT

    /// @endcond

public:

enum
{
    // default initial size
    kDATA_STREAM_INITIAL_SIZE = 1024,
    // default size to grow by
    kDATA_STREAM_GROW_SIZE = 1024
};

    /// @name Constructors and Destructors
    //@{

    /// Create with initial size
    /// @param initialSize the initial size to allocate for the DataStream
    DataStream(UInt32 initialSize = kDATA_STREAM_INITIAL_SIZE);

    /// Create a readonly DataStream from a buffer and size
    /// @param pBuffer pointer to the buffer
    /// @param size the size of the buffer
    DataStream(efd::UInt8* pBuffer, UInt32 size);

    /// Create a copy (possibly readonly) of a DataStream from another.
    /// @param cpy DataStream to copy.
    /// @param readOnly True opens the stream in readonly state.
    DataStream(const DataStream &cpy, bool readOnly = false);

    /// Destructor
    virtual ~DataStream();
    //@}

    /// @name Writers
    //@{
    /// Write a bool value to the stream.
    inline void Write(bool val);

    /// Write a efd::SInt8 value to the stream.
    inline void Write(efd::SInt8 val);

    /// Write a efd::UInt8 value to the stream.
    inline void Write(efd::UInt8 val);

    /// Write a efd::SInt16 value to the stream.
    inline void Write(efd::SInt16 val);

    /// Write a efd::UInt16 value to the stream.
    inline void Write(efd::UInt16 val);

    /// Write a efd::SInt32 value to the stream.
    inline void Write(efd::SInt32 val);

    /// Write a efd::UInt32 value to the stream.
    inline void Write(efd::UInt32 val);

    /// Write a efd::SInt64 value to the stream.
    inline void Write(efd::SInt64 val);

    /// Write a efd::UInt64 value to the stream.
    inline void Write(efd::UInt64 val);

    /// Write a float value to the stream.
    inline void Write(efd::Float32 val);

    /// Write a efd::Float64 value to the stream.
    inline void Write(efd::Float64 val);

    /// Write a efd::utf8string value to the stream.
    inline void Write(const efd::utf8string &val);

    /// Write a utf8char_t value to the stream.
    inline void Write(const efd::utf8char_t &val);

    /// Write a WChar value to the stream.
    inline void Write(const efd::utf16char_t &val);

    /// Write an IStreamable value to the stream.
    void Write(const IStreamable &val);

    inline void Write(const efd::Color& val);
    inline void Write(const efd::ColorA& val);
    inline void Write(const efd::Matrix3& val);
    inline void Write(const efd::Point2& val);
    inline void Write(const efd::Point3& val);
    inline void Write(const efd::Point4& val);
    inline void Write(const efd::Quaternion& val);
    inline void Write(const efd::ID128& val);
    inline void Write(const efd::AssetID& val);

    /**
        Include an DataStream value to stream (stream into this stream).

        As a side effect, the source stream will have SetReadOnly() called on it.  This Write
        method will stream the entire stream, regardless of considerations such as the current
        offset.  The size of the buffer constitutes the first data streamed, followed by the raw
        data.

        @param i_source DataStream to be included in this stream.
    */
    void Write(const DataStream &i_source);

    /**
        A version of data-stream writing that allows sub-sections of the buffer to be written.

        This method is the only way to write less than all of the data stream.

        @param val DataStream to be included in this stream.
        @param offset Offset into val to start pulling data.
        @param size Size, in bytes, of the block to copy.
    */
    void Write(const DataStream &val, size_t offset, size_t size);
    //@}

    /// @name Readers
    //@{
    /// Read a bool value from the stream.
    inline void Read(bool &val) const;

    /// Read a char value from the stream.
    inline void Read(efd::SInt8 &val) const;

    /// Read a efd::UInt8 value from the stream.
    inline void Read(efd::UInt8 &val) const;

    /// Read a efd::SInt16 value from the stream.
    inline void Read(efd::SInt16 &val) const;

    /// Read a float value from the stream.
    inline void Read(efd::UInt16 &val) const;

    /// Read a efd::SInt32 value from the stream.
    inline void Read(efd::SInt32 &val) const;

    /// Read a efd::UInt32 value from the stream.
    inline void Read(efd::UInt32 &val) const;

    /// Read a efd::SInt64 value from the stream.
    inline void Read(efd::SInt64 &val) const;

    /// Read a efd::UInt64 value from the stream.
    inline void Read(efd::UInt64 &val) const;

    /// Read a efd::Float32 value from the stream.
    inline void Read(efd::Float32 &val) const;

    /// Read a efd::Float64 value from the stream.
    inline void Read(efd::Float64 &val) const;

    /// Read a float efd::utf8string from the stream.
    inline void Read(efd::utf8string &val) const;

    /// Read a utf8char_t value from the stream.
    inline void Read(efd::utf8char_t &val) const;

    /// Read a WChar value from the stream.
    inline void Read(efd::utf16char_t &val) const;

    /// Read a IStreamable value from the stream.
    void Read(IStreamable &val) const;

    /// Read a DataStream value from the stream (extract stream from stream).
    void Read(DataStream &val) const;

    inline void Read(efd::Color& val) const;
    inline void Read(efd::ColorA& val) const;
    inline void Read(efd::Matrix3& val) const;
    inline void Read(efd::Point2& val) const;
    inline void Read(efd::Point3& val) const;
    inline void Read(efd::Point4& val) const;
    inline void Read(efd::Quaternion& val) const;
    inline void Read(efd::ID128& val) const;
    inline void Read(efd::AssetID& val) const;
    //@}

    /// @name Skip Functions
    //@{
    /// The same as Read, except that it skips over the data, rather than updating the variable.
    inline void Skip(const bool& val) const;
    inline void Skip(const efd::SInt8& val) const;
    inline void Skip(const efd::UInt8& val) const;
    inline void Skip(const efd::SInt16& val) const;
    inline void Skip(const efd::UInt16& val) const;
    inline void Skip(const efd::SInt32& val) const;
    inline void Skip(const efd::UInt32& val) const;
    inline void Skip(const efd::SInt64& val) const;
    inline void Skip(const efd::UInt64& val) const;
    inline void Skip(const efd::Float32& val) const;
    inline void Skip(const efd::Float64& val) const;
    inline void Skip(const efd::utf8string& val) const;
    inline void Skip(const efd::utf8char_t& val) const;
    inline void Skip(const efd::utf16char_t& val) const;
    void Skip(const DataStream& val) const;
    inline void Skip(const efd::Color& val) const;
    inline void Skip(const efd::ColorA& val) const;
    inline void Skip(const efd::Matrix3& val) const;
    inline void Skip(const efd::Point2& val) const;
    inline void Skip(const efd::Point3& val) const;
    inline void Skip(const efd::Point4& val) const;
    inline void Skip(const efd::Quaternion& val) const;
    inline void Skip(const efd::ID128& val) const;
    inline void Skip(const efd::AssetID& val) const;
    //@}

    /**
        Resets the cursor in the buffer.

        This method should be called when the local message service receives the message, and
        before the first read happens.
    */
    inline void Reset() const;

    /**
        Get the total number of bytes this stream uses.

        This method does not count padded space that is not yet allocated.

        @return Number of bytes used by this stream.
    */
    inline size_t GetSize() const;

    /// Destroys contents of a datastream and replaces it with contents of a named file.
    void ReadFromFile(const efd::utf8string& fileName);

    /// Writes out entire contents of a datastream to a named file.
    void WriteToFile(const efd::utf8string& fileName) const;

    /**
        Read an arbitrary number of bytes starting at the current cursor position.

        @note This method is called by all the other read methods for the basic (mundane) data
        types.

        @param pToBuffer Pointer to which to write data.
        @param dataSize Number of bytes to read from stream.
    */
    void ReadRawBuffer(void *pToBuffer, size_t dataSize) const;

    /**
        Write an arbitrary number of bytes starting at the current cursor position.

        @note This method is called by all the other write methods for the basic (mundane) data
        types.

        @param pFromBuffer Pointer to address from which the raw data is read.
        @param dataSize Number of bytes to write.
    */
    void WriteRawBuffer(const void *pFromBuffer, size_t dataSize);

    /**
        Get a pointer to a buffer for writing.  Advances the stream to point to the end of the
        returned buffer.  Data written into this buffer must already by formatted in the correct
        endianess.  This is intended for special cases such as reading a data stream from the
        wire or other persisted binary form.  Call SetRawBufferSize with the actual amount of data
        written if you write less data than the amount specified by dataSize.

        @param dataSize size of the buffer to return
    */
    void* GetRawBufferForWriting(size_t dataSize);

    /**
        Get a pointer to a buffer for reading.  This is intended for special cases such as writing
        a DataStream to the wire or other persisted binary form.

        @return : a pointer to the beginning of the buffer to send over the wire/write to disk
    */
    void* GetRawBufferForReading();

    /**
        Tell DataStream how many bytes you really wrote into the buffer after calling
        GetRawBufferForWriting

        @return Number of bytes used by this stream.
    */
    void SetRawBufferSize(size_t dataActuallyWritten);

    /**
        Returns the position in the stream.

        @return Location in the stream.
    */
    inline size_t GetPos() const;

    /**
        Seek to an arbitrary absolute position in the stream.

        @param offsetPosition Location to position.
        @return True if no error; false if there is an attempt to seek beyond the end of buffer.
    */
    bool Seek(size_t offsetPosition) const;

    /**
        Seek to an arbitrary relative position in the stream.

        @param bytes Offset from current position to seek.
        @return True if no error; false if there is an attempt to seek beyond the end of buffer.
    */
    inline bool SeekFromCurrentPos(size_t bytes) const;

    /**
        Read an arbitrary number of bytes starting at the specified location within the stream.

        @param offsetPosition Where in the stream from which to read the data.
        @param pToBuffer Pointer to location where data from the stream will be written.
        @param dataSize Number of bytes to read from stream.
        @return True if seek/read is successful; false if an attempt was made to seek/read beyond
            the current stream.
    */
    bool ReadAt(size_t offsetPosition, void *pToBuffer, size_t dataSize);

    /**
        Write an arbitrary number of bytes starting at the specified location within the stream.

        @param offsetPosition Where in the stream to write the data.
        @param pFromBuffer Pointer to where raw data will be read.
        @param dataSize Number of bytes to write to the stream.
        @return True if seek/write successful; false otherwise.
    */
    bool WriteAt(size_t offsetPosition, const void *pFromBuffer, size_t dataSize);

    /// @name Stream Support Methods
    //@{
    /**
        Set the endianness for the associated stream.

        @param eType Endian setting for the stream.
    */
    inline void SetEndian(efd::StreamInfo::Endian eType);

    /**
        Get the endianness for the associated stream.

        @return Endian setting for the stream.
    */
    inline efd::StreamInfo::Endian GetEndian() const;

    /**
        Set the variant (state ID) for this stream.

        Variants are a state enumeration that can be used to differentiate a stream condition (in
        packing/unpacking).

        @param var Variant setting for the stream.
    */
    inline void SetVariant(efd::SInt32 var);

    /**
        Get the variant (state ID) for this stream.

        Variants are a state enumeration that can be used to differentiate a stream condition (in
        packing/unpacking).

        @return Variant setting for the stream.
    */
    inline efd::SInt32 GetVariant() const;

    /**
        Set the version ID for this stream.

        @param version Version ID for this stream.
    */
    inline void SetVersion(efd::UInt32 version);

    /**
        Get the version ID for this stream.

        @return Version ID for this stream.
    */
    inline efd::UInt32 GetVersion() const;

    /**
        After writing to a stream has completed, it may be set as read-only to prevent any further
        writes.

        Once a stream becomes read-only, it can never become writable again.  This function is
        const because read-only status is a mutable property.
    */
    inline void SetReadOnly() const;

    /**
        Check if the stream is read-only.

        @return True if stream is read-only; false otherwise.
    */
    inline bool IsReadOnly() const;
    //@}

public:
    /**
        Return a raw pointer to the current location in the stream.

        @note This method should not be used directly.  It is implementation-dependent and is only
            needed to make the process of sending over the network use fewer copies.
    */
    inline const UInt8* GetRawBuffer() const;

    /// Get the number of bytes remaining.
    inline size_t GetRawBytesRemaining() const;

protected:
    /// Grows the size of the simple buffer.
    void Grow(efd::UInt32 minSizeRemaining = 0);

    /// Simple buffer for data stream.
    efd::UInt8* m_buffer;

    // Maximum usable buffer size; can grow as buffer is reallocated.
    efd::UInt32 m_maxUsableBufferSize;

    // Number of bytes written to this stream.
    efd::UInt32 m_usedBytes;

    // Address to read or write the next byte.
    mutable efd::UInt8 *m_pCurrentStreamPos;

    //@{
    /// Byte swap helpers.
    inline void Swap16(efd::UInt8* buf) const;
    inline void Swap32(efd::UInt8* buf) const;
    inline void Swap64(efd::UInt8* buf) const;
    //@}

    /// Smart pointer to support information for the stream.
    StreamInfoPtr m_spStreamInfo;

    /// Read-only flag (for cloned streams used in behaviors and other instances).
    mutable bool m_readOnly;

    /// Flag to tell us if this DataStream instance owns the buffer it contains
    bool m_ownBuffer;
};

/// Declare a smart pointer for the DataStream class.
typedef efd::SmartPointer<DataStream> DataStreamPtr;

/// @name Template definitions for stream operators from DataStream.h
//@{

template<typename T>
DataStream& operator<< (DataStream& str, const T &val)
{
    str.Write(val);
    return str;
}

template<typename T>
const DataStream& operator>> (const DataStream& str, T &val)
{
    str.Read(val);
    return str;
}

template<typename T>
void DataStreamSkip(const DataStream& str, const T &val)
{
    str.Skip(val);
}
//@}

}   // End namespace efd.

#include <efd/DataStream.inl>

#endif // !defined(EE_DATASTREAM_H)
