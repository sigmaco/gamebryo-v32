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
#ifndef EE_EXTERNALMEMALLOCATOR_H
#define EE_EXTERNALMEMALLOCATOR_H

#include <efd/IAllocator.h>

namespace efd
{

/// Manage allocation of external memory resources.
class ExternalMemAllocator : public IAllocator
{
public:
    // Overridden virtual functions inherit base documentation and thus are not documented here.

    virtual void* Allocate(
        size_t& stSize,
        size_t& stAlignment,
        MemHint kHint,
        MemEventType eEventType,
        const char* pcFile,
        int iLine,
        const char* pcFunction);

    virtual void Deallocate(
        void* pvMemory,
        MemEventType eEventType,
        size_t stSizeinBytes);

    virtual void* Reallocate(
        void* pvMemory,
        size_t& stSize,
        size_t& stAlignment,
        MemHint kHint,
        MemEventType eEventType,
        size_t stSizeCurrent,
        const char* pcFile,
        int iLine,
        const char* pcFunction);

    virtual bool TrackAllocate(
        const void* const pvMemory,
        size_t stSizeInBytes,
        MemHint kHint,
        MemEventType eEventType,
        const char* pcFile,
        int iLine,
        const char* pcFunction);

    virtual bool TrackDeallocate(
        const void* const pvMemory,
        MemEventType eEventType);

    virtual bool SetMarker(
        const char* pcMarkerType,
        const char* pcClassifier,
        const char* pcString);

    virtual void Initialize();
    virtual void Shutdown();
    virtual bool VerifyAddress(const void* pvMemory);
    virtual void CreateMemoryLogHandler();
};

}   // End namespace efd.

#include <efd/ExternalMemAllocator.inl>

#endif // EE_EXTERNALMEMALLOCATOR_H
