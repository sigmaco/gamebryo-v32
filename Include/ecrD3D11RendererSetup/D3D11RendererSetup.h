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
#ifndef EE_D3D11RENDERERSETUP_H
#define EE_D3D11RENDERERSETUP_H

#include <ecrD3D11RendererSetup/ecrD3D11RendererSetupLibType.h>
#include <ecrD3D11RendererSetup/ecrD3D11RendererSetupSDM.h>
#include <NiBaseRendererSetup.h>

class D3D11RendererOptionsView;

namespace ecr
{

class D3D11RendererOptionsView;

/**
    D3D11RendererSetup is the NiBaseRendererSetup that creates a D3D11 renderer.
*/

class EE_ECRD3D11RENDERERSETUP_ENTRY D3D11RendererSetup : public NiBaseRendererSetup
{
public:
    /// @cond EMERGENT_INTERNAL

    /// @name Construction and Destruction
    //@{
    /// Constructor.
    D3D11RendererSetup();
    /// Destructor.
    virtual ~D3D11RendererSetup();
    //@}

    /// Returns the NiBaseRendererOptionsView for this setup object.
    virtual NiBaseRendererOptionsView* GetRenderOptionsView(
        NiRendererSettings* pSettings);
    /// Releases the NiBaseRendererOptionsView for this setup object.
    virtual void ReleaseRendererOptionsView(NiBaseRendererOptionsView* pROV);

    /// Returns which renderer this object is responsible for setting up.
    virtual efd::SystemDesc::RendererID GetRendererID() const;

    /// Creates static instance of this class.
    static void _SDMInit();
    /// Releases static instance of this class.
    static void _SDMShutdown();

    /// @endcond

protected:
    virtual NiRendererPtr CreatePlatformRenderer(
        NiRendererSettings* pRendererSettings,
        NiWindowRef pWndDevice,
        NiWindowRef pWndFocus);

    D3D11RendererOptionsView* m_pROV;

    static D3D11RendererSetup* ms_pRendererSetup;
};

static ecrD3D11RendererSetupSDM ecrD3D11RendererSetupSDMObject;

}   // End namespace ecr.

#endif // EE_D3D11RENDERERSETUPPCH_H
