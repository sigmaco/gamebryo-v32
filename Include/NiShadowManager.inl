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

//--------------------------------------------------------------------------------------------------
inline NiShadowManager* NiShadowManager::GetShadowManager()
{
    return ms_pkShadowManager;
}

//--------------------------------------------------------------------------------------------------
inline bool NiShadowManager::AreShaderModelsValid()
{
    EE_ASSERT(ms_pkShadowManager);
    return ms_pkShadowManager->m_bValidShaderModels;
}

//--------------------------------------------------------------------------------------------------
inline NiMaterial* NiShadowManager::GetShadowWriteMaterial(
    NiStandardMaterial::LightType eType)
{
    EE_ASSERT(ms_pkShadowManager);
    EE_ASSERT(eType < NiStandardMaterial::LIGHT_MAX);
    return ms_pkShadowManager->m_apkShadowWriteMaterial[eType];
}

//--------------------------------------------------------------------------------------------------
inline NiMaterialSwapProcessorPtr NiShadowManager::GetMaterialSwapProcessor(
    NiStandardMaterial::LightType eType)
{
    EE_ASSERT(ms_pkShadowManager);
    EE_ASSERT(eType < NiStandardMaterial::LIGHT_MAX);
    return ms_pkShadowManager->m_aspMaterialSwapProcessor[eType];
}

//--------------------------------------------------------------------------------------------------
inline NiShadowClickValidatorPtr NiShadowManager::GetShadowClickValidator()
{
    EE_ASSERT(ms_pkShadowManager);
    return ms_pkShadowManager->m_spShadowClickValidator;
}

//--------------------------------------------------------------------------------------------------
inline void NiShadowManager::SetShadowClickValidator(
    NiShadowClickValidator* pkValidator)
{
    EE_ASSERT(ms_pkShadowManager);
    ms_pkShadowManager->m_spShadowClickValidator = pkValidator;
}

//--------------------------------------------------------------------------------------------------
inline NiShadowTechnique* NiShadowManager::GetActiveShadowTechnique(
    unsigned short usSlot)
{
    EE_ASSERT(ms_pkShadowManager);
    EE_ASSERT(usSlot < MAX_ACTIVE_SHADOWTECHNIQUES);
    return ms_pkShadowManager->m_pkActiveShadowTechniques[usSlot];
}

//--------------------------------------------------------------------------------------------------
inline NiShadowTechnique* NiShadowManager::GetKnownShadowTechnique(
    unsigned short usID)
{
    EE_ASSERT(ms_pkShadowManager);
    EE_ASSERT(usID < MAX_KNOWN_SHADOWTECHNIQUES);
    return ms_pkShadowManager->m_pkKnownShadowTechniques[usID];
}

//--------------------------------------------------------------------------------------------------
inline NiTListIterator NiShadowManager::RequestClosestShadowMap(
    unsigned int uiDesiredHeight, unsigned int uiDesiredWidth,
    NiTexture::FormatPrefs& kFormatPrefs, bool bExactSizeOnly)
{
    NiShadowMap* pkShadowMap = NULL;
    return RequestClosestShadowMap(uiDesiredHeight, uiDesiredWidth,
        kFormatPrefs, pkShadowMap, bExactSizeOnly);
}

//--------------------------------------------------------------------------------------------------
inline NiTListIterator NiShadowManager::RequestClosestShadowCubeMap(
    unsigned int uiDesiredSize, NiTexture::FormatPrefs& kFormatPrefs,
    bool bExactSizeOnly)
{
    NiShadowCubeMap* pkShadowCubeMap = NULL;
    return RequestClosestShadowCubeMap(uiDesiredSize, kFormatPrefs,
        pkShadowCubeMap, bExactSizeOnly);
}

//--------------------------------------------------------------------------------------------------
inline const NiTObjectPtrSet<NiShadowClickGeneratorPtr>&
    NiShadowManager::GetShadowClickGenerators()
{
    EE_ASSERT(ms_pkShadowManager);
    return ms_pkShadowManager->m_kShadowClickGenerators;
}

//--------------------------------------------------------------------------------------------------
inline NiCamera* NiShadowManager::GetSceneCamera()
{
    EE_ASSERT(ms_pkShadowManager);
    return ms_pkShadowManager->m_spSceneCamera;
}

//--------------------------------------------------------------------------------------------------
inline NiCullingProcess* NiShadowManager::GetCullingProcess()
{
    EE_ASSERT(ms_pkShadowManager);
    return ms_pkShadowManager->m_spCullingProcess;
}

//--------------------------------------------------------------------------------------------------
inline void NiShadowManager::MakeShadowMapUnavailable(NiShadowMap* pkShadowMap)
{
    EE_ASSERT(ms_pkShadowManager);
    ms_pkShadowManager->m_kAvailableShadowMaps.Remove(pkShadowMap);
}

//--------------------------------------------------------------------------------------------------
inline NiShadowMap* NiShadowManager::MakeShadowMapUnavailable(
    NiTListIterator kSMIter)
{
    EE_ASSERT(ms_pkShadowManager);
    EE_ASSERT(kSMIter);
    return ms_pkShadowManager->m_kAvailableShadowMaps.RemovePos(kSMIter);
}

//--------------------------------------------------------------------------------------------------
inline void NiShadowManager::MakeShadowCubeMapUnavailable(
    NiShadowCubeMap* pkShadowCubeMap)
{
    EE_ASSERT(ms_pkShadowManager);
    ms_pkShadowManager->m_kAvailableShadowCubeMaps.Remove(pkShadowCubeMap);
}

//--------------------------------------------------------------------------------------------------
inline NiShadowCubeMap* NiShadowManager::MakeShadowCubeMapUnavailable(
    NiTListIterator kSMIter)
{
    EE_ASSERT(ms_pkShadowManager);
    EE_ASSERT(kSMIter);
    return ms_pkShadowManager->m_kAvailableShadowCubeMaps.RemovePos(kSMIter);
}

//--------------------------------------------------------------------------------------------------
inline void NiShadowManager::AppendRenderClick(NiRenderClick* pkClick)
{
    EE_ASSERT(ms_pkShadowManager);

    EE_ASSERT(pkClick);
    ms_pkShadowManager->m_kRenderClicks.AddTail(pkClick);
}

//--------------------------------------------------------------------------------------------------
inline unsigned int NiShadowManager::GetMaxActiveShadowGenerators()
{
    EE_ASSERT(ms_pkShadowManager);
    return ms_pkShadowManager->m_uiMaxActiveShadowGenerators;
}

//--------------------------------------------------------------------------------------------------
inline bool NiShadowManager::GetActive()
{
    EE_ASSERT(ms_pkShadowManager);
    return ms_pkShadowManager->m_bActive;
}

//--------------------------------------------------------------------------------------------------
inline const NiTPointerList<NiShadowGeneratorPtr>&
    NiShadowManager::GetShadowGenerators()
{
    EE_ASSERT(ms_pkShadowManager);
    return ms_pkShadowManager->m_kGenerators;
}

//--------------------------------------------------------------------------------------------------
inline const NiTPointerList<NiShadowGeneratorPtr>&
    NiShadowManager::GetActiveShadowGenerators()
{
    EE_ASSERT(ms_pkShadowManager);
    return ms_pkShadowManager->m_kActiveGenerators;
}

//--------------------------------------------------------------------------------------------------
inline void NiShadowManager::SetPurgeShadowMapsCallback(
    NiShadowManager::PurgeShadowMaps pfnCallback)
{
    EE_ASSERT(ms_pkShadowManager);
    EE_ASSERT(pfnCallback);
    ms_pkShadowManager->m_pfnPurgeShadowMapsCallback = pfnCallback;
}

//--------------------------------------------------------------------------------------------------
inline void NiShadowManager::SetMaxTextureMemoryAllocation(unsigned int uiMax)
{
    EE_ASSERT(ms_pkShadowManager);
    ms_pkShadowManager->m_uiMaxTexureMemoryAllocation = uiMax;

    if (ms_pkShadowManager->m_uiCurrentTextureMemoryAllocation >
        ms_pkShadowManager->m_uiMaxTexureMemoryAllocation)
    {
        // The currently texture memory allocation exceeds the new maximum
        // allowed texture memory. Purge shadow maps until we no longer exceed
        // this limit.
        EE_ASSERT(ms_pkShadowManager->m_pfnPurgeShadowMapsCallback);
        ms_pkShadowManager->m_pfnPurgeShadowMapsCallback(
            0,
            ms_pkShadowManager->m_kActiveGenerators,
            ms_pkShadowManager->m_kAvailableShadowMaps,
            ms_pkShadowManager->m_kAvailableShadowCubeMaps,
            true);

        // If this assert is hit it means the Purge Shadow maps callback failed
        // to purge enough texture memory. This should never happen, it is the
        // responsibility of that callback to ensure the maximum allowed
        // texture memory allocation is not exceeded.
        EE_ASSERT(ms_pkShadowManager->m_uiCurrentTextureMemoryAllocation <=
            ms_pkShadowManager->m_uiMaxTexureMemoryAllocation);
    }
}

//--------------------------------------------------------------------------------------------------
inline unsigned int NiShadowManager::GetMaxTextureMemoryAllocation()
{
    EE_ASSERT(ms_pkShadowManager);
    return ms_pkShadowManager->m_uiMaxTexureMemoryAllocation;
}

//--------------------------------------------------------------------------------------------------
inline unsigned int NiShadowManager::GetCurrentTextureMemoryAllocation()
{
    EE_ASSERT(ms_pkShadowManager);
    return ms_pkShadowManager->m_uiCurrentTextureMemoryAllocation;
}

//--------------------------------------------------------------------------------------------------
inline void NiShadowManager::SetShadowVisitorFactory(CreateShadowVisitor
    pfnVisitorFactory)
{
    ms_pfnShadowVisitorFactory = pfnVisitorFactory;

    // A Shadow visitor has already been created. Delete it and replace it
    // with the shadow visitor from the new factory.
    if (ms_pkShadowManager &&  ms_pkShadowManager->m_pkShadowVisitor)
    {
        NiDelete ms_pkShadowManager->m_pkShadowVisitor;
        ms_pkShadowManager->m_pkShadowVisitor = ms_pfnShadowVisitorFactory();
    }
}

//--------------------------------------------------------------------------------------------------
inline NiShadowVisitor* NiShadowManager::GetShadowVisitor()
{
    return (ms_pkShadowManager != NULL) ? ms_pkShadowManager->m_pkShadowVisitor : NULL;
}

//--------------------------------------------------------------------------------------------------
inline void NiShadowManager::SetShadowRenderClickValidatorFactory(
    CreateShadowRenderClickValidator pfnValidatorFactory)
{
    ms_pfnShadowClickValidatorFactory = pfnValidatorFactory;

    // A Shadow visitor has already been created. Delete it and replace it
    // with the shadow visitor from the new factory.
    if (ms_pkShadowManager &&  ms_pkShadowManager->m_spShadowClickValidator)
    {
        // The current m_spShadowClickValidator will be dec ref count deleted here.
        ms_pkShadowManager->m_spShadowClickValidator = ms_pfnShadowClickValidatorFactory();
    }
}

//--------------------------------------------------------------------------------------------------
inline void NiShadowManager::SetShadowRenderCullingProcessFactory(
    CreateShadowCullingProcess pfnCullingProcessFactory)
{
    ms_pfnShadowCullingProcessFactory = pfnCullingProcessFactory;

    // A Shadow visitor has already been created. Delete it and replace it
    // with the shadow visitor from the new factory.
    if (ms_pkShadowManager &&  ms_pkShadowManager->m_spCullingProcess)
    {
        // The current m_spCullingProcess will be dec ref count deleted here.
        ms_pkShadowManager->m_spCullingProcess = ms_pfnShadowCullingProcessFactory();
        if (ms_pkShadowManager->m_spShadowClickValidator)
        {
            ms_pkShadowManager->m_spShadowClickValidator->SetCullingProcess(
                ms_pkShadowManager->m_spCullingProcess);
        }
    }
}

//--------------------------------------------------------------------------------------------------