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
#ifndef EE_IBASE_H
#define EE_IBASE_H

#include <efd/ClassInfo.h>
#include <efd/SmartPointer.h>
#include <efd/MemObject.h>
#include <efd/ReferenceCounting.h>

namespace efd
{

/**
    Abstract base class for all interfaces in the Emergent ServiceManager.

    IBase is the base class for all interfaces in the Emergent ServiceManager.  It provides two
    major capabilities:
      1) Run-Time Type Identification (RTTI).  This capability enables a generic interface to be
         queried for its derived types.
      2) Reference Counting.  This capability enables a generic interface to be used throughout
         the codebase, yet still be deleted at the appropriate time.

    @note Unlike COM's implementation of IBase, there is no QueryInterface method.  Instead, a
        generic type conversion process is applied.
    @note RefCounts are not incremented when performing a type cast.  Instead, values should be
        stored in smart pointers.
    @note ClassIDs must be unique within the context of an application. Values for ClassIDs
        that are declared by EE_DECLARE_EXTERNAL_CLASSID are restricted to the
        0x06200000-0x062fffff range.

*/
class EE_EFD_ENTRY IBase: public MemObject
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_INTERFACE(IBase, 0xFFFFFFFF);
    EE_DECLARE_ABSTRACT_REFCOUNT
    /// @endcond

public:
    /**
       Cast "this" to a pointer of the specified class type.

       @note TypeCast does NOT increment the reference count internally, which means that the
           inner workings of TypeCast CANNOT take a reference to the value returned through
           ppValue.

       @param id ClassID that "this" should be cast into.
       @param ppValue Address of the pointer that will hold the type-cast "this" pointer.  This
           value will be NULL if the cast was not successful.
       @return Boolean True if the cast succeeded; false otherwise.
    */
    virtual bool TypeCast(const ClassID id, void** ppValue) const = 0;
    virtual bool TypeCast(const ClassID id, const void** ppValue) const = 0;

    /**
        Get access to the class RTTI information.

        @note GetClassDesc() is virtual, so this function will return the most derived ClassInfo
            by default.
        @note The function is named "GetClassDesc()" to avoid name collisions with Microsoft
            Windows' "GetClassInfo()".

        @return const ClassInfo* : Pointer to ClassInfo instance.
    */
    virtual const ClassInfo* GetClassDesc() const = 0;

    /**
        Helper method to directly get ClassID.

        @note GetClassDesc is virtual, so this function will return the most derived ClassID by
            default.  GetClassID is virtual to support creating multiple "virtual" classes from
            the same C++ class.  E.g., using MessageWrapper<>, or supporting subclasses that do
            not use EE_DECLARE_CLASS macros.

        @return ClassID Returned class ID.
    */
    virtual ClassID GetClassID() const {return GetClassDesc()->GetClassID();}

#if defined(EE_MEMTRACKER_DETAILEDREPORTING)
    /// A constructor that registers a detailed memory leak reporting method for this instance.
    IBase();

    /// A leak dumping method for use in detailed memory reports. To enable detailed memory leak
    /// reporting recompile all source with the EE_USE_MEMTRACKER_DETAILEDREPORTING macro defined.
    /// See efd/MemTracker.h and efd/MemDefines.h for details.
    static void LeakDump(void* pMem, char* o_buffer, unsigned int i_cchBuffer);
#endif

protected:
    /**
        Protected virtual destructor.

        It is protected to make sure that no one can delete an IBase pointer directly. Instead
        the reference counting methods must be used to manage the IBase memory.
    */
    virtual ~IBase() {};
};

/// @name Helper functions for dynamic type conversion.
//@{
template <class Dest, typename Src> Dest* DynamicCast(Src* Source)
{
    void* pValue = NULL;
    if (Source && Source->TypeCast(Dest::CLASS_ID, &pValue))
        return (Dest*) pValue;
    else
        return NULL;
};

template <class Dest, typename Src> const Dest* DynamicCast(const Src* Source)
{
    const void* pValue = NULL;
    if (Source && Source->TypeCast(Dest::CLASS_ID, &pValue))
        return (const Dest*) pValue;
    else
        return NULL;
};

template <class Dest, typename Src>
Dest* DynamicCast(efd::SmartPointer<Src>& Source)
{
    void* pValue = NULL;
    if (Source && Source->TypeCast(Dest::CLASS_ID, &pValue))
        return (Dest*) pValue;
    else
        return NULL;
};

template <class Dest, typename Src>
const efd::SmartPointer<Dest> DynamicCast(const efd::SmartPointer<Src>& Source)
{
    const void* pValue = NULL;
    if (Source && Source->TypeCast(Dest::CLASS_ID, &pValue))
        return (Dest*) pValue;
    else
        return NULL;
};
//@}

//------------------------------------------------------------------------------------------------
/// @def EE_DYNAMIC_CAST
/// Macro for backwards compatibility that calls DynamicCast.
#define EE_DYNAMIC_CAST(classname, value) efd::DynamicCast<classname>(value)

//------------------------------------------------------------------------------------------------
/// Helper function for known compile-time type conversion.
template <class Dest, class Src> Dest* StaticCast(Src* Source)
{
    return static_cast<Dest*>(Source);
};

//------------------------------------------------------------------------------------------------
/// Helper function for known compile-time type conversion.
template <class Dest, class Src> const Dest* StaticCast(const Src* Source)
{
    return static_cast<const Dest*>(Source);
};

//------------------------------------------------------------------------------------------------
/// @def EE_STATIC_CAST
/// Macro for backwards compatibility. It calls StaticCast.
#define EE_STATIC_CAST(classname, value) efd::StaticCast<classname>(value)

//------------------------------------------------------------------------------------------------
/// Declaration of a smart pointer to an IBase instance.
typedef efd::SmartPointer<IBase> IBasePtr;

//------------------------------------------------------------------------------------------------
} // end namespace efd.

#endif // EE_IBASE_H
