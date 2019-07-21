// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not
// be copied or disclosed except in accordance with the terms of that
// agreement.
//
//      Copyright (c) 2006-2009 Todd Berkebile.
//      Copyright (c) 1996-2009 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Calabasas, CA 91302
// http://www.emergent.net

#ifndef EE_DIRECTEDGRAPH_H
#define EE_DIRECTEDGRAPH_H

#include <stlport/algorithm>

namespace efd
{

// We use constant boolean template arguments to alter the function of this class, so disable the
// warning about constant expressions (which is a very silly warning to trigger for a template
// parameter anyway and the compiler really should be more intelligent about that).
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4127) // warning C4127: conditional expression is constant
#endif

/**
    Storage for a directed graph. Can store either a forest of graphs or a single graph. Can
    compute a topological order (for non-cyclical graphs).

    @param VertexData The unique identifier for each node.
    @param AllowCycles Flag for whether cycles are allowed in the graph. Some operations, such as
        computing a topological order, are not valid on graphs that contain cycles.
    @param AllowForst Flag to control whether unconnected vertices can be stored in the graph. If
        true you can have multiple unrelated trees in the graph.
*/
template<
    typename VertexData,
    bool AllowCycles = false,
    bool AllowForest = true>
class DirectedGraph : public efd::MemObject
{
public:
    /// Convenience typedef for the templated type
    typedef DirectedGraph<VertexData, AllowCycles, AllowForest> GraphType;

    /// Constructor
    DirectedGraph();

    /**
        Will add a new node with no dependencies to the graph.

        @return True if the node was added, false if it was not. If the node is already in the
            graph or if the node would start a new tree and AllowForest is not enabled then this
            will return false.
    */
    bool AddNode(const VertexData& node);

    /**
        Will add nodes for the from and to vertices if needed and creates a directed edge between
        the specified nodes.

        @return True if the edge either already exists or was successfully created. False if the
            nodes could not be created (for example, the source node would create a separate tree
            in a graph that only allows one tree) or the specified edge is invalid (for example,
            would create a cycle in a graph that doesn't allow cycles).
    */
    bool AddDirectedEdge(const VertexData& from, const VertexData& to);

    /// Function for providing a secondary sort of the topological order in GetTopologicalOrder.
    typedef bool (*SortFunction)(const VertexData&, const VertexData&);

    /**
        Get a valid topological ordering of the directed graph(s). The resulting order has an
        additional sort applied based on traversal depth in the graph and further those items with
        the same traversal depth can have and additional sort applied on them if desired by
        providing an additional sort functor such as std::less

        @return True if the graph is acyclic and false if the graph has one or more cycles. When
            the graph contains cycles there is no Topological Order but we still return a list
            filled with all the nodes in the graph sorted as best as could be managed. The sort
            order of the VertexData data will indirectly determine the order in which cycles are
            output, the set of all nodes is walked in that order (depth-first from each sorted node)
            and the first node of a cycle visited will be the last node from that cycle in the list.
    */
    bool GetTopologicalOrder(efd::list<VertexData*>& o_topologicalOrder, SortFunction pfn = NULL);

protected:
    class Node
    {
    public:
        Node();

        /// The data for this node
        VertexData m_value;

        /// The deepest dependency depth at which this node was traversed. Used when computing the
        /// topological traversal order, we provide an additional sort so that the deepest results
        /// are first in the topological order. This allows a secondary sort to be applied to items
        /// of the same depth without violating the topological order.
        efd::SInt32 m_maxDepth;

        /// All the dependent nodes
        efd::list<Node*> m_dependencies;

        /// Determine if any directed path leads from this node to another node.
        bool HasDependency(Node* pOther, efd::SInt32 visitationMarker);

        /// Walk all the nodes starting with the current node to generate a topological order.
        bool Traverse(
            efd::SInt32 depth,
            efd::set<Node*>& io_visitationStack,
            efd::vector<Node*>& o_nodeList);
    };

    Node* AddNodeHelper(const VertexData& node);
    Node* FindNode(const VertexData& node);
    Node* FindOrAddNode(const VertexData& node, bool& o_bAdded);

    inline efd::SInt32 GetNextMarker();

    /// A sorting method compatible with stl "strict weak ordering" requirements that sorts first
    /// by the mode depth and then by a secondary method (for example, you might use
    /// EE_STL_NAMESPACE::less).
    class TopologicSorter
    {
    public:
        TopologicSorter(SortFunction pfn = NULL);

        bool operator ()(const Node* one, const Node* two);

        SortFunction m_pfnSecondarySort;
    };

    /// Storage for all nodes in the graph. Since we allow multiple independent trees to be stored
    /// in a single graph we keep track of all nodes here.
    efd::map<VertexData, Node> m_nodes;

private:
    /// A value used when finding dependencies. A unique value is used on every call to indicate
    /// that a given node has been visited already on this call. By using a unique marker value
    /// each time we don't have to reset the previous state on future traversals.
    efd::SInt32 m_nextMarker;
};

} // end namespace efd

#include <efd/DependencyGraph.inl>

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#endif // EE_DIRECTEDGRAPH_H
