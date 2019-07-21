// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not
// be copied or disclosed except in accordance with the terms of that
// agreement.
//
//      Copyright (c) 1996-2008 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Calabasas, CA 91302
// http://www.emergent.net

#ifndef NISHADOWSORTPROCESSOR_H
#define NISHADOWSORTPROCESSOR_H

#include "NiMaterialSwapProcessor.h"
#include "NiMaterial.h"
#include "NiMaterialInstance.h"
#include "NiTSet.h"

class NIMAIN_ENTRY NiShadowSortProcessor : public NiMaterialSwapProcessor
{
    NiDeclareRTTI;

public:
    inline NiShadowSortProcessor(
        NiMaterial* pkMaterial = NULL,
        unsigned int uiMaterialExtraData = NiMaterialInstance::DEFAULT_EXTRA_DATA);
    virtual ~NiShadowSortProcessor();

    // Pre-processing function called before any objects are rendered.
    virtual void PreRenderProcessList(
        const NiVisibleArray* pkInput,
        NiVisibleArray& kOutput,
        void* pvExtraData);

    virtual void ReleaseCaches();
protected:
    NiTPrimitiveSet<NiMaterialInstance*> m_kBatchKeys;
    NiTPrimitiveSet<NiVisibleArray*> m_kMeshBuckets;

    NiTPrimitiveSet<const NiMaterial*> m_kOldMaterials;
};

NiSmartPointer(NiShadowSortProcessor);

#include "NiShadowSortProcessor.inl"

#endif  // #ifndef NISHADOWSORTPROCESSOR_H
