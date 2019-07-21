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

//-----------------------------------------------------------------------------------------------
template< typename T >
inline T* egmToolServices::SelectionService::GetAdapter() const
{
    SelectionAdapterPtr spAdapter;
    if (m_adapters.find(T::CLASS_ID, spAdapter))
        return (T*)static_cast<SelectionAdapter*>(spAdapter);

    return NULL;
}

//-----------------------------------------------------------------------------------------------
template< typename T >
inline bool egmToolServices::SelectionService::GetAdapter(T*& pAdapter) const
{
    SelectionAdapterPtr spAdapter;
    if (m_adapters.find(T::CLASS_ID, spAdapter))
    {
        pAdapter = (T*)static_cast<SelectionAdapter*>(spAdapter);
        return true;
    }

    pAdapter = NULL;
    return false;
}

//-----------------------------------------------------------------------------------------------
template< typename T >
inline void egmToolServices::SelectionService::AddAdapter(SelectionAdapter* pAdapter)
{
    m_adapters[T::CLASS_ID] = pAdapter;

    pAdapter->OnAdded();
}

//-----------------------------------------------------------------------------------------------
inline void egmToolServices::SelectionService::AddAdapter(SelectionAdapter* pAdapter)
{
    m_adapters[pAdapter->GetClassID()] = pAdapter;

    pAdapter->OnAdded();
}

//-----------------------------------------------------------------------------------------------
template< typename T >
inline void egmToolServices::SelectionService::RemoveAdapter(SelectionAdapter* pAdapter)
{
    pAdapter->OnRemoved();

    m_adapters.erase(T::CLASS_ID);
}

//-----------------------------------------------------------------------------------------------
inline void egmToolServices::SelectionService::RemoveAdapter(SelectionAdapter* pAdapter)
{
    pAdapter->OnRemoved();

    m_adapters.erase(pAdapter->GetClassID());
}

//------------------------------------------------------------------------------------------------
