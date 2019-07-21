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
#ifndef EE_ECR_SERVICE_ALLOCATOR_H
#define EE_ECR_SERVICE_ALLOCATOR_H

#include <efd/ServiceManager.h>
#include <ecr/ecrLibType.h>

namespace ecr
{
    /// Define bit flags to modify service allocations in the Create() function
    enum RuntimeServiceAllocatorFlags
    {
        /// Use this flag to skip creation of the pick service
        rsaf_NO_PICK_SERVICE = 0x1,
        /// Use this flag to disable rapid iteration for texture files
        rsaf_NO_RAPID_ITERATION = 0x2
    };

    /**
        Create the common core runtime services needed by most applications. If you use a fairly
        standard configuration you can simply call this method to create, configure and
        register the services.

        This function always creates the following services: ecr::RenderService,
        ecr::SceneGraphService, ecr::CameraService and ecr::LightService.

        In addition, unless disabled by passing the flags defined in RuntimeServiceAllocatorFlags,
        the ecr::PickService and ecr::TextureRapidIterationService services are created.

        @param pServiceManager The ServiceManager to which the services are registered
        @param flags Flags from the RuntimeServiceAllocatorFlags enum to change default behavior
    */
    EE_ECR_ENTRY efd::Bool CreateRuntimeServices(
        efd::ServiceManager* pServiceManager,
        efd::UInt32 flags = 0);

} // end namespace ecr

#endif // EE_ECR_SERVICE_ALLOCATOR_H
