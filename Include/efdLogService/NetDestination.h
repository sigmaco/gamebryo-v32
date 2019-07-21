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
#ifndef EE_NETDESTINATION_H
#define EE_NETDESTINATION_H

#include <efd/UniversalTypes.h>
#include <efd/ILogDestination.h>
#include <efd/utf8string.h>
#include <efd/ILogger.h>
#include <efd/Category.h>
#include <efdLogService/efdLogServiceLibType.h>
#include <efd/efdClassIDs.h>
#include <efd/CriticalSection.h>

namespace efd
{

class MessageService;

// The local memory buffer for log entries.
typedef efd::vector< efd::utf8string > LogMemBuffer;

/**
    A log destination that sends new log entries out to remote subscribers
    via a Category. The NetDestination buffers incoming log messages until
    a high water mark is reached, at which point one or more Log Entry messages
    are sent out on the provided category.
*/
class EE_EFD_LOGSERVICE_ENTRY NetDestination : public efd::ILogDestination
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(NetDestination, efd::kCLASSID_NetDestination, efd::ILogDestination);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

public:
    /**
        Constructor simply receives the Category used to send log messages.

        @param name name of this destination.
        @param category category for send.
        @param pMessageService a message service pointer
        @param highwatermark the number of log entries for which to reserve buffer storage
        @param fileInfoWithMsg if true, include file information with log messages
        @param fileInfoWithAssert if true, include file information with assert messages
        */
    NetDestination(const efd::utf8string& name,
                   const efd::Category& category,
                   MessageService* pMessageService,
                   efd::UInt32 highwatermark = 64,
                   bool fileInfoWithMsg = false,
                   bool fileInfoWithAssert = true);

    virtual ~NetDestination();

    // Overridden virtual functions inherit base documentation and thus
    // are not documented here.

    virtual bool OnInit();

    /**
        Publish the buffered log entries to the Category. This clears the buffer.
    */
    virtual void Publish();

    // See ILogDestination::BeginLog
    virtual void BeginLog(
        efd::Bool assert,
        const char* timeStampMachine,
        efd::TimeType timeStampGame,
        const char* pModule,
        const char* pLevel,
        const char* pFile,
        efd::SInt32 line);

    // See ILogDestination::ContinueLog
    virtual void ContinueLog(const char* pMsg);

    // See ILogDestination::EndLog
    virtual void EndLog();

    // See ILogDestination::Flush
    virtual void Flush();

protected:
    // category to which log messages are sent.
    efd::Category m_category;

    // log buffer to accumulate log entries. This is flushed during Publish.
    LogMemBuffer m_buffer;

    bool m_fileWithMsg;
    bool m_fileWithAssert;

    // the process ID
    efd::UInt64 m_pid;

    efd::SmartPointer< MessageService > m_spMessageService;

    // For protecting access to m_buffer during cross-thread access
    efd::FastCriticalSection m_bufferLock;
};

/**
    A smart pointer (reference counting, self deleting pointer) for the
    NetDestination class
*/
typedef efd::SmartPointer<NetDestination> NetDestinationPtr;

} // end namespace efd

#endif // #ifndef EE_NETDESTINATION_H
