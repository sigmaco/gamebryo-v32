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
#ifndef NITERRAINSECTORFILEVERSION6_H
#define NITERRAINSECTORFILEVERSION6_H

#include "NiTerrainSectorFile.h"

/**
    This version of the sector file is the first to implement the new streaming interface. 
    Its main goal is to minimize the amount of data that is required to be stored on disk.
 */
class NITERRAIN_ENTRY NiTerrainSectorFileVersion6 : public NiTerrainSectorFile
{
    friend class NiTerrainSectorFile;
public:

    /**
        Detect the version of the file requested
        
        @param pcTerrainArchive the path to a sector file to open for iteration
        @param iSectorX the X index of the sector to open
        @param iSectorY the Y index of the sector to open

        @return the file version of the file
    */
    static FileVersion DetectFileVersion(const char* pcTerrainArchive, NiInt32 iSectorX, 
        NiInt32 iSectorY);

    /// Destructor.
    virtual ~NiTerrainSectorFileVersion6();

    /// @see NiTerrainSectorFile
    /// @{
    virtual FileVersion GetFileVersion() const;
    virtual void Close();
    virtual FileVersion GetCurrentVersion();
    virtual void GetFilePaths(efd::set<efd::utf8string>& kFilePaths);
    virtual bool Precache(efd::UInt32 uiBeginLevel, efd::UInt32 uiEndLevel, efd::UInt32 uiData);
    virtual bool ReadSectorConfig(efd::UInt32& uiSectorWidthInVerts, efd::UInt32& uiNumLOD);
    virtual void WriteSectorConfig(efd::UInt32 uiSectorWidthInVerts, efd::UInt32 uiNumLOD);
    virtual bool ReadHeights(efd::UInt16* pusHeights, efd::UInt32 uiDataLength);
    virtual void WriteHeights(efd::UInt16* pusHeights, efd::UInt32 uiDataLength);
    virtual bool ReadNormals(efd::Point2* pkNormals, efd::UInt32 uiDataLength);
    virtual void WriteNormals(efd::Point2* pkNormals, efd::UInt32 uiDataLength);
    virtual bool ReadTangents(efd::Point2* pkTangents, efd::UInt32 uiDataLength);
    virtual void WriteTangents(efd::Point2* pkTangents, efd::UInt32 uiDataLength);
    virtual bool ReadBlendMask(NiPixelData*& pkBlendMask);
    virtual void WriteBlendMask(NiPixelData* pkBlendMask);
    virtual bool ReadLowDetailDiffuseMap(NiPixelData*& pkLowDetailDiffuse);
    virtual void WriteLowDetailDiffuseMap(NiPixelData* pkLowDetailDiffuse);
    virtual bool ReadLowDetailNormalMap(NiPixelData*& pkLowDetailNormal);
    virtual void WriteLowDetailNormalMap(NiPixelData* pkLowDetailNormal);
    virtual bool ReadCellSurfaceIndex(efd::UInt32 uiCellRegionID, efd::UInt32 uiNumCells, 
        LeafData* pkLeafData);
    virtual void WriteCellSurfaceIndex(efd::UInt32 uiCellRegionID, efd::UInt32 uiNumCells, 
        LeafData* pkLeafData);
    virtual bool ReadCellBoundData(efd::UInt32 uiCellRegionID, efd::UInt32 uiNumCells, 
        CellData* pkCellData);
    virtual void WriteCellBoundData(efd::UInt32 uiCellRegionID, efd::UInt32 uiNumCells, 
        CellData* pkCellData);
    virtual bool ReadTerrainSectorPhysXData(
        efd::map<efd::UInt32, NiPhysXMaterialMetaData>& kMaterialMap, 
        NiTerrainSectorPhysXData*& pkSampleData);
    virtual void WriteTerrainSectorPhysXData(
        efd::map<efd::UInt32, NiPhysXMaterialMetaData> kMaterialMap, 
        NiTerrainSectorPhysXData* pkSampleData);
    /// @}
 
protected:

    /**
        Constructor for this sector file iterator

        @param pcTerrainArchive the terrain path to attempt to open from
        @param iSectorX the X index of the sector to open
        @param iSectorY the Y index of the sector to open
        @param kAccessMode a member of efd::File::OpenMode (either read or write)
    */
    NiTerrainSectorFileVersion6(const char* pcTerrainArchive, NiInt32 iSectorX, NiInt32 iSectorY, 
        efd::File::OpenMode kAccessMode);

    struct DataBlockType
    {
        enum VALUE
        {
            CONFIG             = 0,
            HEIGHTS            = 1,
            NORMALS            = 2,
            TANGENTS           = 3,
            BLEND_MASK         = 4,
            LOWDETAIL_NORMALS  = 5,
            LOWDETAIL_DIFFUSE  = 6,
            BOUNDS             = 7,
            SURFACE_INDEXES    = 8,
            PHYSXMATERIAL_DATA = 9,
            PHYSX_DATA         = 10,

            NUM_BLOCK_TYPES
        };
    };

    struct ImageCompressionMode
    {
        enum VALUE
        {
            NONE = 0,
        };
    };

    struct FileHeader
    {
        FileVersion m_kVersion;
        efd::UInt32 m_uiPresentData;
    };

    class DataBlock : public NiMemObject
    {
    public:
        DataBlockType::VALUE m_eBlockType;
        efd::UInt32 m_uiDataLength;
        
        virtual ~DataBlock();
        static bool ReadBlockHeader(efd::BinaryStream& kStream, DataBlock& kBlockHeader);
        virtual bool ReadBlockData(efd::BinaryStream& kStream);
        bool WriteBlockHeader(efd::BinaryStream& kStream);
        virtual bool WriteBlockData(efd::BinaryStream& kStream);
    };
    
    class ConfigDataBlock: public DataBlock
    {
    public:
        efd::UInt32 m_uiSectorWidthInVerts;
        efd::UInt32 m_uiNumLOD;
        
        virtual bool ReadBlockData(efd::BinaryStream& kStream);
        virtual bool WriteBlockData(efd::BinaryStream& kStream);
    };
        
    class ImageDataBlock : public DataBlock
    {
    public:
        efd::UInt32 m_uiWidth;
        efd::UInt32 m_uiHeight;
        efd::UInt16 m_usNumChannels;
        efd::UInt16 m_usBytesPerChannel;
        ImageCompressionMode::VALUE m_eCompressionMode;
        efd::UInt8* m_pucCompressedData;

        static const efd::UInt32 ms_uiStaticDataSize = 4 * sizeof(efd::UInt32);

        ~ImageDataBlock();
        virtual bool ReadBlockData(efd::BinaryStream& kStream);
        virtual bool WriteBlockData(efd::BinaryStream& kStream);

        virtual bool CompressFromStream(ImageCompressionMode::VALUE eCompressionMode,
            efd::UInt8* pucBuffer, efd::UInt32 uiBufferLength, 
            efd::UInt32 uiWidth, efd::UInt32 uiHeight, efd::UInt16 usNumChannels, 
            efd::UInt16 usBytesPerChannel);
        virtual bool CompressFromImageData(ImageCompressionMode::VALUE eCompressionMode, 
            NiPixelData* pkSource);
        virtual bool DecompressToImageData(NiPixelData*& pkSource);
        virtual bool DecompressToStream(efd::UInt8* pucBuffer, efd::UInt32 uiBufferLength);
    
    protected:
        virtual efd::UInt32 CalculateCompressionStride();
    };

    class BoundingDataBlock : public DataBlock
    {
    public:
        efd::UInt32 m_uiNumCells;
        efd::UInt32 m_uiStartCell;
        CellData* m_pkBoundingData;

        static const efd::UInt32 ms_uiCellDataSize = 20 * 4;

        ~BoundingDataBlock();
        virtual bool ReadBlockData(efd::BinaryStream& kStream);
        virtual bool WriteBlockData(efd::BinaryStream& kStream);
    };

    class SurfaceIndexBlock : public DataBlock
    {
    public:
        efd::UInt32 m_uiNumLeaves;
        efd::UInt32 m_uiStartLeaf;
        LeafData* m_pkSurfaceIndexData;

        static const efd::UInt32 ms_uiLeafDataSize = (2 + NiTerrainCellLeaf::MAX_NUM_SURFACES) * 4;

        ~SurfaceIndexBlock();
        virtual bool ReadBlockData(efd::BinaryStream& kStream);
        virtual bool WriteBlockData(efd::BinaryStream& kStream);
    };

    /**
        Class defining a physx material data block for the current sector
    */
    class PhysXMaterialDataBlock : public DataBlock
    {
    public:
        efd::map<efd::UInt32, NiPhysXMaterialMetaData> m_kMaterialData;

        static const efd::UInt32 ms_uiStaticDataSize = sizeof(efd::UInt32) + 3 * sizeof(float);

        ~PhysXMaterialDataBlock();
        virtual bool ReadBlockData(efd::BinaryStream& kStream);
        virtual bool WriteBlockData(efd::BinaryStream& kStream);
    };

    /**
        Class defining a physx data block for the current sector
    */
    class PhysXDataBlock : public DataBlock
    {
    public:
        NiTerrainSectorPhysXData* m_pkPhysXData;

        static const efd::UInt32 ms_uiStaticDataSize = sizeof(efd::UInt16) * 2 + sizeof(bool);

        ~PhysXDataBlock();
        virtual bool ReadBlockData(efd::BinaryStream& kStream);
        virtual bool WriteBlockData(efd::BinaryStream& kStream);
    };

    // Data block pointers:
    DataBlock* m_apkDataBlocks[DataBlockType::NUM_BLOCK_TYPES];

    /**
        Function that reads the file header

        @param kStream stream to read from
        @param[out] kHeader data structure the file header is read to
        @return true
    */
    bool ReadFileHeader(efd::BinaryStream& kStream, FileHeader& kHeader);

    /**
        Function that reads the file into the appropriate data blocks.

        @param kStream stream to read from.
        @param uiBeginLevel the level of detail to start reading at.
        @param uiEndLevel the level of detail to stop redaing at.
        @param uiSelectedData data slected for reading.
        @return true
    */
    bool ReadDataBlocks(efd::BinaryStream& kStream, efd::UInt32 uiBeginLevel, 
        efd::UInt32 uiEndLevel, efd::UInt32 uiSelectedData);

    /**
        Writes all data to the file.

        @return true if successful
    */
    bool WriteFile();

    /**
        Writes the file's header

        @param[out] kStream the stream to write to
        @param kHeader the data structure to write
        @return true if successful
    */
    bool WriteFileHeader(efd::BinaryStream& kStream, FileHeader& kHeader);

    /**
        Writes the file's data content

        @param[out] kStream the stream to write to
        @return true if successful
    */
    bool WriteDataBlocks(efd::BinaryStream& kStream);

    /// @see NiTerrainSectorFile
    virtual bool Initialize();

    /// Generate the filename to use for this sector file
    efd::utf8string GenerateFilename();

    // Filename generation variables
    static const char* ms_pcSectorFilename;
};

#endif // NITERRAINSECTORFILEVERSION6_H
