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
inline float NiSceneGraphUpdateSettings::GetPlaybackStartTimeInSec() const
{
    return m_fPlaybackStartTimeInSec;
}

//--------------------------------------------------------------------------------------------------
inline void NiSceneGraphUpdateSettings::SetPlaybackStartTimeInSec(float fStartTime)
{
    m_fPlaybackStartTimeInSec = fStartTime;
}

//--------------------------------------------------------------------------------------------------
inline bool NiSceneGraphUpdateSettings::IsPlaybackStopTimeValid()
{
    return (m_fPlaybackStopTimeInSec >= 0.0f
        && m_fPlaybackStartTimeInSec <= m_fPlaybackStopTimeInSec);
}

//--------------------------------------------------------------------------------------------------
inline float NiSceneGraphUpdateSettings::GetPlaybackStopTimeInSec() const
{
    return m_fPlaybackStopTimeInSec;
}

//--------------------------------------------------------------------------------------------------
inline void NiSceneGraphUpdateSettings::SetPlaybackStopTimeInSec(float fStopTime)
{
    m_fPlaybackStopTimeInSec = fStopTime;
}

//--------------------------------------------------------------------------------------------------
inline NiSceneGraphUpdateSettings::PlaybackMode NiSceneGraphUpdateSettings::GetPlaybackMode() const
{
    return m_ePlaybackMode;
}

//--------------------------------------------------------------------------------------------------
inline void NiSceneGraphUpdateSettings::SetPlaybackMode(PlaybackMode ePlaybackMode)
{
    m_ePlaybackMode = ePlaybackMode;
}

//--------------------------------------------------------------------------------------------------
inline bool NiSceneGraphUpdateSettings::GetRestartPlaybackAfterEdit() const
{
    return (m_bRestartPlaybackAfterEdit != 0);
}

//--------------------------------------------------------------------------------------------------
inline void NiSceneGraphUpdateSettings::SetRestartPlaybackAfterEdit(bool bEnabled)
{
    m_bRestartPlaybackAfterEdit = bEnabled;
}

//--------------------------------------------------------------------------------------------------
inline bool NiSceneGraphUpdateSettings::GetSimulatePastEndTime() const
{
    return (m_bSimulatePastEndTime != 0);
}

//--------------------------------------------------------------------------------------------------
inline void NiSceneGraphUpdateSettings::SetSimulatePastEndTime(bool bEnabled)
{
    m_bSimulatePastEndTime = bEnabled;
}

//--------------------------------------------------------------------------------------------------
inline bool NiSceneGraphUpdateSettings::GetRunUpParticlesAfterEdit() const
{
    return (m_bRunUpParticlesAfterEdit != 0);
}

//--------------------------------------------------------------------------------------------------
inline void NiSceneGraphUpdateSettings::SetRunUpParticlesAfterEdit(bool bEnabled)
{
    m_bRunUpParticlesAfterEdit = bEnabled;
}

//--------------------------------------------------------------------------------------------------
inline bool NiSceneGraphUpdateSettings::GetAddDefaultLights() const
{
    return (m_bAddDefaultLights != 0);
}

//--------------------------------------------------------------------------------------------------
inline void NiSceneGraphUpdateSettings::SetAddDefaultLights(bool bEnabled)
{
    m_bAddDefaultLights = bEnabled;
}

//--------------------------------------------------------------------------------------------------
inline bool NiSceneGraphUpdateSettings::GetViewerHideUI() const
{
    return (m_bViewerHideUI != 0);
}

//--------------------------------------------------------------------------------------------------
inline void NiSceneGraphUpdateSettings::SetViewerHideUI(bool bEnabled)
{
    m_bViewerHideUI = bEnabled;
}

//--------------------------------------------------------------------------------------------------
