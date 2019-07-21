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
inline float NiPSRadialFieldForce::GetRadialFactor() const
{
    return m_kInputData.m_fRadialFactor;
}

//--------------------------------------------------------------------------------------------------
inline void NiPSRadialFieldForce::SetRadialFactor(float fRadialFactor)
{
    // Ensure that the range is acceptable.
    EE_ASSERT(fRadialFactor >= 0.0f && fRadialFactor <= 1.0f);

    fRadialFactor = NiMax(0.0f, fRadialFactor);
    fRadialFactor = NiMin(1.0f, fRadialFactor);

    m_kInputData.m_fRadialFactor = fRadialFactor;
}

//--------------------------------------------------------------------------------------------------
