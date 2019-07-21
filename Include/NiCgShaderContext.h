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

#ifndef NICGSHADERCONTEXT_H
#define NICGSHADERCONTEXT_H

#include "NiCgShaderLibType.h"
#include "NiCgHeaders.h"

class NICGSHADERLIB_ENTRY NiCgShaderContext
{
public:
    static CGcontext GetCgContext();

    static void _SDMInit();
    static void _SDMShutdown();

protected:
    static CGcontext ms_kContext;
    static unsigned int ms_uiRefCount;
};

#endif  //#ifndef NICGSHADERCONTEXT_H
