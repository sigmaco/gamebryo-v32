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
//  NiLines inline functions

#ifndef EE_REMOVE_BACK_COMPAT_STREAMING

//------------------------------------------------------------------------------------------------
inline NiBool* NiLines::GetFlags()
{
    NiLinesData* pkData = ((NiLinesData*)(m_spModelData.data()));
    return pkData->GetFlags();
}

//------------------------------------------------------------------------------------------------
inline const NiBool* NiLines::GetFlags() const
{
    NiLinesData* pkData = ((NiLinesData*)(m_spModelData.data()));
    return pkData->GetFlags();
}

//------------------------------------------------------------------------------------------------
#endif // #ifndef EE_REMOVE_BACK_COMPAT_STREAMING
