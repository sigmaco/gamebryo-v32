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
RCSFeedback::ErrorAction RCSProvider::HandleError(RCSResult& result)
{
    if (m_pFeedback)
    {
        switch (m_pFeedback->HandleError(result))
        {
        case RCSFeedback::RCS_ERR_ACTION_IGNORE:
            result.SetFailed(RCSResult::RCS_USER_IGNORE);
            return RCSFeedback::RCS_ERR_ACTION_IGNORE;
        case RCSFeedback::RCS_ERR_ACTION_RETRY:
            return RCSFeedback::RCS_ERR_ACTION_RETRY;
        }
    }

    result.SetFailed(RCSResult::RCS_USER_CANCEL);
    return RCSFeedback::RCS_ERR_ACTION_ABORT;
}
//--------------------------------------------------------------------------------------------------
void RCSProvider::LogMessage(RCSFeedback::MessageSeverity severity, const char* pFormat, ...)
{
    if (m_pFeedback)
    {
        va_list kArgs;
        va_start(kArgs, pFormat);
        m_pFeedback->VLogMessage(severity, pFormat, kArgs);
        va_end(kArgs); 
    }
}
//--------------------------------------------------------------------------------------------------
void RCSProvider::SetChangelist(const efd::utf8string& changelistName)
{
    m_changelistName = changelistName;
}
//--------------------------------------------------------------------------------------------------
void RCSProvider::SetFeedback(RCSFeedback* pFeedback)
{
    m_pFeedback = pFeedback;
}
//--------------------------------------------------------------------------------------------------
const RCSFeedback* RCSProvider::GetFeedback() const
{
    return m_pFeedback;
}
//--------------------------------------------------------------------------------------------------
const efd::utf8string& RCSProvider::GetChangelist() const
{
    return m_changelistName;
}
//--------------------------------------------------------------------------------------------------
void RCSProvider::Cancel()
{
    m_cancel = true;
}
//--------------------------------------------------------------------------------------------------
bool RCSProvider::IsCancelled()
{
    return m_cancel;
}
//--------------------------------------------------------------------------------------------------
void RCSProvider::ResetCancel()
{
    m_cancel = false;
}
//--------------------------------------------------------------------------------------------------

} // namespace etk