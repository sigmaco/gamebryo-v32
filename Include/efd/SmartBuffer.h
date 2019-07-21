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

#pragma once
#ifndef EE_SMARTBUFFER_H
#define EE_SMARTBUFFER_H

#include <efd/GrowableBuffer.h>


namespace efd
{
// forward declarations
class Archive;
class utf8string;

/**
    A SmartBuffer is a sized window into a GrowableBuffer.  They can be quickly and cheaply
    copied since they share a reference to the actual memory through the GrowableBuffer.  The
    internal GrowableBuffer is automatically maintained so you can effectively think of
    SmartBuffer as being a generic resizable memory buffer that can be cheaply "copied" around.
    The practical result of this is that SmartBuffer instances are typically placed on the
    stack rather than being allocated from the heap.
*/
class EE_EFD_ENTRY SmartBuffer
{
public:
    /// Default Constructor.  Uses a growable, owned, initially NULL GrowableBuffer.
    SmartBuffer();

    /// Constructor.  Uses a growable, owned GrowableBuffer of the given initial size.
    explicit SmartBuffer(efd::UInt32 i_cbInitialSize);

    /// Borrow Constructor.  Creates a SmartBuffer using a GrowableBuffer that will borrow the
    /// provided memory.
    SmartBuffer(_Borrow, void* i_pData, efd::UInt32 i_cbData);
    /// Adopt Constructor.  Creates a SmartBuffer using a GrowableBuffer that will adopt the
    /// provided memory.
    SmartBuffer(_Adopt, void* i_pData, efd::UInt32 i_cbData);

    /// Constructor.  Creates a SmartBuffer with a reference to a specific pre-existing
    /// GrowableBuffer instance.  A reference will be held to this buffer.  The entire buffer
    /// will be used by the resulting SmartBuffer, to restrict this call MakeWindow on the result.
    SmartBuffer(GrowableBuffer* sourceBuffer);

    /// Copy Constructor
    SmartBuffer(const SmartBuffer& i_rhs);
    /// Assignment Operator
    SmartBuffer& operator=(const SmartBuffer& i_rhs);

    /// Destructor
    ~SmartBuffer();

    /// Any previously owned buffer is released and the provided memory is adopted by a new
    /// GrowableBuffer.  The memory will be freed using EE_EXTERNAL_DELETE when the
    /// GrowableBuffer is destroyed.
    void Adopt(void* i_pData, efd::UInt32 i_cbData);

    /// Any previously owned buffer is released and the provided memory is borrowed by a new
    /// GrowableBuffer.  The caller must maintain the lifetime of the memory used and must
    /// ensure the memory remains available for the life of the GrowableBuffer, which means for
    /// the lifetime of this SmartBuffer and any copy or window made into this SmartBuffer.
    /// Borrowed buffers cannot be grown, only the borrowed memory will be used.
    void Borrow(void* i_pData, efd::UInt32 i_cbData);

    /// Orphan any memory we own. The caller is responsible for deleting the memory using
    /// EE_EXTERNAL_DELETE. Once the memory has been deleted then the SmartBuffer will no
    /// longer be valid, but the buffer continues to point to the orphaned memory.
    efd::UInt8* Orphan();

    /// Grow to a good size not smaller than i_cbNewSize.  Returns false if unable to grow,
    /// for example if you try to grow a borrowed buffer it would fail.
    bool Grow(efd::UInt32 i_cbNewSize);

    /// Grow to a good size not smaller than i_cbNewSize. Returns false if unable to grow,
    /// for example if you try to grow a borrowed buffer it would fail. This will also allocate a
    /// new buffer if more than one reference is held to the original buffer.
    bool GrowExclusive(efd::UInt32 i_cbNewSize);

    /// Make a copy of the buffer.  This creates a new GrowableBuffer owned by the new
    /// SmartBuffer and copies the used memory into the buffer.
    SmartBuffer Clone();

    // Don't remove the empty lines surrounding the grouping tags below. They are necessary
    // for correct doxygen formatting.

    /**
        Create a SmartBuffer that represents a window into the current buffer.
        
        The new SmartBuffer will share a reference to the original memory buffer.

        @param i_start The starting offset for the new window.
        @param i_size The size for the new window, or -1 to make a window to the end of the
            buffer.
        @return A new SmartBuffer representing a window into the current SmartBuffer
    */
    SmartBuffer MakeWindow(efd::UInt32 i_start, efd::UInt32 i_size = -1);

    /**
        Create a SmartBuffer that represents a window into the current buffer, const version.
        
        The new SmartBuffer will share a reference to the original memory buffer.

        @param i_start The starting offset for the new window.
        @param i_size The size for the new window, or -1 to make a window to the end of the
            buffer.
        @return A new const SmartBuffer representing a window into the current SmartBuffer
    */
    const SmartBuffer MakeWindow(efd::UInt32 i_start, efd::UInt32 i_size = -1) const;

    /**
        Shrinks the buffer to the minimum size.

        This can actually increase memory usage since the original master buffer might
        have other references to it. If the buffer is being shared both the new and old buffers
        will remain.
    */
    void Shrink();

    /**
        Get a temporary pointer to the current internal buffer.

        Do not cache pointers returned by GetBuffer, they will become invalid if the
        SmartBuffer grows. Instead, consider storing an offset into the buffer.
    */
    efd::UInt8* GetBuffer();

    /**
        Get a temporary pointer to the current internal buffer, const version.

        Do not cache pointers returned by GetBuffer, they will become invalid if the
        SmartBuffer grows. Instead, consider storing an offset into the buffer.
    */
    const efd::UInt8* GetBuffer() const;

    /// Get the size of the SmartBuffer.
    efd::UInt32 GetSize() const;

    /// Check if the current buffer is able to grow.  Owned buffers can be grown but borrowed
    /// buffers cannot.
    bool CanGrow() const;

    /// Serialize a smart buffer into an archive. The smart buffer is assumed to have compatible
    /// endianness with the archive and is serialized as size-prefixed raw bytes.
    void Serialize(Archive& io_ar);

    /// Release the GrowableBuffer used by this SmartBuffer. This effectively resets the SmartBuffer
    /// to the initial empty state as if it had just been default constructed.
    void ReleaseMasterBuffer();

    /// Fills the buffer with the contents of the given file
    bool ReadFromFile(const efd::utf8string& fileName);

    /// Writes out entire contents of a buffer to a named file.
    bool WriteToFile(const efd::utf8string& fileName) const;

    /// Compare the contents of two SmartBuffers to see if they are identical.
    bool IsEqual(const SmartBuffer& other);

protected:
    /// The master buffer is a reference counted object that actually owns the memory.  A smart
    /// buffer is just a sized window into a shared master buffer.
    GrowableBuffer* m_pMasterBuffer;
    /// Our starting offset into the master buffer
    efd::UInt32 m_cbStart;
    /// The size of our window into the master buffer
    efd::UInt32 m_cbSize;
};

} // end namespace efd

#endif // EE_SMARTBUFFER_H
