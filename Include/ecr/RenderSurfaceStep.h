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
#ifndef RENDERSURFACESTEP_H
#define RENDERSURFACESTEP_H

#include "ecrLibType.h"
#include <NiDefaultClickRenderStep.h>

namespace ecr
{

/**
    The RenderSurfaceStep class is custom NiDefaultClickRenderStep that is only
    meant to be used by a RenderSurface.  The RenderSurfaceStep class operates
    identical to NiDefaultClickRenderStep expect that it forces all PV geometry
    to be re-processes via NiRenderView::FORCE_PV_GEOMETRY_UPDATE.

    Since multiple NiRenderViews are shared across surfaces force PV geometry to
    be updated is required to prevent one surface from using the cached PV results
    from the previous surface in the same frame.
*/
class EE_ECR_ENTRY RenderSurfaceStep : public NiDefaultClickRenderStep
{
    NiDeclareRTTI;
public:

    /// Default constructor.
    RenderSurfaceStep();

    /// Destructor.
    virtual ~RenderSurfaceStep();

protected:

    virtual NiUInt32 GetFrameID();

};

NiSmartPointer(RenderSurfaceStep);

}; // namespace

#endif  // #ifndef RENDERSURFACESTEP_H
