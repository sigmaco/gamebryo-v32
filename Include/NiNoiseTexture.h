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

#ifndef NINOISETEXTURE_H
#define NINOISETEXTURE_H

#include "NiTexturingProperty.h"
#include "NiSourceTexture.h"
#include "NiStandardMaterial.h"

/**
    A noise map creates a texture containing random 8-bit values for each 
    pixel's channel.

    Currently only single channel (red) noise maps are supported
 */
class NIMAIN_ENTRY NiNoiseTexture : public NiSourceTexture
{
    NiDeclareRTTI;

    /// Private Default constructor to force usage of Create function.
    NiNoiseTexture();

public:
    enum NoiseType
    {
        NT_RAND = 0,
        NT_MAX    = 1
    };

    static NiNoiseTexture* Create(NoiseType eNoiseType, NiUInt32 uiTextureSize, 
        NiUInt32 uiRandSeed);

    /**
        @return the current noise generation technique in use
    */
    inline NoiseType GetNoiseType() const;
    
    /**
        @return a fixed string representation of the given map type in
            NiStandardMaterial
    */
    inline static const NiFixedString& GetMapNameFromType(
        NiStandardMaterial::NoiseMapType eType);

    /**
        @return the NiStandardMaterial::NoiseMapType that corresponds to the 
            given type name
    */
    inline static bool GetTypeIDFromName(const NiFixedString& kName, 
        unsigned int& uiID);

    // *** begin Emergent internal use only ***
    static void _SDMInit();
    static void _SDMShutdown();
    // *** end Emergent internal use only ***

    /**
        Initializes the given noise map according to the given parameters. If 
        the given noise map has already been initialized, its existing data is 
        erased and it is re-initialized.
    */
    static bool Initialize(NiNoiseTexture* pkNoiseMap, NoiseType eNoiseType,
        NiTexturingProperty::FilterMode eFilterMode,
        NiTexturingProperty::ClampMode eClampMode, 
        NiUInt32 uiTextureSize, NiUInt32 uiRandSeed = 0);

protected:

    // Protected so that the user doesn't attempt to change the noise type after
    // the texture has been generated
    inline void SetNoiseType(NoiseType eNoiseType);

    static NiFixedString ms_akMapFromTypeName[
        NiStandardMaterial::NOISE_MAX];

    NoiseType m_eNoiseType;
};

NiSmartPointer(NiNoiseTexture);

#include "NiNoiseTexture.inl"

#endif // NINOISETEXTURE_H