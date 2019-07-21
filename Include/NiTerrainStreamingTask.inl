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

//--------------------------------------------------------------------------------------------------
inline NiTerrainStreamingTask::NiTerrainStreamingTask() :
    m_kStatus(Status::INVALID),
    m_uiErrorCode(0),
    m_bWaiting(false),
    m_bBegun(false),
    m_bComplete(false),
    m_kClosed(m_kMutex, false),
    m_uiMaxWorkUnits(1),
    m_uiNumWorkUnits(0),
    m_uiCompletedWorkUnits(0),
    m_pkTerrain(NULL),
    m_pkSector(NULL),
    m_iTargetLOD(SpecialLevelOfDetail::UNCHANGED),
    m_iOriginalLOD(-2),
    m_bRebuildFromHeightmap(false),
    m_bCreateBlankHeightData(false),
    m_bOutputNormals(false),
    m_bOutputTangents(false),
    m_bOutputMorphing(false),
    m_bOutputLowDetailNormalMap(false),
    m_bOutputLowDetailDiffuseMap(false),
    m_bOutputBlendMasks(false),
    m_bBuildNormals(false),
    m_bBuildTangents(false),
    m_bBuildLowDetailNormalMap(false),
    m_kTaskType(TaskType::UNINITIALIZED),
    m_uiNumBlendMasksPerSide(0),
    m_pkDividedBlendMasks(NULL),
    m_pfHeights(NULL),
    m_pkNormals(NULL),
    m_pkTangents(NULL),
    m_pkBounds(NULL),
    m_pkSurfaceIndexes(NULL)
{
}

//--------------------------------------------------------------------------------------------------
inline NiTerrainStreamingTask::~NiTerrainStreamingTask()
{
    EE_ASSERT(!m_bBegun);
    EE_ASSERT(m_kClosed.GetValue() == true);
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainStreamingTask::SetStatus(Status::VALUE kStatus)
{
    m_kMutex.Lock();
    m_kStatus = kStatus;

    EE_ASSERT(kStatus != Status::INVALID);
    if (kStatus != Status::CANCELLED)
        CalculateNumWorkUnits();

    m_kMutex.Unlock();
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainStreamingTask::SetSector(NiTerrainSector* pkSector)
{
    EE_ASSERT(m_kStatus == Status::INVALID);
    EE_ASSERT(pkSector);
    m_pkSector = pkSector;
    m_pkTerrain = pkSector->GetTerrain();
    m_kBuildRegion.m_left = 0;
    m_kBuildRegion.m_right = pkSector->GetSectorData()->GetSectorWidthInVerts() - 1;
    m_kBuildRegion.m_top = pkSector->GetSectorData()->GetSectorWidthInVerts() - 1;
    m_kBuildRegion.m_bottom = 0;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainStreamingTask::SetTargetLOD(NiInt32 iTargetLOD)
{
    EE_ASSERT(m_kStatus == Status::INVALID);
    m_iTargetLOD = iTargetLOD;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainStreamingTask::SetBuildRegion(NiRect<NiInt32> kRegion)
{
    EE_ASSERT(m_kStatus == Status::INVALID);
    EE_ASSERT(kRegion.m_right >= kRegion.m_left);
    EE_ASSERT(kRegion.m_top >= kRegion.m_bottom);
    EE_ASSERT(kRegion.m_left >= 0);
    EE_ASSERT(kRegion.m_right >= 0);
    EE_ASSERT(kRegion.m_top >= 0);
    EE_ASSERT(kRegion.m_bottom >= 0);

    m_kBuildRegion = kRegion;
    m_bRebuildFromHeightmap = true;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainStreamingTask::SetWaiting(bool bWaiting)
{
    m_kMutex.Lock();
    m_bWaiting = bWaiting;
    m_kMutex.Unlock();
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainStreamingTask::CompleteTask(efd::UInt32 eErrorCode)
{
    m_kMutex.Lock();
    m_bComplete = true;
    m_uiErrorCode |= eErrorCode;
    m_kMutex.Unlock();

    Cleanup();
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainStreamingTask::SetCreateBlankHeightData(bool bCreateBlankHeightData)
{
    m_bCreateBlankHeightData = bCreateBlankHeightData;
}

//--------------------------------------------------------------------------------------------------
inline NiTerrainStreamingTask::Status::VALUE NiTerrainStreamingTask::GetStatus() const
{
    return m_kStatus;
}

//--------------------------------------------------------------------------------------------------
inline NiTerrainStreamingTask::TaskType::VALUE NiTerrainStreamingTask::GetTaskType() const
{
    return m_kTaskType;
}

//--------------------------------------------------------------------------------------------------
inline NiTerrain* NiTerrainStreamingTask::GetTerrain() const
{
    return m_pkTerrain;
}

//--------------------------------------------------------------------------------------------------
inline NiInt32 NiTerrainStreamingTask::GetTargetLOD() const
{
    return m_iTargetLOD;
}

//--------------------------------------------------------------------------------------------------
inline NiTerrainSector* NiTerrainStreamingTask::GetSector() const
{
    return m_pkSector;
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiTerrainStreamingTask::GetErrorCode() const
{
    return m_uiErrorCode;
}

//--------------------------------------------------------------------------------------------------
inline bool NiTerrainStreamingTask::GetWaiting() const
{
    return m_bWaiting;
}

//--------------------------------------------------------------------------------------------------
inline bool NiTerrainStreamingTask::GetComplete() const
{
    return m_bComplete;
}
//--------------------------------------------------------------------------------------------------
inline bool NiTerrainStreamingTask::GetCreateBlankHeightData() const
{
    return m_bCreateBlankHeightData;
}
//--------------------------------------------------------------------------------------------------
inline bool NiTerrainStreamingTask::BeginThreading()
{
    m_kMutex.Lock();
    
    bool bCancelled = m_kStatus == Status::CANCELLED;
    m_bBegun = true;

    m_kMutex.Unlock();
    
    return bCancelled;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainStreamingTask::Close()
{
    m_kMutex.Lock();

    EE_ASSERT(GetComplete());
    m_bBegun = false;

    // Signal to any waiting threads that this task is complete
    m_kClosed.SetValue(true);

    m_kMutex.Unlock();
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainStreamingTask::WaitForClose()
{
    m_kMutex.Lock();
    m_kClosed.WaitEqual(true);
    m_kMutex.Unlock();
}

//--------------------------------------------------------------------------------------------------
inline bool NiTerrainStreamingTask::IsClosed()
{
    return m_kClosed.GetValue();
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiTerrainStreamingTask::GetCurrentTotalWorkUnits() const
{
    return m_uiNumWorkUnits;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainStreamingTask::SetMaxWorkUnits(NiUInt32 uiNumWorkUnits)
{
    EE_ASSERT(GetStatus() == Status::INVALID);
    EE_ASSERT(uiNumWorkUnits > 0);

    m_uiMaxWorkUnits = uiNumWorkUnits;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainStreamingTask::StartWorkUnit()
{
}

//--------------------------------------------------------------------------------------------------
inline bool NiTerrainStreamingTask::CompleteWorkUnit()
{
    bool bAllCompleted = false;

    m_kMutex.Lock();

    ++m_uiCompletedWorkUnits;
    if (m_uiCompletedWorkUnits == m_uiNumWorkUnits)
        bAllCompleted = true;

    m_kMutex.Unlock();

    return bAllCompleted;
}
//--------------------------------------------------------------------------------------------------
inline void NiTerrainStreamingTask::CalculateBuildHeightsRegion(NiUInt32 uiStreamWidth)
{
    // Figure out what values require building
    m_kBuildHeightsRegion.m_left = 
        NiClamp(m_kBuildRegion.m_left + 1 - (ms_iBuildNormalKernel), 0, uiStreamWidth - 1);
    m_kBuildHeightsRegion.m_right = 
        NiClamp(m_kBuildRegion.m_right + 1 + (ms_iBuildNormalKernel), 0, uiStreamWidth - 1);
    m_kBuildHeightsRegion.m_top = 
        NiClamp(m_kBuildRegion.m_top + 1 + (ms_iBuildNormalKernel), 0, uiStreamWidth - 1);
    m_kBuildHeightsRegion.m_bottom = 
        NiClamp(m_kBuildRegion.m_bottom + 1 - (ms_iBuildNormalKernel), 0, uiStreamWidth - 1);

    EE_ASSERT(m_kBuildHeightsRegion.m_right >= m_kBuildHeightsRegion.m_left);
    EE_ASSERT(m_kBuildHeightsRegion.m_top >= m_kBuildHeightsRegion.m_bottom);
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainStreamingTask::CalculateBuildLightingRegion(NiUInt32 uiStreamWidth)
{
    // Figure out what values require building
    m_kBuildLightingRegion.m_left = 
        NiClamp(m_kBuildRegion.m_left - (ms_iBuildNormalKernel - 1), 0, uiStreamWidth - 1);
    m_kBuildLightingRegion.m_right = 
        NiClamp(m_kBuildRegion.m_right + (ms_iBuildNormalKernel - 1), 0, uiStreamWidth - 1);
    m_kBuildLightingRegion.m_top = 
        NiClamp(m_kBuildRegion.m_top + (ms_iBuildNormalKernel - 1), 0, uiStreamWidth - 1);
    m_kBuildLightingRegion.m_bottom = 
        NiClamp(m_kBuildRegion.m_bottom - (ms_iBuildNormalKernel - 1), 0, uiStreamWidth - 1);

    EE_ASSERT(m_kBuildLightingRegion.m_right >= m_kBuildLightingRegion.m_left);
    EE_ASSERT(m_kBuildLightingRegion.m_top >= m_kBuildLightingRegion.m_bottom);
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainStreamingTask::GetWorkUnitRegion(NiUInt32 uiWorkUnit, 
    const NiRect<NiInt32>& kTotalRegion, NiRect<NiInt32>& kWorkRegion)
{
    NiInt32 iTotalRegionHeight = kTotalRegion.m_top - kTotalRegion.m_bottom;
    NiInt32 iWorkRegionHeight = iTotalRegionHeight / m_uiNumWorkUnits;

    // The left and right extents are always the same as the total region
    kWorkRegion.m_left = kTotalRegion.m_left;
    kWorkRegion.m_right = kTotalRegion.m_right;

    // The top and bottom of the extent take a portion of the total region
    kWorkRegion.m_bottom = kTotalRegion.m_bottom + uiWorkUnit * iWorkRegionHeight;
    kWorkRegion.m_top = kWorkRegion.m_bottom + iWorkRegionHeight;

    // If we are the last work unit take the largest region (assuming that the total region height
    // is not exactly divisible by the number of work units
    if (uiWorkUnit == m_uiNumWorkUnits - 1)
        kWorkRegion.m_top += iTotalRegionHeight % m_uiNumWorkUnits;

    EE_ASSERT(kWorkRegion.m_top <= kTotalRegion.m_top);
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainStreamingTask::ToString(const char* pcPrefix, NiString& kString)
{
    NiString kStatus; 
    switch(GetStatus())
    {
        case Status::BUILDING_HEIGHTS:
            kStatus = "BUILDING_HEIGHTS";
            break;
        case Status::BUILDING_LIGHTING:
            kStatus = "BUILDING_LIGHTING";
            break;
        case Status::BUILDING_MAPS:
            kStatus = "BUILDING_MAPS";
            break;
        case Status::CANCELLED:
            kStatus = "CANCELLED";
            break;
        case Status::INVALID:
            kStatus = "INVALID";
            break;
        case Status::LOADING:
            kStatus = "LOADING";
            break;
        case Status::PRELOADING:
            kStatus = "PRELOADING";
            break;
        case Status::POPULATING:
            kStatus = "POPULATING";
            break;
        case Status::REMOVING:
            kStatus = "REMOVING";
            break;
        case Status::UNLOADING:
            kStatus = "UNLOADING";
            break;
        default:
            kStatus.Format("%d", GetStatus());
    }

    // In the cancelled and invalid states, the sector pointer may be invalid on the task
    bool bPrintSectorInfo = GetStatus() != Status::CANCELLED && GetStatus() != Status::INVALID;

    if (bPrintSectorInfo)
    {
        NiInt16 sXIndex, sYIndex;
        GetSector()->GetSectorIndex(sXIndex, sYIndex);

        kString.Format("[TID: %d] - %s task on sector [%d, %d] "
            "target:%d->%d type: %d units: %d begun:%s status: %s waiting:%s complete:%s", 
            efd::GetCurrentThreadId(),
            pcPrefix,
            sXIndex, sYIndex, 
            m_iOriginalLOD, GetTargetLOD(), 
            GetTaskType(),
            GetCurrentTotalWorkUnits(),
            m_bBegun ? (const char*)"yes" : (const char*)"no",
            (const char*)kStatus,
            GetWaiting() ? (const char*)"yes" : (const char*)"no",
            GetComplete() ? (const char*)"yes" : (const char*)"no");
    }
    else
    {
        kString.Format("[TID: %d] - %s task on unknown sector "
            "target:%d->%d type: %d units: %d begun:%s status: %s waiting:%s complete:%s", 
            efd::GetCurrentThreadId(),
            pcPrefix,
            m_iOriginalLOD, GetTargetLOD(), 
            GetTaskType(),
            GetCurrentTotalWorkUnits(),
            m_bBegun ? (const char*)"yes" : (const char*)"no",
            (const char*)kStatus,
            GetWaiting() ? (const char*)"yes" : (const char*)"no",
            GetComplete() ? (const char*)"yes" : (const char*)"no");
    }
}

//--------------------------------------------------------------------------------------------------
