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
#ifndef EE_ASSERTS_H
#define EE_ASSERTS_H

#include <efd/UniversalTypes.h>
//#include <stdio.h>
#include <efd/Helpers.h>

#ifdef EE_PLATFORM_LINUX
    #include <signal.h>
#endif

/// Define EE_DISABLE_ASSERTS to disable asserts completely
// #define EE_DISABLE_ASSERTS
/// Define EE_ENABLE_RELEASE_ASSERT to enable asserts in release mode
// #define EE_ENABLE_RELEASE_ASSERT

// The following define is controlled by EE_DISABLE_ASSERTS and EE_ENABLE_RELEASE_ASSERT,
// it should never be set directly, only used to indicate that EE asserts are enabled
#if !defined(EE_DISABLE_ASSERTS) \
    && (defined(EE_EFD_CONFIG_DEBUG) || defined(EE_ENABLE_RELEASE_ASSERT))
    #define EE_ASSERTS_ARE_ENABLED
#else
    #undef EE_ASSERTS_ARE_ENABLED
#endif


//--------------------------------------------------------------------------------------------------
#if defined(EE_PLATFORM_PS3)
    #if defined(__SPU__)
        #define EE_DEBUG_BREAK() __asm__ volatile("stopd 0,1,1")
        #undef EE_SUPPORTS_FRIENDLY_VERIFY
    #elif defined(__GNUC__)
        #define EE_DEBUG_BREAK() __extension__ ({__asm__ volatile("tw 31,1,1");})

        // The (0==1) construct will cause warnings on EE_VERIFYEQUALS not used in an if statement
        #undef EE_SUPPORTS_FRIENDLY_VERIFY
    #else
        // SNC provides a more useful intrinsic for tw 31,1,1
        #define EE_DEBUG_BREAK() __builtin_snpause
        #define EE_SUPPORTS_FRIENDLY_VERIFY
    #endif
    #define EE_TEST_IGNORE_ASSERT                                                       \
        static efd::SInt8 ignore_assert = efd::AssertHelper::kDebugAbort;               \
        if (ignore_assert != efd::AssertHelper::kIgnore)
#elif defined(EE_PLATFORM_WIN32)
    /// @def EE_DEBUG_BREAK
    /// Causes the debugger to break into the code at the point wherever it is called.
    /// This will be defined as needed on different platforms
    // DT20085 This still brings up the MS default crash dialog, can we go direct to the debugger?
    #define EE_DEBUG_BREAK() __debugbreak()
    #define EE_SUPPORTS_FRIENDLY_VERIFY
    #define EE_TEST_IGNORE_ASSERT                                                       \
        static efd::SInt8 ignore_assert = efd::AssertHelper::kDebugAbort;               \
        if (ignore_assert != efd::AssertHelper::kIgnore)
#elif defined(EE_PLATFORM_XBOX360)
    #define EE_DEBUG_BREAK() __debugbreak()
    #define EE_SUPPORTS_FRIENDLY_VERIFY
    #define EE_TEST_IGNORE_ASSERT                                                       \
        static efd::SInt8 ignore_assert = efd::AssertHelper::kDebugAbort;               \
        if (ignore_assert != efd::AssertHelper::kIgnore)
#elif defined (EE_PLATFORM_LINUX)
    #define EE_DEBUG_BREAK() raise(SIGABRT)
    // EE_SUPPORTS_FRIENDLY_VERIFY is disabled on Linux because it causes build warnings.
    #undef EE_SUPPORTS_FRIENDLY_VERIFY
    #define EE_TEST_IGNORE_ASSERT                                                       \
        static efd::SInt8 ignore_assert = efd::AssertHelper::kDebugAbort;               \
        if (ignore_assert != efd::AssertHelper::kIgnore)
#else
    #error Platform undefined.
#endif

//--------------------------------------------------------------------------------------------------

#if defined(EE_ASSERTS_ARE_ENABLED) && !defined(__SPU__)

//--------------------------------------------------------------------------------------------------
// Asserts enabled
//--------------------------------------------------------------------------------------------------

    /**
        @def EE_ASSERT

        Asserts a predicate and if the assert fails it then calls the assert helper so that it
        can log the result and/or display a dialog (if graphical and configured to do so).  If
        the AssertHelper returns a "ignore" then the assert will be ignored (assert is not
        called). AssertHelper will return kIgnoreOnce (2) to skip the assert only this time.
        AssertHelper will return kIgnore (1) if the assert should be ignored for the rest of
        the execution and it will only be logged the first time in that case.

        @param pred The predicate to assert is true
    */
    #define EE_ASSERT(pred)                                                             \
    {                                                                                   \
        EE_TEST_IGNORE_ASSERT                                                           \
        {                                                                               \
            bool predicatePassed = (pred) != 0;                                         \
            if (!predicatePassed)                                                       \
            {                                                                           \
                ignore_assert = efd::AssertHelper::DoAssert(                            \
                    #pred,                                                              \
                    __FILE__,                                                           \
                    __LINE__,                                                           \
                    __FUNCTION__);                                                      \
                if (ignore_assert == efd::AssertHelper::kDebugAbort)                    \
                    EE_DEBUG_BREAK();                                                   \
            }                                                                           \
        }                                                                               \
    }


    /**
        @def EE_ASSERT_MESSAGE

        Asserts a predicate and if the assert fails it then calls the assert helper so that it
        can log the result and/or display a dialog (if graphical and configured to do so).  If
        the AssertHelper returns a "ignore" then the assert will be ignored (assert is not
        called). AssertHelper will return kIgnoreOnce (2) to skip the assert only this time.
        AssertHelper will return kIgnore (1) if the assert should be ignored for the rest of
        the execution and it will only be logged the first time in that case.

        @param pred The predicate to assert is true.
        @param messageAndArgs A () enclosed message with optional arguments in a printf style.
    */
    #define EE_ASSERT_MESSAGE(pred, messageAndArgs)                                     \
    {                                                                                   \
        EE_TEST_IGNORE_ASSERT                                                           \
        {                                                                               \
            bool predicatePassed = (pred) != 0;                                         \
            if (!predicatePassed)                                                       \
            {                                                                           \
                ignore_assert = efd::AssertHelper::DoAssert(                            \
                    #pred,                                                              \
                    __FILE__,                                                           \
                    __LINE__,                                                           \
                    __FUNCTION__,                                                       \
                    efd::PrintfHelper messageAndArgs);                                  \
                if (ignore_assert == efd::AssertHelper::kDebugAbort)                    \
                    EE_DEBUG_BREAK();                                                   \
            }                                                                           \
        }                                                                               \
    }

#if defined(EE_SUPPORTS_FRIENDLY_VERIFY)
    /// Helper for implementing EE_VERIFY* macros.  Do not use directly.
    #define EE_FAILEDVERIFY(msg) \
        ((efd::AssertHelper::DoVerify(msg, __FILE__, __LINE__, __FUNCTION__) == \
        efd::AssertHelper::kDebugAbort) ? \
        ((EE_DEBUG_BREAK()), (0 == 1)) : false)

    /// Helper for implementing EE_VERIFY_MESSAGE macro.  Do not use directly.
    #define EE_FAILEDVERIFY_MSG(pred, messageAndArgs) \
        ((efd::AssertHelper::DoVerify(#pred, __FILE__, __LINE__, __FUNCTION__, \
        efd::PrintfHelper messageAndArgs) \
        == efd::AssertHelper::kDebugAbort) ? ((EE_DEBUG_BREAK()), (0 == 1)) : false)

#else
    /// Helper for implementing EE_VERIFY* macros.  Do not use directly.
    #define EE_FAILEDVERIFY(msg) \
        (efd::AssertHelper::DoVerify(msg, __FILE__, __LINE__, __FUNCTION__) == \
        efd::AssertHelper::kInvalidReturn)

    /// Helper for implementing EE_VERIFY_MESSAGE macro.  Do not use directly.
    #define EE_FAILEDVERIFY_MSG(pred, messageAndArgs) \
        (efd::AssertHelper::DoVerify(#pred, __FILE__, __LINE__, __FUNCTION__, \
        efd::PrintfHelper messageAndArgs) \
        == efd::AssertHelper::kInvalidReturn)

#endif

    /**
        @def EE_VERIFY

        Verifies a predicate and if it fails it then calls the assert helper so that it can log
        the result and/or display a dialog (if graphical and configured to do so).  Even when
        asserts are disabled this will always evaluate the predicate.

        @note This is structured so that it can be used inline (such as in an if statement).
        @note On some platforms the resulting debug break point, should the verify fail, will be
        inside the AssertHelper::DoVerify.  Those platforms that support it will break at the
        location of the verify statement.

        @param predicate The predicate to assert is true.
    */
    #define EE_VERIFY(predicate) \
    ((predicate) ? true : EE_FAILEDVERIFY(#predicate))

    /**
        @def EE_VERIFYEQUALS

        Ensures the computed equals the verified value and if it fails it then calls the assert
        helper so that it can log the result and/or display a dialog (if graphical and configured
        to do so).  Even when asserts are disabled this will always evaluate the "computed"
        parameter.

        @note This is structured so that it can be used inline (such as in an if statement).
        @note On some platforms the resulting debug break point, should the verify fail, will be
        inside the AssertHelper::DoVerify.  Those platforms that support it will break at the
        location of the verify statement.
        @note When asserts are disabled the "verified" parameter is NOT evaluated.  The value
        passed to this parameter must not have any side effects.

        @param computed The value computed by the application.
        @param verified The desired value to verify the computed value against.
    */
    #define EE_VERIFYEQUALS(computed, verified)                                         \
    ((computed) == (verified) ? true : EE_FAILEDVERIFY(#computed " == " #verified))


    /**
        Ensures the computed does not equal the verified value and if it fails it then calls
        the assert helper so that it can log the result and/or display a dialog (if graphical
        and configured to do so).  Even when asserts are disabled this will always evaluate
        the "computed" parameter.

        @note This is structured so that it can be used inline (such as in an if statement).
        @note On some platforms the resulting debug break point, should the verify fail, will be
        inside the AssertHelper::DoVerify.  Those platforms that support it will break at the
        location of the verify statement.
        @note When asserts are disabled the "verified" parameter is NOT evaluated.  The value
        passed to this parameter must not have any side effects.

        @param computed The value computed by the application.
        @param verified The desired value to verify the computed value against.
    */
    #define EE_VERIFY_NOT_EQUAL(computed, verified)                                     \
    ((computed) != (verified) ? true : EE_FAILEDVERIFY(#computed " != " #verified))

    /**
        @def EE_VERIFY_MESSAGE

        Verifies a predicate and if it fails it then calls the assert helper so that it can log
        the result and/or display a dialog (if graphical and configured to do so).  Even when
        asserts are disabled this will always evaluate the predicate.

        @note This is structured so that it can be used inline (such as in an if statement).
        @note On some platforms the resulting debug break point, should the verify fail, will be
        inside the AssertHelper::DoVerify.  Those platforms that support it will break at the
        location of the verify statement.

        Sample usage:
        @code
            // notice the extra parens around the message and arguments:
            if (EE_VERIFY_MESSAGE(result != value,
                ("Invalid result, %d != expected value %d", result, value)))
            {
                // error handling here...
            }
        @endcode

        @param pred The predicate to assert is true.
        @param messageAndArgs A () enclosed message with optional arguments in
            a printf style.
    */
    #define EE_VERIFY_MESSAGE(predicate, messageAndArgs)                                \
    ((predicate) != 0 ? true : EE_FAILEDVERIFY_MSG(predicate,  messageAndArgs))


    /**
        @def EE_FAIL_AT

        Indicates that a failure condition has been reached.  Place in sections of code that
        should be unreachable under expected conditions.

        @note This macro should rarely be used; typically you should use EE_FAIL which will
        automatically supply the current file and line number.

        @param msg The text to log describing the failure.
        @param file The source file containing the assert.
        @param line The line number within the source file containing the assert.
    */
    #define EE_FAIL_AT(msg, file, line, function)                                       \
    {                                                                                   \
        EE_TEST_IGNORE_ASSERT                                                           \
        {                                                                               \
            ignore_assert = efd::AssertHelper::DoAssert(                                \
                msg,                                                                    \
                file,                                                                   \
                line,                                                                   \
                function);                                                              \
            if (ignore_assert == efd::AssertHelper::kDebugAbort)                        \
                EE_DEBUG_BREAK();                                                       \
        }                                                                               \
    }

    /**
        @def EE_FAIL

        Indicates that a failure condition has been reached.  Place in sections of code that
        should be unreachable under expected conditions.  This is roughly equivalent to:
        @code
            EE_ASSERT_MESSAGE(false, (msg))
        @endcode

        @param msg The plain text to log describing the failure.
    */
    #define EE_FAIL(msg)  EE_FAIL_AT(msg, __FILE__, __LINE__, __FUNCTION__)

    /**
        @def EE_FAIL_MESSAGE_AT

        Indicates that a failure condition has been reached.  Place in sections of code that
        should be unreachable under expected conditions.  Unlike EE_FAIL this version accepts
        a printf-style format string with arguments as the message parameter.

        @param messageAndArgs A printf-style format string with arguments.
    */
    #define EE_FAIL_MESSAGE_AT(messageAndArgs, file, line, function)                    \
    {                                                                                   \
        EE_TEST_IGNORE_ASSERT                                                           \
        {                                                                               \
            ignore_assert = efd::AssertHelper::DoAssert(                                \
                "EE_FAIL_MESSAGE",                                                      \
                file,                                                                   \
                line,                                                                   \
                function,                                                               \
                efd::PrintfHelper messageAndArgs);                                      \
            if (ignore_assert == efd::AssertHelper::kDebugAbort)                        \
                EE_DEBUG_BREAK();                                                       \
        }                                                                               \
    }

    /**
        @def EE_FAIL_MESSAGE

        Indicates that a failure condition has been reached.  Place in sections of code that
        should be unreachable under expected conditions.  Unlike EE_FAIL this version accepts
        a printf-style format string with arguments as the message parameter.  This is roughly
        equivalent to:
        @code
            EE_ASSERT_MESSAGE(false, messageAndArgs)
        @endcode

        @param messageAndArgs A printf-style format string with arguments.
    */
    #define EE_FAIL_MESSAGE(messageAndArgs) \
        EE_FAIL_MESSAGE_AT(messageAndArgs, __FILE__, __LINE__, __FUNCTION__)

#elif defined(EE_ASSERTS_ARE_ENABLED) && defined(__SPU__)

    //---------------------------------------------------------------------------------------------
    // Asserts enabled on SPU
    //---------------------------------------------------------------------------------------------

    // Causes a break in debugger, function always returns false
    inline bool EEDebugBreakProc() { EE_DEBUG_BREAK(); return false; }

    #define EE_ASSERT(pred) \
        ((pred) ? true : EEDebugBreakProc())

    #define EE_ASSERT_MESSAGE(pred, messageAndArgs) \
        ((pred) ? true : EEDebugBreakProc())

    #define EE_VERIFY(pred) \
        ((pred) ? true : EEDebugBreakProc())

    #define EE_VERIFYEQUALS(computed, verifed) \
        (((pred) == (verified)) ? true : EEDebugBreakProc())

    #define EE_VERIFY_NOT_EQUAL(computed, verifed) \
        (((pred) != (verified)) ? true : EEDebugBreakProc())

    #define EE_VERIFY_MESSAGE(pred, messageAndArgs) \
        ((pred) ? true : EEDebugBreakProc())

    #define EE_FAIL_AT(msg, file, line) \
        (EEDebugBreakProc())

    #define EE_FAIL(msg) \
        (EEDebugBreakProc())

    #define EE_FAIL_MESSAGE_AT(messageAndArgs, file, line, function) \
        (EEDebugBreakProc())

    #define EE_FAIL_MESSAGE(messageAndArgs) \
        (EEDebugBreakProc())

#else // defined(EE_ASSERTS_ARE_ENABLED)

    //---------------------------------------------------------------------------------------------
    // Asserts disabled
    //---------------------------------------------------------------------------------------------

    #define EE_ASSERT(pred) (void)false

    #define EE_ASSERT_MESSAGE(pred, messageAndArgs) (void)false

    #define EE_VERIFY(pred) (pred)

    #define EE_VERIFY_MESSAGE(pred, messageAndArgs) (pred)

    #define EE_VERIFYEQUALS(computed,verified) (computed)

    #define EE_VERIFY_NOT_EQUAL(computed,verified) (computed)

    #define EE_FAIL_AT(msg, file, line, function) (void)false

    #define EE_FAIL(msg) (void)false

    #define EE_FAIL_MESSAGE_AT(messageAndArgs, file, line, function) (void)false

    #define EE_FAIL_MESSAGE(messageAndArgs) (void)false

#endif // !defined(EE_ASSERTS_ARE_ENABLED)



/// @name Compile Time Assert Helpers
/// Helpers for EE_COMPILETIME_ASSERT
//@{
#define EE_JOIN_HELPER(one, two) one##two
#define EE_JOIN_TOKENS(one, two) EE_JOIN_HELPER(one, two)

#if defined (_MSC_VER)
    #define EE_MAKE_UNIQUE_NAME(root) EE_JOIN_TOKENS(root, __COUNTER__)
#else
    #define EE_MAKE_UNIQUE_NAME(root) EE_JOIN_TOKENS(root, __LINE__)
#endif

namespace efd
{
    template <bool MustBeTrue> struct COMPILE_TIME_ASSERTION_FAILURE;
    template <> struct COMPILE_TIME_ASSERTION_FAILURE<true> {};
    template <int Unused> struct CompileTimeAssertTester {};
}
//@}

/**
    @def EE_COMPILETIME_ASSERT

    A compile time assert will generate a build error if the condition is not true.  It can be
    used to test any invariant condition. This can be used at namespace, class, or function scope.

    @note If you want to stick this into the global namespace you should be careful.  We try to
    generate a unique name but only the MSVC compiler truly allows us to do this.  On other
    compilers we just tag the line number.  This means:
        1.) You should wrap global compile time asserts into a uniquely named namespace.
        2.) You cannot use two compile time asserts on the same line.  This also means you can't
            put multiple compile time asserts into another \#define macro, for example.
    If you break these rules it will still work on MSVC but will fail to compile on other compiles
    due to a "duplicate symbol name" error.
*/
#ifdef EE_USE_ENUM_FOR_COMPILETIME_ASSERT

// For some compilers this version may result in a better error message.  In
// general the typedef version is the preferred method though.
#define EE_COMPILETIME_ASSERT(condition)                                                \
    enum                                                                                \
    {                                                                                   \
        EE_MAKE_UNIQUE_NAME(compile_time_assert_value) =                                \
        sizeof(efd::COMPILE_TIME_ASSERTION_FAILURE<(bool)(condition)>)                  \
    }

#else

// According to Boost a typedef based solution works better.
#define EE_COMPILETIME_ASSERT(condition)                                                \
    typedef efd::CompileTimeAssertTester<                                               \
    sizeof(efd::COMPILE_TIME_ASSERTION_FAILURE<(bool)(condition)>)>                     \
    EE_MAKE_UNIQUE_NAME(compile_time_assert_type)

#endif // EE_USE_ENUM_FOR_COMPILETIME_ASSERT


#endif // EE_ASSERTS_H
