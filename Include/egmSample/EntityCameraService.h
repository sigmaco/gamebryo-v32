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
#ifndef EE_ENTITYCAMERASERVICE_H
#define EE_ENTITYCAMERASERVICE_H

#include <efd/ISystemService.h>
#include <egf/Entity.h>
#include <egf/FlatModelManager.h>
#include "egmSampleLibType.h"
#include "egfDemoSystemServiceIDs.h"

#include "ICamera.h"

namespace egmSample
{
typedef efd::map<const efd::utf8string, egmSample::ICamera*> StringCameraMap;
typedef StringCameraMap::iterator StringCameraMap_Iter;

/**
    The EntityCameraService manages camera entities.  Cameras are implemented as built-in models
    and can be instantiated in the block file like any other entities, or are created from C++ code
    at runtime.  The EntityCameraService takes care of updating the active cameras, tracking which
    camera is active, and activating/deactivating cameras.

    @note This is not a replacement for the ecr::CameraService, rather it is an extension that
        support for the various camera built-in model classed.
*/
// DT32284 Clarify and document the differences between this service and ecr::CameraService.
class EE_EGMSAMPLE_ENTRY EntityCameraService : public efd::ISystemService
{
    /// @cond EMERGERNT_INTERNAL

    EE_DECLARE_CLASS1(EntityCameraService, efd::kCLASSID_EntityCameraService, ISystemService);
    EE_DECLARE_CONCRETE_REFCOUNT;

    /// @endcond

public:
    /// @name Construction and Destruction
    //@{
    EntityCameraService();
    virtual ~EntityCameraService();
    //@}

    /**
        Static function to install a new camera type.  If you derive a new camera built-in type
        from ICamera, you will need to call this function EARLY in the startup process to
        register it. The EntityCameraService will use this data to initialize the built-in model
        factory for your camera.

        Note that any cameras on the C++ side must be derived from both ICamera and from
        IBuiltinModelImpl.  See TargetedCamera for an example.  Please make sure to use a unique
        class ID for your class or EE_DYNAMIC_CAST may not work, and if it doesn't work, the
        EntityCameraService will break.

        All cameras must be registered before the EntityCameraService's OnInit() function is
        called. You can call it from your program's main or from a static initializer, or from a
        service OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar) call.

        @param pName Name of the builtin model

        @param flatID ID of the model from the flat file.  Open the flat file and look for the
                    "id=" value.

        @param pfn Pointer to the factory method for your class.
    */
    static void InstallCameraInstance(
        const char *pName,
        egf::FlatModelID flatID,
        egf::FlatModelManager::BuiltinModelFactory::FactoryMethod* pfn);

    // Overridden virtual functions inherit base documentation and are not documented here.
    virtual const char *GetDisplayName() const;
    efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);
    efd::AsyncResult OnInit();
    efd::AsyncResult OnTick();

    /**
        Activate a given camera

        @param entityID Entity ID of the camera to activate

        @return true on success, false on failure.
    */
    virtual efd::Bool ActivateCamera(egf::EntityID entityID);

    /**
        Deactivate a given camera

        @param entityID EntityID of the camera to deactivate

        @return true on success, false on failure.
    */
    virtual efd::Bool DeactivateCamera(egf::EntityID entityID);

    /**
        Get the active camera

        @return The active camera
    */
    virtual egmSample::ICamera* GetActiveCamera();

    /**
        Set longitudinal movement parameters on the camera with the specified EntityID.

        @param entityID ID of the camera
        @param magnitude Longitudinal movement parameters.  Typically magnitude will vary from
            -1.0 to 1.0 depending on the position of an input analog stick.
    */
    void SetLongitudinalMovement(egf::EntityID entityID, efd::Float32 magnitude);

    /**
        Set lateral movement parameters on the camera with the specified EntityID.

        @param entityID ID of the camera
        @param magnitude Lateral movement parameters.  Typically magnitude will vary from
            -1.0 to 1.0 depending on the position of an input analog stick.
    */
    void SetLateralMovement(egf::EntityID entityID, efd::Float32 magnitude);

    /**
        Set vertical movement parameters on the camera with the specified EntityID.

        @param entityID ID of the camera
        @param magnitude Vertical movement parameters.  Typically magnitude will vary from
                      -1.0 to 1.0 depending on the position of an input analog stick.
    */
    void SetVerticalMovement(egf::EntityID entityID, efd::Float32 magnitude);

    /**
        Set the camera subject.  Each camera type has a different way of treating its subject;
        for example, a third-person camera will always focus on the subject, and may follow
        the subject as it moves around.  A first-person camera might also follow the subject,
        but its point of view is that of the subject itself. Some camera types may not have the
        concept of a subject entity, in which case this function does nothing.

        @param entityCamera ID of the camera entity
        @param entitySubject ID of the subject entity

    */
    void SetSubject(egf::EntityID entityCamera, egf::EntityID entitySubject);

    /**
        Eliminate all references to a given camera.  Basically, if this is the active camera,
        null out its pointer.  No need to deactivate it, though, since it is probably being
        deleted.

        @param pCamera Camera to eliminate
    */
    void EliminateCamera(egmSample::ICamera* pCamera);

    /**
        Allocate a new EntityCameraService instance and install it.  This is a convenience function
        that makes it easier to start up the service.

        @return A pointer to the newly allocated EntityCameraService object is returned.
    */
    static void InstallService(efd::ServiceManager* pServiceManager);

    /**
        Find the C++ camera instance associated with a given entity that mixes in
        its builtin model.

        @param entityID Entity ID to find the camera of

        @param loc (optional) A string to print in any error messages to give context.
                It's fine to leave this parameter off, or you can give a short descriptive
                string of why you are looking for the camera.

        @return Camera interface for the associated camera, or NULL.
    */
    egmSample::ICamera* GetCameraFromEntity(egf::EntityID entityID, const char *loc=NULL);

protected:

    ICamera* m_pActiveCamera;

    egf::EntityManager* m_pEntityManager;
};

typedef efd::SmartPointer<EntityCameraService> EntityCameraServicePtr;

} // end namespace egmSample

#include "EntityCameraService.inl"

#endif // EE_ENTITYCAMERASERVICE_H
