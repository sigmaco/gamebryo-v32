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
#ifndef EE_LIGHTSERVICE_H
#define EE_LIGHTSERVICE_H

#include <egf/EntityManager.h>
#include <egf/Entity.h>
#include <egf/EntityID.h>
#include <efd/MessageHandlerBase.h>
#include <efd/ISystemService.h>
#include <efd/StreamMessage.h>
#include <egf/EntityChangeMessage.h>
#include <ecr/ecrSystemServiceIDs.h>

#include <NiLight.h>
#include <NiShadowManager.h>

#include "ecrLibType.h"


#include "RenderService.h"
#include "SceneGraphService.h"

#include "CoreRuntimeMessages.h"

namespace ecr
{

/**
    LightService is a Gamebryo service which manages light sources and the lists of entities which
    they affect. LightService uses a simple range based algorithm to determine which renderable
    entities are affected by which lights. LightService also manages shadow generators (optionally
    associated with directional, point, and spot lights), as well as the lists of entities which
    may cast and/or receive shadows.

    When determining which lights are within range, the light service computes the variance of
    light ranges across the three cardinal axes. Using the axis with the largest variance, it
    ignores light to entity pairings which can not affect each other. Each potential pairing
    undergoes a more comprehensive test to determine if a light affects an entity.
*/
class EE_ECR_ENTRY LightService : public efd::ISystemService, public ecr::IRenderServiceDelegate
{
    /// @cond EMERGENT_INTERNAL

    EE_DECLARE_CLASS2(LightService, efd::kCLASSID_LightService, efd::ISystemService,
        ecr::IRenderServiceDelegate);
    EE_DECLARE_CONCRETE_REFCOUNT;

    /// @endcond

public:

    enum
    {
        MAX_LIGHT_PRIORITY = 100
    };

    /**
        Constructor for the LightService.

        Among other things, the constructor initializes the NiShadowManager, which is initially
        set to be active.  Also, all entities are initially set to cast and receive shadows.
        However, by default, all lights are initially set to not cast shadows.  This approach
        makes it straightforward to selectively enable shadowing capabilities for individual
        lights, without having to consider the shadow manager itself or individual cast/receive
        shadow properties.
    */
    LightService(bool enableAutomaticRelighting = true);

    /**
        Returns the display name, LightService.
    */
    virtual const char* GetDisplayName() const;

    /**
        Performs simple pre-initialization and gets a pointer to the message service.
    */
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);

    /**
        This method initializes the shadow click generator and activates it, initializes the
        shadow manager's scene camera, and creates a shadow render step and assigns the
        preprocessing callback function.

        During this process, any necessary PSSM configuration is also performed.  OnInit also
        registers for local messages and caches pointers to other services necessary for the
        functioning of the LightService.
    */
    virtual efd::AsyncResult OnInit();

    /**
        Each tick, the light manager calculates which lights affect which entity.

        If a light has changed position or rotation, it is compared against all active entities.
        If an entity has changed, it is compared against all active lights.
    */
    virtual efd::AsyncResult OnTick();

    /**
        Shuts down the light service.
    */
    virtual efd::AsyncResult OnShutdown();

    /**
        This message handler is called when a new entity is added.

        LightService only handles entities that mix in the Light model in this handler.  These
        entities are added to its internal list of lights.

        @param pMessage The entity message.
        @param targetChannel Unused argument.
    */
    void HandleEntityAddedMessage(const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    /**
        This message handler is called when an entity has been removed from the entity manager.

        If the entity mixes in the Light model, the light service will remove that light from its
        internal list as well as removing its influence from all active renderable entities.

        @param pMessage The entity message.
        @param targetChannel Unused argument.
    */
    void HandleEntityRemovedMessage(const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    /**
        This message handler is called when properties of an entity change.

        If the entity being updated is not a light, then check its shadow cast/receive property
        settings.  Then iterate through all the shadow generators and ensure that, depending on
        the entity property settings, the entity and its scene graph cast shadows or not, and
        receive shadows or not, as appropriate.

        If the entity being updated is a light, then this message handler updates the underlying
        NiLight object's and/or corresponding (but optional) NiShadowGenerator object's
        parameters, as needed.

        @param pMessage Entity change message.
        @param targetChannel Unused argument.
    */
    void HandleEntityUpdatedMessage(const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    /**
        This message handler is called when properties of some set of scene graphs associated with
        entities change.

        If the entity being updated is not a light, then check its shadow cast/receive property
        settings.  Then iterate through all the shadow generators and ensure that, depending on
        the entity property settings, the NiNode casts shadows or not, and receives shadows or
        not, as appropriate.

        If the entity being updated is a light, then this message handler updates the NiLight's
        and/or corresponding (but optional) NiShadowGenerator's parameters, as needed.

        @param pMessage Entity change message.
        @param targetChannel Unused argument.
    */
    void HandleSceneGraphsUpdatedMessage(const SceneGraphsUpdatedMessage* pMessage,
        efd::Category targetChannel);

    /// Returns true when an entity is a light, otherwise false.
    inline efd::Bool IsEntityLight(const egf::EntityID& entityID) const;

    /// Force the LightService to recompute which lights should affect which entities.
    ///
    /// It is safe to call this method during OnPreInit and OnInit.
    virtual void RelightScene(bool onlyChangedObjects = false);

    /**
        Tell the LightService whether to use dynamic lighting for precomputed lights on
        precomputed objects.

        This method forces relighting of the scene.

        It is safe to call this method during OnPreInit and OnInit.
    */
    virtual void SetUsePrecomputedLighting(efd::Bool usePrecomputedLighting);

    /// Returns true if precomputed lighting should be used.
    ///
    /// It is safe to call this method during OnPreInit and OnInit.
    virtual efd::Bool GetUsePrecomputedLighting() const;

    /// @cond EMERGENT_INTERNAL
    /**
        EntityChanged records that the node entity changed so that the affect of lights on the
        node can be determined at a later time.

        @param spNode The node associated with the entity.
        @param entityID The ID of the entity that was changed.
   */
    virtual void EntityChanged(NiNodePtr spNode,
        const egf::EntityID entityID);
    /// @endcond

    /**
        This convenience function enables or disables the NiShadowManager.

        It must be called after OnInit has completed.

        @param bEnable True to enable, or false to disable.
    */
    inline void EnableShadowing(bool bEnable);


    /**
        Returns the scene graph lighting object for the given entity.

        @remarks The entity must have completed its creation lifecycle; calling this function
        before OnAssetsLoaded has finished may result in a NULL return value, as LightService
        may not have received the entity creation message.

        @param id The ID of the entity to locate.
        @return The NiLight corresponding to the entity, or NULL if it cannot be found.
    */
    inline NiLight* GetLightFromEntity(egf::EntityID id);

protected:

    /**
        Destructor for the LightService.

        The destructor removes all lights from its internal storage and removes their
        influence from all renderable scene graphs. The destructor also shuts down the
        NiShadowManager.
    */
    virtual ~LightService();

    /**
        CreateLight takes in the model and returns the proper NiLight based on
        what models are mixed into the model passed in.  If anyone extends NiLight
        and creates a model to represent it, they should inherit the light service
        create the NiLight to match the model.

        @param pModel The model to create the light based on.
        @return The NiLight resulting from the model.
    */
    virtual NiLight* CreateLight(const egf::FlatModel* pModel);

    /**
        UpdateLightProperties applies the light entity properties to the NiLight object associated
        with the light entity.

        @param pLight The light associated with the entity.
        @param pEntity The light entity that was updated.
    */
    virtual void UpdateLightProperties(NiLight* pLight,
        egf::Entity* pEntity);

    /**
        UpdateShadowCaster takes a light entity and updates the NiShadowCaster for the NiLight
        associated with the entity when the entity is discovered or changed.

        If the CastShadows property is true, then the NiShadowCaster is created, if necessary, and
        individual properties are queried in order to set appropriate NiShadowCaster parameters,
        as needed.  Also, the function iterates through all the scene graphs to update Unaffected
        Caster and Unaffected Receiver lists appropriately.

        @param pLight The light associated with the entity.
        @param pEntity The entity that was updated.
    */
    virtual void UpdateShadowCaster(NiLight* pLight,
        egf::Entity* pEntity);

    /**
        Looks up the reflector service and registers for entity discovery,
        entity property change, and entity removal messages. These messages are
        used to manage the underlying animations associated with a given
        entity.

        @return True if successful, false otherwise.
        @remark The initialization process calls this method. If this method
            fails, the service initialization is pending until it succeeds.
    */
    virtual void SubscribeToMessages();

    /**
        A pre-processing call back-function for shadow rendering.

        This function is assigned as a pre-processing call-back function, which will be called
        immediately before the shadow render step is executed.  The ShadowRenderStepPre function
        retrieves the set of render click objects need to render the shadow maps from the shadow
        manager and applies those render clicks to the shadow render step.

        @param pkCurrentStep Pointer to the shadow render step (NiRenderStep) with which this
            pre-processing call-back function is associated.
        @param pvCallbackData Unused argument in this context.
    */
    static bool ShadowRenderStepPre(NiRenderStep* pkCurrentStep,
        void* pvCallbackData);

    /// @name Accessors for Light Limits Per Object.
    //@{
    inline void SetMaxAmbientLightsPerObject(efd::UInt8 uiLimit);
    inline void SetMaxDirectionalLightsPerObject(efd::UInt8 uiLimit);
    inline void SetMaxPointLightsPerObject(efd::UInt8 uiLimit);
    inline void SetMaxSpotLightsPerObject(efd::UInt8 uiLimit);

    inline efd::UInt8 GetMaxAmbientLightsPerObject() const;
    inline efd::UInt8 GetMaxDirectionalLightsPerObject() const;
    inline efd::UInt8 GetMaxPointLightsPerObject() const;
    inline efd::UInt8 GetMaxSpotLightsPerObject() const;
    //@}

    // Determine the Axis that we want to sort on (returns true if the axis changed).
    bool DetermineSortAxis();

    void SetAffectedNodeLists(bool sortAxisChanged);


    /// Overridden from IRenderServiceDelegate to add the shadow click generator to the render
    /// surface.
    virtual void OnSurfaceAdded(RenderService* pService, RenderSurface* pSurface);

    /**
        Overridden from IRenderServiceDelegate to handle adding scene graphs to the light list.

        The new entity (which is not a light) is added to every light's affected nodes list.  This
        approach is conservative and may result in extraneous lights affecting an entity.  The
        next time LightService::OnTick is called, the entity will be reevaluated.  Also, all
        shadow generators' unaffected lists are potentially modified based on whether the newly
        added scene graph casts shadows or not, or receives shadows or not.

        @param pService Unused argument.
        @param pEntity The entity that is getting its scene graph added.
        @param pAVObject The root node of the entity scene graph.
    **/
    virtual void OnRenderedEntityAdded(
        RenderService* pService, egf::Entity* pEntity, NiAVObject* pAVObject);
 
    /**
        Overridden from IRenderServiceDelegate to handle removing scene graphs from the light list.
        This can happen when the entity is moved out of world or destroyed.

        The entity (which is not a light) is detached from every light's affected nodes list.
        Also, all shadow generators' unaffected lists are potentially modified to ensure that the
        NiNode is no longer a part of the unaffected caster or unaffected receiver lists.

        @param pService Unused argument.
        @param pEntity The entity that is getting its scene graph removed.
        @param pAVObject The root node of the entity scene graph.
    */
    virtual void OnRenderedEntityRemoved(
        RenderService* pService, egf::Entity* pEntity, NiAVObject* pAVObject);

protected:
    //---------------------------------------------------------------------------------------------
    // This struct is used in determining Affected Node Lists for Lights
    class BaseObjectData : public efd::MemObject
    {
    public:
        inline BaseObjectData();
        inline BaseObjectData(const NiPoint3& position,
            float radius,
            const egf::EntityID& entityID);

        inline bool operator == (const BaseObjectData& kIn) const;

        inline void DumpData();

        inline static bool ObjectFurther(const BaseObjectData* lhs,
            const BaseObjectData* rhs);

        NiPoint3 m_position;
        float m_projectedCenter;
        float m_radius;

        // TODO mbailey 5/6/09 Any reason this shouldn't be a direct pointer to the entity?
        egf::EntityID m_entityID;
    };

    class LightData : public BaseObjectData
    {
    public:
        inline LightData();
        inline LightData(const NiPoint3& position,
            float radius,
            const egf::EntityID& entityID);

        efd::hash_map<egf::EntityID, float, egf::EntityIDHashFunctor> m_entityPriorityOverride;
        NiLightPtr m_spLight;
    };

    class ReceiverData : public BaseObjectData
    {
    public:
        inline ReceiverData();
        inline ReceiverData(const NiPoint3& position,
            float radius,
            const egf::EntityID& entityID);

        NiNodePtr m_spNode;
    };

    class LightPriority : public efd::MemObject
    {
    public:
        inline bool operator<(const LightPriority& kIn) const;
        inline bool operator>(const LightPriority& kIn) const;

        NiLight* m_pLight;
        float m_fPriority;
    };

    void SortList(efd::vector<BaseObjectData*> * pObjList);

    /**
        GetLightPriorityForReceiver returns a priority of the provided light
        for the provided receiver. This priority is used to determine which
        lights should affect a receiver when the receiver as more light within it's
        range that it supports.

        The light priority is computed in the following manner:
         -The receiver's distance from the light is computed, as a measure of percentage
           of the light's range. 100% = distance of 0,  0% = distance equal to the lights range
         -The percentage of the receiver affected by the light is computed,
           as a rough approximation.
         -The intensity of the light on the receiver is computed and clamped to (0.0 - 1.0).
         -The light's priority property is scaled to -4.0-4.0.
         -All of the values above are summed up creating a total possible priority
          range of -4.0 to 7.0. Where the higher priority value wins.

        @param pLightData The ObjectData associated with the light in question.
        @param pReceiverData The ObjectData associated with the receiver in question.
    */
    virtual float GetLightPriorityForReceiver(LightData* pLightData,
        ReceiverData* pReceiverData);

    /**
        LightEntityChanged records that the light entity changed so that it's affect on the scene
        can be processed at a later time.

        @param pLightData The light data associated with the entity.
        @param pEntity The entity that was changed.
    */
    virtual void LightEntityChanged(LightData* pLightData,
        egf::Entity* pEntity);

    inline void SwapLights(unsigned int i,
        unsigned int j);

    inline void SwapReceivers(unsigned int i,
        unsigned int j);

    inline ReceiverData* FindReceiverData(const egf::EntityID& entityID);

    void AddReceiverData(NiNodePtr spNode,
        const egf::EntityID& entityID);
    void RemoveReceiverData(const egf::EntityID& entityID);
    void UpdateLightData(egf::Entity* pEntity,
        const egf::EntityID& entityID);

    bool LightAffectsReceiver(const LightData* pLight,
        const ReceiverData* pReceiver);

    bool AddReceiverToLightQueue(LightData* pLightData,
        ReceiverData* pReceiverData);

    // For debugging.
    void DumpLights();
    void DumpReceivers();

    efd::MessageService* m_pMessageService;
    egf::EntityManager* m_pEntityManager;
    RenderServicePtr m_spRenderService;
    SceneGraphServicePtr m_spSceneGraphService;

    // TODO: mbailey 5/7/09 Should these be declared as hash_map instead?
    efd::map<egf::EntityID, LightData*> m_entityLightMap;
    efd::map<egf::EntityID, ReceiverData*> m_entityReceiverMap;

    efd::priority_queue<LightPriority, efd::vector<LightPriority> > m_PointPriorityQueue;
    efd::priority_queue<LightPriority, efd::vector<LightPriority> > m_SpotPriorityQueue;
    efd::priority_queue<LightPriority, efd::vector<LightPriority> > m_DirPriorityQueue;

    efd::vector<LightData*> m_changedLightList;
    efd::vector<ReceiverData*> m_changedNodeList;

    efd::vector<LightData*> m_lightList;
    efd::vector<ReceiverData*> m_receiverList;
    efd::Point3 m_sortAxis;

    efd::UInt8 m_uiMaxAmbientLightsPerObject;
    efd::UInt8 m_uiMaxDirectionalLightsPerObject;
    efd::UInt8 m_uiMaxPointLightsPerObject;
    efd::UInt8 m_uiMaxSpotLightsPerObject;

    efd::Bool m_RecieverListDirty;
    efd::Bool m_enableAutomaticRelighting;
    efd::Bool m_bUsePrecomputedLighting;
};

typedef efd::SmartPointer<LightService> LightServicePtr;

}   // End namespace ecr.

#include "LightService.inl"

#endif  // EE_LIGHTSERVICE_H
