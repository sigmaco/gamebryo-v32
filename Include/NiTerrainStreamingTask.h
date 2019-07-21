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

#ifndef NITERRAINSTREAMINGTASK_H
#define NITERRAINSTREAMINGTASK_H

#include "NiTerrainStreamLocks.h"
#include "NiTerrainTaskProcessor.h"
#include "NiTerrainSector.h"
#include "NiTerrainSectorFile.h"
#include "NiTerrainConditionVariable.h"

class NiTerrainSector;
class NiPixelData;
class NiTerrainSectorFile;

/**
    This class contains all the functionality required to load, unload or rebuild a terrain.

    It consists of a set of jobs, each in the form of a function. Most jobs are not 
    parallelizable, in that it can only be split up into a single work unit. The building task can 
    be split up into multiple work units, which can run over multiple threads. When a job is split,
    it will not be removed from the relevant queue until all work units have been allocated threads.
 */
class NiTerrainStreamingTask : public NiRefObject
{
    /// @cond EMERGENT_INTERNAL
    NiDeclareRTTI;
    /// @endcond

public:

    /// Task status. At any one point in time, the task will be in one of these states
    struct Status
    {
        enum VALUE
        {
            /// A state for when the task has just been created and not initialized for execution 
            /// yet. 
            INVALID,
            /// A state to show that the task has been cancelled
            CANCELLED,
            /// A state to indicate that the task is preloading data from disk
            PRELOADING,
            /// A state to indicate that the task is decoding data from disk
            LOADING,
            /// A state to indicate that the task is unloading data in a sector
            UNLOADING,
            /// A state to indicate that the task is removing a sector from the terrain
            REMOVING,
            /// A state to indicate that the task is building the heightmap of a sector
            BUILDING_HEIGHTS,
            /// A state to indicate that the task is building the lighting of a sector
            BUILDING_LIGHTING,
            /// A state to indicate that the task is building the textures of a sector
            BUILDING_MAPS,
            /// A state to indicate that the task is locking its streams/textures
            LOCKING,
            /// A state to indicate that the task is populating the sector data structures
            POPULATING,
            /// A state to indicate that the task is unlocking its streams/textures
            UNLOCKING
        };
    };

    /// An enumeration to indicate special types of levels of detail parameters
    struct SpecialLevelOfDetail
    {
        enum VALUE
        {
            /// When an LOD parameter is this value, it means the value should be unchanged
            UNCHANGED = -2,
            /// When an LOD parameter is this value, it means to unload all of the LOD's
            UNLOAD = -1,
            /// The lowest level of detail that can be loaded
            BASE = 0
        };
    };

    /// An enumeration to indicate different types of tasks
    struct TaskType
    {
        enum VALUE
        {
            /// The task has been uninitialized and so does not have a type yet
            UNINITIALIZED,
            /// The task is for loading data into a sector
            LOADING,
            /// The task is for removing data from a sector
            UNLOADING,
            /// The task is for rebuilding data in a sector
            REBUILDING
        };
    };

    /// Constructor
    NiTerrainStreamingTask();
    /// Destructor
    ~NiTerrainStreamingTask();

    /// @name Task configuration
    /// @{

    /// Set the status of the task
    inline void SetStatus(Status::VALUE kStatus);
    /// Set the sector to operate upon
    inline void SetSector(NiTerrainSector* pkSector);
    /// Set the level of detail to target in this task
    inline void SetTargetLOD(efd::SInt32 iTargetLOD);
    /// Set the region over which to build the data of a sector
    inline void SetBuildRegion(NiRect<efd::SInt32> kRegion);
    /// Set whether or not this task is currently waiting on a queue
    inline void SetWaiting(bool bWaiting);
    /// Set whether or not to use blank height data when loading
    inline void SetCreateBlankHeightData(bool bCreateBlankHeightData);

    /// Query the task for it's status
    inline Status::VALUE GetStatus() const;
    /// Query the task for it's type
    inline TaskType::VALUE GetTaskType() const;
    /// Query the task for the sector that it is operating upon
    inline NiTerrainSector* GetSector() const;
    /// Query the task for the terrain that it is operating upon
    inline NiTerrain* GetTerrain() const;
    /// Query the task for the level of detail is targeting
    inline NiInt32 GetTargetLOD() const;
    /// Query the task for its error code
    inline NiUInt32 GetErrorCode() const;
    /// Query the task for its waiting state (false if it is currently executing)
    inline bool GetWaiting() const;
    /// Query the state of the completion of the task
    inline bool GetComplete() const;
    /// Query if the task will be creating blank height data
    inline bool GetCreateBlankHeightData() const;
    /// @}

    /// Helper function to generate strings for debugging output
    inline void ToString(const char* pcPrefix, NiString& kString);

    /// @name Job Parallelization (work units)
    /// @{

    /// Get the total number of work units to be executed on this task in its current state
    inline NiUInt32 GetCurrentTotalWorkUnits() const;
    /// Set the maximum number of work units this task can generate per state
    inline void SetMaxWorkUnits(efd::UInt32 uiNumWorkUnits);
    /// Start a single work unit
    inline void StartWorkUnit();
    /// Complete a work unit
    inline bool CompleteWorkUnit();
    /// @}

    /**
        Call this function after creating a task and configuring it before submitting it to a queue
        for processing
    */
    void Initialize();

    /// Attempt to cancel this task. Returns true if successfull
    bool Cancel();
    /// Close this task. This will signal any threads waiting on the completion of this task
    void Close();
    /// Pause the current thread until another thread closes this task
    void WaitForClose();
    /// Query if the task has been closed
    bool IsClosed();
    /// Calculate the region to build heights over
    void CalculateBuildHeightsRegion(efd::UInt32 uiStreamWidth);
    /// Calculate the region to build lighting over
    void CalculateBuildLightingRegion(efd::UInt32 uiStreamWidth);

    /// @name Task processing pipeline stages
    /// @{

    /// Preload data from disk for the execution of this task
    void Preload();
    /// Decode the data from disk into usable buffers
    void LoadBuffers();
    /// Build the blend mask textures for the sector
    void BuildBlendMasks();
    /// Build the heightmap for this sector
    void BuildHeights(efd::UInt32 uiWorkUnit);
    /// Build the lighting for this sector
    void BuildLighting(efd::UInt32 uiWorkUnit);
    /// Build the low detail normal map for this sector
    void BuildLowDetailNormalMap();
    /// Acquire the locks for the sector's data
    void AcquireLocks();
    /// Populate the sector's data streams with the loaded buffers
    void PopulateStreams();
    /// Release the locks on the sectors's data
    void ReleaseLocks();
    /// Unload the data from the streams in the sector
    void UnloadStreams();
    /// Remove the sector from the terrain
    void RemoveFromTerrain();
    /// Flag the task as completed with a certain error code
    inline void CompleteTask(efd::UInt32 uiErrorCode);
    /// @}

private:

    /// @name Processing pipeline helper functions
    /// @{

    /// Call this function to pre-load data from the sector files depending on what data is required
    bool PreloadSectorFiles();
    /// Call this function to load all the heightmaps from the sectors that have been preloaded
    bool LoadSectorHeights();
    /// Call this function to allocate buffers for all the required pieces of data
    void PrepareBuffers();
    /// Call this function to prepare a sector to receive new cell data
    bool PrepareSector();
    /// Call this function to apply the loaded textures to the relevant objects
    void ApplyTextures();
    /// Call this function after all the cells have been modified to update the sectors data
    bool FinilizeSectorLoading();
    /// Call this function to populate the cells of the sector
    void PopulateCells();
    /// Call this function to populate the streams of a given cell
    bool PopulateCellStreams(NiTerrainCell* pkCell, 
        NiTerrainPositionRandomAccessIterator& kPositions,
        NiTerrainNormalRandomAccessIterator& kNormals,
        NiTerrainTangentRandomAccessIterator& kTangents);
    /// Call this function to empty and release any buffers used by this task
    void Cleanup();
    /// Call this function to sample the height at the given coordinates on the heightmap
    float SampleHeightMap(efd::SInt32 iX, efd::SInt32 iY);
    /// Call this function to generate a blank heightmap
    NiTerrainSector::HeightMap* CreateBlankSectorHeightmap();
    /// Call this function to fetch a cached heightmap for the given sector
    NiTerrainSector::HeightMap* FetchSectorHeightmap(efd::SInt32 iSectorX, efd::SInt32 iSectorY);
    /// This function is called to indicate a point at which cancellation cannot be achieved.
    bool BeginThreading();
    /// This function is called when acquiring locks in a loading task
    void AcquireLocks_Loading();
    /// This function is called when acquiring locks in an unloading task
    void AcquireLocks_Unloading();
    /// This function is called when releasing locks in a loading task
    void ReleaseLocks_Loading();
    /// This function is called when releasing locks in an unloading task
    void ReleaseLocks_Unloading();
    /// @}

    /// Calculate the total number of work units required for the current state
    void CalculateNumWorkUnits();
    /// Calculate the region over which a given work unit is to work
    void GetWorkUnitRegion(efd::UInt32 uiWorkUnit, const NiRect<efd::SInt32>& kTotalRegion, 
        NiRect<efd::SInt32>& kWorkRegion);

    /// @name Task status management
    /// @{

    /// The current status of the task
    Status::VALUE m_kStatus;
    /// The error code generated by the task
    efd::UInt32 m_uiErrorCode;
    /// A flag to show if the task is currently waiting on a queue
    bool m_bWaiting;
    /// A flag to show if the task has begun execution yet
    bool m_bBegun;
    /// A flag to show if the task has been completed
    bool m_bComplete;
    /// A mutex to protect the task's state
    efd::CriticalSection m_kMutex;
    /// A pollable flag to indicate when a task has been closed off
    NiTerrainPollableValue<bool> m_kClosed;
    /// @}
 
    /// @name Task and work unit Parallelization
    /// @{

    /// The maximum number of work units a task can generate per state
    efd::UInt32 m_uiMaxWorkUnits;
    /// The number of work units to be completed in the current state
    efd::UInt32 m_uiNumWorkUnits;
    /// The number of completed work units in the current state
    efd::UInt32 m_uiCompletedWorkUnits;
    /// @}
        
    /// @name Task configuration
    /// @{

    /// The terrain being operated upon
    NiTerrain* m_pkTerrain;
    /// The sector being operated upon
    NiTerrainSector* m_pkSector;
    /// The target LOD for the task
    efd::SInt32 m_iTargetLOD;
    /// The original LOD of the sector before the task began execution
    efd::SInt32 m_iOriginalLOD;
    /// The build region of the task 
    NiRect<efd::SInt32> m_kBuildRegion;
    /// A flag to signal to rebuild the data on the terrain instead of loading it
    bool m_bRebuildFromHeightmap;
    /// A flag to signal to generate blank geometry data
    bool m_bCreateBlankHeightData;
    /// @}

    /// @name Task Analysis results
    /// @{

    /// A flag to indicate if normals should be output to the sector
    bool m_bOutputNormals;
    /// A flag to indicate if tangents should be output to the sector
    bool m_bOutputTangents;
    /// A flag to indicate if morphing data should be output to the sector
    bool m_bOutputMorphing;
    /// A flag to indicate if low detail normal map should be output to the sector
    bool m_bOutputLowDetailNormalMap;
    /// A flag to indicate if low detail diffuse map should be output to the sector
    bool m_bOutputLowDetailDiffuseMap;
    /// A flag to indicate if blend masks should be output to the sector
    bool m_bOutputBlendMasks;
    /// A flag to indicate if normals require building
    bool m_bBuildNormals;
    /// A flag to indicate if tangents require building
    bool m_bBuildTangents;
    /// A flag to indicate if the low detail normal map requires building
    bool m_bBuildLowDetailNormalMap;
    /// The type of task this has been determined to be
    TaskType::VALUE m_kTaskType;
    /// The region over which to build heights
    NiRect<efd::SInt32> m_kBuildHeightsRegion;
    /// The region over which to build lighting
    NiRect<efd::SInt32> m_kBuildLightingRegion;
    /// The region over which to rebuild the normal map
    NiRect<efd::SInt32> m_kNormalMapRegion;
    /// The number of blend masks to divide into per side
    efd::UInt32 m_uiNumBlendMasksPerSide;
    /// @}

    /// @name Buffers used by this task
    /// @{

    /// The preloaded sector files
    NiTerrainSectorFilePtr m_aspSectorFiles[3][3];
    /// The cached and loaded heightmaps
    NiTerrainSector::HeightMapPtr m_aspHeightMaps[3][3];
    /// The normal map to populate or update
    NiPixelDataPtr m_spNormalMap;
    /// The diffuse map to populate or update
    NiPixelDataPtr m_spDiffuseMap;
    /// The loaded blend mask
    NiPixelDataPtr m_spBlendMask;
    /// The array of divided up blend masks
    NiPixelData** m_pkDividedBlendMasks;
    /// The built height map buffer
    efd::Float32* m_pfHeights;
    /// The built normals buffer
    efd::Point2* m_pkNormals;
    /// The built tangents buffer
    efd::Point2* m_pkTangents;
    /// The loaded bounds buffer
    NiTerrainSectorFile::CellData* m_pkBounds;
    /// The loaded surface indexes buffer
    NiTerrainSectorFile::LeafData* m_pkSurfaceIndexes;
    /// An iterator to access the height map buffer
    NiTStridedRandomAccessIterator<efd::Float32> m_kHeightIterator;
    /// An iterator to access the normal buffer
    NiTStridedRandomAccessIterator<efd::Point2> m_kNormalIterator;
    /// An iterator to access the tangent buffer
    NiTStridedRandomAccessIterator<efd::Point2> m_kTangentIterator;
    /// @}

    /// The size of the kernel required to build normals and normal maps
    static const NiInt32 ms_iBuildNormalKernel = 3;
};
NiSmartPointer(NiTerrainStreamingTask);

#include "NiTerrainStreamingTask.inl"

#endif
