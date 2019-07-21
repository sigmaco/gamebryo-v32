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
#ifndef EE_D3D11SHADERCONSTANTMAP_H
#define EE_D3D11SHADERCONSTANTMAP_H

#include <ecrD3D11Renderer/ecrD3D11RendererLibType.h>
#include <ecrD3D11Renderer/D3D11DataStream.h>

#include <NiShaderConstantMap.h>
#include <NiShaderConstantMapEntry.h>

namespace ecr
{

class ConstantBufferDesc;

/**
    D3D11 implementation of NiShaderConstantMap.

    An instance of this class provides data to a signle shader constant buffers. 
    
    The constant entries are stored in a set of arrays. There are NiRenderer::PHASE_COUNT 
    arrays in this set. This set of arrays is implemented in the class as the 
    m_phaseEntryArray member. The entries are partitioned into sets to allow varying update 
    frequency per set. This feature is under development and currently provides no advantage.
*/
class EE_ECRD3D11RENDERER_ENTRY D3D11ShaderConstantMap : public NiShaderConstantMap
{
public:
    /// @name Construction and Destruction
    //@{
    /** 
        Constructor to create a D3D11ShaderConstantMap instance for the given shader program type.

        A single shader constant map can be applied to numerous shader program types, but one of
        those shader program types must be the type that is used to construct the shader constant 
        map.
    */
    D3D11ShaderConstantMap(NiGPUProgram::ProgramType shaderType);
    /// Destructor
    virtual ~D3D11ShaderConstantMap();
    //@}

    /// Set the name of the D3D11ShaderConstantMap, which must match the name of the constant 
    /// buffer the map will manage.
    inline void SetName(const efd::FixedString& name);
    /// Return the name of the D3D11ShaderConstantMap.
    inline const efd::FixedString& GetName() const;

    /**
        Creates a new NiShaderConstantMapEntry.

        The shaderRegister and registerCount parameters are less useful in D3D11, where shaders
        refer to variable by name rather than by a register number. However, the shader constant
        map system in Gamebryo still uses these values to prevent collisions, so a unique value
        must be provided for each entry. D3D11 will also use these values to encode the offset and
        size of each variable in the constant buffer, but applications rarely need to manage those
        details.

        @param pKey Name of the entry.
        @param flags Encoding of the type of entry this will be.
        @param extra Additional information about the entry.
        @param shaderRegister Shader register for this entry, which must be unique for each entry.
        @param registerCount Register count for this entry.
        @param pVariableName Name of the variable to set. If NULL, the name will be obtained from 
            pKey.
        @param dataSize Total size of the data block provided to pDataSource.
        @param dataStride Stride of the individual array entries in the data block provided to 
            pDataSource. If the variable is not an array, this should be equal to dataSize.
        @param pDataSource Data provided to the entry as the default value for the variable.
        @param copyData True if the shader constant map entry should save its own copy of the data, 
            or false if the shader constant map entry should only save a pointer to the data.
    */
    virtual NiShaderError AddEntry(
        const efd::Char* pKey, 
        efd::UInt32 flags,
        efd::UInt32 extra, 
        efd::UInt32 shaderRegister,
        efd::UInt32 registerCount, 
        const efd::Char* pVariableName = NULL,
        efd::UInt32 dataSize = 0, 
        efd::UInt32 dataStride = 0,
        const void* pDataSource = NULL, 
        efd::Bool copyData = false);
    /**
        Creates a new NiShaderConstantMapEntry of the PREDEFINED type.

        The shaderRegister and registerCount parameters are less useful in D3D11, where shaders
        refer to variable by name rather than by a register number. However, the shader constant
        map system in Gamebryo still uses these values to prevent collisions, so a unique value
        must be provided for each entry. D3D11 will also use these values to encode the offset and
        size of each variable in the constant buffer, but applications rarely need to manage those
        details.

        @param pKey Name of the entry.
        @param extra Additional information about the entry.
        @param shaderRegister Shader register for this entry, which must be unique for each entry.
        @param pVariableName Name of the variable to set. If NULL, the name will be obtained from 
            pKey.
    */
    virtual NiShaderError AddPredefinedEntry(
        const efd::Char* pKey,
        efd::UInt32 extra, 
        efd::UInt32 shaderRegister,
        const efd::Char* pVariableName);
    /**
        Creates a new NiShaderConstantMapEntry of the ATTRIBUTE type.

        The shaderRegister and registerCount parameters are less useful in D3D11, where shaders
        refer to variable by name rather than by a register number. However, the shader constant
        map system in Gamebryo still uses these values to prevent collisions, so a unique value
        must be provided for each entry. D3D11 will also use these values to encode the offset and
        size of each variable in the constant buffer, but applications rarely need to manage those
        details.

        @param pKey Name of the entry.
        @param flags Encoding of the type of entry this will be.
        @param extra Additional information about the entry.
        @param shaderRegister Shader register for this entry, which must be unique for each entry.
        @param registerCount Register count for this entry.
        @param pVariableName Name of the variable to set. If NULL, the name will be obtained from 
            pKey.
        @param dataSize Total size of the data block provided to pDataSource.
        @param dataStride Stride of the individual array entries in the data block provided to 
            pDataSource. If the variable is not an array, this should be equal to dataSize.
        @param pDataSource Data provided to the entry as the default value for the variable.
        @param copyData True if the shader constant map entry should save its own copy of the data, 
            or false if the shader constant map entry should only save a pointer to the data.
    */
    virtual NiShaderError AddAttributeEntry(
        const efd::Char* pKey,
        efd::UInt32 flags, 
        efd::UInt32 extra,
        efd::UInt32 shaderRegister, 
        efd::UInt32 registerCount,
        const efd::Char* pVariableName, 
        efd::UInt32 dataSize,
        efd::UInt32 dataStride, 
        const void* pDataSource,
        efd::Bool copyData = true);
    /**
        Creates a new NiShaderConstantMapEntry of the CONSTANT type.

        The shaderRegister and registerCount parameters are less useful in D3D11, where shaders
        refer to variable by name rather than by a register number. However, the shader constant
        map system in Gamebryo still uses these values to prevent collisions, so a unique value
        must be provided for each entry. D3D11 will also use these values to encode the offset and
        size of each variable in the constant buffer, but applications rarely need to manage those
        details.

        @param pKey Name of the entry.
        @param flags Encoding of the type of entry this will be.
        @param extra Additional information about the entry.
        @param shaderRegister Shader register for this entry, which must be unique for each entry.
        @param registerCount Register count for this entry.
        @param pVariableName Name of the variable to set. If NULL, the name will be obtained from 
            pKey.
        @param dataSize Total size of the data block provided to pDataSource.
        @param dataStride Stride of the individual array entries in the data block provided to 
            pDataSource. If the variable is not an array, this should be equal to dataSize.
        @param pDataSource Data provided to the entry as the default value for the variable.
        @param copyData True if the shader constant map entry should save its own copy of the data, 
            or false if the shader constant map entry should only save a pointer to the data.
    */
    virtual NiShaderError AddConstantEntry(
        const efd::Char* pKey,
        efd::UInt32 flags, 
        efd::UInt32 extra,
        efd::UInt32 shaderRegister, 
        efd::UInt32 registerCount,
        const efd::Char* pVariableName, 
        efd::UInt32 dataSize,
        efd::UInt32 dataStride, 
        const void* pDataSource,
        efd::Bool copyData = true);
    /**
        Creates a new NiShaderConstantMapEntry of the GLOBAL type.

        The shaderRegister and registerCount parameters are less useful in D3D11, where shaders
        refer to variable by name rather than by a register number. However, the shader constant
        map system in Gamebryo still uses these values to prevent collisions, so a unique value
        must be provided for each entry. D3D11 will also use these values to encode the offset and
        size of each variable in the constant buffer, but applications rarely need to manage those
        details.

        @param pKey Name of the entry.
        @param flags Encoding of the type of entry this will be.
        @param extra Additional information about the entry.
        @param shaderRegister Shader register for this entry, which must be unique for each entry.
        @param registerCount Register count for this entry.
        @param pVariableName Name of the variable to set. If NULL, the name will be obtained from 
            pKey.
        @param dataSize Total size of the data block provided to pDataSource.
        @param dataStride Stride of the individual array entries in the data block provided to 
            pDataSource. If the variable is not an array, this should be equal to dataSize.
        @param pDataSource Data provided to the entry as the default value for the variable.
        @param copyData True if the shader constant map entry should save its own copy of the data, 
            or false if the shader constant map entry should only save a pointer to the data.
    */
    virtual NiShaderError AddGlobalEntry(
        const efd::Char* pKey,
        efd::UInt32 flags, 
        efd::UInt32 extra,
        efd::UInt32 shaderRegister, 
        efd::UInt32 registerCount,
        const efd::Char* pVariableName, 
        efd::UInt32 dataSize,
        efd::UInt32 dataStride, 
        const void* pDataSource,
        efd::Bool copyData = false);
    /**
        Creates a new NiShaderConstantMapEntry of the OPERATOR type.

        The shaderRegister and registerCount parameters are less useful in D3D11, where shaders
        refer to variable by name rather than by a register number. However, the shader constant
        map system in Gamebryo still uses these values to prevent collisions, so a unique value
        must be provided for each entry. D3D11 will also use these values to encode the offset and
        size of each variable in the constant buffer, but applications rarely need to manage those
        details.

        @param pKey Name of the entry.
        @param flags Encoding of the type of entry this will be.
        @param extra Additional information about the entry.
        @param shaderRegister Shader register for this entry, which must be unique for each entry.
        @param registerCount Register count for this entry.
        @param pVariableName Name of the variable to set. If NULL, the name will be obtained from 
            pKey.
    */
    virtual NiShaderError AddOperatorEntry(
        const efd::Char* pKey,
        efd::UInt32 flags, 
        efd::UInt32 extra,
        efd::UInt32 shaderRegister, 
        efd::UInt32 registerCount,
        const efd::Char* pVariableName);
    /**
        Creates a new NiShaderConstantMapEntry of the OBJECT type.

        The shaderRegister and registerCount parameters are less useful in D3D11, where shaders
        refer to variable by name rather than by a register number. However, the shader constant
        map system in Gamebryo still uses these values to prevent collisions, so a unique value
        must be provided for each entry. D3D11 will also use these values to encode the offset and
        size of each variable in the constant buffer, but applications rarely need to manage those
        details.

        @param pKey Name of the entry.
        @param shaderRegister Shader register for this entry, which must be unique for each entry.
        @param pVariableName Name of the variable to set. If NULL, the name will be obtained from 
            pKey.
        @param objectIndex Index of the NiDynamicEffect object for this entry.
        @param objectType Type of the NiDynamicEffect object for this entry.
        @param count Number of entries in the array if this variable is an array.
    */
    virtual NiShaderError AddObjectEntry(
        const efd::Char* pKey,
        efd::UInt32 shaderRegister, 
        const efd::Char* pVariableName,
        efd::UInt32 objectIndex,
        NiShaderAttributeDesc::ObjectType objectType,
        efd::UInt32 count = 1);

    /// Remove the specified entry from the shader constant map.
    virtual NiShaderError RemoveEntry(const efd::Char* pKey);
    /// Return the specified entry in the shader constant map.
    virtual NiShaderConstantMapEntry* GetEntry(const efd::Char* pKey);
    /// Return the specified entry in the shader constant map.
    virtual NiShaderConstantMapEntry* GetEntryAtIndex(efd::UInt32 index);

    /// Return the number of entries in the shader constant map.
    inline efd::UInt32 GetEntryCount();
    /**
        Update the constant buffer based on the shader constant entries.

        @param callContext Context for the rendering call.
        @param isGlobal Unused.
        @return Whether or not the function succeeded.
    */ 
    NiShaderError UpdateShaderConstants(
        const NiRenderCallContext& callContext,
        efd::Bool isGlobal = false);

    /// Returns whether the shader constant map is capable of being linked to the 
    /// ConstantBufferDesc that is passed in.
    efd::Bool IsLinkable(const ConstantBufferDesc* pCBDesc) const;
    /// Encode the entries in the shader constant map with the offset and size of the variables
    /// in the constant buffer as described by the ConstantBufferDesc.
    efd::Bool LinkShaderConstantBuffer(const ConstantBufferDesc* pCBDesc);

    /// Return the D3D11DataStream that manages the constant buffer for this constant map.
    inline D3D11DataStream* GetShaderConstantDataStream() const;

    /// Create the D3D11DataStream for this constant map's buffer.
    efd::Bool CreateShaderConstantDataStream(
        const ConstantBufferDesc* pCBDesc);
    /// Release the D3D11DataStream for this constant map's buffer.
    void ReleaseShaderConstantDataStream();

    /// Return the string "$Globals", which D3D11 uses for the globnal unnamed constant buffer.
    static const efd::FixedString& GetGlobalConstantBufferString();

    /// @cond EMERGENT_INTERNAL

    /// Copy a texture transform matrix into a matrix that can be passed into a shader program.
    static void SetupTextureTransformMatrix(
        XMMATRIX& result,
        const efd::Matrix3* pTexMatrix, 
        efd::Bool transpose = false);

    /** 
        UpdateConstantBufferPacking will update the register and register
        count of all the NiShaderConstantMapEntry objects in the map
        according to the packed location of each entry in the final constant
        buffer.
        The register and register counts will be encoded with the register and
        the register element; such values will be marked with the
        SCM_REGISTER_ENCODING flag to distinguish them from unencoded values.
        Register values of -1 (0xFFFFFFFF) will remain intact to indicate that
        the entry should not be packed in the constant buffer.
    */
    efd::Bool UpdateConstantBufferPacking(
        const ConstantBufferDesc* pCBDesc,
        NiDataStreamElementSet& dataStreamElements);

    /// Set the D3D11DataStream that manages the constant buffer for this constant map.
    void SetShaderConstantDataStream(D3D11DataStream* pStream);

    /// Enumerations for encoding the register and register element into a 32 bit value.
    enum
    {
        SCM_REGISTER_NONE             = 0xFFFFFFFF,
        SCM_REGISTER_ENCODING         = 0x10000000,
        SCM_REGISTER_ENCODING_MASK    = 0xF0000000,
        SCM_REGISTER_ELEMENT_MASK     = 0x0F000000,
        SCM_REGISTER_ELEMENT_SHIFT    = 24,
        SCM_REGISTER_PACKED_BIT       = 0x00800000,
        SCM_REGISTER_MASK             = 0x0000FFFF,
        SCM_REGISTER_SHIFT            = 0
    };

    /// Encode a register and element into a 32 bit value.
    static efd::Bool EncodePackedRegisterAndElement(
        efd::UInt32& encodedValue,
        efd::UInt32 registerID, 
        efd::UInt32 element,
        efd::Bool packedRegisters);
    /// Decode a register and element from a 32 bit value.
    static efd::Bool DecodePackedRegisterAndElement(
        efd::UInt32 encodedValue,
        efd::UInt32& registerID, 
        efd::UInt32& element,
        efd::Bool& packedRegisters);

    /// Return whether the constant buffer needs to be relinked and possibly reallocated.
    inline efd::Bool IsConstantBufferCurrent() const;
    /// Sets a flag indicating the constant buffer need to be relinked and possibly reallocated.
    inline void SetConstantBufferObsolete();

    /// Return the entry index for a particular entry.
    virtual efd::UInt32 GetEntryIndex(const efd::Char* pKey);

    /// Initialize the static "$Globals" string.
    static void _SDMInit();
    /// Release the static "$Globals" string.
    static void _SDMShutdown();

    /// @endcond
protected:
    enum
    {
        INVALID_ENTRY_INDEX = EE_UINT32_MAX
    };

    /// Insert an entry into the list
    NiShaderError InsertEntry(NiShaderConstantMapEntry* pEntry);

    /// Validate the Predefined entry before it is added.
    static NiShaderError SetupPredefinedEntry(NiShaderConstantMapEntry* pEntry);
    /// Validate the Object entry before it is added.
    static NiShaderError SetupObjectEntry(NiShaderConstantMapEntry* pEntry);

    /// Update all shader constants from the shader constant map entries.
    NiShaderError UpdateShaderConstantValues(
        const NiRenderCallContext& callContext,
        efd::Bool isGlobal);

    /// Copy shader constants for individual shader constant map entries
    /// to the shader constant buffer.
    //@{
    NiShaderError UpdateDefinedConstantValue(
        void* pShaderConstantBuffer,
        NiShaderConstantMapEntry* pEntry, 
        const NiRenderCallContext& callContext);
    NiShaderError UpdateConstantConstantValue(
        void* pShaderConstantBuffer,
        NiShaderConstantMapEntry* pEntry, 
        const NiRenderCallContext& callContext);
    NiShaderError UpdateAttributeConstantValue(
        void* pShaderConstantBuffer,
        NiShaderConstantMapEntry* pEntry, 
        const NiRenderCallContext& callContext,
        efd::Bool isGlobal = false, 
        NiExtraData* pExtraData = 0);
    NiShaderError UpdateGlobalConstantValue(
        void* pShaderConstantBuffer,
        NiShaderConstantMapEntry* pEntry, 
        const NiRenderCallContext& callContext);
    NiShaderError UpdateOperatorConstantValue(
        void* pShaderConstantBuffer,
        NiShaderConstantMapEntry* pEntry, 
        const NiRenderCallContext& callContext,
        efd::Bool isGlobal = false, 
        NiExtraData* pExtraData = 0);
    NiShaderError UpdateObjectConstantValue(
        void* pShaderConstantBuffer,
        NiShaderConstantMapEntry* pEntry, 
        const NiRenderCallContext& callContext);
    //@}

    /// Return the data that will be used to fill in the shader constant.
    //@{
    const void* ObtainDefinedConstantValue(
        NiShaderConstantMapEntry* pEntry,
        const NiRenderCallContext& callContext, 
        efd::UInt32& dataSize,
        efd::UInt32& dataStride,
        XMMATRIX& tempMatrix);
    const void* ObtainConstantConstantValue(
        NiShaderConstantMapEntry* pEntry,
        const NiRenderCallContext& callContext, 
        efd::UInt32& dataSize,
        efd::UInt32& dataStride,
        XMMATRIX& tempMatrix);
    const void* ObtainAttributeConstantValue(
        NiShaderConstantMapEntry* pEntry,
        const NiRenderCallContext& callContext, 
        efd::Bool isGlobal,
        NiExtraData* pExtraData, 
        efd::UInt32& dataSize,
        efd::UInt32& dataStride,
        XMMATRIX& tempMatrix);
    const void* ObtainGlobalConstantValue(
        NiShaderConstantMapEntry* pEntry,
        const NiRenderCallContext& callContext, 
        efd::UInt32& dataSize,
        efd::UInt32& dataStride,
        XMMATRIX& tempMatrix);
    const void* ObtainOperatorConstantValue(
        NiShaderConstantMapEntry* pEntry,
        const NiRenderCallContext& callContext, 
        efd::Bool isGlobal,
        NiExtraData* pExtraData, 
        efd::UInt32& dataSize,
        efd::UInt32& dataStride,
        XMMATRIX& tempMatrix);
    const void* ObtainObjectConstantValue(
        NiShaderConstantMapEntry* pEntry,
        const NiRenderCallContext& callContext, 
        efd::UInt32& dataSize,
        efd::UInt32& dataStride,
        XMMATRIX* pResult);
    //@}

    /// Return the requested data from a specific dynamic effect
    static efd::Bool ObtainDataFromDynamicEffect(
        NiShaderConstantMapEntry* pEntry,
        ObjectMappings mapping, 
        NiDynamicEffect* pDynEffect,
        const NiRenderCallContext& callContext, 
        efd::UInt32& dataSize,
        efd::UInt32& dataStride,
        XMMATRIX* pResult);

    /// Perform the Operator operations.
    //@{
    static const void* PerformOperatorMultiply(
        const void* pOperand1, 
        NiShaderAttributeDesc::AttributeType attributeType1,
        const void* pOperand2, 
        NiShaderAttributeDesc::AttributeType attributeType2,
        efd::Bool inverse, 
        efd::Bool transpose, 
        efd::UInt32& dataSize,
        efd::UInt32& dataStride,
        XMMATRIX& tempMatrix);
    static const void* PerformOperatorDivide(
        const void* pOperand1, 
        NiShaderAttributeDesc::AttributeType attributeType1,
        const void* pOperand2, 
        NiShaderAttributeDesc::AttributeType attributeType2,
        efd::Bool inverse, 
        efd::Bool transpose, 
        efd::UInt32& dataSize,
        efd::UInt32& dataStride,
        XMMATRIX& tempMatrix);
    static const void* PerformOperatorAdd(
        const void* pOperand1, 
        NiShaderAttributeDesc::AttributeType attributeType1,
        const void* pOperand2, 
        NiShaderAttributeDesc::AttributeType attributeType2,
        efd::Bool inverse, 
        efd::Bool transpose, 
        efd::UInt32& dataSize,
        efd::UInt32& dataStride,
        XMMATRIX& tempMatrix);
    static const void* PerformOperatorSubtract(
        const void* pOperand1, 
        NiShaderAttributeDesc::AttributeType attributeType1,
        const void* pOperand2, 
        NiShaderAttributeDesc::AttributeType attributeType2,
        efd::Bool inverse, 
        efd::Bool transpose, 
        efd::UInt32& dataSize,
        efd::UInt32& dataStride,
        XMMATRIX& tempMatrix);
    //@}

    /// Copy the shader constant data into the shader constant buffer.
    static NiShaderError FillShaderConstantBuffer(
        void* pShaderConstantBuffer,
        const void* pSourceData, 
        efd::UInt32 sourceDataSize,
        efd::UInt32 sourceDataStride,
        efd::UInt32 startRegister,
        efd::UInt32 startElement, 
        efd::UInt32 registerCount,
        efd::UInt32 elementCount, 
        efd::UInt32 arrayCount,
        efd::Bool packRegisters, 
        const efd::UInt16* pReorderArray);

    /// Encode start register/register count for a given shader constant entry
    /// based on the current buffer write location.
    static void CalculatePackingEntry(
        efd::UInt32& currentRegister,
        efd::UInt32& currentElement, 
        efd::UInt32 registerCount,
        efd::UInt32 elementCount, 
        efd::UInt32& encodedStartRegister,
        efd::UInt32& encodedRegisterCount, 
        efd::Bool packRegisters);

    /// Determine whether a register value is encoded or not.
    static efd::Bool IsRegisterEncoded(efd::UInt32 registerID);

    /// Pad out an NiDataStreamElementSet.
    void InsertPadding(
        efd::UInt32 paddingInBytes,
        NiDataStreamElementSet& dataStreamElements);

    /// Returns the index of a RenderingPhase.
    efd::UInt32 GetPhaseIndex(NiRenderer::RenderingPhase phase);

    NiTObjectArray<NiShaderConstantMapEntryPtr> m_phaseEntryArray[NiRenderer::PHASE_COUNT];

    D3D11DataStreamPtr m_spShaderConstantDataStream;

    efd::FixedString m_name;

    efd::Bool m_constantBufferCurrent;
    efd::Bool m_externalStream;

    static efd::FixedString ms_globalConstantBufferString;

    static const efd::Float32 ms_dirLightDistance;

    static NiRenderer::RenderingPhase ms_phaseMappingArray[NiRenderer::PHASE_COUNT];
};

/// Define a smart pointer (reference counting, self deleting pointer) for the
/// D3D11ShaderConstantMap class.
typedef efd::SmartPointer<D3D11ShaderConstantMap> D3D11ShaderConstantMapPtr;

}   // End namespace ecr.

#include <ecrD3D11Renderer/D3D11ShaderConstantMap.inl>

#endif // EE_D3D11SHADERCONSTANTMAP_H
