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
#ifndef EE_TIMETYPE_H
#define EE_TIMETYPE_H

#include <efd/efdLibType.h>
#include <efd/UniversalTypes.h>
#include <efd/MemObject.h>
#include <efd/efdClassIDs.h>

// Handle time by supporting different clock classes that can behave in different ways.
#if defined(_WINBASE_) && defined(GetCurrentTime)
#undef GetCurrentTime
#endif

namespace efd
{


/// @name Time functions from TimeType.h

//@{

/**
    TimeType is a reasonably accurate representation of time, measured in fractional seconds.
*/
typedef efd::Float64 TimeType;

/**
    Set the time at which the application starts in relation to system clock.

    Reset the base time used by the system, with an optional offset.  Subsequent calls to
    efd::GetCurrentTimeInSec will return fOffset + the number of seconds elapsed since the
    last call to efd::SetInitialTimeInSec(fOffset).

    Applications that must run for long durations can avoid reductions in floating point
    precision by calling this function periodically to reset time to a range closer to
    zero.  It is recommended that the function be called during level or mode transitions
    of an application to avoid discontinuities in update times for animated objects.
*/
EE_EFD_ENTRY void SetInitialTimeInSec(float offsetInSeconds = 0.0f);

/**
    Get the current time in seconds since the application started, or since the last
    time that efd::SetInitialTimeInSec() was called.
*/
EE_EFD_ENTRY TimeType GetCurrentTimeInSec();

//@}

/**
    A clock interface for managing the flow of time in a ServiceManager-based application.
*/
class EE_EFD_ENTRY IClock : public MemObject
{
public:
    /// Virtual destructor.
    virtual ~IClock();

    /// Get the time for the current update of the clock.
    virtual TimeType GetCurrentTime() const = 0;

    /// Called by the ServiceManager once per tick to update the internal time of the clock.
    virtual void Update(TimeType serviceFrameTime) = 0;

    /// Simple identifier for the clock class type.
    virtual ClassID GetClockClassID() const = 0;
};

/**
    A helper clock class based on real time as exposed by the operating system.

    The time will typically be expressed as seconds since some arbitrary point in history,
    typically midnight 1/1/1970.  This class may have lower precision than other clocks,
    in some cases as low as 1 second precision (returns a value in integral seconds).
*/
class EE_EFD_ENTRY RealTimeClock
{
public:
    /// Get the current real time from the operating system.
    static TimeType GetCurrentTime();
};

/**
    A clock based on high precision counters (QueryPerformanceCounter on Win32) for accessing
    "real time" since some arbitrary point in history (such as whenever the hardware last booted
    or whenever the program initialized). The units are seconds.

    Synchronization between multiple machines is supported, but not provided, so values should not
    be compared between multiple processes unless you use the synchronization features.  Also,
    unless you synchronize to some fixed point in Calendar Time, you should not persist the
    resulting absolute values (consider persisting a delta from "now" instead, for example).
*/
class EE_EFD_ENTRY HighPrecisionClock : public IClock
{
public:
    /// Constructor.
    inline HighPrecisionClock(TimeType i_offset = 0.0);

    /// Get the current time.
    virtual TimeType GetCurrentTime() const;

    /// Set synchronization offset as part of synchronization between multiple machines.
    void SetSynchronizationOffset(TimeType i_offset);

    /// Update for this clock does nothing.  GetCurrentTime always returns the current time.
    virtual void Update(TimeType serviceFrameTime);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::ClassID GetClockClassID() const;

protected:
    // Synchronization offset.
    TimeType m_syncOffset;
};


/// A HighPrecision clock that only advances when told to update. The units are seconds.
class EE_EFD_ENTRY StepHighPrecisionClock : public HighPrecisionClock
{
public:
    /// Constructor.
    inline StepHighPrecisionClock(TimeType offset = 0.0);

    /// Get the current time.
    virtual TimeType GetCurrentTime() const;

    /// Compute the current time.
    inline TimeType ComputeCurrentTime() const;

    /// Advance the clock.  Ignores serviceFrameTime and uses real time.
    virtual void Update(TimeType serviceFrameTime = 0.0);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::ClassID GetClockClassID() const;

protected:
    // Current time.
    TimeType m_currentTime;
};

}   // End namespace efd.

#include <efd/TimeType.inl>

#endif  // EE_TIMETYPE_H

