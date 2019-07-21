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
// Emergent Game Technologies, Chapel Hill, North Carolina 27517
// http://www.emergent.net

#pragma once
#ifndef EE_FINDCHANGELISTCLIENTUSER_H
#define EE_FINDCHANGELISTCLIENTUSER_H

#include "RCSClientUser.h"

namespace etk
{
class FindChangelistClientUser : public RCSClientUser
{
public:
    FindChangelistClientUser(RCSFeedback* pFeedback, efd::utf8string& changelistDesc);
    virtual ~FindChangelistClientUser();

    virtual void OutputStat(StrDict* varList);

    efd::utf8string m_changelistDesc;
    efd::utf8string m_changelistID;
}; 
} // namespace etk

#endif // EE_FINDCHANGELISTCLIENTUSER_H