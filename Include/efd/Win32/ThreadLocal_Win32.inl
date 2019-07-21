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
template <typename T> inline
ThreadLocal<T>::ThreadLocal()
{
    EE_COMPILETIME_ASSERT(sizeof(T) <= sizeof(ThreadLocalReturnType));
    m_tlsHandle = ::TlsAlloc();
}
//-------------------------------------------------------------------------------------------------
template <typename T> inline
ThreadLocal<T>::ThreadLocal(const T& object)
{
    EE_ASSERT(sizeof(T) <= sizeof(ThreadLocalReturnType));
    m_tlsHandle = ::TlsAlloc();
    *(this) = object;
}
//-------------------------------------------------------------------------------------------------
template <typename T> inline
ThreadLocal<T>::~ThreadLocal()
{
    if (IsValid())
        ::TlsFree(m_tlsHandle);
}
//-------------------------------------------------------------------------------------------------
template <typename T> inline
bool ThreadLocal<T>::IsValid() const
{
    return m_tlsHandle != TLS_OUT_OF_INDEXES;
}
//-------------------------------------------------------------------------------------------------
template <typename T> inline
ThreadLocal<T>::operator T() const
{
    EE_ASSERT(IsValid());
    InternalTypeConverter returnValue;
    returnValue.m_internal = ::TlsGetValue(m_tlsHandle);
    return returnValue.m_typed;
}
//-------------------------------------------------------------------------------------------------
template <typename T> inline
ThreadLocal<T>& ThreadLocal<T>::operator=(const T& object)
{
    EE_ASSERT(IsValid());
    InternalTypeConverter dest;
    dest.m_typed = object;
    ::TlsSetValue(m_tlsHandle, dest.m_internal);
    return *(this);
}
//-------------------------------------------------------------------------------------------------
