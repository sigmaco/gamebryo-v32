// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not 
// be copied or disclosed except in accordance with the terms of that 
// agreement.
//
//      Copyright (c) 1996-2008 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Chapel Hill, North Carolina 27517
// http://www.emergent.net

#ifndef NITERRAINSTREAMLOCKS_H
#define NITERRAINSTREAMLOCKS_H

#include <NiDataStreamLock.h>
#include "NiTerrainRandomAccessIterator.h"

class NiTerrainSector;
class NiTerrainCell;

/**
    This class simplifies the locking and accessing of terrain streams.
    An instance of this class should only be used in the NiTerrain library
    when accessing data in the terrain streams.
*/
class NITERRAIN_ENTRY NiTerrainStreamLocks : public NiMemObject
{
public:

    /**
        Enum defining the diferent stream types
    */
    enum StreamType
    {
        /// Position stream
        POSITION, 
        /// Tangent stream
        TANGENT,
        /// Normal stream
        NORMAL,
        ///Index stream
        INDEX,
        /// Texture coordinate stream
        TEXCOORD
    };
    
    /**
        Default constructor
    */
    NiTerrainStreamLocks();

    /**
        Creates a NiTerrainStreamLocks object and acquires locks for
        all available static streams for the given sector at the given 
        level of detail and using the given lock mask

        @param pkSector pointer to the sector to create locks for
        @param ucLockMask the lock mask to use on the lock (read or write)
        @param uiLevel the level of detail to get the lock for (0 by default)
    */
    NiTerrainStreamLocks(NiTerrainSector* pkSector, NiUInt8 ucLockMask, 
        NiUInt32 uiLevel = 0);

    /**
        Creates a NiTerrainStreamLocks object and acquires locks for all
        available streams for the given block. If some streams are dynamic,
        it will lock the dynamic streams.

        @param pkCell pointer to the cell to get the lock for
        @param ucLockMask the lock mask to use on the lock (read or write)
    */
    NiTerrainStreamLocks(NiTerrainCell* pkCell, NiUInt8 ucLockMask);

    /**
        Destructor. Calls on ReleaseLocks.
    */
    ~NiTerrainStreamLocks();

    /**
        Retrieves a position iterator for a block or for a sector at a 
        specific level. If a lock has been acquired and it does not point to
        the same stream or does not use the same mask, it will release the 
        current lock and acquire the appropriate one.
        If the created iterator exists, this functions return true.
    */
    bool GetPositionIterator(NiTerrainCell* pkCell, 
        NiUInt8 ucLockMask,
        NiTerrainPositionRandomAccessIterator& kPosIter);

    /**
        Retrieves a position iterator for a block or for a sector at a 
        specific level. If a lock has been acquired and it does not point to
        the same stream or does not use the same mask, it will release the 
        current lock and acquire the appropriate one.
        If the created iterator exists, this functions return true.
    */
    bool GetPositionIterator(NiTerrainSector* pkSector, 
        NiUInt8 ucLockMask,
        NiTerrainPositionRandomAccessIterator& kPosIter,
        NiUInt32 uiLevel = 0);

    /**
        Retrieves a Normal iterator for a block or for a sector at a 
        specific level. If a lock has been acquired and it does not point to
        the same stream or does not use the same mask, it will release the 
        current lock and acquire the appropriate one.
        If the created iterator exists, this functions return true.
    */
    bool GetNormalIterator(NiTerrainCell* pkCell, 
        NiUInt8 ucLockMask,
        NiTerrainNormalRandomAccessIterator& kNormalIter);

    /**
        Retrieves a Normal iterator for a block or for a sector at a 
        specific level. If a lock has been acquired and it does not point to
        the same stream or does not use the same mask, it will release the 
        current lock and acquire the appropriate one.
        If the created iterator exists, this functions return true.
    */
    bool GetNormalIterator(NiTerrainSector* pkSector, 
        NiUInt8 ucLockMask,
        NiTerrainNormalRandomAccessIterator& kNormalIter,
        NiUInt32 uiLevel = 0);

    /**
        Retrieves a tangent iterator for a block or for a sector at a 
        specific level. If a lock has been acquired and it does not point to
        the same stream or does not use the same mask, it will release the 
        current lock and acquire the appropriate one.
        If the created iterator exists, this functions return true.
    */
    bool GetTangentIterator(NiTerrainCell* pkCell, 
        NiUInt8 ucLockMask,
        NiTerrainTangentRandomAccessIterator& kTangentIter);

    /**
        Retrieves a tangent iterator for a block or for a sector at a 
        specific level. If a lock has been acquired and it does not point to
        the same stream or does not use the same mask, it will release the 
        current lock and acquire the appropriate one.
        If the created iterator exists, this functions return true.
    */
    bool GetTangentIterator(NiTerrainSector* pkSector, 
        NiUInt8 ucLockMask,
        NiTerrainTangentRandomAccessIterator& kTangentIter,
        NiUInt32 uiLevel = 0);

    /**
        Retrieves an index iterator for a block or for a sector at a 
        specific level and for a specific region. If a lock has been acquired 
        and it does not point to the same stream or does not use the same mask,
        it will release the current lock and acquire the appropriate one.
        If the created iterator exists, this functions return true. 
    */
    bool GetIndexIterator(NiTerrainCell* pkCell, 
        NiUInt8 ucLockMask,
        NiTStridedRandomAccessIterator<NiUInt16>& kIndexIter,
        NiUInt8 ucRegion = 0);

    /**
        Retrieves an index iterator for a block or for a sector at a 
        specific level and for a specific region. If a lock has been acquired 
        and it does not point to the same stream or does not use the same mask,
        it will release the current lock and acquire the appropriate one.
        If the created iterator exists, this functions return true. 
    */
    bool GetIndexIterator(NiTerrainSector* pkSector, 
        NiUInt8 ucLockMask,
        NiTStridedRandomAccessIterator<NiUInt16>& kIndexIter,
        NiUInt8 ucRegion = 0);

    /**
        Retrieves an index iterator for a block or for a sector at a 
        specific level and for a specific region. If a lock has been acquired 
        and it does not point to the same stream or does not use the same mask,
        it will release the current lock and acquire the appropriate one.
        If the created iterator exists, this functions return true.  
    */
    bool GetIndexIterator(NiTerrainCell* pkCell, 
        NiUInt8 ucLockMask,
        NiTStridedRandomAccessIterator<NiUInt32>& kIndexIter,
        NiUInt8 ucRegion = 0); 
    
    /**
        Retrieves an index iterator for a block or for a sector at a 
        specific level and for a specific region. If a lock has been acquired 
        and it does not point to the same stream or does not use the same mask,
        it will release the current lock and acquire the appropriate one.
        If the created iterator exists, this functions return true.  
    */
    bool GetIndexIterator(NiTerrainSector* pkSector, 
        NiUInt8 ucLockMask,
        NiTStridedRandomAccessIterator<NiUInt32>& kIndexIter,
        NiUInt8 ucRegion = 0);

    /**
        Retrieves a UV iterator for a block or for a sector at a 
        specific level. If a lock has been acquired and it does not point to
        the same stream or does not use the same mask, it will release the 
        current lock and acquire the appropriate one.
        If the created iterator exists, this functions return true.
    */
    bool GetUVIterator(NiTerrainCell* pkCell, 
        NiUInt8 ucLockMask,
        NiTStridedRandomAccessIterator<NiPoint2>& kUVIter);

    /**
        Retrieves a UV iterator for a block or for a sector at a 
        specific level. If a lock has been acquired and it does not point to
        the same stream or does not use the same mask, it will release the 
        current lock and acquire the appropriate one.
        If the created iterator exists, this functions return true.
    */
    bool GetUVIterator(NiTerrainSector* pkSector, 
        NiUInt8 ucLockMask,
        NiTStridedRandomAccessIterator<NiPoint2>& kUVIter);
    
    /**
        Releases all created locks
    */
    void ReleaseLocks();
    
    /**
        Releases a specific lock
    */
    void ReleaseLock(StreamType eStream);
    

private:

    /**
        Acquires all available locks for the given block or the given
        sector at the specific level and using the given mask lock
    */
    void AcquireLocks(NiTerrainCell* pkCell, NiUInt8 ucLockMask);

    /**
        Acquires all available locks for the given block or the given
        sector at the specific level and using the given mask lock
    */
    void AcquireLocks(NiTerrainSector* pkSector, NiUInt8 ucLockMask, 
        NiUInt32 uiLevel = 0);
    
    /**
        Acquires a specific stream for a given block or for a given sector
        at a specific level of details
    */
    void AcquireLock(StreamType eStreamType, NiTerrainCell* pkCell, 
        NiUInt8 ucLockMask);

    /**
        Acquires a specific stream for a given block or for a given sector
        at a specific level of details
    */
    void AcquireLock(StreamType eStreamType, NiTerrainSector* pkSector, 
        NiUInt8 ucLockMask, NiUInt32 uiLevel = 0);
    
    /**
        Checks if we already have the lock we want for a given block or for
        the given sector at the specified detail level.
        Also checks if the lock uses the right lock mask.
        Returns True if it is the case.
    */
    bool IsLockInitialized(StreamType eStreamType, NiTerrainSector* pkSector, 
        NiUInt8 ucLockMask,
        NiUInt32 uiLevel = 0);

    /**
        Checks if we already have the lock we want for a given block or for
        the given sector at the specified detail level.
        Also checks if the lock uses the right lock mask.
        Returns True if it is the case.
    */
    bool IsLockInitialized(StreamType eStreamType, NiTerrainCell* pkCell, 
        NiUInt8 ucLockMask);
    
    /**
        Makes sure a lock is initialised. If it is not it will release that
        lock and acquire the appropriate lock.
    */
    void VerifyLock(StreamType eStreamType, NiTerrainCell* pkCell, 
        NiUInt8 ucLockMask);

    /**
        Makes sure a lock is initialised. If it is not it will release that
        lock and acquire the appropriate lock.
    */
    void VerifyLock(StreamType eStreamType, NiTerrainSector* pkSector, 
        NiUInt8 ucLockMask, NiUInt32 uiLevel = 0);
    
    ///@name Stream locks
    //@{
    /// We keep the last set stream locks in order to reuse them

    /// The index stream lock
    NiDataStreamLock m_kIndexLock;
    /// The UV stream lock
    NiDataStreamLock m_kUVLock;
    /// The position stream lock
    NiDataStreamLock m_kPositionLock;
    /// The normal stream lock
    NiDataStreamLock m_kNormalLock;
    /// The tangent stream lock
    NiDataStreamLock m_kTangentLock;
    //@}

    /// Array that keeps the current lock masks for the locks currently held
    NiUInt8 m_aucCurrentLockMask[5];
};


#endif