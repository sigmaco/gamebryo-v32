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

#ifndef NISHADOWMATERIALSWAPPROCESSOR_H
#define NISHADOWMATERIALSWAPPROCESSOR_H

#include "NiMaterialSwapProcessor.h"
#include "NiMaterialInstance.h"
#include "NiTSet.h"

class NIMAIN_ENTRY NiShadowMaterialSwapProcessor : public NiMaterialSwapProcessor
{
    NiDeclareRTTI;

public:
    NiShadowMaterialSwapProcessor(NiMaterial* pkMaterial = NULL,
        unsigned int uiMaterialExtraData =
        NiMaterialInstance::DEFAULT_EXTRA_DATA);

    // Pre-processing function called before any objects are rendered.
    virtual void PreRenderProcessList(const NiVisibleArray* pkInput,
        NiVisibleArray& kOutput, void* pvExtraData);

    // Post-processing function called after the obejcts in the previous
    // ouptut array have been rendered by the render click.
    virtual void PostRenderProcessList(NiVisibleArray& kPreviousOutput,
        void* pvExtraData);

protected:
    NiTPrimitiveSet<const NiMaterial*> m_kOldMaterials;

};

NiSmartPointer(NiShadowMaterialSwapProcessor);

#include "NiShadowMaterialSwapProcessor.inl"

#endif  // #ifndef NISHADOWMATERIALSWAPPROCESSOR_H
