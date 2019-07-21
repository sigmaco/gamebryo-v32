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


#include <efd/BitUtils.h>


namespace egf
{

//------------------------------------------------------------------------------------------------
inline PropertyDescriptor::PropertyDescriptor()
: m_dataClassID(0)
, m_propertyClassID(0)
, m_propertyID(0)
, m_traits(0)
, m_updateGroups(0)
, m_pDefaultProperty(NULL)
{
}

//------------------------------------------------------------------------------------------------
inline PropertyDescriptor::PropertyDescriptor(const PropertyDescriptor& other)
: m_name(other.m_name)
, m_source(other.m_source)
, m_semanticType(other.m_semanticType)
, m_dataClassID(other.m_dataClassID)
, m_propertyClassID(other.m_propertyClassID)
, m_propertyID(other.m_propertyID)
, m_traits(other.m_traits)
, m_updateGroups(other.m_updateGroups)
, m_pDefaultProperty(NULL)
{
    if (other.m_pDefaultProperty)
    {
        m_pDefaultProperty = other.m_pDefaultProperty->Clone();
    }
}

//------------------------------------------------------------------------------------------------
inline PropertyDescriptor::~PropertyDescriptor()
{
    EE_DELETE m_pDefaultProperty;
    m_pDefaultProperty = NULL;
}


//------------------------------------------------------------------------------------------------
inline PropertyDescriptor& PropertyDescriptor::operator=(
    const PropertyDescriptor& other)
{
    m_name = other.m_name;
    m_source = other.m_source;
    m_dataClassID = other.m_dataClassID;
    m_propertyClassID = other.m_propertyClassID;
    m_propertyID = other.m_propertyID;
    m_traits = other.m_traits;
    m_semanticType = other.m_semanticType;
    m_updateGroups = other.m_updateGroups;

    if (other.m_pDefaultProperty)
    {
        m_pDefaultProperty = other.m_pDefaultProperty->Clone();
    }
    else
    {
        m_pDefaultProperty = NULL;
    }

    return *this;
}


//------------------------------------------------------------------------------------------------
inline efd::ClassID PropertyDescriptor::GetDataClassID() const
{
    return m_dataClassID;
}


//------------------------------------------------------------------------------------------------
inline void PropertyDescriptor::SetDataClassID(efd::ClassID classID)
{
    EE_ASSERT(NULL == m_pDefaultProperty);

    m_dataClassID = classID;
}


//------------------------------------------------------------------------------------------------
inline efd::ClassID PropertyDescriptor::GetPropertyClassID() const
{
    return m_propertyClassID;
}


//------------------------------------------------------------------------------------------------
inline void PropertyDescriptor::SetPropertyClassID(efd::ClassID classID)
{
    EE_ASSERT(NULL == m_pDefaultProperty);

    m_propertyClassID = classID;
}


//------------------------------------------------------------------------------------------------
inline PropertyID PropertyDescriptor::GetPropertyID() const
{
    return m_propertyID;
}


//------------------------------------------------------------------------------------------------
inline void PropertyDescriptor::SetPropertyID(PropertyID propID)
{
    m_propertyID = propID;
}


//------------------------------------------------------------------------------------------------
inline const efd::utf8string& PropertyDescriptor::GetName() const
{
    return m_name;
}


//------------------------------------------------------------------------------------------------
inline void PropertyDescriptor::SetName(const efd::utf8string& name)
{
    m_name = name;
}


//------------------------------------------------------------------------------------------------
inline efd::Bool PropertyDescriptor::GetTrait(PropertyTraits trait) const
{
    return efd::BitUtils::AllBitsAreSet(m_traits, (efd::UInt32)trait);
}


//------------------------------------------------------------------------------------------------
inline efd::UInt32 PropertyDescriptor::GetTraits() const
{
    return m_traits;
}


//------------------------------------------------------------------------------------------------
inline void PropertyDescriptor::SetTrait(PropertyTraits trait, efd::Bool val)
{
    m_traits = efd::BitUtils::SetBitsOnOrOff(m_traits, (efd::UInt32)trait, val);
    if (trait == PropertyTrait_Persisted)
    {
        SetUpdateGroup(PERSISTENCE_GROUP_INDEX, true);
    }
}


//------------------------------------------------------------------------------------------------
inline efd::UInt32 PropertyDescriptor::GetReplicationGroups() const
{
    return m_updateGroups & REPLICATION_GROUP_MASK;
}


//------------------------------------------------------------------------------------------------
inline const efd::utf8string& PropertyDescriptor::GetSemanticType() const
{
    return m_semanticType;
}


//------------------------------------------------------------------------------------------------
inline void PropertyDescriptor::SetSemanticType(
    const efd::utf8string& semanticType)
{
    m_semanticType = semanticType;
}


//------------------------------------------------------------------------------------------------
inline const efd::utf8string& PropertyDescriptor::GetSource() const
{
    return m_source;
}


//------------------------------------------------------------------------------------------------
inline void PropertyDescriptor::SetSource(const efd::utf8string& source)
{
    m_source = source;
}


//------------------------------------------------------------------------------------------------
inline const IProperty* PropertyDescriptor::GetDefaultProperty() const
{
    return m_pDefaultProperty;
}


//------------------------------------------------------------------------------------------------
inline efd::Bool PropertyDescriptor::GetUpdateGroup(efd::UInt32 index) const
{
    return efd::BitUtils::TestBitByIndex(m_updateGroups, index);
}


//------------------------------------------------------------------------------------------------
inline efd::UInt32 PropertyDescriptor::GetUpdateGroups() const
{
    return m_updateGroups;
}


//------------------------------------------------------------------------------------------------
inline void PropertyDescriptor::SetUpdateGroup(efd::UInt32 index, efd::Bool val)
{
    m_updateGroups = efd::BitUtils::SetBitOnOrOffByIndex(m_updateGroups, index, val);;
}

//------------------------------------------------------------------------------------------------
inline bool PropertyDescriptor::operator==(const PropertyDescriptor& other) const
{
    if (this == &other)
    {
        return true;
    }

    return m_dataClassID == other.m_dataClassID &&
           m_name == other.m_name &&
           m_propertyClassID == other.m_propertyClassID &&
           m_propertyID == other.m_propertyID &&
           m_semanticType == other.m_semanticType &&
           m_source == other.m_source &&
           m_traits == other.m_traits &&
           m_updateGroups == other.m_updateGroups &&
           *(m_pDefaultProperty) == *(other.m_pDefaultProperty);
}

}; // end namespace egf
