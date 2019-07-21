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
#ifndef EE_IPROPERTYCALLBACKINVOKER_H
#define EE_IPROPERTYCALLBACKINVOKER_H

#include "egfLibType.h"

#include <efd/MemObject.h>
#include <efd/StdContainers.h>
#include <egf/IPropertyCallback.h>


namespace egf
{

/**
    The IPropertyCallbackInvoker class provides common functionality for managing
    property callbacks in built-in models.
    
    It has no public methods. Classes that need to send property update callbacks
    should derived from this class.
    
    The protected member function InvokeCallbacks is used to send the callbacks.
*/
class IPropertyCallbackInvoker
{
protected:
    /**
        Constructor.
        
        The callbackList parameter shoud be a static member of the inheriting class so
        that a common copy of the list exists for all instances of the derived class.
        The callback list is not static in this calss so that each derived class has a
        distinct list.
    */
    inline IPropertyCallbackInvoker(efd::vector<IPropertyCallback*>*& pCallbackList);

    /**
        Copy constructor.
        
        The callback lists will be shared.
    */
    inline IPropertyCallbackInvoker(const IPropertyCallbackInvoker& other);

    /**
        Assignment operator.
        
        The callback list is copied.
    */
    inline IPropertyCallbackInvoker& operator=(const IPropertyCallbackInvoker& other);

    /**
        Add a callback.
        
        This function should be called from a static method of the derived
        class in cases where the callback list given in the constructor is a static
        member of the derived class. This allows user of the callbacks to easily
        register just once, via the static member. See egf::PlaceableModel for
        an example.
        
        A callback will be invoked on each event as many times as it is added.
    */
    inline void AddPropertyCallback(IPropertyCallback* pCallback);

    /**
        Remove a callback.

        This function should be called from a static method of the derived
        class in cases where the callback list given in the constructor is a static
        member of the derived class. This allows user of the callbacks to easily
        unregister just once, via the static member. See egf::PlaceableModel for
        an example.
        
        A single instance of the callback is removed. For example, if the callback is
        added twce, then removed once, it will still be invoked once on each event.
    */
    inline void RemovePropertyCallback(IPropertyCallback* pCallback);
    
    /**
        Invoke the callbacks with the given data.
        
        Any callback given in the ignore value will not be invoked.
        
        @param modelID The flat model that is invoking the callback.
        @param pEntity The entity that the property applies to.
        @param propertyID The property ID for the changed property.
        @param pProperty The property containing the new value. It should be safe to cast this
            to the class representing the model ID.
        @param tags Model specific flags for the callback.
        @param ignore Any callbacks to this object should be not be made.
    */
    inline void InvokeCallbacks(
        const egf::FlatModelID& modelID,
        egf::Entity* pEntity,
        const egf::PropertyID& propertyID,
        const IProperty* pProperty,
        const efd::UInt32 tags,
        const IPropertyCallback* ignore);

    /// The callback list.
    efd::vector<IPropertyCallback*>*& m_pCallbacks;
    
}; // class IPropertyCallbackInvoker

}; // namespace egf

#include <egf/IPropertyCallbackInvoker.inl>

#endif // EE_IPROPERTYCALLBACKINVOKER_H
