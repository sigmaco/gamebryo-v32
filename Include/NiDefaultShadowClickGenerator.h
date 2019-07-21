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
#ifndef NIDEFAULTSHADOWCLICKGENERATOR_H
#define NIDEFAULTSHADOWCLICKGENERATOR_H

#include "NiShadowClickGenerator.h"
#include "NiRenderObject.h"

class NIMAIN_ENTRY NiDefaultShadowClickGenerator :
    public NiShadowClickGenerator
{
    NiDeclareRTTI;

public:
    NiDefaultShadowClickGenerator();
    NiDefaultShadowClickGenerator(NiFixedString kName);
    virtual ~NiDefaultShadowClickGenerator();

    virtual bool GenerateRenderClicks(
        const NiTPointerList<NiShadowGeneratorPtr>& kGenerators);

    virtual void ReorganizeActiveShadowGenerators(
        NiTPointerList<NiShadowGeneratorPtr>& kActiveGenerators,
        NiTPointerList<NiShadowGeneratorPtr>& kAllGenerators);

    // Returns the ID of the last frame that the shadow render clicks were
    // produced. The NiDefaultShadowClickGenerator will not produce a new set of
    // shadow render clicks if the last frame ID matches the current frame ID.
    // However, derived subclasses may implement different behavior.
    NiUInt32 GetLastFrameID();

    // Resets the cached last frame ID allowing shadow render clicks to be produced
    // for the same frame ID.
    void ResetLastFrameID();

protected:

    virtual bool PrepareSpotLightShadowGenerator(
        NiShadowGenerator* pkGenerator);
    virtual bool PreparePointLightShadowGenerator(
        NiShadowGenerator* pkGenerator);
    virtual bool PrepareDirectionalLightShadowGenerator(
        NiShadowGenerator* pkGenerator);

    virtual bool HandleSpotLight(NiShadowGenerator* pkGenerator,
        NiSpotLight* pkSpotLight, bool bRegenerateViews,
        bool bUpdateShadowMaps);
    virtual bool HandlePointLight(NiShadowGenerator* pkGenerator,
        NiPointLight* pkPointLight, bool bRegenerateViews,
        bool bUpdateShadowMaps);
    virtual bool HandleDirectionalLight(NiShadowGenerator* pkGenerator,
        NiDirectionalLight* pkDirLight, bool bRegenerateViews,
        bool bUpdateShadowMaps);

    virtual NiShadowMap* ObtainAndAssignShadowMap(
        NiShadowGenerator* pkGenerator,
        unsigned int uiSMIndex,
        NiRenderObject* pkGeometry,
        NiStandardMaterial::LightType eShadowLightType);
    virtual NiShadowCubeMap* ObtainAndAssignShadowCubeMap(
        NiShadowGenerator* pkGenerator,
        unsigned int uiSMIndex,
        NiRenderObject* pkGeometry,
        NiStandardMaterial::LightType eShadowLightType);

    void UpdateDirLightFrustum(NiBound* pkBound,
        NiShadowGenerator* pkGenerator, NiDirectionalLight* pkDirLight,
        float* pfNearClippingDist, float* pfFarClippingDist,
        float* pfFrustumWidth, NiPoint3* pkPosition);

    NiTPrimitiveArray<float> m_kShadowGeneratorsDistSquared;
    NiTPrimitiveArray<NiShadowGenerator*> m_kSortedShadowGenerators;

    // Temporary list used to store the list of all the caster/receiver
    // geometry for a shadow generator.
    NiAVObjectRawList m_kGeometryList;

    NiTMap <NiDirectionalLight*, float> m_kDirLightMap;

    NiFixedString kVSMTechniqueName;

    // The last frame shadow render clicks were generated.
    NiUInt32 m_uiLastFrameID;
};

NiSmartPointer(NiDefaultShadowClickGenerator);

#endif  // #ifndef NIDEFAULTSHADOWCLICKGENERATOR_H
