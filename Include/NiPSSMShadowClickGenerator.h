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

#ifndef NIPSSMSHADOWCLICKGENERATOR_H
#define NIPSSMSHADOWCLICKGENERATOR_H

#include "NiDefaultShadowClickGenerator.h"
#include "NiMainLibType.h"
#include "NiNoiseTexture.h"
#include "NiPSSMConfiguration.h"
#include "NiTMap.h"

/**
    Click generator that supports Parallel Split Shadow Mapping (PSSM). The
    shadow map is split into several cells using texture atlassing, with each
    cell corresponding to a different orthographic shadow frustum.

    The view camera frustum is split into as many portions as there are shadow
    map cells along the view axis. In other words, the near and far planes of
    the view frustum are manipulated to create several sub-frustums.

    The orthographic shadowmap frustums are sized to fit the corresponding view
    frustum splits, resulting in different shadowmap atlas cells corresponding
    to shadowmaps projected at differing distances from the view camera.

    Various settings and tweakables for PSSM can be found in the
    NiPSSMConfiguration class, which is bound to a shadow generator using the
    NiPSSMShadowClickGenerator::BindConfiguration function.
 */
class NIMAIN_ENTRY NiPSSMShadowClickGenerator :
    public NiDefaultShadowClickGenerator
{
    NiDeclareRTTI;

public:

    /**
        Parameterized constructor. If a shadow generator is used which has had
        not configuration bound to it, a copy of the default configuration will
        be bound to that generator.
    */
    NiPSSMShadowClickGenerator(
        const NiPSSMConfiguration& kDefaultConfiguration);

    /// Virtual destructor
    virtual ~NiPSSMShadowClickGenerator();

    /**
        Return the noise map currently used by the slice transitions.

        @note If slice transitions have not been enabled, this function returns
            NULL
    */
    inline NiTexturingProperty::Map* GetNoiseTextureMap() const;

    /**
        Find the unique PSSM configuration associated with the given generator.

        If no configuration exists and bCreateFromDefault is 'true', a copy of
            the default configuration (given upon the click generators
            initialization) will be used.

        If no configuration exists and bCreateFromDefault is 'false', NULL is
            returned.
    */
    NiPSSMConfiguration* GetConfiguration(const NiShadowGenerator* pkGenerator,
        bool bCreateFromDefault = true);

    /**
        Bind the given PSSM configuration to the given shadow generator.

        When the shadow generator is handled by this click generator, the given
            configuration will be used instead of the default configuration.

        @note Smart pointers are used to reference pkConfig internally
        @note A configuration can only ever be bound to a single generator
    */
    void BindConfiguration(const NiShadowGenerator* pkGenerator,
        NiPSSMConfiguration* pkConfig);

    //@{
    /**
        Currently, PSSM is limited to a single generator at a time. This defines
        which generator (and therefore light) will use PSSM.
    */
    static inline void SetActiveGenerator(NiShadowGenerator* pkGenerator);
    static inline const NiShadowGenerator* GetActiveGenerator();
    //@}

    /**
        Determines whether the given light supports PSSM, when in the context
        of the given generators PSSM configuration.

        Currently only NiDirectionalLight supports PSSM, and the PSSM
        configuration must define at least 2 PSSM slices.
    */
    bool LightSupportsPSSM(const NiShadowGenerator* pkGenerator,
        const NiLight* pkLight);

    /**
        Encode a slice count to the format used by the NiStandardMaterial
        descriptors. This is a lossy compression; it quantizes the slice count
        into the following ranges:
        ([1], [2-4], [5-8], [9-12], [13-16])
        then returns the index of the range the slice count fits into.
    */
    static inline NiUInt32 EncodeDescriptorSliceCount(NiUInt32 uiSliceCount);

    /**
        Decodes a slice count encoded by the EncodeDescriptorSliceCount
        function, returning the maximum number of slices that the given encoded
        slice count could possibly represent.
    */
    static inline NiUInt32 DecodeDescriptorMaxSliceCount(
        NiUInt32 uiEncodedSliceCount);

    /// @cond EMERGENT_INTERNAL

    /// Initializes the strings.
    static void _SDMInit();

    /// Releases the strings
    static void _SDMShutdown();

    /// @endcond

protected:

    // Overloaded methods
    virtual bool HandleDirectionalLight(NiShadowGenerator* pkGenerator,
        NiDirectionalLight* pkDirLight, bool bRegenerateViews,
        bool bUpdateShadowMaps);

    virtual bool PrepareDirectionalLightShadowGenerator(
        NiShadowGenerator* pkGenerator);

    // Shadow Map Callbacks
    static bool PSSMGetShaderConstantCallback(void* pvData,
        unsigned int uiDataSize, NiShadowGenerator* pkGenerator,
        NiRenderObject* pkGeometry, unsigned int uiSMIndex,
        NiShaderConstantMap::ObjectMappings eMapping,
        const NiPropertyState* pkState, const NiDynamicEffectState* pkEffects,
        const NiTransform& kWorld, const NiBound& kWorldBound,
        unsigned int uiPass);

    static NiTexturingProperty::Map* PSSMGetTextureMapCallback(
        NiShadowGenerator* pkGenerator, NiStandardMaterial::TextureMap eMapType,
        NiRenderObject* pkGeometry, unsigned int uiTMIndex);

// PSSM Specifics
    virtual bool HandlePSSMDirectionalLight(NiShadowGenerator* pkGenerator, 
        NiDirectionalLight* pkDirLight, bool bRegenerateViews,
        bool bUpdateShadowMaps, NiPSSMConfiguration* pkConfiguration);

    virtual void CalculateSliceDistances(NiShadowGenerator* pkGenerator,
        float fNearDistance, float fFarDistance);

    virtual void CalculateSliceViewports(NiShadowGenerator* pkGenerator,
        NiUInt32 uiTextureWidth, NiUInt32 uiTextureHeight, NiUInt32 uiGapSize);

    // Helper functions
    void CalculateQuantizedTransform(const NiCamera* pkShadowCamera,
        const NiShadowMap* pkShadowMap, NiTransform& kQuantizedTransform);

    /**
        Compute a loose bound fitting the given object list
    */
    bool FindGeometryBound(
        const NiVisibleArray& kVisibleArray,
        NiBound& kVisibleGeometryNiBound);

    /// Given a view frustum and a transform, calculate the position of the 8
    /// corner points of the frustum.
    void CalculateFrustumPoints(const NiFrustum& kSliceFrustum,
        const NiTransform& kTransform, NiPoint3* akPoints,
        NiUInt32 uiPointCount) const;

    /**
        Finds all affected geometry from the dynamic affect attached to the
        given shadow generator and culls it against the given shadow camera.

        The dynamic effects unaffected nodes are removed from the geometry list,
        in addition to any nodes contained in the given addtional unaffected
        node list.
    */
    const NiVisibleArray& GetVisibleAffectedGeometryList(
        Ni3DRenderView* pkRenderView);

    void PopulateCasterListCache(NiShadowGenerator* pkGenerator,
        NiPSSMConfiguration* pkPSSMConfig);

    NiPSSMConfiguration m_kDefaultConfiguration;

    // Set of planes that are currently being used by the IsVisible function
    NiFrustumPlanes m_kPlanes;

    NiTPointerMap<const NiShadowGenerator*, NiPSSMConfigurationPtr>
        m_kConfigurationMap;

    // Noise map used for transitions
    NiTexturingProperty::Map* m_pkNoiseTextureMap;

    static NiShadowGenerator* ms_pkActiveGenerator;

    static NiFixedString ms_kPSSMName;
};

#include "NiPSSMShadowClickGenerator.inl"

NiSmartPointer(NiPSSMShadowClickGenerator);

#endif // NIPSSMSHADOWCLICKGENERATOR_H
