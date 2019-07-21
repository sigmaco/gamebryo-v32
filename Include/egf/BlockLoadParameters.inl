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

//------------------------------------------------------------------------------------------------
namespace egf
{

//------------------------------------------------------------------------------------------------
inline void BlockLoadParameters::SetAutoEnterWorld(bool autoEnter)
{
    m_bits.autoEnterWorld = autoEnter;
}

//------------------------------------------------------------------------------------------------
inline bool BlockLoadParameters::GetDefaultAutoEnterWorld()
{
    return ms_defaultAutoEnterWorld;
}

//------------------------------------------------------------------------------------------------
inline bool BlockLoadParameters::GetAutoEnterWorld() const
{
    return m_bits.autoEnterWorld;
}

//------------------------------------------------------------------------------------------------
inline const efd::Category& BlockLoadParameters::GetNotificationCategory() const
{
    return m_notificationCategory;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 BlockLoadParameters::GetNotificationContext() const
{
    return m_notificationContext;
}

//------------------------------------------------------------------------------------------------
inline egf::BehaviorID BlockLoadParameters::GetNotificationBehavior() const
{
    return m_notificationBehavior;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 BlockLoadParameters::GetActiveCallbacks() const
{
    // If no callback is provided then don't generate any result messages for this load
    if (m_notificationCategory.IsValid())
        return m_callbacks;
    return 0;
}

//------------------------------------------------------------------------------------------------
inline bool BlockLoadParameters::UseRotation() const
{
    return m_bits.rotationSet;
}

//------------------------------------------------------------------------------------------------
inline const efd::Point3& BlockLoadParameters::GetRotation() const
{
    return m_rotation;
}

//------------------------------------------------------------------------------------------------
inline bool BlockLoadParameters::UseOffset() const
{
    return m_bits.offsetSet;
}

//------------------------------------------------------------------------------------------------
inline const efd::Point3& BlockLoadParameters::GetOffset() const
{
    return m_offset;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 BlockLoadParameters::GetLoadThresholdOverride() const
{
    return m_loadThrottleOverride;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 BlockLoadParameters::GetUnloadThresholdOverride() const
{
    return m_unloadThrottleOverride;
}

//------------------------------------------------------------------------------------------------
} // end namespace egf
