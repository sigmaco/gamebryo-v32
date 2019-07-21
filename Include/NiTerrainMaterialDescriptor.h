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
#ifndef NITERRAINMATERIALDESCRIPTOR_H
#define NITERRAINMATERIALDESCRIPTOR_H

#include "NiTerrainLibType.h"
#include <NiMaterialDescriptor.h>
#include <NiBitfield.h>
#include <NiString.h>
#include "NiFragmentLighting.h"

/**
    This class manages the bit field for the terrain material.

    This bit field is then used to construct the individual descriptors for
    both the vertex and pixel shader. The bit field encodes the layers
    affecting the terrain, lights affecting the terrain, and various other
    attributes.
*/
class NITERRAIN_ENTRY NiTerrainMaterialDescriptor : public NiMaterialDescriptor
{
public:

    /// Constructor
    NiTerrainMaterialDescriptor();

    /**
        Helper method that sets the appropriate bits in the bit field based on
        the specified layer parameters.

        @param uiLayerIndex Layer to operate on.
        @param bEnableDiffuseMap True if a diffuse/base map for the specified layer exists.
        @param bEnableNormalMap True if a normal map for the specified layer exists.
        @param bEnableParallaxMap True if a parallax map for the specified layer exists.
        @param bEnableDetailMap True if a detail map for the specified layer exists.
        @param bEnableDistributionMap True if a distribution mask for the specified layer exists.
        @param bEnableSpecularMap True if a distribution mask for the specified layer exists.
    */
    void SetLayerCaps(NiUInt32 uiLayerIndex, bool bEnableDiffuseMap, bool bEnableNormalMap, 
        bool bEnableParallaxMap, bool bEnableDetailMap, bool bEnableDistributionMap, 
        bool bEnableSpecularMap);

    /**
        Helper method to detect if any normal maps have been applied to the terrain's surface
    */
    bool HasNormalMapping() const;

    /**
        Helper method to detect if any parallax maps have been applied to the terrain's surface
    */
    bool HasParallaxMapping() const;

    /**
        Helper method to detect if any specular/gloss maps have been applied to the terrain
    */
    bool HasSpecularMapping() const;

    /**
        Determines if a view vector should be calculated by analyzing the bits
        set on the material descriptor.

        @note A view vector is required if any layer has a parallax map or a
            specular map.
    */
    bool RequiresViewVector();

    /// @cond EMERGENT_INTERNAL
    NiBeginDefaultBitfieldEnum()

    // First byte, Index 0 (1 bit left)
    NiDeclareDefaultIndexedBitfieldEntry(FOGTYPE, 2, BITFIELDSTART, 0)
    NiDeclareDefaultIndexedBitfieldEntry(BLENDMAP_COUNT, 2, FOGTYPE, 0)
    NiDeclareDefaultIndexedBitfieldEntry(ENABLE_SURFACEUVMODIFIERS, 1, BLENDMAP_COUNT, 0);
    NiDeclareDefaultIndexedBitfieldEntry(SPECULAR, 1, ENABLE_SURFACEUVMODIFIERS, 0)
    NiDeclareDefaultIndexedBitfieldEntry(APPLYMODE, 1, SPECULAR, 0)
    NiDeclareDefaultIndexedBitfieldEntry(VERTEXCOLORS, 1, APPLYMODE, 0)

    // Second byte, Index 0
    NiDeclareDefaultIndexedBitfieldEntry(AMBDIFFEMISSIVE, 2, VERTEXCOLORS, 0)
    NiDeclareDefaultIndexedBitfieldEntry(LIGHTINGMODE, 1, AMBDIFFEMISSIVE, 0)
    NiDeclareDefaultIndexedBitfieldEntry(PERVERTEXFORLIGHTS,1, LIGHTINGMODE, 0)
    NiDeclareDefaultIndexedBitfieldEntry(PSSMSLICETRANSITIONSENABLED, 1, PERVERTEXFORLIGHTS, 0)
    NiDeclareDefaultIndexedBitfieldEntry(PSSMSLICECOUNT, 3, PSSMSLICETRANSITIONSENABLED, 0)

    // Third byte, Index 0
    NiDeclareDefaultIndexedBitfieldEntry(SHADOWMAPFORLIGHT, 8, PSSMSLICECOUNT, 0)

    // Fourth byte, Index 0
    NiDeclareDefaultIndexedBitfieldEntry(MORPH_MODE, 2, SHADOWMAPFORLIGHT, 0)
    NiDeclareDefaultIndexedBitfieldEntry(SHADOWTECHNIQUE, 2, MORPH_MODE, 0)
    NiDeclareDefaultLastIndexedBitfieldEntry(PSSMWHICHLIGHT, 4, SHADOWTECHNIQUE, 0)

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
    NiDeclareDefaultIndexedBitfieldEntry(INPUT_TANGENTS, 1, LAYER3_DETAILMAP_ENABLED, 1)
    NiDeclareDefaultIndexedBitfieldEntry(INPUT_MORPHING, 1, INPUT_TANGENTS, 1)
    NiDeclareDefaultIndexedBitfieldEntry(INPUT_LIGHTING_COMPRESSED, 1, INPUT_MORPHING, 1)
    NiDeclareDefaultIndexedBitfieldEntry(INPUT_NORMALS, 1, INPUT_LIGHTING_COMPRESSED, 1)
    NiDeclareDefaultLastIndexedBitfieldEntry(POINTLIGHTCOUNT, 4, INPUT_NORMALS, 1)

    // First byte, Index 2
    NiDeclareDefaultIndexedBitfieldEntry(SPOTLIGHTCOUNT, 4, BITFIELDSTART, 2)
    NiDeclareDefaultIndexedBitfieldEntry(DIRLIGHTCOUNT, 4, SPOTLIGHTCOUNT, 2)

    // Second byte, Index 2
    NiDeclareDefaultIndexedBitfieldEntry(RENDER_MODE, 4, DIRLIGHTCOUNT, 2)
    NiDeclareDefaultIndexedBitfieldEntry(DEBUG_MODE, 4, RENDER_MODE, 2)

    // Third byte, Index 2
    NiDeclareDefaultIndexedBitfieldEntry(USE_LOWDETAILDIFFUSE, 1, DEBUG_MODE, 2)
    NiDeclareDefaultIndexedBitfieldEntry(USE_LOWDETAILNORMAL, 1, USE_LOWDETAILDIFFUSE, 2)
    NiDeclareDefaultIndexedBitfieldEntry(LAYER0_BASEMAP_ENABLED, 1, USE_LOWDETAILNORMAL, 2)
    NiDeclareDefaultIndexedBitfieldEntry(LAYER1_BASEMAP_ENABLED, 1, LAYER0_BASEMAP_ENABLED, 2)
    NiDeclareDefaultIndexedBitfieldEntry(LAYER2_BASEMAP_ENABLED, 1, LAYER1_BASEMAP_ENABLED, 2)
    NiDeclareDefaultIndexedBitfieldEntry(LAYER3_BASEMAP_ENABLED, 1, LAYER2_BASEMAP_ENABLED, 2)

    NiEndDefaultBitfieldEnum();
    /// @endcond
};

#endif
