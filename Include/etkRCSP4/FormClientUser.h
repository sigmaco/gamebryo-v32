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
#ifndef EE_FORMCLIENTUSER_H
#define EE_FORMCLIENTUSER_H

#include "RCSClientUser.h"

namespace etk
{
class FormClientUser : public RCSClientUser
{
public:
    FormClientUser(RCSFeedback* pFeedback);
    virtual ~FormClientUser();

    virtual void Edit(FileSys *f1, Error *e);
    efd::map<efd::utf8string, efd::utf8string> m_fields;
};
} // namespace etk

#endif // EE_FORMCLIENTUSER_H