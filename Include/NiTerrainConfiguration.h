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
#ifndef NITERRAINCONFIGURATION_H
#define NITERRAINCONFIGURATION_H

#include <NiMemObject.h>
#include <NiUniversalTypes.h>
#include <NiDebug.h>

/**
    The terrain configuration class contains various settings used to determine how the terrain
    data is packed and rendered at run-time depending on the current platform.
    @note The configuration is set per platform and cannot be modified.
*/
class NITERRAIN_ENTRY NiTerrainConfiguration : public NiMemObject
{
public:

    /**
        Default constructor. The constructor sets the configuration flags automatically depending
        on what platform the application is currently running.
    */
    NiTerrainConfiguration();

    /// @cond EMERGENT_INTERNAL

    /**
        Enable morphing data on the terrain. Some platforms do not support morphing, for those
        platforms it is important not to waste memory storing data that is not required. 
        Setting this value to false will cause no morphing data to be generated when loading 
        terrain
    */
    inline void EnableMorphingData(bool bMorphingDataEnabled);

    /**
        Enable tangent data on the terrain. Disable tangent data if you prefer that tangents
        are generated in the shader when required. 
        If terrain is using surfaces that have normal mapping then tangents will be required. 
    */
    inline void EnableTangentData(bool bTangentDataEnabled);
    
    /**
        Enable compression of lighting data. This allows normals and tangents to be stored using
        only two float components instead of the usual three. Some platforms do not support this
        format and may require this compression to be disabled.
    */
    inline void EnableLightingDataCompression(bool bLightingDataCompressionEnabled);
    
    /**
        Enable low detail normal mapping. This allows normals on low detail sections of the terrain
        to be derived from sector wide normal maps. Some platforms do not support normal mapping
        and may require this feature to be disabled.
    */
    inline void EnableLowDetailNormalMapping(bool bLowDetailNormalMappingEnabled);

    /// Query if morphing data is enabled in this configuration
    inline bool IsMorphingDataEnabled() const;
    /// Query if tangent data is enabled in this configuration
    inline bool IsTangentDataEnabled() const;
    /// Query if lighting data compression is enabled in this configuration
    inline bool IsLightingDataCompressionEnabled() const;
    /// Query if low detail normal mapping is enabled in this configuration
    inline bool IsLowDetailNormalMappingEnabled() const;

    /// Query the number of position stream components at high/low detail in this configuration
    inline NiUInt32 GetNumPositionComponents(bool bHighDetail) const;
    /// Query the number of tangent stream components at high/low detail in this configuration
    inline NiUInt32 GetNumTangentComponents(bool bHighDetail) const;
    /// Query the number of normal stream components at high/low detail in this configuration
    inline NiUInt32 GetNumNormalComponents(bool bHighDetail) const;

    /**
        Validate the configuration to make sure it is compatible with the current platform and is
        internally consistent. 

        @returns true if the configuration is valid for the platform.
    */
    bool ValidateConfiguration();

    /// @endcond

private:

    /// Is morphing data enabled?
    bool m_bMorphingDataEnabled;
    /// Is tangent data enabled?
    bool m_bTangentDataEnabled;
    /// Is lighting data enabled?
    bool m_bLightingDataCompressionEnabled;
    /// Is low detail normal mapping enabled?
    bool m_bLowDetailNormalMappingEnabled;
};

#include "NiTerrainConfiguration.inl"

#endif