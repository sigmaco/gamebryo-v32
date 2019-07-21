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
#ifndef EE_PERVERTEXLIGHTINGPROCESSOR_H
#define EE_PERVERTEXLIGHTINGPROCESSOR_H

#include "egmToolServicesLibType.h"

#include <NiRenderListProcessor.h>
#include <NiBackToFrontSortProcessor.h>
#include <NiVisibleArray.h>
#include <NiNode.h>
#include <NiTPointerMap.h>

namespace egmToolServices
{

/**
    A render list processor which removes the normal, parallax, and bump
    maps from an object's texturing property to cause NiStandardMaterial
    to use per-vertex lighting as opposed to per-pixel.
    This processor caches the created NiTexturingProperties to avoid
    the speed penalty of creating new NiTexturingProperties for each render.
*/
class EE_EGMTOOLSERVICES_ENTRY PerVertexLightingProcessor : public NiBackToFrontSortProcessor
{
public:
    PerVertexLightingProcessor();
    virtual ~PerVertexLightingProcessor();

    virtual void PreRenderProcessList(const NiVisibleArray* pkInput,
        NiVisibleArray& kOutput, void* pvExtraData);

protected:
    NiTPointerMap<NiRenderObject*, NiTexturingPropertyPtr> m_kTextureProps;

    void PreRender(NiRenderObject* pkGeometry);
    void PostRender(NiRenderObject* pkGeometry);
    bool IsTransparent(const NiRenderObject& kObject);
};

} // end namespace egmToolServices

#endif
