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

#ifndef EE_NITERRAINPHYSXUTILS_H
#define EE_NITERRAINPHYSXUTILS_H

#include <NiTerrain.h>
#include <NiPhysXScene.h>
#include "NiTerrainPhysXLibType.h"

/**
    PhysX Utility class that manages the creation, loading and saving of
    terrain PhysX data.
 */
class NITERRAINPHYSX_ENTRY NiTerrainPhysXUtils : public NiRefObject
{
public:

    /// @name Constructor / Destructor
    //@{

    /**
        Default constructor.
    */
    NiTerrainPhysXUtils();

    /**
        Constructor using a given start index for the creation of NxMaterial.
    */
    NiTerrainPhysXUtils(efd::UInt16 usStartMatIndex);

    /**
        Constructor using a given start index for the creation of NxMaterial and a custom
        NxActorDesc.
    */
    NiTerrainPhysXUtils(efd::UInt16 usStartMatIndex, NxActorDesc kBaseDesc);

    /**
        Destructor
    */
    ~NiTerrainPhysXUtils();
    //@}

    /// @cond EMERGENT_INTERNAL
    static void SDM_Init();
    static void SDM_Shutdown();
    /// @endcond

    /**
        Sets the actor description. 
    */
    void SetActorDesc(NxActorDesc kActorDesc);

    /**
        Sets the physX scene the terrain depends on. 
        WARNING: If a scene already exists, the terrain will need to be reloaded
    */
    void SetPhysXScene(NiPhysXScene* pkScene);

    /**
        PhysX loading function.
    */
    bool LoadPhysXData(NiTerrainSector* pkSector, NiTerrainSectorFile* pkFile);

    /**
        Function that creates the required NxActors. This should be called in a thread safe position
    */
    bool CreatePhysXActors(NiPhysXScene* pkScene, NiTerrainSector* pkSector);

    /**
        Function that creates the required NxMaterials. This should be called in a thread safe 
        position.
    */
    bool CreatePhysXMaterials(NiPhysXScene* pkScene);

    /**
        PhysX unloading function.
    */
    bool UnloadPhysXData(NiTerrainSector* pkSector);

    /**
        Removes all created NxActors from the scene and the list of actors.
        The used NxMaterial are also reset to the default material so that they can be reused.
        This function should only be called when an entire terrain is being removed.
    */
    void RemoveAllActors(NiPhysXScene* m_pkScene);

    /**
        Deletes all actors waiting for release from the scene. This does not release materials
        as the terrain might still have loaded sectors that used those materials.
    */
    bool DeletePhysXData(NiPhysXScene* pkScene);

    /**
        PhysX saving function. 
    */
    static bool SavePhysXData(NiTerrainSector* pkSector, NiTerrainSectorFile* pkFile);

    /// @name Public Static Attributes
    //@{
    /// Static variables holding the names of the meta data to be used for
    /// creation of NxMaterial
    
    /// Name of the Static friction meta-data (NX_STATICFRICTION)
    static NiFixedString ms_kStaticFriction;
    /// Name of the dynamic friction meta-data (NX_DYNAMICFRICTION)
    static NiFixedString ms_kDynamicFriction;
    /// Name of the restitution meta-data (NX_RESTITUTION)
    static NiFixedString ms_kRestitution;
    //@}

    /**
        Returns true if data is present in the temporary maps
    */
    bool IsPhysXDataCreationPending();

    /**
        Returns true if physx actors for this object are still held by the scene.
    */
    bool HasPhysXActors();

    /**
        Returns a list of NxActor created for all the sectors available with this terrain.
    */
    efd::list<NxActor*> GetPhysXTerrainActors();

private:

    /**
        Class holding the data required for the creation of actors
    */
    class TerrainHeightFieldDesc : public NiMemObject
    {
    public:
        ~TerrainHeightFieldDesc();

        NxHeightFieldDesc m_kHeightFieldDesc;
        NxHeightFieldShapeDesc* m_pkHeightFieldShapeDesc;
        NxActorDesc m_kActorDesc;
    };

    /**
        Class holding the data required for the creation of NxMaterial
    */
    class MaterialDesc : public NiMemObject
    {
    public:
        NxMaterialDesc m_kMaterialDesc;
        NiUInt32 m_uiSurfaceIndex;
    };

    /**
        Loads the material data for a terrain and creates the required NxMaterials.
    */
    bool LoadMaterialMap(const efd::map<efd::UInt32, NiPhysXMaterialMetaData>& kMaterialIndex);

    /**
        Parse through all leaves to load physx data for each leaf.
    */
    bool LoadSectorData(
        NiTerrainSector* pkSector, 
        const NiTerrainSectorPhysXData* pkPhysXData, 
        const efd::UInt16* pusHeightData);

    /**
        Creates the required physx descriptors for the given leaf using the given data
    */
    bool LoadLeafData(
        const NiTerrainSectorPhysXData* pkPhysXData, 
        const efd::UInt16* pusHeightData, 
        NiTerrainCellLeaf* pkLeaf);

    /**
        Builds the material map using all the surfaces used on the terrain
    */
    static bool BuildMaterialMap(
        NiTerrain* pkTerrain, 
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
        and returns the index associated with that surface. S
    */
    static void GetDominantSurface(
        NiTerrainCellLeaf* pkLeaf, 
        NiInt32 iX, 
        NiInt32 iY, 
        bool bTessFlag, 
        NiUInt16& usMatIndex0, 
        NiUInt16& usMatIndex1);

    /// Index at which materials should start in the PhysXScene.
    efd::UInt16 m_usStartMaterialIndex;
    
    /// Map associating a Surface index to a NxMaterial index previously added to the NxScene
    efd::map<efd::UInt32, efd::UInt16> m_kMaterialIndexMap;

    /// Map of NxActors created when loading the PhysX data if a physx scene is present or
    /// when the physx scene is assigned or changed. This associates the actors with a sector index
    typedef efd::map< NiTerrainSector*, efd::list<NxActor*> > SectorToNxActorListMap;
    SectorToNxActorListMap m_kLeafActorMap;

    /// Array of heightfield descriptors read in when loading. This will be used when creating the 
    /// actors and then emptied.
    typedef efd::map< NiTerrainSector*, efd::list<TerrainHeightFieldDesc*> > SectorToHeighFieldMap;
    SectorToHeighFieldMap m_kLeafDescMap;

    /// Array of material descriptors read in when loading. This will be used when creating the 
    /// NxMaterials then emptied.
    efd::list<MaterialDesc> m_kMaterialDescArray;

    /// Actor description
    NxActorDesc m_kLeafActorDesc;

    /// List of actors that need to be removed
    efd::list<NxActor*> m_kActorRemovalList;

    /// Mutex safe guarding access to the leaf desc data map
    efd::CriticalSection m_kLeafDescMutex;

    /// Mutex safe guarding access to the material desc data map
    efd::CriticalSection m_kMatDescMutex; 

    /// Mutex safe guarding access to the leaf actors data map
    efd::CriticalSection m_kLeafActorMutex;
};

NiSmartPointer(NiTerrainPhysXUtils);

#endif
