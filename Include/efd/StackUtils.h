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
#ifndef EE_StackTrace_h
#define EE_StackTrace_h

#include <efd/UniversalTypes.h>
#include <efd/efdLibType.h>


#if defined(EE_USE_MEMTRACKER_STACKTRACE) || defined(EE_USE_ASSERT_STACKTRACE) || defined(EE_USE_EXCEPTION_STACKTRACE)
    #if defined(EE_PLATFORM_WIN32) || defined(EE_PLATFORM_XBOX360)
/// @def EE_ENABLE_STACKTRACE
/// If defined, the various functions in the StackUtils namespace will be implemented.
        #define EE_ENABLE_STACKTRACE
    #endif
#endif


namespace efd
{
    namespace StackUtils
    {
        /**
            Initialize stack tracing.  On windows, this will attempt to load the DbgHelp.dll.
            As this method may allocate memory it should be called while your application is
            healthy if you later wish to use the ExceptionStackTrace method.  Otherwise this
            method will be automatically called when needed.

            @param enable true to enable stack tracing, false to disable.

            @return True if stack tracing is available, false otherwise.
        */
        EE_EFD_ENTRY bool EnableStackTracing(bool enable = true);

        /**
            Disable call stack tracing.  Some processes want stack tracing disabled even when
            its compiled it.
        */
        EE_EFD_ENTRY void TurnOffStackTracing();

        /**
            Walk the execution stack recording the instruction pointers.  These symbols are
            not resolved, just stored.  They can be resolved later if needed by calling either
            ResolveSymbolNames or NoAllocResolveSymbolNames.

            @param[out] o_pResults Pointer to an array where the results are stored
            @param[in] i_maxDepth The length of the array pointed to by o_pResults.  This limits
                the maximum depth the stack will be walked.
            @param[in] i_skipFrames The number of frame to skip on the top of the stack.  Used
                to bypass predictable frames like the stack trace method itself.
            @return The number of stack frames captured in o_pResults
        */
        EE_EFD_ENTRY efd::UInt32 FastStackTrace(void** o_pResults,
                                                 efd::UInt32 i_maxDepth,
                                                 efd::UInt32 i_skipFrames = 0);

        /**
            Walk the execution stack following the invocation of an exception handler recording
            the instruction pointers.  Attempts to correct the resulting stack for the effects
            of the exception handler.

            @param[out] o_pResults Pointer to an array where the results are stored
            @param[in] i_maxDepth The length of the array pointed to by o_pResults
            @param[in] i_pPlatform1 Platform specific data passed in from the exception record
            @param[in] i_pPlatform2 Platform specific data passed in from the exception record
            @return The number of stack frames captured in o_pResults
        */
        EE_EFD_ENTRY efd::UInt32 ExceptionStackTrace(void** o_pResults,
                                                      efd::UInt32 i_maxDepth,
                                                      void* i_pPlatform1 = NULL,
                                                      void* i_pPlatform2 = NULL);

        /**
            Walks the stack and provides a string with the resolved symbol names.

            @note Results will be truncated to fit within the provided buffer.  Resulting
            string is guaranteed to be null terminated.

            @param[in] i_maxDepth The maximum depth to recurse the stack
            @param[out] o_pszzResultBuffer The resolved symbols will be written into this buffer
                one per line.
            @param[in] i_cchBufferSize The length of the array pointed to by o_pchResultBuffer.
            @param[in] i_skipFrames The number of frame to skip on the top of the stack.  Used
                to bypass predictable frames like the stack trace method itself.
            @param[in] i_pszPrefix Prefix to prepend to each line of the result
            @return The number of lines in the result string
        */
        EE_EFD_ENTRY efd::UInt32 StackTrace(efd::UInt32 i_maxDepth,
                                             char* o_pszzResultBuffer,
                                             efd::UInt32 i_cchBufferSize,
                                             efd::UInt32 i_skipFrames = 0,
                                             const char* i_pszPrefix = "");

        /**
            Resolve function symbol names without allocating any memory.  By avoiding allocations
            this method is safer to call during exception handlers.  For increased safety you
            should have previously called the EnableStackTracing method while your application
            was healthy.

            @note Results will be truncated to fit within the provided buffer.  Resulting
            string is guaranteed to be null terminated.

            @param[in] i_pSymbols Pointer to an array of symbols previously returned from a call
                to the FastStackTrace or EnableStackTracing function.
            @param[in] i_cSymbols The length of the array pointed to by i_pSymbols
            @param[out] o_pszzResultBuffer The resolved symbols will be written into this buffer
                one per line.
            @param[in] i_cchBufferSize The length of the array pointed to by o_pchResultBuffer.
            @param[in] i_pszPrefix Prefix to prepend to each line of the result
            @return True if symbols were resolved.
        */
        EE_EFD_ENTRY bool ResolveSymbolNames(const void* const * i_pSymbols,
                                              efd::UInt32 i_cSymbols,
                                              char* o_pszzResultBuffer,
                                              efd::UInt32 i_cchBufferSize,
                                              const char* i_pszPrefix = "");


        /**
            Turn on or off an unhandled exception filter that will log the exception record,
            optionally log a stack trace if EE_USE_EXCEPTION_STACKTRACE was defined when foundation
            was compiled and then flush the logs. The handler will then forward the exception off
            to the default exception handler if possible. By default, EE_USE_EXCEPTION_STACKTRACE
            is defined for debug and release configurations.

            @param i_turnOn True to turn on the handler, false to turn it off.
        */
        EE_EFD_ENTRY void LogOnUnhandledException(bool i_turnOn);

    } // end namespace StackUtils
} // end namespace efd

#endif // EE_StackTrace_h
