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
#ifndef EE_XMLMEMLOGHANDLER
#define EE_XMLMEMLOGHANDLER

#include <efd/UniversalTypes.h>
#include <efd/TimeType.h>
#include <efd/MemObject.h>
#include <efd/IBase.h>
#include <efd/MemTracker.h>
#include <efd/IMemLogHandler.h>
#include <efd/IDs.h>
#include <efd/File.h>
#include <efd/efdClassIDs.h>

namespace efd
{
/**
This class is an XML based memory logger. The logger will produce a
Memory-Overview.xml file and a Memory-Leaks.xml file. The Memory-Overview.xml
file contains a log of all memory allocations performed by the application.
The only exception to this is the memory allocations performed by
IMemLogHandler::OnInit() will not be logged. Also a Memory-Leaks.xml file will
be produced listing any memory leaked by the application.

Each xml file has an associated style sheet (MemoryReport.xsl & MemoryLeak.xsl)
that will be produced in the same folder as the xml files. The style sheets
allow the xml files to be view in an web-browser with easy to read formating.
*/
class EE_EFD_ENTRY XMLMemLogHandler : public efd::IMemLogHandler
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(XMLMemLogHandler, efd::kCLASSID_XMLMemLogHandler, IMemLogHandler);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond
public:

    XMLMemLogHandler();

    /**
        Initializes any internal data structures that will be needed. This
        includes all XML file handles. This method is also responsible for
        creating the MemoryReport.xsl & MemoryLeaks.xsl files if they do not
        already exist.

        @return True if the initialization was successful.
    */
    virtual efd::Bool OnInit();

    /**
        Shutdown all internal data structures.

        @return True if the shutdown was successful.
    */
    virtual efd::Bool OnShutdown();

    /// Returns true if the IMemLogHandler has been initialized.
    virtual efd::Bool IsInitialized();

    /**
        This method writes a line of XML code describing the to allocation unit
        (pkUnit) to the specified NiLogger channel (iChannel). Other arguments
        are specified if this line is meant to log information about the
        deallocation.
    */
    virtual void LogAllocUnit(const AllocUnit *pkUnit,
        const char* pcPrefix = "",
        MemEventType eDeallocType = EE_MET_UNKNOWN,
        double fDeallocTime = -FLT_MAX,
        unsigned long ulDeallocThreadId = 0,
        size_t stSizeUnused = 0) const;

    /// This method is responsible for logging a memory leak.
    virtual void LogAllocUnitLeak(const AllocUnit *pkUnit,
        const char* pcPrefix = "") const;

    /// Write data to the memory leak log file about all active allocations.
    void LogMemoryReport() const;

    /// Write a summary of the memory statistics to the memory overview log file.
    void LogSummaryStats() const;

    /**
        The method allows applications to set a mark between allocation events
        that can be used to help better track and organize all memory allocations.
    */
    bool SetMarker(const char* pcMarkerType,
        const char* pcClassifier, const char* pcString);

#if defined(EE_MEMTRACKER_SNAPSHOT)
    virtual void BeginSnapshotLog(const char* pszName);
    virtual void LogAllocUnitSnapshot(const AllocUnit *pkUnit);
    virtual void EndSnapshotLog();
#endif // defined(EE_MEMTRACKER_SNAPSHOT)

protected:
    void WriteLogHeader(
        efd::File* pFile,
        const char* pszXslFile,
        struct tm* pSysTime,
        struct tm* pLocalTime);

    void WriteAllocUnitXMLBlock(
        efd::File* pkFile,
        const AllocUnit *pkUnit,
        const char* pcPrefix,
        bool includeStack,
        MemEventType eDeallocType = EE_MET_UNKNOWN,
        double fDeallocTime = -FLT_MAX,
        unsigned long ulDeallocThreadId = 0,
        size_t stSizeUnused = 0) const;


    static const char* FormatForXML(const char* pcInString);

    static void WriteTextToFile(efd::File* pkFile, const char* pcText, ...);

    static void ReportMemoryLeaks(AllocUnit* pkActiveAllocUnit, IMemLogHandler* pLogHandler);

    void CreateXSLForLeaks();
    void CreateXSLForSnapshot();
    void CreateXSLForFreeReport();

    efd::File* m_pOverviewXMLFile;
    efd::File* m_pLeakXMLFile;
    efd::File* m_pSummaryXMLFile;

    efd::Bool m_bInitalized;
};

    /**
    A smart pointer (reference counting, self deleting pointer) for the
    ILogDestination class
    */
    typedef efd::SmartPointer<XMLMemLogHandler> XMLMemLogHandlerPtr;

}  // namespace efd

#endif // EE_XMLMEMLOGHANDLER
