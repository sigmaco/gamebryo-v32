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

//-------------------------------------------------------------------------------------------------
inline const SystemDesc& SystemDesc::GetSystemDesc()
{
    EE_ASSERT(ms_SystemDesc != NULL);
    return *(ms_SystemDesc);
}
//-------------------------------------------------------------------------------------------------
inline efd::UInt32 SystemDesc::GetLogicalProcessorCount() const
{
    return m_NumLogicalProcessors;
}
//-------------------------------------------------------------------------------------------------
inline efd::UInt32 SystemDesc::GetPhysicalProcessorCount() const
{
    return m_NumPhysicalProcessors;
}
//-------------------------------------------------------------------------------------------------
inline  efd::UInt32 SystemDesc::GetPhysicalCoreCount() const
{
    return m_NumPhysicalCores;
}
//-------------------------------------------------------------------------------------------------
inline efd::Float32 SystemDesc::GetPerformanceCounterHz() const
{
    return m_PCCyclesPerSecond;
}
//-------------------------------------------------------------------------------------------------
inline bool SystemDesc::GetToolMode() const
{
    return m_InToolMode;
}
//-------------------------------------------------------------------------------------------------
inline void SystemDesc::SetToolMode(const bool InToolMode) const
{
    m_InToolMode = InToolMode;
}
//-------------------------------------------------------------------------------------------------
inline SystemDesc::RendererID SystemDesc::GetToolModeRendererID() const
{
    EE_ASSERT(m_InToolMode);
    return m_ToolModeRendererID;
}
//-------------------------------------------------------------------------------------------------
inline void SystemDesc::SetToolModeRendererID(
    const SystemDesc::RendererID eToolModeRendererID) const
{
    EE_ASSERT(m_InToolMode);
    m_ToolModeRendererID = eToolModeRendererID;
}
//-------------------------------------------------------------------------------------------------
#if defined(WIN32)
//-------------------------------------------------------------------------------------------------
inline bool SystemDesc::MMX_Supported(void) const
{
    return m_bMMX_Supported;
}
//-------------------------------------------------------------------------------------------------
inline bool SystemDesc::SSE_Supported(void) const
{
    return m_bSSE_Supported;
}
//-------------------------------------------------------------------------------------------------
inline bool SystemDesc::SSE2_Supported(void) const
{
    return m_bSSE2_Supported;
}
//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
