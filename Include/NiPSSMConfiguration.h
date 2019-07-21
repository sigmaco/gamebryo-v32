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

#ifndef NIPSSMCONFIGURATION_H
#define NIPSSMCONFIGURATION_H

#include "NiMainLibType.h"
#include "NiFlags.h"
#include "NiRefObject.h"
#include "NiFrustum.h"

#include "NiRenderView.h"
#include "NiCamera.h"

/**
    Each shadow generator needs its own set of configuration for use in PSSM,
    which is stored in this class. Configurations can be bound to a generator
    through the NiPSSMShadowClickGenerator::BindConfiguration function.

    The configuration defines how the PSSM click generator should handle a
    light that is governed by the corresponding shadow generator and acts as a
    repository for shadow split frustum and viewport data.

    @note Different shadow generators cannot share the same instance of a
        PSSM configuration, since calculated data is stored within.
 */
class NIMAIN_ENTRY NiPSSMConfiguration : public NiRefObject
{
    NiDeclareFlags(NiUInt8);

    /// Bitwise flags
    enum FLAGS
    {
        SCENEDEPENDENTFRUSTUMS = 0x01,
        SUBTEXELOFFSET         = 0x02,
        BORDERTESTING          = 0x04,
        SLICETRANSITIONS       = 0x08,

        REBUILDFRUSTUMS        = 0x10,
        CUSTOMCAMERAFRUSTUM    = 0x20,
        ISBOUNDTOGENERATOR     = 0x40,
        CUSTOMFARPLANE         = 0x80
    };

public:

    // Configuration
    enum CONFIGURATION
    {
        MAX_SLICES = 16
    };

    /// Default constructor
    NiPSSMConfiguration();
    /// Copy constructor
    NiPSSMConfiguration(const NiPSSMConfiguration& kCopy);
    /// Virtual  Destructor
    virtual ~NiPSSMConfiguration();


    inline NiAVObjectRawList* GetCasterList();

    /**
        Toggles scene dependent frustums for this configuration. When enabled,
        each shadow camera frustum will attempt to shrink all planes to tightly
        fit casters that are visible within its corresponding PSSM slice. The
        near and far planes will also attempt to tightly fit themselves to the
        bounds of affected receivers.
    */
    //@{
    inline bool GetSceneDependentFrustumsEnabled() const;
    inline void SetSceneDependentFrustumsEnabled(bool bEnabled);
    //@}

    /**
        Toggles between the use of the scene camera's far plane, and a custom
        far plane distance.
    */
    inline bool GetCustomSceneCameraFarPlaneEnabled() const;
    inline void SetCustomSceneCameraFarPlaneEnabled(bool bEnabled);

    /**
        Assign a custom scene camera far plane. A call to
        SetCustomSceneCameraFarPlane will also enable it's use.
    */
    inline void SetCustomSceneCameraFarPlane(float fFarPlane);
    inline float GetCustomSceneCameraFarPlane();

    /**
        @return True if a user specified frustum will be used to create the PSSM
            splits rather than the scene camera.
    */
    inline bool GetCustomSceneCameraFrustumEnabled() const;

    /**
        User frustum that will be used to create PSSM splits rather than
        the scene camera. If no custom frustum has been defined, an
        uninitialized frustum will be returned.
    */
    inline const NiFrustum& GetCustomSceneCameraFrustum() const;

    /**
        Define and enable a custom frustum that will be used in place of the
            scene camera for the purposes of creating the PSSM splits. Each
            split will be a portion of the given frustum.

        @note A custom frustum will still have the regular scene camera
            transform applied to it.
    */
    inline void SetCustomSceneCameraFrustumEnabled(const NiFrustum&
        kSceneFrustum);

    /**
        Disable a previously assigned custom scene camera frustum
    */
    inline void SetCustomSceneCameraFrustumDisabled();


    /**
        Specifies the scaling factor used when calculating how far away
        from the scene to place the shadow cameras. A larger scale helps
        to eliminate shadow clipping, but reduces precision in the shadowmap.

        A default camera distance scale factor of 4.0 is used.
    */
    //@{
    inline float GetCameraDistanceScaleFactor() const;
    inline void SetCameraDistanceScaleFactor(float fCameraDistScaleFactor);
    //@}

    /**
        Toggle quantization of shadow camera movements on a shadowmap texel
        basis. This has the effect of removing shimmering of shadow maps when
        the scene camera is moved or rotated.
    */
    //@{
    inline bool GetSubTexelOffsetEnabled() const;
    inline void SetSubTexelOffsetEnabled(bool bEnabled);
    //@}

    /**
        Toggle border testing between adjacent shadowmap cells. When enabled,
        shadowmap lookups are clipped to the relevant shadowmap viewport in the
        pixel-shader.
    */
    //@{
    inline bool GetBorderTestingEnabled() const;
    inline void SetBorderTestingEnabled(bool bEnabled);
    //@}

    /**
        Apply an additional spacing (in texels) between PSSM splits on the
        shadowmap texture.

        @note The PCF Shadow Technique will automatically have 2 texels added
            to it by the generator; any extra split spacing will be added in
            addtition to these 2 texels.
    */
    //@{
    inline NiUInt32 GetExtraSplitSpacing() const;
    inline void SetExtraSplitSpacing(NiUInt32 uiExtraSplitSpacing);
    //@}

    /**
        Toggle screen door noise based transitions between PSSM slices.
    */
    //@{
    inline bool GetSliceTransitionEnabled() const;
    void SetSliceTransitionEnabled(bool bEnabled);
    //@}

    /**
        Define the length from start to finish, in world coordinate space, of a
        transition between two PSSM levels.
    */
    //@{
    inline float GetSliceTransitionSize() const;
    inline void SetSliceTransitionSize(float fSize);
    //@}

    /**
        Define the inverse scale of the noise mask used to create the 'screen-
        door' transitions between PSSM split levels. A smaller value will
        produce a coarser effect; larger numbers will produce less discrete
        transitions which are more susceptable to moire artifacts.
    */
    //@{
    inline float GetSliceTransitionNoiseScale() const;
    inline void SetSliceTransitionNoiseScale(float fScale);
    //@}

    /**
        Defines how much larger a given PSSM slice will be in comparison to the
        previous. A larger value will create a bigger difference in size;
        therefore biasing more shadowmap pixels to objects nearer to the visible
        camera.

        Valid values between 0.0 and 1.0
    */
    //@{
    inline float GetSliceLambda() const;
    inline void SetSliceLambda(float fLambda);
    //@}

    /**
        Defines the number of slices the scene camera frustum will be split
        into to generate the shadow camera frustums

        Valid values between 1 and 16 (inclusive)

        @note A value of 1 will disable PSSM entirely; this click generator will
            revert to all NiDefaultShadowClickGenerator functionality
    */
    //@{
    inline NiUInt8 GetNumSlices() const;
    void SetNumSlices(NiUInt8 ucNumSlices);
    //@}

    /**
        Request that the scene camera splits and the shadow camera frustums are
        recalculated the next time the generator corresponding to this
        configuration is handled. Once the frustums are rebuilt, this flag is
        set to false.
    */
    //@{
    inline bool GetRebuildFrustums() const;
    inline void SetRebuildFrustums(bool bRebuild = true);
    //@}

    /// @return True if this configuration is currently bound to a generator.
    inline bool GetIsBoundToGenerator() const;

    /// @cond EMERGENT_INTERNAL

    inline void SetIsBoundToGenerator(bool bBound);
    inline void GetPSSMSliceViewport(NiUInt8 ucSliceIndex,
        NiRect<float>& kViewport);
    inline const NiRect<float>& GetPSSMSliceViewport(NiUInt8 ucSliceIndex)
        const;
    inline NiRect<float>& GetPSSMSliceViewport(NiUInt8 ucSliceIndex);

    inline float GetPSSMSliceMinDistance(NiUInt8 ucSliceIndex) const;
    inline void SetPSSMSliceMinDistance(float fDist, NiUInt8 ucSliceIndex);
    inline float GetPSSMSliceMaxDistance(NiUInt8 ucSliceIndex) const;
    inline void SetPSSMSliceMaxDistance(float fDist, NiUInt8 ucSliceIndex);

    inline const NiCamera* GetSliceTransitionCamera() const;
    inline NiCamera* GetSliceTransitionCamera();

    void UpdateShaderConstantData(
        NiTPointerList<NiRenderViewPtr>& kRenderViews);
    inline float* GetPackedSplitMatrices() const;
    inline float* GetPackedSplitDistances() const;
    inline float* GetPackedSplitViewports() const;
    inline float* GetPackedTransitionMatrix() const;

    /// @endcond

protected:

    // State
    NiCamera m_kSliceTransitionCamera;
    NiFrustum m_kCustumSceneFrustum;
    NiRect<float>* m_pkSliceViewports;
    NiAVObjectRawList* m_pkCasterList;
    float* m_pfSliceDistances;

    // Shader constant data
    float* m_pfPackedMatrices;
    float* m_pfPackedDistances;
    float* m_pfPackedViewports;
    float* m_pfPackedTransitionMatrix;

    // Configuration
    float m_fSliceLambda;
    float m_fSliceTransitionSize;
    float m_fSliceTransitionScale;
    float m_fCameraDistScaleFactor;

    NiUInt32 m_uiExtraSplitSpacing;
    NiUInt8 m_ucNumSlices;
};

NiSmartPointer(NiPSSMConfiguration);

#include "NiPSSMConfiguration.inl"

#endif // NIPSSMCONFIGURATION_H
