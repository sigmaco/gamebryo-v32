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

#include "NiParticlesData.h"

#ifndef EE_REMOVE_BACK_COMPAT_STREAMING

//------------------------------------------------------------------------------------------------
inline float* NiParticles::GetRadii()
{
    return ((NiParticlesData*)(m_spModelData.data()))->GetRadii();
}

//------------------------------------------------------------------------------------------------
inline float* NiParticles::GetSizes()
{
    return ((NiParticlesData*)(m_spModelData.data()))->GetSizes();
}

//------------------------------------------------------------------------------------------------
inline NiQuaternion* NiParticles::GetRotations()
{
    return ((NiParticlesData*)(m_spModelData.data()))->GetRotations();
}

//------------------------------------------------------------------------------------------------
#endif // #ifndef EE_REMOVE_BACK_COMPAT_STREAMING
