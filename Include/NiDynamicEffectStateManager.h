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
#ifndef NIDYNAMICEFFECTSTATEMANAGER_H
#define NIDYNAMICEFFECTSTATEMANAGER_H

#include "NiMainLibType.h"
#include "NiBool.h"
#include "NiRefObject.h"
#include "NiSmartPointer.h"
#include "NiDynamicEffect.h"
#include "NiRTLib.h"
#include "NiTPointerMap.h"
#include "NiTPool.h"

class NiDynamicEffectState;

class NIMAIN_ENTRY NiDynamicEffectStateManager : public NiMemObject
{
public:
    enum
    {
        DEFAULT_MAP_SIZE    = 257,
        DEFAULT_LIST_ENTRY_POOL_SIZE = 256
    };

    inline void ResizeMap(NiUInt32 uiPrimeSize);

    // *** begin Emergent internal use only ***
    static void _SDMInit();
    static void _SDMShutdown();

    static inline NiDynamicEffectStateManager* GetEffectManager();

    NiDynamicEffectStateManager();
    virtual ~NiDynamicEffectStateManager();

    void AddDynamicEffectState(NiDynamicEffectStatePtr& spEffectState);
    bool RemoveDynamicEffectState(NiDynamicEffectState* pkEffectState);

    // Lock access to the effect state map
    void LockManager();

    // Unlock access to the effect state map
    void UnlockManager();

    class NIMAIN_ENTRY ListEntry : public NiMemObject
    {
    public:
        ListEntry* m_pkNext;
        NiDynamicEffectState* m_pkEffectState;
    };

    // *** end Emergent internal use only ***

protected:

    NiDynamicEffectState* CreateNewEffectState(NiDynamicEffectState* pkParentState,
        NiDynamicEffectList* pkEffectList);

    NiTPointerMap<NiUInt32, ListEntry*>* m_pkEffectStateMap;

    NiTObjectPool<ListEntry>* m_pkListEntryPool;

    // Critical section used to proctect access to the effect state map and
    // the entry pool. This critical section is locked:
    // -When an NiDynamiceEffected is added via AddDynamicEffectState()
    // -When an NiDynamiceEffected is removed via RemoveDynamicEffectState()
    // -When the EffectStateMap is resized via ResizeMap()
    efd::CriticalSection m_kEffectStateCriticalSection;

    static NiDynamicEffectStateManager* ms_pkDynamicEffectStateManager;
};

#include "NiDynamicEffectStateManager.inl"

#endif // NIDYNAMICEFFECTSTATEMANAGER_H