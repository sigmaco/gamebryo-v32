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

#ifndef NITERRAINSECTORSELECTORDEFAULT
#define NITERRAINSECTORSELECTORDEFAULT

#include "NiTerrainSectorSelector.h"

/**
    This class is meant to select a list of sectors that should be added to the terrain. 
    This default selector will find all sectors on disk in the defined range and load them. 
    It should only be used if we want to load all sectors at once.
*/
class NITERRAIN_ENTRY NiTerrainSectorSelectorDefault : public NiTerrainSectorSelector
{
    /// @cond EMERGENT_INTERNAL
    NiDeclareRTTI;
    /// @endcond

public:
    /// @name Construtor / Destructor
    ///@{
    /**
        Constructor that initializes the selector using a terrain.
    */
    NiTerrainSectorSelectorDefault(NiTerrain* pkTerrain);

    /**
        Constructor that initializes the selector using a terrain as well as the region
        of space where sectors will be found.

        @param pkTerrain pointer to the terrain to select sectors for
        @param kFirstSectorIndex The index of the first sector (minimum x and minimum y)
        @param kTerrainExtent the number of sectors the terrain spans (maximum x and maximum y)
    */
    NiTerrainSectorSelectorDefault(NiTerrain* pkTerrain, NiIndex kFirstSectorIndex, 
        NiIndex kTerrainExtent);

    /**
        Destructor
    */
    ~NiTerrainSectorSelectorDefault();
    ///@}

    /**
        Updates the sector selection according to the given terrain.
    */
    virtual bool UpdateSectorSelection();

    /**
        Sets the index of the first sector we can load
    */
    inline void SetFirstSectorIndex(NiIndex kFirstSector);
    
    /**
        Sets the index of the first sector we can load
    */
    inline void SetFirstSectorIndex(NiUInt32 uiSectorX, NiUInt32 uiSectorY);
    
    /**
        Gets the index of the first sector we can load
    */
    inline NiIndex GetFirstSectorIndex();

    /**
        Sets the number of sectors the terrain holds along X and Y
    */
    inline void SetTerrainExtent(NiIndex kTerrainExtent);

    /**
        Sets the number of sectors the terrain holds along X and Y
    */
    inline void SetTerrainExtent(NiUInt32 uiNumSectorX, NiUInt32 uiNumSectorY);

    /**
        Gets the number of sectors the terrain holds along X and Y
    */
    inline NiIndex GetTerrainExtent();

    /**
        Sets the maximum LoD we can load. Setting does not perform any error checking. This 
        will be done by the terrain at loading time
    */
    inline void SetMaxLOD(NiUInt32 uiMaxLOD);

    /**
        Gets the maximum LoD we can load. Setting does not perform any error checking. This 
        will be done by the terrain at loading time
    */
    inline NiUInt32 GetMaxLOD();

protected:
    
    /**
        Builds the list of sectors according to the set range. 

        @return true if we added an object to the list
    */
    bool BuildSectorList();

    /// The index of the first sector
    NiIndex m_kFirstSectorIndex;

    /// The extent of the terrain we want to load
    NiIndex m_kTerrainExtent;
};

#include "NiTerrainSectorSelectorDefault.inl"

#endif