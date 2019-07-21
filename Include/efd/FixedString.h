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
#ifndef EE_FIXEDSTRINGTABLE_H
#define EE_FIXEDSTRINGTABLE_H

#include <efd/RTLib.h>
#include <efd/GlobalStringTable.h>

namespace efd
{
/**
    This class encapsulates a memory efficient implementation of
    reference-counted ASCII strings. Additionally, FixedStrings have the
    property that all strings with the same value point to the same
    efd::Character buffer in memory. This capability allows for fast
    comparison between FixedStrings. FixedStrings are not meant to be
    changed once created. Please see the notes section for details on
    streaming and using FixedStrings in function calls.

    @note Streaming - FixedStrings work slightly differently from normal
    values in the streaming process. NiObject-derived classes that wish to
    save FixedStrings will first need to register the strings using the
    NiStream::RegisterFixedString method in their
    NiObject::RegisterStreamables implementation. In the NiObject::SaveBinary
    implementation, NiStream::SaveFixedString will need to be called.
    Upon load, there is no need for registration and therefore only
    NiStream::LoadFixedString will need to be called.

    @note Usage In Function Calls - Passing FixedStrings directly down the
    stack is quite expensive because a new FixedString is created every
    function call. New strings must increment and decrement the reference
    count, which means pointer de-referencing and cache misses. Instead of
    writing a function like this:  void SetName(FixedString name)
    Write a function like this:    void SetName(const FixedString& name)
    This subtle difference allows the compiler to pass the FixedString down
    the stack without creating a new instance every call.
*/
class EE_EFD_ENTRY FixedString : public MemObject
{
public:
    ///@ name Construction and Destruction
    //@{
    /// Create a string with a value of NULL.
    FixedString();

    /**
        Create a string matching the value of pCString. If the string already
        exists in memory, increment its reference count. If the string does
        not already exist in memory, create a new one and set its reference
        count to one.
    */
    FixedString(const efd::Char* pCString);

    /**
        Create a string pointing to the same data as string and incrementing
        its reference count.
    */
    FixedString(const FixedString& string);

    ~FixedString();
    //@}

    /**
        Access the internal efd::Character data of this string.
        The return value is constant to prevent data manipulation.
    */
    operator const efd::Char*() const;

    /// Determine whether or not this string is NULL.
    bool Exists() const;

    /**
        Create a string pointing to the same data as string and incrementing
        its reference count. Decrement the current value of the string,
        deleting it if the reference count equals zero.
    */
    FixedString& operator=(const FixedString& string);

    /**
        Create a string matching the value of pCString. If the string already
        exists in memory, increment its reference count. If the string does
        not already exist in memory, create a new one and set its reference
        count to one. Decrement the current value of the FixedString,
        deleting it if the reference count equals zero.
    */
    FixedString& operator=(const efd::Char* pCString);

    /// Return the length of the internal efd::Character data.
    size_t GetLength() const;

    /// Return the current reference count of the efd::Character data.
    efd::UInt32 GetRefCount() const;

    /**
        Helper functions for comparing strings with and without case
        sensitivity.
    */
    bool Equals(const efd::Char* pCStr) const;
    bool EqualsNoCase(const efd::Char* pCStr) const;

    /**
        Helper functions for determining if a string is a substring of this
        fixed string  with and without case sensitivity.
    */
    bool Contains(const efd::Char* pCStr) const;
    bool ContainsNoCase(const efd::Char* pCStr) const;


    /**
        Helper functions that assist in comparing strings. FixedString to
        FixedString comparison is very fast since it is a simple pointer
        value comparison and does not need to de-reference the efd::Character
        array. FixedString to efd::Character array comparisons have been
        accelerated for the case where the efd::Character array is really pointing
        to an FixedString.
    */
    //@{
    EE_EFD_ENTRY friend bool operator==(
        const FixedString& s1,
        const FixedString& s2);
    EE_EFD_ENTRY friend bool operator!=(
        const FixedString& s1,
        const FixedString& s2);

    EE_EFD_ENTRY friend bool operator==(
        const FixedString& s1,
        const efd::Char* s2);
    EE_EFD_ENTRY friend bool operator!=(
        const FixedString& s1,
        const efd::Char* s2);

    EE_EFD_ENTRY friend bool operator==(
        const efd::Char* s1,
        const FixedString& s2);
    EE_EFD_ENTRY friend bool operator!=(
        const efd::Char* s1,
        const FixedString& s2);
    //@}

protected:
    GlobalStringTable::GlobalStringHandle m_handle;
};

#include <efd/FixedString.inl>

///
///  Helper functions that assist in comparing strings. FixedString to
/// FixedString comparison is very fast since it is a simple pointer
/// value comparison and does not need to de-reference the efd::Character
/// array. FixedString to efd::Character array comparisons have been
/// accelerated for the case where the efd::Character array is really pointing
/// to an FixedString.
///
/// @name String comparison operators from FixedString.h

//@{

EE_EFD_ENTRY bool operator==(const FixedString& s1, const FixedString& s2);

EE_EFD_ENTRY bool operator!=(const FixedString& s1, const FixedString& s2);

EE_EFD_ENTRY bool operator==(const FixedString& s1, const efd::Char* s2);

EE_EFD_ENTRY bool operator!=(const FixedString& s1, const efd::Char* s2);

EE_EFD_ENTRY bool operator==(const efd::Char* s1, const FixedString& s2);

EE_EFD_ENTRY bool operator!=(const efd::Char* s1, const FixedString& s2);

//@}

} // end namespace efd


#endif
