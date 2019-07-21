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


namespace efd
{

//------------------------------------------------------------------------------------------------
template<typename VertexData, bool AllowCycles, bool AllowForest>
DirectedGraph<VertexData, AllowCycles, AllowForest>::DirectedGraph()
    : m_nextMarker(0)
{
}

//------------------------------------------------------------------------------------------------
template<typename VertexData, bool AllowCycles, bool AllowForest>
bool DirectedGraph<VertexData, AllowCycles, AllowForest>::AddNode(const VertexData& node)
{
    Node* pNode = AddNodeHelper(node);
    return pNode != NULL;
}

//------------------------------------------------------------------------------------------------
template<typename VertexData, bool AllowCycles, bool AllowForest>
bool DirectedGraph<VertexData, AllowCycles, AllowForest>::AddDirectedEdge(
    const VertexData& from,
    const VertexData& to)
{
    bool bAdded = false;
    Node* pFromNode = FindOrAddNode(from, bAdded);
    if (!pFromNode)
    {
        // This should only fail if AllowForest is false and the from node would have started
        // a new tree.
        EE_ASSERT(AllowForest == false);
        return false;
    }
    Node* pToNode = FindNode(to);
    if (pToNode)
    {
        if (!AllowCycles && pToNode->HasDependency(pFromNode, GetNextMarker()))
        {
            // Prevent a cycle from being created when not allowed
            return false;
        }
        typename efd::list<Node*>::iterator it = pFromNode->m_dependencies.find(pToNode);
        if (it != pFromNode->m_dependencies.end())
        {
            // This dependency already exists
            return true;
        }
    }
    else
    {
        // Directly add a new node bypassing the normal forest check
        pToNode = &m_nodes[to];
        pToNode->m_value = to;
    }

    pFromNode->m_dependencies.push_back(pToNode);
    return true;
}

//------------------------------------------------------------------------------------------------
template<typename VertexData, bool AllowCycles, bool AllowForest>
bool DirectedGraph<VertexData, AllowCycles, AllowForest>::GetTopologicalOrder(
    efd::list<VertexData*>& o_topologicalOrder,
    SortFunction pfn)
{
    o_topologicalOrder.clear();

    // Start every node in the "not visited" state:
    for (typename efd::map<VertexData, Node>::iterator it = m_nodes.begin();
        it != m_nodes.end();
        ++it)
    {
        it->second.m_maxDepth = 0;
    }

    bool result = true;
    efd::vector<Node*> nodeList;
    nodeList.reserve(m_nodes.size());

    // Since we might have a forest of graphs, traverse down from every node. Even nodes
    // already visited may need to be traversed in order to update their max-depth.
    for (typename efd::map<VertexData, Node>::iterator it = m_nodes.begin();
        it != m_nodes.end();
        ++it)
    {
        efd::set<Node*> visitationStack;
        result &= it->second.Traverse(1, visitationStack, nodeList);
    }

    // Now we sort the resulting list by depth and by an optional secondary sort if the depth
    // is identical. The sort by depth generally pushes commonly depended upon items early in
    // the result list without violating the topological ordering requirements. Given how we
    // use this class in the ServiceManager this is likely to be the desired effect in the
    // event that a service forgets to register a dependency.
    typename GraphType::TopologicSorter sorter(pfn);
    EE_STL_NAMESPACE::stable_sort(nodeList.begin(), nodeList.end(), sorter);

    for (typename efd::vector<Node*>::iterator it = nodeList.begin();
        it != nodeList.end();
        ++it)
    {
        o_topologicalOrder.push_back(&(*it)->m_value);
    }

    return result;
}

//------------------------------------------------------------------------------------------------
template<typename VertexData, bool AllowCycles, bool AllowForest>
DirectedGraph<VertexData, AllowCycles, AllowForest>::Node::Node()
    : m_maxDepth(0)
{
}

//------------------------------------------------------------------------------------------------
template<typename VertexData, bool AllowCycles, bool AllowForest>
bool DirectedGraph<VertexData, AllowCycles, AllowForest>::Node::HasDependency(
    Node* pOther,
    efd::SInt32 visitationMarker)
{
    EE_ASSERT(visitationMarker < 0);
    if (m_maxDepth == visitationMarker)
    {
        // This node was already visited indicating a cyclical dependency, return false to
        // avoid infinite recursion.
        return false;
    }
    m_maxDepth = visitationMarker;

    for (typename efd::list<Node*>::iterator it = m_dependencies.begin();
        it != m_dependencies.end();
        ++it)
    {
        if (*it == pOther || (*it)->HasDependency(pOther, visitationMarker))
        {
            return true;
        }
    }
    return false;
}

//------------------------------------------------------------------------------------------------
template<typename VertexData, bool AllowCycles, bool AllowForest>
bool DirectedGraph<VertexData, AllowCycles, AllowForest>::Node::Traverse(
    efd::SInt32 depth,
    efd::set<Node*>& io_visitationStack,
    efd::vector<Node*>& o_nodeList)
{
    EE_ASSERT(depth >= 1);
    if (depth <= m_maxDepth)
    {
        // This node was already visited at a deeper depth, so just return.
        return true;
    }
    bool firstVisit = 0 == m_maxDepth;
    m_maxDepth = depth;

    if (0 != io_visitationStack.count(this))
    {
        // This node was already visited for this root item, return to avoid infinite
        // recursion in cyclical graphs. We return false to indicate that the resulting
        // topological order is not valid due to the cycle.
        return false;
    }
    io_visitationStack.insert(this);

    bool result = true;
    for (typename efd::list<Node*>::iterator it = m_dependencies.begin();
        it != m_dependencies.end();
        ++it)
    {
        // Add all of my dependent items before I add myself:
        result &= (*it)->Traverse(++depth, io_visitationStack, o_nodeList);
    }

    io_visitationStack.erase(this);

    // I might already be in the resulting list and am being re-iterated in order to set
    // a deeper max depth value. So only add myself if I'm not already in the list.
    if (firstVisit)
    {
        o_nodeList.push_back(this);
    }
    else
    {
        EE_ASSERT(o_nodeList.find(this) != o_nodeList.end());
    }

    return result;
}

//------------------------------------------------------------------------------------------------
template<typename VertexData, bool AllowCycles, bool AllowForest>
typename DirectedGraph<VertexData, AllowCycles, AllowForest>::Node*
DirectedGraph<VertexData, AllowCycles, AllowForest>::AddNodeHelper(const VertexData& node)
{
    Node* pNode = NULL;
    if (m_nodes.empty())
    {
        pNode = &m_nodes[node];
        pNode->m_value = node;
    }
    else if (AllowForest)
    {
        if (m_nodes.end() == m_nodes.find(node))
        {
            pNode = &m_nodes[node];
            pNode->m_value = node;
        }
    }
    return pNode;
}

//------------------------------------------------------------------------------------------------
template<typename VertexData, bool AllowCycles, bool AllowForest>
typename DirectedGraph<VertexData, AllowCycles, AllowForest>::Node*
DirectedGraph<VertexData, AllowCycles, AllowForest>::FindNode(const VertexData& node)
{
    typename efd::map<VertexData, Node>::iterator it = m_nodes.find(node);
    if (it != m_nodes.end())
    {
        return &it->second;
    }
    return NULL;
}

//------------------------------------------------------------------------------------------------
template<typename VertexData, bool AllowCycles, bool AllowForest>
typename DirectedGraph<VertexData, AllowCycles, AllowForest>::Node*
DirectedGraph<VertexData, AllowCycles, AllowForest>::FindOrAddNode(
    const VertexData& node,
    bool& o_bAdded)
{
    Node* pNode = FindNode(node);
    o_bAdded = pNode == NULL;
    if (o_bAdded)
    {
        pNode = AddNodeHelper(node);
    }
    return pNode;
}

//------------------------------------------------------------------------------------------------
template<typename VertexData, bool AllowCycles, bool AllowForest>
inline efd::SInt32 DirectedGraph<VertexData, AllowCycles, AllowForest>::GetNextMarker()
{
    return --m_nextMarker;
}

//------------------------------------------------------------------------------------------------
template<typename VertexData, bool AllowCycles, bool AllowForest>
DirectedGraph<VertexData, AllowCycles, AllowForest>::TopologicSorter::TopologicSorter(
    SortFunction pfn)
    : m_pfnSecondarySort(pfn)
{
}

//------------------------------------------------------------------------------------------------
template<typename VertexData, bool AllowCycles, bool AllowForest>
bool DirectedGraph<VertexData, AllowCycles, AllowForest>::TopologicSorter::operator ()(
    const Node* one,
    const Node* two)
{
    if (one->m_maxDepth > two->m_maxDepth)
    {
        return true;
    }
    else if (one->m_maxDepth == two->m_maxDepth && m_pfnSecondarySort)
    {
        return m_pfnSecondarySort(one->m_value, two->m_value);
    }
    return false;
}

//------------------------------------------------------------------------------------------------
} // end namespace efd
