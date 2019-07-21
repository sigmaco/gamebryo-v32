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
inline void NetMetricsDestination::BeginLog(
        efd::Bool assert,
        const char* timeStampMachine,
        efd::TimeType timeStampGame,
        const char* pModule,
        const char* pLevel,
        const char* pFile,
        efd::SInt32 line)
{
    EE_UNUSED_ARG(assert);
    EE_UNUSED_ARG(timeStampMachine);
    EE_UNUSED_ARG(timeStampGame);
    EE_UNUSED_ARG(pModule);
    EE_UNUSED_ARG(pLevel);
    EE_UNUSED_ARG(pFile);
    EE_UNUSED_ARG(line);

    EE_FAIL("BeginLog is not supported by the net metrics log destination");
}

//------------------------------------------------------------------------------------------------
inline void NetMetricsDestination::ContinueLog(const char* pMsg)
{
    EE_UNUSED_ARG(pMsg);

    EE_FAIL("ContinueLog is not supported by the net metrics log destination");
}

//------------------------------------------------------------------------------------------------
inline void NetMetricsDestination::EndLog()
{
    EE_FAIL("EndLog is not supported by the net metrics log destination");
}

//------------------------------------------------------------------------------------------------
inline void NetMetricsDestination::Flush()
{
    // Flush is a no-op for this destination type
}

