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
#ifndef EE_HOSTINFO_H
#define EE_HOSTINFO_H

#include <efd/OS.h>

#include <efdNetwork/Net.h>

#include <stdio.h>
#include <efd/utf8string.h>
#include <efd/SmartPointer.h>
#include <efdNetwork/efdNetworkLibType.h>

namespace efd
{

/// max expected length of hostname
const int HOST_NAME_LENGTH = 64;

class EE_EFDNETWORK_ENTRY HostInfo : public efd::MemObject
{
    EE_DECLARE_CONCRETE_REFCOUNT;
public:

    /// Default constructor
    HostInfo();

    /// Retrieves the host entry based on the host name or address
    HostInfo(const efd::utf8string& hostName);

    /// Destructor.  Closes the host entry database.
    ~HostInfo();

    /// Retrieves the hosts IP address
    const char* GetHostIPAddressStr()
    {
        return m_ipAddressStr.c_str();
    }

    /// Retrieves the hosts IP address
    efd::UInt32 GetHostIPAddressNum()
    {
        return m_ipAddressNum;
    }

    /// Retrieves the hosts name
    const char* GetHostName()
    {
        return m_hostName.c_str();
    }

    /// Get last error message.  If empty string, there was no error.
    const char* GetErrorMessage() { return m_errorMessage.c_str(); };

    /// Takes a UInt32 in network order and returns a utf8string of the ip address
    static efd::utf8string NetworkOrderIPToString(efd::UInt32 networkOrderIP);

    /// Takes a UInt32 in host order and returns a utf8string of the ip address
    static efd::utf8string IPToString(efd::UInt32 ip);

    /**
        Blocks the first time it is called with a specific string.  Subsequent times this function
        is called with the exact same string the result from the cache will be returned.
        @note: The cache has no timeout, if the ip address changes the cache will never know.
        FlushCache can be periodically called to force re-looking up of all names.

        @param nameOrIP The host name or ip address to look up
    */
    static efd::UInt32 ResolveNameOrIP(const efd::utf8string& nameOrIP)
    {
        efd::SmartPointer<HostInfo> spServerInfo;
        if (!m_dnsCache.find(nameOrIP,spServerInfo))
        {
            spServerInfo = EE_NEW HostInfo(nameOrIP);
            m_dnsCache[nameOrIP] = spServerInfo;
        }
        EE_ASSERT(spServerInfo);
        return spServerInfo->GetHostIPAddressNum();
    }

    /**
        Blocks the first time it is called with a specific string.  Subsequent times this function
        is called with the exact same string the result from the cache will be returned.
        @note: The cache has no timeout, if the ip address changes the cache will never know.
        FlushCache can be periodically called to force re-looking up of all names.

        @param nameOrIP The host name or ip address to look up
        @param pResultHostInfo [out] Filled in HostInfo for the looked up host.
    */
    static void ResolveNameOrIP(const efd::utf8string& nameOrIP, HostInfo*& pResultHostInfo)
    {
        efd::SmartPointer<HostInfo> spServerInfo;
        if (!m_dnsCache.find(nameOrIP,spServerInfo))
        {
            spServerInfo = EE_NEW HostInfo(nameOrIP);
            m_dnsCache[nameOrIP] = spServerInfo;
        }
        EE_ASSERT(spServerInfo);
        pResultHostInfo = spServerInfo;
    }


    /**
        Removes all cached names from DNS cache
    */
    static void FlushCache()
    {
        m_dnsCache.clear();
    }

private:

    /// Map of string to ip address to prevent requiring multiple DNS lookups
    static efd::map< efd::utf8string, efd::SmartPointer<HostInfo> > m_dnsCache;

    /// holds the hostname to be resolved, or the hostname retrieved
    efd::utf8string m_hostName;

    /// holds the ip address returned in string form, or the ip address to reverse lookup
    efd::utf8string m_ipAddressStr;

    /// holds the ip address returned in network byte order, or the ip address to reverse lookup
    efd::UInt32 m_ipAddressNum;

    /// error message returned from the attempted lookup
    efd::utf8string m_errorMessage;
};

} // end namespace efd

#endif // EE_HOSTINFO_H
