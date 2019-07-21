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
template< typename T >
inline T* egmToolServices::GizmoService::GetPolicy() const
{
    GizmoPolicyPtr spPolicy;
    if (m_policies.find(T::CLASS_ID, spPolicy))
        return (T*)static_cast<GizmoPolicy*>(spPolicy);

    return NULL;
}

//------------------------------------------------------------------------------------------------
inline egmToolServices::GizmoService::RelativeSpace egmToolServices::GizmoService::GetRelativeSpace() const
{
    return m_currentSpace;
}

//------------------------------------------------------------------------------------------------
inline void egmToolServices::GizmoService::SetRelativeSpace(egmToolServices::GizmoService::RelativeSpace space)
{
    m_currentSpace = space;

    m_pRenderService->InvalidateRenderContexts();
}

//------------------------------------------------------------------------------------------------
inline bool egmToolServices::GizmoService::TranslationPrecisionEnabled() const
{
    return m_translationPrecisionEnabled;
}

//------------------------------------------------------------------------------------------------
inline void egmToolServices::GizmoService::SetTranslationPrecisionEnabled(bool flag)
{
    m_translationPrecisionEnabled = flag;
}

//------------------------------------------------------------------------------------------------
inline double egmToolServices::GizmoService::TranslationPrecision() const
{
    return m_translationPrecision;
}

//------------------------------------------------------------------------------------------------
inline void egmToolServices::GizmoService::SetTranslationPrecision(double precision)
{
    m_translationPrecision = precision;
}

//------------------------------------------------------------------------------------------------
inline bool egmToolServices::GizmoService::ScalePrecisionEnabled() const
{
    return m_scalePrecisionEnabled;
}

//------------------------------------------------------------------------------------------------
inline void egmToolServices::GizmoService::SetScalePrecisionEnabled(bool flag)
{
    m_scalePrecisionEnabled = flag;
}

//------------------------------------------------------------------------------------------------
inline double egmToolServices::GizmoService::ScalePrecision() const
{
    return m_scalePrecision;
}

//------------------------------------------------------------------------------------------------
inline void egmToolServices::GizmoService::SetScalePrecision(double precision)
{
    m_scalePrecision = precision;
}

//------------------------------------------------------------------------------------------------
inline bool egmToolServices::GizmoService::TranslationSnapEnabled() const
{
    return m_translationSnapEnabled;
}

//------------------------------------------------------------------------------------------------
inline void egmToolServices::GizmoService::SetTranslationSnapEnabled(bool flag)
{
    m_translationSnapEnabled = flag;
}

//------------------------------------------------------------------------------------------------
inline double egmToolServices::GizmoService::TranslationSnap() const
{
    return m_translationSnap;
}

//------------------------------------------------------------------------------------------------
inline void egmToolServices::GizmoService::SetTranslationSnap(double snap)
{
    m_translationSnap = snap;
}

//------------------------------------------------------------------------------------------------
inline bool egmToolServices::GizmoService::RotationSnapEnabled() const
{
    return m_rotationSnapEnabled;
}

//------------------------------------------------------------------------------------------------
inline void egmToolServices::GizmoService::SetRotationSnapEnabled(bool flag)
{
    m_rotationSnapEnabled = flag;
}

//------------------------------------------------------------------------------------------------
inline double egmToolServices::GizmoService::RotationSnap() const
{
    return m_rotationSnap;
}

//------------------------------------------------------------------------------------------------
inline void egmToolServices::GizmoService::SetRotationSnap(double snap)
{
    m_rotationSnap = snap;
}

//------------------------------------------------------------------------------------------------
inline bool egmToolServices::GizmoService::ScaleSnapEnabled() const
{
    return m_scaleSnapEnabled;
}

//------------------------------------------------------------------------------------------------
inline void egmToolServices::GizmoService::SetScaleSnapEnabled(bool flag)
{
    m_scaleSnapEnabled = flag;
}

//------------------------------------------------------------------------------------------------
inline double egmToolServices::GizmoService::ScaleSnap() const
{
    return m_scaleSnap;
}

//------------------------------------------------------------------------------------------------
inline void egmToolServices::GizmoService::SetScaleSnap(double snap)
{
    m_scaleSnap = snap;
}

//------------------------------------------------------------------------------------------------
inline egmToolServices::GizmoService::PlacementMode egmToolServices::GizmoService::GetPlacementMode() const
{
    return m_placementMode;
}

//------------------------------------------------------------------------------------------------
inline void egmToolServices::GizmoService::SetPlacementMode(GizmoService::PlacementMode mode)
{
    m_placementMode = mode;
}

//-----------------------------------------------------------------------------------------------
inline void egmToolServices::GizmoService::RoundToIncrement(efd::Point3& value, double increment)
{
    RoundToIncrement(value.x, increment);
    RoundToIncrement(value.y, increment);
    RoundToIncrement(value.z, increment);
}

//-----------------------------------------------------------------------------------------------
inline void egmToolServices::GizmoService::RoundToIncrement(float& value, double increment)
{
    double dVal = (double)value / increment + 0.5;
    dVal = efd::Floor((float)dVal) * increment;
    value = (float)dVal;
}