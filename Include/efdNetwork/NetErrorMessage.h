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
// Emergent Game Technologies, Calabasas, California 91302
// http://www.emergent.net

#pragma once
#ifndef NET_ERROR_MESSAGE_H
#define NET_ERROR_MESSAGE_H

#include <efd/NetMessage.h>
#include <efdNetwork/efdNetworkLibType.h>

namespace efd
{

const static Category kCAT_NetErrorMessage( 
    UniversalID::ECU_Any, 
    kNetID_Any, 
    kMSGID_NetErrorMessage);

class EE_EFDNETWORK_ENTRY NetErrorMessage : public efd::NetMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(NetErrorMessage, efd::kMSGID_NetErrorMessage, efd::NetMessage);
    /// @endcond

public:

    NetErrorMessage();
    NetErrorMessage(const ConnectionID& cid, efd::UInt32 senderNetID);

    virtual ~NetErrorMessage();

    // convert this class into a stream of atomic types.
    virtual void Serialize(efd::Archive& ar);

    efd::SInt32 GetNetError() const;
    void SetNetError(efd::SInt32 err);

    const efd::utf8string& GetNetErrorString() const;
    void SetNetErrorString(const efd::utf8string& errString);
    void SetNetErrorString(const char *errString);

    efd::UInt32 GetSystemError() const;
    void SetSystemError(efd::UInt32 err);

    const efd::utf8string& GetSystemErrorString() const;
    void SetSystemErrorString(const efd::utf8string& errString);
    void SetSystemErrorString(const char *errString);

protected:
    efd::SInt32 m_netErr;
    efd::utf8string m_netErrString;
    efd::UInt32 m_sysErr;
    efd::utf8string m_sysErrString;
};

typedef SmartPointer<NetErrorMessage> NetErrorPtr;

} // end namespace efd

#include <efdNetwork/NetErrorMessage.inl>

#endif // NET_ERROR_MESSAGE_H 
