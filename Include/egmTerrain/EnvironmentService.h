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
#ifndef EE_ENVIRONMENTSERVICE_H
#define EE_ENVIRONMENTSERVICE_H

#include "egmTerrainLibType.h"
#include "TimeOfDayMessages.h"

#include <egf/EntityID.h>
#include <efd/FixedString.h>
#include <efd/ISystemService.h>
#include <efd/StreamMessage.h>

#include <ecr/RenderService.h>
#include <ecr/SceneGraphService.h>
#include <ecr/ecrSystemServiceIDs.h>
#include <ecr/LightService.h>
#include <NiEnvironmentLib.h>
#include <NiTimeOfDay.h>

// Forward declarations
namespace egf
{
    class EntityManager;
}

namespace efd
{
    class MessageService;
}

namespace egmTerrain
{

    class TimeOfDayFile;
/**
    The environment service provides an interface and a set of script built-ins for interfacing with
    the Gamebryo environment system. The service allows seamless integration of entities, scripts,
    and behaviors with Gamebryo's environment system without the need for extensive custom code.
*/
class EE_EGMTERRAIN_ENTRY EnvironmentService :
    public efd::ISystemService,
    public efd::AssetChangeHandler,
    public ecr::IRenderServiceDelegate
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(EnvironmentService, efd::kCLASSID_EnvironmentService, efd::ISystemService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

    /// @name Construction and Destruction
    //@{
protected:
    /// Virtual Destructor
    virtual ~EnvironmentService();

public:
    /// Default Constructor
    EnvironmentService();
    //@}

    /// Structure defining a time of day property
    struct ToDProperty
    {
        /// The property's name
        efd::utf8string m_propertyName;
        /// The property's type
        efd::utf8string m_propertyType;
        /// The property's default value
        efd::utf8string m_defaultValue;
        /// The property's minimum value
        efd::utf8string m_minValue;
        /// The property's maximum value
        efd::utf8string m_maxValue;
    };

    /**
        Function that returns the current time. This is virtual as different clocks are used
        at runtime and tool time.
    */
    virtual efd::Float32 GetCurrentTime();

    /**
        Return the current environment.  Returns NULL if none.
    */
    inline NiEnvironment* GetNiEnvironment();

    /**
        Returns the current time of day object. Returns NULL if none.
    */
    inline NiTimeOfDay* GetNiTimeOfDay();

    /**
        Keyframes changed handler. Called when a ToDKeyframesChangedMessage is received
    */
    void HandleKeyframesChangedMessage(
        const ToDKeyframesChangedMessage* pMessage,
        efd::Category targetChannel);

    /**
        Time changed handler. Called when a ToDTimeChangedMessage is received
    */
    void HandleTimeChangedMessage(
        const ToDTimeChangedMessage* pMessage,
        efd::Category targetChannel);

    /**
        This message handler is called when a new entity is discovered.
        @param pMessage The entity message.
        @param targetChannel Channel the message was sent on.
    */
    void HandleEntityDiscoverMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    /**
        This message handler is called when an entity has been removed from the
        EntityManager.
        @param pMessage The entity message.
        @param targetChannel Channel the message was sent on.
    */
    void HandleEntityRemovedMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    /**
        This message handler is called when an entity enters the world. It defines the start of the
        time of day animation (when the TimeOfDay model enters the world) as well as the rendering
        of the environment model.

        @param pMessage The entity message.
        @param targetChannel Channel the message was sent on.
    */
    void HandleEntityEnterWorldMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    /**
        This message handler is called when an entity exits the world. This will pause the
        time of day animation (when the TimeOfDay model enters the world) as well as the rendering
        of the environment model.

        @param pMessage The entity message.
        @param targetChannel Channel the message was sent on.
    */
    void HandleEntityExitWorldMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    /**
        This message handler is called when properties of an entity change.

        @param pMessage Entity change message.
        @param targetChannel Unused argument.
    */
    void HandleEntityUpdatedMessage(
        const egf::EntityChangeMessage* pMessage,
        efd::Category targetChannel);

    /**
        Handle an asset locater response message.
        @param pMessage The asset locater response message.
        @param targetChannel Channel the message was sent on.
    */
    virtual void HandleAssetLocatorResponse(
        const efd::AssetLocatorResponse* pMessage,
        efd::Category targetChannel);

    /**
        Handles changes made to an asset
    */
    virtual void HandleAssetChange(const efd::utf8string& assetId, const efd::utf8string& tag);

    /**
        Overridden from IRenderServiceDelegate to apply the environment's render click to the
        surface.
        @param pService Pointer to the RenderService.
        @param pSurface Pointer to the newly created render surface.
    */
    virtual void OnSurfaceAdded(ecr::RenderService* pService, ecr::RenderSurface* pSurface);

    /**
        Overridden from IRenderServiceDelegate to apply the environment's render click to the
        surface.
        @param pService Pointer to the RenderService.
        @param pSurface Pointer to the newly created render surface.
    */
    virtual void OnSurfaceRecreated(ecr::RenderService* pService, ecr::RenderSurface* pSurface);

    /**
        Marks m_requireRedraw to true. This will eventually invalidate the RenderContext once
        in the update function.
    */
    inline void RequestRedraw();

    /**
        Returns whether or not changes to the service warrant a redraw.
    */
    inline efd::Bool RequiresRedraw();

protected:
    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual const char* GetDisplayName() const;
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);
    virtual efd::AsyncResult OnInit();
    virtual efd::AsyncResult OnTick();
    virtual efd::AsyncResult OnShutdown();

    /// The sun's entity ID used by the environment
    egf::EntityID m_sunEntityRef;

    /// The time of day entity ID
    egf::EntityID m_timeOfDayEntityID;

    /// Pointer to the NiEnvironment object
    NiEnvironmentPtr m_spEnvironment;

    /// Pointer to the NiTimeOfDay object
    NiTimeOfDayPtr m_spTimeOfDay;

    /// Speed of the time of day animation
    efd::UInt32 m_animationSpeed;

    /// Whether the animation should run or not
    efd::Bool m_runAnimation;

    /// Whether the TimeOfDay model is in the world
    efd::Bool m_toDInWorld;

    /// Whether the environment is in the world
    efd::Bool m_environmentInWorld;

    /// Whether the surface requires a redraw or not
    efd::Bool m_requireRedraw;

    /// List of loaded time of day editable entities
    efd::list<egf::EntityID> m_todAnimatedEntities;

    /// A map linking an asset id to a list of entity that might have requested this asset.
    typedef efd::map< efd::AssetID, efd::list< efd::ID128 > > AssetMap;
    AssetMap m_registeredAssetMap;
    
    /// Vector that keeps all the current asset locate requests in order to avoid repeating a 
    /// request
    efd::vector<efd::AssetID> m_currentFileLocateRequest;

    /// Vector that tracks the names of all registered entities.
    efd::vector<egf::EntityID> m_registeredEntities;

    /// The directional light to use with the environment
    NiDirectionalLightPtr m_spSunLight;

    /// Default directional light used when no sunlight is defined
    NiDirectionalLightPtr m_spDefaultSun;

    /// Cached system services used frequently by the environment service.
    efd::MessageServicePtr m_spMessageService;
    egf::EntityManagerPtr m_spEntityManager;
    ecr::RenderServicePtr m_spRenderService;
    ecr::SceneGraphServicePtr m_spSceneGraphService;
    ecr::LightServicePtr m_spLightService;

    /// The length of a day. This not currently modifiable
    efd::Float32 m_dayDuration;

    /// The time of day scale multiplier defining the speed at which the time passes
    efd::Float32 m_timeScaleMultiplier;

    /// flag defining whether the environment should be animated
    efd::Bool m_animatedToD;

    /// The name of the environment entity
    efd::utf8string m_environmentEntityName;

    /// Categories used for asset lookup responses
    efd::Category m_environmentLoadCategory;

    /// The name of the sky render click
    static NiFixedString ms_skyRenderClickName;

    /// Static variable to store the tag names of the terrain assets
    efd::utf8string m_toDAssetTag;

    /// Do we want to handle asset change events?
    efd::Bool m_handleAssetChanges;

    /**
        Requests the AssetLocator to locate the asset for the given URN.

        @param fileURN the URN of the file to locate
    */
    void LocateFile(efd::utf8string fileURN);

    /**
        Adds properties and associated keyframes for a given entity.
    */
    virtual void AddPropertiesFromFile(TimeOfDayFile* pFile, efd::utf8string assetLLID);

    /**
        Creates the environment associated with the given entity. It will also request for the
        asset to be loaded.

        @param pEntity The entity associated with the NiEnvironment object
    */
    virtual efd::Bool CreateOrLoadEnvironment(egf::Entity* pEntity);

    /**
        Creates the time of day object associated with the given entity

        @param pEntity The entity associated with the NiTimeOfDay object
    */
    virtual efd::Bool CreateTimeOfDay(egf::Entity* pEntity);

    /**
        Registers the given entity's properties with the time of day object.

        @param pEntity the Entity to register
        @return true if the entity is successfully registered
    */
    virtual bool RegisterEntity(egf::Entity* pEntity);

    /**
        Unregisters the given entity's properties with the time of day object.

        @param pEntity the Entity to unregister
        @return true if the entity is successfully registered
    */
    virtual bool UnregisterEntity(egf::Entity* pEntity);

    /**
        Determines whether the environment can be rendered or not.

        @param pSurface The surface we want to render the environment to
        @return true if environment can be rendered.
    */
    virtual bool CanRenderEnvironment(ecr::RenderSurface* pSurface);

    /**
        Calls upon the environment and creates the sky render click using the given surface

        @param pSurface The surface used to create the render click
        @return the newly created click.
    */
    virtual NiRenderClick* RetrieveSkyRenderClick(ecr::RenderSurface* pSurface);

    /**
        Function that parses through the entity's animatable property list to resolve whether
        properties are animatable or not.

        @param pEntity the entity to check the properties for
        @param propName the name of the property to check
    */
    efd::Bool IsPropertyAnimatable(egf::Entity* pEntity, efd::utf8string propName);

    /**
        Updates the given render surface to use the sky custom renderclick

        @param pSurface the Surface to update
    */
    virtual efd::Bool UpdateRenderSurface(ecr::RenderSurface* pSurface);

    /**
        Initializes all render surfaces. This should be called after a sky has been added
    */
    virtual efd::Bool InitializeRenderSurfaces();

    /**
        Function that ensures an entity's model has not already been added to the time of day object

        @param pEntity the entity to check
    */
    efd::Bool EnsureEntityIsUnique(egf::Entity* pEntity);

    /**
        Updates the property data common to all time of day editable entities

        @param pEntity the entity to update
    */
    virtual void UpdateTimeOfDayEditableEntity(egf::Entity* pEntity);

    /**
        Updates the property data for the NiEnvironment object associated with the given entity

        @param pEntity the environment entity to update the environment from
    */
    void UpdateEnvironmentData(egf::Entity* pEntity);

    /**
        Updates the property data for the NiTimeOfDay object associated with the given entity

        @param pEntity the TimeOfDay entity to update the NiTimeOfDay from
    */
    void UpdateTimeOfDayData(egf::Entity* pEntity);

    /**
        Removes the environment object
    */
    void RemoveEnvironment();

    /**
        removes the time of day object
    */
    void RemoveTimeOfDay();

    /**
        Clears all created data
    */
    void ClearAll();

    /**
        Returns true if the given entity name was found in the registered entity list
    */
    bool IsEntityRegistered(egf::EntityID entityID);
};

/// Defines a smart pointer (reference counted) for the EnvironmentService
typedef efd::SmartPointer<EnvironmentService> EnvironmentServicePtr;

}; //namespace

#include "EnvironmentService.inl"
#endif
