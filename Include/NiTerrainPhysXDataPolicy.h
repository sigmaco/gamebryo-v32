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

#ifndef EE_NITERRAINPHYSXDATAPOLICY_H
#define EE_NITERRAINPHYSXDATAPOLICY_H

#include <NiTerrain.h>

/**
    Class defining how to load and save custom physx data as part of the terrain dof file
*/
class NITERRAINPHYSX_ENTRY NiTerrainPhysXDataPolicy : public NiTerrain::CustomDataPolicy
{
public:

    /**
        Constructor
    */
    NiTerrainPhysXDataPolicy(NiTerrainPhysXUtils* pkUtils);

    /**
        Destructor
    */
    ~NiTerrainPhysXDataPolicy();

    virtual efd::UInt32 GetLoadPrecacheFields();

    virtual bool BeginLoadCustomData(NiTerrainSector* pkSector, efd::SInt32 iTargetLOD, 
        NiTerrainSectorFile* pkFile);

    virtual bool LoadCustomData(NiTerrainSector* pkSector, efd::SInt32 iTargetLOD, 
        NiTerrainSectorFile* pkFile);

    virtual bool EndLoadCustomData(NiTerrainSector* pkSector, efd::SInt32 iTargetLOD, 
        NiTerrainSectorFile* pkFile);
    
    virtual bool BeginUnloadCustomData(NiTerrainSector* pkSector, efd::SInt32 iTargetLOD);

    virtual bool UnloadCustomData(NiTerrainSector* pkSector, efd::SInt32 iTargetLOD);

    virtual bool EndUnloadCustomData(NiTerrainSector* pkSector, efd::SInt32 iTargetLOD);
    

    /**
        Sets the PhysX scene to be used for the creation of the NxActors
    */
    void SetPhysXScene(NiPhysXScene* pScene);
    
    /**
        Returns true if we are no longer streaming and some data still requires processing
    */
    bool IsDataPending();

    /**
        Returns true if we are ready to be deleted
    */
    bool IsReadyForDeletion();

    /** 
        Remove all actors from the scene
    */
    virtual void ClearSceneActors();

    /**
        Attemps to load actors and materials for pending data in a thread safe location.
    */
    virtual void ProcessPendingData();

    /**
        Calls upon the NiTerrainPhysXUtils to return a list of all created actors
    */
    virtual efd::list<NxActor*> GetPhysXTerrainActors();

protected:

    /**
        Creates the physx actors and materials for the given sector.
    */
    virtual bool CreatePhysXData(NiTerrainSector* pkSector);

    /**
        Release actors marked for release
    */
    virtual bool DeletePhysXData();

    /// TerrainPhysXUtils object used for the performing the required actions
    NiTerrainPhysXUtilsPtr m_spPhysXUtils;

    /// name of the scene associated to the physX terrain we are loading
    NiPhysXScenePtr m_spPhysXScene;

    /// whether we are currently streaming in data or not
    efd::UInt32 m_uiIsStreaming;

    /// Whether some actors need to be deleted or not.
    bool m_bActorDeletionPending;

    /// Whether the policy can be desposed of or not
    bool m_bRequiresDeletion;

    /// Mutex to keep the streaming flag thread safe
    efd::CriticalSection m_kStreamingMutex;

    /// List of sectors that require actors and materials to be created
    efd::list<NiTerrainSector*> m_kPendingSectors;
};

#endif