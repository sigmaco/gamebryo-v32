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
#ifndef EE_LOGGERMACROS_H
#define EE_LOGGERMACROS_H


/// Define EE_DISABLE_LOGGING to disable logging completely.
//#define EE_DISABLE_LOGGING

#if !defined(EE_DISABLE_LOGGING)

    /**
        @def EE_LOG_AT
        Macro to log a message and record the module, level, file, and line number information.
        @note This version is rarely used, use EE_LOG instead to automatically use the current
        file and line number.  This version is used in the rare case where you wish to log a
        message from an external source that provides internal file and line number information.
    */
    #define EE_LOG_AT(module, level, args, file, line)                                  \
    {                                                                                   \
        if (efd::GetLogger()->IsLogging(module, level))                                 \
            efd::GetLogger()->Log(                                                   \
                module,                                                                 \
                level,                                                                  \
                file,                                                                   \
                line,                                                                   \
                efd::LogHelper args);                                                  \
    }

    /**
        @def EE_LOG
        Macro to log a message and record the module, level, file, and line number information.
        @param module module name
        @param level log level
        @param args message to log
    */
    #define EE_LOG(module, level, args) EE_LOG_AT(module, level, args, __FILE__, __LINE__)

    /**
        @def EE_LOG_ONCE
        Macro to log a message only once while recording the module, level, file, and line number
        information. This version prevents a log from filling up with duplicate messages.
    */
    #define EE_LOG_ONCE(module, level, args)                                            \
    {                                                                                   \
        static efd::Bool ignore_log = false;                                            \
        if (!ignore_log)                                                                \
        {                                                                               \
            if (efd::GetLogger()->IsLogging(module, level))                             \
            {                                                                           \
                efd::GetLogger()->Log(                                               \
                    module,                                                             \
                    level,                                                              \
                    __FILE__,                                                           \
                    __LINE__,                                                           \
                    efd::LogHelper args);                                              \
                ignore_log = true;                                                      \
            }                                                                           \
        }                                                                               \
    }

#else // !defined(EE_DISABLE_LOGGING)

    #define EE_LOG_AT(module, level, args, file, line) (void)false
    #define EE_LOG(module, level, args) (void)false
    #define EE_LOG_ONCE(module, level, args) (void)false

#endif // !defined(EE_DISABLE_LOGGING)



//--------------------------------------------------------------------------------------------------
// Routines that return information to user/programmer
//--------------------------------------------------------------------------------------------------
#if !defined(REPLACE_NIOUTPUTDEBUGSTRING_WITH_NILOG)
#    if defined(EE_PLATFORM_WIN32) || defined(EE_PLATFORM_XBOX360)

inline void EE_DO_OUTPUT_DEBUG_STRING(const efd::Char* pText)
{
    OutputDebugStringA(pText != NULL ? pText : "(NULL)");
}

#    elif defined (EE_PLATFORM_PS3) || defined(EE_PLATFORM_LINUX)
#        define EE_DO_OUTPUT_DEBUG_STRING(x)    printf("%s", x)
#    endif
#else //#if !defined(REPLACE_NIOUTPUTDEBUGSTRING_WITH_NILOG)
#    define EE_DO_OUTPUT_DEBUG_STRING(x)        NILOG(x)
#endif

#if defined(EE_EFD_CONFIG_DEBUG)
    inline void WriteToStdErr(const efd::Char* pText);
#   define EE_OUTPUT_DEBUG_STRING(x)    EE_DO_OUTPUT_DEBUG_STRING(x)
#else //#if defined(EE_EFD_CONFIG_DEBUG)
#   define WriteToStdErr(x) ((void)0)
#   define EE_OUTPUT_DEBUG_STRING(x) ((void)0)
#endif //#if defined(EE_EFD_CONFIG_DEBUG)


#endif // EE_LOGGERMACROS_H

