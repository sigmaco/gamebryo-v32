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
//  NiFloatsExtraData inline functions

//--------------------------------------------------------------------------------------------------
inline NiFloatsExtraData::NiFloatsExtraData()
{
    m_pfValue = NULL;
    m_uiSize = 0;
}

//--------------------------------------------------------------------------------------------------
inline NiFloatsExtraData::~NiFloatsExtraData()
{
    NiFree(m_pfValue);
    m_pfValue = NULL;
}

//--------------------------------------------------------------------------------------------------
inline void NiFloatsExtraData::GetArray(unsigned int &uiSize,
                                        float* &pfValue) const
{
    uiSize = m_uiSize;
    pfValue = m_pfValue;
}

//--------------------------------------------------------------------------------------------------
