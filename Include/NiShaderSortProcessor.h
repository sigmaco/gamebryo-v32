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

#ifndef NISHADERSORTPROCESSOR_H
#define NISHADERSORTPROCESSOR_H

#include "NiAlphaSortProcessor.h"
#include "NiMaterialInstance.h"
#include "NiTSet.h"

class NIMAIN_ENTRY NiShaderSortProcessor : public NiAlphaSortProcessor
{
    NiDeclareRTTI;

public:
    NiShaderSortProcessor(
        NiUInt32 uiBucketSize = 32,
        NiUInt32 uiPrimeMapSize = 37,
        NiUInt32 uiNodePoolSize = 512,
        NiUInt32 uiEffectPoolSize = 128);
    virtual ~NiShaderSortProcessor();

    // Pre-processing function called before any objects are rendered.
    virtual void PreRenderProcessList(const NiVisibleArray* pkInput,
        NiVisibleArray& kOutput, void* pvExtraData);

    virtual void ReleaseCaches();
protected:

    // Linked List node for storing NiRenderObjects a set of
    // NiRenderObjects in a way that allows for easy grouping.
    class RenderObjectNode : public NiMemObject
    {
    public:
        RenderObjectNode* m_pkNext;
        NiRenderObject* m_pkRenderObject;
    };

    // In each bucket, there is a sub-bucket for each effect-state
    class PerEffectBucket : public NiMemObject
    {
    public:
        RenderObjectNode* m_pkHead;
        RenderObjectNode* m_pkTail;
    };

    // Bucket of NiRenderObjects that all use the same NiShader.
    // The bucket contains a NiMaterialInstance 'key' that references the
    // NiShader for the bucket, a linked-list of NiRenderObjects in the bucket,
    // and hash map that to nodes in the linked list key'd off of their effect state.
    // This allows for all NiRenderObjects to be easily grouped in the linked list
    // by their NiDynamicEffectState.
    class RenderObjectBucket : public NiMemObject
    {
    public:
        NiMaterialInstance* m_pkMatInstanceKey;

        RenderObjectNode* m_pkRenderObjectList;
        NiTPointerMap<NiDynamicEffectState*, PerEffectBucket*>* m_pkEffectStateMap;
    };

    inline void ClearBuckets();
    inline RenderObjectBucket* GetFreeBucket();

    inline void ClearNodePool();
    inline RenderObjectNode* GetFreeRONode();

    inline void ClearPerEffectBucketPool();
    inline PerEffectBucket* GetFreePerEffectBucket();

    NiVisibleArray m_kTempVisibleArray;
    NiVisibleArray m_kNoSortVisibleArray;

    NiTPrimitiveArray<RenderObjectBucket*> m_kMeshBuckets;
    NiTPrimitiveArray<RenderObjectNode*> m_kNodePool;
    NiTPrimitiveArray<PerEffectBucket*> m_kEffectHeadPool;

    NiUInt32 m_uiActiveNodes;
    NiUInt32 m_uiActiveBuckets;
    NiUInt32 m_uiActiveEffectBuckets;

    NiUInt32 m_uiInitPrimeMapSize;
};

NiSmartPointer(NiShaderSortProcessor);

#include "NiShaderSortProcessor.inl"

#endif  // #ifndef NIBATCHSORTPROCESSOR_H
