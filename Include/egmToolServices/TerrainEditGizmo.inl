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
inline void egmToolServices::TerrainEditGizmo::SetGizmoMesh(NiNode* pObject)
{
    m_spGizmo->DetachChild(m_spGizmoMesh);
    m_spGizmo->AttachChild(pObject);
    m_spGizmoMesh = pObject;
}

//-------------------------------------------------------------------------------------------------
inline NiNode* egmToolServices::TerrainEditGizmo::GetGizmoMesh()
{
    return m_spGizmoMesh;
}

//-------------------------------------------------------------------------------------------------
inline void egmToolServices::TerrainEditGizmo::SetBrushRadius(efd::Float32 radius)
{
    m_brushRadius = radius;
}

//-------------------------------------------------------------------------------------------------
inline efd::Float32 egmToolServices::TerrainEditGizmo::GetBrushRadius() const
{
    return m_brushRadius;
}

//-------------------------------------------------------------------------------------------------
inline efd::Point3 egmToolServices::TerrainEditGizmo::GetLastIntersectionPt() const
{
    return efd::Point3(m_currIntersectionPt.x, m_currIntersectionPt.y, m_currIntersectionPt.z);
}

//-------------------------------------------------------------------------------------------------
inline void egmToolServices::TerrainEditGizmo::EnableAirbrushMode(efd::Bool isEnabled)
{
    m_isAirbrushModeEnabled = isEnabled;
}

//-------------------------------------------------------------------------------------------------
inline void egmToolServices::TerrainEditGizmo::GetLastRay(
    efd::Point3& rayOrigin, 
    efd::Point3& rayDirection)
{
    rayOrigin = m_lastRayOrigin;
    rayDirection = m_lastRayDirection;
}

//-------------------------------------------------------------------------------------------------
