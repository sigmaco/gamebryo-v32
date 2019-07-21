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

#ifndef NISKYRENDERVIEW_H
#define NISKYRENDERVIEW_H

#include <Ni3DRenderView.h>
#include <NiRenderClick.h>
#include "NiEnvironment.h"

/**
    This Ni3DRenderView class is specially designed to render sky objects to the view port. 
    The main customization of this class is it automatically ignores sending camera translation 
    data to the renderer whilst rendering objects in it's scene. This allows sky boxes and sky domes
    to always be centered about the camera without needing to explicitly move the boxes every frame.
*/
class NiSkyRenderView: public Ni3DRenderView
{
public:

    /// @cond EMERGENT_INTERNAL
    NiDeclareRTTI;
    /// @endcond

public:
    /**
        Constructor.
    */
    NiSkyRenderView(NiEnvironment* pkEnvironment = NULL, 
        NiCamera* pkCamera = NULL,
        NiCullingProcess* pkCullingProcess = NULL,
        bool bAlwaysUseCameraViewport = true);

    /**
        Overloaded function from Ni3DRenderView. This function sets the camera
        translation to zero temporarily whilst the camera data is sent to the 
        renderer for the skyview. 
    */
    virtual void SetCameraData(const NiRect<float>& kViewport);

    /**
        A callback function to be used by a render click. This callback
        allows the fog color of the renderer to be configured according to the 
        attmospheric color of the horizon.

        @param pkCurrentRenderClick The render click that the callback is being
            executed from.
        @param pvCallbackData A NiSkyRenderView pointer of the sky to modify the
            fog color of.
    */
    static bool CallbackClickConfigureFog(NiRenderClick* pkCurrentRenderClick,
        void* pvCallbackData);

protected:

    /// The environment that will be rendered in this view.
    NiEnvironmentPtr m_spEnvironment;
};

#endif