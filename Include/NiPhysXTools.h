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

#ifndef NIPHYSXTOOLS_H
#define NIPHYSXTOOLS_H

#include "NiPhysXToolsLibType.h"

#include <NiSystem.h>
#include <NiMain.h>
#include <NiPhysX.h>
#include <NiPhysXFluid.h>
#include <NiPhysXParticle.h>

#include <NxPhysics.h>
#include <NxCooking.h>

/**
    The NiPhysXTools class provides general functionality used by tools working with
    Gamebryo-PhysX content.
*/
class NIPHYSXTOOLS_ENTRY NiPhysXTools : NiMemObject
{
public:
    /// Enumeration of methods for obtaining a velocity.
    enum VelocitySource
    {
        Zero = 0, /// Set the velocity to zero.
        DefaultState = 1 /// Copy the velocity from the default state.
    };

    /**
        Add state to a PhysX prop based on the scene graph state.

        This function iterates through every actor descriptor in
        the prop, and adds the scene graph state as a new state in the
        appropriate actor if that actor has a source or destination.
        The prop's set of states is updated to reflect the new state.

        PhysX materials for the new state are copied from the default state.
        Actors that do not have a Gamebryo node associated with them also
        have the new state copied from the default.

        @param pkProp The NiPhysX prop containig the sources, destinations,
            actors and materials.
        @param kStateName The name to record for this state. If a state of
            this name already exists in the prop, then it is replaced with the
            new state.
        @param eVelocitySource The method to use for obtaining velocity for
            the state.
    */
    static void AddStateFromSceneGraph(
        NiPhysXProp* pkProp,
        NiFixedString& kStateName,
        VelocitySource eVelocitySource = Zero);

    /// Get the area of a cloth mesh in its un-deformed state.
    ///
    /// The area is in PhysX units.
    static float ComputeClothArea(NxClothMesh* pkMesh);
    
    /**
        @name Mesh Fingerprinting
        
        A fingerprint is a probably-unique value that can be compared to other fingerprints
        for a probably-correct answer as to whether the meshes are identical. This may be used
        in tools to identify meshes that can be shared. If it is important that the equality of
        meshes be certain, then use the comparison methods included with this class.
        
        Typical usage computes the fingerprints for all meshes and stores the meshes in a hash
        table sized 2^n for some n, keyed with the lower n bits of the fingerprint. The hash
        table equality testing function is the exact mesh equality function. It is sensible to
        store the complete fingerprint along with the mesh and compare that first (two keys will
        map to the same table slot if the lower n bits match, which is not as discriminating as
        the entire fingerprint matching).
        
        The fingerprinting functions all take mesh descriptor classes. Use the saveToDesc method
        for PhysX meshes (e.g. NxClothMesh::saveToDesc) to obtain a descriptor in cases where
        you have a pointer to a mesh.
    */

    //@{
    
    /// Get a 32-bit fingerprint for a PhysX cloth mesh.
    static efd::UInt32 FingerprintClothMesh(NxClothMeshDesc& clothMeshDesc);

    /// Get a 32-bit fingerprint for a PhysX triangle mesh.
    static efd::UInt32 FingerprintTriangleMesh(NxTriangleMeshDesc& triangleMeshDesc);
    
    /// Get a 32-bit fingerprint for a PhysX convex mesh.
    static efd::UInt32 FingerprintConvexMesh(NxConvexMeshDesc& convexMeshDesc);

    //@}

protected:
    /// Extracts state for a single actor.
    static void AddStateFromTransformDest(NiPhysXActorDesc* pkActorDesc,
        NiPhysXTransformDest* pkDest, float fScale, NiUInt32 uiStateIndex);
    static void AddStateFromDynamicSrc(NiPhysXActorDesc* pkActorDesc,
        NiPhysXDynamicSrc* pkSrc, float fScale, NiUInt32 uiStateIndex);
    static void AddStateFromCloth(NiPhysXClothDesc* pkClothDesc,
        float fScale, NiUInt32 uiStateIndex);

    static void NiPhysXTools::FingerprintMix(
        efd::UInt32* data,
        efd::UInt32 dataSize,
        efd::UInt32& a,
        efd::UInt32& b,
        efd::UInt32& c);
    static void FingerprintFinal(efd::UInt32& a, efd::UInt32& b, efd::UInt32& c);
};

#endif  // #ifndef NIPHYSXTOOLS_H

