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
#ifndef EE_ENTITYIDFACTORY_H
#define EE_ENTITYIDFACTORY_H

#include "egf/egfLibType.h"
#include <efd/UniversalTypes.h>
#include "EntityID.h"

namespace egf
{

/**
    The standard EntityIDFactory implementation.  Use this static class to generate new EntityIDs

    @note: This class contains ALL static members and methods.  For use be an entire process with
    common data elements.

    @note: This class is intended for use in the main application thread only. It is not
    reentrant and should not be used from multiple threads. Use in multiple threads is
    undefined.
*/
class EE_EGF_ENTRY EntityIDFactory
{
public:
    /**
        Init the static class members up to the last ID that was generated.  This will generally
        happen through some sort of initializing phase involving querying the database for the
        last known ID used.

        @param shardID The value that should be placed inside the shard bit pattern for generated
            EntityIDs
        @param netID The value that should be placed inside the net bit pattern for generated
            EntityIDs
        @param baseID The last known Base ID value.  Each new generated EntityID will increment
            this value by 1.
        @return bool true if all input values are within valid ranges, false otherwise.
    */
    static bool InitIDFactory(efd::UInt32 shardID, efd::UInt32 netID, efd::UInt64 baseID);

    /**
        Init the static class members up to the last ID that was generated.  This will generally
        happen through some sort of initializing phase involving querying the database for the
        last known ID used.

        @param entityIDValue The full GUID value of the last EntityID.
        @return bool true if entityIDValue value is within a valid range, false otherwise.
    */
    static bool InitIDFactory(EntityID entityIDValue);

    /**
        Re-init the ID Factory with a new NetID. This should happen when a network connection is
        established or re-established. The baseID is not reset and will continue to increment from
        the previous value.
        @param netID The value that should be placed inside the net bit pattern for generated
        EntityIDs
        @return bool true if netID value is within a valid range, false otherwise.
    */
    static bool ReinitIDFactory(efd::UInt32 netID);

    /**
        Fetch the next EntityID

        @return EntityID The next EntityID, or zero if the ID range has overflowed.
    */
    static EntityID GetNextID();

private:
    /// Storage for root of the EntityID
    static EntityID ms_rootID;
    /// Storage for base of the EntityID
    static efd::UInt64 ms_baseID;
};

} // end namespace egf

#endif // EE_ENTITYIDFACTORY_H
