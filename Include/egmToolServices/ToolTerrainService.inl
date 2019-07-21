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
inline void egmToolServices::ToolTerrainService::EnableAirbrushMode(efd::Bool isEnabled)
{
    if (!m_spTerrainEditGizmo)
        return;
    else
        m_spTerrainEditGizmo->EnableAirbrushMode(isEnabled);
}

//--------------------------------------------------------------------------------------------------
inline bool egmToolServices::ToolTerrainService::IsTerrainEditGizmoActive()
{
    GizmoService* pGizmoService = m_pServiceManager->GetSystemServiceAs<GizmoService>();
    return pGizmoService->GetActiveGizmo() == "TerrainEdit";
}

//--------------------------------------------------------------------------------------------------
inline void egmToolServices::ToolTerrainService::InvertBrushColor(efd::Bool invert)
{
    if (!m_spTerrainEditGizmo)
        return;
    else
        m_spTerrainEditGizmo->InvertBrushColor(invert);
}

//--------------------------------------------------------------------------------------------------