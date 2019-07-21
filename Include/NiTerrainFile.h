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

#ifndef NITERRAINFILE_H
#define NITERRAINFILE_H

#include <efdXML/tinyxml.h>
#include <NiBoxBV.h>

#include "NiTerrainLibType.h"
#include "NiTerrainAssetReference.h"

/** 
    The class is used to iterate over and write terrain sector files.
 */
class NITERRAIN_ENTRY NiTerrainFile : public NiRefObject
{
public:

    /// Version type for storing the file version
    typedef NiUInt32 FileVersion;

    /**
        Create a NiTerrainFile object capable of traversing the 
        data stored in the given file. 

        @param pcArchivePath The archive path of the terrain
        @param bWriteAccess set to true if we are going to output to a file. 
            can only read OR write at once, not both. 

        @return A pointer to the opened file. The pointer is null if the file could not be opened
    */
    static NiTerrainFile *Open(const char* pcArchivePath, bool bWriteAccess = false);

    /**
        This function must be called on all successfully opened files to signal that the file
        is no longer used. Some save files may use this function as a point at which to flush the 
        data to disk.
    */
    virtual void Close();

    /// Destructor.
    virtual ~NiTerrainFile();

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
        Read the configuration of the terrain

        @param uiSectorSize the size of the sector in verts
        @param uiNumLOD the number of LOD on the stored terrain
        @param uiMaskSize the size of blend masks per sector
        @param uiLowDetailSize the size of low detail diffuse textures per sector
        @param fMinElevation the minimum elevation of the terrain
        @param fMaxElevation the maximum elevation of the terrain
        @param fVertexSpacing the spacing between verts of the terrain (XY scaling)
        @param fLowDetailSpecularPower the specular power of the low detail texture
        @param fLowDetailSpecularIntensity the specular intensity of the low detail texture
        @param uiSurfaceCount the total number of surfaces in the terrain's surface index
        @return true when reading was successful
    */
    virtual bool ReadConfiguration(efd::UInt32& uiSectorSize, efd::UInt32& uiNumLOD, 
        efd::UInt32& uiMaskSize, efd::UInt32& uiLowDetailSize, float& fMinElevation, 
        float& fMaxElevation, float& fVertexSpacing, float& fLowDetailSpecularPower, 
        float& fLowDetailSpecularIntensity, efd::UInt32& uiSurfaceCount);

    /**
        Write the configuration of the terrain

        @param uiSectorSize the size of the sector in verts
        @param uiNumLOD the number of LOD on the stored terrain
        @param uiMaskSize the size of blend masks per sector
        @param uiLowDetailSize the size of low detail diffuse textures per sector
        @param fMinElevation the minimum elevation of the terrain
        @param fMaxElevation the maximum elevation of the terrain
        @param fVertexSpacing the spacing between verts of the terrain (XY scaling)
        @param fLowDetailSpecularPower the specular power of the low detail texture
        @param fLowDetailSpecularIntensity the specular intensity of the low detail texture
        @param uiSurfaceCount the total number of surfaces in the terrain's surface index
    */
    virtual void WriteConfiguration(efd::UInt32 uiSectorSize, efd::UInt32 uiNumLOD, 
        efd::UInt32 uiMaskSize, efd::UInt32 uiLowDetailSize, float fMinElevation, 
        float fMaxElevation, float fVertexSpacing, float fLowDetailSpecularPower, 
        float fLowDetailSpecularIntensity, efd::UInt32 uiSurfaceCount);

    /**
        Read the data related to a particular surface index

        @param uiSurfaceIndex the index of the surface we are interested in
        @param pkPackageRef A pointer to an reference object to receive the package details
        @param kSurfaceID A unique surface ID inside the given package
        @param uiIteration The iteration of the package when the terrain was saved
        @return True when successful
    */
    virtual bool ReadSurface(NiUInt32 uiSurfaceIndex, NiTerrainAssetReference* pkPackageRef, 
        NiFixedString& kSurfaceID, efd::UInt32& uiIteration);

    /**
        Write the data related to a particular surface index

        @param uiSurfaceIndex the index of the surface we are interested in
        @param pkPackageRef A pointer to a reference object that holds the package details
        @param kSurfaceID A unique surface ID inside the given package
        @param uiIteration The iteration of the package being referenced
    */
    virtual void WriteSurface(NiUInt32 uiSurfaceIndex, NiTerrainAssetReference* pkPackageRef, 
        NiFixedString kSurfaceID, efd::UInt32 uiIteration);

protected:

    /**
        Constructor for this terrain file iterator.

        @param pcTerrainArchive the file path where to attempt to open the file.
        @param bWriteAccess Whether to write to the file or not.
    */
    NiTerrainFile(const char* pcTerrainArchive, bool bWriteAccess);

    /**
        Initialize the class by opening the file and reading the first couple
        of headers. 

        @return true if the class was successfully initialized.
    */
    virtual bool Initialize();

    /// The file version this class is capable of reading/writing
    /// File version where this file did not exist
    static const FileVersion ms_kFileVersion0 = FileVersion(0);
    /// File version where this file simply stored a surface index
    static const FileVersion ms_kFileVersion1 = FileVersion(1);
    /// File version where terrain config was added to terrain and surface index was converted
    /// to store data about the surface in the new asset management system
    static const FileVersion ms_kFileVersion2 = FileVersion(2);
    /// File version where references to packages became based on both assetID and file location
    /// and an Iteration value is stored for each reference.
    static const FileVersion ms_kFileVersion3 = FileVersion(3);
    /// Current file version
    static const FileVersion ms_kFileVersion = ms_kFileVersion3;

    // File data:
    NiString m_kTerrainArchive;
    /// The access mode used to open this file
    bool m_bWriteAccess;
    /// This file is ready to be read/written
    bool m_bOpen;

    // Current File Data:
    /// The version of the file being read
    FileVersion m_kFileVersion;
};

NiSmartPointer(NiTerrainFile);

#include "NiTerrainFile.inl"

#endif // NITERRAINFILE_H
