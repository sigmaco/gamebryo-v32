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

namespace egmTerrain
{
//--------------------------------------------------------------------------------------------------
inline NiEnvironment* EnvironmentService::GetNiEnvironment()
{
    return m_spEnvironment;
}

//--------------------------------------------------------------------------------------------------
inline NiTimeOfDay* EnvironmentService::GetNiTimeOfDay()
{
    return m_spTimeOfDay;
}

//--------------------------------------------------------------------------------------------------
inline void EnvironmentService::RequestRedraw()
{
    m_requireRedraw = true;
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool EnvironmentService::RequiresRedraw()
{
    return m_requireRedraw;
}

//--------------------------------------------------------------------------------------------------
}// namespace