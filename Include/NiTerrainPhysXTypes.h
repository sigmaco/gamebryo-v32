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
#ifndef NITERRAINPHYSXTYPES_H
#define NITERRAINPHYSXTYPES_H

/**
    Defines the data that should be read from / written to the physx material data block
*/
class NITERRAIN_ENTRY NiPhysXMaterialMetaData
{
public:
    /**
        Default constructor
    */
    inline NiPhysXMaterialMetaData();

    /**
        Initialization constructor
        @param fRestitution the restitution associated with this material meta data
        @param fSFriction the static friction associated with this material meta data
        @param fDFriction the dynamic friction associated with this material meta data
    */
    inline NiPhysXMaterialMetaData(float fRestitution, float fSFriction, float fDFriction);

    /**
        Destructor
    */
    inline ~NiPhysXMaterialMetaData();

    /**
        Sets the restitution value
    */
    inline void SetRestitution(float fRestitution);

    /**
        Gets the restitution value
    */
    inline float GetRestitution() const;

    /**
        Sets the static friction value
    */
    inline void SetStaticFriction(float fFriction);

    /**
        Gets the static friction value
    */
    inline float GetStaticFriction() const;

    /**
        Sets the dynamic friction value
    */
    inline void SetDynamicFriction(float fFriction);

    /**
        Gets the dynamic friction value
    */
    inline float GetDynamicFriction() const;

    /**
        = operator overload allowing to assign a new object using an existing one
    */
    inline NiPhysXMaterialMetaData& operator=(const NiPhysXMaterialMetaData& kData);

private:
    /// The restitution value for this meta data
    float m_fRestitution;

    /// The static friction value for this meta data
    float m_fStaticFriction;

    /// The dynamic friction value for this meta data
    float m_fDynamicFriction;
};

/**
    Helper class to facilitate the storage of a sector's sample values
*/
class NITERRAIN_ENTRY NiTerrainSectorPhysXSampleData
{
public:

    /**
        Default constructor
    */
    inline NiTerrainSectorPhysXSampleData();

    /**
        Initialization constructor
        @param usMat1 material used on the sample's first triangle
        @param usMat2 material used on the sample's second triangle
        @param bTess defines the samples tesselation. The is used as defined by the PhysX SDK
    */
    inline NiTerrainSectorPhysXSampleData(NiUInt16 usMat1, NiUInt16 usMat2, bool bTess);

    /**
        Destructor
    */
    inline ~NiTerrainSectorPhysXSampleData();

    /**
        Sets the material index for the first triangle
    */
    inline void SetMaterialIndex1(NiUInt16 usMatIndex);

    /**
        Gets the material index for the first triangle
    */
    inline NiUInt16 GetMaterialIndex1() const;

    /**
        Sets the material index for the second triangle
    */
    inline void SetMaterialIndex2(NiUInt16 usMatIndex);

    /**
        Gets the material index for the second triangle
    */
    inline NiUInt16 GetMaterialIndex2() const;

    /**
        Sets the tesselation for this sample
    */
    inline void SetTesselation(bool bTess);

    /**
        Gets the tesselation for this sample
    */
    inline bool GetTesselation() const;

    /**
        = operator overload allowing to assign a new object using an existing one
    */
    inline NiTerrainSectorPhysXSampleData& operator=(const NiTerrainSectorPhysXSampleData& kData);

private:

    /// Material used in the first triangle of the sample(as defined by the PhysX SDK)
    NiUInt16 m_usMatIndex1;

    /// Material used in the second triangle of the sample (as defined by the PhysX SDK)
    NiUInt16 m_usMatIndex2;

    /**
    Orientation of the sample's tesselation (as defined by the PhysX SDK):
        _      _
      |\ | or | /|
      |_\|    |/_| 
      true    false

    */
    bool m_bTesselation;
};

/**
    Defines the data that should be read from / written to the physx data block
*/
class NITERRAIN_ENTRY NiTerrainSectorPhysXData : public NiRefObject
{
public:
    /**
        Initialization construction. 
        This allocates the pointer to the terrain sector samples

        @param uiWidth the width of the sector data
        @param uiHeight the height of the sector data
    */
    inline NiTerrainSectorPhysXData(NiUInt32 uiWidth, NiUInt32 uiHeight);

    /**
        Destructor.
    */
    inline ~NiTerrainSectorPhysXData();

    /// Buffer holding all the samples for a terrain sector
    NiTerrainSectorPhysXSampleData* m_pkSamples;

    /// the width the data extends over
    NiUInt32 m_uiWidth;

    /// the height the data extends over
    NiUInt32 m_uiHeight;

    /// the number of samples in the buffer (height * width)
    NiUInt32 m_uiNumSamples;
};

#include "NiTerrainPhysXTypes.inl"

#endif