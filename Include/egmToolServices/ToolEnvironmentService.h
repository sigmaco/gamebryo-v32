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
#ifndef EE_TOOLENVIRONMENTSERVICE_H
#define EE_TOOLENVIRONMENTSERVICE_H

#include <egmTerrain/EnvironmentService.h>
#include <egmTerrain/TimeOfDayMessages.h>

namespace egmTerrain
{
    class TimeOfDayFile;
}

namespace egmToolServices
{

/**
    The tool environment service implements the EnvironmentService and provides extra
    functionalities that allow tools such as toolbench to create and edit Time of Day editable
    objects including the NiEnvironment.
*/
class EE_EGMTOOLSERVICES_ENTRY ToolEnvironmentService : public egmTerrain::EnvironmentService
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(ToolEnvironmentService, efd::kCLASSID_EnvironmentService,
        egmTerrain::EnvironmentService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

public:

    /**
        Constructor.
    */
    ToolEnvironmentService();

    virtual efd::Float32 GetCurrentTime();
        
    /// Time change callback definition.
    typedef void (__stdcall *TimeChangedCallback)(float time);

    /**
        Time changed callback registration.
    */
    void RegisterTimeChangedCallback(TimeChangedCallback callback);

    /**
        Time changed callback unregistration.
    */
    void UnregisterTimeChangedCallback(TimeChangedCallback callback);

    /**
        Calls all registered TimeChangedCallbacks.
    */
    void RaiseTimeChanged(float newTime);

    /// Keyframe loaded callback definition.
    typedef void (__stdcall *KeyframeLoadedCallback)(ToDProperty propertyName,
        const efd::vector<efd::utf8string>& times, const efd::vector<efd::utf8string>& values);

    /**
        Keyframe changed callback registration.
    */
    void RegisterKeyframeLoadedCallback(KeyframeLoadedCallback callback);

    /**
        Keyframe changed callback unregistration.
    */
    void UnregisterKeyframeLoadedCallback(KeyframeLoadedCallback callback);

    /**
        Call all registered TimeChangedCallbacks.
    */
    void RaiseKeyframeLoaded(ToDProperty propertyName,
        const efd::vector<efd::utf8string>& times, const efd::vector<efd::utf8string>& values);

    /// Property changed callback definition
    typedef void (__stdcall *ToDPropertiesChangedCallback)(
        const efd::vector<ToDProperty>& properties);

    /**
        Property changed callback registration.
    */
    void RegisterToDPropertiesChangedCallback(ToDPropertiesChangedCallback callback);

    /**
        Property changed callback unregistration.
    */
    void UnregisterToDPropertiesChangedCallback(ToDPropertiesChangedCallback callback);

    /**
        Call all registered ToDPropertiesChanged callback.
    */
    void RaiseToDPropertiesChanged(const efd::vector<ToDProperty>& properties);

    /**
        Function called to save the time of day data using the given filename.
        This only saves the properties that are linked to the given entity name.
    */
    bool SaveTimeOfDay(efd::utf8string filepath, efd::utf8string entityName, 
        efd::ID128 entityFileID);

    /**
        Animation changed handler. Called when a ToDAnimationChangedMessage is received
    */
    void HandleAnimationChangedMessage(const egmTerrain::ToDAnimationChangedMessage* pMessage,
        efd::Category targetChannel);

    /**
        Overridden from IRenderServiceDelegate to remove a surface from the m_surfaceRenderOptions
        map.
        @param pService Pointer to the RenderService.
        @param pSurface Pointer to the render surface that was removed.
    */
    virtual void OnSurfaceRemoved(ecr::RenderService* pService, ecr::RenderSurface* pSurface);

    /**
        Sets a constraints for a given property.
    */
    void SetPropertyConstraint(efd::utf8string propertyName, efd::utf8string minValue,
        efd::utf8string maxValue);

    /**
        Updates the flag associated with the given surface in order to render the environment 
        appropriatly.
    */
    void UpdateRenderMode(ecr::RenderSurface* pSurface, bool renderEnvironment, bool useWireframe);

protected:
    virtual void OnServiceRegistered(efd::IAliasRegistrar* pAliasRegistrar);
    virtual efd::AsyncResult OnInit();
    virtual efd::AsyncResult OnTick();
    virtual efd::AsyncResult OnShutdown();

    virtual void AddPropertiesFromFile(egmTerrain::TimeOfDayFile* pFile, efd::utf8string assetLLID);
    virtual bool RegisterEntity(egf::Entity* pEntity);
    virtual bool UnregisterEntity(egf::Entity* pEntity);
    virtual bool CanRenderEnvironment(ecr::RenderSurface* pSurface);
    virtual NiRenderClick* RetrieveSkyRenderClick(ecr::RenderSurface* pSurface);

    /// A set of flags used to indicate how environment is rendered
    enum EnvironmentRenderOptions
    {
        /// Controls whether to render the environment or not
        ENVIRONMENT_RENDER          = 0x01,
        /// Controls whether the environment should be rendered using wireframe
        ENVIRONMENT_USE_WIREFRAME   = 0x02
    };
    
    /**
        Function that will gather all the properties held by the NiTimeOfDay object and
        raise the ToDPropertiesChanged callback.
    */
    void UpdateToDProperties();

    /// Registered time changed callback functions.
    efd::list<TimeChangedCallback> m_registeredTimeChangedCallbacks;

    /// Registered keyframe loaded callback functions.
    efd::list<KeyframeLoadedCallback> m_registeredKeyframeLoadedCallbacks;

    /// Registered property changed callback functions.
    efd::list<ToDPropertiesChangedCallback> m_registeredToDPropertiesChangedCallbacks;

    /// Keeps a map of properties registered with the time of day object.
    efd::map<efd::utf8string, ToDProperty> m_propertyMap;

    /// Keeps a map of surfaces to render mode flags
    typedef efd::map<ecr::RenderSurface*, NiUInt8> SurfaceToRenderOptionsMap;
    SurfaceToRenderOptionsMap m_surfaceRenderOptions;

    /// Keeps a map of filenames associated with resolved entity names
    typedef efd::map<efd::ID128, efd::utf8string> EntityToFileMap;
    EntityToFileMap m_assetFilePath;
};

}//namespace

#endif
