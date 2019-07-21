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

namespace egmSample
{

//--------------------------------------------------------------------------------------------------
template <class T>
inline T* GameState::Context()
{
    EE_ASSERT(m_pMasterService);
    return EE_DYNAMIC_CAST(T, m_pMasterService);
}

//--------------------------------------------------------------------------------------------------
template <class T>
inline T* GameState::Context() const
{
    EE_ASSERT(m_pMasterService);
    return EE_DYNAMIC_CAST(T, m_pMasterService);
}

//--------------------------------------------------------------------------------------------------
inline GameStateService* GameState::Context()
{
    EE_ASSERT(m_pMasterService);
    return m_pMasterService;
}

//--------------------------------------------------------------------------------------------------
inline GameStateService* GameState::Context() const
{
    EE_ASSERT(m_pMasterService);
    return m_pMasterService;
}

//--------------------------------------------------------------------------------------------------
inline void GameState::SetActions(efd::UInt32 actions)
{
    m_actions = actions;
}

//--------------------------------------------------------------------------------------------------
inline efd::UInt32 GameState::GetActions() const
{
    return m_actions;
}

//--------------------------------------------------------------------------------------------------
inline void GameState::SetTimeout(efd::TimeType timeout)
{
    m_timeout = timeout;
}

//--------------------------------------------------------------------------------------------------
inline efd::TimeType GameState::GetTimeout() const
{
    return m_timeout;
}

//--------------------------------------------------------------------------------------------------
inline void GameState::SetNextStateID(GameStateID nextStateID)
{
    m_nextStateID = nextStateID;
}

//--------------------------------------------------------------------------------------------------
inline GameStateID GameState::GetNextStateID() const
{
    return m_nextStateID;
}

//--------------------------------------------------------------------------------------------------
inline void GameState::SetDisplayTexture(const char *displayTexture)
{
    m_pDisplayTexture = displayTexture;
}

//--------------------------------------------------------------------------------------------------
inline const char *GameState::GetDisplayTexture() const
{
    return m_pDisplayTexture;
}

//--------------------------------------------------------------------------------------------------
} // end namespace egmSample
