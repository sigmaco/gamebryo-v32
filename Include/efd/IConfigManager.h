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
#ifndef EE_ICONFIGMANAGER_H
#define EE_ICONFIGMANAGER_H

#include <efd/ISystemService.h>
#include <efd/IConfigSection.h>

namespace efd
{

/**
    IConfigManager is the interface class for the Configuration Manager which provides applications
    access to a hierarchical configuration of name/value pairs drawn from multiple sources.

    @note All methods exposed by IConfigManager are available as soon as the ConfigManager instance
        is created. They can be accessed during the OnPreInit or OnInit methods for any system
        services requiring configuration.

    @note See the CommandLineSource and IniSource classes for details on specifying configuration
        information.
*/
class EE_EFD_ENTRY IConfigManager : public ISystemService
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_INTERFACE1(IConfigManager, efd::kCLASSID_IConfigManager, ISystemService);
    /// @endcond

    // Grant protected access to the ConfigSource class.
    friend class ConfigSource;

public:

    /// The character '.' used to separate section names
    const static char kSectionSeperator;

    /// The character '=' used to separate the name from the value in source files and on the
    /// command-line.
    const static char kNameValueSeperator;

    /// The character '>' used to link a name to an existing name/value pair.
    const static char kNameLinkSeperator;

    /// The character '+' used to add an additional file source to the configuration with an
    /// optional section to add it under specified to the left of the separator.
    const static char kNameFileSeperator;

    /// The character '#' used to specify that the name should be converted to a unique name in a
    /// list but replacing the '#' character with unique number in sequence.
    const static char kNameListChar;

    /// Characters that start a variable name in a value or source file.
    const static char kVarStart[];

    /// Character that ends a variable name in a value or source file
    const static char kVarEnd[];

    /// Set of characters that are illegal to use in a section name
    const static char kIllegalSectionChars[10];

    /// Set of characters that are illegal to use in a value name.
    const static char kIllegalNameChars[10];

    /**
        Writes a copy of the current configuration data to the specified file.

        @param strFileName Filename for the file in which to write the data.
        @param bPrintRelative True means the INI file should be formatted with a relative
            section hierarchy.  False will produce absolute section headers.
    */
    virtual void WriteConfiguration(
        const efd::utf8string& strFileName,
        bool bPrintRelative = true) = 0;

    /**
        Adds a new configuration source to the available sources and immediately processed the
        source for new configuration values.

        @param pSource Pointer to the new source.
        @param iPriority Priority of the configuration source.  It does not determine the order
            that sources are processed.  It does how ever determine what happens when two sources
            attempt to set the same entry.  A higher source will overwrite a value from a lower
            source.
    */
    virtual void AddConfigSource(IConfigSource *pSource, int iPriority) = 0;

    /**
        Removes a previously added configuration source from the available sources. This will remove
        any sections or values that were added by this source. Removing sources is not recommended
        (see the notes below) and should only be done in situations where the value and section
        names added by the given source are unique to that source. Otherwise the results of source
        removal can be confusing.

        @note All sections added by this source are removed even if a later source extended that
            section. This can result in some sections or values being removed that were actually
            added by other sources loaded after the given source.
        @note Values overridden by the removed source will be removed, they will not be returned to
            the previous value prior to being overridden. This can result in some values being
            removed that were actually added by other sources loaded before the given source.
        @note Links to sections or values owned by the removed source will remain after the source
            is removed. This can result in some sections or values added by this source remaining
            after the source is removed.

        @param pSource Pointer to the existing source to remove.
    */
    virtual void RemoveConfigSource(IConfigSource *pSource) = 0;

    /**
        Returns the root configuration section that contains all the configuration data and
        sections.

        @return Pointer to the root configuration section.
    */
    virtual const ISection *GetConfiguration() = 0;

    /**
        Searches for a given child value by name.

        If a dot separated section hierarchy is specified, it will start searching beginning with
        the current section as the parent.  It will then traverse the section hierarchy and find
        the value by name in the section specified.  This version of FindValue cannot distinguish
        between a missing values and a values set to an empty string.

        @note If you need to find multiple values from the same section, then it is more efficient
        to use GetConfiguration() to get the root ISection and then use FindSection() to find the
        section containing the values you need to read.  Then use FindValue() to read each value.
        This approach avoids parsing the section hierarchy multiple times.

        @param strName Name of the section to retrieve.  Dot separated section hierarchy names
            are accepted.
        @return The value, or unchanged if not found.
    */
    virtual efd::utf8string FindValue(const efd::utf8string& strName) const = 0;

    /**
        Searches for a given child value by name(alternate interface).

        If a dot separated section hierarchy is specified, it will start searching beginning with
        the current section as the parent.  It will then traverse the section hierarchy and find
        the value by name in the section specified.  This version of FindValue can distinguish
        between missing values and values set to empty strings.

        @note If you need to find multiple values from the same section, then it is more efficient
        to use GetConfiguration to get the root ISection and then use FindSection to find the
        section containing the values you need to read.  Then use FindValue to read each value.
        This approach avoids parsing the section hierarchy multiple times.

        @param strName Name of the section to retrieve.  Dot separated section hierarchy names
            are accepted.
        @param o_value The value, or unchanged if not found.
        @return True if the value was found.
    */
    virtual bool FindValue(const efd::utf8string& strName, efd::utf8string& o_value) const = 0;

    /**
        Checks if the specified value represents a true value.

        If the value is equal to the string "true" (ignoring case) or the integer "1" then the
        value is considered true.  All other values are considered false.  If the value is not
        found at all then the defaultValue is returned.

        @param strName Name of the value to retrieve.  Dot separated section hierarchy names
            are accepted.
        @param defaultValue The return value if the specified strName is not found.
        @return True if the value represents a true value, false otherwise.
    */
    virtual bool IsTrue(const efd::utf8string& strName, bool defaultValue = false) const = 0;

    /**
        Checks if the specified value represents a false value.

        If the value is equal to the string "false" (ignoring case) or the integer "0" then the
        value is considered false.  All other values are considered true.  If the value is not
        found at all then the defaultValue is returned.

        @param strName Name of the value to retrieve.  Dot separated section hierarchy names
            are accepted.
        @param defaultValue The return value if the specified strName is not found.
        @return False if the value represents a false value, true otherwise.
    */
    virtual bool IsFalse(const efd::utf8string& strName, bool defaultValue = true) const = 0;
protected:
    /**
        A special version of AddConfigSource used by the ConfigSource base class to add any other
        included IniSource files. It is special in that the root and priority for the source is set
        by the caller before adding the source.

        @param pSource Pointer to the new source.
    */
    virtual void AddConfigSourceInternal(IConfigSource *pSource) = 0;
};

/// A SmartPointer for the IConfigManager class.
typedef efd::SmartPointer<IConfigManager> IConfigManagerPtr;

} // end namespace efd

#endif // EE_ICONFIGMANAGER_H
