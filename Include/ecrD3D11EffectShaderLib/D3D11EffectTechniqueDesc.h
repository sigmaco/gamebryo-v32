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
#ifndef EE_D3D11EFFECTTECHNIQUEDESC_H
#define EE_D3D11EFFECTTECHNIQUEDESC_H

#include <ecrD3D11EffectShaderLib/ecrD3D11EffectShaderLibType.h>

#include <ecrD3D11Renderer/D3D11Headers.h>
#include <NiGPUProgram.h>
#include <NiSemanticAdapterTable.h>

namespace ecr
{

/// @cond EMERGENT_INTERNAL

/**
    D3D11EffectTechniqueDesc is an internal class for managing Gamebryo's Effects11 implementation.
*/
class EE_ECRD3D11EFFECTSHADER_ENTRY D3D11EffectTechniqueDesc : public NiMemObject
{
public:
    D3D11EffectTechniqueDesc();

    efd::FixedString m_shaderName;
    efd::FixedString m_techniqueName;
    efd::FixedString m_desc;

    efd::UInt32 m_implementation;
    efd::UInt32 m_featureLevel;
    efd::UInt32 m_userVersion;

    efd::UInt32 m_bonesPerPartition;
    efd::UInt32 m_nbtSourceUV;

    NiShaderRequirementDesc::NBTFlags m_nbtMethod;
    efd::Bool m_usesNiRenderState;

    // This is an arbitrary constant - if shaders with more passes need
    // to be parsed, then this value can be increased without causing problems.
    enum
    {
        MAX_PASS_COUNT = 8
    };

    efd::UInt32 m_passCount;
    efd::UInt8 m_bufferCount[MAX_PASS_COUNT];

    efd::FixedString m_constantBufferNames
        [MAX_PASS_COUNT]
        [D3D11_COMMONSHADER_CONSTANT_BUFFER_REGISTER_COUNT];

    efd::UInt32 m_constantBufferShaderTypes
        [MAX_PASS_COUNT]
        [D3D11_COMMONSHADER_CONSTANT_BUFFER_REGISTER_COUNT];

    NiSemanticAdapterTable m_adapterTable;
};

/// @endcond

}   // End namespace ecr.

#endif // EE_D3D11EFFECTTECHNIQUEDESC_H
