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
#ifndef EE_PLACEABLEMODEL_H
#define EE_PLACEABLEMODEL_H

#include "egfLibType.h"

#include <egf/StandardModelLibraryPropertyIDs.h>
#include <egf/StandardModelLibraryFlatModelIDs.h>
#include <egf/BuiltinModelHelper.h>
#include <egf/IPropertyCallbackInvoker.h>
#include <egf/egfLogIDs.h>


namespace egf
{

/**
    The PlaceableModel class provides the built-in model functionality for the
    Placeable model in the StandardModelLibrary.

    Entites that mix in Placeable use this built-in, with the expectation that other
    models will provide functionality to interpret the Placeable properties.

    The PlaceableModel class holds an internal copy of the property values and provides accessor
    functions, as is required for a built-in model. In addition, objects may be registered
    as callbacks to receive notification of property changes, and other code may update
    the internal values directly. Any number of callbacks may be added, allowing multiple
    consumers of the data to register.

    Note that EntityUpdate messages will be sent when an external source modifies the
    property values via the SetInternal functions. Code may choose to rely on the update messages
    rather than use the callback mechanism.
*/
class EE_EGF_ENTRY PlaceableModel
    : public egf::IBuiltinModelImpl
    , public egf::IPropertyCallbackInvoker
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(
        PlaceableModel,
        efd::kCLASSID_PlaceableModel,
        egf::IBuiltinModelImpl);
    EE_DECLARE_CONCRETE_REFCOUNT;

    // Define the properties that are built in
    EE_DECLARE_BUILTINMODEL_PROPERTIES

        EE_BUILTINMODELPROPERTY_ACCESSOR(
            PlaceableModel,
            egf::kPropertyID_StandardModelLibrary_Position,
            efd::Point3,
            PlaceableModel,
            GetPosition,
            SetPosition)

        EE_BUILTINMODELPROPERTY_ACCESSOR(
            PlaceableModel,
            egf::kPropertyID_StandardModelLibrary_Rotation,
            efd::Point3,
            PlaceableModel,
            GetRotation,
            SetRotation)

        EE_BUILTINMODELPROPERTY_ACCESSOR(
            PlaceableModel,
            egf::kPropertyID_StandardModelLibrary_Scale,
            efd::Float32,
            PlaceableModel,
            GetScale,
            SetScale)

    EE_END_BUILTINMODEL_PROPERTIES
    /// @endcond

public:

    /// Constructor sets all default properties.
    PlaceableModel();

    /// Virtual destructor does nothing.
    virtual ~PlaceableModel();

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
    
    /**
        Get the owning entity.
    */
    Entity* GetOwningEntity() const;

    // @}

    /// @name Property Accessors

    //@{

    /**
        Get the position.
    */
    inline efd::Point3 GetPosition() const;

    /**
        Set the position.

        The internally cached value is set. Callbacks are invoked with the
        Position property ID if the value has changed.
    */
    inline void SetPosition(const efd::Point3& position);

    /**
        Get the rotation.

        Rotation is stored as XYZ Euler angles.
    */
    inline efd::Point3 GetRotation() const;

    /**
        Set the rotation.

        The internally cached value is set. Callbacks are invoked with the
        Rotation property ID if the value has changed.
    */
    inline void SetRotation(const efd::Point3& rotation);

    /**
        Get the scale.
    */
    inline efd::Float32 GetScale() const;

    /**
        Set the scale.

        The internally cached value is set. Callbacks are invoked with the
        Scale property ID if the value has changed.
    */
    inline void SetScale(const efd::Float32& scale);

    // @}

    /**
        @name SetInternal Methods

        These methods are to be used by code that manages Placeable data from an external source,
        such as animated character locations or physical object locations. Such code should
        call the SetInternal methods with new values every time the property is known to have
        changed. If the new property value differs from that stored internally, the internal
        value is updated, the property is marked dirty, and callbacks are invoked.

        The ignoreCallback, if given, is not invoked in response to the change. The class setting
        the internal position, if also a registered callback object, may use this to avoid getting
        a callback for a change that the class just caused.
    */

    //@{

    /**
        Set the position cached in this object.

        This causes the property to be marked dirty on the entity.
    */
    void SetInternalPosition(const efd::Point3& position, IPropertyCallback* ignoreCallback = 0);

    /**
        Set the rotation cached in this object.

        This causes the property to be marked dirty on the entity.
    */
    void SetInternalRotation(const efd::Point3& rotation, IPropertyCallback* ignoreCallback = 0);

    /**
        Set the scale cached in this object.

        This causes the property to be marked dirty on the entity.
    */
    void SetInternalScale(const efd::Float32 scale, IPropertyCallback* ignoreCallback = 0);

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
    inline static void AddCallback(IPropertyCallback* pCallback);

    /**
        Remove a callback.

        A single instance of the callback is removed. For example, if the callback is
        added twce, then removed once, it will still be invoked once on each event.
    */
    inline static void RemoveCallback(IPropertyCallback* pCallback);

    //@}

    /**
        The factory class for the Placeable built-in model.

        It is public to allow the egf::FlatModelManager to register the factory in its
        PreInit method.
    */
    static egf::IBuiltinModel* PlaceableModelFactory();

    /// @cond EMERGENT_INTERNAL
    static void _SDMInit();
    static void _SDMShutdown();
    /// @endcond

protected:
    efd::Point3 m_position;
    efd::Point3 m_rotation;
    efd::Float32 m_scale;

    static efd::vector<IPropertyCallback*>* ms_pCallbackList;
};

} // end namespace egf

#include <egf/PlaceableModel.inl>

#endif // EE_PLACEABLEMODEL_H
