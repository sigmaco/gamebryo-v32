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
#ifndef EE_CAMERASERVICE_H
#define EE_CAMERASERVICE_H

#include <egf/Entity.h>
#include <egf/EntityID.h>
#include <efd/MessageHandlerBase.h>
#include <efd/ISystemService.h>
#include <efd/StreamMessage.h>
#include <egf/EntityChangeMessage.h>
#include <ecr/ecrSystemServiceIDs.h>

#include "ecrLibType.h"

#include "CameraData.h"
#include "RenderSurface.h"

#include "RenderService.h"

namespace ecr
{

/**
    The CameraService handles registration and runtime update of entities that mix in the Camera
    model. Internally, it creates and manages NiCamera objects that can be used by the Gamebryo
    renderers. The CameraService handles correct initialization and update of these NiCamera
    objects using the various properties in the Camera model.

    The CameraService also listens for entity update messages and refreshes the internal NiCamera
    objects as the properties on entities change.
*/
class EE_ECR_ENTRY CameraService : public efd::ISystemService, public ecr::IRenderServiceDelegate
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS2(CameraService, efd::kCLASSID_CameraService, efd::ISystemService,
        ecr::IRenderServiceDelegate);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond
public:

    /**
        Default constructor.
    */
    CameraService();

    /**
        Returns the display name, CameraService.
    */
    virtual const char* GetDisplayName() const;

    /**
        Performs pre-init operations including retrieving pointers to other necessary service
        and registering for necessary messages.
    */
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);

    /**
        Performs initial updates on registered cameras. The initial update reads the relevant
        property values from the Camera model and sets them to the underlying NiCamera object.
    */
    virtual efd::AsyncResult OnInit();

    /**
        Iterates over registered cameras and calls NiCamera::Update on each with the current
        game time.
    */
    virtual efd::AsyncResult OnTick();

    /**
        Shuts down by unsubscribing to messages and releasing references to all camera
        entities.
    */
    virtual efd::AsyncResult OnShutdown();

    /**
        Creates a camera with the given entity ID.
        @param id The id for the camera.
        @param pRenderTarget Render target group used to calculate the viewport and
            frustum values for the newly created camera.
        @return The newly created NiCamera object.
    */
    NiCamera* CreateCamera(const egf::EntityID id, NiRenderTargetGroup* pRenderTarget);

    /**
        Create a camera from an existing camera and using the given entity ID.

        This method is intended for registering cameras in pre-existing scene graphs (NIF files)
        that belong to a Mesh model entity. In practice, an application can wait for the
        scene graph's entity, get the camera using scene graph access functions provided by
        the ecr::SceneGraphService, and register the camera for use with this method.

        @param pExistingCamera An NiCamera node that came from some other source. It is stored
            but not otherwise modified.
        @param id The entity ID for an entity that could be considered as owning this camera. It
            must be unique (only on camera per entity) and we recommend using the scene graph
            entity where possible.
    */
    virtual void CreateCamera(
        NiCamera* pExistingCamera,
        const egf::EntityID id);

    /**
        Set the camera by ID for a given window handle.
        @param windowHandle Window reference for the camera to target. This reference is
            resolved internally to an ecr::RenderSurface object.
        @param id ID of the camera to set.
    */
    void SetCamera(NiWindowRef windowHandle, const egf::EntityID& id);

    /**
        Get the active camera for a given RenderSurface object.
        @param pSurface The surface for which the camera is active.
        @return The active camera.
    */
    CameraData* GetActiveCamera(RenderSurface* pSurface);

    /**
        Set a camera to be the new active scene camera. This method updates the NiShadowManager
        class as well with the new active camera as the scene camera.
        @param id Entity id of the camera to set as active.
        @param window Reference to the window that the camera targets.
    */
    void SetActiveCamera(egf::EntityID id, efd::WindowRef window);

    /**
        This message handler is called when a new entity is discovered. The
        entity is inspected for the Camera model. If found, the entity is registered
        with the Camera service.
        @param pMessage The entity message.
        @param targetChannel The category on which the message arrived.
    */
    void HandleEntityDiscoverMessage(const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    /**
        This message handler is called when an entity is has been removed from the
        entity manager. The camera service removes any references to the entity if any
        are held.
        @param pMessage The entity message.
        @param targetChannel The category on which the message arrived.
    */
    void HandleEntityRemovedMessage(const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    /**
        This message handler is called when properties of an entity change. If the
        referenced entity is registerd with the camera service, the internal NiCamera object
        is updated with any potentially new values from the entity's properties.
        @param pMessage The entity message.
        @param targetChannel The category on which the message arrived.
    */
    void HandleEntityUpdatedMessage(const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);


    /// @name Camera Control Helper Methods
    //@{
    /**
        Returns a point that results from starting at the inputPoint and moving dZ units in
        the positive x direction relative to the rotation matrix provided in the inputRotation
        argument.
    */
    static NiPoint3 Dolly(
        const float dZ,
        const NiPoint3& inputPoint,
        const NiMatrix3& inputRotation);

    /**
        Returns a matrix that results from starting with a rotation matrix of inputRotation
        and "looking" dX units in the z direction, and dY units in the y direction, with the
        directions relative to the inputRotation argument.

        The resulting look vector is converted to a rotation matrix that obeys the up vector
        argument.

        This function is useful if you supply a camera's rotation and mouse movement deltas
        into the arguments. The resulting rotation will be the camera's new rotation after
        looking up and to the right in screen space.
    */
    static NiMatrix3 Look(
        const float dX,
        const float dY,
        const NiMatrix3& inputRotation,
        const NiPoint3& up);

    /**
        Returns a point that results from starting at the inputPoint and moving dX in the
        negative z direction and dY in the y direction, with the directions relative to the
        rotation passed into the function in the inputRotation argument.
    */

    static NiPoint3 Pan(
        const float dX,
        const float dY,
        const NiPoint3& inputPoint,
        const NiMatrix3& inputRotation);

    /**
        You supply an object's location and rotation with inputPoint and inputRotation,
        respectively, and you get a new position and rotation of the object as if it was
        orbiting around the center point.

        The new rotation will obey the up vector argument. The dX and dY arguments tell how
        far perpendicular and towards the provided up-axis to go. The return values are stored
        in the returnPoint and returnRotation function arguments.
    */
    static void Orbit(
        const float dX,
        const float dY,
        const NiPoint3& inputPoint,
        const NiMatrix3& inputRotation,
        const NiPoint3& center,
        const NiPoint3& up,
        NiPoint3& returnPoint,
        NiMatrix3& returnRotation);

    /**
        Returns a new NiFrustum that has the same parameters as inputFrustum, but with the right,
        left, top, and bottom parameters reduced by the same amount proportional to the dZ
        argument.
    */
    static NiFrustum OrthoZoom(const float dZ, const NiFrustum& inputFrustum);

    /// Returns a rotation matrix that is constructed using the vector from the source point
    /// to the focus point that obeys the up vector.
    static NiMatrix3 LookAt(const NiPoint3& focus, const NiPoint3& source, const NiPoint3& up);

    /**
        Returns a point to which you could move a camera such that it could see the entire
        focus bound in its frustum if the cameras frustum was equal to the argument frustum
        and was rotated with the currentRotation matrix.
    */
    static NiPoint3 PanTo(
        const NiBound& focus,
        const NiMatrix3& currentRotation,
        const NiFrustum& frustum);

    /**
        This function is intended to turn a mouse cursor location in pixels into a world space ray.

        The x and y arguments are the pixel location of the cursor, coming from the top left of
        the camera's view frustum. The appWidth and appHeight arguments provide the pixel width
        and pixel height of that the frustum covers. The pCamera argument provides the camera from
        which to cast the ray. The origin and direction arguments store the return values for
        the resulting ray.
    */
    static void MouseToRay(
        const float x,
        const float y,
        const unsigned int appWidth,
        const unsigned int appHeight,
        const NiCamera* pCamera, NiPoint3& origin,
        NiPoint3& direction);

    /**
        Returns a point on the line defined by the point startingPoint and vector axis that is
        closest to the line defined by the point inputOrigin and vector inputDirection.
    */
    static NiPoint3 TranslateOnAxis(
        const NiPoint3& startingPoint,
        const NiPoint3& axis,
        const NiPoint3& inputOrigin,
        const NiPoint3& inputDirection);

    /**
        Returns a point on the plane defined by the point startingPoint and the normal vector
        normal that is the intersection with the line defined by the point inputOrigin and
        vector inputDirection.
    */
    static NiPoint3 TranslateOnPlane(
        const NiPoint3& startingPoint,
        const NiPoint3& normal,
        const NiPoint3& inputOrigin,
        const NiPoint3& inputDirection);

    /**
        Returns a radian indicating an amount of rotation about the axis.

        The startingPoint is the center point of the rotation, and the axis argument is
        the rotation axis. The rotation is expressed in terms of number of radians around
        the axis starting from the tangent direction and moving towards the biTangent direction.
        Both the tangent and bitangent arguments should be perpendicular to each other and the
        rotation axis.

        The inputOrigin and inputDirection arguments specify a line. The specified line is
        projected onto the plane defined by the starting point and rotation axis. The returned
        rotation is the rotation of the resulting vector from the tangent argument.
    */
    static float RotateAboutAxis(
        const NiPoint3& startingPoint,
        const NiPoint3& axis,
        const NiPoint3& tangent,
        const NiPoint3& biTangent,
        const NiPoint3& inputOrigin,
        const NiPoint3& inputDirection);
    //@}

    /**
        Overridden from IRenderServiceDelegate to remove the camera from the active list.
    */
    virtual void OnSurfaceRemoved(RenderService* pService, RenderSurface* pSurface);

protected:

    static const float ms_kParallelThreshold;
    static const float ms_kInvParallelThreshold;
    static float ms_kOrthoZoomSpeed;

    /**
    */
    virtual ~CameraService();

    /**
        Looks up the reflector service and registers for entity discovery,
        entity property change, and entity removal messages. These messages are
        used to manage the underlying animations associated with a given
        entity.
        @return True if successful, false otherwise.
        @remark The initialization process calls this method. If this method
            fails, the service initialization is pending until it succeeds.
    */
    void RegisterForEntityMessages();

    void UpdateCamera(CameraData* pCamera, egf::Entity* pEntity);


    /**
        Creates a default camera. The default camera is used to render the
        scene to its parent render surface unless overridden.
        @param pRenderTarget The render target group that the camera is bound
        to.
        @return A default camera positioned at (0,0,0) with the up axis as +z
        looking down the +y axis.
    */
    NiCamera* CreateDefaultCamera(NiRenderTargetGroup* pRenderTarget);

    efd::MessageService* m_pMessageService;
    egf::EntityManager* m_pEntityManager;
    RenderServicePtr m_spRenderService;

    // 1-1 correspondence of entities to cameras.
    typedef efd::map<egf::EntityID, CameraDataPtr> EntityCameraMap;
    EntityCameraMap m_entityCameraMap;
    // n-1 correspondence of surfaces to entities
    typedef efd::map<efd::WindowRef, egf::EntityID> WindowEntityMap;
    WindowEntityMap m_activeCameraIds;
};

typedef efd::SmartPointer<CameraService> CameraServicePtr;

} // end namespace ecr

#include "CameraService.inl"

#endif // EE_CAMERASERVICE_H
