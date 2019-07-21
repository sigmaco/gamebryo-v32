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

namespace egf
{

//------------------------------------------------------------------------------------------------
template<typename T, efd::UInt32 msgguid>
tBreakpointRequest<T, msgguid>::tBreakpointRequest()
    : BreakpointRequest()
    , m_identity()
{
}

//------------------------------------------------------------------------------------------------
template<typename T, efd::UInt32 msgguid>
tBreakpointRequest<T, msgguid>::tBreakpointRequest(
    const T& identity,
    const efd::utf8string& behaviorName,
    const efd::Category& callback)
    : BreakpointRequest(behaviorName, callback)
    , m_identity(identity)
{
}

//------------------------------------------------------------------------------------------------
template< typename T, efd::UInt32 msgguid >
void tBreakpointRequest<T, msgguid>::Serialize(efd::Archive& ar)
{
    BreakpointRequest::Serialize(ar);
    efd::Serializer::SerializeObject(m_identity, ar);
}


//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
bool BreakpointResponse::Succeeded() const
{
    return (m_result == bp_Success);
}

//------------------------------------------------------------------------------------------------
bool BreakpointResponse::Failed() const
{
    return !Succeeded();
}

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
template< typename T, efd::UInt32 msgguid >
tBreakpointResponse< T, msgguid>::tBreakpointResponse()
    : BreakpointResponse()
    , m_breakpoints()
{
}

//------------------------------------------------------------------------------------------------
template< typename T, efd::UInt32 msgguid >
tBreakpointResponse< T, msgguid>::tBreakpointResponse(
    Result result,
    const tBehaviorBreakpointMap<T>& breakpoints)
    : BreakpointResponse(result)
    , m_breakpoints(breakpoints)
{
}

//------------------------------------------------------------------------------------------------
template< typename T, efd::UInt32 msgguid >
void tBreakpointResponse< T, msgguid>::Serialize(efd::Archive& ar)
{
    BreakpointResponse::Serialize(ar);

    efd::SR_StdMap<efd::SR_Default, efd::SR_StdSet<> >::Serialize(m_breakpoints, ar);
}

//------------------------------------------------------------------------------------------------
} // end namespace egf
