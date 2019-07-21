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
#ifndef EE_NOTEXTURESRENDERCLICK_H
#define EE_NOTEXTURESRENDERCLICK_H

#include "egmToolServicesLibType.h"
#include <NiViewRenderClick.h>
#include <egmToolServices/PropertySwapProcessor.h>

namespace egmToolServices
{

/**
    A render click which swaps out texturing properties with an empty texturing
    property before rendering to turn off textures.
*/
class EE_EGMTOOLSERVICES_ENTRY NoTexturesRenderClick : public NiViewRenderClick
{
public:
    NoTexturesRenderClick();
    virtual ~NoTexturesRenderClick();

protected:
    NiTexturingProperty* m_pkTexturingProperty;
    NiPropertyList* m_pkTexturePropList;
    egmToolServices::PropertySwapProcessor* m_pkPropertySwapProcessor;
};

NiSmartPointer(NoTexturesRenderClick);

} // namespace

#endif // EE_NOTEXTURESRENDERCLICK_H
