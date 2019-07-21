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

//--------------------------------------------------------------------------------------------------
inline void NiVisualTracker::ShowGraph(bool bShow, unsigned int uiWhichGraph)
{
    EE_ASSERT(uiWhichGraph < m_callbackData.GetSize());
    m_callbackData.GetAt(uiWhichGraph)->SetShow(bShow);
}

//--------------------------------------------------------------------------------------------------
inline bool NiVisualTracker::GetGraphShow(unsigned int uiWhichGraph)
{
    EE_ASSERT(uiWhichGraph < m_callbackData.GetSize());
    return m_callbackData.GetAt(uiWhichGraph)->GetShow();
}

//--------------------------------------------------------------------------------------------------
inline NiVisualTracker::GraphCallbackObject::~GraphCallbackObject()
{
}

//--------------------------------------------------------------------------------------------------
inline NiVisualTracker::DataPointCallbackObject::~DataPointCallbackObject()
{
}

//--------------------------------------------------------------------------------------------------
inline bool NiVisualTracker::GraphCallbackObject::TakeSample(float fTime, float& fDataOut)
{
    fDataOut = TakeSample(fTime);
    return true;
}

//--------------------------------------------------------------------------------------------------
inline void NiVisualTracker::CallbackObjectData::ResetLastSampleTime()
{
    m_fLastTime = -NI_INFINITY;
}

//--------------------------------------------------------------------------------------------------
inline NiVisualTracker::LegendEntry* NiVisualTracker::CallbackObjectData::GetLegendEntry()
{
    return m_spLegendEntry;
}

//--------------------------------------------------------------------------------------------------
