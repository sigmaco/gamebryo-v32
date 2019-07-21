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
#ifndef EE_D3D11GEOMETRYSHADER_H
#define EE_D3D11GEOMETRYSHADER_H

#include <ecrD3D11Renderer/D3D11ShaderProgram.h>

namespace ecr
{

/**
    Encapsulates a D3D11 geometry shader.
*/
class EE_ECRD3D11RENDERER_ENTRY D3D11GeometryShader : public D3D11ShaderProgram
{
    /// @cond EMERGENT_INTERNAL

    NiDeclareRTTI;

    /// @endcond
public:
    /// @name Construction and Destruction
    //@{
    /// Constructor for an uninitialized D3D11GeoemtryShader.
    D3D11GeometryShader();

    /// This constructor creates an initialized D3D11GeometryShader using the provided geometry 
    /// shader and an ID3DBlob containing the shader's byte code.
    D3D11GeometryShader(ID3D11GeometryShader* pGeometryShader, ID3DBlob* pShaderByteCode);

    /// Destructor
    virtual ~D3D11GeometryShader();
    //@}

    /// Returns the D3D11 geometry shader
    inline ID3D11GeometryShader* GetGeometryShader() const;

    /// Sets the D3D11 geometry shader
    void SetGeometryShader(ID3D11GeometryShader* pGeometryShader);

    /// Releases the ID3D11GeometryShader reference
    virtual void DestroyRendererData();

    /// Recreates the ID3D11ComptueShader from shader byte code, if it exists.
    virtual void RecreateRendererData();

    /// Stream output
    //@{
    /**
        Sets the declaration for stream output from the geometry shader.
        @param pSODeclaration Array of D3D11_SO_DECLARATION_ENTRY objects that describe the
            expected arrangement of the output streams.
        @param numEntries Number of entries in pSODeclaration.
        @param outputStreamStrideArray Array of strides for the output streams.
        @param numOutputStreams Number of output streams, and number of entries in 
            outputStreamStrideArray.
        @param rasterizedStream ID of the output stream to be rasterized, if any. If none will
            be rasterized, pass in D3D11_SO_NO_RASTERIZED_STREAM.
    */
    void SetStreamOutputDeclaration(
        const D3D11_SO_DECLARATION_ENTRY* pSODeclaration,
        efd::UInt32 numEntries, 
        efd::UInt32* outputStreamStrideArray,
        efd::UInt32 numOutputStreams,
        efd::UInt32 rasterizedStream);

    /// Returns the array of stream output declaration objects.
    inline const D3D11_SO_DECLARATION_ENTRY* GetStreamOutputDeclaration() const;

    /// Returns the number of entries in the stream output declaration array.
    inline efd::UInt32 GetNumStreamOutputEntries() const;

    /// Returns the array of strides for the output streams.
    inline const efd::UInt32* GetOutputStreamStrideArray() const;

    /// Returns the number of the output streams.
    inline efd::UInt32 GetNumStreamOutputStreams() const;

    /// Returns the ID of the output stream to be rasterized, if any. If none will
    /// be rasterized, this function will return D3D11_SO_NO_RASTERIZED_STREAM.
    inline efd::UInt32 GetRasterizedStreamOutputStream() const;
    //@}

protected:
    ID3D11GeometryShader* m_pGeometryShader;

    D3D11_SO_DECLARATION_ENTRY* m_pSODeclaration;
    efd::UInt32 m_numEntries; 
    efd::UInt32 m_outputStreamStrideArray[D3D11_SO_STREAM_COUNT];
    efd::UInt32 m_numOutputStreams;
    efd::UInt32 m_rasterizedStream;
};

/// Define a smart pointer (reference counting, self deleting pointer) for the D3D11GeometryShader
/// class.
typedef efd::SmartPointer<D3D11GeometryShader> D3D11GeometryShaderPtr;

}   // End namespace ecr.

#include <ecrD3D11Renderer/D3D11GeometryShader.inl>

#endif // EE_D3D11GEOMETRYSHADER_H
