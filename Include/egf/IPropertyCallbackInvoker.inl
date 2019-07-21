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

//-------------------------------------------------------------------------------------------------
inline egf::IPropertyCallbackInvoker::IPropertyCallbackInvoker(
    efd::vector<IPropertyCallback*>*& pCallbackList)
    : m_pCallbacks(pCallbackList)
{
}
//-------------------------------------------------------------------------------------------------
inline egf::IPropertyCallbackInvoker::IPropertyCallbackInvoker(
    const egf::IPropertyCallbackInvoker& other)
    : m_pCallbacks(other.m_pCallbacks)
{
}
//-------------------------------------------------------------------------------------------------
inline egf::IPropertyCallbackInvoker& egf::IPropertyCallbackInvoker::operator=(
    const IPropertyCallbackInvoker& other)
{
    m_pCallbacks = other.m_pCallbacks;
    
    return *this;
}
//-------------------------------------------------------------------------------------------------
inline void egf::IPropertyCallbackInvoker::AddPropertyCallback(egf::IPropertyCallback* pCallback)
{
    m_pCallbacks->push_back(pCallback);
}

//-------------------------------------------------------------------------------------------------
inline void egf::IPropertyCallbackInvoker::RemovePropertyCallback(
    egf::IPropertyCallback* pCallback)
{
    efd::vector<egf::IPropertyCallback*>::iterator iter = m_pCallbacks->find(pCallback);
    if (iter != m_pCallbacks->end())
        m_pCallbacks->erase(iter);
}
    
//-------------------------------------------------------------------------------------------------
inline void egf::IPropertyCallbackInvoker::InvokeCallbacks(
    const egf::FlatModelID& modelID,
    egf::Entity* pEntity,
    const egf::PropertyID& propertyID,
    const egf::IProperty* pProperty,
    const efd::UInt32 tags,
    const egf::IPropertyCallback* ignore)
{
    efd::UInt32 count = m_pCallbacks->size();
    for (efd::UInt32 ui = 0; ui < count; ++ui)
    {
        IPropertyCallback* pCallback = (*m_pCallbacks)[ui];
        if (!ignore || (ignore != pCallback))
            pCallback->OnPropertyUpdate(modelID, pEntity, propertyID, pProperty, tags);
    }
}

