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
#ifndef EE_RENDERABLEMODEL_H
#define EE_RENDERABLEMODEL_H

#include "ecrLibType.h"

#include <ecr/ecrClassIDs.h>
#include <egf/StandardModelLibraryPropertyIDs.h>
#include <egf/StandardModelLibraryFlatModelIDs.h>
#include <egf/BuiltinModelHelper.h>
#include <egf/IPropertyCallbackInvoker.h>
#include <egf/egfLogIDs.h>
#include <egf/Entity.h>

namespace ecr
{

/**
    The RenderableModel class provides the built-in model functionality for the
    Renderable model in the StandardModelLibrary.
    
    Entites that mix in Renderable use this built-in, with the expectation that other
    models or services will provide functionality to interpret the IsVisible property.
    
    The RenderableModel class holds an internal copy of the IsVisible value and provides accessor
    functions, as is required for a built-in model. In addition, objects may be registered
    as callbacks to receieve notification of property changes, and other code may update
    the internal values directly. Any number of callbacks may be added, allowing multiple
    consumers of the data to register. See the egf::IPropertyCallbackInvoker class for the
    API to add and remove callbacks.
    
    Note that EntityUpdate messages will be sent when an external source modifies the
    property values via the SetInternalIsVisible function. Code may choose to rely on the
    update messages rather than use the callback mechanism.
*/
class RenderableModel : public egf::IBuiltinModelImpl, public egf::IPropertyCallbackInvoker
{
    /// @cond EMERGENT_INTERNAL

    EE_DECLARE_CLASS1(
        RenderableModel,
        efd::kCLASSID_RenderableModel,
        egf::IBuiltinModelImpl);
    EE_DECLARE_CONCRETE_REFCOUNT;

    // Define the properties that are built in
    EE_DECLARE_BUILTINMODEL_PROPERTIES
    
        EE_BUILTINMODELPROPERTY_ACCESSOR(
            RenderableModel,
            egf::kPropertyID_StandardModelLibrary_IsVisible, 
            efd::Bool, 
            RenderableModel, 
            GetIsVisible,
            SetIsVisible)
    EE_END_BUILTINMODEL_PROPERTIES

    /// @endcond

public:

    /// Constructor sets all default properties.
    RenderableModel();
    
    /// Virtual destructor does nothing.
    virtual ~RenderableModel();

    /**
        @name Built-in Model Functionality
    */
    // @{

    /**
        Initialization function sets the entity and the default values for properties.
        
        Callbacks are not invoked on initialization.
    */
    virtual bool Initialize(egf::Entity* pOwner, const egf::PropertyDescriptorList& defaults);

    /**
        Resets the given property to the default.
        
        Callbacks are invoked.
    */
    virtual bool ResetProperty(const egf::PropertyDescriptor* pDefault);

    /**
        Checks for equality of all properties.
    */
    virtual bool operator==(const IProperty& other) const;

    // @}

    /// @name Property Accessors
    
    //@{
    
    /**
        Get the IsVisible property.
    */
    inline efd::Bool GetIsVisible() const;

    /**
        Set the IsVisible property.
        
        The internally cached value is set. Callbacks are invoked with the
        IsVisible property ID if the value has changed.
    */
    inline void SetIsVisible(const efd::Bool& isVisible);

    /**
        Set the IsVisible property directly, without passing through the entity property system.
        
        This method is to be used by code that manages IsVisible data from an external source.
        Such code should call the SetInternal methods with new values every time the property is
        known to have changed. If the new property value differs from that stored internally,
        the internal value is updated, the property is marked dirty, and callbacks are invoked.
        
        The ignoreCallback, if given, is not invoked in response to the change. The class setting
        the value if also a registered callback object, may use this to avoid getting
        a callback for a change that the class just caused.
    */
    inline void SetInternalIsVisible(
        const efd::Bool isVisible,
        egf::IPropertyCallback* ignoreCallback = 0);

    //@}

    /**
        @name Callback Registration

        Use these static methods to register and unregister for callbacks from this model.        
    */
    
    //@{

    /**
        Add a callback.
        
        A callback will be invoked on each event as many times as it is added.
    */
    inline static void AddCallback(egf::IPropertyCallback* pCallback);

    /**
        Remove a callback.
        
        A single instance of the callback is removed. For example, if the callback is
        added twice, then removed once, it will still be invoked once on each event.
    */
    inline static void RemoveCallback(egf::IPropertyCallback* pCallback);

    //@}


    /**
        The factory class for the Renderable built-in model.
        
        It is public to allow the ecr::SceneGraphService to register the factory in its
        PreInit method.
    */
    static egf::IBuiltinModel* RenderableModelFactory();

    /**
        Init must be called before any instances of this class are created.
        
        The method allocates the callback list.
    */
    static void Initialize();

    /**
        Shutdown must be called after all instances of this class are deleted.
        
        The method deallocates the callback list.
    */
    static void Shutdown();

protected:
    efd::Bool m_isVisible;

    static efd::vector<egf::IPropertyCallback*>* ms_pCallbackList;
};

}; // namespace ecr

#include <ecr/RenderableModel.inl>

#endif // EE_RENDERABLEMODEL_H
