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
#ifndef EE_ICONFIGSECTION_H
#define EE_ICONFIGSECTION_H

#include <efd/IBase.h>
#include <efd/MemObject.h>
#include <efd/utf8string.h>
#include <efd/IConfigSource.h>
#include <efd/StdContainers.h>
#include <efd/efdClassIDs.h>

namespace efd
{

class ISection;
class ISectionEntry;
class File;

/// Define smart pointer for the ISection class.
typedef efd::SmartPointer<ISection> ISectionPtr;

/// Define smart pointer for the ISectionEntry class.
typedef efd::SmartPointer<ISectionEntry> ISectionEntryPtr;

/// Iterator for the section map.
typedef efd::map<efd::utf8string, ISectionPtr>::const_iterator SectionIter;

/// Iterator for the value map.
typedef efd::map<efd::utf8string, ISectionEntryPtr>::const_iterator ValueIter;

/// Interface to the configuration manager section entries, each of which contains a single
/// name/value pair and the associated data that goes with it.
class EE_EFD_ENTRY ISectionEntry : public efd::IBase
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_INTERFACE1(ISectionEntry, efd::kCLASSID_ISectionEntry, efd::IBase);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

public:
    /**
        Retrieves the value of this section entry.

        @return Section entry value.
    */
    virtual const efd::utf8string& GetValue() const = 0;

    /**
        Retrieves the priority of this section entry.

        @return int Priority value
    */
    virtual int GetPriority() const = 0;

    /**
        Retrieves the current priority(in case it changed) of the source from which this value
        came.

        @return int Priority value
    */
    virtual int GetSourcePriority() const = 0;

    /**
        Get the ConfigSource type of this section.
        @return Type of the ConfigSource this section is from.
    */
    virtual unsigned int GetSourceType() const = 0;

    /**
        Get the ConfigSource name of this section.
        @return Name of the ConfigSource this section is from.
    */
    virtual const efd::utf8string& GetSourceName() const = 0;

    /**
        Get the ConfigSource pretty human readable name of this section.
        @return Pretty human readableName of the ConfigSource this section is from.
    */
    virtual efd::utf8string GetSourceByString() const = 0;
};


/// Interface for the configuration manager section class, which contains all the subsections and
/// name/value pairs for this section.
class EE_EFD_ENTRY ISection : public efd::MemObject
{
    EE_DECLARE_CONCRETE_REFCOUNT;

protected:
    /// Virtual destructor.
    inline virtual ~ISection();

public:
    /**
        Retrieves the name of the section.

        @return The section name.
    */
    virtual const efd::utf8string& GetName() const = 0;

    /**
        Returns a pointer to the parent section of this section.

        This version returns a const section that cannot be modified.

        @return A pointer to the section parent.
    */
    virtual const ISection *GetParent() const = 0;

    /**
        Returns a pointer to the parent section of this section.

        This version returns a pointer to the section which can be modified.  So, if you are able
        to modify the current section, then you will be able to modify the parent.

        @return A pointer to the section parent.
    */
    virtual ISection *GetParent() = 0;

    /**
        Retrieves an iterator for cycling through all the sections that are children of this
        section.

        The iterator follows STL conventions.

        @return SectionIter A section iterator.
    */
    virtual SectionIter GetBeginChildSectionIterator() const = 0;

    /**
        Retrieves an end iterator for comparing against the begin iterator.

        Use as you would an STL end iterator.

        @return SectionIter An end iterator.
    */
    virtual SectionIter GetEndChildSectionIterator() const = 0;

    /**
        Searches for a given child section by name.

        If a dot separated section hierarchy is specified, it will start searching beginning with
        the current section as the parent.  This version returns a const section that cannot be
        modified.

        @param strName Name of the section to retrieve.  Dot separated section hierarchy names
            are accepted.
        @return A pointer to the requested section if found; otherwise NULL.
    */
    virtual const ISection* FindSection(const efd::utf8string& strName) const = 0;

    /**
        Searches for a given child section by name.

        If a dot separated section hierarchy is specified, it will start searching beginning with
        the current section as the parent.  This version returns a pointer to the section, which
        can be modified.  So if you are able to modify the current section, you will be able to
        modify the found section.

        @param strName Name of the section to retrieve.  Dot separated section hierarchy names
            are accepted.
        @return A pointer to the requested section if found; otherwise NULL.
    */
    virtual ISection* FindSection(const efd::utf8string& strName) = 0;

    /**
        Retrieves an iterator for cycling through all the values that are contained in this
        section.

        The iterator follows STL conventions.

        @return A value iterator or type ValueIter.
    */
    virtual ValueIter GetBeginValueIterator() const = 0;

    /**
        Retrieves an end iterator for comparing against the begin iterator.

        Use as you would an STL end iterator.

        @return A value iterator or type ValueIter.
    */
    virtual ValueIter GetEndValueIterator() const = 0;

    /**
        Searches for a given child value by name.

        If a dot separated section hierarchy is specified, it will start searching beginning with
        the current section as the parent.  It will then traverse the section hierarchy and find
        the value by name in the section specified.  This version returns a const value string
        that cannot be modified.

        @param strName Name of the section to retrieve.  Dot separated section hierarchy names
            are accepted.
        @return The value if found or an empty string if not found.
    */
    virtual const efd::utf8string& FindValue(const efd::utf8string& strName) const = 0;

    /**
        Searches for a given child value by name.

        If a dot separated section hierarchy is specified, it will start searching beginning with
        the current section as the parent.  It will then traverse the section hierarchy and find
        the value by name in the section specified.  This version of FindValue() supports setting
        empty strings.  This version returns a reference to a value string, which can be modified.

        @param strName Name of the value to retrieve.  Dot separated section hierarchy names
            are accepted.
        @param[out] o_value Value, or unchanged if not found.

        @return bool True if the value was found.
    */
    virtual bool FindValue(
        const efd::utf8string& strName,
        efd::utf8string& o_value) const = 0;

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

    /**
        Searches for a given child value by name as does FindValue(), but it returns the entire
        entry structure so that the source and priority may be accessed by the application.

        If a dot separated section hierarchy is specified, it will start searching beginning with
        the current section as the parent.  It will then traverse the section hierarchy and find
        the entry by name in the section specified.  This version returns a const section entry
        that cannot be modified.

        @param strName Name of the section to retrieve.  Dot separated section hierarchy names
            are accepted.
        @return const ISectionEntry * : Pointer to the entry class, or NULL if not found.
    */
    virtual const ISectionEntry *FindEntry(const efd::utf8string& strName) const = 0;

    /**
        Searches for a given child value by name as does FindValue(), but it returns the entire
        entry structure so that the source and priority may be accessed by the application.

        If a dot separated section hierarchy is specified, it will start searching beginning with
        the current section as the parent.  It will then traverse the section hierarchy and find
        the entry by name in the section specified.  This version returns a non-const pointer if
        you have a non-const section.

        @param strName Name of the section to retrieve.  Dot separated section hierarchy names
            are accepted.
        @return const ISectionEntry * : Pointer to the entry class, or NULL if not found.
    */
    virtual ISectionEntry *FindEntry(const efd::utf8string& strName) = 0;

    /**
        Get the ConfigSource type of this section.
        @return Type of the ConfigSource this section is from.
    */
    virtual unsigned int GetSourceType() const = 0;

    /**
        Get the ConfigSource name of this section.
        @return Name of the ConfigSource this section is from.
    */
    virtual const efd::utf8string& GetSourceName() const = 0;

    /**
        Get the ConfigSource pretty human readable name of this section.
        @return Pretty human readableName of the ConfigSource this section is from.
    */
    virtual efd::utf8string GetSourceByString() const = 0;

    /**
        Adds a new section as a child of the current section.

        If a dot separated section hierarchy is specified, it will add the section(s) as a child
        of the current section.  If a section exists, it will use that section; otherwise it will
        add the new section specified.

        @note A section name may not contain the characters specified by
            IConfigManager::kIllegalSectionChars.

        @param strName Name of the section to retrieve.  Dot separated section hierarchy names
            are accepted.
        @param pSource Pointer to the source that added the section.
        @return ISection * : Pointer to the section specified(regardless of whether it was added
            or an existing section was found), or NULL if the section names specified are illegal.
    */
    virtual ISection *AddSection(
        const efd::utf8string& strName,
        IConfigSource *pSource) = 0;

    /**
        Adds a new value as a child of the current section.

        If a dot separated section hierarchy is specified, it will add the required section(s) as
        a child of the current section and then as the name/value pair to the last section just as
        if AddSection() were called first.

        @note A value name may not contain the characters specified by
            IConfigManager::kIllegalNameChars.

        @param pRoot Root section, so that it can find variables.
        @param strName Name of the section to retrieve.  Dot separated section hierarchy names
            are accepted.
        @param strValue Value string to associate with the name specified.
        @param iPriority Priority of the name/value pair.
        @param pSource Pointer to the source that added the name/value pair.
        @return bool True if the value was added; false if the name already exists with a higher
            priority.
    */
    virtual bool AddValue(
        ISection *pRoot,
        const efd::utf8string& strName,
        const efd::utf8string& strValue,
        int iPriority,
        IConfigSource *pSource) = 0;

    /**
        Adds a new value link as a child of the current section.

        A link simply points the given name to the value of another entry in the configuration.
        It creates a true link, not a copy, so that if the original information changes, the link
        will still point to the updated information.  If a dot separated section hierarchy is
        specified, it will add the required section(s) as a child of the current section and then
        add the link to the last section the same as if AddSection() were called first.

        @note A link name may not contain the characters specified by
            IConfigManager::kIllegalNameChars.

        @param pRoot Root section, so that it can find variables.
        @param strName Name of the section to retrieve.  Dot separated section hierarchy names
            are accepted.
        @param strLink Name of the entry to which to point.
        @param pILink Entry to which to point.
        @param iPriority Priority of the name/value pair.
        @param pSource Pointer to the source that added the name/value pair.
        @return bool True if the value was added; false if the name already exists with a higher
            priority.
    */
    virtual bool AddLink(
        ISection *pRoot,
        const efd::utf8string& strName,
        const efd::utf8string& strLink,
        const ISectionEntry *pILink,
        int iPriority,
        IConfigSource *pSource) = 0;

    /**
        Adds a new section link as a child of the current section.

        A link simply points the given name to another section in the configuration.  It creates a
        true link, not a copy, so that if the original information changes the link will still
        point to the updated information.  If a dot separated section hierarchy is specified, it
        will add the required section(s) as a child of the current section and then add the link
        to the last section as if AddSection() were called first.

        @param strName Name of the section to retrieve.  Dot separated section hierarchy names
            are accepted.
        @param pILink Section to which to point.
        @param pSource Pointer to the source that added the name/value pair.
        @return bool True if the value was added; false if the name already exists with a higher
            priority.
    */
    virtual bool AddSectionLink(
        const efd::utf8string& strName,
        ISection *pILink,
        IConfigSource *pSource) = 0;

    /**
        Writes out a copy of the current configuration in the INI file style.

        @note This method is called by the IConfigManager::WriteConfiguration() method to write
            this section.  It is not recommended to call this method directly.

        @param pFile Pointer to an open file into which to write the configuration.
        @param strParents Dot separated string of the parents of this section.
        @param strIndent String of spaces to use to create the indent level.
        @param bPrintRelative True if the output should be formatted using the relative section
            style; false for absolute section names.
    */
    virtual void WriteConfiguration(
        efd::File *pFile,
        const efd::utf8string& strParents,
        const efd::utf8string& strIndent,
        bool bPrintRelative = true) = 0;

    /**
        Generates a metric name for a section by adding each section parent name to the prefix
        string provided with a dot separating each name in all caps.

        @param strPrefix Prefix of the metric name.

        @return Final metric name containing all the parent section names.
    */
    virtual efd::utf8string GetMetricSectionName(const efd::utf8string& strPrefix = "") const = 0;

protected:

    /*
        Searches for the reserved list character IConfigManager::kNameListChar.
        If found, it replaces the character with a unique number in sequence.
          strName : String for the entry name.
    */
    virtual void ConvertListName(efd::utf8string& io_strName) = 0;

    /*
        Searches for the reserved list character IConfigManager::kNameListChar.
        If found, it replaces the character with a unique number in sequence.
          strName : String for the section name.
    */
    virtual void ConvertSectionListName(efd::utf8string& io_strName) = 0;
};

} // end namespace efd.

#include <efd/IConfigSection.inl>

#endif // EE_ICONFIGSECTION_H
