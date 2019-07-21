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
#ifndef EE_IBUILTINMODELIMPL_H
#define EE_IBUILTINMODELIMPL_H

#include <egf/IProperty.h>
#include <egf/PropertyDescriptor.h>
#include <efd/StdContainers.h>
#include <egf/PrimitiveProperties.h>
#include <egf/UtilityProperties.h>
#include <egf/IBuiltinModel.h>
#include <efd/Serialize.h>


// The ugly nitty-gritty details are in a separate header file to avoid needless confusion
#include "BuiltinModelHelper_details.inl"


namespace egf
{

class Entity;
class BehaviorDescriptor;


/// Storage type used internally by IBuiltinModelImpl
typedef efd::map<egf::PropertyID, efd::SmartPointer<egf::BuiltinHelper::PropertyData> >
    BuiltinModelPropertyMap;


/**
    A helper class to implement all of the property access methods needed in order to implement
    IBuiltinModel.

    By deriving from this class you can then use the various EE_BUILTINMODELPROPERTY_* macros
    to easily bind properties to either raw variables or accessor methods.

    @see See egf::IProperty and egf::IBuiltinModel for descriptions of the methods implemented
        by this class.
*/
class EE_EGF_ENTRY IBuiltinModelImpl : public IBuiltinModel
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_INTERFACE1(IBuiltinModelImpl, efd::kCLASSID_IBuiltinModelImpl, IBuiltinModel);
    /// @endcond
protected:
    IBuiltinModelImpl();
    virtual ~IBuiltinModelImpl();

    /// You must use EE_DECLARE_BUILTINMODEL_PROPERTIES in your final class in order to override
    /// this method.  Alternatively you can use EE_NO_BUILTINMODEL_PROPERTIES if you have no
    /// properties on your built-in model.
    virtual const BuiltinModelPropertyMap& GetPropertyMap() const = 0;

    // Overridden IBuiltinModel methods are documented in the parent class
    virtual egf::PropertyResult GetValue(egf::PropertyID i_propID, void* o_pData) const;

    virtual egf::PropertyResult GetValue(
        PropertyID i_propID,
        const efd::utf8string& key,
        void* o_pData) const;

    virtual PropertyResult SetValue(
        PropertyID i_propID,
        const efd::utf8string& key,
        const void* i_pData);

    virtual egf::PropertyResult SetValue(egf::PropertyID i_propID, const void* i_pData);

    virtual PropertyResult GetValueAsString(PropertyID propID, efd::utf8string& data) const;

    virtual PropertyResult GetValueAsString(
        PropertyID propID,
        const efd::utf8string& key,
        efd::utf8string& data) const;

    virtual PropertyResult SetValueByString(
        PropertyID i_propID,
        const efd::utf8string& key,
        const efd::utf8string& i_data);

    virtual PropertyResult SetValueByString(PropertyID i_propID, const efd::utf8string& i_data);

    virtual PropertyResult GetPropertyCount(PropertyID i_propID, efd::UInt32& o_count) const;

    virtual PropertyResult GetPropertyKeys(
        PropertyID i_propID,
        efd::list<efd::utf8string>& o_keys) const;

    virtual PropertyResult GetNextPropertyKey(
        PropertyID i_propID,
        const efd::utf8string& i_previousKey,
        efd::utf8string& o_nextKey) const;

    virtual PropertyResult HasValue(PropertyID propID, const efd::utf8string& key) const;

    virtual PropertyResult RemoveValue(PropertyID propID, const efd::utf8string& key);

    virtual efd::ClassID GetDataType(egf::PropertyID i_propID) const;

    virtual bool Initialize(egf::Entity* i_pOwner, const egf::PropertyDescriptorList& i_Defaults);

    virtual bool ResetProperty(const egf::PropertyDescriptor* pDesc);

    void SerializeProperty(egf::PropertyID i_propID, efd::Archive& ar);
    void AdvanceStream(egf::PropertyID i_propID, efd::Archive& ar) const;
};


/// This class helps free memory used by the static maps used by every IBuiltinModelImpl class.
/// This avoids false positives when doing memory leak detection.
class BuiltinModelStaticMapCleaner
{
public:
    /// Add a map to the list requiring cleanup
    static EE_EGF_ENTRY void CleanMapAtSDMShutdown(BuiltinModelPropertyMap& map);

    /// Perform SDM Shutdown cleanup
    static void _SDMShutdown();

private:
    /// List of all the maps that need cleanup during SDMShutdown
    static efd::list<BuiltinModelPropertyMap*> ms_mapsNeedingCleanup;
};

} // end namespace egf

#endif // EE_IBUILTINMODELIMPL_H

