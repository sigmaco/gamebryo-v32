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
#ifndef NIPSMESHPARTICLESYSTEM_H
#define NIPSMESHPARTICLESYSTEM_H

#include "NiPSParticleSystem.h"
#include <NiNode.h>

/**
    Represents a particle system that uses mesh particles instead of
    sprite-based particles.

    The main purpose of this sub-class of NiPSParticleSystem is to override
    the rendering and updating functions to deal with mesh particles. It holds
    a set of master particles, one for each particle generation. A master
    particle must be set for every generation prior to filling the particle
    pools, streaming, or cloning.

    Each master particle is just a scene graph that in most cases is a single
    NiMesh object but that could be any arbitrary graph of nodes and mesh
    objects. Master particles are owned by the NiPSMeshParticleSystem object,
    and unexpected behavior may occur if a master particle also exists in the
    scene graph and is modified there. In general, master particles should be
    cloned when being added if they also exist in the scene graph so that the
    particle system has its own copy of each master particle.

    When particles are emitted, the master particle of the matching particle
    generation is cloned, and the instanced particle is placed underneath a
    container node. Every frame, each particle is updated with its age,
    allowing time controllers attached in that particle's scene graph to
    properly animate. The container node is then culled and rendered like any
    other scene graph.

    To mitigate the memory thrashing that may occur when particles are
    allocated, cloned, and deleted, NiPSMeshParticleSystem holds pools of
    deleted mesh particles to be recycled. When a particle is removed from the
    particle system, it is added into its respective pool. When the system
    attempts to create a particle, it will first try to get one from the pools.
    The size of the pools is configurable by the user and is by default set to
    the maximum number of particles. When a mesh particle system is started
    for the first time, there may be a performance hit as lots of particles
    are cloned. To mitigate this problem you can preload the pools in code, or
    you can specify that the pools be initially filled during PostLinkObject
    when loading from a NIF (AutoFillPools).
*/
class NIPARTICLE_ENTRY NiPSMeshParticleSystem : public NiPSParticleSystem
{
    /// @cond EMERGENT_INTERNAL

    NiDeclareRTTI;
    NiDeclareClone(NiPSMeshParticleSystem);
    NiDeclareStream;
    NiDeclareViewerStrings;

    /// @endcond

public:
    enum
    {
        /// Used to indicate that the maximum number of particles should be
        /// used for the pool size.
        DEFAULT_POOL_SIZE = -1
    };

    /// @name Construction and Destruction
    //@{
    /**
        Creates an NiPSMeshParticleSystem object with the specified parameters.

        This function takes care of creating an NiPSMeshParticleSystem
        object and attaching an NiPSSimulator to it.

        @param uiMaxNumParticles The maximum number of particles allowed by
            this system. This determines the allocated size of all data arrays
            and cannot be changed.
        @param eNormalMethod The method to use for the normal direction when orienting particles.
        @param kNormalDirection The fixed direction vector to use for the normal direction when
            orienting particles with a fixed direction method.
        @param eUpMethod The method to use for the "up" direction when orienting particles.
        @param kUpDirection The fixed direction vector to use for the "up" direction when
            orienting particles with a fixed direction method.
        @param bHasLivingSpawner Whether or not living spawner data will be allocated.
        @param bHasColors Whether or not color data will be allocated.
        @param bHasRotations Whether or not rotation angle, speed, and axis
            data will be allocated.
        @param bWorldSpace Whether or not the particle system will compute its
            particles in world-space or local-space.
        @param bDynamicBounds Whether or not an NiPSBoundUpdater object will be
            attached to the particle system.
        @param bAttachMeshModifiers Whether or not the simulator mesh modifier
            will be attached when it is added.
        @param usNumGenerations The number of generations supported by the
            particle system. This determines how many master particles must be
            stored in the system.
        @param uiPoolSize The size to use for the pools of deleted mesh
            particles.
        @param bAutoFillPools Whether or not the pools of particles are
            automatically populated during streaming and cloning.
        @param fScaleAmount The amount of scaling increases as the speed increases.
            If negative, the particle will shrink as the speed increases.
        @param fScaleRest The scale when the speed is zero. This value must not be the same as
            the limit. If the Scale Amount is positive, this value must be less than the limit.
            If the Scale Amount is negative, it must be greater than the limit.
        @param fScaleLimit The maximum value for scale (or the minimum if the scale amount is
            negative). The scale will approach this value as the speed goes to infinity.

        @return The newly created NiPSMeshParticleSystem object.
    */
    static NiPSMeshParticleSystem* Create(
        const NiUInt32 uiMaxNumParticles,
        const AlignMethod eNormalMethod = ALIGN_LOCAL_FIXED,
        const NiPoint3& kNormalDirection = NiPoint3::UNIT_X,
        const AlignMethod eUpMethod = ALIGN_LOCAL_VELOCITY,
        const NiPoint3& kUpDirection = NiPoint3::ZERO,
        const bool bHasLivingSpawner = false,
        const bool bHasColors = false,
        const bool bHasRotations = false,
        const bool bWorldSpace = true,
        const bool bDynamicBounds = true,
        const bool bAttachMeshModifiers = true,
        const NiUInt16 usNumGenerations = 1,
        const NiUInt32 uiPoolSize = DEFAULT_POOL_SIZE,
        const bool bAutoFillPools = false,
        const float fScaleAmount = 0.0f,
        const float fScaleRest = 1.0f,
        const float fScaleLimit = 1e4f);

    /// Virtual destructor.
    virtual ~NiPSMeshParticleSystem();
    //@}

    /// @name Base Class Overrides
    //@{
    virtual void ResetParticleSystem(const float fNewLastTime = -NI_INFINITY);
    //@}

    /// @name Particle Data Accessors
    //@{
    /// Returns the array of particle rotations.
    ///
    /// The columns of the matrices are stored and returned.
    NiPoint3* GetRotations();

    /// Returns the array of particle rotations.
    ///
    /// The columns of the matrices are stored and returned.
    const NiPoint3* GetRotations() const;

    /// Returns the array of particle velocities.
    float* GetScales();

    /// Returns the array of particle velocities.
    const float* GetScales() const;
    //@}

    /**
       Returns the number of particle generations supported by this particle
       system.

       This determines the number of generations for which there is a distinct mesh.
    */
    virtual NiUInt16 GetNumGenerations() const;

    /**
        Sets the master particle for the specified generation.

        These master particles are used to fill the particle pools.

        @note A master particle must be set for every generation prior to
            filling the pools, streaming, or cloning.

        @param usGeneration The generation at which to set the master particle.
        @param pkMasterParticle The master particle to set.
        @return The old master particle for the generation, if one had already
            been set.
    */
    inline NiAVObjectPtr SetMasterParticle(
        NiUInt16 usGeneration,
        NiAVObject* pkMasterParticle);

    /**
        Gets the master particle for the specified generation.

        @param usGeneration The generation of the desired master particle.
        @return The master particle at the specified generation or NULL if
            none exists.
    */
    inline NiAVObject* GetMasterParticle(NiUInt16 usGeneration) const;

    /// Gets whether or not the pools of particles are automatically populated
    /// during streaming and cloning.
    inline bool GetAutoFillPools() const;

    /// Sets whether or not the the pools of particles are automatically
    /// populated during streaming and cloning.
    inline void SetAutoFillPools(bool bAutoFillPools);

    /**
        Fills up the internal particle pools using the master particles that
        have been set for this particle system.

        @note A master particle must be set for every generation prior to
            calling this function.
    */
    void FillPools();

    /// @cond EMERGENT_INTERNAL

    /// Gets the container node for all the mesh particles.
    NiNode* GetParticleContainer() const;

    /// @name Base Class Overrides
    //@{
    virtual void InitializeParticle(NiUInt32 uiNewParticle);
    virtual void InitializeSpawnedParticle(NiUInt32 uiNewParticle);
    virtual void UpdatePropertiesDownward(NiPropertyState* pkParentState);
    virtual void UpdateEffectsDownward(NiDynamicEffectState* pkParentState);
    virtual void OnVisible(NiCullingProcess& kCuller);
    virtual void SetSelectiveUpdateFlags(
        bool& bSelectiveUpdate,
        bool bSelectiveUpdateTransforms,
        bool& bRigid);
    virtual void RenderImmediate(NiRenderer* pkRenderer);
    virtual void PurgeRendererData(NiRenderer* pkRenderer);
    virtual void RetrieveMeshSet(NiTPrimitiveSet<NiMesh*>& kMeshSet);
    virtual void ProcessClone(NiCloningProcess& kCloning);
    virtual void PostLinkObject(NiStream& kStream);
    //@}

    /// @endcond

protected:
    /// @name Construction and Destruction
    //@{
    /**
        Protected main constructor.

        @note Instances of this class should be created with the static Create
            function instead of with this constructor.

        @param pkSimulator A pointer to the simulator mesh modifier that will
            be attached to this particle system.
        @param uiMaxNumParticles The maximum number of particles allowed by
            this system. This determines the allocated size of all data arrays.
        @param usNumGenerations The number of generations supported by the
            particle system. This determines how many master particles must be
            stored in the system.
        @param eNormalMethod The method to use for the normal direction when orienting particles.
        @param kNormalDirection The fixed direction vector to use for the normal direction when
            orienting particles with a fixed direction method.
        @param eUpMethod The method to use for the "up" direction when orienting particles.
        @param kUpDirection The fixed direction vector to use for the "up" direction when
            orienting particles with a fixed direction method.
        @param bHasLivingSpawner Whether or not living spawner data will be allocated.
        @param bHasColors Whether or not color data will be allocated.
        @param bHasRotations Whether or not rotation angle and speed data will
            be allocated.
        @param bHasRotationAxes Whether or not rotation axis data will be
            allocated. This value should not be true if bHasRotations is false.
        @param bWorldSpace Whether or not the particle system will compute its
            particles in world-space or local-space.
        @param pkBoundUpdater A pointer to the bound updater to use with this
            particle system. This should be NULL if the particle system is to
            have a static bounding volume.
        @param uiPoolSize The size to use for the pools of deleted mesh
            particles.
        @param bAutoFillPools Whether or not the pools of particles are
            automatically populated during streaming and cloning.
    */
    NiPSMeshParticleSystem(
        NiPSSimulator* pkSimulator,
        const NiUInt32 uiMaxNumParticles,
        const AlignMethod eNormalMethod,
        const NiPoint3& kNormalDirection,
        const AlignMethod eUpMethod,
        const NiPoint3& kUpDirection,
        const bool bHasLivingSpawner,
        const bool bHasColors,
        const bool bHasRotations,
        const bool bHasRotationAxes,
        const bool bWorldSpace,
        NiPSBoundUpdater* pkBoundUpdater,
        const NiUInt16 usNumGenerations,
        const NiUInt32 uiPoolSize,
        const bool bAutoFillPools);

    /// Protected default constructor for cloning and streaming only.
    NiPSMeshParticleSystem();
    //@}

    /// @name Base Class Overrides
    //@{
    virtual void PostUpdate(NiUpdateProcess& kUpdate);
    virtual void RemoveParticle(NiUInt32 uiIndexToRemove);
    virtual void ResolveAddedParticles(const bool bUpdateBound);
    virtual void UpdateWorldData();
    virtual void UpdateWorldBound();
    //@}

    /**
        Helper function used by RetrieveMeshSet that recursively searches for
        NiMesh objects in each master particle's scene graph.

        NiMesh objects that are found by this function are added to the set
        passed in.

        @param pkObject The scene graph root to recursively search.
        @param kMeshSet A set of NiMesh object to which found meshes will be
            added.
    */
    void RecursiveRetrieveMeshSet(
        NiAVObject* pkObject,
        NiTPrimitiveSet<NiMesh*>& kMeshSet);

    /// The container node for all active mesh particles.
    NiNodePtr m_spParticleContainer;

    /// An array of smart pointers to NiAVObject objects.
    typedef NiTObjectArray<NiAVObjectPtr> NiAVObjectArray;

    /**
        An array of pools of available mesh particles.

        When particles are removed, they are added to one of these pools. The
        size of this array equals the number of generations.
    */
    NiTPrimitiveArray<NiAVObjectArray*> m_kPools;

    /// An array of master particles used when creating active mesh particles.
    NiAVObjectArray m_kMasterParticles;

    /// Arrays of per-particle transform data.
    NiPoint3* m_pkRotations;
    float* m_pfScales;

    /// The size of each individual pool in the m_kPools array.
    NiUInt32 m_uiPoolSize;

    /// Whether or not the existing pools should be copied over during a
    /// cloning operation and automatically populated with clones during a
    /// streaming operation.
    bool m_bAutoFillPools;
};

NiSmartPointer(NiPSMeshParticleSystem);

#include "NiPSMeshParticleSystem.inl"

#endif  // #ifndef NIPSMESHPARTICLESYSTEM_H
