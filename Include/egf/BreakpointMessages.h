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
#ifndef EE_BREAKPOINTMESSAGES_H
#define EE_BREAKPOINTMESSAGES_H

#include <efd/StreamMessage.h>
#include <efd/Category.h>
#include <egf/egfMessageIDs.h>
#include <egf/egfLibType.h>
//#include <efd/SerializeRoutines.h> // needed on PS3 compiler

#if defined(_MSC_VER)
#pragma warning(disable:4505)  // unreferenced local function has been removed.
#endif


namespace egf
{

// map of identifiers to behavior breakpoints
template <typename T>
class tBehaviorBreakpointMap : public efd::map< T, efd::set<efd::utf8string> >
{
};


/**
    A request to start a debugger session. Request to the simulator to connect to
    the python debugger on a certain host/port and start a session. This causes an
    immediate breakpoint in scheduler.py. Once a debugger is started, the caller is
    free to add/remove python behavior breakpoints.
 */
class EE_EGF_ENTRY StartDebuggerRequest : public efd::StreamMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(StartDebuggerRequest, efd::kMSGID_StartDebuggerRequest, efd::StreamMessage);
    /// @endcond

public:
    StartDebuggerRequest();
    virtual ~StartDebuggerRequest();

    /**
        A request to connect to and start a python debugger session.
        @param host name of the host running the debugger
        @param port port number the debugger is listening on
        @param callback Callback category.
    */
    StartDebuggerRequest(
        const efd::utf8string& host,
        efd::UInt32 port,
        const efd::Category& callback = efd::kCAT_INVALID);

    // convert this class into a stream of atomic types.
    virtual void Serialize(efd::Archive& ar);

    efd::utf8string m_host;
    efd::UInt32 m_port;
    efd::Category m_callback;
};

typedef efd::SmartPointer<StartDebuggerRequest> StartDebuggerRequestPtr;


/**
    A breakpoint request. Request to the simulator to add/remove breakpoints, etc.
    This base class is the basis for all breakpoint requests.
 */
class EE_EGF_ENTRY BreakpointRequest : public efd::StreamMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(BreakpointRequest, efd::kMSGID_BreakpointRequest, efd::StreamMessage);
    /// @endcond

public:
    BreakpointRequest();
    ~BreakpointRequest();

    /**
        Create a new breakpoint request.
        @param behaviorName
        @param callback the category used for responses
    */
    BreakpointRequest(
        const efd::utf8string& behaviorName,
        const efd::Category& callback = efd::kCAT_INVALID);

    // convert this class into a stream of atomic types.
    virtual void Serialize(efd::Archive& ar);

    efd::utf8string m_behaviorName;
    efd::Category m_callback;
};

typedef efd::SmartPointer<BreakpointRequest> BreakpointRequestPtr;


/**
    A templated breakpoint request. The template argument is the behavior owner's
    identity type. e.g. utf8string for model names, EntityID for entities, etc.

    Usage: tBreakpointRequest<EntityID, kMSGID_InsertEntityBreakpoint>
 */
template<typename T, efd::UInt32 msgguid>
class tBreakpointRequest : public BreakpointRequest
{
public:
    inline tBreakpointRequest<T, msgguid>();

    inline tBreakpointRequest<T, msgguid>(
        const T& identity,
        const efd::utf8string& behaviorName,
        const efd::Category& callback = efd::kCAT_INVALID);

    virtual void Serialize(efd::Archive& ar);

    static efd::IBasePtr FactoryMsg()
    {
        // The PS3 compiler requires this be here and not in the inl file
        return EE_NEW tBreakpointRequest< T, msgguid >;
    }

    T m_identity;
};


/// usage: RegisterBreakpointRequestFactory< type, guid >();
template <typename T, efd::UInt32 msgguid>
void RegisterBreakpointRequestFactory(efd::MessageFactory* pMessageFactory)
{
    pMessageFactory->RegisterFactoryMethod(
        msgguid,
        &tBreakpointRequest< T, msgguid >::FactoryMsg);
}


/**
    A response message to a breakpoint request.
 */
class EE_EGF_ENTRY BreakpointResponse : public efd::StreamMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(BreakpointResponse, efd::kMSGID_BreakpointResponse, efd::StreamMessage);
    /// @endcond

public:

    enum Result
    {
        bp_Unknown,
        bp_Success,
        bp_Failed,
    };

    BreakpointResponse();

    ~BreakpointResponse();

    /**
        Construct a new breakpoint response.

        @param result The result to use for the response.
    */
    BreakpointResponse(Result result);

    // convert this class into a stream of atomic types.
    virtual void Serialize(efd::Archive& ar);

    inline bool Succeeded() const;
    inline bool Failed() const;

    Result m_result;
};

typedef efd::SmartPointer<BreakpointResponse> BreakpointResponsePtr;


/**
    Templated version of the BreakpointResponse. The template class is the
    base class for the breakpoint container. e.g. egf::EntityID
 */
template<typename T, efd::UInt32 msgguid>
class tBreakpointResponse : public BreakpointResponse
{
public:
    tBreakpointResponse<T, msgguid>();

    tBreakpointResponse<T, msgguid>(
        Result result,
        const tBehaviorBreakpointMap<T>& breakpoints);

    virtual void Serialize(efd::Archive& ar);

    static efd::IBasePtr FactoryMsg()
    {
        // The PS3 compiler requires this be here and not in the inl file
        return EE_NEW tBreakpointResponse<T, msgguid>;
    }

    tBehaviorBreakpointMap<T> m_breakpoints;
};

//usage: RegisterBreakpointResponseFactory< type, guid >();
template <typename T, efd::UInt32 msgguid>
void RegisterBreakpointResponseFactory(efd::MessageFactory* pMessageFactory)
{
    pMessageFactory->RegisterFactoryMethod(
        msgguid,
        &tBreakpointResponse< T, msgguid >::FactoryMsg);
}

} // end namespace egf

EE_SPECIALIZE_ENUM(egf::BreakpointResponse::Result, efd::UInt8);

#include "BreakpointMessages.inl"


#endif // EE_BREAKPOINTMESSAGES_H

