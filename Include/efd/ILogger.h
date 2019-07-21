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
#ifndef EE_ILOGGER_H
#define EE_ILOGGER_H

#include <efd/ILogDestination.h>
#include <efd/LoggerMacros.h>


namespace efd
{

// Forward references
class IConfigManager;
class DataDrivenEnumBase;
class EnumManager;


/**
    Interface to the logging system.

    This class receives all log, assert, and verify statements, which it filters and passes to the
    proper destination to be recorded.
*/
class EE_EFD_ENTRY ILogger : public efd::IBase
{
public:

    /// @name Log Levels
    /// Level definitions used in calls to ILogger::Log and the EE_LOG* macros
    //@{

    /// System fatal errors.
    static const efd::UInt8 kERR0 /*= 0*/;

    /// Serious errors (lost connection, etc.)
    static const efd::UInt8 kERR1 /*= 1*/;

    /// Common and recoverable errors
    static const efd::UInt8 kERR2 /*= 2*/;

    /// Trivial errors
    static const efd::UInt8 kERR3 /*= 3*/;

    /// Rare, important events, such as client connects, disconnects, DB connection established.
    static const efd::UInt8 kLVL0 /*= 4*/;

    /// Significant, but more common events (e.g., avatar moves between locales).
    static const efd::UInt8 kLVL1 /*= 5*/;

    /// Common events (a message is handled).
    static const efd::UInt8 kLVL2 /*= 6*/;

    /// Debugging (generally only enabled during development).
    static const efd::UInt8 kLVL3 /*= 7*/;

    /// An unknown level has been detected.
    static const efd::UInt8 kUknownLevel /*= EE_UINT8_MAX*/;
    //@}

    /// @name Log Level Masks
    /// Mask definitions used in calls to ILogger::SetLogLevel.  These refer to one or more of
    /// the "Log Levels" values above.
    //@{
    static const efd::UInt8 kLogMask_Err0 /*= 1 << kERR0*/;
    static const efd::UInt8 kLogMask_Err1 /*= 1 << kERR1*/;
    static const efd::UInt8 kLogMask_Err2 /*= 1 << kERR2*/;
    static const efd::UInt8 kLogMask_Err3 /*= 1 << kERR3*/;
    static const efd::UInt8 kLogMask_Lvl0 /*= 1 << kLVL0*/;
    static const efd::UInt8 kLogMask_Lvl1 /*= 1 << kLVL1*/;
    static const efd::UInt8 kLogMask_Lvl2 /*= 1 << kLVL2*/;
    static const efd::UInt8 kLogMask_Lvl3 /*= 1 << kLVL3*/;
    static const efd::UInt8 kLogMask_UptoErr1 /*= kLogMask_Err0 | kLogMask_Err1*/;
    static const efd::UInt8 kLogMask_UptoErr2 /*= kLogMask_UptoErr1 | kLogMask_Err2*/;
    static const efd::UInt8 kLogMask_UptoErr3 /*= kLogMask_UptoErr2 | kLogMask_Err3*/;
    static const efd::UInt8 kLogMask_UptoLvl1 /*= kLogMask_Lvl0 | kLogMask_Lvl1*/;
    static const efd::UInt8 kLogMask_UptoLvl2 /*= kLogMask_UptoLvl1 | kLogMask_Lvl2*/;
    static const efd::UInt8 kLogMask_UptoLvl3 /*= kLogMask_UptoLvl2 | kLogMask_Lvl3*/;
    static const efd::UInt8 kLogMask_All /*= kLogMask_UptoErr3 | kLogMask_UptoLvl3*/;
    /// Turn of logging.
    static const efd::UInt8 kLogMask_None /*= 0*/;
    //@}

    /// Constructor
    ILogger()
        : m_bUseStackTrace(true)
    {
    }

    /**
        Receives the log message from the helper class and forwards it to the proper destination.

        @param module Module ID that generated the log message.
        @param level Log message level.
        @param pFile Source file where the log message was generated.
        @param line Source line where the log message was generated.
        @param pMsg Formatted log message.
    */
    virtual void Log(
        efd::UInt16 module,
        efd::UInt8 level,
        const char* pFile,
        efd::SInt32 line,
        const char* pMsg) = 0;

    /**
        Receives the assert or verify message from the helper class and forwards it to the proper
        destination.

        @param pFile Source file where the log message was generated.
        @param line Source line where the log message was generated.
        @param pFunction Function where the log message was generated.
        @param pPred Predicate of the assert that failed.
        @param pMsg Optional formatted assert message.
        @param pStack Optional If EE_USE_ASSERT_STACKTRACE was defined at compile time, a stack
            backtrace is passed in.  If enabled and NoStackTraceOnAssert has not been called
            the backtrace will be included in the output.
        @return True if successful; false otherwise.
    */
    virtual efd::Bool AssertMessage(
        const char* pFile,
        efd::SInt32 line,
        const char* pFunction,
        const char* pPred,
        const char* pMsg,
        const char* pStack = NULL) = 0;

    /**
        Registers the name of a new module name and automatically assigns an ID to it.  If this
        method is called with an already known module name the previously assigned module ID
        will be returned.

        @param pName Name of the new module.
        @return Module ID assigned to the new module.
    */
    virtual efd::UInt16 RegisterModuleName(const char* pName) = 0;

    /**
        Registers the name of a new module name and assigns it the specified ID.  If the specified
        ID is already in use this method will fail.

        @param module ID of the module for which to register the name.
        @param pName Name to assign to the module ID.
        @return True if the module was registered, false if it conflicts with existing entries.
    */
    virtual bool RegisterModuleName(
        efd::UInt16 module,
        const char* pName) = 0;

    /**
        Register the name of a level mask.  A level mask is one or more bits which correspond
        by index to the "Log Levels" used by ILogger::Log.  Combinations of bits can be
        given a name and this name can then be used to configure logging through the ConfigManager
        service.  Typically you won't need to call this method since default names are registered
        automatically for all of the standard masks and these default names can be combined
        together using the '|' character.  However you may wish to register additional names for
        convenience or in order to have more control over the mask value.  For example, your
        code could register a string name using a different mask value based on the compile
        target so that a single configuration name behaved differently in debug and release
        builds.

        @note In order to use the names you register in the configuration you must call this
        method prior to calling ILogger::ReadConfig.

        @note The default mask names that are automatically registered for use in the configuration
        files are:
        @verbatim
            String Name     Corresponding Mask
            -----------     ------------------
            "Err0"          kLogMask_Err0
            "Err1"          kLogMask_Err1
            "Err2"          kLogMask_Err2
            "Err3"          kLogMask_Err3

            "Lvl0"          kLogMask_Lvl0
            "Lvl1"          kLogMask_Lvl1
            "Lvl2"          kLogMask_Lvl2
            "Lvl3"          kLogMask_Lvl3

            "UptoLvl1"      kLogMask_UptoLvl1
            "UptoLvl2"      kLogMask_UptoLvl2
            "UptoLvl3"      kLogMask_UptoLvl3

            "UptoErr1"      kLogMask_UptoErr1
            "UptoErr2"      kLogMask_UptoErr2
            "UptoErr3"      kLogMask_UptoErr3

            "All"           kLogMask_All
            "None"          kLogMask_None
        @endverbatim

        @param levelMask Mask of the level(s) for which to register the name.
        @param pName The string name to assign to the level mask.
    */
    virtual void RegisterLevelMaskName(
        efd::UInt8 levelMask,
        const char* pName) = 0;

    /**
        Sets the log level for the specified module ID.

        Use one or more "Log Level Masks" values logically ORed (|) together to specify which
        log levels should be enabled.  Calls to logging methods like EE_LOG will do nothing if
        the given log level is not enabled.  By default

        If the provided module is efd::kALL then this will set all modules to use the given level.
        This will override previous settings for a specific module.  So, for example, calling
        SetLogLevel(efd::kALL, kLogMask_None) would disable all logging regardless of previous
        configuration.  Future calls to SetLogLevel would work as normal.

        You may also optionally specify a specific log destination in order to only adjust the
        settings for that single destination.  Passing an empty string ("") as the destination
        will result in all currently registered log destination being affected.  When all
        destinations are selected by using the empty string this call can override previous
        settings specific to a single destination.  If a destination name is provided but no
        destination of the given name exists then SetLogLevel will do nothing and return failure.

        Based on how SetLogLevel overriding works, generally you will want to set your most
        generic log options first and provide more specific settings last.

        @param module Module ID to register the level.
        @param levelMask The "Log Level Masks" to accept.
        @param destination Log destination to which to write the statements.
        @return True if the destination was found and the log level was set; false otherwise.
    */
    virtual efd::Bool SetLogLevel(
        efd::UInt16 module,
        efd::UInt8 levelMask,
        const efd::utf8string& destination = "")=0;

    /**
        Adds the destination to the logger and initializes it.

        @param pDest Pointer to the new log destination class.
        @param useDefaults If true, the destination is initialized to the default module / log
            levels are set.
        @param overrideExisting If true, the destination will replace any previous destination
            with the same name.
        @return True if successful; false otherwise.
    */
    virtual efd::Bool AddDest(
        ILogDestination* pDest,
        bool useDefaults = false,
        bool overrideExisting = false) = 0;

    /**
        Removes a log destination by name.

        @note Reserved for future use when multiple destinations are supported.

        @param name Name used to refer to the destination.
    */
    virtual void RemoveDest(const efd::utf8string& name) = 0;

    /**
        Removes a log destination by pointer.

        @param pDest Pointer to the new log destination class.
    */
    virtual void RemoveDest(ILogDestination* pDest) = 0;

    /**
        Removes all the log destinations.
    */
    virtual void RemoveAllDests() = 0;

    /**
        Get the names of all registered destinations.

        @param names Set of destination names.
    */
    virtual void GetDestinationNames(efd::set<efd::utf8string>& names) = 0;

    /**
        True if 'name' is a destination.

        @param name Name to query.
        @return True if the name is a destination name; false otherwise.
    */
    virtual efd::Bool IsDestination(const efd::utf8string& name) const = 0;

    /**
        Returns true if the logger is logging messages for the specified log mask to one or
        more log destinations.

        @param module Logging module to check.
        @param level Level bits to check.
        @return True if the module and level are being logged; false otherwise.
    */
    virtual efd::Bool IsLogging(
        efd::UInt16 module,
        efd::UInt8 level) const = 0;

    /**
        Retrieves the module ID, given a module name.

        @param moduleName Name of the module to lookup.
        @return Module ID, if not found kUnknownModule.
    */
    virtual efd::UInt16 GetModuleInt(const efd::utf8string& moduleName) = 0;

    /**
        Parses a string into a level mask.  This will convert any default mask name or mask name
        passed to RegisterLevelMaskName into the corresponding mask bits.  In addition it will
        parse combinations of known mask names separated by the '|' character into the
        corresponding logically or'ed mask.  Finally, it can also parse a string containing
        a decimal integer.

        See ILogger::RegisterLevelMaskName for a list of the default mask names.

        @param levelName Name of the level to lookup.
        @return Level ID, if not found kUnknownLevel.
    */
    virtual efd::UInt8 GetLevelMaskByName(const efd::utf8string& levelName) = 0;

    /**
        Retrieves the module name, given the module ID.

        @param module Module ID to look up.
        @return Module name.
    */
    virtual efd::utf8string GetModuleName(efd::UInt16 module) = 0;

    /**
        Retrieves the level name, given the level ID.

        @param level Level ID to look up.
        @return level name
    */
    virtual const char* GetLevelName(efd::UInt8 level) = 0;

    /**
        Reads the configuration information from the ConfigManager and sets up the Logger as
        specified.

        [Log.FileDests."<name>"] is a section that specifies the file destination for the logger.
        The "<name>" is the name assigned to the log file and is reserved for future use when
        multiple destinations are supported.  The section contains two keys, FileName and
        FileMode, that specify the file to open and how to open it.  FileInfoWithMsg, if set to
        true, is used to turn on file and line reporting for log messages.  FileInfoWithAssert, if
        set to false, is used to turn off file and line reporting for asserts.

        The [Log.Modules] section is used to specify string names for module IDs.  It contains one
        key value pair for each module that needs a name.  The key is the module string name and
        the value is the ID.

        The [Log.Levels] section is used to specify string names for level IDs.  It contains one
        key value pair for each level that needs a name.  The key is the level string name and the
        value is the ID.  The value can either be a numeric version of the level bits or a string
        of registered level names to be combined.  The individual level names are separated with
        '|' characters.

        The [Log.Filters."<name>"] section is used to setup the log filters.  It contains key value
        pairs for each module that is to be logged.  The key is the module in either numeric or
        string form.  The value is the filter level in either numeric or string form.  The
        optional name is the name of the log destination (not the log file name) to which you want
        the filter applied.

        Below is example configuration information for the Logger:

            @verbatim
            [Log]
            ; Module names are defined using enum files.  You can specify which enum file should
            ; be loaded.  When the enum is loaded this allows you to use friendly string names
            ; for configuring the Log.Filters and also uses those friendly names in the log file
            ; output.
            ModuleEnum=efdLogIds

            ; Override the default log destination.  The destination name "default" is the name
            ; that is typically used from code when adding the initial log destination.  By
            ; reusing the same name here we can replace the hardcoded destination with an override.
            ; Some programs may create multiple or differently named destinations in code, all
            ; of those can be overridden in this same way.
            [Log.Destinations.default]
            Type = File
            FileName = LogCfgMn.log
            FileMode = FileOverwrite

            ; Create a second log destination which we will config to only get error messages.
            ; Note:  The name given to the log destination is placed in the section header and in
            ; this case it is "ErrorFile".  Any name can be used.
            [Log.Destinations.ErrorFile]
            Type = File
            ; By default newly added destinations typically log nothing until a filter config is
            ; specified.  If you want, you can instead set UseDefaults to true and the new
            ; destination will have the default config applied.  The default is equivalent to a
            ; filter of "ALL = UptoErr3 | UptoLvl2".
            UseDefaults = true
            FileName = ErrsOnly.log
            FileMode = FileOverwrite

            ; Besides file based log destinations, there are 'Printf' and 'DebugOut' destinations
            ; registered by default.  These can also be extended by your program to provide new
            ; types.
            [Log.Destinations.DebugOutput]
            Type = DebugOut

            ; Create a custom named level mask.  These can be used for convenience when setting log
            ; filters.
            [Log.Levels]
            MyDefaultLevels = UptoErr3 | UptoLvl1

            ; Set the default log filters to be used for all log destinations.
            ; Note:  No destination name is used, this applies to all destinations.
            ; Each line of the filter takes the form "<ModuleName> = <Log Level Mask>".  The
            ; module name can be specified as an integer or as a friendly name.  However, in order
            ; to use friendly names you need to configure Log.ModuleEnum, Enum.Path and use the
            ; EnumManager service.  For a list of valid log level mask strings, see
            ; ILogger::RegisterLevelMaskName.
            [Log.Filters]
            1 = UptoErr3 | UptoLvl3
            Testing = All
            Foundation = None
            TestModule2 = MyDefaultLevels

            ; Create log filters for the ErrorFile log destination by providing its name as part
            ; of the section header.
            [Log.Filters.ErrorFile]
            ALL = UptoErr3

            [Log.Filters.DebugOutput]
            ALL = Err0
            @endverbatim

        @param pConfigManager Pointer to the configuration manager from which to read the
            configuration information.
        @param pEnumManager Pointer to the EnumManager.
        @param force If true, we are re-reading the configuration due to settings changes. Normally
            only the first call to ReadConfig has any effect but this can override that.
        @return True if a log section is found; false otherwise. True does not mean the method
            found any settings, merely that it found the section.  This behavior is due to the fact
            that all settings are optional.
    */
    virtual efd::Bool ReadConfig(
        efd::IConfigManager* pConfigManager,
        efd::EnumManager* pEnumManager,
        bool force = false) = 0;

    /// Clears the module/level filters and sets it to log nothing.
    virtual void ResetLogLevels() = 0;

    /**
        Reset the log levels for the destination.

        @param dest Log destination to which to write the statements.
    */
    virtual void ResetLogLevels(const efd::utf8string& dest) = 0;

    /**
        Look up the log level for a module.

        @param moduleId Module ID.
        @param destination Log destination to which to write the statements.
        @return Log level for the module specified.
    */
    virtual efd::UInt8 GetLogLevel(
        efd::UInt16 moduleId,
        const efd::utf8string& destination) const = 0;

    /**
        Get a map of all modules.

        @param names Map of all modules.
    */
    virtual void GetModules(efd::map<efd::UInt16, efd::utf8string>& names) const = 0;

    /**
        Get all the level names registered with the logger.

        @param names Set of all level names.
    */
    virtual void GetLevelNames(efd::set<efd::utf8string>& names) const = 0;

    /**
        Get the default logger.

        @return Pointer to the ILogDestination for the default logger.
    */
    virtual const ILogDestination* GetDefaultDestination() const = 0;

    /**
        Set the default log levels for the log destination to which to write the statements.

        @param destName Name of the log destination.
    */
    virtual void SetDefaultLogLevels(const efd::utf8string& destName) = 0;

    /**
        Force all the registered log destinations to flush their buffers.
    */
    virtual void Flush() = 0;

    /**
        Set the enumeration for mapping module names to module ids and vice versa.
    */
    virtual void SetModuleEnum(efd::DataDrivenEnumBase* pEnum) = 0;

    /**
        Force all the registered log destinations to flush their buffers.
    */
    void NoStackTraceOnAssert()
    {
        m_bUseStackTrace = false;
    }

protected:
    bool m_bUseStackTrace;
};

/// Get the default logger.
extern EE_EFD_ENTRY ILogger* GetLogger();

/// Define a smart pointer for the ILogger class.
typedef efd::SmartPointer<ILogger> ILoggerPtr;

}   // End namespace efd.

#endif // EE_ILOGGER_H
