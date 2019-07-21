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
inline void GameStateService::AddState(T* state)
{
    EE_ASSERT(state);
    AddState(GameStatePtr(state), state->GetID());
}

//--------------------------------------------------------------------------------------------------
inline GameState* GameStateService::GetState() const
{
    return m_currentState;
}

//--------------------------------------------------------------------------------------------------
template <class T>
inline T* GameStateService::GetStateAs(efd::ClassID stateID)
{
    return EE_DYNAMIC_CAST(T, FindState(stateID));
}

//--------------------------------------------------------------------------------------------------
template <class T>
inline T* GameStateService::GetStateAs(const efd::utf8string& name)
{
    return EE_DYNAMIC_CAST(T, FindState(name));
}

//--------------------------------------------------------------------------------------------------
inline const efd::utf8string& GameStateService::GetDataPath() const
{
    return m_dataPath;
}

//--------------------------------------------------------------------------------------------------
inline void GameStateService::SetDataPath(const efd::utf8string& dataPath)
{
    m_dataPath = dataPath;
}

//--------------------------------------------------------------------------------------------------
}
