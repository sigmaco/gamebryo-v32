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
#ifndef EE_D3D11BINARYSHADER_H
#define EE_D3D11BINARYSHADER_H

#include <ecrD3D11BinaryShaderLib/ecrD3D11BinaryShaderLibLibType.h>
#include "NSBUserDefinedDataSet.h"

#include <ecrD3D11Renderer/D3D11ShaderCore.h>
#include <NiShaderDeclaration.h>
#include <NiShaderRequirementDesc.h>

// For reporting errors...
#include <ecrD3D11Renderer/D3D11ShaderFactory.h>

class NSBImplementation;

namespace ecr
{

/**
    D3D11BinaryShader is the D3D11-specific shader that represents NSB shaders.

    This D3D11ShaderCore-derived class that provides a completely data-driven model for shader 
    usage. All functions, even those considered 'internal', are documented to provide a model for 
    developing your own shader classes.
*/

class EE_ECRD3D11BINARYSHADERLIB_ENTRY D3D11BinaryShader : public ecr::D3D11ShaderCore
{
    /// @cond EMERGENT_INTERNAL

    NiDeclareRTTI;

    /// @endcond
public:
    /// @name Construction and Destruction
    //@{
    /// Constructor.
    D3D11BinaryShader();
    /// Destructor.
    virtual ~D3D11BinaryShader();
    //@}

    /// Initialize the shader by loading all shader programs from each pass.
    virtual efd::Bool Initialize();

    /// Prepare each pass by ensuring all shader resources have been uploaded to the D3D11 device.
    virtual efd::UInt32 UpdatePipeline(const NiRenderCallContext& callContext);

    /// Return a pointer to the shader's NSBUserDefinedDataSet.
    inline NSBUserDefinedDataSet* GetShaderUserDefinedDataSet();
    /// Return a pointer to the implementation's NSBUserDefinedDataSet.
    inline NSBUserDefinedDataSet* GetImplementationUserDefinedDataSet();
    /// Return a pointer to the pass's NSBUserDefinedDataSet.
    inline NSBUserDefinedDataSet* GetPassUserDefinedDataSet(efd::UInt32 passID);

    /// @cond EMERGENT_INTERNAL

    /// Set a pointer to the shader's NSBUserDefinedDataSet.
    inline void SetUserDefinedDataSet(NSBUserDefinedDataSet* pUDDSet);
    /// Set a pointer to the implementation's NSBUserDefinedDataSet.
    inline void SetImplementationUserDefinedDataSet(NSBUserDefinedDataSet* pUDDSet);
    /// Set a pointer to the pass's NSBUserDefinedDataSet.
    inline void SetPassUserDefinedDataSet(efd::UInt32 passID, NSBUserDefinedDataSet* pUDDSet);

    /// Sets the render state group object.
    inline void SetRenderStateGroup(D3D11RenderStateGroup* pRenderStateGroup);

    /// Inserts the pass at the given position.
    inline efd::Bool InsertPass(efd::UInt32 passID, D3D11Pass* pPass);

    /// Enumerate the different ways data can be packed into the bone matrices.
    enum BoneMatrixCalcMethod
    {
        /// Bone matrices contain the transform of the skinned mesh.
        BONECALC_SKIN       = 0x00000000,
        /// Bone matrices do not contain the transform of the skinned mesh.
        BONECALC_NO_SKIN    = 0x00000001
    };

    /// Return the maximum number of bones per partition that the shader can handle.
    inline efd::UInt32 GetBonesPerPartition() const;
    /// Set the maximum number of bones per partition that the shader can handle.
    inline void SetBonesPerPartition(efd::UInt32 boneCount);
    /// Return the expected number of rows in each bone matrix.
    inline efd::UInt32 GetBoneMatrixRegisters() const;
    /// Set the expected number of rows in each bone matrix.
    inline void SetBoneMatrixRegisters(efd::UInt32 registerCount);
    /// Return the BoneMatrixCalcMethod the shader expects.
    BoneMatrixCalcMethod GetBoneCalcMethod() const;
    /// Set the BoneMatrixCalcMethod the shader expects.
    inline void SetBoneCalcMethod(BoneMatrixCalcMethod method);

    /// Return the method used to generate normal/binormal/tangent data.
    inline NiShaderRequirementDesc::NBTFlags GetBinormalTangentMethod() const;
    /// Set the method used to generate normal/binormal/tangent data.
    inline void SetBinormalTangentMethod(NiShaderRequirementDesc::NBTFlags nbtMethod);

    /// Return the UV source for the normal/binormal/tangent calculations.
    inline efd::UInt32 GetBinormalTangentUVSource() const;
    /// Set the UV source for the normal/binormal/tangent calculations.
    inline void SetBinormalTangentUVSource(efd::UInt32 nbtUVSource);

    /**
        Search the shader for settings that will affect how the mesh is treated in the scene graph.

        Check the shader for alpha blend states, and if found, set up an NiAlphaProperty on the 
        mesh so it will be managed by Gamebryo's alpha accumulators. Also, look for time-based
        parameters, and if found, create an NiTimeSyncController and ensure the mesh will be
        updated correctly by the UpdateSelected system.
    */ 
    virtual efd::Bool SetupGeometry(
        NiRenderObject* pRenderObject, 
        NiMaterialInstance* pMaterialInstance);
    /// Return whether the shader constant map contains any time-based parameters.
    virtual efd::Bool IsTimeBased(D3D11ShaderConstantMap* pMap);

    /// @endcond

protected:
    //@{
    /// Load the specified shader program.
    efd::Bool LoadVertexShaderProgram(D3D11Pass& pass);
    efd::Bool LoadHullShaderProgram(D3D11Pass& pass);
    efd::Bool LoadDomainShaderProgram(D3D11Pass& pass);
    efd::Bool LoadGeometryShaderProgram(D3D11Pass& pass);
    efd::Bool LoadPixelShaderProgram(D3D11Pass& pass);
    efd::Bool LoadComputeShaderProgram(D3D11Pass& pass);
    //@}

    //@{
    /// Find the source file for the specified shader program.
    efd::Bool ResolveVertexShaderFileName(
        const efd::Char* pOriginalName,
        efd::Char* pTrueName, 
        efd::UInt32 nameLength);
    efd::Bool ResolveHullShaderFileName(
        const efd::Char* pOriginalName,
        efd::Char* pTrueName, 
        efd::UInt32 nameLength);
    efd::Bool ResolveDomainShaderFileName(
        const efd::Char* pOriginalName,
        efd::Char* pTrueName, 
        efd::UInt32 nameLength);
    efd::Bool ResolveGeometryShaderFileName(
        const efd::Char* pOriginalName,
        efd::Char* pTrueName, 
        efd::UInt32 nameLength);
    efd::Bool ResolvePixelShaderFileName(
        const efd::Char* pOriginalName,
        efd::Char* pTrueName, 
        efd::UInt32 nameLength);
    efd::Bool ResolveComputeShaderFileName(
        const efd::Char* pOriginalName,
        efd::Char* pTrueName, 
        efd::UInt32 nameLength);
    //@}

    efd::UInt32 m_bonesPerPartition;
    efd::UInt32 m_boneMatrixRegisters;
    BoneMatrixCalcMethod m_boneCalcMethod;
    NiShaderRequirementDesc::NBTFlags m_nbtMethod;
    efd::UInt32 m_nbtUVSource;

    // User defined data set
    NSBUserDefinedDataSetPtr m_spUDDSet_Shader;
    NSBUserDefinedDataSetPtr m_spUDDSet_Implementation;
    NiTObjectArray<NSBUserDefinedDataSetPtr> m_uddSetArray;

    efd::UInt32 m_passCount;
};

}   // End namespace ecr.

#include <ecrD3D11BinaryShaderLib\D3D11BinaryShader.inl>

#endif // EE_D3D11BINARYSHADER_H
