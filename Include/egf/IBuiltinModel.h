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
#ifndef EE_IBUILTINMODEL_H
#define EE_IBUILTINMODEL_H

#include <egf/IProperty.h>
#include <efd/IBase.h>
#include <egf/PropertyDescriptor.h>
#include <egf/egfClassIDs.h>

namespace efd
{
// Forward declarations
class ServiceManager;
class ParameterList;
}

namespace egf
{

// Forward declarations.
class BehaviorDescriptor;
class Entity;

/// Interface from which all built-in models derive.
class EE_EGF_ENTRY IBuiltinModel
    : public efd::IBase
    , public IProperty
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_INTERFACE1(IBuiltinModel, efd::kCLASSID_IBuiltinModel, efd::IBase);
    /// @endcond
public:
    /**
        After the built-in model is "factoried", this method is called to associate the built-in
        model with its owning entity.  This is effectively part of the construction of the entity
        in question, as a result the owning entity is not yet fully constructed.  This means it
        is not yet valid to call most methods (for example, property and behavior related methods)
        on the owning entity during Initialize.

        It is possible that the owning entity might fail to be fully constructed even after you
        have successfully completed your initialization.  If this happens then the entity and
        your built-in model may be deleted with no further method calls.  As such you should
        avoid caching references to your built-in model implementation until the OnAdded method
        is invoked.  Otherwise a memory leak may result if the entity fails construction.

        The base class version of this method must be called if the method is overridden.
        The return value of the IBuiltinModel implementation should be ignored (see below).

        @param i_pOwner Owning entity.
        @param i_Defaults Default property descriptor list.
        @return True if initialization was successful, false otherwise.  The default implementation
            will fail if there are built-in properties; override to handle setting the defaults.
    */
    virtual bool Initialize(
        Entity* i_pOwner,
        const PropertyDescriptorList& i_Defaults);

    /**
        Behavior invocation for built-in model behaviors occurs through this dispatch function.

        If a built-in model implements any script callable behaviors, then it must override
        Dispatch().  A typical override would switch on the behavior, unpack the arguments,
        possibly do a few lookups, and then call whatever existing API does the work.

        @param i_pBehaviorToInvoke Descriptor of the behavior to invoke.
        @param i_pArgumentList ParameterList consisting of all the arguments to this behavior.
        @return True if the requested behavior is valid for this built-in model.  A true value
            does not mean the behavior itself "succeeded"; normal behavior response methods are
            used for the behavior to indicate its results.
    */
    virtual bool Dispatch(
        const BehaviorDescriptor* i_pBehaviorToInvoke,
        efd::ParameterList* i_pArgumentList);

    /**
        This method is called during the addition of the owning entity to the EntityManager.
        This is the first method called on the IBuiltinModel where you can be assured your owning
        entity has been fully constructed.  As such this is the earliest opportunity where it is
        safe for your built-in model implementation to interact with other services.

        The default implementation does nothing.

        @note If other services hold direct references to your built-in model then those references
        should be released in or before OnRemoved is called.
    */
    virtual void OnAdded();

    /**
        Called when an entity lifecycle has completed.

        @param lifecycle The lifecycle that is ending.  See the Entity::LifeCycles enum for
            some default lifecycle values.  Other sources may define additional lifecycles.
    */
    virtual void OnEndLifecycle(efd::UInt32 lifecycle);

    /**
        This method is called during the removal of the owning entity from the EntityManager.

        After this method is called, you can no longer rely on accessing the owning entity (the
        default implementation sets the m_pOwningEntity member to NULL).  Anything holding a
        reference to your built-in model should be asked to release those references when this
        method is called.

        The base class version of this method must be called if the method is overridden, at
        the end of the overriding method. The default implementation clears the owning entity,
        which makes the service manager unavailable.
    */
    virtual void OnRemoved();

    /**
        Reset the property described by the PropertyDescriptor to the default value contained
        within that PropertyDescriptor.
    */
    virtual void OnOwningEntityReinitialized(Entity* i_pOwner);

    /**
        Reset the property described by the PropertyDescriptor to the default value contained
        within that PropertyDescriptor.
    */
    virtual bool ResetProperty(const egf::PropertyDescriptor* pDefault);

    /**
        Equality operator.

        Property values should be compared, but not derived values that might be modified
        or set during usage. Also, the base class operator should always be checked.
    */
    virtual bool operator==(const IProperty& other) const;

    /**
        Helper function to retrieve the ServerManager.  This method will only work between when
        OnAdded has been called and when OnRemoved has been called.  This is the only time when
        it is safe for a built-in model to interact with other servers anyway since prior to
        OnAdded you cannot be sure your owning entity is fully created and after OnRemoved your
        owning entity will be destructed.

        @return efd::ServiceManager* The ServiceManager, or NULL if the service manager is not
            available at this time.
    */
    const efd::ServiceManager* GetServiceManager() const;

private:
    /// A built-in model cannot be cloned, so this method returns NULL. This method is marked as
    /// private to prevent direct usage.
    virtual IProperty* Clone() const;

protected:
    /// Constructor.
    IBuiltinModel();

    /**
        Components are special; they have no specific property type since the built-in model
        itself is the holder of the data.  This organization is ok, however, since the
        GetPropertyType() method is only used to validate the PropertyDescriptor, and built-in
        model properties still use regular IProperty instances to store their default values.
        So IBuiltinModel overrides this method to provide a default implementation that should
        not be further modified.
    */
    virtual efd::ClassID GetPropertyType() const;

    /*
        Helper for marking changed built-in model properties as dirty. SetDirty is a protected
        Entity method, but IBuiltinModel is a friend of Entity, so derived IBuiltinModel classes
        can use this method to call Entity::SetDirty. Built-in Model implementations must mark
        modified properties as dirty in order for the update notifications to properly reach the
        interested system services (many services rely on receiving these updates to function). It
        is not necessary to call this method for the property being changed by a SetValue call as
        that property is automatically marked dirty, but you must call this if your SetValue call
        changes other property values as well or if a behavior call or other method changes a
        property value property. Changes to data not exposed as a property does not need to call
        SetDirty.
    */
    void SetDirty(PropertyID propID);

    /*
        All built-in models are owned by an entity. This member variable tracks the owner. Since
        the owning entity manages the life cycle of the built-in model, this pointer is a regular
        pointer, to avoid circular references. This pointer should remain valid from Initialize
        where it is first set through OnRemoved but should not be used after OnRemoved has been
        called.
    */
    Entity* m_pOwningEntity;
};

/// Define smart pointer to IBuiltinModel class.
typedef efd::SmartPointer<IBuiltinModel> IBuiltinModelPtr;

} // end namespace egf.


#endif // EE_IBUILTINMODEL_H
