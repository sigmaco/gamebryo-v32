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
#ifndef PHYSXTERRAINDATAPOLICY_H
#define PHYSXTERRAINDATAPOLICY_H

#include <NiTerrainPhysXUtils.h>
#include <NiTerrainPhysXDataPolicy.h>

// Forward declarations
namespace ecrPhysX
{
    class PropService;
}

class NiTerrain;

namespace egmPhysXTerrain
{

    /**
        Class defining how to load and save custom physx data as part of the terrain dof file
    */
    class EE_EGMPHYSXTERRAIN_ENTRY PhysXTerrainDataPolicy : public NiTerrainPhysXDataPolicy
    {

    public:

        /**
            Initialization constructor.
            @param pPropService reference to the prop service.
            @param pUtils the NiTerrainPhysXUtils that will create the physx data for the terrain
            @param sceneName the name of the scene the terrain is associated to.
        */
        PhysXTerrainDataPolicy(ecrPhysX::PropService* pPropService, 
            NiTerrainPhysXUtils* pUtils, efd::utf8string sceneName);
        
        /**
            Destrcutor.
        */
        ~PhysXTerrainDataPolicy();

        /// @name NiTerrainPhysXDataPolicy overrides.
        /// @see NiTerrainPhysXDataPolicy
        //@{
        virtual bool CreatePhysXData(NiTerrainSector* pkSector);                
        virtual bool DeletePhysXData();                
        virtual void ClearSceneActors();
        virtual void ProcessPendingData();
        //@}

    private:

        /// name of the scene associated to the physX terrain we are loading
        efd::utf8string m_associatedSceneName;

        /// Holds the prop service
        ecrPhysX::PropService* m_pPropService;
    };

    typedef efd::SmartPointer<PhysXTerrainDataPolicy> PhysXTerrainDataPolicyPtr;
}

#endif