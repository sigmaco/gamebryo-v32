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
#ifndef NIALPHACONTROLLER_H
#define NIALPHACONTROLLER_H

#include "NiFloatInterpController.h"


class NIANIMATION_ENTRY NiAlphaController : public NiFloatInterpController
{
    NiDeclareRTTI;
    NiDeclareClone(NiAlphaController);
    NiDeclareStream;
    NiDeclareViewerStrings;

public:
    NiAlphaController();

    virtual void Update(float fTime);
    virtual bool UpdateValue(float fTime, float fFloat,
        unsigned short usIndex = 0);

protected:
    // Virtual function overrides from base classes.
    virtual bool InterpTargetIsCorrectType(NiObjectNET* pkTarget) const;
    virtual void GetTargetFloatValue(float& fValue);
};

typedef efd::SmartPointer<NiAlphaController> NiAlphaControllerPtr;

#endif

