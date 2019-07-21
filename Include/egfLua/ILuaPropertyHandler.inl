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
template<typename T>
inline egf::PropertyResult egf::ILuaPropertyHandler::GetPropertyHelper(
    egf::Entity* i_pEntity,
    egf::PropertyID i_pid,
    const efd::utf8string& i_key,
    T& o_result)
{
    if (i_key.empty())
    {
        return i_pEntity->GetPropertyValue(i_pid, o_result);
    }
    return i_pEntity->GetPropertyValue(i_pid, i_key, o_result);
}

//--------------------------------------------------------------------------------------------------
template<typename T>
inline egf::PropertyResult egf::ILuaPropertyHandler::GetDefaultPropertyHelper(
    egf::Entity* i_pEntity,
    egf::PropertyID i_pid,
    const efd::utf8string& i_key,
    T& o_result)
{
    if (i_key.empty())
    {
        return i_pEntity->GetDefaultPropertyValue(i_pid, o_result);
    }
    return i_pEntity->GetDefaultPropertyValue(i_pid, i_key, o_result);
}

//--------------------------------------------------------------------------------------------------
template<typename T>
inline egf::PropertyResult egf::ILuaPropertyHandler::SetPropertyHelper(
    egf::Entity* i_pEntity,
    egf::PropertyID i_pid,
    const efd::utf8string& i_key,
    const T& i_value)
{
    if (i_key.empty())
    {
        return i_pEntity->SetPropertyValue(i_pid, i_value);
    }
    return i_pEntity->SetPropertyValue(i_pid, i_key, i_value);
}

//--------------------------------------------------------------------------------------------------
