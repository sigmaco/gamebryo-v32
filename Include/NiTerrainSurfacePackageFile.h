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
#ifndef NITERRAINSURFACEPACKAGEFILE_H
#define NITERRAINSURFACEPACKAGEFILE_H

#include <NiMemManager.h>
#include <NiRefObject.h>
#include <NiUniversalTypes.h>
#include <efd/utf8string.h>
#include <NiTexture.h>

#include "NiTerrainLibType.h"
#include "NiSurfacePackage.h"
#include "NiTerrainAssetReference.h"
#include "NiMetaData.h"

/**
    This class is used to stream a surface package's data to/from disk. 
    The class provides basic versioning support to allow backwards compatibility with older
    package formats.
*/
class NITERRAIN_ENTRY NiTerrainSurfacePackageFile : public NiRefObject
{
public:
    /// Version type for storing the file version
    typedef NiUInt32 FileVersion;

    /**
        A structure with a list of enumeration values describing discrete data fields that may be 
        loaded from the file.
    */
    struct DataField
    {
        /// The enumeration containing a list of data field type ID's
        enum Value
        {
            /// Indicates all package configuration information and surface/texture information.
            SURFACE_CONFIG = 1,

            /// Indicates the set of pre-compiled textures that have been saved into the format.
            COMPILED_TEXTURES = 2
        };
    };

    /**
        Create a NiTerrainSurfacePackageFile object capable of traversing the 
        data stored in the given file. 

        @param kFilename The filename of the package to open.
        @param bWriteAccess set to true if we are going to output to a file. 
            can only read OR write at once, not both. 

        @return A pointer to the opened file. The pointer is null if the file could not be opened
    */
    static NiTerrainSurfacePackageFile *Open(const efd::utf8string& kFilename, 
        bool bWriteAccess = false);

    /**
        When reading from the file, the first operation to perform upon the class
        is a call to this Precache function to indicate what data should be loaded from disk.

        @param uiDataFields A bitmask combining values from the DataField enumeration.
    */
    virtual void Precache(efd::UInt32 uiDataFields);

    /**
        This function must be called on all successfully opened files to signal that the file
        is no longer used. Some save files may use this function as a point at which to flush the 
        data to disk.
    */
    virtual void Close();

    /// Destructor.
    virtual ~NiTerrainSurfacePackageFile();

    /**
        Return the version of the file being written/read.
    */
    inline FileVersion GetFileVersion() const;

    /**
        @return true if file is ready to be written/read.
    */
    inline bool IsReady() const;

    /**
        @return true if the file has been opened for write access.
    */
    inline bool IsWritable() const;

    /**
        function returning the file version that is currently in use

        @return the Terrain's file version currently in use
    */
    static inline FileVersion GetCurrentVersion();

    /**
        Return the set of files that are relevant to this format

        @param kFilePaths A set to populate with the list of filepaths that this file spans.
    */
    virtual void GetFilePaths(efd::set<efd::utf8string>& kFilePaths) = 0;

    /**
        Read the name of the package from the file

        @param kPackageName The variable to store the package name in.
        @param uiIteration The iteration count of the last save.
        @return false If the package name could not be read.
    */
    virtual bool ReadPackageConfig(efd::utf8string& kPackageName, efd::UInt32& uiIteration);

    /**
        Write the name of the package to the file.

        @param kPackageName The name of the package.
        @param uiIteration The iteration count of the last save.
    */
    virtual void WritePackageConfig(const efd::utf8string& kPackageName, 
        efd::UInt32 uiIteration);

    /**
        Read the number of surfaces from the file.

        @param uiNumSurfaces The variable to store the number of surfaces in
        @return True if the number of surfaces could be determined.
    */
    virtual bool ReadNumSurfaces(efd::UInt32& uiNumSurfaces);

    /**
        Write the number of surfaces to the file

        @param uiNumSurfaces The number of surfaces to be stored in the file.
    */
    virtual void WriteNumSurfaces(const efd::UInt32& uiNumSurfaces);

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
        Write the configuration of a single surface to the file by it's index.

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
    */
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
        Write the reference to a texture asset stored for a particular slot in the material 
        package.

        @param uiSurfaceIndex The index of the surface the user is interested in
        @param uiSlotID The ID of the texture slot the user is interested in
        @param pkReference An asset reference object to write the relevant data from
    */
    virtual void WriteSurfaceSlot(efd::UInt32 uiSurfaceIndex,
        efd::UInt32 uiSlotID,
        const NiTerrainAssetReference* pkReference);

    /**
        Read any metadata that has been assigned to a particular surface

        @param uiSurfaceIndex The index of the surface the user is interested in
        @param kMetaData A metadata object to store the requested information in

        @return True if the data could be read successfully
    */
    virtual bool ReadSurfaceMetadata(efd::UInt32 uiSurfaceIndex,
        NiMetaData& kMetaData);

    /**
        Write a surface's metadata to the file. 

        @param uiSurfaceIndex The index of the surface the user is interested in
        @param kMetaData The metadata object to store inside the file for the surface.
    */
    virtual void WriteSurfaceMetadata(efd::UInt32 uiSurfaceIndex,
        const NiMetaData& kMetaData);

    /**
        Read the compiled textures for a particular surface

        @param uiSurfaceIndex The index of the surface the user is interested in.
        @param aspTextures The texture data.
        @param uiNumTextures The number of textures.
        @return true if the read succeeded.
    */
    virtual bool ReadSurfaceCompiledTextures(efd::UInt32 uiSurfaceIndex,
        NiTexturePtr* aspTextures, efd::UInt32 uiNumTextures);

    /**
        Read the compiled textures for a particular surface

        @param kSurfaceName The name of the surface the user is interested in.
        @param aspTextures The texture data.
        @param uiNumTextures The number of textures.
        @return true if the read succeeded.
    */
    virtual bool ReadSurfaceCompiledTextures(efd::utf8string kSurfaceName, 
        NiTexturePtr* aspTextures, efd::UInt32 uiNumTextures);

    /**
        Write a surface's metadata to the file. 

        @param uiSurfaceIndex The index of the surface the user is interested in.
        @param aspTextures The texture data.
        @param uiNumTextures The number of textures.
    */
    virtual void WriteSurfaceCompiledTextures(efd::UInt32 uiSurfaceIndex,
        NiTexturePtr* aspTextures, efd::UInt32 uiNumTextures);

    

protected:

    /**
        Constructor for this surface package file iterator

        @param kFilename the file path where to attempt to open the file
        @param bWriteAccess Whether to write to the file or not
    */
    NiTerrainSurfacePackageFile(efd::utf8string kFilename, bool bWriteAccess);

    /**
        Initialize the class by opening the file and reading the first couple
        of headers. 

        @return true if the class was successfully initialized.
    */
    virtual bool Initialize();

    /// The file versions this class is capable of reading/writing
    /// File version where this file was at it's most basic without a version number
    static const FileVersion ms_kFileVersion0 = FileVersion(0);
    /// File version where this file was moved into the GameFramework and loaded/saved there
    static const FileVersion ms_kFileVersion1 = FileVersion(1);
    /// File version where this file was moved back to CoreRuntime and includes prebuilt 
    /// textures for it's surfaces.
    static const FileVersion ms_kFileVersion2 = FileVersion(2);
    /// Current file version
    static const FileVersion ms_kFileVersion = ms_kFileVersion1;

    // Filename
    efd::utf8string m_kPackageFilename;
    /// The access mode used to open this file
    bool m_bWriteAccess;
    /// This file is ready to be read/written
    bool m_bOpen;
    /// The version of the file being read
    FileVersion m_kFileVersion;
};
/// Smart pointer typedef
NiSmartPointer(NiTerrainSurfaceLibrary);

#include "NiTerrainSurfacePackageFile.inl"

#endif // NITERRAINSURFACEPACKAGEFILE_H
