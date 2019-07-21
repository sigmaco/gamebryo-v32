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
#ifndef EE_IATTACHEDOBJECTSPROPERTY_H
#define EE_IATTACHEDOBJECTSPROPERTY_H

#include "ecrLibType.h"

#include <efd/StdContainers.h>
#include <egf/PropertyDescriptor.h>
#include <ecr/AttachNifData.h>

namespace ecr
{

/**
    The IAttachedObjectsProperty class provides the data structures used by built-in models that
    include an associative array of AttachedNifAsset data.
    
    The current implementation is a simple data container, with convenience functions for
    models that use it. The class must be derived from to access the data - see the class
    header file for details.
*/
class EE_ECR_ENTRY IAttachedObjectsProperty
{
public:

    /// @name Accessor Functions Required by EE_BUILTINMODELASSOCPROPERTY_ACCESSOR
    
    //@{
    
    /// Get the value for a given key.
    egf::PropertyResult GetAttachedObject(const efd::utf8string& key, AttachNifData& val) const;
    
    /// Set the value at a given key.
    void SetAttachedObject(const efd::utf8string& key, const AttachNifData& val);
    
    /// Get the number of keys.
    efd::UInt32 GetKeyCount() const;
    
    /// Clear the map of all attachments
    void ClearAllAttachedObjects();
    
    /// Get the key that follows the given key
    void GetNextKey(const efd::utf8string& prevKey, efd::utf8string& nextKey) const;
    
    /// Remove the value at the given key.
    egf::PropertyResult RemoveAttachedObject(const efd::utf8string& key);
    
    //@}

protected:
    /// Call this to set the stored value from the given property
    bool SetAttachedObjectsProperty(const egf::PropertyDescriptor* pDefault);

    /// Comparison function.
    bool operator==(const IAttachedObjectsProperty& other) const;

    /// The actual data.
    efd::map<efd::utf8string, AttachNifData> m_attachNifData;
};

} // end namespace ecr

#endif // EE_IATTACHEDOBJECTSPROPERTY_H
