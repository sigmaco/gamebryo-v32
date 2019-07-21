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

#ifndef NITERRAINSECTORSELECTOR
#define NITERRAINSECTORSELECTOR

class NiTerrain;

/**
    This class is meant to select a list of sectors that should be added to the terrain. 
    This default selector will find all sectors on disk in the defined range and load them. 
    It should only be used if we want to load all sectors at once.
*/
class NITERRAIN_ENTRY NiTerrainSectorSelector : public NiRefObject
{
    /// @cond EMERGENT_INTERNAL
    NiDeclareRootRTTI(NiTerrainSectorSelector);
    /// @endcond
public:

    /// A structure to store a sector data
    class LoadingInfo : public NiMemObject
    {
    public:
        /// The sector's X coordinate
        NiInt16 m_sIndexX;
        /// The sector's Y coordinate
        NiInt16 m_sIndexY;
        /// The sector's targeted level of detail
        NiInt32 m_iTargetLoD;
    };

    /// Defines a list of Loading info objects
    typedef efd::list<LoadingInfo> LoadingInfoListType;

    /**
        Constructor
    */
    NiTerrainSectorSelector(NiTerrain* pkTerrain);

    /**
        Destructor
    */
    virtual ~NiTerrainSectorSelector();

    /**
        Updates the sector selection according to the given terrain.
    */
    virtual bool UpdateSectorSelection() = 0;

    /**
        Gets the list of sectors to load
    */
    inline const efd::list<LoadingInfo>& GetSelectedSectors() const;

    /**
        Add a sector load level to the selection
    */
    void AddToSelection(NiInt16 sIndexX, NiInt16 sIndexY, NiInt32 iTargetLOD);

    /**
        Removes all items from the selection list
    */
    void ClearSelection();

    /**
        After the selection has been cleared, call this function to re-add the task to the 
        selection. This function assumes that the given info is not already in the list.
    */
    void Resubmit(const LoadingInfo& kInfo);

protected:

    /**
        Ensures a particular sector exists on disk, was not created before or that level of detail
        was not loaded before
    */
    virtual bool CheckSectorValidForSelection(const LoadingInfo& kSectorInfo);

    /**
        Check a sector exists on disk and caches it for quicker access.

        @return true if the sector was found on disk and false otherwise.
    */
    bool CheckSectorIsOnDisk(NiInt16 sSectorX, NiInt16 sSectorY);

    /// The terrain that this selector will be dealing with
    NiTerrain* m_pkTerrain;

    /// The list of selected sectors
    LoadingInfoListType m_kSelectedSector;

    /// Cache of sector on disk tests. 
    efd::map<NiUInt32, NiUInt32> m_kSectorCatalogue;

    /// A map containing all sectors that we have asked to be loaded, and the LOD which we requested
    efd::map<NiTerrainSector::SectorID, NiInt32> m_kSectorDetailLevels;

    /// A flag to signal whether to use the sector catalogue cache or not
    bool m_bUseSectorCatalogue;

};
NiSmartPointer(NiTerrainSectorSelector);

#include "NiTerrainSectorSelector.inl"


#endif