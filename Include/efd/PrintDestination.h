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
#ifndef EE_PrintDestination_h
#define EE_PrintDestination_h

#include <efd/UniversalTypes.h>
#include <efd/ILogDestination.h>
#include <efd/utf8string.h>
#include <efd/ILogger.h>
#include <efd/efdLibType.h>
#include <efd/efdClassIDs.h>

namespace efd
{

/**
    PrintDestination class receives messages from the logger and writes them to printf.
*/
class EE_EFD_ENTRY PrintDestination : public ILogDestination
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(PrintDestination, efd::kCLASSID_PrintDestination, ILogDestination);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond
public:

    /**
        Constructor simply receives the filename and file option for later use.

        @param name name for this destination
        @param decorateMessage True if you want headers on the log messages.
        @param fileInfoWithMsg True if the file and line number should be
            included when a log message is written (default is false)
        @param fileInfoWithAssert True if the file and line number should be
            included when an assert message is written (default is true)
        */
    PrintDestination(
        const efd::utf8string& name,
        efd::Bool decorateMessage = false,
        efd::Bool fileInfoWithMsg = false,
        efd::Bool fileInfoWithAssert = true);

    /**
        Destructor closes the file.
    */
    virtual ~PrintDestination();

    // See ILogDestination::OnInit
    virtual efd::Bool OnInit();

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

    virtual void Flush();

protected:
    /// True if you want headers on the log messages
    efd::Bool m_decorateMessage;

    /// True if the file and line number should be included when a log message is written
    efd::Bool m_fileWithMsg;

    /// True if the file and line number should be included when an assert message is written
    efd::Bool m_fileWithAssert;
};

/**
    A smart pointer (reference counting, self deleting pointer) for the PrintDestination class
*/
typedef efd::SmartPointer<PrintDestination> PrintDestinationPtr;

} // namespace efd

#endif // EE_PrintDestination_h
