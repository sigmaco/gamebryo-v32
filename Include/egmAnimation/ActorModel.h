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
#ifndef EE_ACTORMODEL_H
#define EE_ACTORMODEL_H

#include "egmAnimationLibType.h"

#include <ecr/ecrClassIDs.h>
#include <egf/StandardModelLibraryPropertyIDs.h>
#include <egf/StandardModelLibraryFlatModelIDs.h>
#include <egf/BuiltinModelHelper.h>
#include <egf/IPropertyCallbackInvoker.h>
#include <egf/egfLogIDs.h>
#include <ecr/IAttachedObjectsProperty.h>


namespace egmAnimation
{

/**
    The ActorModel class provides the built-in model functionality for the
    Actor model in the Standard Model Library.
    
    Entites that mix in Actor use this built-in, and the Animation Service makes use of its
    properties. This model is primarily a data container. However, it is responsible for
    notifying the egm::AnimationService that an entity with the Actor model has been created
    or deleted. This is done in the OnAdded and OnRemoved methods.
*/
class EE_EGMANIMATION_ENTRY ActorModel :
    public egf::IBuiltinModelImpl,
    public ecr::IAttachedObjectsProperty
{
    /// @cond EMERGENT_INTERNAL

    EE_DECLARE_CLASS1(
        ActorModel,
        efd::kCLASSID_ActorModel,
        egf::IBuiltinModelImpl);
    EE_DECLARE_CONCRETE_REFCOUNT;

    /// @endcond

    // Define the properties that are built in
    EE_DECLARE_BUILTINMODEL_PROPERTIES
    
        EE_BUILTINMODELPROPERTY(
            ActorModel,
            egf::kPropertyID_StandardModelLibrary_KfmAsset, 
            efd::AssetID, 
            ActorModel,
            m_kfmAsset)

        EE_BUILTINMODELPROPERTY(
            ActorModel,
            egf::kPropertyID_StandardModelLibrary_IsKfmAssetShared, 
            bool, 
            ActorModel,
            m_isKfmAssetShared)

        EE_BUILTINMODELPROPERTY(
            ActorModel,
            egf::kPropertyID_StandardModelLibrary_IsNifAssetShared, 
            bool, 
            ActorModel,
            m_isNifAssetShared)

        EE_BUILTINMODELPROPERTY(
            ActorModel,
            egf::kPropertyID_StandardModelLibrary_InitialSequence, 
            efd::utf8string, 
            ActorModel,
            m_initialSequence)

        EE_BUILTINMODELPROPERTY(
            ActorModel,
            egf::kPropertyID_StandardModelLibrary_AccumulatesTransforms, 
            bool, 
            ActorModel,
            m_accumulatesTransforms)

        EE_BUILTINMODELASSOCPROPERTY_ACCESSOR(
            ActorModel,
            egf::kPropertyID_StandardModelLibrary_AttachedObjects,
            ecr::AttachNifData,
            IAttachedObjectsProperty,
            GetAttachedObject,
            SetAttachedObject,
            GetKeyCount,
            GetNextKey,
            ClearAllAttachedObjects,
            RemoveAttachedObject)

    EE_END_BUILTINMODEL_PROPERTIES


public:

    /// Constructor sets all default properties.
    ActorModel();
    
    /// Virtual destructor does nothing.
    virtual ~ActorModel();

    /**
        @name Built-in Model Functionality
    */
    // @{

    /**
        Initialization function sets the entity and the default values for properties.
    */
    virtual bool Initialize(egf::Entity* pOwner, const egf::PropertyDescriptorList& defaults);

    /**
        Resets the given property to the default.
    */
    virtual bool ResetProperty(const egf::PropertyDescriptor* pDefault);
    
    /**
        Registers the entity with the egmAnimation::AnimationService.
    */
    virtual void OnAdded();

    /**
        Removes the entity from the egmAnimation::AnimationService.
    */
    virtual void OnRemoved();

    /**
        Checks for equality of all properties.
    */
    virtual bool operator==(const IProperty& other) const;

    // @}

    /**
        The factory class for the Actor built-in model.
        
        It is public to allow the egmAnimation::AnimationService to register the factory in its
        PreInit method.
    */
    static egf::IBuiltinModel* ActorModelFactory();

protected:
    efd::AssetID m_kfmAsset;
    bool m_isKfmAssetShared;
    bool m_isNifAssetShared;
    bool m_accumulatesTransforms;
    efd::utf8string m_initialSequence;
};

}; // namespace egmAnimation

#endif // EE_ACTORMODEL_H
