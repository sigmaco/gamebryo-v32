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
#ifndef EE_FSTATCLIENTUSER_H
#define EE_FSTATCLIENTUSER_H

#include "RCSClientUser.h"

namespace etk
{
class FstatClientUser : public RCSClientUser
{
public:
    FstatClientUser(RCSFeedback* pFeedback, RCSStatus& status);
    virtual ~FstatClientUser();

    virtual void OutputStat(StrDict* varList);
    FstatClientUser & operator=( const FstatClientUser& rhs );

protected:
    RCSStatus& m_status;
};
} // namespace etk

#endif // EE_FSTATCLIENTUSER_H