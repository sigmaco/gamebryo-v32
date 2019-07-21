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
#ifndef EE_D3D11ERROR_H
#define EE_D3D11ERROR_H

#include <ecrD3D11Renderer/ecrD3D11RendererLibType.h>

#include <efd/UniversalTypes.h>
#include <efd/MemObject.h>

namespace ecr
{
/**
    Class for handling error reports in the ecrD3D11Renderer library. 

    It allows applications to programmatically query the library to determine the cause of 
    any failure so that the application can respond in an appropriate manner.
*/
class EE_ECRD3D11RENDERER_ENTRY D3D11Error : public efd::MemObject
{
public:
    /// Enumeration of error messages.
    enum ErrorMessage
    {
        /// No error.
        D3D11ERROR_NONE,

        /// Error in error reporting system.
        D3D11ERROR_ERROR_SYSTEM_ERROR,

        /// Missing D3D11 lib.
        D3D11ERROR_D3D11_LIB_MISSING,
        /// Missing DXGI lib.
        D3D11ERROR_DXGI_LIB_MISSING,
        /// Error creating D3D11 device.
        D3D11ERROR_DEVICE_CREATION_FAILED,
        /// Error creating DXGI device.
        D3D11ERROR_FACTORY_CREATION_FAILED,

        /// Error creating swap chain.
        D3D11ERROR_SWAP_CHAIN_CREATION_FAILED,
        /// Error creating 1D texture.
        D3D11ERROR_TEXTURE1D_CREATION_FAILED,
        /// Error creating 2D texture.
        D3D11ERROR_TEXTURE2D_CREATION_FAILED,
        /// Error creating 3D texture.
        D3D11ERROR_TEXTURE3D_CREATION_FAILED,
        /// Error creating buffer.
        D3D11ERROR_BUFFER_CREATION_FAILED,
        /// Error creating render target view.
        D3D11ERROR_RENDER_TARGET_VIEW_CREATION_FAILED,
        /// Error creating depth stencil view.
        D3D11ERROR_DEPTH_STENCIL_VIEW_CREATION_FAILED,
        /// Error creating shader resource view.
        D3D11ERROR_SHADER_RESOURCE_VIEW_CREATION_FAILED,
        /// Error creating unordered access view.
        D3D11ERROR_UNORDERED_ACCESS_VIEW_CREATION_FAILED,
        /// Error creating blend state.
        D3D11ERROR_BLEND_STATE_CREATION_FAILED,
        /// Error creating depth stencil state.
        D3D11ERROR_DEPTH_STENCIL_STATE_CREATION_FAILED,
        /// Error creating rasterizer state.
        D3D11ERROR_RASTERIZER_STATE_CREATION_FAILED,
        /// Error creating sampler.
        D3D11ERROR_SAMPLER_CREATION_FAILED,
        /// Error creating input layout.
        D3D11ERROR_INPUT_LAYOUT_CREATION_FAILED,

        /// Error presenting swap chain.
        D3D11ERROR_DISPLAY_SWAP_CHAIN_FAILED,
        /// Error obtaining buffer from swap chain.
        D3D11ERROR_GET_BUFFER_FROM_SWAP_CHAIN_FAILED,
        /// Error locking 1D texture.
        D3D11ERROR_TEXTURE1D_LOCK_FAILED,
        /// Error locking 2D texture.
        D3D11ERROR_TEXTURE2D_LOCK_FAILED,
        /// Error locking 3D texture.
        D3D11ERROR_TEXTURE3D_LOCK_FAILED,
        /// Error locking resource that does not support locking.
        D3D11ERROR_UNSUPPORTED_RESOURCE_LOCK_FAILED,
        /// Shader constant map not found for constant buffer.
        D3D11ERROR_SHADER_CONSTANT_MAPPING_FAILED,
        /// Expected shader missing.
        D3D11ERROR_SHADER_MISSING,

    };

    /// Returns the enumeration value of the last error message.
    static ErrorMessage GetLastErrorMessage();
    /// Returns a description string for the error enumeration.
    static const efd::Char* const GetErrorText(ErrorMessage eMessage);

    /// @cond EMERGENT_INTERNAL

    /// Report the input string as a message
    static void ReportMessage(const efd::Char* pMessage, ...);
    /// Report the input string as a warning
    static void ReportWarning(const efd::Char* pWarningMessage, ...);
    /// Report the input string as an error
    static void ReportError(ErrorMessage eError,
        const efd::Char* pAdditionalMessage = NULL, ...);

    /// Initialize the static instance of this class.
    static void _SDMInit();
    /// Shut down the static instance of this class.
    static void _SDMShutdown();

    /// @endcond

protected:
    D3D11Error();
    ~D3D11Error();

    ErrorMessage m_lastErrorMessage;
    enum
    {
        MAX_ADDITIONAL_INFO_STRING_LENGTH = 1024
    };
    char m_lastAdditionalInfo[MAX_ADDITIONAL_INFO_STRING_LENGTH];

    static D3D11Error* ms_pD3D11Error;
};

}   // End namespace ecr.

#endif // EE_D3D11ERROR_H