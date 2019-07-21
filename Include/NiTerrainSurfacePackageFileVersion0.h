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
#ifndef NiTerrainSurfacePackageFileVersion0_H
#define NiTerrainSurfacePackageFileVersion0_H

#include <NiMemManager.h>
#include <NiRefObject.h>
#include <NiUniversalTypes.h>
#include <efd/utf8string.h>

#include "NiTerrainLibType.h"
#include "NiSurface.h"
#include "NiTerrainSurfacePackageFile.h"

/**
    This class is used to stream a surface package's data to/from disk. 
    The class provides basic versioning support to allow backwards compatibility with older
    package formats.
*/
class NITERRAIN_ENTRY NiTerrainSurfacePackageFileVersion0 : public NiTerrainSurfacePackageFile
{
    friend class NiTerrainSurfacePackageFile;

public:
    /// Version type for storing the file version
    typedef NiUInt32 FileVersion;

    /**
        This function must be called on all successfully opened files to signal that the file
        is no longer used. Some save files may use this function as a point at which to flush the 
        data to disk.
    */
    virtual void Close();

    /// Destructor.
    virtual ~NiTerrainSurfacePackageFileVersion0();

    /**
        Return the set of files that are relevant to this format

        @param kFilePaths A set to populate with the list of filepaths that this file spans.
    */
    virtual void GetFilePaths(efd::set<efd::utf8string>& kFilePaths);

    /**
        Read the name of the package from the file.

        @param kPackageName The variable to store the package name in.
        @param uiIteration The iteration count of the last save.
        @return false If the package name could not be read.
    */
    virtual bool ReadPackageConfig(efd::utf8string& kPackageName, efd::UInt32& uiIteration);

    /**
        Read the number of surfaces from the file.

        @param uiNumSurfaces The variable to store the number of surfaces in
        @return True if the number of surfaces could be determined.
    */
    virtual bool ReadNumSurfaces(efd::UInt32& uiNumSurfaces);

    /**
        Read the configuration of a single surface from the package by it's index.

        @param uiSurfaceIndex The index of the surface the user is interested in
        @param kName The name of the surface
        @param fTextureTiling The tiling of the main texture
        @param fDetailTiling The tiling of the detail texture
        @param fRotation The rotation of the main texture
        @param fParallaxStrength The strength of the parallax mapping effect
        @param fDistributionMaskStrength The strength of the distribution mask effect
        @param fSpecularPower The power to use in specular calculations
        @param fSpecularIntensity The intensity to use in specular calculations
        @param uiNumDecorationLayers The number of decoration layers assigned to this surface

        @return True if the surface data could be read successfully
    */
    virtual bool ReadSurfaceConfig(efd::UInt32 uiSurfaceIndex,
        efd::utf8string& kName, 
        efd::Float32& fTextureTiling,
        efd::Float32& fDetailTiling,
        efd::Float32& fRotation,
        efd::Float32& fParallaxStrength,
        efd::Float32& fDistributionMaskStrength,
        efd::Float32& fSpecularPower,
        efd::Float32& fSpecularIntensity,
        efd::UInt32& uiNumDecorationLayers);
    
    /**
        Read out the reference to the texture asset stored for a particular slot in the material 
        package.

        @param uiSurfaceIndex The index of the surface the user is interested in
        @param uiSlotID The ID of the texture slot the user is interested in
        @param pkReference An asset reference object to store the relevant data in

        @return True if the data could be successfully read from the file
    */
    virtual bool ReadSurfaceSlot(efd::UInt32 uiSurfaceIndex,
        efd::UInt32 uiSlotID,
        NiTerrainAssetReference* pkReference);
    
    /**
        Read any metadata that has been assigned to a particular surface

        @param uiSurfaceIndex The index of the surface the user is interested in
        @param kMetaData A metadata object to store the requested information in

        @return True if the data could be read successfully
    */
    virtual bool ReadSurfaceMetadata(efd::UInt32 uiSurfaceIndex,
        NiMetaData& kMetaData);

protected:

    /**
        A structure to store the data relevant to surface texture slots
    */
    struct TextureSlotData
    {
        efd::utf8string m_kLastRelativePath;
        efd::utf8string m_kAssetID;
    };

    /**
        A structure to store the all the data about a surface in the file
    */
    struct SurfaceData : public NiMemObject
    {
        efd::utf8string m_kName;
        efd::Float32 m_fTextureTiling;
        efd::Float32 m_fDetailTiling;
        efd::Float32 m_fRotation;
        efd::Float32 m_fParallaxStrength;
        efd::Float32 m_fDistributionMaskStrength;
        efd::Float32 m_fSpecularPower;
        efd::Float32 m_fSpecularIntensity;
        efd::UInt32 m_uiNumDecorationLayers;
        TextureSlotData m_akTextureSlots[NiSurface::NUM_SURFACE_MAPS];
        NiMetaData m_kMetaData;
    };

    /**
        Constructor for this surface package file iterator

        @param kFilename the file path where to attempt to open the file
        @param bWriteAccess Whether to write to the file or not
    */
    NiTerrainSurfacePackageFileVersion0(efd::utf8string kFilename, bool bWriteAccess);

    /**
        Initialize the class by opening the file and reading the first couple
        of headers. 

        @return true if the class was successfully initialized.
    */
    virtual bool Initialize();

    /**
        Read the package wide information from the file
    */
    bool ReadOldPackage(const efd::TiXmlElement* pkRootElement);

    /**
        Read an old surface from the file
    */
    bool ReadOldSurface(const efd::TiXmlElement* pkRootElement, SurfaceData& kTempSurfaceData);

    /// The file object to access the file through
    efd::TiXmlDocument m_kFile;
    // Has the configuration data in this file been read from the file yet?
    bool m_bConfigurationValid;
    // Package name
    efd::utf8string m_kPackageName;
    // Iteration count
    efd::UInt32 m_uiIteration;
    // The list of surfaces
    efd::vector<SurfaceData*> m_kSurfaces;
};

#endif // NiTerrainSurfacePackageFileVersion0_H
