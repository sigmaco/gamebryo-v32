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

#ifndef NIPHYSXSNAPSHOTEXTRACTOR_H
#define NIPHYSXSNAPSHOTEXTRACTOR_H

#include "NiPhysXToolsLibType.h"

#include <NiSystem.h>
#include <NiMain.h>
#include <NiPhysX.h>
#include <NiPhysXFluid.h>
#include <NiPhysXParticle.h>

#include <NxPhysics.h>
#include <NxCooking.h>

/**
    NiPhysXSnapshotExtractor objects are used to convert PhysX NxScene objects into
    Gamebryo PhysX scene descriptor objects. To access the functionality, create an
    NiPhysXSnapshotExtractor object and call its member functions.
*/
class NIPHYSXTOOLS_ENTRY NiPhysXSnapshotExtractor : public NiMemObject
{
public:
    /// The default constructor allows you to, optionally, set the target platform
    /// for the snapshot.
    NiPhysXSnapshotExtractor(const NxPlatform kPlatform = PLATFORM_PC);

    /**
        Get the target platform.
    */
    NxPlatform GetTargetPlatform() const;

    /**
        Set the target platform.

        This determines the format for cooked cloth, convex and triangle meshes.
    */
    void SetTargetPlatform(const NxPlatform kPlatform);

    /**
        Construct an NiPhysXScene object with props and a full set of descriptors
        necessary to recreate a PhysX scene.
        
        The pose matrix, kXform, is used to convert all the poses and velocities of PhysX
        actors as they are saved to the descriptors. Use it if you would like the saved
        representation to be in a different coordinate system to the original scene.

        This returned scene does not include information about how the PhysX content is
        attached to Gamebryo objects; NiPhysX sources and destinations must be set up
        separately. However, if bSetPhysXPtrs is true, the Gamebryo descriptors will
        include pointers to the PhysX objects from which they were constructed. Otherwise,
        those pointers are NULL.

        The global pose of cloth objects is always saved as the identity matrix, with the
        pose matrix used to transform the cloth mesh vertices.

        The number of simulation compartments is inferred from the PhysX scene, and
        multiple props are created to separate content into the correct compartments.
        It will be necessary for the application to create appropriate compartments
        when using the snapshot that results.
    */
    NiPhysXScene* ExtractSnapshot(NxScene* pkScene, const NxMat34& kXform, bool bSetPhysXPtrs);

protected:
    void CreateProps(NxScene* pkScene, NiPhysXScene* pkResult,
        NiTMap<NxCompartment*, unsigned int>& kCompartmentIDMap,
        NiTMap<unsigned int, NiPhysXProp*>& kCompartmentPropMap);
    NiPhysXActorDesc* CaptureActor(NxActor* pkActor, const NxMat34& kXform,
        bool bSetPhysXPtrs, NxCookingInterface* pkCookInterface,
        NiTMap<NxShape*, NiPhysXShapeDescPtr>& kShapeMap);
    NiPhysXClothDesc* CaptureCloth(NxCloth* pkCloth, const NxMat34& kXform,
        bool bSetPhysXPtrs, NxCookingInterface* pkCookInterface);
    NiPhysXShapeDesc* CaptureConvex(const NxConvexShapeDesc& kConvexDesc,
        NxCookingInterface* pkCookInterface);
    NiPhysXShapeDesc* CaptureTriMesh(
        const NxTriangleMeshShapeDesc& kTriMeshDesc,
        NxCookingInterface* pkCookInterface);
    NiPhysXMeshDesc* CaptureClothMesh(const NxClothMesh* pkClothMesh,
        NiFixedString& kName, NxCookingInterface* pkCookInterface,
        const NxMat34& kXform);

    // Prime numbers
    static const int NUM_PRIMES;
    static const unsigned int PRIMES[10];
    static unsigned int NextPrime(const unsigned int target);

    NxPlatform kTargetPlatform;
};

#endif  // #ifndef NIPHYSXSNAPSHOTEXTRACTOR_H

