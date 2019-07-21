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
template<typename T>
inline void RefCountObject<T>::IncRefCount() const
{
    ++m_RefCount;
}

//-------------------------------------------------------------------------------------------------
template<typename T>
void RefCountObject<T>::DecRefCount() const
{
    if (--m_RefCount == 0)
    {
        DeleteThis();
    }
}

//-------------------------------------------------------------------------------------------------
template<typename T>
UInt32 RefCountObject<T>::GetRefCount() const
{
    return m_RefCount;
}

//-------------------------------------------------------------------------------------------------
template<typename T>
void RefCountObject<T>::DeleteThis() const
{
    EE_DELETE this;
}

//-------------------------------------------------------------------------------------------------
} // namespace efd
