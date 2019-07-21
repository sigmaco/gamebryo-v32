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
#ifndef EE_EON_SERVICE_ALLOCATOR_H
#define EE_EON_SERVICE_ALLOCATOR_H

#include <efd/ServiceManager.h>
#include <eon/OnlineEntry.h>

namespace eon
{
    /// Define bit flags to modify service allocations in the Create() function
    enum OnlineServiceAllocatorFlags
    {
    };

    /**
        Create the common Online services needed by most applications. If you use a fairly
        standard configuration you can simply call this method to create, configure and
        register the services.

        This function always creates the following services: eon::OnlineEntityManager and
        eon::ReplicationService.

        @param pServiceManager The ServiceManager to which the services are registered
        @param flags Flags from the OnlineServiceAllocatorFlags enum to change default behavior
    */
    EE_EONENTRY efd::Bool CreateOnlineServices(
        efd::ServiceManager* pServiceManager,
        efd::UInt32 flags = 0);

} // end namespace eon

#endif // EE_EON_SERVICE_ALLOCATOR_H
