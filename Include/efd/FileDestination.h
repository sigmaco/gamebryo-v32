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
#ifndef ELG_FILEDESTINATION_H
#define ELG_FILEDESTINATION_H

#include <efd/ILogDestination.h>
#include <efd/File.h>
#include <efd/efdClassIDs.h>
#include <efd/CriticalSection.h>

namespace efd
{

class ILogger;

/**
    File destination class receives messages from the logger and writes them to a file.
*/
class EE_EFD_ENTRY FileDestination : public ILogDestination
{
    /// @cond EMERGENT_INTERNAL

    EE_DECLARE_CLASS1(FileDestination, efd::kCLASSID_FileDestination, ILogDestination);
    EE_DECLARE_CONCRETE_REFCOUNT;

    /// @endcond

public:
    /// Enumerates options for opening the file.
    enum FileOption
    {
        /// Option to append to the existing file.
        kFileAppend,

        /// Option to overwrite the contents of the existing file.
        kFileOverwrite,

        /// Option to create a unique filename, if a file exists with the provided filename.
        kUniqueFileName,

        /// Option to create a unique filename by incrementing an index. This doesn't protect
        /// from stomping a log file between sessions (for that, use kUniqueFileName), but it
        /// will allow debugging multiple instances of the application simultaneously (with
        /// separate log files).
        kIndexedFileName
    };

    /**
        Constructor simply receives the filename and file option for later use.

        @param name Name for this destination.
        @param fileName Name, and optional path, for the file.
        @param option Option specifying how to open the file.
        @param fileInfoWithMsg True if the file and line number should be included when a log
            message is written; false otherwise (default is false).
        @param fileInfoWithAssert True if the file and line number should be included when an
            assert message is written; false otherwise (default is true).
        @param flushOnWrite Immediately flush to disk on every write (default is false).
        */
    FileDestination(
        const efd::utf8string& name,
        const efd::utf8string& fileName,
        FileOption option = kFileOverwrite,
        efd::Bool fileInfoWithMsg = false,
        efd::Bool fileInfoWithAssert = true,
        efd::Bool flushOnWrite = false);

    /**
        Destructor closes the file.
    */
    virtual ~FileDestination();

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

    /// Flush all data buffered for write.
    virtual void Flush();

    /**
        Static factory that creates a FileDestination and registers it with the ILogger that is
        passed in.

        @param pLogger Pointer to logger.
        @param name Name for this destination; ".log" is appended for the log file name.
        @param option Option specifying how to open the file.
        @param fileInfoWithMsg True if the file and line number should be included when a log
            message is written; false otherwise (default is false).
        @param fileInfoWithAssert True if the file and line number should be included when an
            assert message is written; false otherwise (default is true).
        @param flushOnWrite Every write will flush the buffer to disk. (default is false).
        @return Smart pointer to FileDestination.
    */
    static efd::SmartPointer<FileDestination> CreateAndOpen(
        ILogger* pLogger,
        const efd::utf8string& name,
        FileOption option = kFileOverwrite,
        efd::Bool fileInfoWithMsg = false,
        efd::Bool fileInfoWithAssert = true,
        efd::Bool flushOnWrite = false);

protected:
    /*
        Creates a unique filename based on the provided filename.
        This function appends a number to the file name until it finds a unique value.
          fileName : Name of the original file (and resulting unique filename).
    */
    void UniqueFileName(efd::utf8string& fileName);

    // Name of the file to which messages will be written.
    efd::utf8string m_fileName;

    // Option to use when opening the file.
    FileOption m_option;

    // True if the file and line number should be included when a log message is written.
    efd::Bool m_fileWithMsg;

    // True if the file and line number should be included when an assert message is written.
    efd::Bool m_fileWithAssert;

    // True if every write is immediately flushed to disk.
    efd::Bool m_flushOnWrite;

    // The file to which messages will be written.
    efd::File* m_pLogFile;

    // Used to ensure that multi-threaded logging writes to the file sequentially.
    efd::FastCriticalSection m_fileLock;

};

/// Define a smart pointer (reference counting, self deleting pointer) for the IFileDestination
/// class.
typedef efd::SmartPointer<FileDestination> FileDestinationPtr;

}   // End namespace efd.

#endif
