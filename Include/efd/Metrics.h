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
#ifndef EE_METRICS_H
#define EE_METRICS_H

// Define winsock, etc properly before including metrics headers.
#include <efd/OS.h>

#if defined(EE_ENABLE_METRICS_LOGGING) && !defined(EE_DISABLE_LOGGING)

    #include <efd/UniversalTypes.h>
    #include <efd/efdLibType.h>
    #include <efd/ILogger.h>

    namespace efd
    {
        EE_EFD_ENTRY void LogMetric(efd::UInt16 module, const char* metric, efd::SInt32 data);
        EE_EFD_ENTRY void LogMetric(efd::UInt16 module, const char* metric, efd::UInt32 data);
        EE_EFD_ENTRY void LogMetric(efd::UInt16 module, const char* metric, efd::SInt64 data);
        EE_EFD_ENTRY void LogMetric(efd::UInt16 module, const char* metric, efd::UInt64 data);
        EE_EFD_ENTRY void LogMetric(efd::UInt16 module, const char* metric, efd::Float64 data);
    } // end namespace efd

    // These hooks are for profiling; they are disabled for simple metrics logging
    #define METRICS_INIT(config)
    #define METRICS_TICK()
    #define METRICS_DEINIT()
    #define METRICS_STANDARD_FILE_INIT(filename, processname)

    /**
       Basic metrics probe macro. Writes a timestamped entry to the metrics logfile with the probe
       name and an arbitrary data value.
    */
    #define EE_LOG_METRIC(module, probeName, data) \
        efd::LogMetric(module, probeName, data);

    /**
        Tick off an instance of a probe, writing an entry to the metrics log with a value of 1.
    */
    #define EE_LOG_METRIC_COUNT(module, probeName) \
        EE_LOG_METRIC(module, probeName, 1)

    /**
        Increment a running tally counter. Functionally, this is the same as METRICS_PROBE_COUNT;
        however, this probe is intended to be paired with a METRICS_PROBE_DECREMENT on the same
        probe name that happens elsewhere in the code.
    */
    #define EE_LOG_METRIC_INCREMENT(module, probeName) \
        EE_LOG_METRIC(module, probeName, 1)

    /**
        Decrement a running tally counter. Meant to be paired with a METRICS_PROBE_INCREMENT.
    */
    #define EE_LOG_METRIC_DECREMENT(module, probeName) \
        EE_LOG_METRIC(module, probeName, -1)

    /**
       Same as METRICS_PROBE_METRIC, except that it allows the probe name to include printf-style
       formatting strings and a list of arguments to be inserted. Note that the nameWithArgs param
       must be enclosed in parentheses for the macro to expand correctly.

       All the subsequent probes follow the same structure; otherwise they correspond to their
       counterparts above.
    */
    #define EE_LOG_METRIC_FMT(module, nameWithArgs, data) \
        EE_LOG_METRIC(module, (const char*)efd::PrintfHelper nameWithArgs, data)

    #define EE_LOG_METRIC_COUNT_FMT(module, nameWithArgs) \
        EE_LOG_METRIC_FMT(module, nameWithArgs, 1);

    #define EE_LOG_METRIC_INCREMENT_FMT(module, nameWithArgs) \
        EE_LOG_METRIC_COUNT_FMT(module, nameWithArgs)

    #define EE_LOG_METRIC_DECREMENT_FMT(module, nameWithArgs) \
        EE_LOG_METRIC_FMT(module, nameWithArgs, -1)

    // Conditionally include code (such as variable declarations needed for a probe to display a
    // computed result)
    #define METRICS_ONLY(code) code

#else

    #define EE_LOG_METRIC(module, probeName, data)
    #define EE_LOG_METRIC_COUNT(module, probeName)
    #define EE_LOG_METRIC_INCREMENT(module, probeName)
    #define EE_LOG_METRIC_DECREMENT(module, probeName)

    #define EE_LOG_METRIC_FMT(module, nameWithArgs, data)
    #define EE_LOG_METRIC_COUNT_FMT(module, nameWithArgs)
    #define EE_LOG_METRIC_INCREMENT_FMT(module, nameWithArgs)
    #define EE_LOG_METRIC_DECREMENT_FMT(module, nameWithArgs)

    #define METRICS_INIT(config)
    #define METRICS_TICK()
    #define METRICS_DEINIT()
    #define METRICS_STANDARD_FILE_INIT(filename, processname)

    #define METRICS_ONLY(code)

#endif // defined(EE_ENABLE_METRICS_LOGGING) && !defined(EE_DISABLE_LOGGING)

#endif // EE_METRICS_H
