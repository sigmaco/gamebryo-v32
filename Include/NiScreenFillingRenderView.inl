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
inline NiScreenFillingRenderView* NiScreenFillingRenderView::Create()
{
    // make sure the create function implementation actually exists!
    EE_ASSERT(CreateFunc);
    return CreateFunc();
}

//--------------------------------------------------------------------------------------------------
inline void NiScreenFillingRenderView::AttachEffect(NiDynamicEffect* pkEffect)
{
    EE_ASSERT(pkEffect);

    // Ensure that the effect is not already in list.
    if (m_kEffectList.FindPos(pkEffect))
    {
        return;
    }

    m_kEffectList.AddHead(pkEffect);
    m_bEffectsChanged = true;
}

//--------------------------------------------------------------------------------------------------
inline void NiScreenFillingRenderView::DetachEffect(NiDynamicEffect* pkEffect)
{
    EE_ASSERT(pkEffect);

    // Ensure that the effect is already in the list.
    if (!m_kEffectList.FindPos(pkEffect))
    {
        return;
    }

    m_kEffectList.Remove(pkEffect);
    m_bEffectsChanged = true;
}

//--------------------------------------------------------------------------------------------------
inline void NiScreenFillingRenderView::DetachAllEffects()
{
    m_kEffectList.RemoveAll();
    m_bEffectsChanged = true;
}

//--------------------------------------------------------------------------------------------------
