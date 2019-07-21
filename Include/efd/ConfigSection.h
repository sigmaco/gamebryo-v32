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
#ifndef EE_CONFIGSECTION_H
#define EE_CONFIGSECTION_H

#include <efd/IConfigSection.h>

namespace efd
{

class IConfigSource;
class Section;

/// Implementation class for the configuration manager section entries, each of which contains a
/// single name/value pair and the associated data that goes with it.
class SectionEntry : public ISectionEntry
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(SectionEntry, kCLASSID_ConfigSection, ISectionEntry);
    /// @endcond

protected:
    // Grant protected access to the Section class.
    friend class Section;

    // Grant protected access to the ConfigManager class.
    friend class ConfigManager;

    /// Protected destructor, use reference counting
    ~SectionEntry() {}

public:
    /**
        Constructor for the section entry creates and initializes the section entry values.

        @param strValue Value of the entry.
        @param iPriority Priority number for the entry.
        @param pSource Pointer to the source that set the entry.
        @param isLink True if the entry is a link.
        @param pLink Link to the entry to which this entry links, or NULL.  If NULL and this
            entry is a link, it will attempt to locate the item on each Get().
    */
    SectionEntry(
        const efd::utf8string& strValue = efd::utf8string::NullString(),
        int iPriority = 0,
        IConfigSource *pSource = NULL,
        bool isLink = false,
        const SectionEntry *pLink = NULL);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual const efd::utf8string& GetValue() const;
    virtual int GetPriority() const;
    virtual int GetSourcePriority() const;
    virtual unsigned int GetSourceType() const;
    virtual const efd::utf8string& GetSourceName() const;
    virtual efd::utf8string GetSourceByString() const;

protected:
    /// Pointer to the root section for looking up links that did not exist at the time they were
    /// created.
    static Section *ms_pRoot;

    /// Boolean to specify whether m_pLink should be used.
    bool m_isLink;

    /// Pointer to the entry this links to or NULL if this is a real value.
    efd::SmartPointer<const SectionEntry> m_pLink;

    /// String value for this entry.
    efd::utf8string m_value;

    /// String value with variables in tack for this entry.
    efd::utf8string m_valueVars;

    /// Priority for this entry.
    int m_priority;

    /// Pointer to the source that last set the entry for this value.
    IConfigSourcePtr m_spSource;

    /// A list of section entries that are using this entry as a variable, so that when this entry
    /// changes, it can update the other entries.
    typedef efd::list<SectionEntry*> SectionUsersList;

    /// Specific list of section entries, as member data.
    SectionUsersList m_usedInVar;
};

/// Implementation class for the configuration manager section, which contains all the subsections
/// and name/value pairs for this section.
class Section : public ISection
{
public:
    /**
        Constructor for the section which creates and initializes the section values.

        @param strName Name of the section.
        @param pParent Pointer to the parent section for this section.
        @param pSource Pointer to the source that created this section.
        @param pLink Pointer to the linked section if this section is a link.
    */
    Section(
        const efd::utf8string& strName,
        Section *pParent,
        IConfigSource *pSource,
        Section *pLink = NULL);

    /// Destructor clears the map of sections and value entries.
    virtual ~Section();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual const efd::utf8string& GetName() const;
    virtual const ISection *GetParent() const;
    virtual ISection *GetParent();
    virtual SectionIter GetBeginChildSectionIterator() const;
    virtual SectionIter GetEndChildSectionIterator() const;
    virtual const ISection *FindSection(const efd::utf8string& strName) const;
    virtual ISection *FindSection(const efd::utf8string& strName);
    virtual ValueIter GetBeginValueIterator() const;
    virtual ValueIter GetEndValueIterator() const;
    virtual const efd::utf8string& FindValue(const efd::utf8string& strName) const;
    virtual bool FindValue(const efd::utf8string& strName, efd::utf8string& o_value) const;
    virtual bool IsTrue(const efd::utf8string& strName, bool defaultValue = false) const;
    virtual bool IsFalse(const efd::utf8string& strName, bool defaultValue = true) const;
    virtual const ISectionEntry *FindEntry(const efd::utf8string& strName) const;
    virtual ISectionEntry *FindEntry(const efd::utf8string& strName);
    virtual unsigned int GetSourceType() const;
    virtual const efd::utf8string& GetSourceName() const;
    virtual efd::utf8string GetSourceByString() const;
    virtual ISection *AddSection(const efd::utf8string& strName, IConfigSource *pSource);
    virtual bool AddValue(
        ISection *pRoot,
        const efd::utf8string& strName,
        const efd::utf8string& strValue,
        int iPriority,
        IConfigSource *pSource);
    virtual bool AddLink(
        ISection *pRoot,
        const efd::utf8string& strName,
        const efd::utf8string& strLink,
        const ISectionEntry *pILink,
        int iPriority,
        IConfigSource *pSource);
    virtual bool AddSectionLink(
        const efd::utf8string& strName,
        ISection *pILink,
        IConfigSource *pSource);
    virtual void WriteConfiguration(
        File *pFile,
        const efd::utf8string& strParents,
        const efd::utf8string& strIndent,
        bool bPrintRelative = true);
    virtual efd::utf8string GetMetricSectionName(const efd::utf8string& strPrefix = "") const;

    /// A method to remove all sub-sections or values that came from the given source.
    void RemoveConfigSource(IConfigSource *pSource);

protected:
    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void ConvertListName(efd::utf8string& io_strName);
    virtual void ConvertSectionListName(efd::utf8string& io_strName);

    /**
        Scans for and converts variables in the string into their actual values.
        Note:  The current version does not handles variable values that change after this call
        has been performed.  It also does not handles using variables whose value does not exist.
          pRoot : Pointer to the root section.
          pEntry : Pointer to entry that contains the variable to convert.
          pSource : Pointer to the source that created this section.
          curDepth : Recursion depth, used to prevent infinite recursion.
          return : True if a variable was found and successfully replaced.
    */
    virtual bool ConvertVariables(
        ISection *pRoot,
        SectionEntry *pEntry,
        IConfigSource *pSource,
        unsigned int curDepth);

    /**
        Recursively updates variables throughout a section, up to a recursion depth of 20.
          pRoot : Pointer to the root section.
          pEntry : Pointer to entry that contains the variable to update.
          pSource : Pointer to the source that created this section.
          curDepth : Recursion depth, used to prevent infinite recursion.
    */
    virtual bool UpdateVariables(
        ISection *pRoot,
        SectionEntry *pEntry,
        IConfigSource *pSource,
        unsigned int curDepth = 0);

protected:
    /// Pointer to the parent section if it exists. Not a smart point to avoid circular references.
    Section *m_pParent;

    /// Name of this section.
    efd::utf8string m_name;

    /// Map of the child sections.
    typedef efd::map<efd::utf8string, ISectionPtr> ChildSectionMap;

    /// Specific map of the child sections, as member data.
    ChildSectionMap m_sections;

    /// Map of the entry values in this section.
    typedef efd::map<efd::utf8string, ISectionEntryPtr> SectionEntryMap;

    /// Specific map of the entry values in this section, as member data.
    SectionEntryMap m_values;

    /// Pointer to the source that created this section.
    IConfigSourcePtr m_spSource;

    /// Pointer to the linked section if this section is a link.
    ISectionPtr m_pLink;
};

} // end namespace efd.

#endif  // EE_CONFIGSECTION_H
