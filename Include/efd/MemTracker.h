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
#ifndef EE_MEMTRACKER_H
#define EE_MEMTRACKER_H

#include <stdio.h>
#include <efd/IAllocator.h>
#include <efd/CriticalSection.h>
#include <efd/Utilities.h>

namespace efd
{
class IMemLogHandler;

EE_EFD_ENTRY efd::IMemLogHandler* InitializeMemoryLogHandler();

#if defined(EE_EFD_EXPORT) || defined(EE_EFD_IMPORT)
    #define EE_FLF_FILE_LENGTH 256
    #define EE_FLF_FUNCTION_LENGTH 256
#endif

/// Size of the stack trace to grab on each allocation when EE_MEMTRACKER_STACKTRACE is defined.
#define EE_MEMSTACKTRACE_DEPTH  10

/**
    @def EE_MEM_SETDETAILEDREPORT
    Macro to associate a detailed report generator with a specific allocation.
    @param pObject The already allocated object
    @param pfn The detailed reporting function
*/
#if defined(EE_MEMTRACKER_DETAILEDREPORTING)
    #define EE_MEM_SETDETAILEDREPORT(pObject, pfn) \
    if (efd::MemTracker::Get()) efd::MemTracker::Get()->SetDetailReportForAllocation(pObject, pfn)
#else
    #define EE_MEM_SETDETAILEDREPORT(pObject, pfn) (void)false
#endif

/**
    This class is designed to store the file, line, and function information
    for later access by the memory tracking system. This data is stored in the
    public variables: m_pcFile, m_pcFunc, and m_uiLine.
*/
class EE_EFD_ENTRY FLF
{
public:
    /// @name Constructors and Destructors
    //@{
    FLF();
    FLF(const char* pcFile, unsigned int uiLine, const char* pcFunc);
    //@}

    /// Set the file, line, and function name for the allocation.
    inline void Set(const char* pcFile, unsigned int uiLine, const char* pcFunc);

    /// Reset this FLF to the default unknown state.
    inline void Reset();

    /// Return true if this FLF contains a valid file, line, and function name.
    inline bool IsValid() const;

    // Since DLL builds can potentially detach at any time,
    // it is necessary to copy the file and function strings
    // in DLL builds rather than using the pointer directly.
#if defined(EE_EFD_EXPORT) || defined(EE_EFD_IMPORT)
    char m_pcFile[EE_FLF_FILE_LENGTH];
    char m_pcFunc[EE_FLF_FUNCTION_LENGTH];
#else
    const char* m_pcFile;
    const char* m_pcFunc;
#endif
    unsigned int m_uiLine;


    static const FLF UNKNOWN;

    const char* SourceFileStripper() const;
    const char* CreateTempFLFString();
};

/**
    This class is designed to hold all information about a piece of allocated
    memory. Since it does not persist beyond that piece of memory's
    deallocation, it holds no deallocation information.
*/
class EE_EFD_ENTRY AllocUnit
{
public:

    /**
        A unique identifier for the allocation unit with respect to the
        m_stAccumulatedAllocationCount count.
    */
    size_t m_stAllocationID;

    /**
        The address returned by the internal allocator. Depending on how the
        sub-allocator works, this address may or may not be the start of the
        full allocation.
    */
    void* m_pvMem;

    /// The alignment of the memory as requested at allocation time.
    size_t m_stAlignment;

    /// The amount of memory that was requested at allocation time.
    size_t m_stSizeRequested;

    /**
        The amount of memory that was actually allocated at allocation time.
        This number should be greater than or equal to m_stSizeRequested.
    */
    size_t m_stSizeAllocated;

    /// The prior allocation unit in the active array.
    AllocUnit* m_pkPrev;

    /// The next allocation unit in the active array.
    AllocUnit* m_pkNext;

    /**
        The unique identifier for the thread that was used to allocate the
        memory.
    */
    unsigned long m_ulAllocThreadId;

    /// The time at which the allocation occurred, as reported by GetCurrentTimeInSec
    /// Note: This is stored as a float instead of double to save space.
    float m_fAllocTime;

    /// The MemEventType used to allocate the memory.
    MemEventType m_eAllocType;

    /// The MemHint used to allocate the memory.
    MemHint m_kAllocHint;

#if defined(EE_MEMTRACKER_DETAILEDREPORTING)
    /// Helper to generate a detailed report if there is a m_pfnDetails function
    inline void GetDetailedReport(char* o_buffer, unsigned int i_cchBuffer) const;

    typedef void(*pfnDetailMethod)(void* pMem, char* o_buffer, unsigned int i_cchBuffer);
    pfnDetailMethod m_pfnDetails;
#endif

    /// The FLF storing the file, line, and function information
    FLF m_kFLF;

#if defined(EE_MEMTRACKER_STACKTRACE)
    int m_stackSize;
    void* m_stack[EE_MEMSTACKTRACE_DEPTH];
#endif

#if defined(EE_MEMTRACKER_SNAPSHOT)
    /// The prior allocation unit in the active array.
    AllocUnit* m_pShapshotPrev;

    /// The next allocation unit in the active array.
    AllocUnit* m_pShapshotNext;
#endif

    inline void Reset();
};

/**
    A platform-independent wrapper class to handle memory tracking and
    debugging. There are four major areas of functionality provided by the
    memory tracker:

    Memory Debugging - Provide functionality to assist in tracking down common
    memory errors.

    Memory Leak Tracking - Provide functionality to detect and help correct
    leaked memory.

    Memory Logging - Provide functionality to understand an application's
    memory behavior over time.

    Memory Summary Statistics - Provide functionality to quickly get a snapshot
    of the memory behavior over time.

    Please see the notes for commentary on the supported functionality for
    the tracker.

    @note that while the MemTracker provides thread safety for itself and its
    internal allocator, all allocator classes should be responsible for their
    own thread-safety.

    @note Memory Debugging - The tracker provides several levels of debugging
    functionality to catch common memory errors. These errors are caught by
    using asserts. Should a user encounter one of the asserts, please read the
    comments surrounding the assert. The comment should provide useful clues
    about the source of the assert. The debugger can then be used to inspect
    the current AllocUnit for more information about the allocation.
    Additionally, there are several variables that can be used to help trap
    when certain memory errors occur once specific information is known about
    the memory.

    @note Memory Leaks - When the application exits, all currently active
    allocations will be reported. There are two formats for the report,
    output debug strings and an XML log file. These log file, stored as
    "Memory-Leaks.xml", can be viewed in a variety of packages. On the
    Windows platform, double-clicking the file will display the contents
    of the XML file filtered by the corresponding XSL stylesheet in your
    default web browser. Note that these logs can sometimes be very large
    and can take some time to load in Internet Explorer or Firefox. The debug
    strings will be visible if bOutputLeaksToDebugStream is set to true.
    In some packages, like Microsoft Developer Studio, double-clicking on the
    individual leak records in the output stream will open the code browser
    to the line in which the allocation occurred.

    @note Memory Logs - The tracker will write all allocation records to file
    as they are deallocated. These records, stored in "Memory-Overview.xml",
    can be viewed in a variety of packages. On the Windows platform,
    double-clicking the file will display the contents of the XML file
    filtered by the corresponding XSL stylesheet in your default web browser.
    Note that these logs can sometimes be very large and can take some time to
    load in Internet Explorer or Firefox.
*/
class EE_EFD_ENTRY MemTracker : public IAllocator
{
public:
    /**
        Creates a MemTracker.

        @param pkActualAllocator Perform all actual allocations.
        @param uiInitialSize Size of the initial pool of allocation tracking
            units
        @param uiGrowBy The growth factor of the pool of allocation units when
            no units are available.
        @param bAlwaysValidateAll If true, the tracker will test all allocation
            units for errors upon alloc, realloc, or free.
        @param bCheckArrayOverruns If true, the tracker will add
            sentinel bytes to the beginning and end of the allocation to
            guarantee that code does not stomp over the end of the array.
        @param bWriteToLog If false, memory tracking is enabled, but no memory
            logs are written.
        @param assertOutsideOfMain When true, the MemTracker will assert if an
            attempt is made to allocate memory outside of main. This flag is useful
            for identifying and removing pre-main allocations.
    */
    MemTracker(IAllocator* pkActualAllocator,
        bool bWriteToLog = false,
        unsigned int uiInitialSize = 65536,
        unsigned int uiGrowBy = 4096,
        bool bAlwaysValidateAll = false,
        bool bCheckArrayOverruns = true,
        bool assertOutsideOfMain = true);

    /// Destructor.
    virtual ~MemTracker();

    // Overridden virtual functions inherit base documentation and thus
    // are not documented here.
    virtual void* Allocate(size_t& stSize,
        size_t& stAlignment,
        MemHint kHint,
        MemEventType eEventType,
        const char* pcFile, int iLine, const char* pcFunction);
    virtual void Deallocate(void* pvMemory,
        MemEventType eEventType,
        size_t stSizeinBytes);
    virtual void* Reallocate(void* pvMemory, size_t& stSize,
        size_t& stAlignment,
        MemHint kHint,
        MemEventType eEventType,
        size_t stSizeCurrent,
        const char* pcFile,
        int iLine,
        const char* pcFunction);

    virtual bool TrackAllocate(
        const void* const pvMemory,
        size_t stSizeInBytes,
        MemHint kHint,
        MemEventType eEventType,
        const char* pcFile,
        int iLine,
        const char* pcFunction);

    virtual bool TrackDeallocate(
        const void* const pvMemory,
        MemEventType eEventType);

    virtual bool SetMarker(const char* pcMarkerType, const char* pcClassifier,
        const char* pcString);

    /// Called by the memory manager during Init()
    virtual void Initialize();

    /// Called by the memory manager during Shutdown()
    virtual void Shutdown();

    // Called by the memory manager during per-thread Init
    virtual void PerThreadInit();

    // Called by the memory manager during per-thread Shutdown
    virtual void PerThreadShutdown();

    virtual bool VerifyAddress(const void* pvMemory);

    /// Find the address of an allocation that contains pvMemory.
    virtual void* FindContainingAllocation(const void* pvMemory);

    // Summary statistics

    /// Tracks the current amount of memory allocated in bytes.
    size_t m_stActiveMemory;

    /**
        Tracks the maximum amount of memory (in bytes) used at any point in
        the past by the application. This corresponds to the "high water mark"
        for the application.
    */
    size_t m_stPeakMemory;

    /**
        Tracks the accumulated total amount of memory (in bytes) used by
        the application
    */
    size_t m_stAccumulatedMemory;

    /**
        Tracks the total amount of memory (in bytes) that has been allocated
        but still filled with the sentinel bytes when deallocated.
    */
    size_t m_stUnusedButAllocatedMemory;

    /// Tracks the current number of allocations that are active.
    size_t m_stActiveAllocationCount;

    /**
        Tracks the maximum number of allocations used at any point in the past
        by the application.
    */
    size_t m_stPeakAllocationCount;

    /// Tracks the accumulated number of allocations made by the application.
    size_t m_stAccumulatedAllocationCount;

    /**
        Tracks the current amount of memory (in bytes) used by the memory]
        tracking system. Note that this number is not included in
        m_stActiveMemory.
    */
    size_t m_stActiveTrackerOverhead;

    /**
        Tracks the maximum amount of memory (in bytes) used by the memory
        tracking system in the past. Note that this number is not included in
        m_stPeakMemory.
    */
    size_t m_stPeakTrackerOverhead;

    /**
        Tracks the total amount of memory (in bytes) used by the memory
        tracking system. Note that this number is not included in
        m_stAccumulatedMemory.
    */
    size_t m_stAccumulatedTrackerOverhead;

    /**
        Tracks the total amount of memory (in bytes) of external memory.
    */
    size_t m_stActiveExternalMemory; // in bytes

    /**
        Tracks the peak amount of memory (in bytes) of external memory.
    */
    size_t m_stPeakExternalMemory; // in bytes

    /**
        Tracks the accumulated total amount of memory (in bytes) of external memory.
    */
    size_t m_stAccumulatedExternalMemory; // in bytes

    /**
        Tracks the total number of active memory allocations of external memory.
    */
    size_t m_stActiveExternalAllocationCount;

    /**
        Tracks the peak number of memory allocations of external memory.
    */
    size_t m_stPeakExternalAllocationCount;

    /**
        Tracks the total amount of memory  of external memory over the app's lifetime.
    */
    size_t m_stAccumulatedExternalAllocationCount;

    /**
        Tracks the point in time as reported by GetCurrentTimeInSec when
        m_stPeakMemory was set to its current value.
    */
    double m_fPeakMemoryTime;

    /**
        Tracks the point in time as reported by GetCurrentTimeInSec when
        m_stPeakAllocationCount was set to its current value.
    */
    double m_fPeakAllocationCountTime;

    /// Determine the counter for the current allocation ID.
    inline size_t GetCurrentAllocationID() const;

    /// Find the allocation for the given memory.
    AllocUnit* FindAllocUnit(const void* pvMem) const;

    /// callback function called for active allocations.
    typedef void (*ReportActiveAllocUnit)(AllocUnit* pkActiveAllocUnit,
        IMemLogHandler* pLogHandler);

    void ReportActiveAllocations(ReportActiveAllocUnit pfnReportCallBack);

    /**
        Reset the counts on all summary stats. This can potentially be a
        hazardous operation and should be used with caution.
    */
    virtual void ResetSummaryStats();

    void OutputLeakedMemoryToDebugStream(bool bUseLog) const;
    void OutputAllocUnitToDebugStream(const AllocUnit* pkUnit) const;
    void OutputMemorySummaryToDebugStream() const;

    void OutputAllocUnitToLog(const AllocUnit* pkUnit, bool outputDebugString=false) const;

    void OutputActiveToDebugStream(const char* pcStringId, size_t stMinAllocID) const;

    /**
        Determine whether or not the tracker validates all of its internal
        allocation units upon allocate/deallocate/reallocate.
    */
    inline bool GetAlwaysValidateAll() const;

    /**
        Sets m_bAlwaysValidateAll
        @param bOn boolean value
    */
    inline void SetAlwaysValidateAll(bool bOn);

    /// Check to see if the tracker will try to detect memory overflows.
    inline bool GetCheckForArrayOverruns() const;

    /// Determine if the memory specified by an alloc unit is valid.
    bool ValidateAllocUnit(const AllocUnit* pkUnit) const;

    /// Validate all alloc units.
    bool ValidateAllAllocUnits() const;

    inline void SetWriteToLog(bool bOn);

    /**
        Function to allow the memory allocator to create an IMemLogHandler for logging
        memory allocations. This method will be called on the allocator after
        the MemManager has been constructed.

        The IMemHandler implementation used is defined in the implementation of
        InitializeMemoryLogHandler(). The method InitializeMemoryLogHandler() is explicitly
        defined as an extern to allow applications to specify a unique implementation of
        InitializeMemoryLogHandler(). This allows applications to specify the IMemHandler
        implementation used by MemTracker.
    */
    void CreateMemoryLogHandler();

#if defined(EE_MEMTRACKER_DETAILEDREPORTING)
    /**
        Associate a function with a specific allocation which can dump detailed information
        about the allocation in the event that it is leaked.
    */
    void SetDetailReportForAllocation(const void* pvMem, AllocUnit::pfnDetailMethod pfn);
#endif

    /**
        The tracker will output leaks to the debug stream if this
        boolean is true.
    */
    static bool ms_bOutputLeaksToDebugStream;

    /**
        The tracker will assert when the allocation unit's m_stAllocationID
        equals this value upon allocate/reallocate/deallocate.
    */
    static size_t ms_stBreakOnAllocID;

    /**
        The tracker will assert when the allocation unit's memory address
        equals this value upon allocate/reallocate/deallocate
    */
    static void* ms_pvBreakOnAllocRangeStart;

    /**
        The tracker will assert when the allocation unit's memory address
        equals this value upon allocate/reallocate/deallocate.
    */
    static void* ms_pvBreakOnAllocRangeEnd;

    /**
        The tracker will assert when the allocation unit's m_pcFunc equals
        this value upon allocate/reallocate.
    */
    static const char* ms_pcBreakOnFunctionName;

    /**
        The tracker will assert when the allocation unit's size equals this
        value.
    */
    static size_t ms_stBreakOnSizeRequested;

    /// @cond EMERGENT_INTERNAL
    void SetAllocatorAvailableStatus(bool bInsideOfMain);
    /// @endcond


    /// Accessor for the singleton instance of the MemTracker
    static MemTracker* Get();

#if defined(EE_MEMTRACKER_SNAPSHOT)
    /// Start or continue a snapshot. All allocations made while the snapshot is active will be
    /// tracked and outstanding allocations can then be displayed. Even after the snapshot has
    /// completed the allocations from the snapshot will continue to be tracked and you can dump
    /// those that remain at any time until ClearShapshot is called.
    void BeginSnapshot();

    /// Stop collecting allocations in the snapshot. This will not clear the snapshot, it will
    /// simply stop adding new allocations to the snapshot. You may later call BeginSnapshot to
    /// add additional allocations to the existing snapshot.
    void EndSnapshot();

    /// Clear all allocation units from the snapshot.
    void ClearSnapshot();

    /**
        Create a memory report detailing the outstanding allocations from the snapshot. Only those
        allocations that have not been freed are displayed.

        @param pszSuffix A name associated with the snapshot to generate. This is passed on to the
            IMemLogHandler implementation to deal with as appropriate for that handler. For example,
            the default implementation, XMLMemLogHandler, appends this string to the resulting log
            file name.
    */
    void ReportSnapshotAllocations(const char* pszName = "");
#endif

protected:
    static const char* SourceFileStripper(const char *pcSourceFile);

    void** m_ppManagedAllocUnitAddresses;
    size_t* m_pstManagedAllocUnitSizes;
    efd::UInt32 m_uiManagedAllocUnitCount;
    efd::UInt32 m_uiManagedAllocUnitMaxSize;

    void GrowReservoir();
    void InsertAllocUnit(AllocUnit* pkUnit);
    void RemoveAllocUnit(AllocUnit* pkUnit);

    inline bool CanAllocateNow();

    static unsigned int AddressToHashIndex(const void* pvAddress);
    static const char* FormatForXML(const char* pcInString);
    void MemoryFillWithPattern(void* pvMemory, size_t stSizeinBytes);
    size_t MemoryBytesWithPattern(void* pvMemory, size_t stSizeinBytes) const;

    // Note that MemoryFillForArrayOverrun and CheckForArrayOverrun
    // modify the address passed in to reflect the sentinel characters
    // before the allocation. PadForArrayOverrun will adjust the size
    // of an allocation to reflect the sentinel characters.
    void MemoryFillForArrayOverrun(void*& pvMemory, size_t stAlignment,
        size_t stSizeOriginal);
    bool CheckForArrayOverrun(void*& pvMemory, size_t stAlignment,
        size_t stSizeOriginal) const;
    size_t PadForArrayOverrun(size_t stAlignment,
        size_t stSizeOriginal);

    static bool IsInsideBreakRange(const void* pvMem, size_t stSize);

    static const unsigned int ms_uiHashBits = 12;
    static const unsigned int ms_uiHashSize = 1 << ms_uiHashBits;

    bool m_bAlwaysValidateAll;
    AllocUnit* m_pkReservoir;
    size_t m_stReservoirGrowBy;
    AllocUnit** m_ppkReservoirBuffer;
    size_t m_stReservoirBufferSize;
    AllocUnit* m_pkActiveMem[ms_uiHashSize];

    int m_iLoggerLeakChannel;
    int m_iLoggerCompleteChannel;

    IMemLogHandler* m_pkMemLogHandler;
    IAllocator* m_pkActualAllocator;
    size_t m_stCurrentAllocID;

    size_t m_stIgnoreRangeStart;
    size_t m_stIgnoreRangeEnd;

    bool m_bCheckArrayOverruns;
    unsigned char m_ucFillChar;
    bool m_bWriteToLog;

    static MemTracker* ms_pkTracker;
    CriticalSection m_kCriticalSection;

    bool m_insideOfMain;
    bool m_assertOutsideOfMain;

#if defined(EE_MEMTRACKER_SNAPSHOT)
    bool m_bSnapshotActive;
    AllocUnit* m_pSnapshotHead;
#endif

};

} // end namespace efd

#include <efd/MemTracker.inl>

#endif // #ifndef EE_MEMTRACKER_H
