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
inline void egmTerrain::ToDAnimationChangedMessage::SetAnimationStatus(bool status)
{
    m_animationRunning = status;
}

//--------------------------------------------------------------------------------------------------
inline bool egmTerrain::ToDAnimationChangedMessage::GetAnimationStatus() const
{
    return m_animationRunning;
}

//--------------------------------------------------------------------------------------------------
inline void egmTerrain::ToDAnimationChangedMessage::SetAnimationSpeedMultiplier(
    efd::UInt32 uiMultiplier)
{
    m_speedMultiplier = uiMultiplier;
}

//--------------------------------------------------------------------------------------------------
inline efd::UInt32 egmTerrain::ToDAnimationChangedMessage::GetAnimationSpeedMultiplier() const
{
    return m_speedMultiplier;
}

//--------------------------------------------------------------------------------------------------
inline void egmTerrain::ToDTimeChangedMessage::SetNewTime(float time)
{
    m_currentTime = time;
}

//--------------------------------------------------------------------------------------------------
inline float egmTerrain::ToDTimeChangedMessage::GetNewTime() const
{
    return m_currentTime;
}

//--------------------------------------------------------------------------------------------------
inline void egmTerrain::ToDKeyframesChangedMessage::SetPropertyName(efd::utf8string name)
{
    m_propertyName = name;
}

//--------------------------------------------------------------------------------------------------
inline efd::utf8string egmTerrain::ToDKeyframesChangedMessage::GetPropertyName() const
{
    return m_propertyName;
}

//--------------------------------------------------------------------------------------------------
inline void egmTerrain::ToDKeyframesChangedMessage::SetNumberOfKeyframes(efd::UInt32 num)
{
    m_numberOfKeyframes = num;
}

//--------------------------------------------------------------------------------------------------
inline efd::UInt32 egmTerrain::ToDKeyframesChangedMessage::GetNumberOfKeyframes() const
{
    return m_numberOfKeyframes;
}

//--------------------------------------------------------------------------------------------------
inline void egmTerrain::ToDKeyframesChangedMessage::AddKeyframe(float time, 
    efd::utf8string keyframeValue)
{
    m_keyframesTimes.push_back(time);
    m_keyframesValue.push_back(keyframeValue);
}

//--------------------------------------------------------------------------------------------------
inline void egmTerrain::ToDKeyframesChangedMessage::GetKeyframe(efd::UInt32 index, 
    float& time, efd::utf8string& keyframeValue) const
{
    time = m_keyframesTimes.at(index);
    keyframeValue = m_keyframesValue.at(index);
}

//--------------------------------------------------------------------------------------------------