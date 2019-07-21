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
#ifndef NITIMESYNCCONTROLLER_H
#define NITIMESYNCCONTROLLER_H

#include "NiShaderTimeController.h"
#include "NiFloatExtraData.h"

class NIMAIN_ENTRY NiTimeSyncController : public NiShaderTimeController
{
    NiDeclareRTTI;
    NiDeclareClone(NiTimeSyncController);
    NiDeclareStream;
    NiDeclareViewerStrings;

public:
    NiTimeSyncController();
    virtual ~NiTimeSyncController();

    virtual void Update(float fTime);

    // *** begin Emergent internal use only ***
    virtual void GuaranteeKeysAtStartAndEnd(float fStartTime, float fEndTime);

    // Overridden from NiTimeController so that m_spExtraData can be set
    // appropriately.
    virtual void SetTarget(NiObjectNET* pkTarget);

    virtual bool CanBeExtracted() const;
    virtual bool TargetIsRequiredType() const;
    // *** end Emergent internal use only ***

    virtual bool IsStreamable() const;

protected:

    NiFloatExtraDataPtr m_spExtraData;

};

NiSmartPointer(NiTimeSyncController);

#include "NiTimeSyncController.inl"

#endif  // #ifndef NITIMESYNCCONTROLLER_H
