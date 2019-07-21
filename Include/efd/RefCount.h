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
#ifndef EE_REFCOUNT_H
#define EE_REFCOUNT_H

#include <efd/SmartPointer.h>
#include <efd/MemObject.h>
#include <efd/UniversalTypes.h>
#include <efd/efdLibType.h>
#include <efd/AtomicOperations.h>

namespace efd
{


/**
    A non-atomic reference count.  This reference count cannot be used simultaneously from
    multiple threads but is very fast when you know your object is only used from one thread
    at a time.
*/
class EE_EFD_ENTRY NonAtomicRefCount
{
public:
    /// @name Construction and Destruction
    //@{
    inline NonAtomicRefCount(efd::UInt32 startAt = 0) : m_ref(startAt) {}
    //@}

    /// Increment the reference count.
    /// @return The incremented reference count.
    inline efd::UInt32 operator++() { return ++m_ref; }

    /// Decrement the reference count.
    /// @return The decremented reference count.
    inline efd::UInt32 operator--() { return --m_ref; }

    /// Get the current reference count.
    /// @return The current reference count.
    inline operator efd::UInt32() { return m_ref; }

protected:
    efd::UInt32 m_ref;
};


/**
    An atomic reference count.  This reference count can be safely used from multiple threads
    so long as normal reference counting policies are followed.
*/
class EE_EFD_ENTRY AtomicRefCount
{
public:
    /// @name Construction and Destruction
    //@{
    inline AtomicRefCount() : m_ref(0) {}
    //@}

    /// Increment the reference count.
    /// @return The incremented reference count.
    inline efd::UInt32 operator++() { return efd::AtomicIncrement(m_ref); }

    /// Decrement the reference count.
    /// @return The decremented reference count.
    inline efd::UInt32 operator--() { return efd::AtomicDecrement(m_ref); }

    /// Get the current reference count.
    /// @return The current reference count.
    inline operator efd::UInt32() { return m_ref; }

protected:
    efd::UInt32 m_ref;
};


/**
    RefCountObject provides a concrete implementation of reference counting. This allows an
    object to delete itself when no more references are held.

    RefCountObject is intended for use in single inheritance situations where performance is
    critical.  The increment and decrement functions are non-virtual which makes the common
    operations for maintaining the reference count quicker at the cost of preventing multiple
    derivation from RefCountObject.  If you require multiple inheritance (or runtime typing)
    then you should use efd::IBase instead of this class.

    The signatures for these methods mirror those used in efd::IBase, so you can use a RefCount
    as the concrete implementation for an IBase derived class by using the forwarded reference
    macro, EE_DECLARE_FORWARDED_CONCRETE_REFCOUNT.  If you do this you still must ensure that
    only a single RefCountObject instance provides your concrete reference count implementation.

    Pass in either NonAtomicRefCount or AtomicRefCount as the template argument for this class.
    Use AtomicRefCount if your object will be used from multiple threads, or NonAtomicRefCount
    for a faster implementation that can only be used from one thread at a time.
*/
template< typename RefCountImpl >
class RefCountObject : public MemObject
{
public:
    /**
       Increment the reference count.
    */
    inline void IncRefCount() const;

    /**
       Decrement the reference count. Once the reference count equals zero, DeleteThis is called
       to delete the object.
    */
    inline void DecRefCount() const;

    /// Get the current reference count.
    /// @return The current reference count.
    inline efd::UInt32 GetRefCount() const;

protected:
    /// keeps track of the ref count for this object
    mutable RefCountImpl m_RefCount;

    /// Delete ourself.  A virtual method called by DecRefCount when the reference reaches zero.
    virtual void DeleteThis() const;

    /// Protected destructor. This makes sure that no one can delete an RefCount pointer directly.
    virtual ~RefCountObject() {}
};


/// Class for backward compatibility
class RefCount : public RefCountObject<NonAtomicRefCount>
{
};



} // end namespace efd

#include <efd/RefCount.inl>

#endif // EE_REFCOUNT_H
