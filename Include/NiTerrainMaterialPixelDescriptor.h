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
#ifndef NITERRAINPIXELDESCRIPTOR_H
#define NITERRAINPIXELDESCRIPTOR_H

#include "NiTerrainLibType.h"
#include <NiGPUProgramDescriptor.h>
#include <NiBitfield.h>
#include <NiString.h>

class NiTerrainMaterialDescriptor;

/**
    This class manages the bit fields that are constructed from the terrain
    material descriptor.

    It is used when determining how to construct a shade tree in order to
    generate a pixel shader.
*/
class NITERRAIN_ENTRY NiTerrainMaterialPixelDescriptor :
    public NiGPUProgramDescriptor
{
public:

    /// Convert the bit field to a human readable string.
    ///
    /// This is useful when debugging the values set in the bit field.
    NiString ToString();

    /// Return true if the specified layer supports a base/albedo map.
    bool SupportsBaseMap(NiUInt32 uiLayerIndex);

    /// Enable or disable the base/albedo map for the specified layer.
    void SetSupportsBaseMap(NiUInt32 uiLayerIndex, bool bEnabled);

    /// Return true if the specified layer supports a detail map.
    bool SupportsDetailMap(NiUInt32 uiLayerIndex);

    /// Enable or disable the detail map for the specified layer.
    void SetSupportsDetailMap(NiUInt32 uiLayerIndex, bool bEnabled);

    /// Return true if the specified layer supports a normal map.
    bool SupportsNormalMap(NiUInt32 uiLayerIndex);

    /// Enable or disable normal map for a given layer.
    void SetNormalMapEnabled(NiUInt32 uiLayerIndex, bool bEnabled);

    /// Return true if the specified layer supports a parallax map.
    bool SupportsParallaxMap(NiUInt32 uiLayerIndex);

    /// Enable or disable parallax map for a given layer.
    void SetParallaxMapEnabled(NiUInt32 uiLayerIndex, bool bEnabled);

    /// Return true if the specified layer supports a distribution mask.
    bool SupportsDistributionMap(NiUInt32 uiLayerIndex);

    /// Enables or disables the distribution map on the specified layer.
    void SetSupportsDistributionMap(NiUInt32 uiLayerIndex, bool bEnabled);

    /// Return true if the specified layer supports specular maps.
    bool SupportsSpecularMap(NiUInt32 uiLayerIndex);

    /// Enables or disables specular map support on the given layer.
    void SetSupportsSpecularMap(NiUInt32 uiLayerIndex, bool bEnabled);

    /// Analyzes the material descriptor and sets the appropriate bits in the
    /// pixel descriptor's bit field to reflect the necessary state.
    void SetLayerCapabilitiesFromMaterialDescriptor(
        NiTerrainMaterialDescriptor* pkMaterialDesc, NiUInt32 uiLayer);

    /// @cond EMERGENT_INTERNAL
    NiBeginDefaultBitfieldEnum()

    // First byte, index 0
    NiDeclareDefaultIndexedBitfieldEntry(FOGTYPE, 3, BITFIELDSTART, 0)
    NiDeclareDefaultIndexedBitfieldEntry(BLENDMAP_COUNT, 2, FOGTYPE, 0);
    NiDeclareDefaultIndexedBitfieldEntry(INPUT_WORLDPOSITION, 1, BLENDMAP_COUNT, 0)
    NiDeclareDefaultIndexedBitfieldEntry(AMBDIFFEMISSIVE, 2, INPUT_WORLDPOSITION, 0)

    // Second byte, index 0
    NiDeclareDefaultIndexedBitfieldEntry(LIGHTINGMODE, 2, AMBDIFFEMISSIVE, 0)
    NiDeclareDefaultIndexedBitfieldEntry(SPECULAR, 1, LIGHTINGMODE, 0)
    NiDeclareDefaultIndexedBitfieldEntry(APPLYAMBIENT, 1, SPECULAR, 0)
    NiDeclareDefaultIndexedBitfieldEntry(APPLYEMISSIVE, 1, APPLYAMBIENT, 0)
    NiDeclareDefaultIndexedBitfieldEntry(APPLYMODE, 1, APPLYEMISSIVE, 0)
    NiDeclareDefaultIndexedBitfieldEntry(PERVERTEXLIGHTING, 1, APPLYMODE, 0)
    NiDeclareDefaultIndexedBitfieldEntry(INPUT_WORLDNBT, 1, PERVERTEXLIGHTING, 0)

    // Third byte, index 0
    NiDeclareDefaultIndexedBitfieldEntry(POINTLIGHTCOUNT, 4, INPUT_WORLDNBT, 0)
    NiDeclareDefaultIndexedBitfieldEntry(SPOTLIGHTCOUNT, 4, POINTLIGHTCOUNT, 0)

    // Fourth byte, index 0
    NiDeclareDefaultIndexedBitfieldEntry(DIRLIGHTCOUNT, 4, SPOTLIGHTCOUNT, 0)
    NiDeclareDefaultLastIndexedBitfieldEntry(SHADOWTECHNIQUE, 4, DIRLIGHTCOUNT, 0)

    // First byte, Index 1
    NiDeclareDefaultIndexedBitfieldEntry(NUM_LAYERS, 4, BITFIELDSTART, 1)
    NiDeclareDefaultIndexedBitfieldEntry(LAYER0_NORMALMAP_ENABLED, 1, NUM_LAYERS, 1)
    NiDeclareDefaultIndexedBitfieldEntry(LAYER0_PARALLAXMAP_ENABLED, 1, LAYER0_NORMALMAP_ENABLED, 1)
    NiDeclareDefaultIndexedBitfieldEntry(LAYER0_DISTMAP_ENABLED, 1, LAYER0_PARALLAXMAP_ENABLED, 1)
    NiDeclareDefaultIndexedBitfieldEntry(LAYER0_SPECULARMAP_ENABLED, 1, LAYER0_DISTMAP_ENABLED, 1)

    // Second byte, Index 1
    NiDeclareDefaultIndexedBitfieldEntry(LAYER0_DETAILMAP_ENABLED, 1, LAYER0_SPECULARMAP_ENABLED, 1)
    NiDeclareDefaultIndexedBitfieldEntry(LAYER1_NORMALMAP_ENABLED, 1, LAYER0_DETAILMAP_ENABLED, 1)
    NiDeclareDefaultIndexedBitfieldEntry(LAYER1_PARALLAXMAP_ENABLED, 1, LAYER1_NORMALMAP_ENABLED, 1)
    NiDeclareDefaultIndexedBitfieldEntry(LAYER1_DISTMAP_ENABLED, 1, LAYER1_PARALLAXMAP_ENABLED, 1)
    NiDeclareDefaultIndexedBitfieldEntry(LAYER1_SPECULARMAP_ENABLED, 1, LAYER1_DISTMAP_ENABLED, 1)
    NiDeclareDefaultIndexedBitfieldEntry(LAYER1_DETAILMAP_ENABLED, 1, LAYER1_SPECULARMAP_ENABLED, 1)
    NiDeclareDefaultIndexedBitfieldEntry(LAYER2_NORMALMAP_ENABLED, 1, LAYER1_DETAILMAP_ENABLED, 1)
    NiDeclareDefaultIndexedBitfieldEntry(LAYER2_PARALLAXMAP_ENABLED, 1, LAYER2_NORMALMAP_ENABLED, 1)

    // Third byte, Index 1
    NiDeclareDefaultIndexedBitfieldEntry(LAYER2_DISTMAP_ENABLED, 1, LAYER2_PARALLAXMAP_ENABLED, 1)
    NiDeclareDefaultIndexedBitfieldEntry(LAYER2_SPECULARMAP_ENABLED, 1, LAYER2_DISTMAP_ENABLED, 1)
    NiDeclareDefaultIndexedBitfieldEntry(LAYER2_DETAILMAP_ENABLED, 1, LAYER2_SPECULARMAP_ENABLED, 1)
    NiDeclareDefaultIndexedBitfieldEntry(LAYER3_NORMALMAP_ENABLED, 1, LAYER2_DETAILMAP_ENABLED, 1)
    NiDeclareDefaultIndexedBitfieldEntry(LAYER3_PARALLAXMAP_ENABLED, 1, LAYER3_NORMALMAP_ENABLED, 1)
    NiDeclareDefaultIndexedBitfieldEntry(LAYER3_DISTMAP_ENABLED, 1, LAYER3_PARALLAXMAP_ENABLED, 1)
    NiDeclareDefaultIndexedBitfieldEntry(LAYER3_SPECULARMAP_ENABLED, 1, LAYER3_DISTMAP_ENABLED, 1)
    NiDeclareDefaultIndexedBitfieldEntry(LAYER3_DETAILMAP_ENABLED, 1, LAYER3_SPECULARMAP_ENABLED, 1)

    // Fourth byte, Index 1
    NiDeclareDefaultLastIndexedBitfieldEntry(SHADOWMAPFORLIGHT, 8, LAYER3_DETAILMAP_ENABLED, 1)

    // First byte, Index 2
    NiDeclareDefaultIndexedBitfieldEntry(PSSMSLICETRANSITIONSENABLED, 1, BITFIELDSTART, 2)
    NiDeclareDefaultIndexedBitfieldEntry(PSSMSLICECOUNT, 3, PSSMSLICETRANSITIONSENABLED, 2)
    NiDeclareDefaultIndexedBitfieldEntry(PSSMWHICHLIGHT, 4, PSSMSLICECOUNT, 2)

    // Second byte, Index 2
    NiDeclareDefaultIndexedBitfieldEntry(USE_LOWDETAILDIFFUSE, 1, PSSMWHICHLIGHT, 2)
    NiDeclareDefaultIndexedBitfieldEntry(USE_LOWDETAILNORMAL, 1, USE_LOWDETAILDIFFUSE, 2)
    NiDeclareDefaultIndexedBitfieldEntry(DEBUG_MODE, 4, USE_LOWDETAILNORMAL, 2)
    NiDeclareDefaultIndexedBitfieldEntry(INPUT_WORLDVIEW, 1, DEBUG_MODE, 2);
    NiDeclareDefaultIndexedBitfieldEntry(INPUT_WORLDNORMAL, 1, INPUT_WORLDVIEW, 2);

    // Third byte, Index 2
    NiDeclareDefaultIndexedBitfieldEntry(RENDER_MODE, 4, INPUT_WORLDNORMAL, 2)
    NiDeclareDefaultIndexedBitfieldEntry(LAYER0_BASEMAP_ENABLED, 1, RENDER_MODE, 2)
    NiDeclareDefaultIndexedBitfieldEntry(LAYER1_BASEMAP_ENABLED, 1, LAYER0_BASEMAP_ENABLED, 2)
    NiDeclareDefaultIndexedBitfieldEntry(LAYER2_BASEMAP_ENABLED, 1, LAYER1_BASEMAP_ENABLED, 2)
    NiDeclareDefaultIndexedBitfieldEntry(LAYER3_BASEMAP_ENABLED, 1, LAYER2_BASEMAP_ENABLED, 2)

    NiEndDefaultBitfieldEnum()

    /// @endcond
};

#endif
