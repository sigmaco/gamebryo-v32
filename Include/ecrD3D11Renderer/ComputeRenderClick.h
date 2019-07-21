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
#ifndef EE_COMPUTERENDERCLICK_H
#define EE_COMPUTERENDERCLICK_H

#include <ecrD3D11Renderer/ecrD3D11RendererLibType.h>

#include <NiRenderClick.h>

namespace ecr
{

/**
    ComputeRenderClick is an NiRenderClick that is responsible for invoking compute shaders.

    Compute shaders are run without a mesh, and so cannot be invoked from the standard
    frame rendering system. A ComputeRenderClick enables applications to insert a compute shader
    (or a set of compute shaders) into the frame at the appropriate point.
*/
class EE_ECRD3D11RENDERER_ENTRY ComputeRenderClick : public NiRenderClick
{
    /// @cond EMERGENT_INTERNAL

    NiDeclareRTTI;

    /// @endcond

public:
    /// @name Construction and Destruction
    //@{
    /// Constructor that creates an empty ComputeRenderClick.
    ComputeRenderClick();
    /// Destructor
    virtual ~ComputeRenderClick();
    //@}

    /// Returns the number of compute shaders run in most recent frame.
    virtual efd::UInt32 GetNumObjectsDrawn() const;

    /**
        Returns the time spent culling in most recent frame. 
        
        Because compute shaders do not require any culling, this function will always return 0.0f.
    */
    virtual efd::Float32 GetCullTime() const;

    /// Returns the time spent running compute shaders in the most recent frame.
    virtual efd::Float32 GetRenderTime() const;

    /**
        Appends a shader to the list of NiShaders to be run when the ComputeRenderClick is invoked.
        @param pShader The shader to be appended to the list.
    */
    inline void AppendShader(NiShader* pShader);

    /**
        Prepends a shader to the list of NiShaders to be run when the ComputeRenderClick is invoked.
        @param pShader The shader to be prepended to the list.
    */
    inline void PrependShader(NiShader* pShader);

    /**
        Removes a shader from the list of NiShaders to be run when the ComputeRenderClick is 
        invoked.
        @param pShader The shader to be removed from the list.
    */
    inline void RemoveShader(NiShader* pShader);

    /**
        Removes all shaders from the list of NiShaders to be run when the ComputeRenderClick is 
        invoked.
    */
    inline void RemoveAllShaders();

    /**
        Returns the list of NiShaders to be run when the ComputeRenderClick is invoked.
    */
    inline NiTPointerList<NiShaderPtr>& GetShaders();

    /**
        Returns the list of NiShaders to be run when the ComputeRenderClick is invoked as a 
        const list.
    */
    inline const NiTPointerList<NiShaderPtr>& GetShaders() const;

    /**
        Searches the list of NiShaders for the shader of a given name and returns the first match.

        @param shaderName Shader name to search for.
        @return The first shader in the list with a matching name, or NULL if no such shader is 
            found.        
    */
    inline NiShader* GetShaderByName(const efd::FixedString& shaderName) const;

    /**
        Searches the list of NiShaders for the shader of a given name and returns an 
        NiTListIterator that points to the first match.

        @param shaderName Shader name to search for.
        @return The NiTListIterator pointing to the first shader in the list with a matching name, 
            or NULL if no such shader is found.        
    */
    inline NiTListIterator GetShaderPosByName(const efd::FixedString& shaderName) const;

    /**
        Searches the list of NiShaders for the shader of a given name and returns an 
        NiTListIterator that points to the first match.

        @param shaderName Shader name to search for.
        @param iter Output: the function will place a NiTListIterator pointing to the first shader 
            in the list with a matching name, or NULL if none is found, into this parameter.
        @return The first shader in the list with a matching name, or NULL if no such shader 
            is found.        
    */
    inline NiShader* GetShaderAndPosByName(
        const efd::FixedString& shaderName,
        NiTListIterator& iter) const;

protected:
    /// Invokes the list of shaders.
    virtual void PerformRendering(efd::UInt32 frameID);

    /// List of shaders to invoke.
    NiTPointerList<NiShaderPtr> m_shaderList;

    /// Rendering statistics.
    efd::UInt32 m_numObjectsDrawn;
    efd::Float32 m_renderTime;
};

/// Define a smart pointer (reference counting, self deleting pointer) for the ComputeRenderClick
/// class.
typedef efd::SmartPointer<ComputeRenderClick> ComputeRenderClickPtr;

}   // End namespace ecr.

#include <ecrD3D11Renderer/ComputeRenderClick.inl>

#endif // EE_COMPUTERENDERCLICK_H
