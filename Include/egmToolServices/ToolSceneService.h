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
#ifndef EE_TOOLSCENEGRAPHSERVICE_H
#define EE_TOOLSCENEGRAPHSERVICE_H

#include "egmToolServicesLibType.h"
#include "egmToolServicesClassIDs.h"

#include <NiDirectionalLight.h>

#include <efd/MessageHandlerBase.h>
#include <efd/ISystemService.h>

#include <ecr/SceneGraphService.h>
#include <ecr/RenderService.h>
#include <ecr/CoreRuntimeMessages.h>
#include <ecr/ecrSystemServiceIDs.h>

#include "ToolServicesMessages.h"

namespace egmToolServices
{

class SettingUpdateMessage;


class EE_EGMTOOLSERVICES_ENTRY ToolSceneGraphService
    : public ecr::SceneGraphService
    , public ecr::IRenderServiceDelegate
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS2(
        ToolSceneGraphService,
        efd::kCLASSID_ToolSceneService,
        ecr::SceneGraphService,
        ecr::IRenderServiceDelegate);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond
public:

    /**
        Constructor.

        The constructor passes its arguments to ecr::SceneService. See that class for
        accessor functions.

        The service is always operated in tool mode, with all scene graphs converted to
        have cpu readable data streams.

        @param pWorkflowManager The workflow manager used to coordinate Floodgate task submission.
            If NULL, the service creates its own workflow manager. In general,
            all services should use the same workflow manager if they are operating in the
            same thread, or one manager per-thread otherwise.
        @param pTexturePalette The texture palette is used to facilitate texture sharing.
            The service will create a default palette if one is not provided in this constructor.
            The palette is stored as a smart pointer, so applications must not explicitly
            delete it.
    */
    ToolSceneGraphService(
        NiSPWorkflowManager* pWorkflowManager = NULL,
        NiTexturePalette* pTexturePalette = NULL);

    /**
    */
    inline const NiBound& GetSceneBounds() const;

    /**
    */
    inline float GetWorldScale() const;

    /**
        Handle a settings changed message.
        @param pMessage The settings changed message.
        @param targetChannel Channel the message was sent on.
    */
    void OnSettingsChanged(const SettingsUpdateMessage* pMessage, efd::Category targetChannel);

    /**
        Handle a tools visibility changed message.
        @param pMsg The tools visibility changed message.
        @param targetChannel Channel the message was sent on.
    */
    void OnToolsVisibilityChanged(const efd::StreamMessage* pMsg, efd::Category targetChannel);

    /**
        Load a scene graph directly from disk.

        This function bypasses the standard loading process and synchronously loads the
        named NIF and returns the top level object. Returns NULL if the scene graph could
        not be loaded.

        Internally, this function tries to load the given name from the data directory.
        If that fails, it tries to load it from the application directory. When loaded, the
        objects in the file are registered with SceneGraphService::AddSceneGraph.
    */
    virtual NiAVObjectPtr LoadSceneGraph(const efd::utf8string& fileName);


    /**
        Callback for built-in model property changes.

        Over-ridden from SceneGraphService in order to perform additional updates due to
        property changes.
    */
    virtual void OnPropertyUpdate(
        const efd::ClassID& callerID,
        egf::Entity* pEntity,
        const egf::PropertyID& propertyID,
        const egf::IProperty* pProperty,
        const efd::UInt32 tags);

    /// @cond EMERGENT_INTERNAL
    virtual void OnSurfacePreDraw(ecr::RenderService* pService, ecr::RenderSurface* pSurface);
    virtual void OnSurfacePostDraw(ecr::RenderService* pService, ecr::RenderSurface* pSurface);
    /// @endcond

protected:

    /// Destructor
    virtual ~ToolSceneGraphService();

    /// @name ISystemService methods
    //@{
    virtual const char* GetDisplayName() const;
    virtual void OnServiceRegistered(efd::IAliasRegistrar* pAliasRegistrar);
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);
    virtual efd::AsyncResult OnInit();
    virtual efd::AsyncResult OnTick();
    virtual efd::AsyncResult OnShutdown();
    //@}

    /**
        Updates any entities that are dynamic, like those with animations.  Also updates
        entities that are not usually dynamic that were added to the update once queue.  The
        Tools implementation of this function ignores the inputs and overrides then based on
        external factors.
    
        @param advanceUpdateTime should we advance the current animation time during the update.
        @param performUpdate true to perform updates for dynamic entities.
        @param performUpdateOnce true to perform updates for items in the update once queue.
    */
    virtual void UpdateDynamicEntities(
        bool advanceUpdateTime = true,
        bool performUpdate = true,
        bool performUpdateOnce = true);

    /**
        Updates the dirty properties described by pEntity.

        @param pEntity The entity.
    */
    virtual void UpdateDirtyProperties(egf::Entity* pEntity);

    virtual void UpdateVolatileProperties(
        egf::Entity* pEntity,
        NiAVObject* pSceneGraph,
        bool initialUpdate = false);

    virtual void UpdateAttachedProperty(egf::Entity* pEntity);

    virtual void ToolSceneGraphService::UpdateToolScene(
        egf::Entity* pEntity,
        NiAVObject* pSceneGraph);

    virtual void OnSceneGraphAdded(egf::Entity* pEntity, NiAVObject* pSceneGraph);
    virtual void OnSceneGraphRemoved(egf::Entity* pEntity, NiAVObject* pSceneGraph);
    virtual void OnSceneGraphAdded(SceneGraphHandle handle, NiAVObject* pSceneGraph);
    virtual void OnSceneGraphRemoved(SceneGraphHandle handle, NiAVObject* pSceneGraph);

    void AttachDefaultLights(NiAVObject* pSceneGraph, bool updateLightEffects);
    void DetachDefaultLights(NiAVObject* pSceneGraph, bool updateLightEffects);


    enum VisibilityCategories
    {
        VISIBILITY_PER_ENTITY = 0,
        VISIBILITY_PER_LAYER,
        VISIBILITY_CAMERA_BOUND,
        VISIBILITY_MAX
    };

    class DefaultLightAttacherFunctor :
        public ecr::SceneGraphService::EntitySceneGraphFunctor,
        public ecr::SceneGraphService::HandleSceneGraphFunctor
    {
    public:
        DefaultLightAttacherFunctor(ToolSceneGraphService* pSceneService, bool attachLights);
        ~DefaultLightAttacherFunctor();

        efd::Bool operator()(const egf::Entity* pEntity,
                             const efd::vector<NiObjectPtr>& objects);

        efd::Bool operator()(const ecr::SceneGraphService::SceneGraphHandle handle,
                             const efd::vector<NiObjectPtr>& objects);
    protected:
        ToolSceneGraphService* m_pSceneService;
        bool m_attachLights;
    };

protected:

    efd::map<egf::EntityID, bool> m_invisibilityOverride[VISIBILITY_MAX];

    bool m_useDefaultLights;
    NiDirectionalLightPtr m_spDefaultLight1;
    NiDirectionalLightPtr m_spDefaultLight2;

    bool m_isShutdown;

    NiBound m_sceneBound;
    int m_recomputeBoundsCounter;
    int m_recomputeBoundsEpsilon;

    float m_worldScale;
    bool m_playAnimations;
};

typedef efd::SmartPointer<ToolSceneGraphService> ToolSceneGraphServicePtr;

} // namespace

#include "ToolSceneService.inl"

#endif // EE_TOOLSCENEGRAPHSERVICE_H
