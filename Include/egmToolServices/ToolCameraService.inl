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
inline bool egmToolServices::ToolCameraService::GetIsLooking() const
{
    return m_isLooking;
}
//--------------------------------------------------------------------------------------------------
inline bool egmToolServices::ToolCameraService::GetIsTranslating() const
{
    return m_isTranslating;
}
//--------------------------------------------------------------------------------------------------
inline bool egmToolServices::ToolCameraService::GetIsPanning() const
{
    return m_isPanning;
}
//--------------------------------------------------------------------------------------------------
inline bool egmToolServices::ToolCameraService::MovingForward() const
{
    return m_forward;
}
//--------------------------------------------------------------------------------------------------
inline bool egmToolServices::ToolCameraService::MovingBackward() const
{
    return m_backward;
}
//--------------------------------------------------------------------------------------------------
inline bool egmToolServices::ToolCameraService::MovingLeft() const
{
    return m_strafeLeft;
}
//--------------------------------------------------------------------------------------------------
inline bool egmToolServices::ToolCameraService::MovingRight() const
{
    return m_strafeRight;
}
//--------------------------------------------------------------------------------------------------
inline bool egmToolServices::ToolCameraService::MovingFast() const
{
    return m_shift;
}
//--------------------------------------------------------------------------------------------------
inline float egmToolServices::ToolCameraService::GetTurboScale() const
{
    return m_turboScale;
}
//--------------------------------------------------------------------------------------------------
inline void egmToolServices::ToolCameraService::SetTurboScale(float value)
{
    m_turboScale = value;
}
//--------------------------------------------------------------------------------------------------
inline float egmToolServices::ToolCameraService::GetKeyboardBaseMovement() const
{
    return m_keyboardBaseMovement;
}
//--------------------------------------------------------------------------------------------------
inline void egmToolServices::ToolCameraService::SetKeyboardBaseMovement(float value)
{
    m_keyboardBaseMovement = value;
}
//--------------------------------------------------------------------------------------------------
inline float egmToolServices::ToolCameraService::GetMouseBaseMovement() const
{
    return m_mouseBaseMovement;
}
//--------------------------------------------------------------------------------------------------
inline void egmToolServices::ToolCameraService::SetMouseBaseMovement(float value)
{
    m_mouseBaseMovement = value;
}
//--------------------------------------------------------------------------------------------------
inline float egmToolServices::ToolCameraService::GetMovementScale() const
{
    return m_spToolSceneGraphService->GetWorldScale() * m_movementScale;
}
//--------------------------------------------------------------------------------------------------
inline void egmToolServices::ToolCameraService::SetMovementScale(float value)
{
    m_movementScale = value;
}
//--------------------------------------------------------------------------------------------------
inline float egmToolServices::ToolCameraService::GetLookScale() const
{
    return m_lookScale;
}
//--------------------------------------------------------------------------------------------------
inline void egmToolServices::ToolCameraService::SetLookScale(float value)
{
    m_lookScale = value;
}
//--------------------------------------------------------------------------------------------------
inline bool egmToolServices::ToolCameraService::IsFlyingLevel() const
{
    return m_flyLevel;
}
//--------------------------------------------------------------------------------------------------
inline void egmToolServices::ToolCameraService::IsFlyingLevel(bool value)
{
    m_flyLevel = value;
}
//--------------------------------------------------------------------------------------------------
inline float egmToolServices::ToolCameraService::GetNearPlane() const
{
    return m_nearPlane;
}
//--------------------------------------------------------------------------------------------------
inline float egmToolServices::ToolCameraService::GetFarPlane() const
{
    return m_farPlane;
}
//--------------------------------------------------------------------------------------------------
