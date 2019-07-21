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
#ifndef EE_MESHMODEL_H
#define EE_MESHMODEL_H

#include "ecrLibType.h"

#include <ecr/ecrClassIDs.h>
#include <egf/StandardModelLibraryPropertyIDs.h>
#include <egf/StandardModelLibraryFlatModelIDs.h>
#include <egf/BuiltinModelHelper.h>
#include <egf/IPropertyCallbackInvoker.h>
#include <egf/egfLogIDs.h>
#include <ecr/IAttachedObjectsProperty.h>


namespace ecr
{

/**
    The MeshModel class provides the built-in model functionality for the
    Mesh model in the StandardModelLibrary.
    
    Entites that mix in Mesh use this built-in, and the Scene Graph Service makes use of its
    properties. This model is primarily a data container. However, it is responsible for
    notifying the ecr::SceneGraphService that an entity with the Mesh model has been created
    or deleted. This is done in the OnAdded and OnRemoved methods.
*/
class EE_ECR_ENTRY MeshModel : public egf::IBuiltinModelImpl, public IAttachedObjectsProperty
{
    /// @cond EMERGENT_INTERNAL

    EE_DECLARE_CLASS1(
        MeshModel,
        efd::kCLASSID_MeshModel,
        egf::IBuiltinModelImpl);
    EE_DECLARE_CONCRETE_REFCOUNT;

    // Define the properties that are built in
    EE_DECLARE_BUILTINMODEL_PROPERTIES
    
        EE_BUILTINMODELPROPERTY(
            MeshModel,
            egf::kPropertyID_StandardModelLibrary_NifAsset, 
            efd::AssetID, 
            MeshModel,
            m_nifAsset)

        EE_BUILTINMODELPROPERTY(
            MeshModel,
            egf::kPropertyID_StandardModelLibrary_IsNifAssetShared, 
            efd::Bool, 
            MeshModel,
            m_isNifAssetShared)
            
        EE_BUILTINMODELASSOCPROPERTY_ACCESSOR(
            MeshModel,
            egf::kPropertyID_StandardModelLibrary_AttachedObjects,
            ecr::AttachNifData,
            IAttachedObjectsProperty,
            GetAttachedObject,
            SetAttachedObject,
            GetKeyCount,
            GetNextKey,
            ClearAllAttachedObjects,
            RemoveAttachedObject)

    EE_END_BUILTINMODEL_PROPERTIES;

    /// @endcond

public:

    /// Constructor sets all default properties.
    MeshModel();
    
    /// Virtual destructor does nothing.
    virtual ~MeshModel();

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
        Registers the entity with the ecr::SceneGraphService.
    */
    virtual void OnAdded();

    /**
        Removes the entity from the ecr::SceneGraphService.
    */
    virtual void OnRemoved();

    /**
        Checks for equality of all properties.
    */
    virtual bool operator==(const IProperty& other) const;

    // @}

    /**
        The factory class for the Mesh built-in model.
        
        It is public to allow the ecr::SceneGraphService to register the factory in its
        PreInit method.
    */
    static egf::IBuiltinModel* MeshModelFactory();

protected:
    efd::AssetID m_nifAsset;
    efd::Bool m_isNifAssetShared;
};

}; // namespace ecr

#endif // EE_MESHMODEL_H
