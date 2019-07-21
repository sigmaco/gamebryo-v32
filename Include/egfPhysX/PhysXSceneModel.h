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
#ifndef EE_PHYSXSCENEMODEL_H
#define EE_PHYSXSCENEMODEL_H

#include "egfPhysXLibType.h"

#include <egfPhysX/PhysXSceneData.h>
#include <egfPhysX/PhysXModelLibraryPropertyIDs.h>
#include <egfPhysX/PhysXModelLibraryFlatModelIDs.h>
#include <egf/BuiltinModelHelper.h>


namespace egfPhysX
{

/**
    The PhysXSceneModel class provides the built-in model functionality for the
    PhysX Scene model in the PhysXModelLibrary.
    
    Entites that mix in PhysXScene use this built-in, and the egfPhysX::SceneService
    caches pointers to the model when it discovers entities that contain it.
*/
class PhysXSceneModel : public egf::IBuiltinModelImpl, public egfPhysX::PhysXSceneData
{
    /// @cond EMERGENT_INTERNAL

    EE_DECLARE_CLASS2(
        PhysXSceneModel,
        efd::kCLASSID_PhysXSceneModel,
        egf::IBuiltinModelImpl,
        egfPhysX::PhysXSceneData);
    EE_DECLARE_CONCRETE_REFCOUNT;

    /// @endcond

    // Define the properties that are built in (all of them)
    EE_DECLARE_BUILTINMODEL_PROPERTIES
    
        EE_BUILTINMODELPROPERTY_ACCESSOR_REF(
            PhysXSceneModel,
            egf::kPropertyID_PhysXModelLibrary_SceneName, 
            efd::utf8string, 
            PhysXSceneModel, 
            GetSceneName,
            SetSceneName)
    
        EE_BUILTINMODELPROPERTY_ACCESSOR(
            PhysXSceneModel,
            egf::kPropertyID_PhysXModelLibrary_ScaleFactor, 
            efd::Float32, 
            PhysXSceneData, 
            GetScaleWorldToPhysX,
            SetScaleWorldToPhysX)
    
        EE_BUILTINMODELPROPERTY_ACCESSOR(
            PhysXSceneModel,
            egf::kPropertyID_PhysXModelLibrary_Timestep, 
            efd::Float32, 
            PhysXSceneData, 
            GetTimeStep,
            SetTimeStep)

        EE_BUILTINMODELPROPERTY_ACCESSOR(
            PhysXSceneModel,
            egf::kPropertyID_PhysXModelLibrary_MaxSubSteps,
            efd::UInt32, 
            PhysXSceneData, 
            GetMaxSubSteps,
            SetMaxSubSteps)

        EE_BUILTINMODELPROPERTY_ACCESSOR(
            PhysXSceneModel,
            egf::kPropertyID_PhysXModelLibrary_NumSubSteps,
            efd::UInt32, 
            PhysXSceneData, 
            GetNumSubSteps,
            SetNumSubSteps)

        EE_BUILTINMODELPROPERTY_ACCESSOR(
            PhysXSceneModel,
            egf::kPropertyID_PhysXModelLibrary_Gravity,
            efd::Point3, 
            PhysXSceneData, 
            GetGravity,
            SetGravity)

        EE_BUILTINMODELPROPERTY_ACCESSOR(
            PhysXSceneModel,
            egf::kPropertyID_PhysXModelLibrary_DoFixedStep,
            efd::Bool, 
            PhysXSceneData, 
            GetFixedTimeStep,
            SetFixedTimeStep)

        EE_BUILTINMODELPROPERTY_ACCESSOR(
            PhysXSceneModel,
            egf::kPropertyID_PhysXModelLibrary_BlockOnFetch,
            efd::Bool, 
            PhysXSceneData, 
            GetBlockOnFetch,
            SetBlockOnFetch)

        EE_BUILTINMODELPROPERTY_ACCESSOR(
            PhysXSceneModel,
            egf::kPropertyID_PhysXModelLibrary_UseHardware,
            efd::Bool, 
            PhysXSceneData, 
            GetUseHardware,
            SetUseHardware)

        EE_BUILTINMODELPROPERTY_ACCESSOR(
            PhysXSceneModel,
            egf::kPropertyID_PhysXModelLibrary_ActivateOnSetFinished,
            efd::Bool, 
            PhysXSceneModel, 
            GetActivateOnSetFinished,
            SetActivateOnSetFinished)
    
        EE_BUILTINMODELPROPERTY_READONLY_ACCESSOR(
            PhysXSceneModel,
            egf::kPropertyID_PhysXModelLibrary_SimActive,
            efd::Bool,
            PhysXSceneData,
            GetSimActive)

    EE_END_BUILTINMODEL_PROPERTIES


public:

    /// Constructor sets all default properties.
    PhysXSceneModel();
    
    /// Virtual destructor.
    virtual ~PhysXSceneModel();

    /**
        @name Built-in Model Functionality
    */
    // @{

    /// Initialization function sets the entity and the default values for properties.
    virtual bool Initialize(egf::Entity* pOwner, const egf::PropertyDescriptorList& defaults);

    /// The PhysX scene is created.
    virtual void OnAdded();

    /// The PhysX scene is released after simulation is forced to complete.
    virtual void OnRemoved();

    /// Resets the given property to the default.
    virtual bool ResetProperty(const egf::PropertyDescriptor* pDefault);

    /**
        Checks for equality of all properties, but not runtime modified data.
    */
    virtual bool operator==(const IProperty& other) const;

    // @}

    /// Get the name of the scene.
    inline const efd::utf8string& GetSceneName() const;

    /**
        Set the name of the scene.
        
        We implement it here because special action must be taken with the scene
        service to ensure corret handling if a scene rename.
    */
    virtual void SetSceneName(const efd::utf8string& newName);

    inline efd::Bool GetActivateOnSetFinished() const;
    inline void SetActivateOnSetFinished(const efd::Bool& activate);

    /**
        The factory class for the PhysX Scene built-in model.
        
        It is public to allow the egfPhysX::SceneService to register the factory in its
        PreInit method.
    */
    static egf::IBuiltinModel* PhysXSceneModelFactory();

protected:
    efd::Bool m_activateOnSetFinished;
};

}; // namespace egfPhysX

#include <egfPhysX/PhysXSceneModel.inl>

#endif // EE_PHYSXSCENEMODEL_H
