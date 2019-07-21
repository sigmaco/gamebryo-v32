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

#include <efd/ClassIDHelpers.h>
#include <efd/ParseHelper.h>
//--------------------------------------------------------------------------------------------------
efd::DataDrivenEnumBase::DataDrivenEnumBase(const efd::utf8string& i_name,
                                             efd::EnumType i_type,
                                             efd::ClassID i_storage)
: m_name(i_name)
, m_type(i_type)
, m_storage(i_storage)
{
}

//--------------------------------------------------------------------------------------------------
const efd::utf8string& efd::DataDrivenEnumBase::GetName() const
{
    return m_name;
}

//--------------------------------------------------------------------------------------------------
efd::EnumType efd::DataDrivenEnumBase::GetEnumType() const
{
    return m_type;
}

//--------------------------------------------------------------------------------------------------
efd::ClassID efd::DataDrivenEnumBase::GetStorageType() const
{
    return m_storage;
}

//--------------------------------------------------------------------------------------------------
template< typename T >
efd::DataDrivenEnum<T>* efd::DataDrivenEnumBase::CastTo()
{
    if (efd::GetClassIDFromType<T>() == GetStorageType())
    {
        return (efd::DataDrivenEnum<T>*)this;
    }
    return NULL;
}

//--------------------------------------------------------------------------------------------------
template< typename T >
const efd::DataDrivenEnum<T>* efd::DataDrivenEnumBase::CastTo() const
{
    if (efd::GetClassIDFromType<T>() == GetStorageType())
    {
        return (const efd::DataDrivenEnum<T>*)this;
    }
    return NULL;
}

//--------------------------------------------------------------------------------------------------
bool efd::DataDrivenEnumBase::HasBaseEnum() const
{
    return m_spParent != NULL;
}

//--------------------------------------------------------------------------------------------------
efd::DataDrivenEnumBase* efd::DataDrivenEnumBase::GetBaseEnum() const
{
    return m_spParent;
}

//--------------------------------------------------------------------------------------------------
template< typename T >
efd::DataDrivenEnum<T>::DataDrivenEnum(const efd::utf8string& i_name, efd::EnumType i_type)
: DataDrivenEnumBase(i_name, i_type, efd::GetClassIDFromType<T>())
, m_fUseInvalid(true)
, m_invalidName("INVALID")
, m_invalidValue(DefaultInvalidValue<T>())
{
}

//--------------------------------------------------------------------------------------------------
template< typename T >
efd::DataDrivenEnum<T>::DataDrivenEnum(const efd::utf8string& i_name,
                                        efd::DataDrivenEnum<T>* pParentEnum)
: DataDrivenEnumBase(i_name, pParentEnum->GetEnumType(), efd::GetClassIDFromType<T>())
, m_fUseInvalid(false)
{
    EE_ASSERT(pParentEnum);
    EE_ASSERT(pParentEnum->GetStorageType() == efd::GetClassIDFromType<T>());
    m_spParent = pParentEnum;
}

//--------------------------------------------------------------------------------------------------
template< typename T >
bool efd::DataDrivenEnum<T>::FindEnumValue(const efd::utf8string& i_name, T& o_value)
{
    typename efd::map< efd::utf8string, T >::iterator iter = m_nameToValue.find(i_name);
    if (iter != m_nameToValue.end())
    {
        o_value = iter->second;
        return true;
    }
    if (GetBaseEnum())
    {
        return GetBaseEnum()->FindEnumValue(i_name, o_value);
    }
    return false;
}

//--------------------------------------------------------------------------------------------------
template< typename T >
bool efd::DataDrivenEnum<T>::FindEnumName(const T& i_value, efd::utf8string& o_name)
{
    typename efd::map< T, efd::utf8string >::iterator iter = m_valueToName.find(i_value);
    if (iter != m_valueToName.end())
    {
        o_name = iter->second;
        return true;
    }
    if (GetBaseEnum())
    {
        return GetBaseEnum()->FindEnumName(i_value, o_name);
    }
    return false;
}

//--------------------------------------------------------------------------------------------------
template< typename T >
T efd::DataDrivenEnum<T>::GetEnumValue(const efd::utf8string& i_name)
{
    typename efd::map< efd::utf8string, T >::iterator iter = m_nameToValue.find(i_name);
    if (iter != m_nameToValue.end())
    {
        return iter->second;
    }
    if (GetBaseEnum())
    {
        return GetBaseEnum()->GetEnumValue(i_name);
    }
    return m_invalidValue;
}

//--------------------------------------------------------------------------------------------------
template< typename T >
efd::utf8string efd::DataDrivenEnum<T>::GetEnumName(const T& i_value)
{
    typename efd::map< T, efd::utf8string >::iterator iter = m_valueToName.find(i_value);
    if (iter != m_valueToName.end())
    {
        return iter->second;
    }
    if (GetBaseEnum())
    {
        return GetBaseEnum()->GetEnumName(i_value);
    }

    // Value not found, build a default value instead:
    efd::utf8string strValue("???");
    efd::ParseHelper<T>::ToString(i_value, strValue);

    efd::utf8string result(efd::Formatted, "%s(%s)", GetName().c_str(), strValue.c_str());
    return result;
}

//--------------------------------------------------------------------------------------------------
template< typename T >
bool efd::DataDrivenEnum<T>::HasName(const efd::utf8string& i_name) const
{
    typename efd::map< efd::utf8string, T >::const_iterator iter = m_nameToValue.find(i_name);
    if (iter != m_nameToValue.end())
    {
        return true;
    }
    if (GetBaseEnum())
    {
        return GetBaseEnum()->HasName(i_name);
    }
    return false;
}

//--------------------------------------------------------------------------------------------------
template< typename T >
bool efd::DataDrivenEnum<T>::HasValue(const T& i_value) const
{
    typename efd::map< T, efd::utf8string >::const_iterator  iter = m_valueToName.find(i_value);
    if (iter != m_valueToName.end())
    {
        return true;
    }
    if (GetBaseEnum())
    {
        return GetBaseEnum()->HasValue(i_value);
    }
    return false;
}

//--------------------------------------------------------------------------------------------------
template< typename T >
efd::DataDrivenEnum<T>* efd::DataDrivenEnum<T>::GetBaseEnum() const
{
    // NOTE: a hard cast is ok here since the only way to set the parent is via the constructor
    // which only takes a properly typed value.
    return static_cast<efd::DataDrivenEnum<T>*>(m_spParent.data());
}

