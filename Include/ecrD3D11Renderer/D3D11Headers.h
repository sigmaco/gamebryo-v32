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
#ifndef EE_D3D11HEADERS_H
#define EE_D3D11HEADERS_H

/** @file D3D11Headers.h
    This header file contains the various D3D11 header files needed by the ecrD3D11Renderer library.
*/

#include <efd/OS.h>

// Include so _IID_ID3D11ShaderReflection is defined.
#include <initguid.h>

#include <D3D11.h>
#include <D3DX11.h>
#include <D3DCompiler.h>
#include <DXGI.h>
#include <xnamath.h>

// D3D9 needed for PIX events
#include <D3D9.h>

#if defined(EE_CONFIG_DEBUG)
    #pragma comment(lib, "D3DX11d.lib")
#else //#if defined(EE_CONFIG_DEBUG)
    #pragma comment(lib, "D3DX11.lib")
#endif //#if defined(EE_CONFIG_DEBUG)
#pragma comment(lib, "D3DCompiler.lib")


#endif // EE_D3D11HEADERS_H