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
#ifndef EE_GROWABLEBUFFER_H
#define EE_GROWABLEBUFFER_H

#include <efd/UniversalTypes.h>
#include <efd/ReferenceCounting.h>

namespace efd
{

/// A special tag for distinguishing functions that otherwise would have the same signature.
enum _Borrow { Borrow };
/// A special tag for distinguishing functions that otherwise would have the same signature.
enum _Adopt  { Adopt };

/**
    GrowableBuffer is simply a reference counted chunk of memory.  The memory can either be
    owned by the buffer or borrowed from an external source.
*/
class EE_EFD_ENTRY GrowableBuffer : public efd::MemObject
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CONCRETE_REFCOUNT
    /// @endcond

public:
    /// Default Constructor.  Creates a growable, owned, initially NULL buffer.
    GrowableBuffer();

    /// Constructor.  Creates a growable, owned buffer of the given initial size.
    explicit GrowableBuffer(efd::UInt32 i_cbInitialSize);

    /// Borrow Constructor.  Borrows a reference to the provided memory.  The caller must
    /// maintain the lifetime of the memory used and must ensure the memory remains available
    /// for the life of the GrowableBuffer.  Borrowed buffers cannot be grown, only the borrowed
    /// memory will be used.
    GrowableBuffer(_Borrow, void* i_pData, efd::UInt32 i_cbData);

    /// Adopt Constructor.  The provided memory is adopted by the GrowableBuffer and will be
    /// freed using EE_EXTERNAL_DELETE when the GrowableBuffer is destroyed.
    GrowableBuffer(_Adopt, void* i_pData, efd::UInt32 i_cbData);

    /// Destructor
    virtual ~GrowableBuffer();

    /// Grow to at least the given size.  Data from the previous buffer is copied into the new
    /// buffer.
    /// @return The actual size when done.
    efd::UInt32 Grow(efd::UInt32 i_cbSize);

    /// Grow to exactly the given size.  Data from the previous buffer is copied into the new
    /// buffer.  This will not shrink the buffer if the used space already exceeds the requested
    /// size.
    /// @return The actual size when done.
    efd::UInt32 GrowExact(efd::UInt32 i_cbSize);

    /// Any previously owned buffer is freed and the provided memory is adopted by the
    /// GrowableBuffer.  The memory will be freed using EE_EXTERNAL_DELETE when the
    /// GrowableBuffer is destroyed.
    void Adopt(void* i_pData, efd::UInt32 i_cbData);

    /// Any previously owned buffer is freed and the provided memory is borrowed by the
    /// GrowableBuffer.  The caller must maintain the lifetime of the memory used and must
    /// ensure the memory remains available for the life of the GrowableBuffer.  Borrowed
    /// buffers cannot be grown, only the borrowed memory will be used.
    void Borrow(void* i_pData, efd::UInt32 i_cbData);

    /// Relinquishes ownership of the memory buffer to the caller.  The GrowableBuffer will
    /// continue to reference the memory buffer but will not free the memory upon destruction.
    /// The caller must eventually free the returned memory using EE_EXTERNAL_DELETE.  If the
    /// memory buffer is not owned this will return NULL.
    efd::UInt8* Orphan();

    /// Access the memory buffer.
    //@{
    inline efd::UInt8* GetBuffer();
    inline const efd::UInt8* GetBuffer() const;
    //@}

    /// Get the size of the memory buffer.
    inline efd::UInt32 GetSize() const;

    /// Determine if the buffer can be grown.
    inline bool CanGrow() const;

    /// Determine if the buffer is owned.
    inline bool OwnsBuffer() const;

    /// Returns true if only one reference exists to this buffer implying that it is exclusively
    /// owned and not currently being shared.
    inline bool IsExclusive() const;

protected:
    /// Helper function to free the memory buffer if it is owned.
    void FreeBuffer();

    /// Given a number, get round up to the nearest power of two. Used by GetAllocSizeFromMinSize
    /// for mid-sized numbers.
    static efd::UInt32 RoundUpToNextPowerOfTwo(efd::UInt32 i_num);

    /// Given a minimum size find a good size to allocate.  Normally the next highest power
    /// of two but exact behavior is tweakable via statics.
    static efd::UInt32 GetAllocSizeFromMinSize(efd::UInt32 i_cbMinSize);

    /// The memory buffer
    efd::UInt8* m_pData;
    /// The size of the memory buffer
    efd::UInt32 m_cbData;

    /// True if we own the memory buffer
    bool m_fOwnsBuffer : 1;
    /// True if we are allowed to grow the memory buffer
    bool m_fCanGrow : 1;
};

} // end namespace efd

#include <efd/GrowableBuffer.inl>

#endif // EE_GROWABLEBUFFER_H
