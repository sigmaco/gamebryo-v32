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
#ifndef EE_ECRPCH_H
#define EE_ECRPCH_H

#if defined(EE_USE_PCH)

#include <efd/efdPCH.h>
#include <egf/egfPCH.h>

#include <NiVersion.h>
#include <NiMeshLib.h>
#include <NiParticle.h>
#include <NiCollision.h>

// Platform specific renderer includes. Aborts if a non-supported platform is found.
#if defined (EE_PLATFORM_XBOX360)
    #include <NiXenonRenderer.h>
#elif defined (EE_PLATFORM_WIN32)
    #include <NiDX9Renderer.h>
    #include <NiD3D10Renderer.h>
    #include <ecrD3D11Renderer/D3D11Renderer.h>
#elif defined (EE_PLATFORM_PS3)
    #include <NiPS3Renderer.h>
#elif defined (EE_PLATFORM_LINUX)
    #error Linux not supported by ecr!
#else
    #error Unknown platform!
#endif

#include <egf/egfLogIDs.h>

#endif // EE_USE_PCH

#endif // EE_ECRPCH_H
