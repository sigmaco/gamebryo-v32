#pragma once
#ifndef EE_EXTRADATA_H
#define EE_EXTRADATA_H

#include <efd/RefCount.h>
#include <egf/egfLibType.h>
#include <efd/utf8string.h>

namespace egf
{

/**
    ExtraDataEntry are the building blocks of ExtraData - ExtraData stores
    a group of ExtraDataEntry objects which can be accessed by name and
    serve as extra data annotated onto flat models.
*/
struct EE_EGF_ENTRY ExtraDataEntry : public efd::RefCount
{
    efd::utf8string m_type;
    efd::utf8string m_key;
    efd::utf8string m_value;
};

typedef efd::SmartPointer<ExtraDataEntry> ExtraDataEntryPtr;

/**
    ExtraData represents a grouping of key-value pairs which can be used
    to annotate a FlatModel with extra information not explicitly specified
    but which may be useful for debugging or tools purposes.
*/
class EE_EGF_ENTRY ExtraData : public efd::RefCount
{
public:

    /**
        Default constructor.
    */
    ExtraData();

    /**
        Constructor which initializes the ExtraData given a name and type

        @param name name of this extra data block
        @param type type of this extra data block
    */
    ExtraData(const efd::utf8string& name, const efd::utf8string& type);

    /**
        Gets the name of this extra data block.
    */
    const efd::utf8string& GetName() const;

    /**
        Gets the type of this extra data block as a string.
    */
    const efd::utf8string& GetType() const;

    /**
        Adds an entry to this extra data block.

        @param type type of entry to add
        @param key key of the entry to add
        @param value value associated with the key
    */
    void AddEntry(
        const efd::utf8string& type,
        const efd::utf8string& key,
        const efd::utf8string& value);

    /**
        Gets an entry by its key.

        @param key key of the entry to get.
    */
    ExtraDataEntry* GetEntry(const efd::utf8string& key);

    /**
        Retrieves all the entries in this extra data set of the same type
        and returns them in a list.

        @param type type of entry to retrieve.
        @param o_entries the list that will contain the entries of the given type.
    */
    void GetEntriesOfType(const efd::utf8string& type,
        efd::list<ExtraDataEntryPtr>& o_entries);

    /**
        Retrieves all the entries in this extra data set of the same type
        and returns them in a map that maps an entry name to its ExtraDataEntry object.

        @param type type of entry to retrieve.
        @param o_entries the map that will contain the entries of the given type.
    */
    void GetEntriesOfType(const efd::utf8string& type,
        efd::map<efd::utf8string, ExtraDataEntryPtr>& o_entries);
private:
    efd::utf8string m_name;
    efd::utf8string m_type;

    typedef efd::map<efd::utf8string, ExtraDataEntryPtr> ExtraDataEntryByName;
    ExtraDataEntryByName m_entries;
};

typedef efd::SmartPointer<ExtraData> ExtraDataPtr;

}

#endif
