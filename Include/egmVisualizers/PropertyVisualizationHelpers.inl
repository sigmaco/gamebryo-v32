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
template<class T>
inline egf::PropertyResult egmVisualizers::PropertyVisualizationHelpers::GetDependency(
    egf::ExtraDataPtr spExtraData,
    egf::Entity* pEntity,
    const efd::utf8string& dependency,
    const efd::utf8string& defaultProperty,
    T& o_value)
{
    egf::ExtraDataEntryPtr entry = spExtraData->GetEntry(dependency);
    efd::utf8string propertyName;

    if (!entry || entry->m_value == "Default")
        propertyName = defaultProperty;
    else
        propertyName = entry->m_value;

    egf::PropertyResult result = pEntity->GetPropertyValue(propertyName, o_value);
    return result;
}
//--------------------------------------------------------------------------------------------------
template<class T>
inline egf::PropertyResult egmVisualizers::PropertyVisualizationHelpers::GetAssocArrayDependency(
    egf::ExtraDataPtr spExtraData,
    egf::Entity* pEntity,
    const efd::utf8string& dependency,
    const efd::utf8string& defaultProperty,
    efd::map<efd::utf8string, T>& o_values)
{
    EE_ASSERT(pEntity);

    egf::ExtraDataEntryPtr entry = spExtraData->GetEntry(dependency);
    efd::utf8string propertyName;

    if (!entry || entry->m_value == "Default")
        propertyName = defaultProperty;
    else
        propertyName = entry->m_value;

    efd::list<efd::utf8string> keys;
    egf::PropertyResult result = pEntity->GetPropertyKeys(propertyName, keys);
    if (result != egf::PropertyResult_OK)
        return result;

    efd::map<efd::utf8string, T> tempValues;
    for (efd::list<efd::utf8string>::iterator
        itr = keys.begin();
        itr != keys.end();
        itr++)
    {
        T value;
        result = pEntity->GetPropertyValue(propertyName, *itr, value);
        if (result != egf::PropertyResult_OK)
            return result;

        tempValues[*itr] = value;
    }

    o_values = tempValues;

    return egf::PropertyResult_OK;
}
//--------------------------------------------------------------------------------------------------
