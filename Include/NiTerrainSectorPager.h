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

#ifndef NITERRAINSECTORPAGER_H
#define NITERRAINSECTORPAGER_H

/**
    This class defines a prototype SectorSelector class that issues paging commands to the terrain
    according to the location of the camera and some basic settings. This class is intended as 
    an example for testing and inspiration. It is not recommended for production code.
*/
class NiTerrainSectorPager : public NiTerrainSectorSelector
{
    /// @cond EMERGENT_INTERNAL
    NiDeclareRTTI;
    /// @endcond
public:

    /**
        Constructor
    */
    NiTerrainSectorPager(NiTerrain* pkTerrain);

    /**
        Destructor
    */
    ~NiTerrainSectorPager();

    /**
        Constructs a terrain paging manager object that has been initialized
        with default values for the specified terrain and the given reference 
        object.
    */
    NiTerrainSectorPager(NiTerrain* pkTerrain, NiAVObject* pkRefObject);

    virtual bool UpdateSectorSelection();

    /**
        Sets the reference point around which to load a terrain
    */
    inline void AddReferenceObject(NiAVObject* pkRefObject);

    /**
        Gets the reference point around which to load a terrain
    */
    inline const NiAVObject* GetCurrentReferenceObject() const;

    /**
        Sets the range around the reference objects to load sectors.
    */
    inline void SetLoadDistance(float fLoadDistance);

    /**
        Gets the range around the reference objects to load sectors.
    */
    inline float GetLoadDistance() const;

    /**
        Sets the amount of movement between loading a sector and 
        unloading it again.
    */
    inline void SetUnloadDistanceTolerance(float fUnloadDistance);

    /**
        Gets the amount of movement between loading a sector and 
        unloading it again.
    */
    inline float GetUnloadDistanceTolerance() const;

    /**
        Sets the distance at which the highest level of detail 
        should be loaded.
    */
    inline void SetMaxLODLoadDistance(float fLoadDistance);

    /**
        Sets the distance at which the highest level of detail 
        should be loaded.
    */
    inline float GetMaxLODLoadDistance() const;

private:

    void FindNextSectorsToLoad();
    void FindNextSectorsToUnload();

    /// Calculate the minimum LOD that a sector should be loaded to
    NiInt32 CalculateMinSectorLOD(float fDistanceToSector);

    /// Calculate the maximum LOD that a sector should be loaded to
    NiInt32 CalculateMaxSectorLOD(float fDistanceToSector);
    
    /// Calculate the shortest distance to a sector from a reference point
    float CalculateMinDistanceToSector(NiInt16 sIndexX, NiInt16 sIndexY, NiPoint2 kRefPoint);

    /// Distance from the center of a reference point at which loading should
    /// be done.
    float m_fLoadDistance;
    
    /// Distance from the center of a reference point at which the sectors 
    /// be loaded to their maximum level of detail.
    float m_fMaxLODLoadDistance;

    /// A tolerance value that defines a range over which the reference node
    /// can move before a loaded sector is unloaded again.
    float m_fUnloadDistanceTolerance;

    /// Reference objects
    NiTObjectArray<NiAVObjectPtr> m_kReferenceObjects;

    /// The current reference object being used
    NiUInt32 m_uiCurrentRefObject;

};

#include "NiTerrainSectorPager.inl"


#endif