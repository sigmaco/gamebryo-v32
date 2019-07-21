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
#ifndef EE_EGFPHYSX_SERVICE_ALLOCATOR_H
#define EE_EGFPHYSX_SERVICE_ALLOCATOR_H

#include <efd/ServiceManager.h>
#include <egfPhysX/egfPhysXLibType.h>

namespace egfPhysX
{
    /// Define bit flags to modify service allocations in the Create() function
    enum PhysXServiceAllocatorFlags
    {
    };

    /**
        Create the common PhysX services needed by most applications. If you use a fairly
        standard configuration you can simply call this method to create, configure and
        register the services.

        This function always creates the following services:
            - egfPhysX::SceneService
            - egfPhysX::TriggerService.

        @param pServiceManager The ServiceManager to which the services are registered
        @param flags Flags from the PhysXServiceAllocatorFlags enum to change default behavior
    */
    EE_EGFPHYSX_ENTRY efd::Bool CreatePhysXServices(
        efd::ServiceManager* pServiceManager,
        efd::UInt32 flags = 0);

} // end namespace egfPhysX

#endif // EE_EGFPHYSX_SERVICE_ALLOCATOR_H
