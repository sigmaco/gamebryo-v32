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
#ifndef NITERRAINDECAL_H
#define NITERRAINDECAL_H

#include <NiMesh.h>

#include "NiTerrainLibType.h"
#include "NiTerrainSector.h"
#include "NiTerrainSectorData.h"

/**
    This class represents a decal that will be placed on a terrain sector. The
    decal mesh will form itself around the terrain geometry and be placed
    slightly above the terrain mesh itself for rendering purposes.

    Decals support alpha decay over time, as well as a life span. When a decal
    reaches the end of its life span, the owner of the decal will need to
    remove the decal from the terrain, it is not done by the decal itself.
 */
class NITERRAIN_ENTRY NiTerrainDecal : public NiNode
{
public:

    /**
        List of flags returned when updating a decal
    */
    struct UpdateFlags
    {
        enum Value
        {
            /// Decal updated successfully
            DECAL_UPDATED,
            /// Decal has expired
            DECAL_EXPIRED,
            /// Decal was rebuilt
            DECAL_REBUILT
        };
    };

    /** @name Constructors */
    //@{
    /// Default constructor
    NiTerrainDecal();
    //@}

    /// Destructor
    ~NiTerrainDecal();

    /** @name Decal manipulation functions */
    //@{
    /**
        Initializes the geometry for this decal from the positional data given
        by the sector and initializes time to live variables.

        @param pkTexture Texture to apply to the decal. Stored internally as a
            reference counted pointer
        @param kPosition Terrain space position to center the decal around.
            Only the X and Y components are taken into account.
        @param pkTerrain Terrain that this decal is placed upon.
        @param uiSize Side length and breadth, in terrain space, of the decal
        @param fRatio Scale of the texture on the decal. A larger value will
            result in smaller texture
        @param fTimeOfDeath Accumulated app time at which this decal will need
            destroying
        @param fDecayStartTime Accumulated app time at which this decal will
            begin time based alpha decay
        @param fDepthBiasOffset offset modifier used to avoid z fighting issues
    */
    void Initialize(NiTexture* pkTexture, NiPoint3 kPosition,
        NiTerrain* pkTerrain, NiUInt32 uiSize = 2,
        float fRatio = 1, float fTimeOfDeath = 0, float fDecayStartTime = 0,
        float fDepthBiasOffset = 0.005f);

    /**
        Initialize the region that the decal is interested in.

        @param pkTerrain Terrain the decal is interested in.
        @param kPosition Terrain space position to center the decal around.
        @param uiSize Side length and breadth, in terrain space, of the decal
    */
    void InitializeRegion(NiTerrain* pkTerrain, NiPoint3 kPosition, NiUInt32 uiSize);

    /**
        UpdateDecal is responsible for keeping track of the lifespan of this
        decal and updating its alpha according to distance from camera and
        time until death. This function should be called every frame.

        Return values:
            returns 0 when the decal doesn't require an update
            returns 1 when the decal has reached the end of its lifespan
            returns 2 when the decal has been updated

        @param pkTerrain The terrain to which this decal belongs
        @param fDeltaTime Optional time that has elapsed since the last update,
            required if a timer is in use.
        @return Integer return value listed above
    */
    NiUInt8 UpdateDecal(NiTerrain* pkTerrain, float fDeltaTime = 0.0f);
    
    /**
        Rebuild the mesh based on the location on the terrain
        @param pkTerrain terrain the decal is on
    */
    void BuildMesh(NiTerrain* pkTerrain);

    /**
        Adjust the decal according to the camera viewing it

        @param pkCamera Camera to adjust the decal to
    */
    void AdjustToCamera(const NiCamera* pkCamera);

    /**
        Notify the decal that the terrain has changed in the given region

        @param kTerrainRegion region where the terrain has changed
    */
    void NotifyTerrainChanged(NiRect<efd::SInt32>& kTerrainRegion);

    //@}

    /** @name Member Get & Set */
    //@{

    /**
        Mark this decal is requiring an update in the next update loop
    */
    void RequestUpdate();

    /**
        Set the accumulated app time at which this decal will begin alpha
        decay.
        @param fDecayTime Time at which decay begins.
    */
    void SetDecayStartTime(float fDecayTime);

    /**
        Set the distance at which the decal will become completely transparent

        @param fMaxDistance Maximum distance from the camera that the decal
            will be slightly visible from
    */
    void SetFadingDistance(float fMaxDistance);

    /**
        @return true if this decal requires an update in the next update cycle
    */
    NiBool GetRequiresUpdate();

    /**
        @return a pointer to the internal decal mesh, or NULL if the mesh has
            not yet been initialized.
    */
    NiMeshPtr GetMesh();
    //@}

private:

    /**
        Create the mesh object and the streams
    */
    void CreateMesh();

    /**
        Attach the appropriate properties to the mesh
    */
    void AttachProperties();

    /**
        Calculate the alpha for the decal mesh, according to the distance from
        the mesh to the given camera position and the remaining time to live.

        @param pkCamera The camera to use for distance calculation
    */
    void CalculateAlphaDegeneration(const NiCamera* pkCamera);

    /**
        Updates the decals position according to the camera's position to
        avoid z fighting issues
        @param pkCamera Camera to use for the decal update
    */
    void UpdateZFightingOffset(const NiCamera* pkCamera);

    /// The mesh that represents the decal
    NiMeshPtr m_spMesh;

    /// Texture applied to the decal mesh
    NiTexturePtr m_spTexture;

    NiRect<efd::SInt32> m_kTerrainSpaceRegion;

    /// The center point of the decal
    NiPoint3 m_kPosition;

    /**
        Time, in seconds since the application was started, after which the decal
        should be destroyed
    */
    float m_fTimer;

    /**
        Time, in seconds since the application was started, at which we begin
        the decay process
    */
    float m_fDecayTime;

    /// Alpha factor, according to time
    float m_fTimedAlpha;

    /// Alpha factor, according to distance from camera
    float m_fDistanceAlpha;

    /// Distance from camera where the decal first becomes totally transparent
    float m_fFadingDistance;

    /// The multiplier by which the vector between the decal and the camera
    /// should be multiplied by to avoid z fighting
    float m_fDepthBiasOffset;

    /**
        Length and breadth of the decal (local).
    */
    NiUInt32 m_uiSize;

    /**
        Determines the scale of the texture on the mesh. A larger ratio will
        give the effect of making the decal smaller
    */
    float m_fRatio;

    /// Flag to determine whether or not the decal needs to be updated
    bool m_bRequiresUpdate;

    /// Flag that determines whether the timer for the decal is in use
    bool m_bUseTimer;
};

NiSmartPointer(NiTerrainDecal);

#endif
