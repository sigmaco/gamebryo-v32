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
inline NiPick* ecr::PickService::GetPickObject() const
{
    return m_pPicker;
}
//--------------------------------------------------------------------------------------------------
inline ecr::PickService::PickRecord::PickRecord(
    const efd::Point3& origin,
    const efd::Point3& direction)
    : m_rayOrigin(origin)
    , m_rayDirection(direction)
    , m_pResults(NULL)
{
}
//--------------------------------------------------------------------------------------------------
inline const efd::Point3& ecr::PickService::PickRecord::GetRayOrigin() const
{
    return m_rayOrigin;
}
//--------------------------------------------------------------------------------------------------
inline const efd::Point3& ecr::PickService::PickRecord::GetRayDirection() const
{
    return m_rayDirection;
}
//--------------------------------------------------------------------------------------------------
inline const NiPick::Results* ecr::PickService::PickRecord::GetPickResult() const
{
    return m_pResults;
}
//--------------------------------------------------------------------------------------------------
