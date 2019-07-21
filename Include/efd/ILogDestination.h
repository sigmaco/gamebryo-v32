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
#ifndef EE_ILOGDESTINATION_H
#define EE_ILOGDESTINATION_H

#include <efd/UniversalTypes.h>
#include <efd/TimeType.h>
#include <efd/IBase.h>
#include <efd/utf8string.h>
#include <efd/SystemUniqueIndex.h>

namespace efd
{
/**
    Interface for log destination classes.  Any class that derives from this
    class maybe added as a destination for the logger.
*/
class EE_EFD_ENTRY ILogDestination : public efd::IBase
{
public:

    /// Constructor
    ILogDestination(const efd::utf8string& name)
        : m_name(name)
    {}
    
    /**
        Get the log destination name.

        @return destination name
    */
    virtual const efd::utf8string& GetName() const { return m_name; }

    /**
        Initializes the destination and prepares it for use

        @return True if the destination initialized properly
    */
    virtual efd::Bool OnInit()=0;

    /**
        Receives a complete log message from the logger to be written to the destination.

        @param assert True if the message is from an assert of verify
        @param timeStampMachine The time stamp that the log message occurred
            as a date time string based on the local machines clock.
        @param timeStampGame The time stamp that the log message occurred
            as a float in game time.
        @param pModule The name of the module that generated the log message.
        @param pLevel The level the log message is.
        @param pFile The source file where the log message was generated.
        @param line The source line where the log message was generated.
        @param pMsg The formatted log message.
    */
    virtual void LogMessage(
        efd::Bool assert,
        const char* timeStampMachine,
        efd::TimeType timeStampGame,
        const char* pModule,
        const char* pLevel,
        const char* pFile,
        efd::SInt32 line,
        const char* pMsg)
    {
        BeginLog(assert, timeStampMachine, timeStampGame, pModule, pLevel, pFile, line);
        ContinueLog(pMsg);
        EndLog();
    }

    /**
        Begin receiving a multi-part log message from the logger to be written to the destination.
        This call must be followed by zero or more calls to ContinueLog and then exactly one call
        to EndLog.

        @param assert True if the message is from an assert of verify
        @param timeStampMachine The time stamp that the log message occurred
            as a date time string based on the local machines clock.
        @param timeStampGame The time stamp that the log message occurred
            as a float in game time.
        @param pModule The name of the module that generated the log message.
        @param pLevel The level the log message is.
        @param pFile The source file where the log message was generated.
        @param line The source line where the log message was generated.
    */
    virtual void BeginLog(
        efd::Bool assert,
        const char* timeStampMachine,
        efd::TimeType timeStampGame,
        const char* pModule,
        const char* pLevel,
        const char* pFile,
        efd::SInt32 line) = 0;

    /**
        Add output to the current log following a BeginLog call.
    */
    virtual void ContinueLog(const char* pMsg) = 0;

    /// Used to complete a multi-part log statement
    virtual void EndLog() = 0;

    /// Flush any buffered data to output.
    virtual void Flush()=0;

protected:
    // Creates a unique filename by appending the value of m_uniqueIndex to the filename
    void IndexedFileName(efd::utf8string& fileName);

    // For generating unique file indexes
    efd::SystemUniqueIndex m_uniqueIndex;

    /// The unique name of this log destination.  Used for various log control functions.
    efd::utf8string m_name;
};

///    A SmartPointer for the ILogDestination class
typedef efd::SmartPointer<ILogDestination> ILogDestinationPtr;

#include "ILogDestination.inl"

} // end namespace efd

#endif // EE_ILOGDESTINATION_H
