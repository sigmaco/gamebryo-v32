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

#ifndef TIMEOFDAYFILEVERSION1_H
#define TIMEOFDAYFILEVERSION1_H

#include "ecr/ecrClassIDs.h"
#include "egmTerrainLibType.h"
#include "TimeOfDayFile.h"

// foreward declaration:
namespace efd
{
    class TiXmlDocument;
};

namespace egmTerrain
{

/**
    Class that defines how to read and write from and to a time of day file
*/
class EE_EGMTERRAIN_ENTRY TimeOfDayFileVersion1 : public TimeOfDayFile
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(TimeOfDayFileVersion1, efd::kCLASSID_TimeOfDayFileVersion1, 
        egmTerrain::TimeOfDayFile);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

public:
    /**
        Constructor for this time of day file iterator

        @param pFileName the time of day file to attempt to open
        @param writeAccess Marks whether to read or write the file
    */
    TimeOfDayFileVersion1(const char* pFileName, bool writeAccess);

protected:
    /**
        Read the list of keyframes from a section of a DOM document.
    */
    virtual bool ReadPropertySet(const efd::TiXmlElement* pRootElement);

};

/// Defines a smart pointer (reference counted) for the TimeOfDayFile class
typedef efd::SmartPointer<TimeOfDayFileVersion1> TimeOfDayFileVersion1Ptr;

}

#endif
