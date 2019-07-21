
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

namespace efd
{

//-------------------------------------------------------------------------------------------------
inline efd::SInt32 NetErrorMessage::GetNetError() const
{
    return m_netErr;
}
//-------------------------------------------------------------------------------------------------
inline void NetErrorMessage::SetNetError(efd::SInt32 err)
{
    m_netErr = err;
}
//-------------------------------------------------------------------------------------------------
inline const efd::utf8string& NetErrorMessage::GetNetErrorString() const
{
    return m_netErrString;
}
//-------------------------------------------------------------------------------------------------
inline void NetErrorMessage::SetNetErrorString(const efd::utf8string& errString)
{
    m_netErrString.assign(errString);
}
//-------------------------------------------------------------------------------------------------
inline void NetErrorMessage::SetNetErrorString(const char *errString)
{
    m_netErrString.assign(errString);
}
//-------------------------------------------------------------------------------------------------
inline efd::UInt32 NetErrorMessage::GetSystemError() const
{
    return m_sysErr;
}
//-------------------------------------------------------------------------------------------------
inline void NetErrorMessage::SetSystemError(efd::UInt32 err)
{
    m_sysErr = err;
}
//-------------------------------------------------------------------------------------------------
inline const efd::utf8string& NetErrorMessage::GetSystemErrorString() const
{
    return m_sysErrString;
}
//-------------------------------------------------------------------------------------------------
inline void NetErrorMessage::SetSystemErrorString(const efd::utf8string& errString)
{
    m_sysErrString.assign(errString);
}
//-------------------------------------------------------------------------------------------------
inline void NetErrorMessage::SetSystemErrorString(const char *errString)
{
    m_sysErrString.assign(errString);
}

} //end namespace efd

