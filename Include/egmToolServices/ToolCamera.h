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
#ifndef EE_TOOLCAMERA_H
#define EE_TOOLCAMERA_H

#include "egmToolServicesLibType.h"
#include "egmToolServicesClassIDs.h"

#include <NiCamera.h>
#include <NiSmartPointer.h>

namespace egmToolServices
{

class EE_EGMTOOLSERVICES_ENTRY ToolCamera : public NiCamera
{
public:
    ToolCamera();

    void SetFOV(const efd::Float32 fov);
    efd::Float32 GetFOV() const;

    void Zoom(const efd::Float32 deltaZoom);

    ecr::RenderSurface* m_pRenderSurface;

    bool m_invert;
    efd::Float32 m_zoom;
    efd::Float32 m_fov;

    efd::utf8string m_displayName;

    egf::EntityID m_boundEntity;
    bool m_boundEntityDirty;
};

NiSmartPointer(ToolCamera);

} // namespace

#endif // EE_TOOLCAMERA_H
