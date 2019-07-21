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
#ifndef EE_EGF_SERVICE_ALLOCATOR_H
#define EE_EGF_SERVICE_ALLOCATOR_H

#include <efd/ServiceManager.h>
#include <egf/egfLibType.h>

namespace egf
{
    /// Define bit flags to modify service allocations in the Create() function
    enum GameServiceAllocatorFlags
    {
        /// Use this flag to skip creation of the EntityManager. If you use this then it is assumed
        /// that you will registered your own EntityManager derived class.
        gsaf_USE_CUSTOM_ENTITY_MANAGER = 0x1,

        /// Use this flag to skip creation of rapid iteration support services
        gsaf_NO_RAPID_ITERATION = 0x2,
    };

    /**
        Create the common Game Framework services needed by most applications. If you use a fairly
        standard configuration you can simply call this method to create, configure and
        register the services.

        This function always creates the following services: egf::FlatModelManager,
        egf::EntityLoaderService, egf::Scheduler and egf::NotificationService.

        In addition, unless disabled by passing the flags defined in GameServiceAllocatorFlags,
        the egf::EntityManager and egf::RapidIterationSystemService services are created.

        @param pServiceManager The ServiceManager to which the services are registered
        @param flags Flags from the GameServiceAllocatorFlags enum to change default behavior
    */
    EE_EGF_ENTRY efd::Bool CreateGameServices(
        efd::ServiceManager* pServiceManager,
        efd::UInt32 flags = 0);

} // end namespace egf

#endif // EE_EGF_SERVICE_ALLOCATOR_H
