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
// Emergent Game Technologies, Calabasas, CA 91302
// http://www.emergent.net

#ifndef NITERRAINSECTORFILEVERSION2_H
#define NITERRAINSECTORFILEVERSION2_H

#include "NiTerrainLibType.h"
#include "NiTerrainSectorFileVersion3.h"
#include "NiIndex.h"

/**
    The class is used to iterate over and write terrain sector files.
 */
class NITERRAIN_ENTRY NiTerrainSectorFileVersion2 : public NiTerrainSectorFileVersion3
{
    friend class NiTerrainSectorFileVersion5;

public:

    /**
        Destructor
    */
    virtual ~NiTerrainSectorFileVersion2();

protected:
    /**
        Constructor for this sector file iterator

        @param pcSectorFile the sector file to attempt to open
        @param kAccessMode a member of efd::File::OpenMode (either read or write)
    */
    NiTerrainSectorFileVersion2(const char* pcSectorFile,
        efd::File::OpenMode kAccessMode);

    /**
        Initialize this file reading parser. This function will attempt
        to generate the missing information from the file header
        (NumLOD was added to the file header after this version)

        @return true if successful
    */
    virtual bool Initialize();

    /**
        Function used to load a block header from an old version of the file
        format. This basically skips over the values that were stored for
        the sum of all points as bounding information.

        @param[out] kFileHeader the file header to load
        @param[out] kStream the loaded binary stream
    */
    void LoadLegacyFileHeaderBinary(FileHeader& kFileHeader,
        efd::BinaryStream& kStream);
};

NiSmartPointer(NiTerrainSectorFileVersion2);

#endif
