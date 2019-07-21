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
#ifndef NITERRAINSECTORFILE_H
#define NITERRAINSECTORFILE_H

#include <NiBoxBV.h>
#include <NiPixelData.h>

#include "NiTerrainLibType.h"
#include "NiTerrainPhysXTypes.h"
#include "NiTerrainSector.h"

/**
    A class to abstract the storage of sector data to the disk. By overloading this class
    different file formats can be introduced.
 */
class NITERRAIN_ENTRY NiTerrainSectorFile : public NiRefObject
{
public:
    /// Version type for storing the file version
    typedef NiUInt32 FileVersion;

    /// Enum to identify different data items stored in the file
    struct DataField
    {
        enum Value
        {
            /// Configuration file block
            CONFIG              = 0x0001,
            /// Heghtmap for the sector
            HEIGHTS             = 0x0002,
            /// Normal data for the sector
            NORMALS             = 0x0004,
            /// Tangent data for the sector
            TANGENTS            = 0x0008,
            /// The sector's blend mask
            BLEND_MASK          = 0x0010,
            /// The sector's low detail normal map
            LOWDETAIL_NORMALS   = 0x0020,
            /// The sector's low detail diffuse map
            LOWDETAIL_DIFFUSE   = 0x0040,
            /// The sector's bounds
            BOUNDS              = 0x0080,
            /// The surface index map
            SURFACE_INDEXES     = 0x0100,
            /// The terrain's material information
            PHYSXMATERIAL_DATA  = 0x0200,
            /// The sector's PhysX data
            PHYSX_DATA          = 0x0400
        };
    };

    /// Structure to store cell bounding information
    struct CellData
    {
        /// Spherical bound for the cell
        NiBound m_kBound;
        /// Box bounding volume for the cell
        NiBoxBV m_kBox;
    };

    /// Structure to store leaf surface information
    struct LeafData
    {
        /// Number of surfaces on this leaf
        efd::UInt32 m_uiNumSurfaces;
        /// Indexes of surfaces used on this leaf
        efd::UInt32 m_auiSurfaceIndex[NiTerrainCellLeaf::MAX_NUM_SURFACES];
    };

    /**
        Create a NiTerrainSectorFile object capable of traversing the
        data stored in the given file.

        @param pcTerrainArchive the path to a sector file to open for iteration
        @param iSectorX the X index of the sector to open
        @param iSectorY the Y index of the sector to open
        @param bWriteAccess set to true if we are going to output to a file.
            can only read OR write at once, not both.

        @return a pointer to the opened sector file. This is null if opening failed
    */
    static NiTerrainSectorFile *Open(const char* pcTerrainArchive, NiInt32 iSectorX, 
        NiInt32 iSectorY, bool bWriteAccess = false);

    /// Destructor.
    virtual ~NiTerrainSectorFile();

    /**
        @return the version of the file being written/read.
    */
    virtual FileVersion GetFileVersion() const = 0;

    /**
        @return true if file is ready to be written/read.
    */
    virtual bool IsReady() const;

    /**
        @return true if the file has been opened for write access.
    */
    virtual bool IsWritable() const;

    /**
        Initialize the file by opening files, reading the first bit of data, or checking for
        access to mandatory files. This function is usually called immediately after instantiation
        of the object.
        NOTE: This function is for internal use only and under most cicumstances should not be
        called by a user.
        @return true if the class was successfully initialized.
    */
    virtual bool Initialize();

    /**
        Close the file, this function causes any unfinished files to be completed and closed off.
        Every file must have this function called on it if it was successfully opened.
    */
    virtual void Close();

    /**
        @return the file version of the file currently being manipulated
    */
    virtual FileVersion GetCurrentVersion();

    /**
        Return the set of files that are relevant to this format

        @param kFilePaths A set to populate with the list of filepaths that this file spans.
    */
    virtual void GetFilePaths(efd::set<efd::utf8string>& kFilePaths) = 0;

    /**
        Request certain data to be pre-cached. This function must be called with the data that
        will be required before any read operations may be performed. 

        @note Whilst a data field may be requested, it may not be available in this file. Use
        the IsDataReady function to determine if the data is available after calling precache.

        @param uiBeginLevel The first LOD level that the user wants data from
        @param uiEndLevel The last LOD level that the user wants data from
        @param uiData A set of flags denoting what data fields are required to be loaded.
        @return true if successful
    */
    virtual bool Precache(efd::UInt32 uiBeginLevel, efd::UInt32 uiEndLevel, efd::UInt32 uiData);

    /**
        Query the file to see if a certain data field is available to be read. In order for this
        function to return true, the relevant data field must have been pre-cached successfully in
        a previous call to Precache. 

        @param eDataField The data field to test for. 
        @return whether the requested data is ready
    */
    virtual bool IsDataReady(DataField::Value eDataField);

    /**
        Read the sector configuration from the file. 

        @param uiSectorWidthInVerts A reference to an integer that will receive the width of a 
            sector in verts according to this file.
        @param uiNumLOD A reference to an integer that will receive the number of LOD stored in 
            this sector.
        @return true if the data was successfully read
    */
    virtual bool ReadSectorConfig(efd::UInt32& uiSectorWidthInVerts, efd::UInt32& uiNumLOD);

    /**
        Write the sector configuration to the file

        @param uiSectorWidthInVerts The width of the sector in verts
        @param uiNumLOD The number of LOD stored in the sector
    */
    virtual void WriteSectorConfig(efd::UInt32 uiSectorWidthInVerts, efd::UInt32 uiNumLOD);

    /**
        Read the sector's height map from file into the supplied buffer.
        
        @param pusHeights The height map buffer to read the data into
        @param uiDataLength The number of elements stored in the buffer. 
            (Must be equal to sectorWidth * sectorWidth)
        @return true if the data was successfully read
    */
    virtual bool ReadHeights(efd::UInt16* pusHeights, efd::UInt32 uiDataLength);

    /**
        Write the sector's height map to the file from the supplied buffer.

        @param pusHeights The height map buffer
        @param uiDataLength The number of elements stored in the buffer.
            (Must be equal to sectorWidth * sectorWidth)
    */  
    virtual void WriteHeights(efd::UInt16* pusHeights, efd::UInt32 uiDataLength);
    
    /**
        Read the sector's normals from the file into the specified buffer. 
        The normals are compressed by not storing the Z value.
        (calculate Z based on what it needs to be to make the normal a unit vector)

        @param pkNormals The normal buffer
        @param uiDataLength the number of elements stored in the buffer
        @return true if the data was successfully read
    */
    virtual bool ReadNormals(efd::Point2* pkNormals, efd::UInt32 uiDataLength);

    /**
        Write the sector's normals to the file from the specified buffer
        The normals are compressed by not storing the Z value. 
        (calculate Z based on what it needs to be to make the normal a unit vector)

        @param pkNormals The normal buffer
        @param uiDataLength the number of elements stored in the buffer
    */
    virtual void WriteNormals(efd::Point2* pkNormals, efd::UInt32 uiDataLength);

    /**
        Read the sector's tangents from the file into the specified buffer. 
        The tangents are compressed by not storing the Y value (assumed 0).

        @param pkTangents The normal buffer
        @param uiDataLength the number of elements stored in the buffer
        @return true if the data was successfully read
    */
    virtual bool ReadTangents(efd::Point2* pkTangents, efd::UInt32 uiDataLength);

    /**
        Write the sector's tangents to the file from the specified buffer. 
        The tangents are compressed by not storing the Y value (assumed 0).

        @param pkTangents The tangent buffer
        @param uiDataLength the number of elements stored in the buffer
    */
    virtual void WriteTangents(efd::Point2* pkTangents, efd::UInt32 uiDataLength);

    /**
        Read the sector's blend mask from the file

        @param pkBlendMask the pointer to return the blend mask into.
        @return true if the data was successfully read.
    */
    virtual bool ReadBlendMask(NiPixelData*& pkBlendMask);
    
    /**
        Write the sector's blend mask to the file. 

        @param pkBlendMask The blend mask 
    */
    virtual void WriteBlendMask(NiPixelData* pkBlendMask);

    /**
        Read the sector's low detail diffuse map from the file

        @param pkLowDetailDiffuse the pointer to return the map into.
        @return true if the data was successfully read.
    */
    virtual bool ReadLowDetailDiffuseMap(NiPixelData*& pkLowDetailDiffuse);

    /**
        Write the sector's low detail diffuse map to the file. 

        @param pkLowDetailDiffuse The low detail diffuse map
    */
    virtual void WriteLowDetailDiffuseMap(NiPixelData* pkLowDetailDiffuse);

    /**
        Read the sector's low detail normal map from the file

        @param pkLowDetailNormal the pointer to return the map into.
        @return true if the data was successfully read.
    */
    virtual bool ReadLowDetailNormalMap(NiPixelData*& pkLowDetailNormal);

    /**
        Write the sector's low detail normal map to the file. 

        @param pkLowDetailNormal The low detail normal map
    */
    virtual void WriteLowDetailNormalMap(NiPixelData* pkLowDetailNormal);

    /**
        Read the surface index of a range of leaf cells from the file. 
        
        @param uiCellRegionID The first leaf to read into the buffer
        @param uiNumCells The number of cells to read 
        @param pkLeafData The buffer to read the data into (must be allocated)
        @return true if the data was successfully read.
    */
    virtual bool ReadCellSurfaceIndex(efd::UInt32 uiCellRegionID, efd::UInt32 uiNumCells, 
        LeafData* pkLeafData);

    /**
        Write the surface index of a range of leaf cells to the file. 

        @param uiCellRegionID The first leaf to write to the file
        @param uiNumCells The number of cells to write 
        @param pkLeafData The buffer to write the data from
    */
    virtual void WriteCellSurfaceIndex(efd::UInt32 uiCellRegionID, efd::UInt32 uiNumCells, 
        LeafData* pkLeafData);
    
    /**
        Read the bounding information of a range of cells from the file. 

        @param uiCellRegionID The first cell to read into the buffer
        @param uiNumCells The number of cells to read 
        @param pkCellData The buffer to read the data into (must be allocated)
        @return true if the data was successfully read.
    */
    virtual bool ReadCellBoundData(efd::UInt32 uiCellRegionID, efd::UInt32 uiNumCells, 
        CellData* pkCellData);

    /**
        Write the bounding information of a range of cells to the file. 

        @param uiCellRegionID The first cell to write to the file
        @param uiNumCells The number of cells to write 
        @param pkCellData The buffer to write the data from
    */
    virtual void WriteCellBoundData(efd::UInt32 uiCellRegionID, efd::UInt32 uiNumCells, 
        CellData* pkCellData);

    /**
        Reads in the physx data for the sector.
        
        @param kMaterialMap The material data we are going to return
        @param pkSampleData The physx data for each sector samples that we are going to return. This
            parameter should not yet be allocated
        @return true if the data was successfully read.
    */
    virtual bool ReadTerrainSectorPhysXData(
        efd::map<efd::UInt32, NiPhysXMaterialMetaData>& kMaterialMap, 
        NiTerrainSectorPhysXData*& pkSampleData);

    /**
        Writes in the physx data for the sector.

        @param kMaterialMap The material data we are going to write
        @param pkSampleData The physx data for each sector samples that we are going to write.
            This should not be null.
    */
    virtual void WriteTerrainSectorPhysXData(
        efd::map<efd::UInt32, NiPhysXMaterialMetaData> kMaterialMap, 
        NiTerrainSectorPhysXData* pkSampleData);
 
protected:

    /**
        Constructor for this sector file iterator

        @param pcTerrainArchive the terrain path to attempt to open from
        @param iSectorX the X index of the sector to open
        @param iSectorY the Y index of the sector to open
        @param kAccessMode a member of efd::File::OpenMode (either read or write)
    */
    NiTerrainSectorFile(const char* pcTerrainArchive, NiInt32 iSectorX, NiInt32 iSectorY, 
        efd::File::OpenMode kAccessMode);

    /// The file version this class is capable of reading/writing
    // V1: Files with deprecated LoD hierarchy:
    static const FileVersion ms_kFileVersion1 = FileVersion(1); 
    // V2: Files without the number of lod in the header
    static const FileVersion ms_kFileVersion2 = FileVersion(2);
    // V3: Files with deprecated material system
    static const FileVersion ms_kFileVersion3 = FileVersion(3);
    // V4: SPECIAL 2.6 OVERLAY with new material system but without the 
    // number of lod in header
    static const FileVersion ms_kFileVersion4 = FileVersion(4);
    // V5: Files with New material system and lod in header
    static const FileVersion ms_kFileVersion5 = FileVersion(5);
    // V6: Files with the new streaming loading system
    static const FileVersion ms_kFileVersion6 = FileVersion(6);
    // Current version
    static const FileVersion ms_kFileVersion = ms_kFileVersion6;

    /// Is the file open or closed?
    bool m_bOpen;
    /// The access mode to manipulate the file
    efd::File::OpenMode m_kAccessMode;
    /// The terrain archive to use when generating filenames
    NiString m_kTerrainArchive;
    /// The sector's X coordinate
    efd::SInt32 m_iSectorX;
    /// The sector's Y coordinate
    efd::SInt32 m_iSectorY;
    /// The set of flags identifying what data has been cached
    efd::UInt32 m_eCachedData;
};

NiSmartPointer(NiTerrainSectorFile);

#include "NiTerrainSectorFile.inl"

#endif // NITERRAINSECTORFILE_H
