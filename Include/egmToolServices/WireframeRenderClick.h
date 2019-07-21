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
#ifndef EE_WIREFRAMERENDERCLICK_H
#define EE_WIREFRAMERENDERCLICK_H

#include "egmToolServicesLibType.h"

#include <NiViewRenderClick.h>
#include "PropertySwapProcessor.h"

namespace egmToolServices
{

class EE_EGMTOOLSERVICES_ENTRY WireframeRenderClick : public NiViewRenderClick
{
public:
    WireframeRenderClick();
    virtual ~WireframeRenderClick();

protected:
    NiWireframeProperty* m_pkWireframeProperty;
    NiPropertyList* m_pkWirePropList;
    PropertySwapProcessor* m_pkPropertySwapProcessor;
};

NiSmartPointer(WireframeRenderClick);

} // namespace

#endif // EE_WIREFRAMERENDERCLICK_H
