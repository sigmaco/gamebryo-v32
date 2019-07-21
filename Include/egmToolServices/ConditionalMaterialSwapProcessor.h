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
#ifndef EE_CONDITIONALMATERIALSWAPPROCESSOR_H
#define EE_CONDITIONALMATERIALSWAPPROCESSOR_H

#include "egmToolServicesLibType.h"

#include <NiMaterialSwapProcessor.h>

namespace egmToolServices
{
/**
    A special NiMaterialSwapProcessor which inspects the ExtraData on a RenderObject before doing
    a material swap.  If there is a piece of ExtraData with the name "NiNoMaterialSwap," the
    material will not be swapped.
    
    This is used for when certain objects in a render view should not have their material swapped
    but need to be in the same render click as objects that do require their material swapped.
*/
class EE_EGMTOOLSERVICES_ENTRY ConditionalMaterialSwapProcessor : public NiMaterialSwapProcessor
{
    NiDeclareRTTI;

public:
    ConditionalMaterialSwapProcessor(NiMaterial* pkMaterial = NULL,
        unsigned int uiMaterialExtraData =
        NiMaterialInstance::DEFAULT_EXTRA_DATA);

    // Pre-processing function called before any objects are rendered.
    virtual void PreRenderProcessList(const NiVisibleArray* pkInput,
        NiVisibleArray& kOutput, void* pvExtraData);
};

NiSmartPointer(ConditionalMaterialSwapProcessor);

} // namespace

#endif // EE_CONDITIONALMATERIALSWAPPROCESSOR_H
