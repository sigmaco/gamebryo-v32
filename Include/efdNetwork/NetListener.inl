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

//--------------------------------------------------------------------------------------------------
inline NetListener::NetListener(const ConnectionID& remoteConnectionID, INetCallback* callback)
: m_remoteConnectionID(remoteConnectionID)
, m_pCallback(callback)
{
}

//--------------------------------------------------------------------------------------------------
inline NetListener::~NetListener()
{
}

//--------------------------------------------------------------------------------------------------
inline const efd::ConnectionID& NetListener::GetRemoteConnectionID()
{
    return m_remoteConnectionID;
}

//--------------------------------------------------------------------------------------------------
inline efd::INetCallback* NetListener::GetCallback()
{
    return m_pCallback;
}

} // end namespace efd
