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
#ifndef NISHADOWMANAGER_H
#define NISHADOWMANAGER_H

#include "NiShadowCubeMap.h"
#include "NiTObjectList.h"
#include "NiShadowClickValidator.h"
#include "NiMaterialSwapProcessor.h"
#include "NiShadowGenerator.h"
#include "NiShadowVisitor.h"

class NiSpotShadowWriteMaterial;
class NiPointShadowWriteMaterial;
class NiDirectionalShadowWriteMaterial;
class NiShadowTechnique;
class NiCamera;
class NiCullingProcess;
class NiShadowClickGenerator;

NiSmartPointer(NiShadowClickGenerator);
NiSmartPointer(NiShadowGenerator);

class NIMAIN_ENTRY NiShadowManager : public NiMemObject
{
public:

    enum
    {
        MIN_VERTEX_SHADER_VERSION = 2,
        MIN_GEOMETRY_SHADER_VERSION = 0,
        MIN_PIXEL_SHADER_VERSION = 2,

        MAX_ACTIVE_SHADOWTECHNIQUES = 4,
        MAX_KNOWN_SHADOWTECHNIQUES = 16
    };

    static void Initialize();
    static void Shutdown();

    static NiShadowManager* GetShadowManager();
    static NiMaterial* GetShadowWriteMaterial(
        NiStandardMaterial::LightType eType);
    static NiMaterialSwapProcessorPtr GetMaterialSwapProcessor(
        NiStandardMaterial::LightType eType);
    static NiShadowClickValidatorPtr GetShadowClickValidator();
    static void SetShadowClickValidator(NiShadowClickValidator* pkValidator);

    static bool ValidateShaderVersions(
        unsigned short usVertexShaderVersionMajor,
        unsigned short usVertexShaderVersionMinor,
        unsigned short usGeometryShaderVersionMajor,
        unsigned short usGeometryShaderVersionMinor,
        unsigned short usPixelShaderVersionMajor,
        unsigned short usPixelShaderVersionMinor);
    static bool AreShaderModelsValid();

    static void SetMaxActiveShadowGenerators(unsigned int uiMax);
    static unsigned int GetMaxActiveShadowGenerators();

    static void RendererRecreated();

    static void SetActive(bool bActive, bool bRetainShadowMaps = false);
    static bool GetActive();

    // Specifies if the shadowing system should keep all unused shadow maps in
    // pool for future use, or if they should be deleted. Unused shadow maps
    // will be pooled by default.
    static void SetPoolShadowMaps(bool bPoolShadowMaps);
    static bool GetPoolShadowMaps();

    // Callback for creating the NiShadowVisitor object that will be used
    // by the shadowing system.
    typedef NiShadowVisitor* (*CreateShadowVisitor)();

    static void SetShadowVisitorFactory(CreateShadowVisitor pfnVisitorFactory);

    static void RecreateShadowVisitor();

    static NiShadowVisitor* GetShadowVisitor();

    // Callback for creating the NiRenderClickValidator object that will be used
    // by the shadowing system.
    typedef NiShadowClickValidator* (*CreateShadowRenderClickValidator)();

    static void SetShadowRenderClickValidatorFactory(
        CreateShadowRenderClickValidator pfnValidatorFactory);

    // Callback for creating the NiCullingProcess object that will be used
    // by the shadowing system.
    typedef NiCullingProcess* (*CreateShadowCullingProcess)();

    static void SetShadowRenderCullingProcessFactory(
        CreateShadowCullingProcess pfnCullingProcessFactory);

    // Default callback for specifying the NiCullingProcess for the
    // shadowing system to use. This callback creates the NiMeshCullingProcess
    // object.
    static NiCullingProcess* CreateDefaultShadowCullingProcess();

    // Maximum texture memory management
    typedef void (*PurgeShadowMaps)
        (unsigned int uiBytesNeeded,
        NiTPointerList<NiShadowGeneratorPtr>& kActiveShadowGenerators,
        NiTPointerList<NiShadowMap*>& m_kAvailableShadowMaps,
        NiTPointerList<NiShadowCubeMap*>& m_kAvailableShadowCubeMaps,
        bool bMaxTexMemoryResized);

    static void DefaultPurgeCallback(
        unsigned int uiBytesNeeded,
        NiTPointerList<NiShadowGeneratorPtr>& kActiveShadowGenerators,
        NiTPointerList<NiShadowMap*>& m_kAvailableShadowMaps,
        NiTPointerList<NiShadowCubeMap*>& m_kAvailableShadowCubeMaps,
        bool bMaxTexMemoryResized);
    static inline void SetPurgeShadowMapsCallback(PurgeShadowMaps pfnCallback);
    static inline void SetMaxTextureMemoryAllocation(unsigned int uiMax);
    static inline unsigned int GetMaxTextureMemoryAllocation();
    static inline unsigned int GetCurrentTextureMemoryAllocation();

    // NiShadowTechnique management
    static bool RegisterShadowTechnique(NiShadowTechnique* pkShadowTechnique,
        unsigned short usSlot, unsigned short usShaderID);

    static NiShadowTechnique* GetActiveShadowTechnique(unsigned short usSlot);
    static NiShadowTechnique* GetActiveShadowTechnique(
        const NiFixedString& kTechniqueName);

    static NiShadowTechnique* GetKnownShadowTechnique(unsigned short usID);
    static NiShadowTechnique* GetKnownShadowTechnique(
        const NiFixedString& kTechniqueName);

    // NiShadowGenerator management
    static bool AddShadowGenerator(NiShadowGenerator* pkGenerator);
    static bool DeleteShadowGenerator(NiShadowGenerator* pkGenerator);
    static void ReorganizeActiveShadowGenerators();

    static const NiTPointerList<NiShadowGeneratorPtr>& GetShadowGenerators();
    static const NiTPointerList<NiShadowGeneratorPtr>&
        GetActiveShadowGenerators();

    // NiShadowMap management
    static NiShadowMap* CreateShadowMap(
        unsigned int uiWidth,
        unsigned int uiHeight,
        NiShadowTechnique* pkTechnique,
        NiStandardMaterial::LightType eType);
    static void DestroyShadowMap(NiShadowMap* pkShadowMap);
    static void DestroyAllShadowMaps();

    // NiShadowCubeMap management
    static NiShadowCubeMap* CreateShadowCubeMap(
        unsigned int uiSize, 
        NiShadowTechnique* pkTechnique,
        NiStandardMaterial::LightType eType);
    static void DestroyShadowCubeMap(NiShadowCubeMap* pkShadowCubeMap);
    static void DestroyAllShadowCubeMaps();

    static NiTListIterator RequestClosestShadowMap(
        unsigned int uiDesiredHeight, unsigned int uiDesiredWidth,
        NiTexture::FormatPrefs& kFormatPrefs, bool bExactSizeOnly);
    static NiTListIterator RequestClosestShadowMap(
        unsigned int uiDesiredHeight, unsigned int uiDesiredWidth,
        NiTexture::FormatPrefs& kFormatPrefs, NiShadowMap*& pkClosestShadowMap,
        bool bExactSizeOnly);
    static NiTListIterator RequestClosestShadowCubeMap(
        unsigned int uiDesiredSize, NiTexture::FormatPrefs& kFormatPrefs,
        bool bExactSizeOnly);
    static NiTListIterator RequestClosestShadowCubeMap(
        unsigned int uiDesiredSize,
        NiTexture::FormatPrefs& kFormatPrefs,
        NiShadowCubeMap*& pkClosestShadowCubeMap,
        bool bExactSizeOnly);

    // Shadow click generator functions.
    static bool RegisterShadowClickGenerator(
        NiShadowClickGenerator* pkShadowClickGenerator);
    static NiShadowClickGenerator* GetShadowClickGenerator(
        const NiFixedString& kName);
    static NiShadowClickGenerator* GetActiveShadowClickGenerator();
    static bool SetActiveShadowClickGenerator(
        NiShadowClickGenerator* pkActiveShadowClickGenerator);
    static bool SetActiveShadowClickGenerator(const NiFixedString& kName);
    static const NiTObjectPtrSet<NiShadowClickGeneratorPtr>&
        GetShadowClickGenerators();

    static void SetSceneCamera(NiCamera* pkSceneCamera);
    static NiCamera* GetSceneCamera();

    static void SetCullingProcess(NiCullingProcess* pkCullingProcess);
    static NiCullingProcess* GetCullingProcess();

    // Function that generates a list of render click objects that can be used
    // to render the shadow maps.
    static const NiTPointerList<NiRenderClick*>& GenerateRenderClicks();

    // Helper functions
    static unsigned int GetApproximateTexMemUsage(
        const unsigned int uiWidth, const unsigned int uiHeight,
        const NiTexture::FormatPrefs& kPrefs, const bool bCubeMap);

    // *** begin Emergent internal use only ***
    static void MakeShadowMapAvailable(NiShadowMap* pkShadowMap);
    static void MakeShadowMapUnavailable(NiShadowMap* pkShadowMap);
    static NiShadowMap* MakeShadowMapUnavailable(NiTListIterator kSMIter);

    static void MakeShadowCubeMapAvailable(NiShadowCubeMap* pkShadowCubeMap);
    static void MakeShadowCubeMapUnavailable(NiShadowCubeMap* pkShadowCubeMap);
    static NiShadowCubeMap* MakeShadowCubeMapUnavailable(
        NiTListIterator kSMIter);

    static void AppendRenderClick(NiRenderClick* pkClick);
    static bool SetShadowGeneratorActiveState(NiShadowGenerator* pkGenerator,
        bool bActive);

    static NiDepthStencilBuffer* GetCompatibleDepthStencil(
        Ni2DBuffer* pkBuffer, const NiPixelFormat* pkDepthFormat);
    // *** end Emergent internal use only ***

protected:
    NiShadowManager();
    ~NiShadowManager();

    // Locks/Unlocks access to global the list of NiShadowGenerator objects.
    // Access to the shadow generator list is automatically locked when:
    // -Generating shadow render clicks
    // -Reorganizing active the NiShadowGenerator objects
    // -Adding a new NiShadowGenerator
    // -Deleting a NiShadowGenerator
    void LockShadowGenerators();
    void UnlockShadowGenerators();

    void OnActiveShadowClickGeneratorChanged();

    // Masks used to encode light data
    enum
    {
        LIGHT_TYPE_MASK = 0x00FF,
        LIGHT_INDEX_MASK = 0xFF00,
        LIGHT_INDEX_SHIFT = 8
    };

    NiShadowTechnique* m_pkActiveShadowTechniques[MAX_ACTIVE_SHADOWTECHNIQUES];
    NiShadowTechnique* m_pkKnownShadowTechniques[MAX_KNOWN_SHADOWTECHNIQUES];

    NiMaterial* m_apkShadowWriteMaterial[
        NiStandardMaterial::LIGHT_MAX];

    NiTObjectList<NiShadowMap> m_kShadowMapPool;
    NiTPointerList<NiShadowMap*> m_kAvailableShadowMaps;

    NiTObjectList<NiShadowCubeMap> m_kShadowCubeMapPool;
    NiTPointerList<NiShadowCubeMap*> m_kAvailableShadowCubeMaps;

    NiTObjectPtrSet<NiShadowClickGeneratorPtr> m_kShadowClickGenerators;

    int m_iActiveShadowClickGeneratorIndex;
    unsigned int m_uiCurrentTextureMemoryAllocation;

    PurgeShadowMaps m_pfnPurgeShadowMapsCallback;
    unsigned int m_uiMaxActiveShadowGenerators;
    unsigned int m_uiMaxTexureMemoryAllocation;

    NiCameraPtr m_spSceneCamera;
    NiCullingProcessPtr m_spCullingProcess;

    NiMaterialSwapProcessorPtr
        m_aspMaterialSwapProcessor[NiStandardMaterial::LIGHT_MAX];

    NiShadowClickValidatorPtr m_spShadowClickValidator;

    NiTPointerList<NiShadowGeneratorPtr> m_kGenerators;
    NiTPointerList<NiShadowGeneratorPtr> m_kActiveGenerators;

    NiTPointerList<NiRenderClick*> m_kRenderClicks;

    // Fast critical section for locking access to the global NiShadowGenerator list.
    // Note, since this is a efd::FastCriticalSection recursive locking is _not_ supported.
    efd::FastCriticalSection m_kShadowGeneratorCritcalSection;

    // Used to create the set of shadow caster/reciever objects of
    // a NiShadowGenerator.
    NiShadowVisitor* m_pkShadowVisitor;

    bool m_bActive;
    bool m_bValidShaderModels;
    bool m_bPoolShadowMaps;

    // Boolean used to gate logging of shadow map memory related issues.
    bool m_bPrevShadowMapAllocFailed;

    static NiShadowManager* ms_pkShadowManager;
    static CreateShadowVisitor ms_pfnShadowVisitorFactory;
    static CreateShadowRenderClickValidator ms_pfnShadowClickValidatorFactory;
    static CreateShadowCullingProcess ms_pfnShadowCullingProcessFactory;
};

#include "NiShadowManager.inl"

#endif // NISHADOWMANAGER_H
