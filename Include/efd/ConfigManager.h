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
#ifndef EE_CONFIGMANAGER_H
#define EE_CONFIGMANAGER_H

#include <efd/IConfigManager.h>
#include <efd/ConfigSection.h>

namespace efd
{

/**
    ConfigManager is the implementation class for the Configuration Manager. which provides
    applications access to a hierarchical configuration of name/value pairs drawn from multiple
    sources.

    @note See the CommandLineSource and IniSource classes for details on specifying configuration
    information.
*/
class EE_EFD_ENTRY ConfigManager : public IConfigManager
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(ConfigManager, efd::kCLASSID_ConfigManager, IConfigManager);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

public:
    /**
        Constructor that creates the Configuration Service and creates the default command-line
        and default INI file sources.

        @param configFile Optional path and file name of the config file.
        @param argcInit Number of command line arguments passed to the application.
        @param argvInit Array of strings containing each of the command line arguments.
        @param processEnvVars True to create an Environment Variables source(EnvVarSource) and
            read in all the environment variables into the configuration.
    */
    ConfigManager(
        const efd::utf8string& configFile,
        int argcInit,
        char **argvInit,
        bool processEnvVars = false);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void WriteConfiguration(const efd::utf8string& strFileName, bool bPrintRelative = true);
    virtual void AddConfigSource(IConfigSource *pSource, int iPriority);
    virtual void RemoveConfigSource(IConfigSource *pSource);
    virtual const ISection *GetConfiguration();
    virtual bool FindValue(const efd::utf8string& strName, efd::utf8string& o_value) const;
    virtual efd::utf8string FindValue(const efd::utf8string& strName) const;
    virtual bool IsTrue(const efd::utf8string& strName, bool defaultValue = false) const;
    virtual bool IsFalse(const efd::utf8string& strName, bool defaultValue = true) const;

protected:
    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void OnServiceRegistered(IAliasRegistrar* pAliasRegistrar);
    virtual const char* GetDisplayName() const;

    /// Virtual destructor that destroys the Configuration Service and releases all references to
    /// any messages and targets that may still exist.
    virtual ~ConfigManager();

    /**
        A special version of AddConfigSource used by the ConfigSource base class to add any other
        included IniSource files. It is special in that the root and priority for the source is set
        by the caller before adding the source.

        @param pSource Pointer to the new source.
    */
    void AddConfigSourceInternal(IConfigSource *pSource);

    /// Removes a previously added source
    void RemoveConfigSourceInternal(IConfigSource *pSource);

private:
    /// List of the configuration sources.
    efd::list<IConfigSourcePtr> m_sources;

    /// Root section for the configuration.
    Section m_root;

#if defined(EE_EFD_CONFIG_DEBUG) && defined(EE_PLATFORM_XBOX360)
private:
    static void ConfigManager::ImportXDKCommandLine(int& argcInit, char **& argvInit);
#endif // defined(EE_EFD_CONFIG_DEBUG) && defined(EE_PLATFORM_XBOX360)

};

/// A SmartPointer for the ConfigManager class.
typedef efd::SmartPointer<ConfigManager> ConfigManagerPtr;

} // end namespace efd.

#include <efd/ConfigManager.inl>

#endif // EE_CONFIGMANAGER_H
