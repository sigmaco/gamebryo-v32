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

#pragma once
#ifndef EE_THREADLOCAL_H
#define EE_THREADLOCAL_H

#include <efd/efdLibType.h>
#include <efd/UniversalTypes.h>
#include <efd/Asserts.h>
#include <efd/MemObject.h>

#if defined(EE_PLATFORM_PS3) || defined(EE_PLATFORM_LINUX)
#include <pthread.h>
#endif

namespace efd
{

/**
    A cross platform template class to support thread local storage.

    Normally all threads receive memory from the same allocation pool. Stack allocated memory is
    isolated to the containing instance. Global or static class member data, however, is associated
    with the class and share a common memory location across instances. In a multithreaded
    application this data can be accessed from multiple threads. Access to this data across
    multiple threads must be controlled in a thread-safe manner.

    There are times when its desirable to access data throughout a thread without having to worry
    about synchronization issues.

    Thread local storage provides a way to share data across an entire thread in a thread-safe
    manner. Static or global variables that use thread local storage are unique to the containing
    thread. TLS static or global variables are considered thread safe as each thread has its own
    unique copy of the data.

    An example declaring a static thread local variable of type MyClass:
    \verbatim
    static efd::ThreadLocal<MyClass> ms_threadLocalMyClass;
    \endverbatim

    Warning: Static initialization to a non zero value is not supported.
 */

template <typename ValueType>
class ThreadLocal
{
public:
    /// @name Construction and Destruction
    //@{
    ThreadLocal();
    ThreadLocal(const ValueType& object);
    ~ThreadLocal();
    //@}

    /**
        Return true if this instance is valid thread local storage. The meaning of 'valid' is
        platform specific.
    */
    inline bool IsValid() const;

    /// Implicit conversion to T.
    operator ValueType() const;

    /// Assignment operator.
    ThreadLocal& operator=(const ValueType& object);

private:

#if defined(EE_PLATFORM_WIN32) || defined(EE_PLATFORM_XBOX360)
    DWORD m_tlsHandle;
    typedef void* ThreadLocalReturnType;
#elif defined (EE_PLATFORM_PS3)
    pthread_key_t m_tlsHandle;
    static const pthread_key_t INVALID_KEY = 0xFFFFFFFF;
    typedef void* ThreadLocalReturnType;
#elif defined (EE_PLATFORM_LINUX)
    pthread_key_t m_tlsHandle;
    static const pthread_key_t INVALID_KEY = 0xFFFFFFFF;
    typedef void* ThreadLocalReturnType;
#endif

    union InternalTypeConverter
    {
        ThreadLocalReturnType m_internal;
        ValueType m_typed;
    };

};

//--------------------------------------------------------------------------------------------------

/// @def EE_DECLARE_STATIC_TLS_MEMBER
/// EE_DECLARE_STATIC_TLS_MEMBER(Type, Name) declares a static thread-local storage member.
/// The Type must have a constructor capable of taking 0 as an argument.  This macro is meant to be
/// paired with an EE_IMPLEMENT_STATIC_TLS_MEMBER invocation.  These macros provide a cross-platform
/// wrapper for the fastest (but not only*) way to make use of TLS.
///
/// * ThreadLocal<Type> also works on all platforms but may not be the fastest path.

/// @def EE_IMPLEMENT_STATIC_TLS_MEMBER
/// EE_IMPLEMENT_STATIC_TLS_MEMBER(Type, Name, Parent) defines the implementation of a thread-local
/// storage member that was declared in a class via EE_DECLARE_STATIC_TLS_MEMBER.

/// @def EE_DEFINE_STATIC_TLS
/// EE_DEFINE_STATIC_TLS(Type, Name) declares a thread-local storage member in global or namespace
/// global scope.

/// @def EE_IS_STATIC_TLS_VALID
/// EE_IS_STATIC_TLS_VALID(Ref) returns true/false with the same conditions as
/// ThreadLocal<T>::IsValid().


#if defined(EE_PLATFORM_PS3)

#define EE_TLS_PREFIX __thread

#elif defined(EE_PLATFORM_XBOX360)

#define EE_TLS_PREFIX __declspec(thread)

#endif


#if defined(EE_PLATFORM_PS3) || defined(EE_PLATFORM_XBOX360)

#define EE_DEFINE_STATIC_TLS(Type, Name) \
    static EE_TLS_PREFIX Type Name = 0

// pthread TLS internally uses a mutex, making __thread a better option
#define EE_DECLARE_STATIC_TLS_MEMBER(Type, Name) \
    static EE_TLS_PREFIX Type Name

#define EE_IMPLEMENT_STATIC_TLS_MEMBER(Type, Name, Parent) \
    EE_TLS_PREFIX Type Parent::Name = 0

#define EE_IS_STATIC_TLS_VALID(QualifiedName) \
    true

#else

#define EE_DEFINE_STATIC_TLS(Type, Name) \
    static efd::ThreadLocal<Type> Name = 0

#define EE_DECLARE_STATIC_TLS_MEMBER(Type, Name) \
    static efd::ThreadLocal<Type> Name

#define EE_IMPLEMENT_STATIC_TLS_MEMBER(Type, Name, Parent) \
    efd::ThreadLocal<Type> Parent::Name = 0

#define EE_IS_STATIC_TLS_VALID(Ref) \
    Ref.IsValid()

#endif

//--------------------------------------------------------------------------------------------------

#if defined (EE_PLATFORM_WIN32)
#include <efd/Win32/ThreadLocal_Win32.inl>
#elif defined (EE_PLATFORM_LINUX)
#include <efd/Linux/ThreadLocal_Linux.inl>
#elif defined (EE_PLATFORM_PS3)
#include <efd/PS3/ThreadLocal_PS3.inl>
#elif defined (EE_PLATFORM_XBOX360)
#include <efd/XBox360/ThreadLocal_XBox360.inl>
#endif

}

//--------------------------------------------------------------------------------------------------

#endif
