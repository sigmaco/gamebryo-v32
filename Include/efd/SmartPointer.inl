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

//------------------------------------------------------------------------------------------------
template <class T>
EE_FORCEINLINE SmartPointer<T>::SmartPointer(T* pObject)
    : m_pObject(pObject)
{
    if (m_pObject)
        m_pObject->IncRefCount();
}

//------------------------------------------------------------------------------------------------
template <class T>
EE_FORCEINLINE SmartPointer<T>::SmartPointer(const SmartPointer& ptr)
    : m_pObject(ptr.m_pObject)
{
    if (m_pObject)
        m_pObject->IncRefCount();
}

//------------------------------------------------------------------------------------------------
template <class T>
EE_FORCEINLINE SmartPointer<T>::~SmartPointer()
{
    if (m_pObject)
        m_pObject->DecRefCount();
}

//------------------------------------------------------------------------------------------------
template <class T>
EE_FORCEINLINE SmartPointer<T>::operator T*() const
{
    return m_pObject;
}

//------------------------------------------------------------------------------------------------
template <class T>
EE_FORCEINLINE T* SmartPointer<T>::data() const
{
    return m_pObject;
}


//------------------------------------------------------------------------------------------------
template <class T>
EE_FORCEINLINE T& SmartPointer<T>::operator*() const
{
    return *m_pObject;
}

//------------------------------------------------------------------------------------------------
template <class T>
EE_FORCEINLINE T* SmartPointer<T>::operator->() const
{
    return m_pObject;
}

//------------------------------------------------------------------------------------------------
template <class T>
EE_FORCEINLINE SmartPointer<T>& SmartPointer<T>::operator=(const SmartPointer& ptr)
{
    if (m_pObject != ptr.m_pObject)
    {
        if (m_pObject)
            m_pObject->DecRefCount();
        m_pObject = ptr.m_pObject;
        if (m_pObject)
            m_pObject->IncRefCount();
    }
    return *this;
}

//------------------------------------------------------------------------------------------------
template <class T>
EE_FORCEINLINE SmartPointer<T>& SmartPointer<T>::operator=(T* pObject)
{
    if (m_pObject != pObject)
    {
        if (m_pObject)
            m_pObject->DecRefCount();
        m_pObject = pObject;
        if (m_pObject)
            m_pObject->IncRefCount();
    }
    return *this;
}

//------------------------------------------------------------------------------------------------
template <class T>
EE_FORCEINLINE bool SmartPointer<T>::operator==(T* pObject) const
{
    return (m_pObject == pObject);
}

//------------------------------------------------------------------------------------------------
template <class T>
EE_FORCEINLINE bool SmartPointer<T>::operator!=(T* pObject) const
{
    return (m_pObject != pObject);
}

//------------------------------------------------------------------------------------------------
template <class T>
EE_FORCEINLINE bool SmartPointer<T>::operator==(const SmartPointer& ptr) const
{
    return (m_pObject == ptr.m_pObject);
}

//------------------------------------------------------------------------------------------------
template <class T>
EE_FORCEINLINE bool SmartPointer<T>::operator!=(const SmartPointer& ptr) const
{
    return (m_pObject != ptr.m_pObject);
}

//------------------------------------------------------------------------------------------------
template <class T>
EE_FORCEINLINE bool SmartPointer<T>::operator<(T* pObject) const
{
    return (m_pObject < pObject);
}

//------------------------------------------------------------------------------------------------
template <class T>
EE_FORCEINLINE bool SmartPointer<T>::operator>(T* pObject) const
{
    return (m_pObject > pObject);
}

//------------------------------------------------------------------------------------------------
template <class T>
EE_FORCEINLINE bool SmartPointer<T>::operator<(const SmartPointer& ptr) const
{
    return (m_pObject < ptr.m_pObject);
}

//------------------------------------------------------------------------------------------------
template <class T>
EE_FORCEINLINE bool SmartPointer<T>::operator>(const SmartPointer& ptr) const
{
    return (m_pObject > ptr.m_pObject);
}

//------------------------------------------------------------------------------------------------
template <class T>
EE_FORCEINLINE void SmartPointer<T>::Swap(SmartPointer& otherPtr)
{
    T* pTemporary = m_pObject;
    m_pObject = otherPtr.m_pObject;
    otherPtr.m_pObject = pTemporary;
}

//------------------------------------------------------------------------------------------------
} // end namespace efd

