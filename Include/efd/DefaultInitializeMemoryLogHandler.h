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
#ifndef EE_DEFAULTINITIALIZEMEMORYLOGHANDLER_H
#define EE_DEFAULTINITIALIZEMEMORYLOGHANDLER_H

#include <efd/IMemLogHandler.h>

namespace efd
{
    /**
        Default implementation of the InitializeMemoryLogHandler() function.

        To use the default implementation in a statically linked application, invoke the macro
        EE_USE_DEFAULT_ALLOCATOR in a source file linked into the application.

        This implementation is always used in dynamically linked versions
        (see MemManager.cpp for more details).

        @return Pointer to an IMemLogHandler instance.
    */
    EE_EFD_ENTRY IMemLogHandler* CreateDefaultMemoryLogHandler();
} // end namespace efd

#define EE_USE_DEFAULT_MEMORY_LOG_HANDLER \
    EE_EFD_ENTRY efd::IMemLogHandler* efd::InitializeMemoryLogHandler() \
    { \
        return efd::CreateDefaultMemoryLogHandler(); \
    }

#endif // #ifndef EE_DEFAULTINITIALIZEMEMORYLOGHANDLER_H
