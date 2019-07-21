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
#ifndef EE_PHYSXUSEROUTPUT_H
#define EE_PHYSXUSEROUTPUT_H

#include <efdPhysX/efdPhysXLibType.h>

#include <efd/MemObject.h>

#if defined(EE_PLATFORM_WIN32) || defined(EE_PLATFORM_XBOX360)
#pragma warning(push)
#pragma warning(disable: 4100) // unreferenced formal parameter
#pragma warning(disable: 4512) // assignment operator could not be generated
#pragma warning(disable: 4244) // conversion from 'type' to 'type', possible loss of data
#pragma warning(disable: 4245) // conversion from 'type' to 'type', signed/unsigned mismatch
#elif defined(EE_PLATFORM_PS3)
#pragma GCC system_header
#endif
#include <NxPhysics.h>
#if defined(EE_PLATFORM_WIN32) || defined(EE_PLATFORM_XBOX360)
#pragma warning(pop)
#endif

#if defined(EE_PLATFORM_WIN32)
#pragma warning(push)
#pragma warning(disable: 4275) // DLL export warning due to PhysX
#endif

namespace efdPhysX {

/**
    This class implements the PhysX's NxUserOutputStream interface with
    Emergent Foundation's various debug output and assertion macros.

    If no alternative is explicitly passed to efdPhysX::PhysXSDKManager::Initialize
    then an instance of this class is created and passed to the PhysX SDK
    initialization function. Users wishing to override this behavior should
    create their own class that implements NxUserOutputStream and pass it to
    efdPhysX::PhysXSDKManager::Initialize.
*/
class EE_EFDPHYSX_ENTRY PhysXUserOutput : public NxUserOutputStream, public efd::MemObject
{
public:

    /// Constructs a string from the given information and passes it to EE_LOG_AT.
    virtual void reportError(NxErrorCode code, const char *message, const char *file, int line);

    /**
        Constructs a string from the given information and passes it to EE_FAIL_MESSAGE_AT,
        and then asserts.

        This behavior mimics the PhysX default output stream.
    */
    virtual NxAssertResponse reportAssertViolation (const char *message,
        const char *file, int line);

    /// Passes the message directly to EE_LOG.
    virtual void print(const char *message);
};

} // namespace

#if defined (WIN32)
#pragma warning(pop)
#endif

#endif  // #ifndef EE_PHYSXUSEROUTPUT_H

