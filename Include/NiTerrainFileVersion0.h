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

#ifndef NITERRAINFILEVERSION0_H
#define NITERRAINFILEVERSION0_H

#include <NiBoxBV.h>

#include "NiTerrainLibType.h"
#include "NiTerrainFileVersion1.h"

/** 
    The class is used to iterate over and write terrain sector files.
 */
class NITERRAIN_ENTRY NiTerrainFileVersion0 : public NiTerrainFileVersion1
{
    friend class NiTerrainFile;

public:

    /// Destructor.
    virtual ~NiTerrainFileVersion0();

protected:

    /**
        Constructor for this terrain file iterator

        @param pcFileName the terrain file to attempt to open
        @param bWriteAccess whether the file should be read of written
    */
    NiTerrainFileVersion0(const char* pcFileName, bool bWriteAccess);

    /**
        Initialize the class by opening the file and reading the first couple
        of headers. 

        @return true if the class was successfully initialized.
    */
    virtual bool Initialize();

    /**
        Read the list of surfaces from a section of a DOM document.

        @param pkDocument Pointer to the XML document to read
        @return true when read is successful
    */
    bool ReadSurfaceIndex(const efd::TiXmlElement* pkDocument);
};

NiSmartPointer(NiTerrainFileVersion0);

#endif // NITERRAINFILEVERSION0_H
