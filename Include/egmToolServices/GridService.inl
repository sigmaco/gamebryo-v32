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
inline void egmToolServices::GridService::ToggleDisplayGrid()
{
    SetDisplayGrid(!m_displayGrid);
}
//--------------------------------------------------------------------------------------------------
inline bool egmToolServices::GridService::GetDisplayGrid()
{
    return m_displayGrid;
}
//--------------------------------------------------------------------------------------------------
inline void egmToolServices::GridService::SetDisplayGrid(bool flag)
{
    if (m_displayGrid != flag)
    {
        m_displayGrid = flag;
        RequestRebuildGrid();
    }
}
//--------------------------------------------------------------------------------------------------
inline void egmToolServices::GridService::SetMinorLineColor(const NiColor& color)
{
    if (m_minorLineColor != color)
    {
        m_minorLineColor = color;
        RequestRebuildGrid();
    }
}
//--------------------------------------------------------------------------------------------------
inline void egmToolServices::GridService::SetMajorLineColor(const NiColor& color)
{
    if (m_majorLineColor != color)
    {
        m_majorLineColor = color;
        RequestRebuildGrid();
    }
}
//--------------------------------------------------------------------------------------------------
inline void egmToolServices::GridService::SetMinorLineSpacing(float spacing)
{
    if (efd::Abs(spacing - m_minorLineSpacing) > 1e-06f) // safe float compare
    {
        m_minorLineSpacing = spacing;
        RequestRebuildGrid();
    }
}
//--------------------------------------------------------------------------------------------------
inline void egmToolServices::GridService::SetMajorLineSpacing(float spacing)
{
    if (efd::Abs(spacing - m_majorLineSpacing) > 1e-06f) // safe float compare
    {
        m_majorLineSpacing = spacing;
        RequestRebuildGrid();
    }
}
//--------------------------------------------------------------------------------------------------
inline void egmToolServices::GridService::SetExtents(float extents)
{
    if (efd::Abs(extents - m_extents) > 1e-06f) // safe float compare
    {
        m_extents = extents;
        RequestRebuildGrid();
    }
}
//--------------------------------------------------------------------------------------------------
inline float egmToolServices::GridService::GetVerticalInterval()
{
    return m_verticalInterval;
}
//--------------------------------------------------------------------------------------------------
inline void egmToolServices::GridService::SetVerticalInterval(float interval)
{
    m_verticalInterval = interval;
}
//--------------------------------------------------------------------------------------------------
inline bool egmToolServices::GridService::GetUseVerticalInterval()
{
    return m_useVerticalInterval;
}
//--------------------------------------------------------------------------------------------------
inline void egmToolServices::GridService::SetUseVerticalInterval(bool useInterval)
{
    m_useVerticalInterval = useInterval;
}
//--------------------------------------------------------------------------------------------------
