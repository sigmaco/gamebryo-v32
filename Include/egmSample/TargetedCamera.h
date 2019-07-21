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
#ifndef EE_SIMPLECAMERA_H
#define EE_SIMPLECAMERA_H

#include <efd/ISystemService.h>
#include <egf/Entity.h>

#include <egf/BuiltinModelHelper.h>
#include <egf/Entity.h>
#include <ecr/CameraService.h>
#include <ecr/RenderService.h>

#include "ICameraImpl.h"
#include "SamplesModelLibraryPropertyIDs.h"


namespace egmSample
{

// forward declaration
class EntityCameraService;

/*
    TargetedCamera is a camera that does respect movement settings, but does not subscribe to any
    particular control events to set them.  That means that Lua or C++ code will need to pass
    along input events to get it to move around.  There is an TargetedCamera builtin model that
    implements Lua scripts to tie this camera to the input analog stick.  This camera will look
    at the camera subject entity.
*/
class EE_EGMSAMPLE_ENTRY TargetedCamera
    : public ICameraImpl
{
    /// @cond EMERGENT_INTERNAL

    EE_DECLARE_CLASS1(
        TargetedCamera,
        efd::kCLASSID_TargetedCamera,
        ICameraImpl);
    EE_DECLARE_CONCRETE_REFCOUNT;

    EE_DECLARE_BUILTINMODEL_PROPERTIES
        EE_BUILTINMODELPROPERTY_ACCESSOR(
            TargetedCamera,
            egf::kPropertyID_SamplesModelLibrary_IsCameraActive,
            efd::Bool,
            ICameraImpl,
            GetIsCameraActive,
            SetIsCameraActive)

        EE_BUILTINMODELPROPERTY_ACCESSOR_REF(
            TargetedCamera,
            egf::kPropertyID_SamplesModelLibrary_CameraSubject,
            egf::EntityID,
            ICameraImpl,
            GetCameraSubject,
            SetCameraSubject)
    EE_END_BUILTINMODEL_PROPERTIES
    /// @endcond

public:

    ///@name Construction and Destruction
    //@{
    TargetedCamera();
    virtual ~TargetedCamera();
    //@}

    // Overridden virtual functions inherit base documentation and are not documented here.
    virtual void OnTick();
    virtual void OnEndLifecycle(efd::UInt32 lifecycle);

    /// Get the camera subject's position.
    virtual efd::Point3 GetSubjectPosition() const;

    /// Get the camera subject's rotation.
    virtual efd::Point3 GetSubjectRotation() const;

    /**
        TargetedCamera factory function.  This will be passed to the game framework to allow it
        to instantiate instances of our builtin model.
    */
    static egf::IBuiltinModel* Factory();

    /**
        Constant indicating the camera speed in units/sec
    */
    static const efd::Float32 kCameraSpeed;
};
typedef efd::SmartPointer<TargetedCamera> SimpleCameraPtr;

} // end namespace egmSample

#endif // EE_SIMPLECAMERA_H
