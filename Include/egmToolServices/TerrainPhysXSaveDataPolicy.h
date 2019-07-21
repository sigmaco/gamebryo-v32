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
#ifndef EE_TERRAINPHYSXSAVEDATAPOLICY_H
#define EE_TERRAINPHYSXSAVEDATAPOLICY_H

class NiTerrain;

namespace egmToolServices
{
    /**
        Terrain data policy used to save the physx data when necessary. This can only save physx 
        data and can not load it. Saving is independant from the PhysX SDK
    */
    class EE_EGMTOOLSERVICES_ENTRY TerrainPhysXSaveDataPolicy : public NiTerrain::CustomDataPolicy
    {
    public:

        virtual bool SaveCustomData(NiTerrainSector* pkSector, NiTerrainSectorFile* pkFile);

        /**
            Entry point for the saving of the sector's physX data

            @param pkSector The sector we want to save physX data for
            @param pkFile The file we are saving to
        */
        static bool SavePhysXData(NiTerrainSector* pkSector, NiTerrainSectorFile* pkFile);

        /**
            Builds the material map using all the surfaces used on the terrain
        */
        static bool BuildMaterialMap(NiTerrain* pkTerrain, 
            efd::map<efd::UInt32, NiPhysXMaterialMetaData>& kMaterialIndex);
            
        /**
            Builds the physx data for a given sector. This function does not use any physX related 
            classes. Returns a data structure that can be used by the terrain file for writing.
        */
        static NiTerrainSectorPhysXData* BuildPhysXData(const NiTerrainSector* pkSector);

        /**
            Builds the physx data for a given leaf. This is where the data is created. Parses through
            the leaf's index stream to resolve tesselation and surface index. This function does not 
            rely on any PhysX functionality.
        */
        static bool BuildLeafData(NiTerrainSectorPhysXData*& pkPhysXData, NiTerrainCellLeaf* pkLeaf);

        /**
            Calculates which is the dominant surface at a given point on a block
            and returns the index associated with that surface.
        */
        static void GetDominantSurface(NiTerrainCellLeaf* pkLeaf, NiInt32 iX, NiInt32 iY, bool bTessFlag, 
            NiUInt16& usMatIndex0, NiUInt16& usMatIndex1);
    };

    /// Defines a smart pointer (reference counted) for the TerrainPhysXSaveDataPolicy class
    typedef efd::SmartPointer<TerrainPhysXSaveDataPolicy> TerrainPhysXSaveDataPolicyPtr;
}

#endif