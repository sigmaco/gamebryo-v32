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
#ifndef EE_GLOBALSTRINGTABLE_H
#define EE_GLOBALSTRINGTABLE_H

#include <efd/efdLibType.h>
#include <efd/MemObject.h>
#include <efd/CriticalSection.h>
#include <efd/Utilities.h>
#include <efd/StdContainers.h>

namespace efd
{
/**
    An internal-only class used for managing FixedStrings.
*/
class EE_EFD_ENTRY GlobalStringTable : public MemObject
{
    friend class StaticFixedString;

public:
    typedef efd::Char* GlobalStringHandle;

    static GlobalStringTable& Get();

    // Global string handle interfaces
    static GlobalStringHandle AddString(const efd::Char* pString);
    static void IncRefCount(GlobalStringHandle& handle);
    static void DecRefCount(GlobalStringHandle& handle);
    static const efd::Char* GetString(const GlobalStringHandle& handle);
    static size_t GetLength(const GlobalStringHandle& handle);
    static size_t GetRefCount(const GlobalStringHandle& handle);
    static bool ValidateString(const GlobalStringHandle& handle);

    // Begin Emergent internal use only
    static size_t GetBucketSize(efd::UInt32 uiWhichBucket);
    static inline size_t GetTotalNumberOfBuckets();
    static size_t GetMaxBucketSize();

    static const GlobalStringHandle NULL_STRING;
    static size_t ms_numStrings;
    static size_t ms_numCollisions;

    enum
    {
        GSTABLE_LEN_MASK        = 0x0000FFFF,
        GSTABLE_LEN_SHIFT       = 0,
        GSTABLE_HASH_MASK       = 0xFFFF0000,
        GSTABLE_HASH_SHIFT      = 16,
        GSTABLE_NUM_GLOBAL_STRING_HASH_BUCKETS  = 513,
        GSTABLE_NUM_ENTRIES_PER_BUCKET_GROWBY   = 10
    };

    static void _SDMInit();
    static void _SDMShutdown();
    // End Emergent internal use only

protected:
    GlobalStringHandle FindString(const efd::Char* pString, size_t len);
    void InsertString(const GlobalStringHandle& handle, efd::UInt32 hash);
    void RemoveString(const GlobalStringHandle& handle, efd::UInt32 hashValue);
    static efd::Char* GetRealBufferStart(const GlobalStringHandle& handle);

    static efd::UInt32 HashFunction(const efd::Char* pKey, size_t len);
    static inline efd::UInt32 GetHashValue(const GlobalStringHandle& handle);

    GlobalStringTable();

    efd::vector<GlobalStringHandle> m_hashArray[GSTABLE_NUM_GLOBAL_STRING_HASH_BUCKETS];
    CriticalSection m_criticalSection;
    static GlobalStringTable* ms_pGlobalStringTable;
};

} // end namespace efd

#include <efd/GlobalStringTable.inl>

#endif
