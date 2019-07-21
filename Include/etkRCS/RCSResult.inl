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

namespace etk
{

//--------------------------------------------------------------------------------------------------
bool RCSResult::Succeeded()
{
    return !m_failed;
}
//--------------------------------------------------------------------------------------------------
bool RCSResult::Failed()
{
    return m_failed;
}
//--------------------------------------------------------------------------------------------------
bool RCSResult::Cancelled()
{
    return (m_reason == RCS_USER_CANCEL);
}
//--------------------------------------------------------------------------------------------------
void RCSResult::SetFailed(Reason reason)
{
    m_failed = (reason != RCS_NO_ERROR); 
    m_reason = reason;
}
//--------------------------------------------------------------------------------------------------
void RCSResult::SetSucceeded()
{
    m_failed = false;
    m_reason = RCS_NO_ERROR;
}
//--------------------------------------------------------------------------------------------------
RCSResult::Reason RCSResult::GetReason()
{
    return m_reason;
}
//--------------------------------------------------------------------------------------------------
efd::utf8string& RCSResult::GetAction()
{
    return m_action;
}
//--------------------------------------------------------------------------------------------------
void RCSResult::SetAction(const char* pAction)
{
    m_action = pAction;
}
//--------------------------------------------------------------------------------------------------
void RCSResult::SetHideCommand(bool hideCommand)
{
    m_hideCommand = hideCommand;
}
//--------------------------------------------------------------------------------------------------
efd::utf8string& RCSResult::GetCommand()
{
    return m_command;
}
//--------------------------------------------------------------------------------------------------
void RCSResult::SetCommand(const char* pCommand)
{
    m_command = pCommand;
}
//--------------------------------------------------------------------------------------------------
efd::utf8string& RCSResult::GetResponse()
{
    return m_response;
}
//--------------------------------------------------------------------------------------------------
void RCSResult::SetHelpMessage(const char* pHelp)
{
    m_help = pHelp;
}
//--------------------------------------------------------------------------------------------------
efd::utf8string& RCSResult::GetHelpMessage()
{
    return m_help;
}
//--------------------------------------------------------------------------------------------------
void RCSResult::SetResponseMessage(const char* pResponse)
{
    m_response = pResponse;
}
//--------------------------------------------------------------------------------------------------

} // end namespace etk
