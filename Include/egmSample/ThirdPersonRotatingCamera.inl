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

namespace egmSample
{

//--------------------------------------------------------------------------------------------------
inline efd::Float32 ThirdPersonRotatingCamera::GetSubjectCameraFocusHeightAdjust(
    efd::Float32 defaultValue) const
{
    efd::Float32 value = defaultValue;
    if (m_spSubjectEntity)
    {
        m_spSubjectEntity->GetPropertyValue(
            egf::kPropertyID_SamplesModelLibrary_CameraFocusHeightAdjust,
            value);
    }
    return value;
}

//--------------------------------------------------------------------------------------------------
inline efd::Float32 ThirdPersonRotatingCamera::GetSubjectCameraFocusHorizAdjust(
    efd::Float32 defaultValue) const
{
    efd::Float32 value = defaultValue;
    if (m_spSubjectEntity)
    {
        m_spSubjectEntity->GetPropertyValue(
            egf::kPropertyID_SamplesModelLibrary_CameraFocusHorizAdjust,
            value);
    }
    return value;
}

//--------------------------------------------------------------------------------------------------
inline efd::Float32 ThirdPersonRotatingCamera::GetSubjectCameraStopHeightAdjust(
    efd::Float32 defaultValue) const
{
    efd::Float32 value = defaultValue;
    if (m_spSubjectEntity)
    {
        m_spSubjectEntity->GetPropertyValue(
            egf::kPropertyID_SamplesModelLibrary_CameraStopHeightAdjust,
            value);
    }
    return value;
}

//--------------------------------------------------------------------------------------------------
inline efd::Float32 ThirdPersonRotatingCamera::GetSubjectCameraStopOffsetAdjust(
    efd::Float32 defaultValue) const
{
    efd::Float32 value = defaultValue;
    if (m_spSubjectEntity)
    {
        m_spSubjectEntity->GetPropertyValue(
            egf::kPropertyID_SamplesModelLibrary_CameraStopOffsetAdjust,
            value);
    }
    return value;
}

//--------------------------------------------------------------------------------------------------
inline efd::Float32 ThirdPersonRotatingCamera::ApplyCurveFilter(efd::Float32 input) const
{
    efd::Float32 result = 0.0f;
    result = 1.0f - efd::Cos(input * NI_HALF_PI);
    if (input < 0)
    {
        result = -result;
    }
    return result;
}

//--------------------------------------------------------------------------------------------------
}
