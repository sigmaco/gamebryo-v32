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
#ifndef NITERRAINSURFACEPACKAGEFILEVERSION1_H
#define NITERRAINSURFACEPACKAGEFILEVERSION1_H

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
class NITERRAIN_ENTRY NiTerrainSurfacePackageFileVersion1 : public NiTerrainSurfacePackageFile
{
    friend class NiTerrainSurfacePackageFile;

public:
    /// Version type for storing the file version
    typedef NiUInt32 FileVersion;

    /**
        Attempt to detect what version of this file format this file is.

        @param kFilename The file to attempt to detect the version of
        @return The version of the file
    */
    static FileVersion DetectFileVersion(const efd::utf8string& kFilename);

    /**
        This function must be called on all successfully opened files to signal that the file
        is no longer used. Some save files may use this function as a point at which to flush the 
        data to disk.
    */
    virtual void Close();

    /// Destructor.
    virtual ~NiTerrainSurfacePackageFileVersion1();

    /**
        Return the set of files that are relevant to this format

        @param kFilePaths A set to populate with the list of filepaths that this file spans.
    */
    virtual void GetFilePaths(efd::set<efd::utf8string>& kFilePaths);

    /// @see NiTerrainSurfacePackageFile
    /// @{
    virtual void Precache(efd::UInt32 uiDataFields);
    virtual bool ReadPackageConfig(efd::utf8string& kPackageName, efd::UInt32& uiIteration);
    virtual bool ReadNumSurfaces(efd::UInt32& uiNumSurfaces);
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
    virtual bool ReadSurfaceSlot(efd::UInt32 uiSurfaceIndex,
        efd::UInt32 uiSlotID,
        NiTerrainAssetReference* pkReference);
    virtual bool ReadSurfaceMetadata(efd::UInt32 uiSurfaceIndex,
        NiMetaData& kMetaData);
    virtual bool ReadSurfaceCompiledTextures(efd::UInt32 uiSurfaceIndex,
        NiTexturePtr* aspTextures, efd::UInt32 uiNumTextures);
    virtual bool ReadSurfaceCompiledTextures(efd::utf8string kSurfaceName, 
        NiTexturePtr* aspTextures, efd::UInt32 uiNumTextures);

    virtual void WritePackageConfig(const efd::utf8string& kPackageName, efd::UInt32 uiIteration);
    virtual void WriteNumSurfaces(const efd::UInt32& uiNumSurfaces);
    virtual void WriteSurfaceConfig(efd::UInt32 uiSurfaceIndex,
        const efd::utf8string& kName, 
        efd::Float32 fTextureTiling,
        efd::Float32 fDetailTiling,
        efd::Float32 fRotation,
        efd::Float32 fParallaxStrength,
        efd::Float32 fDistributionMaskStrength,
        efd::Float32 fSpecularPower,
        efd::Float32 fSpecularIntensity,
        efd::UInt32 uiNumDecorationLayers);
    virtual void WriteSurfaceSlot(efd::UInt32 uiSurfaceIndex,
        efd::UInt32 uiSlotID,
        const NiTerrainAssetReference* pkReference);
    virtual void WriteSurfaceMetadata(efd::UInt32 uiSurfaceIndex,
        const NiMetaData& kMetaData);
    virtual void WriteSurfaceCompiledTextures(efd::UInt32 uiSurfaceIndex,
        NiTexturePtr* aspTextures, efd::UInt32 uiNumTextures);
    /// @}

protected:

    // Typedef to help when saving the list of compiled textures
    typedef efd::map<efd::utf8string, efd::UInt32> StreamOffsetTable;

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
        NiTexturePtr m_aspTextures[NiSurface::NUM_SURFACE_TEXTURES];
    };

    /**
        Constructor for this surface package file iterator

        @param kFilename the file path where to attempt to open the file
        @param bWriteAccess Whether to write to the file or not
    */
    NiTerrainSurfacePackageFileVersion1(efd::utf8string kFilename, bool bWriteAccess);

    /**
        Initialize the class by opening the file and reading the first couple
        of headers. 

        @return true if the class was successfully initialized.
    */
    virtual bool Initialize();

    /**
        Read the package wide information from the file
    */
    bool ReadConfiguration(efd::TiXmlElement* pkRootElement);

    /**
        Read all the surfaces stored in the file ready to be retrieved
    */
    bool ReadSurfaces(efd::TiXmlElement* pkRootElement);

    /**
        Read a single surface in from the file
    */
    bool ReadSurface(const efd::TiXmlElement* pkRootElement, SurfaceData& kTempSurfaceData);

    /**
        Read a set of precompiled textures from the binary file
    */
    bool ReadCompiledTextures();

    /**
        Write the file header
    */
    bool WriteFileHeader();

    /**
        Write the package information to the file
    */
    bool WritePackage();

    /**
        Write the surface data to the file
    */
    bool WriteSurfaces();

    /**
        Write the set of precompiled textures to the binary file
    */
    bool WriteCompiledTextures();

    /**
        Write a compiled texture table at a certain point in the file
    */
    bool WriteCompiledTextureTable(efd::BinaryStream& kStream, StreamOffsetTable& kOffsetMap);

    /// The file object to access the file through
    efd::TiXmlDocument m_kFile;
    /// Has the configuration data in this file been read from the file yet?
    bool m_bConfigurationValid;
    /// Package name
    efd::utf8string m_kPackageName;
    /// Iteration count
    efd::UInt32 m_uiIteration;
    /// The list of surfaces
    typedef efd::vector<SurfaceData*> SurfaceList;
    SurfaceList m_kSurfaces;
    /// A map of surface names to offsets for the compiled texture streams
    StreamOffsetTable m_kCompiledStreamOffsets;
};

#endif // NITERRAINSURFACEPACKAGEFILEVERSION1_H
