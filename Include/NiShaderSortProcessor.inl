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

//--------------------------------------------------------------------------------------------------
inline void NiShaderSortProcessor::ClearBuckets()
{
    m_uiActiveBuckets = 0;
}

//--------------------------------------------------------------------------------------------------
inline void NiShaderSortProcessor::ClearNodePool()
{
    m_uiActiveNodes = 0;
}

//--------------------------------------------------------------------------------------------------
inline void NiShaderSortProcessor::ClearPerEffectBucketPool()
{
    m_uiActiveEffectBuckets = 0;
}

//--------------------------------------------------------------------------------------------------
inline NiShaderSortProcessor::RenderObjectBucket* NiShaderSortProcessor::GetFreeBucket()
{
    if (m_uiActiveBuckets == m_kMeshBuckets.GetAllocatedSize())
    {
        // Double the size of the array
        m_kMeshBuckets.SetSize((m_uiActiveBuckets > 0) ? (m_uiActiveBuckets * 2) : 16);

        for (NiUInt32 uiBucketID = m_uiActiveBuckets;
            uiBucketID < m_kMeshBuckets.GetAllocatedSize(); uiBucketID++)
        {
            RenderObjectBucket* pkBucket = NiNew RenderObjectBucket();
            pkBucket->m_pkEffectStateMap = NiNew
                NiTPointerMap<NiDynamicEffectState*, PerEffectBucket*>(m_uiInitPrimeMapSize);
            m_kMeshBuckets.SetAt(uiBucketID, pkBucket);
        }
    }

    RenderObjectBucket* pkRet = m_kMeshBuckets.GetAt(m_uiActiveBuckets);

    pkRet->m_pkMatInstanceKey = NULL;
    pkRet->m_pkRenderObjectList = NULL;
    pkRet->m_pkEffectStateMap->RemoveAll();

    m_uiActiveBuckets++;

    return pkRet;
}

//--------------------------------------------------------------------------------------------------
inline NiShaderSortProcessor::RenderObjectNode* NiShaderSortProcessor::GetFreeRONode()
{
    if (m_uiActiveNodes == m_kNodePool.GetAllocatedSize())
    {
        // Double the size of the array
        m_kNodePool.SetSize((m_uiActiveNodes > 0) ? (m_uiActiveNodes * 2) : 16);

        for (NiUInt32 uiNodeID = m_uiActiveNodes;
            uiNodeID < m_kNodePool.GetAllocatedSize(); uiNodeID++)
        {
            m_kNodePool.SetAt(uiNodeID, NiNew RenderObjectNode());
        }
    }

    RenderObjectNode* pkRet = m_kNodePool.GetAt(m_uiActiveNodes);
    pkRet->m_pkRenderObject = NULL;
    pkRet->m_pkNext = NULL;

    m_uiActiveNodes++;

    return pkRet;
}

//--------------------------------------------------------------------------------------------------
inline NiShaderSortProcessor::PerEffectBucket* NiShaderSortProcessor::GetFreePerEffectBucket()
{
    if (m_uiActiveEffectBuckets == m_kEffectHeadPool.GetAllocatedSize())
    {
        // Double the size of the array
        m_kEffectHeadPool.SetSize(
            (m_uiActiveEffectBuckets > 0) ? (m_uiActiveEffectBuckets * 2) : 16);

        for (NiUInt32 ui = m_uiActiveEffectBuckets;
            ui < m_kEffectHeadPool.GetAllocatedSize(); ui++)
        {
            m_kEffectHeadPool.SetAt(ui, NiNew PerEffectBucket());
        }
    }

    PerEffectBucket* pkResult = m_kEffectHeadPool.GetAt(m_uiActiveEffectBuckets);

    pkResult->m_pkHead = NULL;
    pkResult->m_pkTail = NULL;

    m_uiActiveEffectBuckets++;

    return pkResult;
}

//--------------------------------------------------------------------------------------------------
