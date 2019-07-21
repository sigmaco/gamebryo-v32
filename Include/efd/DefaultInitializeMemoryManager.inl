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
efd::IAllocator* efd::CreateDefaultGlobalMemoryAllocator(bool silentPremainAllocations)
{
    efd::IAllocator* pkAllocator = NULL;

#ifdef EE_MEMORY_DEBUGGER
    pkAllocator = EE_EXTERNAL_NEW efd::MemTracker(
        EE_EXTERNAL_NEW efd::StandardAllocator(),
        true,  // writeToLog
        65536, // initial size
        4096,  // grow by
        false, // always validate all
        true,  // check for array overruns
        !silentPremainAllocations); // assert outside of the begin/end of main
#else
    (void)silentPremainAllocations;

    pkAllocator = EE_EXTERNAL_NEW efd::StandardAllocator();
#endif

    return pkAllocator;
}
//-------------------------------------------------------------------------------------------------
