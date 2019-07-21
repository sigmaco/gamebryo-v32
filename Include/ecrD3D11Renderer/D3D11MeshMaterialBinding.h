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
#ifndef EE_D3D11MESHMATERIALBINDING_H
#define EE_D3D11MESHMATERIALBINDING_H

#include <ecrD3D11Renderer/ecrD3D11RendererLibType.h>
#include <ecrD3D11Renderer/D3D11Headers.h>

#include <NiRefObject.h>

class NiDataStreamRef;
class NiRenderObject;
class NiSemanticAdapterTable;

namespace ecr
{

class D3D11MeshMaterialBinding;
/// Define a smart pointer (reference counting, self deleting pointer) for the
/// D3D11MeshMaterialBinding class.
typedef efd::SmartPointer<D3D11MeshMaterialBinding> D3D11MeshMaterialBindingPtr;

/**
    ecr::D3D11MeshMaterialBinding is a class that wraps functionality needed to build a 
    D3D11 vertex layout for an NiRenderObject.
*/
class EE_ECRD3D11RENDERER_ENTRY D3D11MeshMaterialBinding : public NiRefObject
{
public:
    /// @name Construction and Destruction
    //@{
    /// Destructor
    virtual ~D3D11MeshMaterialBinding();
    //@}

    /**
        Creates a new D3D11MeshMaterialBinding object. 
        
        @param pMesh Mesh to create a new mesh material binding for.
        @param adapterTable NiSemanticAdapterTable to use when creating the binding.
        @return The newly created D3D11MeshMaterialBinding. If no binding can be created or the 
            D3D11 renderer fails to create a vertex declaration, then this function will return 
            NULL.
    */
    static D3D11MeshMaterialBindingPtr Create(
        NiRenderObject* pMesh,
        const NiSemanticAdapterTable& adapterTable);

    /**
        Updates the D3D11MeshMaterialBinding with the input signature from a specific vertex shader. 
        
        The D3D11MeshMaterialBinding will remember which ID3D11InputLayout object is associated 
        with which input signature, so it will not need to recreate the input layout each time 
        the vertex shader is changed.

        @param pInputSignature The new input signature for the vertex shader.
        @param inputSignatureSize The size of the new input signature.
    */
    void UpdateInputLayout(
        void* pInputSignature,
        efd::UInt32 inputSignatureSize);

    /// Returns the array of D3D11_INPUT_ELEMENT_DESC structures that was created from the 
    /// NiSemanticAdapterTable provided during initialization to describe the vertex buffers.
    inline D3D11_INPUT_ELEMENT_DESC* GetInputElementDescArray() const;
    /// Returns the number of elements in the D3D11_INPUT_ELEMENT_DESC array.
    inline efd::UInt32 GetInputElementDescCount() const;

    /**
        Returns the D3D11 vertex layout represented by this instance. 
        
        The layout will be based on the most recent input signature passed into UpdateInputLayout.
    */
    inline ID3D11InputLayout* GetInputLayout() const;

    /// Releases all the ID3D11InputLayout objects that have been created for the various input 
    /// signatures that have been passed into UpdateInputLayout.
    inline void ReleaseCachedInputLayouts();
    /// Releases the array of D3D11_INPUT_ELEMENT_DESC structures that was created from the 
    /// NiSemanticAdapterTable provided during initialization to describe the vertex buffers.
    inline void ReleaseElementArray();

    /// Returns a pointer to the NiDataStreamRef representing the index buffer.
    inline const NiDataStreamRef* GetIndexStreamRef() const;
    /// Returns a pointer to an internal array describing the indices of the data streams that will 
    /// be set as vertex buffers.
    inline const efd::UInt16* GetStreamsToSetArray() const;

    /// Returns the index of the highest-numbered stream that will be set.
    inline efd::UInt16 GetLastValidStream() const;

protected:
    /// Hidden Constructor
    D3D11MeshMaterialBinding();

    /// Convert the NiSemanticAdapterTable to a D3D11_INPUT_ELEMENT_DESC array.
    efd::Bool FillElementDescArray(
        NiRenderObject* pMesh,
        const NiSemanticAdapterTable& adapterTable);

    D3D11_INPUT_ELEMENT_DESC* m_elementDescArray;

    /// Internal class to store the input layouts associated with various vertex shaders in a 
    /// linked list.
    class InputLayoutEntry : public efd::MemObject
    {
    public:
        InputLayoutEntry();
        ~InputLayoutEntry();

        ID3D11InputLayout* m_pInputLayout;
        void* m_pInputSignature;
        InputLayoutEntry* m_pNext;
    };

    InputLayoutEntry* m_inputLayoutArray;
    ID3D11InputLayout* m_pCurrentInputLayout;

    const NiDataStreamRef* m_pIndexStreamRef;
    efd::UInt16 m_streamsToSetArray[D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];

    efd::UInt16 m_lastValidStream;
    efd::UInt16 m_elementCount;
};

}   // End namespace ecr.

#include <ecrD3D11Renderer/D3D11MeshMaterialBinding.inl>

#endif // EE_D3D11MESHMATERIALBINDING_H
