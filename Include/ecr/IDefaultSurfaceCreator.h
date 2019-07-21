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
#ifndef EE_IDEFAULTSURFACECREATOR_H
#define EE_IDEFAULTSURFACECREATOR_H

#include "ecrLibType.h"


namespace ecr
{

// forward declaration
class RenderService;

/**
    By default the RenderService will create a RenderContext and call CreateRenderSurface during
    OnInit in order to create a default active surface. Applications that wish to create a
    different type of RenderContext or set specific settings on the render context and/or render
    surface can override the default creation by providing an instance of this interface prior to
    RenderService::OnInit being called. Call the RenderService::SetDefaultSurfaceCreator after
    construction of the RenderService, it is recommended this be done during OnPreInit of another
    service.
*/
class EE_ECR_ENTRY IDefaultSurfaceCreator
{
public:
    /**
        Method for creating a Render Context and an active Render Surface. This method is required
        to call RenderService::AddRenderContext on the resulting context and
        RenderService::SetActiveRenderSurface on the resulting surface. If this method returns
        false then the RenderServuce will create and activate a default context and surface.

        @param pRenderService The render service on which you must call AddRenderContext and
            SetActiveRenderSurface.
        @param color The default background color for the context. Implementations are free to
            ignore this color recommendation if desired.
        @return True if the context and surface were created, added and activated or false if the
            RenderService should proceed with creation of default context and surface.
    */
    virtual bool CreateDefaultSurface(RenderService* pRenderService, const efd::ColorA& color) = 0;

protected:
    /// Destructor
    virtual ~IDefaultSurfaceCreator() {}
};

} // end namespace ecr

#endif // EE_IDEFAULTSURFACECREATOR_H
