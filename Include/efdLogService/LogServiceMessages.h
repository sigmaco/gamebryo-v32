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
#ifndef EE_LOGSERVICEMESSAGES_H
#define EE_LOGSERVICEMESSAGES_H

#include <efd/StreamMessage.h>
#include <efd/Category.h>
#include <efd/efdMessageIDs.h>
#include <efdLogService/efdLogServiceLibType.h>
#include <efd/NetMessage.h>

namespace efd
{
/**
    Base log service request class. All log service request messages contain
    an optional callback category. This category is used by the target to
    send a response back to the caller.
*/
class EE_EFD_LOGSERVICE_ENTRY LogServiceRequest : public efd::StreamMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(LogServiceRequest, efd::kMSGID_LogServiceRequest, efd::StreamMessage);
    /// @endcond

public:

    /**
        Set method

        @param netId The net ID we want to service the request, or 0 for all log services.
        @param callback Category used to send responses, if needed.
    */
    void Set(efd::UInt32 netId, const efd::Category& callback);

    // convert this class into a stream of atomic types.
    virtual void Serialize(efd::Archive& ar);

    // category to send the response to.
    efd::UInt32 m_netid;
    efd::Category m_callback;
};

typedef efd::SmartPointer<LogServiceRequest> LogServiceRequestPtr;

/// @name MessageWrappers from LogServiceMessages.h
//@{
typedef MessageWrapper<LogServiceRequest,efd::kMSGID_GetLogDestinationsRequest>
    GetLogDestinationsRequest;
typedef MessageWrapper<LogServiceRequest,efd::kMSGID_GetModulesRequest> GetModulesRequest;
//@}

/**
    Base log service request class for getting / setting specific log levels.
    We add an optional log destination to to the base tLogServiceRequest. If this
    destination is the empty string then the message applies to the default destination.
*/
class EE_EFD_LOGSERVICE_ENTRY LogLevelRequest: public LogServiceRequest
{
public:
    /**
        Set method.

        @param netId Target identity for the message. e.g. net ID for server log services.
        @param callback Callback category for responses.
        @param dest Log destination
    */
    void Set(efd::UInt32 netId,
        const efd::Category& callback,
        const efd::utf8string& dest);

    virtual void Serialize(efd::Archive& ar);

    efd::utf8string m_destination;
};

/// @name MessageWrappers from LogServiceMessages.h
//@{

typedef MessageWrapper<LogLevelRequest, efd::kMSGID_StopLogStreamRequest> StopLogStreamRequest;
//@}

/**
    Helper class for requesting a module-based log level. We add the moduleId to
    the base tLogLevelRequest to identify which module the caller is interested in.
*/
class EE_EFD_LOGSERVICE_ENTRY BaseGetLogLevelRequest : public LogLevelRequest
{
public:
    /**
        Set method.

        @param moduleId The module id in question
        @param netId Net ID of the log service we want to respond. 0 for all.
        @param callback Callback category for responses.
        @param dest Log destination
    */
    void Set(
        efd::UInt16 moduleId,
        efd::UInt32 netId,
        const efd::Category& callback,
        const efd::utf8string& dest = "");

    // convert this class into a stream of atomic types.
    virtual void Serialize(efd::Archive& ar);

    efd::UInt16 m_moduleId;
};

/// @name MessageWrappers from LogServiceMessages.h
//@{

typedef MessageWrapper<BaseGetLogLevelRequest, efd::kMSGID_GetLogLevelRequest> GetLogLevelRequest;
//@}

typedef efd::SmartPointer<GetLogLevelRequest> GetLogLevelRequestPtr;


/**
    Helper class for requesting a category / message type based log level. We add both
    a category and message type id to the base tLogLevelRequest to identify the category
    and / or message type the caller is interested in.
*/
class EE_EFD_LOGSERVICE_ENTRY BaseGetMsgLogLevelRequest: public LogLevelRequest
{
public:
    /// @name Construction and Destruction
    //@{

    BaseGetMsgLogLevelRequest() {}

    virtual ~BaseGetMsgLogLevelRequest() { }
    //@}

    /**
        Set method.

        @param category The category in question, or 0 if not interested.
        @param msgClassID The message type ID in question, or 0 if not interested.
        @param netId Net ID of the log service we want to respond. 0 for all.
        @param callback Callback category for responses.
        @param dest Log destination
    */
    void Set(const efd::Category& category,
        efd::ClassID msgClassID,
        efd::UInt32 netId,
        const efd::Category& callback,
        const efd::utf8string& dest = "");

    // convert this class into a stream of atomic types.
    virtual void Serialize(efd::Archive& ar);


    efd::Category m_category;
    efd::ClassID m_msgClassID;
};

/// @name MessageWrappers from LogServiceMessages.h
//@{
typedef MessageWrapper<BaseGetMsgLogLevelRequest, efd::kMSGID_GetMsgLogLevelRequest>
    GetMsgLogLevelRequest;

//@}
typedef efd::SmartPointer<GetMsgLogLevelRequest> GetMsgLogLevelRequestPtr;

/**
    Helper class for setting a module-based log level. We add the moduleId and levelId
    to the base tLogLevelRequest to indicate the module and log level to set.
*/
class EE_EFD_LOGSERVICE_ENTRY BaseSetLogLevelRequest : public LogLevelRequest
{
public:
    /**
        Set method.

        @param moduleId The module id in question
        @param levelId The log level to set.
        @param netId Net ID of the log service we want to respond. 0 for all.
        @param callback Callback category for responses.
        @param dest Log destination
    */
    void Set(efd::UInt16 moduleId,
        efd::UInt8 levelId,
        efd::UInt32 netId,
        const efd::Category& callback = efd::kCAT_INVALID,
        const efd::utf8string& dest = "");

    // convert this class into a stream of atomic types.
    virtual void Serialize(efd::Archive& ar);


    efd::UInt16 m_moduleId;
    efd::UInt8 m_levelId;
};

/// @name MessageWrappers from LogServiceMessages.h
//@{

typedef MessageWrapper<BaseSetLogLevelRequest, efd::kMSGID_SetLogLevelRequest> SetLogLevelRequest;
//@}

typedef efd::SmartPointer<SetLogLevelRequest> SetLogLevelRequestPtr;

/**
    Helper class for setting a module-based log level. We add the moduleId and levelId
    to the base tLogLevelRequest to indicate the module and log level to set.
*/
class EE_EFD_LOGSERVICE_ENTRY BaseStartLogStreamRequest : public LogLevelRequest
{
public:
    /**
        Set method

        @param moduleId The module id in question
        @param levelId The log level to set.
        @param netId Net ID of the log service we want to respond.
        @param streamName A unique name for the new stream.
        @param callback Callback category for responses.
    */
    void Set(efd::UInt16 moduleId,
        efd::UInt8 levelId,
        efd::UInt32 netId,
        const efd::utf8string& streamName,
        const efd::Category& callback = efd::kCAT_INVALID);

    // convert this class into a stream of atomic types.
    virtual void Serialize(efd::Archive& ar);

    efd::UInt16 m_moduleId;
    efd::UInt8 m_levelId;
};
/// @name MessageWrappers from LogServiceMessages.h
//@{
typedef MessageWrapper<BaseStartLogStreamRequest, efd::kMSGID_StartLogStreamRequest>
    StartLogStreamRequest;
//@}

typedef efd::SmartPointer<StartLogStreamRequest> StartLogStreamRequestPtr;


/**
    Helper class for setting a category / message type based log level. We add the
    category, message type id, and log level to the base tLogLevelRequest to identify
    which category and/or message type to set.
*/
class EE_EFD_LOGSERVICE_ENTRY BaseSetMsgLogLevelRequest : public LogLevelRequest
{
public:
    /**
        Set method.

        @param category Category we want to set, or kCAT_INVALID if N/A.
        @param msgClassID Message type id we want to set, or 0 if N/A.
        @param levelId The log level to set.
        @param netId Net ID of the log service we want to respond. 0 for all.
        @param callback Callback category for responses.
        @param dest Log destination
    */
    void Set(const efd::Category& category,
        efd::ClassID msgClassID,
        efd::UInt8 levelId,
        efd::UInt32 netId,
        const efd::Category& callback = efd::kCAT_INVALID,
        const efd::utf8string& dest = "");

    // convert this class into a stream of atomic types.
    virtual void Serialize(efd::Archive& ar);

    efd::Category m_category;
    efd::ClassID m_msgClassID;
    efd::UInt8 m_levelId;
};
/// @name MessageWrappers from LogServiceMessages.h
//@{

typedef MessageWrapper<BaseSetMsgLogLevelRequest, efd::kMSGID_SetMsgLogLevelRequest>
    SetMsgLogLevelRequest;
//@}

typedef efd::SmartPointer<SetMsgLogLevelRequest> SetMsgLogLevelRequestPtr;

/**
    Base class for all responses to log service request messages. This class defines
    the result codes for operations executed against the Log Service. It also contains
    the netId of the respondent.
*/
class EE_EFD_LOGSERVICE_ENTRY LogServiceResponse : public efd::StreamMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(LogServiceResponse, efd::kMSGID_LogServiceResponse, efd::StreamMessage);
    /// @endcond

public:
    enum Result
    {
        lsr_Unknown,
        lsr_Success,
        lsr_Failure,
    };

    /// Constructor
    LogServiceResponse();

    /**
        Set method.

        @param netId Net ID of the respondent.
        @param result Result of the operation
    */
    void Set(efd::UInt32 netId, Result result);

    // convert this class into a stream of atomic types.
    virtual void Serialize(efd::Archive& ar);

    efd::UInt32 m_netid;
    Result m_result;
};
typedef efd::SmartPointer<LogServiceResponse> LogServiceResponsePtr;


/**
    Base class for log service responses that contain a set of names. e.g.
    Get Destinations. This adds a efd::set<efd::utf8string> set of names
    to the LogServiceResponse base class.
*/
class EE_EFD_LOGSERVICE_ENTRY NameSetResponse : public LogServiceResponse
{
public:
    typedef efd::set<efd::utf8string> NameSet;

     /**
        Set method.

        @param names Set of names
        @param netId Net ID of the respondent
        @param result Result of the operation.
    */
    void Set(
        const NameSet& names,
        efd::UInt32 netId,
        LogServiceResponse::Result result);

    // convert this class into a stream of atomic types.
    virtual void Serialize(efd::Archive& ar);

    NameSet m_names;
};
/// @name MessageWrappers from LogServiceMessages.h
//@{

typedef MessageWrapper<NameSetResponse, efd::kMSGID_GetLogDestinationsResponse>
    GetLogDestinationsResponse;
//@}

/**
    Base class for log service responses that contain a map of names. e.g.
    Get Destinations. This adds a efd::map<efd::UInt16, efd::utf8string> map of names
    to the LogServiceResponse base class.
*/
class EE_EFD_LOGSERVICE_ENTRY GetModulesResponse
    : public LogServiceResponse
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(GetModulesResponse, efd::kMSGID_GetModulesResponse, efd::LogServiceResponse);
    /// @endcond

public:
    typedef efd::map<efd::UInt16, efd::utf8string> NameMap;

    /**
        Set method

        @param names Map of UInt32 ids to names
        @param netId Net ID of the respondent
        @param result Result of the operation.
    */
    void Set(const NameMap& names, efd::UInt32 netId, LogServiceResponse::Result result);

    // convert this class into a stream of atomic types.
    virtual void Serialize(efd::Archive& ar);

    NameMap m_names;
};


/**
    Response to a get log level request. It adds the module id and level id to the
    base LogServiceResponse.
*/
class EE_EFD_LOGSERVICE_ENTRY GetLogLevelResponse
    : public LogServiceResponse
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(GetLogLevelResponse,
        efd::kMSGID_GetLogLevelResponse,
        efd::LogServiceResponse);
    /// @endcond

public:

    /**
        Set method

        @param moduleId The module id in question
        @param levelId The log level to set.
        @param netId Net ID of the log service we want to respond. 0 for all.
        @param result result of the operation
    */
    void Set(
        efd::UInt16 moduleId,
        efd::UInt8 levelId,
        efd::UInt32 netId,
        LogServiceResponse::Result result);

    // convert this class into a stream of atomic types.
    virtual void Serialize(efd::Archive& ar);

    efd::UInt32 m_moduleId;
    efd::UInt8 m_levelId;
};

/**
    Response to a get msg log level request message. It adds the category,
    message type id, and log level id to the base LogServiceResponse.
*/
class EE_EFD_LOGSERVICE_ENTRY GetMsgLogLevelResponse
    : public LogServiceResponse
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(GetMsgLogLevelResponse,
        efd::kMSGID_GetMsgLogLevelResponse,
        efd::LogServiceResponse);
    /// @endcond

public:
    /// @name Construction and Destruction
    //@{

    /// Default constructor.
    GetMsgLogLevelResponse();

    /**
        Get the message log response.

        @param category the category of the message.
        @param msgClassID Message type id.
        @param levelId Log level.
        @param netId Net ID of the log service we want to respond. 0 for all.
        @param result The result of the operation.
    */
    GetMsgLogLevelResponse(
        const efd::Category& category,
        efd::ClassID msgClassID,
        efd::UInt8 levelId,
        efd::UInt32 netId,
        LogServiceResponse::Result result);

    //@}

    // convert this class into a stream of atomic types.
    virtual void Serialize(efd::Archive& ar);

    efd::Category m_category;
    efd::ClassID m_msgClassID;
    efd::UInt8 m_levelId;
};

/// @name MessageWrappers from LogServiceMessages.h
//@{

typedef MessageWrapper<LogServiceResponse, efd::kMSGID_SetLogLevelResponse> SetLogLevelResponse;
typedef MessageWrapper<LogServiceResponse, efd::kMSGID_SetMsgLogLevelResponse>
    SetMsgLogLevelResponse;
typedef MessageWrapper<LogServiceResponse, efd::kMSGID_StartLogStreamResponse>
    StartLogStreamResponse;
typedef MessageWrapper<LogServiceResponse, efd::kMSGID_StopLogStreamResponse> StopLogStreamResponse;
//@}


/**
    A message containing one or more log entries.
*/
class EE_EFD_LOGSERVICE_ENTRY LogEntriesMessage : public efd::StreamMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(LogEntriesMessage, efd::kMSGID_LogEntriesMessage, efd::StreamMessage);
    /// @endcond

public:
    typedef efd::vector< efd::utf8string > LogEntries;

    /// Default constructor
    LogEntriesMessage();

    /**
        Create a new request to the log service.

        @param netID      The NetId of the producer
        @param PID        The producers process ID
        @param entries    A vector of log entries.
    */
    LogEntriesMessage(
        efd::UInt32 netID,
        efd::UInt64 PID,
        const efd::vector< efd::utf8string >& entries);

    // convert this class into a stream of atomic types.
    virtual void Serialize(efd::Archive& ar);

    efd::UInt32 m_netID;
    efd::UInt64 m_pid;
    LogEntries m_entries;
};

typedef efd::SmartPointer<LogEntriesMessage> LogEntriesMessagePtr;


/// A message with a target and callback Category.
class EE_EFD_LOGSERVICE_ENTRY ClientLogServiceRequest : public efd::EnvelopeMessage
{
    /// @cond EMERGENT_INTERNAL

    EE_DECLARE_CLASS1(
        ClientLogServiceRequest,
        efd::kMSGID_ClientLogServiceRequest,
        efd::EnvelopeMessage);

    /// @endcond

public:
    /// @name Construction and Destruction
    //@{
    ClientLogServiceRequest();

    virtual ~ClientLogServiceRequest();
    //@}

    /**
        Client log service request.

        @param payload going to the client.
        @param targetCategory the target category for this message. (e.g. the gateway category)
        @param callback the callback category used to send a response to the caller.
    */
    ClientLogServiceRequest(
        efd::IMessagePtr payload,
        const efd::Category& targetCategory,
        const efd::Category& callback = efd::kCAT_INVALID);

    /// convert this class into a stream of atomic types.
    virtual void Serialize(efd::Archive& ar);

    efd::Category m_callback;
    efd::Category m_target;
};

} // end namespace efd

EE_SPECIALIZE_ENUM(efd::LogServiceResponse::Result, efd::UInt8);

#endif // EE_LOGSERVICEMESSAGES_H
