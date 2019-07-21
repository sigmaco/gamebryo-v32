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
#ifndef NITERRAINSECTORFILEVERSION1_H
#define NITERRAINSECTORFILEVERSION1_H

#include "NiTerrainLibType.h"
#include "NiTerrainSectorFileVersion2.h"

/**
    The class is used to iterate over and write terrain sector files.
 */
class NITERRAIN_ENTRY NiTerrainSectorFileVersion1 : 
    public NiTerrainSectorFileVersion2
{
    friend class NiTerrainSectorFileVersion5;

public:

    /**
        Destructor
    */
    virtual ~NiTerrainSectorFileVersion1();

    /**
        Read in the next block of information from the file

        @note Can only be called on a file opened for read access

        @return True if the next block was successfully read.
    */
    virtual bool NextBlock();

    /**
        Jump to the [iChildID]th child of the current block

        @note Can only be called on a file opened for read access
        @note Can be useful for jumping to a specific level of detail region
            of the file

        @param iChildID the ID of the block to jump to
        @return True if the block was successfully read, false otherwise.
    */
    virtual bool PushBlock(NiInt32 iChildID);

    /**
        Jump to the parent of the current block

        @note Can only be called on a file opened for read access

        @note Using this function after reading a LOD region of the file
            (i.e. sequentially reading more than the 4 children of the parent
            block) will cause any further GetBlockID calls to return
            incorrect information

        @return True if the block was successfully read.
    */
    virtual bool PopBlock();

protected:    

    /// Array that keeps child offsets
    NiUInt32 m_auiChildOffsetsX[4];
    NiUInt32 m_auiChildOffsetsY[4];


    /// The number of blocks in the file
    NiUInt32 m_uiNumBlocks;

    /// Pointer to block ids offsets for each lod
    NiUInt32* m_puiLODOffsets;

    /// Look up table
    NiUInt32* m_puiLookUpTable;

    /**
        Constructor for this sector file iterator

        @param pcSectorFile the sector file to attempt to open
        @param kAccessMode a member of efd::File::OpenMode (either read or write)
    */
    NiTerrainSectorFileVersion1(
        const char* pcSectorFile,
        efd::File::OpenMode kAccessMode);

    /**
        Initialize the class by opening the file and reading the first couple
        of headers.

        @return true if the class was successfully initialized.
    */
    virtual bool Initialize();

    /**
        This function creates the look up table that will associate the new
        version block ID with IDs in the old version of the file. It calls
        on the recursive function AddBlockToLookUp.

        @param uiNewBlockID the new ID to asscociate with and old ID
    */
    void CreateHierarchyLookUpTable(NiUInt32 uiNewBlockID);

    /**
        Recursive function that parses the block hierarchy and works out the
        old ID corresponding to the given uiNewBlockID.

        @param uiNewBlockID The ID of the block being added
        @param uiCurrentLOD the lod that block belongs to
        @param uiBlockX the X index of the block
        @param uiBlockY the Y index of the block
    */
    void AddBlockToLookUp(NiUInt32 uiNewBlockID, NiUInt32 uiCurrentLOD,
        NiUInt32 uiBlockX, NiUInt32 uiBlockY);

    /**
        Function that calls the parent NextBlock() function.
        @return true if successful
    */
    bool OldNextBlock();

    /**
        Function that calls the parent OldPopBlock() function.
        @return true if successful
    */
    bool OldPopBlock();

    /**
        Function that calls the parent OldPushBlock() function.

        @param uiLOD the lod to push the block for
        @return true if successful
    */
    bool OldPushBlock(NiUInt32 uiLOD);

    /**
        This function converts the given uiBlockID to the appropriate ID in the
        file. It then calls OldNextBlock to find the block we want to read.

        @param uiBlockID the ID to be converted
    */
    void ReadFromBlockIDConverted(NiUInt32 uiBlockID);
};

NiSmartPointer(NiTerrainSectorFileVersion1);

#endif
