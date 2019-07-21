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

#ifndef NiTerrainSectorFileVersion3_H
#define NiTerrainSectorFileVersion3_H

#include "NiTerrainLibType.h"
#include "NiTerrainSectorFileVersion5.h"
#include "NiIndex.h"

/** 
    The class is used to iterate over and write terrain sector files.
 */
class NITERRAIN_ENTRY NiTerrainSectorFileVersion3 : public NiTerrainSectorFileVersion5
{
    friend class NiTerrainSectorFileVersion5;

public:
        
    /**
        Destructor
    */
    virtual ~NiTerrainSectorFileVersion3();

    /**
        Read in the next block of information from the file
        This version performs the old method of getting the next block, and 
        uses the ObjectSize in the old fashion (object size being the length of
        an object per vertex) the new definition is the size of each field
        in the file, as it should be for endian aware files.

        @note Can only be called on a file opened for read access

        @return True if the next block was successfully read. 
    */
    virtual bool NextBlock();

    /**
        Get the data for a particular stream of information in the current
        block. This function is overridden from the parent to specifically
        handle the old methods for storing blend masks. It will also supply
        an empty stream for the low detail texture (generally the low detail
        texture will be regenerated under scene designer anyway).

        @note Can only be called on a readable file

        @param kStreamID The ID of the stream to set the data for.
        @param uiDataLength A reference to a variable to place the length of 
            the stream in.

        @return A pointer to the data stored in the stream.
    */
    virtual void* GetStreamData(StreamType kStreamID, NiUInt32& uiDataLength);

protected:
    
    /**
        Constructor for this sector file iterator

        @param pcSectorFile the sector file to attempt to open
        @param kAccessMode a member of NiFile::OpenMode (either read or write)
    */
    NiTerrainSectorFileVersion3(
        const char* pcSectorFile,
        efd::File::OpenMode kAccessMode);

    /**
        Initialize this file reading parser. This function will also attempt
        to open the blend mask files from previous versions and adjust it.

        @return true if successful
    */
    virtual bool Initialize();

    /**
        Function used to load a block header from an old version of the file
        format. This basically skips over the values that were stored for
        the sum of all points as bounding information.

        @param[out] kBlockHeader the block header to load
        @param[out] kStream the loaded binary stream
    */
    void LoadLegacyBlockHeaderBinary(BlockHeader& kBlockHeader, 
        NiBinaryStream& kStream);

    /**
        Use this function to resize an old blend mask image so that it may
        be split into individual textures for the new format.

        @param pucOriginalPixels the original pixels
        @param uiOriginalWidth The original image size
        @param uiNewWidth The new image size
        @return Pointer to the first new pixel
    */
    NiUInt8* ResizeImage(NiUInt8* pucOriginalPixels, NiUInt32 uiOriginalWidth, 
        NiUInt32 uiNewWidth);

    /**
        Use this function to generate a blend mask for a particular block
        of the terrain in the new format. 

        @param[out] pucDestination the resulting buffer
        @param uiMaskWidth the width of the blend mask
        @param pucSource the buffer data is generated from
        @param kLocation index location of the resulting buffer
        @param uiOriginalWidth the size of the original buffer
    */
    void GenerateCellBlendMask(NiUInt8* pucDestination, NiUInt32 uiMaskWidth,  
        NiUInt8* pucSource, NiIndex kLocation, NiUInt32 uiOriginalWidth);

    /// A static array of values to return in place of a low detail texture.
    NiUInt8 m_auiDefaultLowDetailTexture[64];

    /// A static array of values to return in place of a surface index stream
    NiInt32 m_aiCurrentSurfaceIndexStream[4];

    /// Store the reduced mask pixels to generate the individual block
    /// blend masks in a straightforward way.
    NiUInt8* m_pucReducedOriginalBlendMask;

    /// Store the mask width of the original blend mask
    NiUInt32 m_uiOriginalMaskWidth;

    /// Store the current block's generated blend mask stream here
    NiUInt8* m_pucCurrentBlockBlendMask;

    /// Store the mask width of the new blend mask
    NiUInt32 m_uiCellMaskWidth;

    /// Store the block ID of the beginning of the 'leaf' nodes
    NiUInt32 m_uiHighDetailLeafOffset;

    /// Store the number of levels of detail stored in this sector
    NiUInt32 m_uiNumLOD;

    /**
        Flips values of a texture loaded at the given stream number.
        Fliping happens along the Y axis

        @param uiStreamNumber the index of the texture stream to flip
        @param kCurrentStreamHeader the header for the stream to flip.
    */
    virtual void FlipTextureBuffer(NiUInt32 uiStreamNumber, 
        DataStreamHeader kCurrentStreamHeader);
};

#endif