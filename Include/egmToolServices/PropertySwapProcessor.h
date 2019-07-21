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
#ifndef EE_PROPERTYSWAPPROCESSOR_H
#define EE_PROPERTYSWAPPROCESSOR_H

#include "egmToolServicesLibType.h"

#include <NiRenderListProcessor.h>
#include <NiProperty.h>

namespace egmToolServices
{

class EE_EGMTOOLSERVICES_ENTRY PropertySwapProcessor : public NiRenderListProcessor
{
    NiDeclareRTTI;

public:
    inline PropertySwapProcessor(NiPropertyList* pkPropertyList);

    // Pre-processing function called before any objects are rendered.
    virtual void PreRenderProcessList(const NiVisibleArray* pkInput, NiVisibleArray& kOutput,
        void* pvExtraData);

    // Functions for accessing the property list.
    inline void SetPropertyList(NiPropertyList* pkPropertyList);
    inline NiPropertyList* GetPropertyList() const;

protected:
    // The list of properties to use when rendering.
    NiPropertyList* m_pkPropertyList;
};

NiSmartPointer(PropertySwapProcessor);

} // namespace

#include "PropertySwapProcessor.inl"

#endif  // #ifndef EE_PROPERTYSWAPPROCESSOR_H
