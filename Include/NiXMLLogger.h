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

#pragma once
#ifndef NIXMLLOGGER_H
#define NIXMLLOGGER_H

#include "NiPluginToolkitLibType.h"
#include <NiString.h>

class NIPLUGINTOOLKIT_ENTRY NiXMLLogger
{
public:
    NiXMLLogger();
    ~NiXMLLogger(void);

    bool CreateLog(const NiString& kFilename);
    bool CloseLog();
    bool LogElement(const NiString& kElementName, const NiString& kData);
    bool LogData(const NiString& kData);
    bool StartElement(const NiString& kElementName);
    bool EndElement(const NiString& kElementName);

protected:
    void AddTabs(NiString& kString, bool bPrepend = true);

    FILE* m_pFileHandle;
    NiUInt32 m_uiTabDepth;
};

#endif NIXMLLOGGER_H