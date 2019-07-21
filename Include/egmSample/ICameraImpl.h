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
#ifndef EE_ICAMERAIMPL_H
#define EE_ICAMERAIMPL_H

#include <efd/ISystemService.h>
#include <egf/Entity.h>
#include "egmSampleLibType.h"
#include "egfDemoSystemServiceIDs.h"
#include "SamplesModelLibraryPropertyIDs.h"

#include <egf/BuiltinModelHelper.h>
#include <egf/Entity.h>
#include <ecr/CameraService.h>
#include <ecr/RenderService.h>

#include "ICamera.h"

namespace egmSample
{
// forward declaration
class EntityCameraService;

/**
    A base implementation of most of the functionality of the ICamera interface.
    Instantiating this implementation would actually give you a fully functional
    camera, but there would be no way to move it around except by setting its
    Position and Rotation properties directly.
*/
class EE_EGMSAMPLE_ENTRY ICameraImpl
    : public egf::IBuiltinModelImpl
    , public ICamera
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS2(ICameraImpl, efd::kCLASSID_ICameraImpl, egf::IBuiltinModelImpl, ICamera);
    /// @endcond
public:

    ///@name Construction and Destruction
    //@{
    ICameraImpl();
    virtual ~ICameraImpl();
    //@}

    // Functionality inherited from parents not documented here
    virtual void OnTick();
    virtual efd::Bool Activate();
    virtual efd::Bool Deactivate();

    efd::Point3 GetPosition() const;
    void SetPosition(const efd::Point3& position);
    efd::Point3 GetRotation() const;
    void SetRotation(const efd::Point3& rotation);
    void SetLongitudinalMovement(efd::Float32 magnitude);
    void SetLateralMovement(efd::Float32 magnitude);
    void SetVerticalMovement(efd::Float32 magnitude);
    void SetMovement(const efd::Point3& movement);

    /// @name Built-in model property accessors
    //@{
    efd::Bool GetIsCameraActive() const;
    void SetIsCameraActive(const efd::Bool& active);

    const egf::EntityID& GetCameraSubject() const;
    void SetCameraSubject(const egf::EntityID& target);
    //@}

protected:
    // We override the ICamera method to return the IBuiltinModelImpl owning entity pointer.
    virtual egf::Entity* GetAssociatedEntity() const;

    virtual void InstallControlServiceCallbacks();
    virtual void UninstallControlServiceCallbacks();

    virtual void OnAdded();
    virtual void OnRemoved();

    /// Helper to cache the subject entity pointer.  Only call this when the owner entity is
    /// added to the EntityManager (after our OnAdded is called and before our OnRemoved).
    /// @return true if the subject entity was found
    bool CacheSubjectEntity();

    /// Helper for setting the m_pCameraData to look at a specific point
    void LookAt(const efd::Point3& focusPos,
        const efd::Point3& cameraPos,
        const efd::Point3& upAxis);

    /// The "IsCameraActive" property
    efd::Bool m_bIsActive;
    /// The "CameraSubject" property
    egf::EntityID m_CameraSubject;
    /// True if CameraSubject has changed since the last OnTick
    efd::Bool m_hasNewSubject;
    /// A cached pointer to the subject entity
    egf::EntityPtr m_spSubjectEntity;

    ecr::CameraData* m_pCameraData;
    egmSample::EntityCameraService* m_pEntityCameraService;

    // movement direction as indicated by the most recent
    // SetLongitudinalMovement/SetLateralMovement calls
    efd::Point3 m_moveDir;

    /*
        Allow a "dead zone" around the center of the joystick when controlling the player character.
    */
    static const efd::Float32 kDeadZone;
    static const efd::Float32 kCameraSpeed;

    // Time of last OnTick call
    efd::TimeType m_lastElapsedTime;
};

typedef efd::SmartPointer<ICameraImpl> ICameraImplPtr;

} // end namespace egmSample

#endif // EE_ICAMERAIMPL_H
