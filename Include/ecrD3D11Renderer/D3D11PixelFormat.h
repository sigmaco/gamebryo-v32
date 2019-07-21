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
#ifndef EE_D3D11PIXELFORMAT_H
#define EE_D3D11PIXELFORMAT_H

#include <ecrD3D11Renderer/ecrD3D11RendererLibType.h>
#include <ecrD3D11Renderer/D3D11Headers.h>

#include <NiPixelFormat.h>
#include <NiDataStreamElement.h>

namespace ecr
{

/**
    D3D11PixelFormat contains NiPixelFormat representations of the D3D11 texture formats.
*/

class EE_ECRD3D11RENDERER_ENTRY D3D11PixelFormat
{
public:
    /**
        Returns the DXGI_FORMAT that matches an NiPixelFormat. 
        
        If a match cannot be found, DXGI_FORMAT_UNKNOWN will be returned.
    */
    static DXGI_FORMAT DetermineDXGIFormat(const NiPixelFormat& pixelFormat);
    /**
        Returns the DXGI_FORMAT that matches a NiDataStreamElement::Format. 
        
        If a match cannot be found, DXGI_FORMAT_UNKNOWN will be returned.
    */
    static DXGI_FORMAT DetermineDXGIFormat(NiDataStreamElement::Format format);

    /// Initializes an NiPixelFormat with the description of a specific DXGI_FORMAT. 
    static void InitFromDXGIFormat(DXGI_FORMAT dxgiFormat, NiPixelFormat& pixelFormat);
    /// Return the NiPixelFormat that describes a specific DXGI_FORMAT.
    static const NiPixelFormat* ObtainFromDXGIFormat(DXGI_FORMAT dxgiFormat);

    /// Return the number of bits per pixel for a specific DXGI_FORMAT.
    static unsigned int GetBitsPerPixel(DXGI_FORMAT dxgiFormat);

    /**
        Return a text string containing the name of a DXGI_FORMAT.

        @param dxgiFormat Format to get a name for.
        @param withPrefix If true, the string will contain the prefix "DXGI_FORMAT_", and if false,
            it will not.
        @return The name of the format.
    */
    static const efd::Char* const GetFormatName(DXGI_FORMAT dxgiFormat,
        efd::Bool withPrefix = true);

    /// Returms whether the format is supported in D3D11.
    static efd::Bool IsDXGIFormatSupported(DXGI_FORMAT dxgiFormat);
    /// Returns whether the format supports mipmaps in D3D11.
    static efd::Bool DXGIFormatSupportsMipmaps(DXGI_FORMAT dxgiFormat);

//------------------------------------------------------------------------------------------------

    static NiPixelFormat EE_FORMAT_R32G32B32A32_TYPELESS;
    static NiPixelFormat EE_FORMAT_R32G32B32A32_FLOAT;
    static NiPixelFormat EE_FORMAT_R32G32B32A32_UINT;
    static NiPixelFormat EE_FORMAT_R32G32B32A32_SINT;
    static NiPixelFormat EE_FORMAT_R32G32B32_TYPELESS;
    static NiPixelFormat EE_FORMAT_R32G32B32_FLOAT;
    static NiPixelFormat EE_FORMAT_R32G32B32_UINT;
    static NiPixelFormat EE_FORMAT_R32G32B32_SINT;
    static NiPixelFormat EE_FORMAT_R16G16B16A16_TYPELESS;
    static NiPixelFormat EE_FORMAT_R16G16B16A16_FLOAT;
    static NiPixelFormat EE_FORMAT_R16G16B16A16_UNORM;
    static NiPixelFormat EE_FORMAT_R16G16B16A16_UINT;
    static NiPixelFormat EE_FORMAT_R16G16B16A16_SNORM;
    static NiPixelFormat EE_FORMAT_R16G16B16A16_SINT;
    static NiPixelFormat EE_FORMAT_R32G32_TYPELESS;
    static NiPixelFormat EE_FORMAT_R32G32_FLOAT;
    static NiPixelFormat EE_FORMAT_R32G32_UINT;
    static NiPixelFormat EE_FORMAT_R32G32_SINT;
    static NiPixelFormat EE_FORMAT_R32G8X24_TYPELESS;
    static NiPixelFormat EE_FORMAT_D32_FLOAT_S8X24_UINT;
    static NiPixelFormat EE_FORMAT_R32_FLOAT_X8X24_TYPELESS;
    static NiPixelFormat EE_FORMAT_X32_TYPELESS_G8X24_UINT;
    static NiPixelFormat EE_FORMAT_R10G10B10A2_TYPELESS;
    static NiPixelFormat EE_FORMAT_R10G10B10A2_UNORM;
    static NiPixelFormat EE_FORMAT_R10G10B10A2_UINT;
    static NiPixelFormat EE_FORMAT_R11G11B10_FLOAT;
    static NiPixelFormat EE_FORMAT_R8G8B8A8_TYPELESS;
    static NiPixelFormat EE_FORMAT_R8G8B8A8_UNORM;
    static NiPixelFormat EE_FORMAT_R8G8B8A8_UNORM_SRGB;
    static NiPixelFormat EE_FORMAT_R8G8B8A8_UINT;
    static NiPixelFormat EE_FORMAT_R8G8B8A8_SNORM;
    static NiPixelFormat EE_FORMAT_R8G8B8A8_SINT;
    static NiPixelFormat EE_FORMAT_R16G16_TYPELESS;
    static NiPixelFormat EE_FORMAT_R16G16_FLOAT;
    static NiPixelFormat EE_FORMAT_R16G16_UNORM;
    static NiPixelFormat EE_FORMAT_R16G16_UINT;
    static NiPixelFormat EE_FORMAT_R16G16_SNORM;
    static NiPixelFormat EE_FORMAT_R16G16_SINT;
    static NiPixelFormat EE_FORMAT_R32_TYPELESS;
    static NiPixelFormat EE_FORMAT_D32_FLOAT;
    static NiPixelFormat EE_FORMAT_R32_FLOAT;
    static NiPixelFormat EE_FORMAT_R32_UINT;
    static NiPixelFormat EE_FORMAT_R32_SINT;
    static NiPixelFormat EE_FORMAT_R24G8_TYPELESS;
    static NiPixelFormat EE_FORMAT_D24_UNORM_S8_UINT;
    static NiPixelFormat EE_FORMAT_R24_UNORM_X8_TYPELESS;
    static NiPixelFormat EE_FORMAT_X24_TYPELESS_G8_UINT;
    static NiPixelFormat EE_FORMAT_R8G8_TYPELESS;
    static NiPixelFormat EE_FORMAT_R8G8_UNORM;
    static NiPixelFormat EE_FORMAT_R8G8_UINT;
    static NiPixelFormat EE_FORMAT_R8G8_SNORM;
    static NiPixelFormat EE_FORMAT_R8G8_SINT;
    static NiPixelFormat EE_FORMAT_R16_TYPELESS;
    static NiPixelFormat EE_FORMAT_R16_FLOAT;
    static NiPixelFormat EE_FORMAT_D16_UNORM;
    static NiPixelFormat EE_FORMAT_R16_UNORM;
    static NiPixelFormat EE_FORMAT_R16_UINT;
    static NiPixelFormat EE_FORMAT_R16_SNORM;
    static NiPixelFormat EE_FORMAT_R16_SINT;
    static NiPixelFormat EE_FORMAT_R8_TYPELESS;
    static NiPixelFormat EE_FORMAT_R8_UNORM;
    static NiPixelFormat EE_FORMAT_R8_UINT;
    static NiPixelFormat EE_FORMAT_R8_SNORM;
    static NiPixelFormat EE_FORMAT_R8_SINT;
    static NiPixelFormat EE_FORMAT_A8_UNORM;
    static NiPixelFormat EE_FORMAT_R1_UNORM;
    static NiPixelFormat EE_FORMAT_R9G9B9E5_SHAREDEXP;
    static NiPixelFormat EE_FORMAT_R8G8_B8G8_UNORM;
    static NiPixelFormat EE_FORMAT_G8R8_G8B8_UNORM;
    static NiPixelFormat EE_FORMAT_BC1_TYPELESS;
    static NiPixelFormat EE_FORMAT_BC1_UNORM;
    static NiPixelFormat EE_FORMAT_BC1_UNORM_SRGB;
    static NiPixelFormat EE_FORMAT_BC2_TYPELESS;
    static NiPixelFormat EE_FORMAT_BC2_UNORM;
    static NiPixelFormat EE_FORMAT_BC2_UNORM_SRGB;
    static NiPixelFormat EE_FORMAT_BC3_TYPELESS;
    static NiPixelFormat EE_FORMAT_BC3_UNORM;
    static NiPixelFormat EE_FORMAT_BC3_UNORM_SRGB;
    static NiPixelFormat EE_FORMAT_BC4_TYPELESS;
    static NiPixelFormat EE_FORMAT_BC4_UNORM;
    static NiPixelFormat EE_FORMAT_BC4_SNORM;
    static NiPixelFormat EE_FORMAT_BC5_TYPELESS;
    static NiPixelFormat EE_FORMAT_BC5_UNORM;
    static NiPixelFormat EE_FORMAT_BC5_SNORM;
    static NiPixelFormat EE_FORMAT_B5G6R5_UNORM;
    static NiPixelFormat EE_FORMAT_B5G5R5A1_UNORM;
    static NiPixelFormat EE_FORMAT_B8G8R8A8_UNORM;
    static NiPixelFormat EE_FORMAT_B8G8R8X8_UNORM;
    static NiPixelFormat EE_FORMAT_R10G10B10_XR_BIAS_A2_UNORM;
    static NiPixelFormat EE_FORMAT_B8G8R8A8_TYPELESS;
    static NiPixelFormat EE_FORMAT_B8G8R8A8_UNORM_SRGB;
    static NiPixelFormat EE_FORMAT_B8G8R8X8_TYPELESS;
    static NiPixelFormat EE_FORMAT_B8G8R8X8_UNORM_SRGB;
    static NiPixelFormat EE_FORMAT_BC6H_TYPELESS;
    static NiPixelFormat EE_FORMAT_BC6H_UF16;
    static NiPixelFormat EE_FORMAT_BC6H_SF16;
    static NiPixelFormat EE_FORMAT_BC7_TYPELESS;
    static NiPixelFormat EE_FORMAT_BC7_UNORM;
    static NiPixelFormat EE_FORMAT_BC7_UNORM_SRGB;
};

}   // End namespace ecr.

#endif // EE_D3D11PIXELFORMAT_H
