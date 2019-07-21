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
#ifndef EE_IPROPERTYCALLBACK_H
#define EE_IPROPERTYCALLBACK_H

#include "egfLibType.h"

#include <efd/MemObject.h>
#include <egf/IProperty.h>


namespace egf
{

/**
    The IPropertyCallback interface class describes the method required for
    a callback that is invoked by a built-in model property event.

    Built-in models are intended to provide an efficient way of handling entity property
    data and updates. Many standard built-in models provide a callback mechanism to provide
    immediate notification of property changes in the model. This class defines the interface
    used by those callbacks. For example, the Placeable model provides callbacks for when the
    pose properties change, and the Scene Graph Service sets itself as a callback object to
    receive notification when those properties change.
*/
class IPropertyCallback : public efd::MemObject
{
public:
    /**
        Method invoked when a property changes.

        @param callerID The class ID of the calling object.
        @param pEntity The entity that owns the property.
        @param propertyID The property ID of the property that has changed.
        @param pProperty The property data for the changed property.
        @param tags Class specific tags. If used, they are defined in the calling class.
    */
    virtual void OnPropertyUpdate(
        const efd::ClassID& callerID,
        egf::Entity* pEntity,
        const egf::PropertyID& propertyID,
        const IProperty* pProperty,
        const efd::UInt32 tags) = 0;

    /// Virtual Destryctor
    virtual ~IPropertyCallback() {}

}; // class IPropertyCallback

} // end namespace egf

#endif // EE_IPROPERTYCALLBACK_H
