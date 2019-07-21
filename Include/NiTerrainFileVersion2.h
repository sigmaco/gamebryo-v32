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

#ifndef NITERRAINFILEVERSION2_H
#define NITERRAINFILEVERSION2_H

#include <efdXML/tinyxml.h>
#include <NiBoxBV.h>

#include "NiTerrainLibType.h"
#include "NiTerrainFile.h"

/** 
    The class is used to iterate over and write terrain sector files.
 */
class NITERRAIN_ENTRY NiTerrainFileVersion2 : public NiTerrainFile
{
    friend class NiTerrainFile;

public:

    /**
        Detect the version of the file in a particular terrain archive

        @param pcTerrainArchive The file for which we want the file version
        @return The file version currently in use
    */
    static FileVersion DetectFileVersion(const char* pcTerrainArchive);

    /// Destructor.
    virtual ~NiTerrainFileVersion2();

    /// @name NewInterface
    /// @see NiTerrainFile
    /// @{
    virtual void Close();
    virtual void GetFilePaths(efd::set<efd::utf8string>& kFilePaths);
    virtual bool ReadConfiguration(efd::UInt32& uiSectorSize, efd::UInt32& uiNumLOD, 
        efd::UInt32& uiMaskSize, efd::UInt32& uiLowDetailSize, float& fMinElevation, 
        float& fMaxElevation, float& fVertexSpacing, float& fLowDetailSpecularPower, 
        float& fLowDetailSpecularIntensity, efd::UInt32& uiSurfaceCount);
    virtual void WriteConfiguration(efd::UInt32 uiSectorSize, efd::UInt32 uiNumLOD, 
        efd::UInt32 uiMaskSize, efd::UInt32 uiLowDetailSize, float fMinElevation, 
        float fMaxElevation, float fVertexSpacing, float fLowDetailSpecularPower, 
        float fLowDetailSpecularIntensity, efd::UInt32 uiSurfaceCount);
    virtual bool ReadSurface(NiUInt32 uiSurfaceIndex, NiTerrainAssetReference* pkPackageRef, 
        NiFixedString& kSurfaceID, efd::UInt32& uiIteration);
    /// @}

    /// Deprecated read interface
    virtual bool ReadSurface(NiUInt32 uiSurfaceIndex, NiFixedString& kPackageID, 
        NiFixedString& kSurfaceID);
    /// Deprecated write interface
    virtual void WriteSurface(NiUInt32 uiSurfaceIndex, NiFixedString kPackageID, 
        NiFixedString kSurfaceID);

protected:

    /**
        Constructor for this terrain file iterator.

        @param pcFileName the terrain file to attempt to open.
        @param bWriteAccess whether the file should be read of written.
    */
    NiTerrainFileVersion2(const char* pcFileName, bool bWriteAccess);

    /**
        Initialize the class by opening the file and reading the first couple
        of headers. 

        @return true if the class was successfully initialized.
    */
    virtual bool Initialize();

    /**
        Write the file header to the terrain file
        @return true when successful
    */
    bool WriteFileHeader();
    
    /**
        Write the configuration out to file
        @return true when successful
    */
    bool WriteConfiguration();
    /**
        Write the list of surfaces to a section of a DOM document.
        @return true when successful
    */
    bool WriteSurfaceIndex();

    /**
        Read the configuration from the file
        @param pkRootElement the Xml element to read the configuration from
        @return true when successful
    */
    bool ReadConfiguration(efd::TiXmlElement* pkRootElement);
    
    /**
        Read the list of surfaces from a section of a DOM document.
        @param pkRootElement the Xml element to read the surface index from
        @return true when successful
    */
    bool ReadSurfaceIndex(efd::TiXmlElement* pkRootElement);

    /**
        Generate the terrain config file's filename
        @return the generated file name
    */
    inline NiString GenerateTerrainConfigFilename();

    /// The file object to access the file through
    static const char* ms_pcTerrainConfigFile;

    // File data:
    /// The file object to access the file through
    efd::TiXmlDocument m_kFile;

    // Current File Data:
    /// The array of surface packages - per index
    NiTObjectArray<NiFixedString> m_kSurfacePackageArray;
    /// The array of surface names - per index
    NiTObjectArray<NiFixedString> m_kSurfaceNameArray;

    /// The sector size in verts
    efd::UInt32 m_uiSectorSize;
    /// The number of LOD per sector
    efd::UInt32 m_uiNumLOD;
    /// The size of a blend mask per sector
    efd::UInt32 m_uiMaskSize;
    /// The size of a low detail diffuse texture per sector
    efd::UInt32 m_uiLowDetailSize;
    /// The minimum elevation of a terrain
    efd::Float32 m_fMinElevation;
    /// The maximum elevation of a terrain
    efd::Float32 m_fMaxElevation;
    /// The spacing between vertices of the terrain
    efd::Float32 m_fVertexSpacing;
    /// The low detail specular power
    efd::Float32 m_fLowDetailSpecularPower;
    /// The low detail specular intensity
    efd::Float32 m_fLowDetailSpecularIntensity;
    /// The number of surfaces on the terrain
    efd::UInt32 m_uiSurfaceCount;
    /// Flag to signal that the configuration is valid
    bool m_bConfigurationValid;
};

#include "NiTerrainFileVersion2.inl"

#endif // NITERRAINFILEVERSION2_H
