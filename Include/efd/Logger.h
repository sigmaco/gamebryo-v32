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
#ifndef EE_LOGGER_H
#define EE_LOGGER_H

// NOTE: Users of Logging should include efd/ILogger.h, not efd/Logger.h.  This class is all
// implementation detail.

#include <efd/DataDrivenEnum.h>
#include <efd/efdClassIDs.h>
#include <efd/ILogger.h>
#include <efd/BitUtils.h>

namespace efd
{
// Forward declarations
class ISection;
class ISectionEntry;
class Category;
class ServiceManager;

/**
    Concrete implementation of the ILogger base class. Logger provides methods to set / get
    logging levels, and write Log messages to a registered set of ILogDestinations. Typical usage
    is to construct a Logger instance at the start of the application, register one or more
    log destinations with it, and then set the newly configured logger as the ILogger instance
    used by the LoggerSingleton.

    @verbatim
    Example:

    LoggerPtr spLogger = EE_NEW Logger();
    EE_ASSERT(spLogger);

    ILogDestination* logDest = EE_NEW FileDestination(
    "default",
    "MyLogFile.log",
    FileDestination::kFileOverwrite);
    spLogger->AddDest(logDest, true);

    LoggerSingleton::Initialize(spLogger);

    @endverbatim

    Typically logging is abstracted by the EE_LOG macros defined in ILogger.h. These macros
    hide the details of getting the LoggerSingleton, accessing the registered ILogger, and calling
    the ILogger.Log method. Using Logger directly should be constrained to very specific cases
    where the EE_LOG macros are insufficient.
*/
class EE_EFD_ENTRY Logger : public efd::ILogger
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(Logger, efd::kCLASSID_Logger, efd::ILogger);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond
public:
    /// The section name for retrieving configuration variables
    const static char *kConfigSection;
    /// The section name for the file destinations
    const static char *kConfigFilesSection;
    /// The key for the file destination file name
    const static char *kConfigDestFileNameKey;
    /// The key for the file destination file mode
    const static char *kConfigDestFileModeKey;
    /// The key for the file destination file information with messages mode
    const static char *kConfigDestFileMsgKey;
    /// The key for the file destination file information with asserts mode
    const static char *kConfigDestFileAssertKey;
    /// The section name for the module names
    const static char *kConfigModuleNamesSection;
    /// The section name for the level names
    const static char *kConfigLevelNamesSection;
    /// The section name for the log levels
    const static char *kConfigLogLevelsSection;

    /**
        Constructor for the logger.  It sets up the default Assert handler (if
        there is not already installed).  It also sets up all the default
        module and level names.
    */
    Logger();

    /**
        Destructor removes all the registered destinations.  If they are not
        referenced anywhere else then they will destroy themselves.
    */
    virtual ~Logger();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void Log(
        efd::UInt16 module,
        efd::UInt8 level,
        const char* pFile,
        efd::SInt32 line,
        const char* pMsg);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::Bool AssertMessage(
        const char* pFile,
        efd::SInt32 line,
        const char* pFunction,
        const char* pPred,
        const char* pMsg,
        const char* pStack = NULL);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::UInt16 RegisterModuleName(const char* pName);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual bool RegisterModuleName(efd::UInt16 module, const char* pName);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void RegisterLevelMaskName(efd::UInt8 level, const char* pName);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::Bool SetLogLevel(
        efd::UInt16 module,
        efd::UInt8 level,
        const efd::utf8string& destination = "");

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::Bool AddDest(
        ILogDestination* pDest,
        bool useDefaults = false,
        bool overrideExisting = false);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void RemoveDest(const efd::utf8string& name);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void RemoveDest(ILogDestination* pDest);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void RemoveAllDests();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void GetDestinationNames(efd::set<efd::utf8string>& names);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::Bool IsDestination(const efd::utf8string& name) const;

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::Bool IsLogging(efd::UInt16 module, efd::UInt8 level) const;

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::UInt16 GetModuleInt(const efd::utf8string& moduleName);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::UInt8 GetLevelMaskByName(const efd::utf8string& levelName);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void GetModules(efd::map<efd::UInt16, efd::utf8string >& names) const;

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::utf8string GetModuleName(efd::UInt16 module);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual const char* GetLevelName(efd::UInt8 level);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::Bool ReadConfig(
        efd::IConfigManager* pConfigManager,
        efd::EnumManager* pEnumManager = NULL,
        bool force = false);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void ResetLogLevels();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void ResetLogLevels(const efd::utf8string& dest);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::UInt8 GetLogLevel(efd::UInt16 moduleId, const efd::utf8string& destination) const;

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void GetLevelNames(efd::set< efd::utf8string >& names) const;

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual const ILogDestination* GetDefaultDestination() const
    {
        return m_destinations[0];
    }

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void SetDefaultLogLevels(const efd::utf8string& destName);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void Flush();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void SetModuleEnum(efd::DataDrivenEnumBase* pEnum);

    /**
        Copy settings from the provided logger into the current logger.  This will transfer any
        registered module names, level names, friendly names, and destination factories.
    */
    virtual void Clone(const Logger* logger);


    /**
        typedef for the function signature used to factory ILogDestination instances.
    */
    typedef ILogDestination* (*DestinationFactoryMethod)(
        const efd::utf8string& destSectionName,
        const efd::ISection* pDestSection);

    /**
        Method to register a factory for a file destination.  Once registered you can use the
        given name to configure logging from your Config.ini file.  For example, if you register
        a factory for the name "Jabberwocky" then you could place the following in your config
        file:

        @verbatim
        ; The section name can be whatever unique name you want to use
        [Log.Destinations.WhateverName]
        Type = Jabberwocky
        ; The config section is passed to the factory method so you can read options specific
        ; to your ILogDestination type:
        JabberwockySomeOption = foo
        JabberwockyAnotherOption = bar

        ; You can set also filters specific to your handler as normal using the section name
        [Log.Filters.WhateverName]
        ALL = UPTO_ERR3
        @endverbatim

        There are several default destination types that are already registered.  You may override
        these default factory methods with your own factories if so desired, but if you do it is
        recommended that the overrides support the same configuration options in order to avoid
        possible confusion.  The default log destination factories and their options are:

        File - creates a FileDestination handler that logs to a text file using a specific
        row format.  Supports the following config parameters:
        FileName [required] - the name of the log file
        FileMode [optional] - one of FileAppend, FileOverwrite, or FileMove specifying the
        behavior if FileName already exists.  Defaults to FileOverwrite.
        FileInfoWithMsg [optional] - Set to "true" if you want all log statements to include
        the file name and line number they originated from.  Defaults to false.
        FileInfoWithAssert [optional] - Set to "false" to prevent assert messages from
        including the file name and line number.  Defaults to true.

        Printf - creates a PrintDestination that simply performs a printf for each log statement.
        Supports the following config parameters:
        Decorate [optional] - Set to "true" if you want printed lines to include a detailed
        header identical to the header FileDestination uses.  Defaults to false which
        will simply display the timestamp and message body.
        FileInfoWithMsg [optional] - Set to "true" if you want all log statements to include
        the file name and line number they originated from.  Defaults to false.  This
        option only applies when Decorate is set to true.
        FileInfoWithAssert [optional] - Set to "false" to prevent assert messages from
        including the file name and line number.  Defaults to true.  This option only
        applies when Decorate is set to true.

        DebugOut - creates a DebugOutDestination that outputs using OutputDebugString on Windows
        or the nearest equivalent method on other platforms.  This destination only generates
        output for debug builds.  DebugOut supports the same config parameters as Printf.

        Additional help for config file logging options can be found in ILogger::ReadConfig.
        @see ILogger::ReadConfig
    */
    bool RegisterDestinationFactory(const utf8string& strName, DestinationFactoryMethod pfn);

    /**
        Set the pointer to the service manager from logging so that it can assess the game time
        clock. This is optional, if not set game time will simply not be logged.
    */
    void SetServiceManager(efd::ServiceManager* pServiceManager);

    /**
        Set the ClassID for the clock that should be logged as "game time", which can really be
        any clock you desire. If not set game time is simply not logged.
    */
    void SetGameClockClassID(ClassID id);

    /**
        Sets a flush log level.  If anything is logged at or above this level in priority the
        logs will be flushed immediately.
    
        @param level The level to flush the logs at.
    */
    virtual void SetFlushLogLevel(efd::UInt8 level);

protected:
    /**
	    Just flushes destinations that are file destinations.
	*/
    void FlushFileLogDestinations();

    /**
        This method is different than the public module number lookup.  It first
        determines if the string contains a module ID in string form.  If it does
        it converts the string to that number and uses it.  If it is not just a
        number than it looks up the module number using the public lookup.

        @param module The name of the module to lookup
        @return The module ID, if not found -1
    */
    efd::UInt16 StringToModuleID(const efd::utf8string& module);

    /**
        Fills the supplied string with the formatted date and time of the
        current machine.

        @param timeStamp The string to fill with the machine date and time
        @param bufferSize The size of the buffer
    */
    void GetMachineTimeStamp(char *timeStamp, efd::UInt32 bufferSize);

    /**
        Reads the config file section and creates a log destination based on
        its information.

        @param destName The name to give the log destination.
        @param pDestSection The section in the config file that contains the log
        destination information.
    */
    efd::Bool ReadDestConfig(
        const efd::utf8string& destName,
        const efd::ISection* pDestSection);

    /**
        Reads the config file section and creates a set of log filters based on
        its information and assigns those filters to the log destination
        specified.

        @param destName The name of the log destination to set filters for.
        @param pFilterSection The section in the config file that contains the log
        filter information for the specified log destination.
    */
    void ReadFilterConfig(
        const efd::utf8string& destName,
        const efd::ISection* pFilterSection);

    /**
        Helper to parse the Log.Levels configuration section, which registeres user defined
        Log Level Mask values.
        @param pLogSection The "Log" config section.
        */
    void ReadLogLevelNames(const efd::ISection* pLogSection);

    /**
        Helper to parse the value of a log configuration.
        @param moduleID The module name as already parsed from a string.
        @param pValSection The config entry containing the value
        @param destName The name of the current destination being configured
    */
    void ReadFilterValue(
        efd::UInt16 moduleID,
        efd::ISectionEntry* pValSection,
        const efd::utf8string& destName);

    /**
        Helper to map a destination name to the index at which it was registered.
        @param name ILogDestination name to lookup
    */
    efd::SInt32 GetDestinationIndexByName(const efd::utf8string& name) const;

    /**
        Helper to lookup a registered destination factory and create an instance.

        @param strTypeName the name as passed to RegisterDestinationFactory
        @param strSectionName the section name to be passed on to ILogDestination constructor
        @param pDestSection the config section from which to read any needed parameters
        @return ILogDestination* : the fully configured log destination, or NULL on failure
    */
    ILogDestination* FactoryLogDestination(const efd::utf8string& strTypeName,
        const efd::utf8string& strSectionName,
        const efd::ISection* pDestSection);

    /**
        A helper used when adding new destinations while parsing the configuration. It will
        remove a destination without doing the normal clean-up of electing a new default
        handler (because we are about to recreate the same destination name and if the old was
        the default the new will become the default.

        @param name Name used to refer to the destination.
    */
    void RemoveDestWithoutChangingDefault(const efd::utf8string& name);

protected:

    /// The module names map used to lookup names from IDs for custom modules.  Default modules
    /// are mapped through a data driven enumeration.
    typedef efd::map<efd::UInt16, efd::utf8string> ModuleNameMap;
    ModuleNameMap m_moduleNames;

    /// The level mask names map used to lookup names from masks.
    typedef efd::map<efd::utf8string, efd::UInt8> LevelNameMap;
    LevelNameMap m_levelNames;

    /// Map of names to destination factories
    typedef efd::map<utf8string, DestinationFactoryMethod> DestinationFactory;
    DestinationFactory m_destinationFactory;

    /// Destinations
    static const efd::SInt32 kMaxLogDestinations = 32;
    ILogDestinationPtr m_destinations[kMaxLogDestinations];

    /// Internal class used to store data specific to each configured module
    class ModuleSettings
    {
    public:
        ModuleSettings();

        /// Clear all destinations for all log levels
        void Clear();

        /// Clear all destinations with high bits in the mask
        void Clear(efd::UInt32 mask);

        /// Shift the bit setting from the old index into the new index and then clear the
        /// old index.
        void MoveDestination(efd::UInt32 oldIndex, efd::UInt32 newIndex);

        /// Retrieve the mask bits for the given log level
        efd::UInt32 GetDestinationsMask(efd::UInt8 level) const;

        /// Given a destination index, build a log mask from all the bits for that index
        efd::UInt8 GetLogMaskForDestination(efd::SInt32 destIndex) const;

        /// Turn on the destination mask for all active destinations that match the log mask and
        /// turn the destination mask off for all the remaining active destinations.
        void SetLogMask(efd::UInt8 levelMask, efd::UInt32 destMask);

        /// Storage for the masks for every possible log level
        efd::UInt32 m_activeDestinations[8];
    };

    /// A map from log modules to a ModuleSetting instance.
    typedef efd::map<efd::UInt16, ModuleSettings> ModuleSettingsMap;
    /// Configuration information for each configured module
    ModuleSettingsMap m_modules;

    /// Default module settings for modules that are not overridden in the m_modules map.
    ModuleSettings m_defaults;

    /// A helper to access the ModuleSetting for a given log module.  If the log module is not
    /// overridden then this will return the appropriate defaults.
    inline ModuleSettings& GetModuleSettings(efd::UInt16 module)
    {
        ModuleSettingsMap::iterator iter = m_modules.find(module);
        if (iter != m_modules.end())
        {
            return iter->second;
        }
        // No specific entry for this module, so fall back to the defaults:
        return m_defaults;
    }

    /// A helper to access the ModuleSetting for a given log module.  If the log module is not
    /// overridden then this will return the appropriate defaults.
    inline const ModuleSettings& GetModuleSettings(efd::UInt16 module) const
    {
        ModuleSettingsMap::const_iterator iter = m_modules.find(module);
        if (iter != m_modules.end())
        {
            return iter->second;
        }
        // No specific entry for this module, so fall back to the defaults:
        return m_defaults;
    }

    /// A mask of all the active destinations.  The various ModuleSetting entries tend to set
    /// bits that aren't actually used so we combine with this mask to optimize the results.
    efd::UInt32 m_activeDestinations;

    /// The name<->id mapper for logging module names
    efd::SmartPointer< DataDrivenEnum<efd::UInt16> > m_spModuleEnum;

    /// The service manager
    efd::ServiceManager* m_pServiceManager;
    /// The class ID for the gametime clock
    efd::ClassID m_clockID;
    /// The level to automatically flush the logs at.
    efd::UInt8 m_flushLevel;
    /// An indicator of whether ReadConfig has been successfully called already.
    bool m_alreadyConfigured;
};

/// A SmartPointer for the Logger class
typedef efd::SmartPointer<Logger> LoggerPtr;



/**
    Singleton logger wrapper. This allows us to plug-in different loggers based on needs. Only
    once ILogger instance can be active at any one time. The LoggerSingleton provides access to
    this ILogger instance across the entire application.
*/
class EE_EFD_ENTRY LoggerSingleton : public MemObject
{
public:
    /**
        Get the LoggerSingleton instance. If the singleton hasn't been initialized,
        this method returns null.
    */
    static LoggerSingleton* Instance();


    /**
        Deletes the active LoggerSingleton instance and the logger associated with it.
    */
    static void DestroyInstance();

    /**
        Initialized the global logger singleton with the given ILogger instance.
    */
    static void Initialize(LoggerPtr logger);

    /**
        Get the currently defined logger.
    */
    ILogger* GetLogger();

private:
    // make these private. We want to control the way this class is constructed.
    LoggerSingleton();
    LoggerSingleton(const LoggerSingleton&);

    LoggerPtr m_spLogger;
    static LoggerSingleton* ms_instance;
};

} // end namespace efd

#endif // EE_LOGGER_H
