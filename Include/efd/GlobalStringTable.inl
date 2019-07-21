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

#include <efd/AtomicOperations.h>

namespace efd
{

//-------------------------------------------------------------------------------------------------
inline char* GlobalStringTable::GetRealBufferStart(
    const GlobalStringHandle& handle)
{
    EE_ASSERT(handle != NULL);
    return ((char*)handle - 2*sizeof(size_t));
}

//-------------------------------------------------------------------------------------------------
inline void GlobalStringTable::IncRefCount(GlobalStringHandle& handle)
{
    if (handle == NULL_STRING)
        return;

    EE_ASSERT(ValidateString(handle));
    size_t* mem = (size_t*)GetRealBufferStart(handle);
    AtomicIncrement(mem[0]);
}

//-------------------------------------------------------------------------------------------------
inline void GlobalStringTable::DecRefCount(GlobalStringHandle& handle)
{
    if (handle == NULL_STRING)
        return;

    EE_ASSERT(ValidateString(handle));
    size_t* mem = (size_t*)GetRealBufferStart(handle);

    // We must get the hash value before we decrement. After decrementing,
    // the fixed string could be deleted in another thread which would
    // make the results of any hash retrieval invalid.
    unsigned int hash = GetHashValue(handle);

    if (AtomicDecrement(mem[0]) == 1)
    {
        Get().RemoveString(handle, hash);
    }
}

//-------------------------------------------------------------------------------------------------
inline const char* GlobalStringTable::GetString(
    const GlobalStringHandle& handle)
{
    EE_ASSERT(ValidateString(handle));
    // No need to perform an if NULL_STRING check, because
    // it will correctly return NULL if handle == NULL_STRING
    return (const char*) handle;
}

//-------------------------------------------------------------------------------------------------
inline size_t GlobalStringTable::GetLength(
    const GlobalStringHandle& handle)
{
    if (handle == NULL_STRING)
    {
        return 0;
    }
    else
    {
        EE_ASSERT(ValidateString(handle));
        size_t* mem = (size_t*)GetRealBufferStart(handle);
        return ((unsigned int)mem[1] & GSTABLE_LEN_MASK) >>
            GSTABLE_LEN_SHIFT;
    }
}

//-------------------------------------------------------------------------------------------------
inline size_t GlobalStringTable::GetRefCount(
    const GlobalStringHandle& handle)
{
    if (handle == NULL_STRING)
    {
        return 0;
    }
    else
    {
        EE_ASSERT(ValidateString(handle));
        size_t* mem = (size_t*)GetRealBufferStart(handle);
        return (unsigned int)mem[0];
    }
}

//-------------------------------------------------------------------------------------------------
inline unsigned int GlobalStringTable::GetHashValue(
    const GlobalStringHandle& handle)
{
    // Get the hash value stored in the global string handle. We don't
    // perform a null check here. Since this method is protected, we assume
    // the calling context of GlobalStringTable has verified the handle to
    // be non-null.
    EE_ASSERT(ValidateString(handle));
    size_t* mem = (size_t*)GetRealBufferStart(handle);
    return ((unsigned int)mem[1] & GSTABLE_HASH_MASK) >> GSTABLE_HASH_SHIFT;
}

//-------------------------------------------------------------------------------------------------
inline bool GlobalStringTable::ValidateString(
    const GlobalStringHandle& handle)
{
    if (handle == NULL_STRING)
        return true;

    size_t* mem = (size_t*)GetRealBufferStart(handle);
    size_t length = (mem[1] & GSTABLE_LEN_MASK) >> GSTABLE_LEN_SHIFT;

    if (length != strlen((const char*)handle))
        return false;

    return true;
}

//-------------------------------------------------------------------------------------------------
inline size_t GlobalStringTable::GetTotalNumberOfBuckets()
{
    return GSTABLE_NUM_GLOBAL_STRING_HASH_BUCKETS;
}

//-------------------------------------------------------------------------------------------------
} // end namespace efd

