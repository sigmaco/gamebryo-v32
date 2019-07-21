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
#ifndef EE_HELPERS_H
#define EE_HELPERS_H

#include <efd/UniversalTypes.h>
#include <efd/efdLibType.h>

namespace efd
{
/// Function prototype used for assert handlers
typedef efd::SInt8 (*AssertHandler)(
    const char* pszFile,
    efd::SInt32 line,
    const char* pszFunction,
    const char* pszPred,
    const char* pszMsg,
    const char* pszStack,
    efd::Bool isAVerify);


/**
    The AssertHelper class is used to capture all the parameter information
    for an assert for later use
*/
class EE_EFD_ENTRY AssertHelper
{
public:
    /// Value returned by an assert handler to say the assert should be ignored
    /// for the rest of the applications execution.
    static const efd::SInt8 kIgnore = 2;

    /// Value returned by an assert handler to say the assert should be ignored
    /// this time only.
    static const efd::SInt8 kIgnoreOnce = 1;

    /// Value returned by an assert handler to invoke a debug break, core, etc...
    static const efd::SInt8 kDebugAbort = 0;

    /// This is a return value that is guaranteed never to be returned from DoAssert or DoVerify
    static const efd::SInt8 kInvalidReturn = (efd::SInt8)(-1);

    /**
        Passes the arguments from an assert statement to the logging system for output.  This
        is only called once we already know the assert has failed.

        @param pPredicate The string version of the assert predicate (expression that was
            asserted to be true).
        @param pFile The path and filename that the assert occurred in.
        @param line The line number the assert occurred at.
        @param pFunction The function the assert occurred in, if available
        @param pMessage Plain string for the assert statement, or NULL to use the predicate
            string as the message.
        @return Value to indicate how the assert should be handled
    */
    static efd::SInt8 DoAssert(
        const char* pPredicate,
        const char* pFile,
        efd::SInt32 line,
        const char* pFunction,
        const char* pMessage = NULL);

    /**
        Passes the arguments from a verify statement to the logging system for output.  This
        is only called once we already know the verify has failed.

        @param pPredicate The string version of the assert predicate (expression that was
            asserted to be true).
        @param pFile The path and filename that the assert occurred in.
        @param line The line number the assert occurred at.
        @param pFunction The function the assert occurred in.
        @param pMessage Plain string for the verify statement, or NULL to use the predicate
            string as the message.
        @return Value to indicate how the assert should be handled.
    */
    static efd::SInt8 DoVerify(
        const char* pPredicate,
        const char* pFile,
        efd::SInt32 line,
        const char* pFunction,
        const char* pMessage = NULL);

    /**
        Gets the assert handler for the application.

        @return The assert handler
    */
    static AssertHandler GetAssertHandler();

    /**
        Sets the assert handler for the application.

        @param handler The new assert handler to call
        @return The old assert handler
    */
    static AssertHandler SetAssertHandler(AssertHandler handler);

    /**
        An assert handler that prints a message but otherwise ignores the assert and
        attempts to continue.  Most commonly used in automated tests.
      */
    static efd::SInt8 IgnoringAssertHandler(
        const char* pFile,
        efd::SInt32 line,
        const char* pFunction,
        const char* pPredicate,
        const char* pMessage,
        const char* pStackTrace,
        efd::Bool isAVerify);

    /**
        An assert handler that logs the message and breaks
      */
    static efd::SInt8 StandardAssertHandler(
        const char* pFile,
        efd::SInt32 line,
        const char* pFunction,
        const char* pPredicate,
        const char* pMessage,
        const char* pStackTrace,
        efd::Bool isAVerify);
protected:
    /// Pointer to the assert handler function
    static AssertHandler ms_assertHandler;
    static bool ms_alreadyInDoAssert;
};


/**
    The PrintfHelper class is used to convert a macro parameter containing a printf-style format
    string and a list of arguments into a plain string.  The string is formatted into a fixed
    size buffer and the string will be truncated if required to fit into this buffer.

    @see EE_ASSERT_MESSAGE
*/
class EE_EFD_ENTRY PrintfHelper
{
public:
    /**
        Creates the PrintfHelper class and computes the result string.

        @param pszFormat Printf-style format string for the log statement
        @param ... Variable number of arguments like a printf statement.
    */
    PrintfHelper(const char* pszFormat, ...);

    /**
        Retrieve the formatted string.

        @return A buffer into which the formated string is written
    */
    inline operator const char*() const
    {
        return m_szBuffer;
    }

protected:
    /// A large fixed size buffer.  The formated string is placed in this buffer, truncating
    /// the string if needed.
    char m_szBuffer[1024];
};


/**
    The LogHelper class is used to convert a macro parameter containing a printf-style format
    string and a list of arguments into a plain string.  Unlike the PrintfHelper class this
    class uses an allocated variable size buffer into which the string is generated.

    @see EE_LOG
*/
class EE_EFD_ENTRY LogHelper
{
public:
    /**
        Creates the LogHelper class and computes the result string.

        @param pMessage Printf-style format string for the log statement
        @param ... Variable number of arguments like a printf statement.
    */
    LogHelper(const char* pMessage, ...);

    ///Destructor
    ~LogHelper();

    /**
        Retrieve the formatted string.

        @return The fully formated string
    */
    inline operator const char*() const
    {
        return m_pszBuffer;
    }

protected:
    /// An allocated character buffer to store the formatted string.  A raw buffer is used
    /// rather than an efd::utf8string or efd::String to avoid circular header dependencies.
    char* m_pszBuffer;

    /// A small fixed size buffer.  If the formated string is small enough this buffer is
    /// used to avoid performing an allocation.
    char m_szBuffer[124];
};

} // namespace efd

#endif // EE_HELPERS_H
