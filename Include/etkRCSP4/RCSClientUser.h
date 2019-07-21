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
#ifndef EE_RCSCLIENTUSER_H
#define EE_RCSCLIENTUSER_H

// Perforce SDK Headers
#include <p4/clientapi.h>
#include <p4/strtable.h>

namespace etk
{
class RCSClientUser : public ClientUser
{
public:
    RCSClientUser(RCSFeedback* pFeedback);
    virtual ~RCSClientUser();

	virtual void HandleError(Error* pP4Error);
	virtual void Message(Error *pP4Error);
	virtual void OutputError(const char* /*pMessage*/);
	virtual void OutputInfo(char /*level*/, const char* /*pMessage*/);
	virtual void OutputBinary( const char* /*data*/, int /*length*/);
	virtual void OutputText( const char* /*data*/, int /*length*/);
	virtual void Prompt(const StrPtr& promptMsg, StrBuf& rsp, int /*noEcho*/, Error* pP4Error);
	virtual void ErrorPause(char* /* errBuf */, Error* pP4Error);
    void ClearError();
    void CopyToResult(RCSResult &result);

    efd::utf8string m_promptResponse;

protected:
    void LogMessage(Error* pP4Error, const char* pMessage, ...);
    void ErrorToReason(Error *pP4Error);

    RCSFeedback* m_pFeedback;
    RCSResult::Reason m_errorReason;
    efd::utf8string m_errorMsg;
};

} // namespace etk

#endif // EE_RCSCLIENTUSER_H