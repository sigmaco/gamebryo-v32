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
#ifndef EE_CAMERABUILTINS_H
#define EE_CAMERABUILTINS_H

#include <egf/Entity.h>
#include "egmSampleLibType.h"

namespace egmSample
{

EE_EGMSAMPLE_ENTRY egf::EntityID GetActiveCamera();

EE_EGMSAMPLE_ENTRY void ActivateCamera(egf::EntityID);

EE_EGMSAMPLE_ENTRY void DeactivateCamera(egf::EntityID);

EE_EGMSAMPLE_ENTRY void SetLongitudinalMovement(egf::EntityID, efd::Float32 magnitude);

EE_EGMSAMPLE_ENTRY void SetLateralMovement(egf::EntityID, efd::Float32 magnitude);

EE_EGMSAMPLE_ENTRY void SetSubject(egf::EntityID, egf::EntityID);

} // end namespace egmSample

#endif // EE_CAMERABUILTINS_H
