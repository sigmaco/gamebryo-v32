// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not
// be copied or disclosed except in accordance with the terms of that
// agreement.
//
//      Copyright (c) 2006-2009 Todd Berkebile.
//      Copyright (c) 1996-2009 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Calabasas, CA 91302
// http://www.emergent.net

#ifndef EE_ARCHIVE_H
#define EE_ARCHIVE_H


#include <efd/SmartBuffer.h>


namespace efd
{

/// List of supported endian types.
enum Endianness
{
    /// Big Endian (non-intel architecture, typically).
    Endian_Big = 0,

    /// Little Endian (Intel machines).
    Endian_Little,

    /// Network byte order is the same as Little Endian.
    Endian_NetworkOrder = Endian_Little,
};

/**
    An Archive provides the storage media for data marshaling.  You can toss objects into the
    archive using Serialize and then later use the exact same code to retrieve the objects.
    Archives help protect against data overflows and underflows too.

    Sample usage for packing:
    @code
        Archive ar(Archive::Packing);
        Serializer::SerializeObject(object1, ar);
        ...
        Serializer::SerializeObject(objectN, ar);
        if (!ar.GetError())
        {
            SmartBuffer sbResult = ar.GetUsedBuffer();
            // sbResult now contains the marshaled data, it could be written to the wire or
            // persisted to disk or whatever.
        }
    @endcode

    Sample usage for unpacking:
    @code
        Archive ar(Archive::Unpacking, pData, cbData);
        Serializer::SerializeObject(object1, ar);
        ...
        Serializer::SerializeObject(objectN, ar);
        ar.CheckForUnderflow();
        if (!ar.GetError())
        {
            // use the unpacked results
        }
    @endcode
*/
class EE_EFD_ENTRY Archive
{
public:
    enum _Packing { Packing };
    enum _Unpacking { Unpacking };

    /// Default Constructor. Creates an archive for packing.
    Archive();

    /// Constructor. Explicit version of the default constructor to provide consistent syntax.
    Archive(_Packing);

    /// Constructor. Pack into a borrowed buffer. The caller must ensure the lifetime of the
    /// provided buffer exceeds the lifetime of the Archive. If you want the Archive to adopt
    /// the buffer instead, use:
    /// @code
    ///     Archive(Archive::Packing, SmartBuffer(Adopt, i_pBuffer, i_cbBuffer));
    /// @endcode
    Archive(_Packing, void* i_pBuffer, efd::UInt32 i_cbBuffer);

    /// Constructor. Pack into the provided SmartBuffer.
    Archive(_Packing, const SmartBuffer& i_buffer);

    /// Constructor. Unpack from a borrowed buffer. The caller must ensure the lifetime of the
    /// provided buffer exceeds the lifetime of the Archive. The memory in the buffer will be read
    /// but will not be modified by the archive. If you want the Archive to adopt the buffer
    /// instead, use:
    /// @code
    ///     Archive(Archive::Unpacking, SmartBuffer(Adopt, i_pBuffer, i_cbBuffer));
    /// @endcode
    Archive(_Unpacking, const void* i_pBuffer, efd::UInt32 i_cbBuffer);

    /// Constructor. Unpack from the provided SmartBuffer.
    Archive(_Unpacking, const SmartBuffer& i_buffer);

    /// Destructor
    ~Archive();

    /// Determine if this archive is being used for packing.
    inline bool IsPacking() const;

    /// Determine if this archive is being used for unpacking.
    inline bool IsUnpacking() const;

    /// Determine if any errors have been raised on this archive.
    inline bool GetError() const;

    /// Raise an error on the current archive.  This will assert when called.
    void RaiseError();

    /// Determine the current position in the archive.
    inline efd::UInt32 GetCurrentPosition() const;

    /// Determine how many bytes of the archive have been used.
    inline efd::UInt32 GetUsedSize() const;

    /// Create a SmartBuffer representing the currently used portion of the archive.
    //@{
    inline SmartBuffer GetUsedBuffer();
    inline const SmartBuffer GetUsedBuffer() const;
    //@}

    /// Determine the bytes remaining in the archive. When unpacking this number is the limit
    /// of how much can be read from the archive, but when packing this amount can change if
    /// the underlying SmartBuffer grows.
    inline efd::UInt32 GetRemainingSize() const;

    /// Create a SmartBuffer representing the currently unused portion of the archive.
    //@{
    inline SmartBuffer GetRemainingBuffer();
    inline const SmartBuffer GetRemainingBuffer() const;
    //@}

    /// Create a SmartBuffer representing the entire buffer used by the archive. This is a seldom
    /// needed method, typically only the used portion of the archive is of interest so you should
    /// consider using GetUsedBuffer instead.
    //@{
    inline const SmartBuffer& GetEntireBuffer() const;
    //@}

    /// Returns true if the given number of bytes remain in the archive.  Will grow the archive
    /// if necessary and possible.  Will RaiseError if there isn't enough room left.  This can
    /// also help with efficiency when packing a large amount of data of know size.  By calling
    /// a single CheckBytes up front you will grow the buffer just once and avoid the cost of
    /// multiple smaller grows which might otherwise occur as you pack the sub components.
    inline bool CheckBytes(efd::UInt32 i_cbSize);

    /// GetBytes is used to access a block of the buffer.  It will grow the buffer if needed
    /// (and that is possible).  If there isn't enough room it will RaiseError and return NULL.
    /// It it not typically safe to cache the resulting pointer since it will become invalid if
    /// the archive grows and will most often become invalid when the archive is destroyed
    /// (there are rare exceptions when unpacking from a borrowed buffer).
    efd::UInt8* GetBytes(efd::UInt32 i_cbSize);

    /// Grabs a pointer directly into the archive without adjusting the current location.  Will
    /// grow the buffer if necessary and possible.  If there isn't enough room it will
    /// RaiseError and return NULL. Caching the resulting pointer isn't recommended, see
    /// GetBytes for details.  You can pass in a previous position obtained by calling
    /// GetCurrentPosition() in order to update previous positions in the archive.  An example
    /// might be if you were packing a linked list of unknown size.  You might call
    /// GetCurrentPosition() and then pack a dummy size of zero into the archive.  Then you
    /// could walk the list packing each element and counting the number of elements.  When you
    /// are done you could use the stored position to PeekBytes and write the actual number of
    /// elements packed.  Although this is possible its not typically recommended as it forces
    /// your "packing" and "unpacking" code paths to diverge.
    efd::UInt8* PeekBytes(efd::UInt32 i_cbOffset, efd::UInt32 i_cbSize);

    /// Make another archive representing a window into the current archive's buffer at the current
    /// position in this archive. This will advance the archive by the requested size if needed.
    /// The new archive will have the same pack/unpack mode as the current archive. This can be
    /// used to reserve a chunk of space in the archive which can be packed or unpacked at a later
    /// time. For example, when packing you might make a 4 byte window before walking a linked list
    /// and then count the number of elements actually serialized. When finished you can serialize
    /// the actual number of elements into the reserved window.
    Archive MakeWindow(efd::UInt32 i_cbSize);

    /// You can call this after you finish unpacking from a buffer.  It will raise an error if
    /// the entire buffer wasn't consumed
    bool CheckForUnderflow();

    /// @name Endianness routines
    //@{
    /// Gets the endianness of the archive. The endianness will default to the hardware endianness.
    inline efd::Endianness GetEndianness() const;

    /// Sets the endianness of the archive. Set this on packing or unpacking archives after the
    /// are constructed but before they are first used to serialize data. This method will assert
    /// if the endianness is changed after the archive had been used for serialization.
    inline void SetEndianness(efd::Endianness val);

    /// Gets the endianness of the hardware. Intel architectures are typically little endian and
    /// everything else is typically big endian.
    inline static efd::Endianness GetHardwareEndianness();

    /// Returns true if the archive's endianness differs from the hardware's endianness.
    inline bool NeedsSwap();

    /// Assigns the given value to the resulting value with a possible byte swap to adjust the
    /// endianness if necessary. This only works for plain-old-data types (integers, floats, enums).
    template<typename T>
    void MaybeSwap(const T& i_value, T& o_result);
    //@}

protected:
    /// @name State flags
    //{
    /// True if packing, false if unpacking
    bool m_fPacking : 1;
    /// starts false, becomes true if RaiseError is called
    bool m_fError : 1;
    //@}

    /// The actual storage.  When unpacking this contains the results of a previous packing.
    SmartBuffer m_buffer;

    /// Where we are inside the buffer.
    efd::UInt32 m_CurrentPos;

    /// The endianness of the archive buffer
    efd::Endianness m_endianness;
};

} // end namespace efd

#include <efd/Archive.inl>

#endif // EE_ARCHIVE_H
