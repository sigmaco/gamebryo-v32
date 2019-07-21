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
#ifndef EE_ECRD3D11BINARYSHADERLIBPCH_H
#define EE_ECRD3D11BINARYSHADERLIBPCH_H

/** @file ecrD3D11RendererPCH.h
    This header file is used as the Precompiled Header for building ecrD3D11BinaryShaderLib. 
    It should only include ecrD3D11BinaryShaderLib headers that are commonly used and not expected 
    to change frequently. In addition it should include various external headers such as OS or 
    CRT headers.
*/

#if defined(EE_USE_PCH)

#include <NSBShaderLibPCH.h>
#include <ecrD3D11Renderer\D3D11Headers.h>
#include <ecrD3D11Renderer\D3D11ShaderCore.h>
#include <ecrD3D11Renderer\D3D11ShaderLibrary.h>

#endif //#if defined(EE_USE_PCH)

#endif // EE_ECRD3D11BINARYSHADERLIBPCH_H
