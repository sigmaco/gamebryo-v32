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
#ifndef EE_ORDEREDMAP_H
#define EE_ORDEREDMAP_H

#include <efd/StdContainers.h>

namespace efd
{

/// OrderedMap is a container supporting both list-like ordering and map-like key based lookup.
/// It is implemented by using both a list and a map internally.
// DT20122 Add more std::list-like methods, mainly insert is needed.
// DT20121 Add more iterators.  We want to be able to use the map for a find and
//     then do operator ++ on the iterator to traverse the list order.
template< typename KEY, typename VALUE >
class OrderedMap
{
public:
    /// The node data that is stored in both the list and the map
    class NodeType : public MemObject
    {
    public:
        NodeType(const KEY& i_key, const VALUE& i_value);
        KEY first;
        VALUE second;
    };
    /// The type used for the list member
    typedef efd::list< NodeType* > OMList;
    /// The type used for the map member
    typedef efd::map< KEY, NodeType* > OMMap;
    /// The type used for iterating the OrderedMap. Traversal is performed in list order.
    typedef typename OMList::iterator iterator;

    /// Returns the begin iterator for the list member.
    iterator begin();

    /// Returns the end iterator for the list member.
    iterator end();

    /**
        Adds value to both the map and list members.

        @param i_key map key for the value to add
        @param i_value value to add to map and list
    */
    bool push_back(const KEY& i_key, const VALUE& i_value);

    /**
        Finds a value in the map member.

        @param i_key the key to find in the map
    */
    NodeType* find(const KEY& i_key);

    /**
        Finds a value in the map member.  Const version.

        @param i_key the key to find in the map
    */
    const NodeType* find(const KEY& i_key) const;

    /**
        Removes a value from both the map and list members.

        @param i_key the key to erase from both the map and list
    */
    bool erase(const KEY& i_key);

    /**
        Removes a value from both the map and list members.

        @param i_node the node to erase from both the map and list
    */
    bool erase(const NodeType* i_node);

    /**
        Removes a value from both the map and list members.

        @param it An iterator for the item to remove
    */
    iterator erase(iterator it);

    /// Clears both the map and list members.
    void clear();

    /// Returns the first element in the list member.
    NodeType* front();
    const NodeType* front() const;

    /// Returns the number of stored elements
    efd::UInt32 size() const;

    /// Returns true if the list member is empty.
    bool empty() const;

    /// Removes the first element from both the map and list members.
    bool pop_front();

    /**
        Removes the first element from both the map and list members.

        @param o_key map key for the first value in the list
        @param o_value the first value in the list
    */

    bool pop_front(KEY& o_key, VALUE& o_value);

protected:

    OMList m_list;
    OMMap  m_map;
};

} // end namespace efd

#include <efd/OrderedMap.inl>

#endif // EE_ORDEREDMAP_H
