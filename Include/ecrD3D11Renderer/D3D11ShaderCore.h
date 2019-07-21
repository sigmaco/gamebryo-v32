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
#ifndef EE_D3D11SHADER_H
#define EE_D3D11SHADER_H

#include <ecrD3D11Renderer/D3D11ShaderInterface.h>
#include <ecrD3D11Renderer/D3D11Pass.h>
#include <ecrD3D11Renderer/D3D11RenderStateGroup.h>
#include <ecrD3D11Renderer/D3D11ShaderConstantMap.h>
#include <ecrD3D11Renderer/UnorderedAccessResource.h>

namespace ecr
{

/**
    Represents an unordered access view variable on a D3D11ShaderCore object.

    During D3D11Pass::ExposeShaderParameters, any unordered access view variables that a shader 
    requires will have a UAVSlot created for them on the D3D11ShaderCore object. An application 
    can then attach an UnorderdAccessResource to the UAVSlot to provide a specific D3D11 resource 
    to that shader variable.

    New UAVSlot objects should be created on a D3D11ShaderCore object using 
    D3D11ShaderCore::AddUAVSlot.
*/
class EE_ECRD3D11RENDERER_ENTRY UAVSlot : public efd::MemObject
{
public:
    /// Return the name of the unordered access view shader variable.
    inline const efd::FixedString& GetName() const;

    /// Provide an UnorderedAccessResource to the shader variable.
    inline void SetUnorderedAccessResource(UnorderedAccessResource* pResource);
    /// Return the UnorderedAccessResource that will be used for the shader variable.
    inline UnorderedAccessResource* GetUnorderedAccessResource() const;

protected:
    /// Hidden constructor.
    UAVSlot(efd::FixedString samplerName);
    /// Destructor.
    virtual ~UAVSlot();

    efd::FixedString m_name;
    UnorderedAccessResourcePtr m_spResource;

    UAVSlot* m_pNext;

    friend class D3D11ShaderCore;
};

/**
    D3D11ShaderCore derives from D3D11ShaderInterface and adds some commonly-used functionality.

    D3D11ShaderCore introduces pass-based rendering, 'global' render state settings, and 
    unordered access view resources.
*/

class EE_ECRD3D11RENDERER_ENTRY D3D11ShaderCore : public D3D11ShaderInterface
{
    /// @cond EMERGENT_INTERNAL

    NiDeclareRTTI;

    /// @endcond
public:
    /// @name Construction and Destruction
    //@{

    /// Constructs an empty, uninitialized shader object.
    D3D11ShaderCore();
    /// Destructor
    virtual ~D3D11ShaderCore();
    //@}

    /// Returns whether or not the shader has been initialized.
    virtual efd::Bool IsInitialized();

    /// Performs initialization, including calling ExposeShaderParameters on each pass.
    virtual efd::Bool Initialize();

    /// Method for calling a shader that only contains compute shader programs.
    virtual void InvokeShader();

    /// Updates the render state manager with all properties in the active NiPropertyState, as 
    /// well as the shader's render state group.
    virtual efd::UInt32 PreProcessPipeline(const NiRenderCallContext& callContext);
    /// Set the shader's current pass ID to the first pass in the shader's pass array.
    virtual efd::UInt32 FirstPass();
    /// Set up the stream output settings, if necessary, and calls SetupRenderingPass on
    /// the currently active pass.
    virtual efd::UInt32 SetupRenderingPass(const NiRenderCallContext& callContext);
    /// Set the mesh's model transform on the renderer.
    virtual efd::UInt32 SetupTransformations(const NiRenderCallContext& callContext);
    /// Calls ApplyShaderPrograms and ApplyShaderConstants on the currently active pass.
    virtual efd::UInt32 SetupShaderPrograms(const NiRenderCallContext& callContext);
    /// Set the index buffer, vertex buffer, input layout, and primitive topology.
    virtual efd::UInt32 PreRenderSubmesh(const NiRenderCallContext& callContext);
    /// Set the shader's current pass ID to the next pass in the shader's pass array.
    virtual efd::UInt32 NextPass();

    /// Cache extra data pointers that the shader constant maps will use, and generate
    /// the input layout for the geometry/vertex shader combination.
    virtual efd::Bool SetupGeometry(
        NiRenderObject* pGeometry, 
        NiMaterialInstance* pMaterialInstance);

    /// Cache extra data pointers that the shader constant maps will use.
    static void SetupSCMExtraData(D3D11ShaderCore* pShader, NiRenderObject* pGeometry);
    /// Remove any cached extra data pointers.
    void ResetSCMExtraData(NiRenderObject* pGeometry);

    /// Release D3D11 shader programs in the shader.
    virtual void DestroyRendererData();
    /// Recreate D3D11 shader programs in the shader.
    virtual void RecreateRendererData();

    /// Return whether the shader should set render state based on the NiPropertyState.
    inline efd::Bool GetUsesNiRenderState() const;
    /// Set whether shader should set render state based on the NiPropertyState.
    inline efd::Bool SetUsesNiRenderState(efd::Bool bUses);

    /**
        Get parameters related to how the shader expects bone matrices to be packed.

        @param transposeBones Returns whether the bone matrices should be transposed.
        @param boneMatrixRegisters Returns the number of rows expected for each matrix - 3 or 4.
        @param worldSpaceBones Returns whether bone matrices are packed in world space as opposed
            to skinned model space.
    */
    inline void GetBoneParameters(
        efd::Bool& transposeBones,
        efd::UInt32& boneMatrixRegisters,
        efd::Bool& worldSpaceBones);
    /**
        Set parameters related to how the shader expects bone matrices to be packed.

        @param transposeBones Whether the bone matrices should be transposed.
        @param boneMatrixRegisters The number of rows expected for each matrix - 3 or 4.
        @param worldSpaceBones Whether bone matrices are packed in world space as opposed
            to skinned model space.
    */
    inline void SetBoneParameters(
        efd::Bool transposeBones,
        efd::UInt32 boneMatrixRegisters,
        efd::Bool worldSpaceBones);

    /// Add a new unordered access view slot with the given name to the shader.
    UAVSlot* AddUAVSlot(efd::FixedString& name);
    /// Return the unordered access view slot with the given name on the shader.
    UAVSlot* GetUAVSlot(efd::FixedString& name) const;
    /// Remove the unordered access view slot with the given name from the shader.
    efd::Bool RemoveUAVSlot(efd::FixedString& name);
    /// Remove the providedi unordered access view slot from the shader.
    efd::Bool RemoveUAVSlot(UAVSlot* pUAVSlot);

    /// Return the first UAVSlot on the shader.
    inline const UAVSlot* GetFirstUAVSlot() const;
    /// Return the next UAVSlot on the shader.
    inline const UAVSlot* GetNextUAVSlot(const UAVSlot* pUAVSlot) const;

    /// Get the total pass count/
    inline efd::UInt32 GetPassCount() const;
    /// Get a specific pass.
    inline D3D11Pass* GetPass(efd::UInt32 passID);

    /// @cond EMERGENT_INTERNAL

    /// Returns a number that can be used to indicate whether a pass needs to updates its UAVs.
    inline efd::UInt32 GetUAVSlotResetCount() const;

    /// Return a static string used to set up the SCMExtraData.
    static const NiFixedString& GetEmergentShaderMapName();

    /// Returns a specific texture and sampling flags given the NiTexturingProperty map flags
    /// in gbMapFlags and NiTextureEffect flags in objectTextureFlags.
    static efd::Bool ObtainTexture(
        efd::UInt32 gbMapFlags,
        efd::UInt16 objectTextureFlags,
        const NiRenderCallContext& callContext,
        NiTexture*& pTexture,
        NiTexturingProperty::ClampMode& clampMode,
        NiTexturingProperty::FilterMode& filterMode,
        efd::UInt16& maxAnisotropy);

    /// Initialize the static string used to set up the SCMExtraData.
    static void _SDMInit();
    /// Release the static string used to set up the SCMExtraData.
    static void _SDMShutdown();

    /// @endcond

protected:

    /// Render all meshes contained in the provided NiVisibleArray.
    virtual void Do_RenderMeshes(NiVisibleArray* pVisibleArray);

    /// Invoking a shader without a mesh (such as a Compute Shader)
    virtual void Do_InvokeShader();

    /// Ensure a shader resource has been updated to the D3D11 device, and optionally override the
    /// sampler state based on the sampler parameters found on the shader resource source.
    void PrepareResource(
        const NiRenderCallContext& callContext,
        efd::UInt8 shaderResource,
        D3D11Pass* pPass,
        efd::Bool updateSampler = false);

    /// Return a UAVSlot and its predecessor.
    UAVSlot* FindUAVSlot(efd::FixedString& name, UAVSlot*& pUAVSlotBefore) const;

    D3D11RenderStateGroupPtr m_spRenderStateGroup;

    efd::UInt32 m_currentPassID;
    NiTObjectArray<D3D11PassPtr> m_passArray;

    NiTObjectSet<UnorderedAccessResource> m_UnorderedAccessResources;

    UAVSlot* m_pUAVSlots;

    D3D11Pass* m_pCurrentPass;

    efd::UInt32 m_resetIndexUAVSlots;

    efd::UInt32 m_boneMatrixRegisters;
    efd::Bool m_transposeBones;
    efd::Bool m_worldSpaceBones;

    efd::Bool m_usesGBRenderState;

    static NiFixedString ms_emergentShaderMapName;
};

/// Define a smart pointer (reference counting, self deleting pointer) for the D3D11ShaderCore
/// class.
typedef efd::SmartPointer<D3D11ShaderCore> D3D11ShaderPtr;

}   // End namespace ecr.

#include <ecrD3D11Renderer/D3D11ShaderCore.inl>

#endif // EE_D3D11SHADER_H
