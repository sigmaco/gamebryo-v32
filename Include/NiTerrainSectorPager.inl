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
inline void NiTerrainSectorPager::AddReferenceObject(NiAVObject* pkRefObject)
{
    m_kReferenceObjects.Add(pkRefObject);
}

//--------------------------------------------------------------------------------------------------
inline const NiAVObject* NiTerrainSectorPager::GetCurrentReferenceObject() const
{
    if (m_uiCurrentRefObject >= m_kReferenceObjects.GetSize())
        return NULL;

    return m_kReferenceObjects.GetAt(m_uiCurrentRefObject);
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSectorPager::SetLoadDistance(float fLoadDistance)
{
    EE_ASSERT(fLoadDistance >= m_fMaxLODLoadDistance);
    m_fLoadDistance = fLoadDistance;
}

//--------------------------------------------------------------------------------------------------
inline float NiTerrainSectorPager::GetLoadDistance() const
{
    return m_fLoadDistance;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSectorPager::SetUnloadDistanceTolerance(float fUnloadDistance)
{
    m_fUnloadDistanceTolerance = fUnloadDistance;
}

//--------------------------------------------------------------------------------------------------
inline float NiTerrainSectorPager::GetUnloadDistanceTolerance() const
{
    return m_fUnloadDistanceTolerance;
}

//--------------------------------------------------------------------------------------------------
inline void NiTerrainSectorPager::SetMaxLODLoadDistance(float fLoadDistance)
{
    EE_ASSERT(fLoadDistance <= m_fLoadDistance);
    m_fMaxLODLoadDistance = fLoadDistance;
}

//--------------------------------------------------------------------------------------------------
inline float NiTerrainSectorPager::GetMaxLODLoadDistance() const
{
    return m_fMaxLODLoadDistance;
}

//--------------------------------------------------------------------------------------------------