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
#ifndef EE_NAMERESOLUTIONMESSAGE_H
#define EE_NAMERESOLUTIONMESSAGE_H

#include <efd/ISystemService.h>
#include <efd/INetCallback.h>
#include <efd/SmartPointer.h>
#include <efd/IMessage.h>
#include <efd/efdClassIDs.h>
#include <efdNetwork/efdNetworkLibType.h>

namespace efd
{
class Archive;

/**
    Message used by the NameResolutionService to send Requests and Responses
*/
class EE_EFDNETWORK_ENTRY NameResolutionMessage : public IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(NameResolutionMessage, kCLASSID_NameResolutionMessage, IMessage);
    /// @endcond
public:

    /// @name Construction and Destruction
    //@{
    /// Default constructor.
    NameResolutionMessage();

    /// Virtual destructor.
    virtual ~NameResolutionMessage();
    //@}

    /// @name Accessors
    //@{
    inline efd::UInt32 GetServiceClassID() const;
    inline void SetServiceClassID(efd::UInt32 classID);

    inline const efd::utf8string& GetName() const;
    inline void SetName(const efd::utf8string& name);

    inline const efd::utf8string& GetHostname() const;
    inline void SetHostname(const efd::utf8string& hostname);

    inline efd::UInt16 GetPort() const;
    inline void SetPort(efd::UInt16 port);

    inline efd::Category GetResponseCategory() const;
    inline void SetResponseCategory(efd::Category responseCategory);

    inline efd::UInt32 GetResponseIP() const;
    inline void SetResponseIP(efd::UInt32 ip);

    inline efd::UInt16 GetResponsePort() const;
    inline void SetResponsePort(efd::UInt16 port);

    inline efd::TimeType GetTimestamp() const;
    inline void SetTimestamp(efd::TimeType timestamp);

    inline efd::TimeType GetRequestTimeout()const;
    inline void SetRequestTimeout(efd::TimeType tmo);

    inline const efd::utf8string& GetExtraInfo() const;
    inline void SetExtraInfo(const efd::utf8string& extraInfo);
    //@}

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void Serialize(efd::Archive& ar);

    /// @name Operators
    //@{
    bool operator==(const NameResolutionMessage& a) const;
    bool operator<(const NameResolutionMessage& a) const;
    //@}

protected:
    efd::UInt32 m_classID;
    efd::utf8string m_name;
    efd::UInt16 m_port;
    efd::utf8string m_hostname;
    efd::Category m_responseCategory;
    efd::UInt16 m_responsePort;
    efd::UInt32 m_responseIP;
    efd::TimeType m_timestamp;
    efd::TimeType m_request_timeout;
    efd::utf8string m_extraInfo;
public:
    efd::TimeType m_lastSend;
    efd::TimeType m_delay;
    efd::UInt16 m_requestNumber;
};
typedef efd::SmartPointer< NameResolutionMessage > NameResolutionMessagePtr;

/**
    Comparison operator for comparing two NameResolutionMessage instances.
    We use this below when defining a Set of NameResolutionMessage smart pointers.
*/
class NameResolutionMessagePtrLess
{
public:
    bool operator()(const NameResolutionMessagePtr& a, const NameResolutionMessagePtr& b) const;
};

typedef efd::set< NameResolutionMessagePtr, NameResolutionMessagePtrLess >
    NameResolutionMessageSet;
typedef efd::SmartPointer< efd::RefCountedMemObj<NameResolutionMessageSet> >
    NameResolutionMessageSetPtr;

typedef efd::list< NameResolutionMessagePtr > NameResolutionMessageList;
typedef efd::SmartPointer< efd::RefCountedMemObj< NameResolutionMessageList > >
    NameResolutionMessageListPtr;

} // end namespace efd

#include <efdNetwork/NameResolutionMessage.inl>

#endif //EE_NAMERESOLUTIONMESSAGE_H


