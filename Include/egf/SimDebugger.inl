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

namespace egf
{

//-------------------------------------------------------------------------------------------------
inline SimDebugger* SimDebugger::Instance()
{
    return ms_spInstance;
}

//-------------------------------------------------------------------------------------------------
inline void SimDebugger::SetInstance(SimDebugger* pInstance)
{
    EE_ASSERT(ms_spInstance == NULL);

    ms_spInstance = pInstance;
}

//-------------------------------------------------------------------------------------------------
inline void SimDebugger::Release()
{
    EE_ASSERT(ms_spInstance != NULL);

    ms_spInstance = NULL;
}

}
