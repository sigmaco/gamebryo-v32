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
#ifndef NIDYNAMICEFFECTSTATE_H
#define NIDYNAMICEFFECTSTATE_H

#include "NiBool.h"
#include "NiRefObject.h"
#include "NiSmartPointer.h"
#include "NiDynamicEffect.h"
#include "NiRTLib.h"
#include "NiDynamicEffectStateManager.h"


class NiLight;

NiSmartPointer(NiDynamicEffectState);
NiSmartPointer(NiTextureEffect);

typedef void* NiDynEffectStateIter;

class NIMAIN_ENTRY NiDynamicEffectState : public NiRefObject
{
public:
    inline NiDynamicEffectState();

    NiDynamicEffectState* Copy() const;

    virtual ~NiDynamicEffectState();

    void AddEffect(NiDynamicEffect* pEffect);
    void RemoveEffect(NiDynamicEffect* pEffect);

    inline NiDynEffectStateIter GetLightHeadPos() const;
    inline NiLight* GetNextLight(NiDynEffectStateIter& iter) const;

    inline NiDynEffectStateIter GetProjLightHeadPos() const;
    inline NiTextureEffect* GetNextProjLight(
        NiDynEffectStateIter& iter) const;

    inline NiDynEffectStateIter GetProjShadowHeadPos() const;
    inline NiTextureEffect* GetNextProjShadow(
        NiDynEffectStateIter& iter) const;

    inline NiTextureEffect* GetEnvironmentMap() const;
    inline NiTextureEffect* GetFogMap() const;

    NiBool Equal(const NiDynamicEffectState* pState) const;

    inline unsigned int GetHashKey();

    inline bool IsMultiTexture() const;

protected:
    NiDynamicEffectState(const NiDynamicEffectState&) : NiRefObject() { /* */ }
    inline void SetMultiTexture();

    virtual void DeleteThis();

    class NIMAIN_ENTRY ListItem : public NiMemObject
    {
    public:
        ListItem* m_pNext;
        NiDynamicEffect* m_pItem;
    };

    static bool ListsEqual(const ListItem* pL1, const ListItem* pL2);
    static void ListDelete(ListItem* &pL);
    static void ListCopy(const ListItem* pSrc, ListItem* &pDest);

    void ListInsertSorted(ListItem* &pL, NiDynamicEffect* pItem);
    void ListRemove(ListItem* &pL, NiDynamicEffect* pItem);

    ListItem* m_pLightList;
    ListItem* m_pProjLightList;
    ListItem* m_pProjShadowList;
    NiTextureEffect* m_pEnvMap;
    NiTextureEffect* m_pFogMap;

    unsigned int m_uiHashKey;
    bool m_bMultiTexture;
};

#include "NiDynamicEffectState.inl"

#endif // NIDYNAMICEFFECTSTATE_H
