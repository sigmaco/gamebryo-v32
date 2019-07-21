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

//------------------------------------------------------------------------------------------------
inline INetLib::INetLib()
    :m_netID(kNetID_Unassigned)
{
}

//------------------------------------------------------------------------------------------------
inline INetLib::~INetLib()
{
    if (ms_pNetLibFactory != NULL)
        EE_DELETE ms_pNetLibFactory;
    ms_pNetLibFactory = NULL;
}

//------------------------------------------------------------------------------------------------
inline ConnectionID INetLib::GenerateConnectionID(
    efd::QualityOfService qos,
    efd::UInt32 ip,
    efd::UInt16 remotePort,
    efd::UInt16 localPort)
{
    return ConnectionID(qos, ip, localPort, remotePort);
}

//------------------------------------------------------------------------------------------------
inline void INetLib::SetNetID(UInt32 netID)
{
    m_netID = netID;
}

//------------------------------------------------------------------------------------------------
inline UInt32 INetLib::GetNetID() const
{
    return m_netID;
}

//------------------------------------------------------------------------------------------------
template<typename T>
inline void INetLib::RegisterNetLib(const efd::utf8string& netLibName)
{
    if (ms_pNetLibFactory == NULL)
        ms_pNetLibFactory = EE_NEW NetLibFactory();
    ms_pNetLibFactory->RegisterFactoryMethod(
        netLibName,
        NetLibFactory::GenerateFactoryMethod<T>);
}

//------------------------------------------------------------------------------------------------
} // end namespace efd
