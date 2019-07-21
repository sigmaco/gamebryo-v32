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
#ifndef EE_GameTimeClock_h
#define EE_GameTimeClock_h

#include <efd/TimeType.h>
#include <egf/egfClassIDs.h>
#include <egf/egfLibType.h>

namespace egf
{

    /**
        This class is the clock used by the Scheduler to maintain GameTime.  All behavior related
        times are GameTime times which use this clock.
    */
    class EE_EGF_ENTRY GameTimeClock : public efd::IClock
    {
    public:
        /// Constructor
        GameTimeClock(efd::TimeType currentRealTime = 0.0);

        /// Get the time for the current update of the clock.
        virtual efd::TimeType GetCurrentTime() const;

        /// Returns the delta amount by which the clock was updated on the last Update call.  This
        /// will return 0.0 if the clock was paused during the last update.  The value is only
        /// changed by calls to Update, calling SetCurrentTime will not change the last delta.
        efd::TimeType GetLastDelta() const;

        /** Advance the clock.  Based on the current mode, this either advances by a fixed delta
            (fixed delta mode) or advances by the amount of real time that has passed (real-time
            mode), possibly modified by a scale factor.  By default, real-time mode is used.
            @param serviceFrameTime The current real-time as reported by the ServiceManager
        */
        virtual void Update(efd::TimeType serviceFrameTime);

        /**
            Attempts to set the current time.  Will be ignored if the provided value would cause
            time to move backwards.
            @param currentTime The current time
        */
        bool SetCurrentTime(efd::TimeType currentTime);

        /// Pause the advancement of GameTime.  Every call to pause must be matched with a call to
        /// Resume.  You can pause multiple times in a row so long as you eventually resume an
        /// equal number of times.
        void Pause();

        /// Test if the clock is currently paused
        bool IsPaused() const;

        /// Start moving the clock forward again.
        void Resume();

        /**
            Enter "fixed delta" mode instead of "real-time" mode, on each update of the clock
            GameTime will advance by the provided delta regardless of how much real-time has
            passed.  This mode can help with debugging so that you can slowly step through the
            code.
            @param deltaPerTick The number of seconds to advance the clock on each Update
        */
        void UseFixedDeltaMode(efd::TimeType deltaPerTick);

        /**
            Enter "real-time" mode instead of "fixed delta" mode.  Real-time mode is the default
            clock mode, in this mode each update will advance the clock based on the passage of
            time measured by the ServiceManager's high precision clock.
        */
        void UseRealTimeMode();

        /**
            Scale the passage of time relative to real time.  "scale" must be greater than zero
            as time can never move backwards.  The scale only applies when "real-time" mode is
            active.
            @param scale A scale factor which must be greater than zero.  Using a scale of one
                will advance the clock at real time.
        */
        bool SetTimeScale(efd::Float64 scale);

        /**
            Prevent time from advancing by more than the provided delta.  This prevents large
            time jumps during slow frames, for example when you are debugging the program.  The
            default value for the maxDelta is 0.25 seconds.  The maximum delta only applies when
            "real-time" mode is active.
            @param delta The maximum time in seconds
        */
        bool SetMaxDelta(efd::Float64 delta);

        /// Get the class id for a game clock, which is kCLASSID_GameTimeClock
        virtual efd::ClassID GetClockClassID() const;

    protected:
        /// Given m_currentTime and m_realTimeScale, compute the delta from our real time clock
        /// (m_realTimeDelta) needed so that the next call to Update will advance time correctly.
        void ComputeDelta();

        /// Helper to read from the real time clock.
        efd::TimeType GetRealTime();

        /// The most recently computed game time
        efd::TimeType m_currentTime;
        /// The most recently provided 'real time' as supplied in the last call to Update
        efd::TimeType m_realTime;
        /// The amount by which m_currentTime changed on the last Update call
        efd::TimeType m_lastDelta;
        /// The maximum amount by which m_currentTime will change during an Update call.  This can
        /// be used to prevent time from jumping during slow frames (for example, if you are
        /// debugging the program and spend several minutes at a break point).
        efd::TimeType m_maxDelta;
        /// Counter of how many times the clock has been paused.  The clock can be paused
        /// multiple times and will not resume until it has been resumed the same number of times.
        efd::UInt32 m_pauseCount;

        /// True if the clock is using fixed delta mode
        bool m_useFixedDelta;
        /// When in fixed delta mode, game time advances by this amount on every Update call
        /// regardless of how much real time has advanced.
        efd::TimeType m_fixedDelta;

        /// An offset value used to adjust real time.  When the clock is paused and then resumed
        /// this delta will increase to subtract out the time spent paused.
        efd::TimeType m_realTimeDelta;
        /// GameTime clock can be scaled to run faster or slower than 'real time'
        efd::Float64 m_realTimeScale;
    };

} // end namespace egf

#endif // EE_GameTimeClock_h
