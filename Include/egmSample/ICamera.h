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
#ifndef EE_ICAMERA_H
#define EE_ICAMERA_H

#include <efd/ISystemService.h>
#include <egf/Entity.h>
#include "egfDemoSystemServiceIDs.h"

#include <egf/BuiltinModelHelper.h>
#include <egf/Entity.h>
#include <ecr/CameraService.h>
#include <ecr/RenderService.h>

namespace egmSample
{
// forward declaration
class EntityCameraService;

/**
    ICamera is an abstract interface class used to define a camera.  Specific camera
    implementations will derive from this so that they can be manipulated by the
    EntityCameraService.
*/
class ICamera : public efd::IBase
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_INTERFACE1(ICamera, efd::kCLASSID_ICamera, efd::IBase);
    /// @endcond
public:

    /// Constructor
    virtual ~ICamera() {}

    /// Process movement and other time-based phenomena.  Called by EntityCameraService.
    virtual void OnTick() = 0;

    /**
        Activate this camera

        @return true on success, false on failure.
    */
    virtual efd::Bool Activate() = 0;


    /**
        Deactivate this camera

        @return true on success, false on failure.
    */
    virtual efd::Bool Deactivate() = 0;

    /// Get the camera's position
    virtual efd::Point3 GetPosition() const = 0;

    /// Set the camera's position
    virtual void SetPosition(const efd::Point3& position) = 0;

    /// Get the camera's rotation
    virtual efd::Point3 GetRotation() const = 0;

    /**
        Set the camera's rotation
    */
    virtual void SetRotation(const efd::Point3& rotation) = 0;

    /**
        Set longitudinal movement parameters on the camera

        @param magnitude Longitudinal movement parameters.  Typically magnitude will vary from
                      -1.0 to 1.0 depending on the position of an input analog stick.  Setting
                      this to 1.0 will move the camera forward (relative to itself).  -1.0 will
                      move the camera backward.
    */
    virtual void SetLongitudinalMovement(efd::Float32 magnitude) = 0;

    /**
        Set lateral movement parameters on the camera

        @param magnitude Lateral movement parameters.  Typically magnitude will vary from
                      -1.0 to 1.0 depending on the position of an input analog stick.  Setting
                      this to 1.0 will move the camera left (relative to itself).  -1.0 will
                      move the camera right.
    */
    virtual void SetLateralMovement(efd::Float32 magnitude) = 0;

    /**
        Set vertical movement parameters on the camera

        @param magnitude Vertical movement parameters.  Typically magnitude will vary from
                      -1.0 to 1.0 depending on the position of an input analog stick.  Setting
                      this to 1.0 will move the camera up (relative to itself).  -1.0 will
                      move the camera down.
    */
    virtual void SetVerticalMovement(efd::Float32 magnitude) = 0;

    /**
        Set all movement parameters on the camera simultaneously.  This is equivalent to calling
        SetLongitudinalMovement, SetLateralMovement, and SetVerticalMovement sequentially.

        @param movement Movement parameters to set.
    */
    virtual void SetMovement(const efd::Point3& movement) = 0;

    /**
        Get the Entity associated with this camera.

        @return Entity pointer or NULL.
    */
    virtual egf::Entity* GetAssociatedEntity() const = 0;

protected:
    virtual void InstallControlServiceCallbacks() = 0;
    virtual void UninstallControlServiceCallbacks() = 0;
};

typedef efd::SmartPointer<ICamera> ICameraPtr;

} // end namespace egmSample

#endif // EE_ICAMERA_H
