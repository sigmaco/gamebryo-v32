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
#ifndef EE_THIRDPERSONROTATINGCAMERA_H
#define EE_THIRDPERSONROTATINGCAMERA_H

#include "TargetedCamera.h"


namespace ecrInput
{
// forward declaration
class InputActionMessage;
class InputStickMessage;
} // end namespace ecrInput

namespace egmSample
{
// forward declaration
class EntityCameraService;

/**
    ThirdPersonRotatingCamera class - gameplay camera

    This camera has the concept of a camera "subject" on which it is focused, making it a
    third-person camera.  It follows as the subject moves.  The input stick rotates the
    camera around the subject and moves closer and farther away.  Control events are
    automatically installed with the control service; while this is easier to use, it's
    a bit less flexible than using Lua scripts like the TargetedCamera.

    The camera has a single subject entity at any given time.  The camera translates toward
    and away from the subject along a rail that is calculated at runtime.  The shape of the rail
    is determined by a hinge on the horizon (tunable) such that, normally, the top edge of the
    camera's field of view is aligned with hinge regardless of the distance from the camera to
    the subject.  The rail has a near-subject camera stop point that sets the minimum distance
    from the camera to the subject.  The camera stop point exists on a ring that is a given
    height (tunable) above the subject's ground point and a given distance (tunable) from the
    subject's vertical center line.  The rail has a far-subject camera stop point that is
    determined by the maximum camera-hinge-subject angle (tunable).

    Regardless of translation the camera always rotates towards a focus point that is a given
    height (tunable) above the subject's ground point.  Having a focus point separate from the
    near-subject camera stop point allows some variety in the close-in perspective:

    * When the focus point and near-subject camera stop point are the same, the camera
      appears to simply zoom into the subject along the rail with the horizon locked at
      the hinge.  That is, the hinge will appear to be fixed on the screen and no terrain
      beyond the hinge will be visible.

    * When the focus point is above the near-subject camera stop point, the horizon appears
      to flare up gradually as the camera gets closer to the subject and the camera will be
      pointed upwards when it hits the camera stop point.

    * When the focus point is below the near-subject camera stop point, the horizon appears to
      close in as the camera gets closer to the subject and the camera will be pointed
      downwards when it hits the camera stop point.

    In order for a camera to properly view an entity the entity's model must mix in the
    SparkCameraSubject model and provide values for the properties defined in that model.
 */
class EE_EGMSAMPLE_ENTRY ThirdPersonRotatingCamera : public TargetedCamera
{
    /// @cond EMERGENT_INTERNAL

    EE_DECLARE_CLASS1(
        ThirdPersonRotatingCamera,
        efd::kCLASSID_ThirdPersonRotatingCamera,
        TargetedCamera);

    // Note: I must declare all properties here, even those also declared in my base class.
    EE_DECLARE_BUILTINMODEL_PROPERTIES
        EE_BUILTINMODELPROPERTY_ACCESSOR(
            ThirdPersonRotatingCamera,
            egf::kPropertyID_SamplesModelLibrary_IsCameraActive,
            efd::Bool,
            ICameraImpl,
            GetIsCameraActive,
            SetIsCameraActive)

        EE_BUILTINMODELPROPERTY_ACCESSOR_REF(
            ThirdPersonRotatingCamera,
            egf::kPropertyID_SamplesModelLibrary_CameraSubject,
            egf::EntityID,
            ICameraImpl,
            GetCameraSubject,
            SetCameraSubject)

        EE_BUILTINMODELPROPERTY(
            ThirdPersonRotatingCamera,
            egf::kPropertyID_SamplesModelLibrary_HorizonRadius,
            efd::Float32,
            ThirdPersonRotatingCamera,
            m_horizonRadius)

        EE_BUILTINMODELPROPERTY(
            ThirdPersonRotatingCamera,
            egf::kPropertyID_SamplesModelLibrary_AltitudeLimit,
            efd::Float32,
            ThirdPersonRotatingCamera,
            m_altitudeLimit)

        EE_BUILTINMODELPROPERTY(
            ThirdPersonRotatingCamera,
            egf::kPropertyID_SamplesModelLibrary_DefaultDistanceFromStop,
            efd::Float32,
            ThirdPersonRotatingCamera,
            m_defaultDistanceFromStop)
    EE_END_BUILTINMODEL_PROPERTIES
    /// @endcond

public:

    /// @name Construction and Destruction
    //@{
    ThirdPersonRotatingCamera();
    virtual ~ThirdPersonRotatingCamera();
    //@}

    /**
        Get the current horizon radius.  The horizon radius determines the distance to the horizon
        hinge from the camera's current position.  The horizon hinge will be tangent to the circle
        defined by this radius intersecting at the center of the camera's current field of view.
    */
    efd::Float32 GetHorizonRadius() const;

    /**
        Set the current horizon radius.  The horizon radius determines the distance to the horizon
        hinge from the camera's current position.  The horizon hinge will be tangent to the circle
        defined by this radius intersecting at the center of the camera's current field of view.

        @param horizonRadius The new horizon radius.
    */
    void SetHorizonRadius(efd::Float32 horizonRadius);

    /**
        Get the current altitude limit.  The altitude limit is the maximum camera-hinge-subject
        angle, in degrees.  You can use this to tune the maximum camera-subject distance.  (Or,
        the maximum camera-ground distance.)
    */
    efd::Float32 GetAltitudeLimit() const;

    /**
        Set the current altitude limit.  The altitude limit is the maximum camera-hinge-subject
        angle, in degrees.  You can use this to tune the maximum camera-subject distance.  (Or,
        the maximum camera-ground distance.)

        @param altitudeLimit The new altitude limit.
    */
    void SetAltitudeLimit(efd::Float32 altitudeLimit);

    /**
        Get the default distance from stop.  This is the initial distance from the camera to the
        subject's camera stop point when a camera acquires a new subject.
    */
    efd::Float32 GetDefaultDistanceFromStop() const;

    /// Get the camera's Field of View.
    efd::Float32 GetFOV() const;

    /**
        Get the focus height adjustment to use with the current camera subject.  The focus
        height adjustment determines the height of the camera's focus above the subject's
        ground point along the vertical centerline.

        @param defaultValue Value to return if there is no value set on the entity
    */
    inline efd::Float32 GetSubjectCameraFocusHeightAdjust(efd::Float32 defaultValue) const;

    /**
        Get the focus horizontal adjustment to use with the current camera subject.  This
        adjustment determines the left-right offset of the camera's focus from the subject's
        vertical centerline. Positive values offset to the right.

        @param defaultValue Value to return if there is no value set on the entity
    */
    inline efd::Float32 GetSubjectCameraFocusHorizAdjust(efd::Float32 defaultValue) const;

    /**
        Get the camera stop offset adjustment to use with the current camera subject. This
        value determines the height of the camera stop point ring above the subject's ground
        point along the vertical centerline.

        @param defaultValue Value to return if there is no value set on the Entity
    */
    inline efd::Float32 GetSubjectCameraStopHeightAdjust(efd::Float32 defaultValue) const;

    /**
        Get the camera stop offset adjustment.  This value determines the radius of the camera
        stop point ring around the subject's vertical centerline.

        @param defaultValue Value to return if there is no value set on the Entity
    */
    inline efd::Float32 GetSubjectCameraStopOffsetAdjust(efd::Float32 defaultValue) const;

    /// @cond EMERGENT_INTERNAL

    static egf::IBuiltinModel* Factory();

    virtual void HandleCameraButtonActions(
        const ecrInput::InputActionMessage* pMessage,
        efd::Category);
    virtual void HandleCameraStickActions(
        const ecrInput::InputStickMessage* pMessage,
        efd::Category);

    /// @endcond

    /// @name built-in model property storage
    //@{
    efd::Float32 m_horizonRadius;
    efd::Float32 m_altitudeLimit;
    efd::Float32 m_defaultDistanceFromStop;
    //@}

protected:

    // Base-class overrides not documented here
    virtual void OnTick();

    virtual void InstallControlServiceCallbacks();
    virtual void UninstallControlServiceCallbacks();

    /// Values used in the user data for my button actions to quickly tell forward, backward,
    /// left, and right apart.
    enum CameraMovementType
    {
        CMT_Normal          = 1,
        CMT_Inverted        = 2,

        CMT_Longitudinal    = 4,
        CMT_Lateral         = 8,
    };

    // Minimum distance from camera to subject's camera stop offset.
    // (Should be greater than 0.0f)
    static const efd::Float32 kMinDistCO;
    static const efd::Float32 kDefaultHeightAdjust;
    static const efd::Float32 kHorizontalOrbitMultiplier;

    /// @name Subject info.
    //@{
    NiAVObject* m_niAvObject;
    efd::Point3 m_subjectCurrentPos;
    efd::Point3 m_subjectPreviousPos;
    efd::Float32 m_subjectRadius;
    efd::Float32 m_subjectCameraFocusHeightAdjust;
    efd::Float32 m_subjectCameraFocusHorizAdjust;
    efd::Float32 m_subjectCameraStopHeightAdjust;
    efd::Float32 m_subjectCameraStopOffsetAdjust;
    //@}

    /// camera to offset distance
    efd::Float32 m_distCO;
    /// offset to camera-ground distance (calculated)
    efd::Float32 m_distOG;
    /// camera to camera-ground distance (calculated)
    efd::Float32 m_distCG;
    /// camera is within min camera to offset distance zone
    efd::Bool m_isInMinDistCOZone;
    /// camera is within max camera to offset distance zone
    efd::Bool m_isInMaxDistCOZone;

    /// The category on which we listen for actions
    efd::Category m_inputCategory;

    /// Called during OnTick whenever the CameraSubject is different than the last tick
    efd::Bool InitializeForNewSubject();

    /// @name Camera Movement Helpers
    //@{
    void MoveCameraByHingedHorizonOrbit(efd::Float32 speedX, efd::Float32 speedY);
    efd::Float32 ApplyCurveFilter(efd::Float32 input) const;

    /**
        Calculates offset to camera-ground (OG) distance and camera to camera-ground (CG)
        distance.

        @param horizonRadius Distance to the viewable horizon
        @param cameraFOV Field of view of the camera
        @param altLimit Limit of altitude
        @param distCO Distance from camera to object
        @param distOG Distance from object to ground
        @param distCG Distance from camera to ground
        @return true if computation was successful (all results within limits)
    */
    efd::Bool CalculateHingedHorizonOrbitLegs(
        efd::Float32 horizonRadius,
        efd::Float32 cameraFOV,
        efd::Float32 altLimit,
        efd::Float32 distCO,
        efd::Float32& distOG,
        efd::Float32& distCG);
    //@}
};
typedef efd::SmartPointer<ThirdPersonRotatingCamera> ThirdPersonRotatingCameraPtr;

} // end namespace egmSample

#include "ThirdPersonRotatingCamera.inl"

#endif // EE_THIRDPERSONROTATINGCAMERA_H
