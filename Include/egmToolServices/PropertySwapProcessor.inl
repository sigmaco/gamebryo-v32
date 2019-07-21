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
inline egmToolServices::PropertySwapProcessor::PropertySwapProcessor(
    NiPropertyList* pkPropertyList) : m_pkPropertyList(pkPropertyList)
{
}
//--------------------------------------------------------------------------------------------------
inline void egmToolServices::PropertySwapProcessor::SetPropertyList(NiPropertyList* pkPropertyList)
{
    m_pkPropertyList = pkPropertyList;
}
//--------------------------------------------------------------------------------------------------
inline NiPropertyList* egmToolServices::PropertySwapProcessor::GetPropertyList() const
{
    return m_pkPropertyList;
}
//--------------------------------------------------------------------------------------------------
