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


//--------------------------------------------------------------------------------------------------
template< typename T >
bool efd::EnumManager::FindEnumValue(
    const efd::utf8string& i_enumName,
    const efd::utf8string& i_itemName,
    T& o_value)
{
    efd::DataDrivenEnumBase* pEnum = FindEnum(i_enumName);
    if (pEnum)
    {
        efd::DataDrivenEnum<T>* pTypedEnum = pEnum->CastTo<T>();
        if (pTypedEnum)
        {
            return pTypedEnum->FindEnumValue(i_itemName, o_value);
        }
    }
    return false;
}

//--------------------------------------------------------------------------------------------------
template< typename T >
bool efd::EnumManager::FindOrLoadEnumValue(
    const efd::utf8string& i_enumName,
    const efd::utf8string& i_itemName,
    T& o_value)
{
    efd::DataDrivenEnumBase* pEnum = FindOrLoadEnum(i_enumName);
    if (pEnum)
    {
        efd::DataDrivenEnum<T>* pTypedEnum = pEnum->CastTo<T>();
        if (pTypedEnum)
        {
            return pTypedEnum->FindEnumValue(i_itemName, o_value);
        }
    }
    return false;
}

//--------------------------------------------------------------------------------------------------
template< typename T >
bool efd::EnumManager::FindEnumName(const efd::utf8string& i_enumName,
                                     const T& i_value,
                                     efd::utf8string& o_itemName)
{
    efd::DataDrivenEnumBase* pEnum = FindEnum(i_enumName);
    if (pEnum)
    {
        efd::DataDrivenEnum<T>* pTypedEnum = pEnum->CastTo<T>();
        if (pTypedEnum)
        {
            return pTypedEnum->FindEnumName(i_value, o_itemName);
        }
    }
    return false;
}

