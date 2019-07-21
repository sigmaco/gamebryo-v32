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
// Constructors
//-------------------------------------------------------------------------------------------------
inline ecrInput::InputServiceStick::InputServiceStick() :
    m_stickType(ecrInput::InputService::INVALID_STICK),
    m_axisSemanticX(0),
    m_axisSemanticY(0),
    m_axisSemanticZ(0),
    m_axisControlX(0),
    m_axisControlY(0),
    m_axisControlZ(0),
    m_minRangeX(0.0f),
    m_maxRangeX(0.0f),
    m_minRangeY(0.0f),
    m_maxRangeY(0.0f),
    m_minRangeZ(0.0f),
    m_maxRangeZ(0.0f),
    m_pFilter(0)
{
}
//-------------------------------------------------------------------------------------------------
inline ecrInput::InputServiceStick::InputServiceStick(
    ecrInput::InputService::StickType stickType,
    efd::UInt32 flags,
    efd::UInt32 appData,
    efd::UInt32 deviceID,
    efd::UInt32 modifiers,
    efd::Float32 minRangeX,
    efd::Float32 maxRangeX,
    efd::Float32 minRangeY,
    efd::Float32 maxRangeY,
    efd::Float32 minRangeZ,
    efd::Float32 maxRangeZ,
    ecrInput::InputService::InputFilteringCallback pFilter,
    efd::UInt32 axisSemanticX,
    efd::UInt32 axisSemanticY,
    efd::UInt32 axisSemanticZ) :
    ecrInput::InputServiceActionBase(flags, appData, deviceID, modifiers),
    m_minRangeX(minRangeX),
    m_maxRangeX(maxRangeX),
    m_minRangeY(minRangeY),
    m_maxRangeY(maxRangeY),
    m_minRangeZ(minRangeZ),
    m_maxRangeZ(maxRangeZ),
    m_pFilter(pFilter)
{
    SetType(stickType);
    SetCustomSemantic(axisSemanticX, axisSemanticY, axisSemanticZ);
}
//-------------------------------------------------------------------------------------------------
// Data accessors - querying
//-------------------------------------------------------------------------------------------------
inline ecrInput::InputService::StickType ecrInput::InputServiceStick::GetType() const
{
    return m_stickType;
}
//-------------------------------------------------------------------------------------------------
inline void ecrInput::InputServiceStick::GetCustomSemantic(
    efd::UInt32& axisSemanticX,
    efd::UInt32& axisSemanticY,
    efd::UInt32& axisSemanticZ) const
{
    axisSemanticX = m_axisSemanticX;
    axisSemanticY = m_axisSemanticY;
    axisSemanticZ = m_axisSemanticZ;
}
//-------------------------------------------------------------------------------------------------
inline void ecrInput::InputServiceStick::GetRange(
    efd::Float32& xMin,
    efd::Float32& xMax,
    efd::Float32& yMin,
    efd::Float32& yMax,
    efd::Float32& zMin,
    efd::Float32& zMax) const
{
    xMin = m_minRangeX;
    xMax = m_maxRangeX;
    yMin = m_minRangeY;
    yMax = m_maxRangeY;
    zMin = m_minRangeZ;
    zMax = m_maxRangeZ;
}
//-------------------------------------------------------------------------------------------------
// Data accessors - setting
//-------------------------------------------------------------------------------------------------
inline void ecrInput::InputServiceStick::SetType(ecrInput::InputService::StickType stickType)
{
    m_stickType = stickType;
}
//-------------------------------------------------------------------------------------------------
inline void ecrInput::InputServiceStick::SetCustomSemantic(
    efd::UInt32 axisSemanticX,
    efd::UInt32 axisSemanticY,
    efd::UInt32 axisSemanticZ)
{
    m_axisSemanticX = axisSemanticX;
    m_axisSemanticY = axisSemanticY;
    m_axisSemanticZ = axisSemanticZ;

    m_axisControlX = NiAction::SemanticToDeviceControl(m_axisSemanticX);
    m_axisControlY = NiAction::SemanticToDeviceControl(m_axisSemanticY);
    m_axisControlZ = NiAction::SemanticToDeviceControl(m_axisSemanticZ);
}
//-------------------------------------------------------------------------------------------------
inline void ecrInput::InputServiceStick::SetRange(
    efd::Float32 xMin,
    efd::Float32 xMax,
    efd::Float32 yMin,
    efd::Float32 yMax,
    efd::Float32 zMin,
    efd::Float32 zMax)
{
    m_minRangeX = xMin;
    m_maxRangeX = xMax;
    m_minRangeY = yMin;
    m_maxRangeY = yMax;
    m_minRangeZ = zMin;
    m_maxRangeZ = zMax;
}
//-------------------------------------------------------------------------------------------------