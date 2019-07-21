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


namespace efd
{

//-------------------------------------------------------------------------------------------------
template<typename T, typename KEY>
template<typename TConcrete>
inline T GenericFactory<T, KEY>::GenerateFactoryMethod()
{
    return EE_NEW TConcrete();
}

//-------------------------------------------------------------------------------------------------
template<typename T, typename KEY>
template<typename TConcrete>
inline void GenericFactory<T, KEY>::RegisterDefaultFactoryMethod(KEY classID)
{
    RegisterFactoryMethod(classID, GenerateFactoryMethod<TConcrete>);
}


//-------------------------------------------------------------------------------------------------
template<typename T, typename KEY>
inline T GenericFactory<T, KEY>::CreateObject(KEY classID) const
{
    typename FactoryMap::const_iterator itr = m_factoryMap.find(classID);

    if (itr == m_factoryMap.end())
    {
        // Should log this failure
        return NULL;
    }

    // create the concrete object and return it
    FactoryMethod* pFactoryMethod = itr->second;
    return pFactoryMethod();
}


//-------------------------------------------------------------------------------------------------
template<typename T, typename KEY>
inline void GenericFactory<T, KEY>::RegisterFactoryMethod(
    KEY classID,
    FactoryMethod* pMethod)
{
    m_factoryMap[classID] = pMethod;
}


//-------------------------------------------------------------------------------------------------
template<typename T, typename KEY>
inline void GenericFactory<T, KEY>::UnregisterFactoryMethod(KEY classID)
{
    m_factoryMap.erase(classID);
}


//-------------------------------------------------------------------------------------------------
} // end namespace efd

