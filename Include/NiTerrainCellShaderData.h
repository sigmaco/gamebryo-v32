// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not 
// be copied or disclosed except in accordance with the terms of that 
// agreement.
//
//      Copyright (c) 1996-2008 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Chapel Hill, North Carolina 27517
// http://www.emergent.net

#ifndef NITERRAINCELLSHADERDATA_H
#define NITERRAINCELLSHADERDATA_H

#include "NiTerrainLibType.h"
#include <NiMemObject.h>

#include <NiPoint4.h>
#include <NiPoint2.h>
#include <NiUniversalTypes.h>
#include <NiExtraData.h>

class NiMesh;
class NiTerrain;

/**
    This class is used to manage and store the shader data for each Cell in the terrain.
*/
struct NITERRAIN_ENTRY NiTerrainCellShaderData : public NiMemObject
{
    /**
        @name Global Shader Constants

        These strings are declared for the shader constant parameters
        used by the material.
    */
    //@{
    /// Stitching info constant name
    static const char* STITCHINGINFO_SHADER_CONSTANT;
    /// LOD threshold constant name
    static const char* LODTHRESHOLD_SHADER_CONSTANT;
    /// LOD morphing distance constant name
    static const char* LODMORPHDISTANCE_SHADER_CONSTANT;
    /// LOD morphing technique info constant name
    static const char* MORPHMODE_SHADER_CONSTANT;
    /// Adjusted eye position constant name
    static const char* ADJUSTED_EYE_POSITION;
    /// Low detail texture size constant name
    static const char* LOWDETAIL_TEXTURE_SIZES_SHADER_CONSTANT;
    /// Low detail texture offset constant name
    static const char* LOWDETAIL_TEXTURE_OFFSET_SHADER_CONSTANT;
    /// Low detail texture scale constant name
    static const char* LOWDETAIL_TEXTURE_SCALE_SHADER_CONSTANT;
    /// Low detail texture specular constant name
    static const char* LOWDETAIL_SPECULAR_SHADER_CONSTANT;
    /// Blend mask texture scale constant name
    static const char* BLENDMAP_SCALE_SHADER_CONSTANT;
    /// Blend mask texture offset constant name
    static const char* BLENDMAP_OFFSET_SHADER_CONSTANT;
    /// Layer scale constant name
    static const char* LAYER_SCALE_SHADER_CONSTANT;
    /// Debug mode constant name
    static const char* DEBUGMODE_SHADER_CONSTANT;
    /// Render mode constant name
    static const char* RENDERMODE_SHADER_CONSTANT;
    /// Distribution ramp constant name
    static const char* DISTRIBUTION_RAMP_SHADER_CONSTANT;
    /// Parallax map strength constant name
    static const char* PARALLAX_MAP_STRENGTH_SHADER_CONSTANT;
    /// Specular power constant name
    static const char* SPECULAR_POWER_SHADER_CONSTANT;
    /// Specular intensity constant name
    static const char* SPECULAR_INTENSITY_SHADER_CONSTANT;
    /// Layer detail texture scale constant name
    static const char* LAYER_DETAIL_TEXTURE_SCALE_SHADER_CONSTANT;
    
    //@}

    /**
        Render modes
    */
    enum RenderMode
    {
        /// Render the terrain for display to the user
        RENDER_DISPLAY = 0,
        /// Render the terrain for baking diffuse textures
        BAKE_DIFFUSE = 1,
    };

    /**
        Shader debug modes
    */
    enum DebugMode
    {
        /// Disable all debug functionality.
        DEBUG_OFF = 0,

        /// Colorize the terrain according to the normal calculated at
        /// that pixel.
        DEBUG_SHOW_NORMALS = 1,

        /// Colorize the terrain according to the geo-morphing value.
        DEBUG_SHOW_MORPH_VALUE = 2,

        /// Colorize the terrain to highlight the number of surfaces used on
        /// the terrain.
        DEBUG_SHOW_NUM_SURFACES = 3,

        /// Colorize the terrain according to the total mask value
        DEBUG_SHOW_UNPAINTED_AREA = 4,

        /// Colorize the terrain according to the glossiness at the current pixel
        DEBUG_SHOW_GLOSSINESS = 5,

        /// Debug flags section - for disabling specific parts of the shader.
        DEBUG_FLAG_MASK = 0xFFF00000,

        /// Disable the use of normal mapping on the terrain.
        DEBUG_DISABLE_NORMAL_MAPS = 0x01000000,

        /// Disable the use of parallax mapping on the terrain.
        DEBUG_DISABLE_PARALLAX_MAPS = 0x02000000,

        /// Disable the use of specular mapping on the terrain.
        DEBUG_DISABLE_SPECULAR_MAPS = 0x04000000,

        /// Disable the use of detail mapping on the terrain.
        DEBUG_DISABLE_DETAIL_MAPS = 0x08000000,

        /// Disable the use of distribution masks on the terrain.
        DEBUG_DISABLE_DISTRIBUTION_MASKS = 0x10000000,

        /// Disable the effect of lights on the terrain.
        DEBUG_DISABLE_LIGHTING = 0x20000000,

        /// Disable rendering of high detail data. Only use baked maps
        DEBUG_DISABLE_HIGH_DETAIL = 0x40000000,

        /// Disable low detail normal mapping
        DEBUG_DISABLE_BASE_NORMAL_MAP = 0x80000000
    };

    /// Constructor: Sets up default values for the different shader parameters.
    NiTerrainCellShaderData(NiTerrain* pkTerrain);

    /// Sets up the NiExtraData objects on the specified mesh. The NiExtraData objects are used to 
    /// track data from this data class.
    void InitializeShaderData(NiMesh* pkMesh);

    /// Sets the various NiExtraData objects on the specified mesh to match the current data values
    /// of this instance.
    void UpdateShaderData(NiMesh* pkMesh);

    /// Used when morphing between cell lods in order to keep the borders from cracking.
    NiPoint4 m_kStitchingInfo;

    /// Modified camera coordinates used for lod calculations.
    NiPoint3 m_kAdjustedEyePos;

    /// Size of the low detail texture in pixels.
    NiPoint2 m_kLowDetailTextureSize;

    /// Offset to apply to uv lookups when sampling the low detail texture map. X coordinate stores
    /// the offset of the low detail diffuse map, y coordinate stores the offset of the low detail 
    /// normal map.
    NiPoint2 m_kLowDetailTextureOffset;

    /// Scale to apply to uv lookups when sampling the low detail texture map. X coordinate stores
    /// the size of the low detail diffuse map, y coordinate stores the size of the low detail 
    /// normal map.
    NiPoint2 m_kLowDetailTextureScale;

    /// Each component stores the scale for the given surface material layer.
    NiPoint4 m_kLayerScale;

    /// Scale used to modify the incoming uv coordinates for properly accessing the blend map for 
    /// a given cell.
    NiPoint2 m_kBlendMapScale;

    /// Offset used to modify the incoming uv coordinates for property accessing the blend map for
    /// a given cell.
    NiPoint2 m_kBlendMapOffset;

    /// Strength used to modify the distribution map effect on a given layer.
    NiPoint4 m_kDistributionRamp;

    /// Strength used to modify the parallax map effect on a given layer.
    NiPoint4 m_kParallaxStrength;

    /// For a given layer, defines how tight the specular highlights on on the surface.
    NiPoint4 m_kSpecularPower;

    /// Defines the overall strength of the specular lighting for a given layer.
    NiPoint4 m_kSpecularIntensity;

    /// Scale value for the detail map on a given layer.
    NiPoint4 m_kDetailTextureScale;

    /// Threshold for which morphing starts
    float m_fMorphThreshold;

    /// Distance over which morphing occurs
    float m_fMorphDistance;

    /// Type of LOD calculations to perform on the terrain. (2D, 2.5D, 3D).
    NiUInt32 m_uiMorphMode;

    ///@name Terrain wide shader data
    //@{
    /// Debug mode extra data
    NiExtraData* m_pkDebugModeData;
    /// Render mode extra daya
    NiExtraData* m_pkRenderModeData;
    /// Low detail specular data
    NiExtraData* m_pkLowDetailSpecularData;
    //@}
};

#endif
