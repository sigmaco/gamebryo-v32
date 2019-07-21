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
#ifndef EE_SMARTPOINTER_H
#define EE_SMARTPOINTER_H

#include <efd/OS.h>
#include <efd/MemObject.h>

namespace efd
{

/**
    Smart pointer for reference counting objects.

    The class T must contain IncRefCount and DecRefCount methods.  It does not have to be derived
    from any specific base class as long as it implements these methods.  Suitable methods include
    using one of the following macros in a class definition:
        EE_DECLARE_ABSTRACT_REFCOUNT (+ implementations of the methods)
        EE_DECLARE_CONCRETE_REFCOUNT
        EE_DECLARE_CONCRETE_ATOMIC_REFCOUNT
    or deriving from the following class:
        efd::RefCount
        NiRefObject
    or using one of these templates to make a reference counted wrapper:
        efd::RefCounted<>
        efd::RefCountedMemObject<>

    Assignment of a non-NULL pointer to this class will cause IncRefCount to be called on the
    pointer.

    If the smart pointer contains a non-NULL pointer when a different pointer is assigned or when
    the SmartPointer is destructed, then it will call DecRefCount on the existing pointer.

    DecRefCount will typically be implemented such that dropping to zero will delete the object.
*/
template <class T>
class SmartPointer : public efd::MemObject
{
public:
    /**
        Constructor that takes a pointer to a reference counted object.

        It will add a reference (call IncRefCount) if pObject is non-NULL.
    */
    EE_FORCEINLINE SmartPointer(T* pObject = (T*) 0);

    /**
        Constructor that takes another smart pointer.

        It will add a reference if the pointer object contains a non-NULL value.
    */
    EE_FORCEINLINE SmartPointer(const SmartPointer& ptr);

    /// Destructor; it will remove a reference (DecRefCount) if the contained pointer is non-NULL.
    EE_FORCEINLINE ~SmartPointer();

    /// Implicit conversion to the underlying pointer type.
    EE_FORCEINLINE operator T*() const;

    /// Explicit conversion to the underlying pointer type.
    EE_FORCEINLINE T* data() const;

    /// @name 'Pointer-like' operators.
    //@{
    EE_FORCEINLINE T& operator*() const;
    EE_FORCEINLINE T* operator->() const;
    //@}

    /// @name Pointer assignment operators.
    //@{
    EE_FORCEINLINE SmartPointer& operator=(const SmartPointer& ptr);
    EE_FORCEINLINE SmartPointer& operator=(T* pObject);
    //@}

    /// @name Pointer comparison operators.
    //@{
    EE_FORCEINLINE bool operator==(T* pObject) const;
    EE_FORCEINLINE bool operator!=(T* pObject) const;
    EE_FORCEINLINE bool operator==(const SmartPointer& ptr) const;
    EE_FORCEINLINE bool operator!=(const SmartPointer& ptr) const;
    EE_FORCEINLINE bool operator<(T* pObject) const;
    EE_FORCEINLINE bool operator>(T* pObject) const;
    EE_FORCEINLINE bool operator<(const SmartPointer& ptr) const;
    EE_FORCEINLINE bool operator>(const SmartPointer& ptr) const;
    //@}

    /**
        Swaps the underlying pointer values of two smart pointer objects.  Using this method
        is significantly faster for atomic refcounted objects than writing code of the form:
            SmartPointer<T> x = a;
            a = b;
            b = x;
    */
    EE_FORCEINLINE void Swap(SmartPointer& otherPtr);

protected:
    // The managed smart pointer, a reference counting, self deleting pointer.
    T* m_pObject;
};

//------------------------------------------------------------------------------------------------
/// Macro to declare a typedef for a smart pointer to a class, of the form ClassNamePtr.
#define EE_DECLARE_SMART_POINTER(classname) \
    class classname; \
    typedef efd::SmartPointer<classname> classname##Ptr

//------------------------------------------------------------------------------------------------
/// Macro to declare a typedef for a smart const pointer to a class, of the form ClassNameConstPtr.
#define EE_DECLARE_SMART_CONST_POINTER(classname) \
    class classname; \
    typedef efd::SmartPointer<const classname> classname##ConstPtr

//------------------------------------------------------------------------------------------------
} // end namespace efd.

#include <efd/SmartPointer.inl>

#endif // EE_SMARTPOINTER_H
