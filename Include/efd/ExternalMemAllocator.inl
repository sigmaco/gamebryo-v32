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


namespace efd
{

//--------------------------------------------------------------------------------------------------
inline void* ExternalMemAllocator::Allocate(
    size_t& stSizeInBytes,
    size_t& stAlignment,
    MemHint,
    MemEventType,
    const char*,
    int,
    const char*)
{
    EE_ASSERT(EE_IS_POWER_OF_TWO(stAlignment));

    return EE_EXTERNAL_ALIGNED_MALLOC(stSizeInBytes, stAlignment);
}

//--------------------------------------------------------------------------------------------------
inline void ExternalMemAllocator::Deallocate(
    void* pvMemory,
    MemEventType,
    size_t)
{
    if (pvMemory == NULL)
        return;

    EE_EXTERNAL_ALIGNED_FREE(pvMemory);
}

//--------------------------------------------------------------------------------------------------
inline void* ExternalMemAllocator::Reallocate(
    void* pvMemory,
    size_t& stSizeInBytes,
    size_t& stAlignment,
    MemHint,
    MemEventType,
    size_t,
    const char*,
    int,
    const char*)
{
    EE_ASSERT(EE_IS_POWER_OF_TWO(stAlignment));

    // The deallocation case should have been caught by us before in the allocation functions.
    EE_ASSERT(stSizeInBytes != 0);

    return EE_EXTERNAL_ALIGNED_REALLOC(pvMemory, stSizeInBytes, stAlignment);
}

//--------------------------------------------------------------------------------------------------
inline bool ExternalMemAllocator::TrackAllocate(
    const void* const,
    size_t,
    MemHint,
    MemEventType,
    const char*,
    int,
    const char*)
{
    return false;
}

//--------------------------------------------------------------------------------------------------
inline bool ExternalMemAllocator::TrackDeallocate(
    const void* const,
    MemEventType)
{
    return false;
}

//--------------------------------------------------------------------------------------------------
inline bool ExternalMemAllocator::SetMarker(const char*,
    const char*, const char*)
{
    return true;
}

//--------------------------------------------------------------------------------------------------
inline void ExternalMemAllocator::Initialize()
{
}

//--------------------------------------------------------------------------------------------------
inline void ExternalMemAllocator::Shutdown()
{
}

//--------------------------------------------------------------------------------------------------
inline bool ExternalMemAllocator::VerifyAddress(const void*)
{
    return true;
}

//--------------------------------------------------------------------------------------------------
inline void ExternalMemAllocator::CreateMemoryLogHandler()
{
}

//--------------------------------------------------------------------------------------------------

}   // End namespace efd.
