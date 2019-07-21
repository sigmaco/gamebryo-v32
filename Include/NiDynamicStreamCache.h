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
#ifndef NIDYNAMICSTREAMCACHE_H
#define NIDYNAMICSTREAMCACHE_H

#include <NiTArray.h>
#include <NiMemorydefines.h>
#include <NiDataStream.h>

#include "NiTerrainLibType.h"
#include "NiTerrainResourceManager.h"

/**
    A dynamic stream cache is a manager that takes care of allocation and
    de-allocation of dynamic position and normal/tangent streams on behalf of a
    terrain sector.

    It should be regarded as internal use only.

    @internal
 */
class NITERRAIN_ENTRY NiDynamicStreamCache : public NiRefObject
{

public:
    // Expose the stream types
    typedef NiTerrainResourceManager::StreamType StreamType;

    /**
        Default constructor
        @param pkResourceManager The terrain ressource manager
    */
    NiDynamicStreamCache(NiTerrainResourceManager* pkResourceManager);

    /// Destructor
    virtual ~NiDynamicStreamCache();

    /**
        Request a stream of the given type from the cache.

        If no streams of desired type are available the cache will grow
        by the preset 'GrowBy' amount.

        @param eStreamType The type of stream requested
        @return A data stream from the cache, who's data is allocated but
            undefined.
    */
    NiDataStream* RequestStream(StreamType::Value eStreamType);

    /**
        Initializes the stream cache for the given type and grows it to the
        given initial size.

        @param eStreamType The stream type for which to initialize the cache
        @param uiInitialSize The number of entries that will initially be
            available for request in the cache
        @param uiGrowBy When the cache is full, expand it by this amount

        @return false if not all streams could be created. Note, that some
            entries may have been created if this occurs
    */
    bool InitializeStreamCache(
        StreamType::Value eStreamType,
        NiUInt32 uiInitialSize, 
        NiUInt32 uiGrowBy);

    /**
        Get the number of streams that have been requested for the given
        type.

        @param eStreamType the type of stream to count
        @return the Number of streams
    */
    NiUInt32 GetCurrentSize(StreamType::Value eStreamType);

    /**
        Get the total number of streams that are contained within the cache
        for the given type.

        @param eStreamType the type of stream to count
        @return the Number of streams
    */
    NiUInt32 GetMaxSize(StreamType::Value eStreamType);

    /**
        Get the number of streams of the given type that may be requested
        before the cache needs to grow.

        @param eStreamType the type of stream to count
        @return the Number of streams
    */
    NiUInt32 GetNumAvailable(StreamType::Value eStreamType);

private:

    NiUInt32 m_uiStreamSize;

    NiTObjectArray<NiDataStreamPtr> m_akStreams[StreamType::NUM_STREAM_TYPES];
    NiUInt32 m_auiCurrentPosition[StreamType::NUM_STREAM_TYPES];

    NiDataStreamElementSet m_akElements[StreamType::NUM_STREAM_TYPES];
    NiDataStream::Usage m_aeUsage[StreamType::NUM_STREAM_TYPES];
    NiUInt8 m_aucAccessMask[StreamType::NUM_STREAM_TYPES];
    NiTerrainResourceManager* m_pkResourceManager;
};

NiSmartPointer(NiDynamicStreamCache);

#endif // AEDYNAMICSTREAMCACHE_H
