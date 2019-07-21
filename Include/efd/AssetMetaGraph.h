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
#ifndef EE_ASSETMETAGRAPH_H
#define EE_ASSETMETAGRAPH_H

#include <efd/StdHashMap.h>
#include <efd/File.h>

namespace efd
{
// Forward declared
class Graph;
class SimpleGraph;

/**
    Class to represent the content of an Resource Description Framework (RDF) triple.
*/
enum NodeDescription
{
    NodeDescUri,
    NodeDescBlank,
    NodeDescLiteral,
    NodeDescNone
};

/**
    A Resource Description Framework (RDF) triple. Basically a Triple is a way of identifying the
    value (called the object) of a specific property (called a predicate) on a specific object
    (called a subject). For more information on the main concepts behind RDF see
    http://www.w3.org/2007/02/turtle/primer/.
*/
class EE_EFD_ENTRY Triple
{
public:
    Triple()
        : subject_desc(NodeDescUri)
        , predicate_desc(NodeDescUri)
        , object_desc(NodeDescLiteral)
    {}

    efd::utf8string subject;
    efd::utf8string predicate;
    efd::utf8string object;

    NodeDescription subject_desc;
    NodeDescription predicate_desc;
    NodeDescription object_desc;

    efd::Bool operator <(const efd::Triple& other) const
    {
        return subject < other.subject;
    }

    efd::Bool operator ==(const efd::Triple& other) const
    {
        return (subject == other.subject) &&
            (predicate == other.predicate) &&
            (object == other.object);
    }
};

/// A collection of Triples forms a TripleSet
typedef efd::vector<Triple> TripleSet;

/// Must be able to iterate over the collection of Triples
typedef efd::vector<Triple>::const_iterator TripleSetIterator;


/**
    Class used for parsing and serializing a Graph in Ntriples format
*/
class NTripleFormat
{
public:
    NTripleFormat();
    bool parse(const char* stream, Graph* graph);
    bool parse(const char* stream, SimpleGraph* graph);
    bool serialize(const efd::utf8string& filename, Graph* graph);
    bool serialize(const efd::utf8string& filename, SimpleGraph* graph);

private:
    enum ctxState
    {
        sNTriples,
        sSubject,
        sPWS,
        sPredicate,
        sOWS,
        sObject,
        sTriple
    };

    bool parse(const char* stream);
    void insert_node(const Triple& triple);
    void write_triple(const Triple& triple, File* file);
    void write_node(const utf8string& str, NodeDescription desc, File* file);

    Graph* m_graph;
    SimpleGraph* m_simple_graph;
    ctxState parserState;
    Triple add;
    char token[512];
    int tidx;
};

/**
    Enum value used to indicate the results of persisting a metadata file.
*/
enum GraphSaveResult
{
    GRAPH_SAVE_FAIL = -1,
    GRAPH_SAVE_SUCCESS,
    GRAPH_SAVE_UNCHANGED
};

/// Custom compare function signature used for querying. @see queryWithCompare()
typedef bool (*AssetQueryCompareFunc)(const Triple&, const Triple&);


/**
    The Graph class represents a collection of RDF triples. It provides methods for loading and
    persisting the graph using Ntriples text-based file format. It also provides methods for
    searching the graph to find triples that are partial matches of the search criteria.
*/
class EE_EFD_ENTRY Graph
{
public:
    /// @name Constructor
    //@{

    /**
        Create a Graph object.

        @param predicate The common predicate value for all triples in the Graph
        @param isIndexed Set to true to include a value->subject index for fast searching
        @param refValue Some graphs have the same object value for every triple. Specify that
            value in this parameter. This is used for specifying asset tags.
    */
    Graph(
        const efd::utf8string& predicate,
        efd::Bool isIndexed = false,
        const efd::utf8string& refValue = "");

    /// Default constructor
    Graph();
    //@}

    /// Load a graph from an Ntriples file
    bool load (const efd::utf8string& filename);

    /// Retrieve or set current loaded status
    bool isLoaded();

    /// Serialize a graph in Ntriples format. Will default to using the same
    /// filename previously passed to load().
    GraphSaveResult save(bool always_overwrite=false);

    /// Remove all data previously associated with the Graph, including persistent data
    void purge(efd::Bool removePersistent);

    /// Query the graph for all matching triples
    void query(const Triple& q, TripleSet& matches);
    /// Query the graph for all matching triples as indicated by the compare function
    void queryWithCompare(const Triple& q, AssetQueryCompareFunc comp, TripleSet& matches);

    /// Add a new property value. Any index associated with 'value' may also be updated
    /// if it is passed in as the 'index' parameter.
    bool append(const efd::utf8string& subject, const efd::utf8string& value);

    /// Delete all triples with matching 'subject' value
    void deleteAllSubject(const efd::utf8string& subject);

    /// Methods for combining graph contents with another TripleSet
    //@{
    static void intersection(TripleSet& set, const TripleSet& other);
    void intersection(TripleSet& set);
    static void unionize(TripleSet& set, const TripleSet& other);
    void unionize(TripleSet& set);
    static void unique_values(TripleSet& set, const TripleSet& other);
    static bool compareTriple(const Triple& a, const Triple& b);
    //@}

    /// Methods for inserting triples into the graph
    void merge_triple(const Triple& triple);

    /**
        Child class used for iterating the contents of the Graph
    */
    class Iterator
    {
    public:
        Iterator(Graph* graph);
        Iterator();

        /// @name Operator methods
        //@{
        const Triple& operator*() const;
        bool operator==(const Iterator& rhs) const;
        bool operator!=(const Iterator& rhs) const;
        Iterator& operator++();
        void begin();
        bool find(const efd::utf8string& key);
        //@}

    private:
        /// Local cache pointer of the graph being iterated
        Graph* m_graph;
        /// Signify the end of the graph was reached
        bool m_end;
        /// Internal storage for the current position of the cursor
        Triple m_cursor;
        /// Internal iterator over the Graph
        efd::hash_map<efd::utf8string, efd::utf8string>::const_iterator m_iterator;
    };

    /// These two classes will access private member variables
    friend class Iterator;
    friend class NTripleFormat;

private:
    bool m_isLoaded;
    bool m_isIndexed;
    bool m_dirty;
    efd::utf8string m_filename;

    /// Storage for the triples is a map of subject and object values
    typedef efd::hash_map<efd::utf8string, efd::utf8string> GraphStore;
    GraphStore m_store;
    efd::utf8string m_reference_property, m_reference_value;

    /// Additional storage for index, if used
    typedef efd::hash_map< efd::utf8string, efd::vector<efd::utf8string> > IndexContainer;
    IndexContainer m_index;

    void insert_triple(const Triple& triple);

    /**
        @name Index methods

        Some graphs may be indexed to improve the performance. For example, if we are searching a
        large number triples for all subjects that have a 'name' property of 'X', then it will be
        much faster to have an index of all such subjects mapped to the value of 'X'.
    */
    //@{
    /// add a triple to the index (triple.subject, m_property, value)
    void set_index(const Triple& triple);
    /// remove a triple from the index (triple.subject, m_property, value)
    void remove_index(const efd::utf8string& key);
    /// lookup value and return (triple.subject, m_property, value)
    bool index_lookup(const efd::utf8string& value, TripleSet& triples);
    //@}
};


/**
    The SimpleGraph class also represents a collection of RDF triples. It is not optimized in its
    internal storage mechanisms, and is only suitable for small graphs, such as those used for
    per-asset-file metadata. The main difference in the interface arises from the fact that
    SimpleGraphs can include any mix of un-related triples, whereas the Graph class only stores
    sets of triples that share the same predicate value.
*/
class EE_EFD_ENTRY SimpleGraph : public TripleSet
{
public:
    /// Constructor.
    SimpleGraph();

    /// Load a graph from an Ntriples file
    bool load(const efd::utf8string& filename);

    /// Retrieve or set current loaded status
    bool isLoaded(bool useCache = true);

    /// Serialize a graph in Ntriples format. Will default to using the same
    /// filename previously passed to load().
    GraphSaveResult save(bool always_overwrite = false);

    /// Insert a triple to the graph.
    void insert_triple(const Triple& triple);
    void merge_triple(const Triple& triple);

    /// Query for matching triples
    bool find_triple(const Triple& triple);
    void query(const Triple& q, TripleSet& matches);

private:
    bool m_isLoaded;
    bool m_dirty;
    efd::utf8string m_filename;
};

} // end namespace efd

#endif // EE_ASSETMETAGRAPH_H
