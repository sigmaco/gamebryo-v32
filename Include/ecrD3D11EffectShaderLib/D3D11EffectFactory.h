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
#ifndef EE_D3D11EFFECTFACTORY_H
#define EE_D3D11EFFECTFACTORY_H

#include <ecrD3D11EffectShaderLib/ecrD3D11EffectShaderLibType.h>
#include <ecrD3D11Renderer/D3D11Renderer.h>
#include <ecrD3D11Renderer/D3D11Include.h>

#include <NiCriticalSection.h>
#include <NiSmartPointer.h>
#include <NiTStringMap.h>

namespace ecr
{

class D3D11EffectFile;

/// @cond EMERGENT_INTERNAL

/**
    D3D11EffectFactory is an internal class for managing Gamebryo's Effects11 implementation.
*/
class EE_ECRD3D11EFFECTSHADER_ENTRY D3D11EffectFactory : public NiMemObject
{
public:
    static D3D11EffectFactory* GetInstance(efd::Bool createNew = true);

    //*** Helper functions
    // D3D11Effect creation
    static D3D11EffectFile* LoadD3D11EffectFromMemory(
        ID3D11Device* pDevice,
        const efd::Char* pShaderName,
        efd::UInt32 codeSize,
        void* pCode,
        efd::Bool isCompiled,
        const efd::Char* pPathToFile = NULL);

    // Effect compilation flags
    static efd::UInt32 GetD3D11EffectHLSLFlags();
    static void SetD3D11EffectHLSLFlags(efd::UInt32 hlslFlags);

    static efd::UInt32 GetD3D11EffectFXFlags();
    static void SetD3D11EffectFXFlags(efd::UInt32 fxFlags);

    // *** begin Emergent internal use only ***
    static const efd::Char* GetD3D11EffectDirectory();
    static void SetD3D11EffectDirectory(const efd::Char* pDirectory);

    D3D11EffectFile* CompileD3D11Effect(
        const efd::Char* pEffectName,
        efd::UInt32 codeSize,
        void* pCode,
        efd::Bool isCompiled,
        const efd::Char* pPathToFile = NULL);

    inline efd::Bool CreateD3D11Effect(
        ID3D11Device* pDevice,
        D3D11EffectFile* pD3D11EffectFile,
        efd::Bool parse = true);

    // Find functions
    virtual D3D11EffectFile* GetD3D11EffectFile(
        const efd::Char* pFileName) const;

    // Shader insertion/removal
    virtual void InsertD3D11EffectFileIntoMap(D3D11EffectFile* pEffectFile);
    virtual void RemoveD3D11EffectFileFromMap(const efd::Char* pName);

    static efd::Bool D3D11EffectFactory::ResolveD3D11EffectFileName(
        const efd::Char* pOriginalName,
        efd::Char* pTrueName,
        unsigned int bufferSize);

    void DestroyRendererData();

    static void _SDMInit();
    static void _SDMShutdown();

    static void SetFXLSupport(efd::Bool enable);
    static efd::Bool GetFXLSupport();
    // *** end Emergent internal use only ***

protected:
    D3D11EffectFactory();
    virtual ~D3D11EffectFactory();

    void UpdateMacros();

    static D3D11EffectFactory* ms_pFactory;

    static efd::UInt32 ms_fxFlags;

    static efd::Char* ms_pD3D11EffectDirectory;
    static efd::Char* ms_pDefaultExtension;

    // Maps for effect file names to effects.
    NiTStringPointerMap<D3D11EffectFile*>* m_pD3D11EffectMap;

    static efd::Bool ms_fxlSupport;

    efd::CriticalSection m_criticalSection;
    D3D11Include m_include;
};

/// Define a smart pointer (reference counting, self deleting pointer) for the D3D11EffectFactory
/// class.
typedef efd::SmartPointer<D3D11EffectFactory> D3D11EffectFactoryPtr;

/// @endcond

}   // End namespace ecr.

#include <ecrD3D11EffectShaderLib/D3D11EffectFactory.inl>

#endif // EE_D3D11EFFECTFACTORY_H
