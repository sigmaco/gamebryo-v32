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
#ifndef NITERRAINSECTORFILEDEVELOPER_H
#define NITERRAINSECTORFILEDEVELOPER_H

#include "NiTerrainLibType.h"
#include "NiTerrainSectorFile.h"
#include "NiTerrainCellLeaf.h"

/**
    The class is used to iterate over and write terrain sector files.
 */
class NITERRAIN_ENTRY NiTerrainSectorFileDeveloper : public NiTerrainSectorFile
{
public:
    /**
        Create a NiTerrainSectorFileDeveloper object capable of traversing the
        data stored for the given sector using the Developer format.

        @param pcTerrainArchive the path to a sector file to open for iteration
        @param iSectorX the X index of the sector to open
        @param iSectorY the Y index of the sector to open
        @param bWriteAccess set to true if we are going to output to a file.
            can only read OR write at once, not both.

        @return a pointer to the opened sector file. This is null if opening failed
    */
    static NiTerrainSectorFile* Open(const char* pcTerrainArchive, NiInt32 iSectorX, 
        NiInt32 iSectorY, bool bWriteAccess = false);

    /// Destructor.
    virtual ~NiTerrainSectorFileDeveloper();

    virtual FileVersion GetFileVersion() const;
    virtual FileVersion GetCurrentVersion();
    virtual void GetFilePaths(efd::set<efd::utf8string>& kFilePaths);

    virtual bool Precache(efd::UInt32 uiBeginLevel, efd::UInt32 uiEndLevel, efd::UInt32 eData);
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

protected:

    /**
        Constructor for this sector file iterator

        @param pcTerrainArchive the path to a sector file to open for iteration
        @param iSectorX the X index of the sector to open
        @param iSectorY the Y index of the sector to open
        @param kAccessMode a member of efd::File::OpenMode (either read or write)
    */
    NiTerrainSectorFileDeveloper(const char* pcTerrainArchive, NiInt32 iSectorX, NiInt32 iSectorY, 
        efd::File::OpenMode kAccessMode);

    /**
        Initialize the class by opening the file and reading the first couple
        of headers.

        @return true if the class was successfully initialized.
    */
    virtual bool Initialize();

    /// Filename generation functions
    NiString GenerateSectorPathPrefix();
    NiString GenerateHeightsFilename();
    NiString GenerateNormalsFilename();
    NiString GenerateTangentsFilename();
    NiString GenerateLowDetailDiffuseMapFilename();
    NiString GenerateLowDetailNormalMapFilename();
    NiString GenerateSectorDataFilename();
    NiString GenerateBoundsFilename();
    NiString GenerateSurfaceIndexFilename();
    NiString GenerateBlendMaskFilename();
    
    /// The file version this class is capable of reading/writing
    // V1: Basic data files stored on disk in a folder:
    static const FileVersion ms_kFileVersion = FileVersion(1); 

    /// Filenames used in this format
    static const char* ms_pcFolder;
    static const char* ms_pcHeightsFile;
    static const char* ms_pcNormalsFile;
    static const char* ms_pcTangentsFile;
    static const char* ms_pcLowDetailDiffuseMapFile;
    static const char* ms_pcLowDetailNormalMapFile;
    static const char* ms_pcSectorDataFile;
    static const char* ms_pcBoundsFile;
    static const char* ms_pcSurfaceIndexFile;
    static const char* ms_pcBlendMaskFile;
};

#include "NiTerrainSectorFileDeveloper.inl"

#endif // NITERRAINSECTORFILEDEVELOPER_H
