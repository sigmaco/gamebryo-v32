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
#ifndef EE_PROCESSORAFFINITY_H
#define EE_PROCESSORAFFINITY_H

#include <efd/efdLibType.h>
#include <efd/UniversalTypes.h>

namespace efd
{

/**
    A platform-independent wrapper class for setting processor affinities.
    NiProcessorAffinity supports both an ideal processor and a processor
    affinity mask. Note that different platforms may only support one of
    these methods for specifying target processors.
*/

class EE_EFD_ENTRY ProcessorAffinity
{
public:


    /// @name ProcessorAffinity::Processor
    //@{

    /// ProcessorAffinity::Processor is an enumeration with the following values.
    enum Processor
    {
        /**
            Assigned a single bit from bit 0 to 31, these values map directly
            to the 0th through 31st processor on the system
        */

        PROCESSOR_0                     = 0x00000001,
        PROCESSOR_1                     = 0x00000002,
        PROCESSOR_2                     = 0x00000004,
        PROCESSOR_3                     = 0x00000008,
        PROCESSOR_4                     = 0x00000010,
        PROCESSOR_5                     = 0x00000020,
        PROCESSOR_6                     = 0x00000040,
        PROCESSOR_7                     = 0x00000080,
        PROCESSOR_8                     = 0x00000100,
        PROCESSOR_9                     = 0x00000200,
        PROCESSOR_10                    = 0x00000400,
        PROCESSOR_11                    = 0x00000800,
        PROCESSOR_12                    = 0x00001000,
        PROCESSOR_13                    = 0x00002000,
        PROCESSOR_14                    = 0x00004000,
        PROCESSOR_15                    = 0x00008000,
        PROCESSOR_16                    = 0x00010000,
        PROCESSOR_17                    = 0x00020000,
        PROCESSOR_18                    = 0x00040000,
        PROCESSOR_19                    = 0x00080000,
        PROCESSOR_20                    = 0x00100000,
        PROCESSOR_21                    = 0x00200000,
        PROCESSOR_22                    = 0x00400000,
        PROCESSOR_23                    = 0x00800000,
        PROCESSOR_24                    = 0x01000000,
        PROCESSOR_25                    = 0x02000000,
        PROCESSOR_26                    = 0x04000000,
        PROCESSOR_27                    = 0x08000000,
        PROCESSOR_28                    = 0x10000000,
        PROCESSOR_29                    = 0x20000000,
        PROCESSOR_30                    = 0x40000000,
        PROCESSOR_31                    = 0x80000000,

        // Xenon processors
        /**
        An Xbox 360 specific processor enumeration that maps to the
        first hardware thread on the first core.
        */
        PROCESSOR_XENON_CORE_0_THREAD_0 = 0x00000001,
        /**
        An Xbox 360 specific processor enumeration that maps to the
        second hardware thread on the first core.
        */
        PROCESSOR_XENON_CORE_0_THREAD_1 = 0x00000002,
        /**
        An Xbox 360 specific processor enumeration that maps to the
        first hardware thread on the second core.
        */
        PROCESSOR_XENON_CORE_1_THREAD_0 = 0x00000004,
        /**
        An Xbox 360 specific processor enumeration that maps to the
        second hardware thread on the second core.
        */
        PROCESSOR_XENON_CORE_1_THREAD_1 = 0x00000008,
        /**
        An Xbox 360 specific processor enumeration that maps to the
        first hardware thread on the third core.
        */
        PROCESSOR_XENON_CORE_2_THREAD_0 = 0x00000010,
        /**
        An Xbox 360 specific processor enumeration that maps to the
        second hardware thread on the third  core.
        */
        PROCESSOR_XENON_CORE_2_THREAD_1 = 0x00000020,

        /// Assigned the value of 0xFFFFFFFF this mask represents all processors.
        PROCESSOR_DONT_CARE             = 0xFFFFFFFF
    };

    //@}

    /// @name Constructors
    //@{

    /**
    Creates an ProcessorAffinity object with an ideal processor
    and an affinity of PROCESSOR_DONT_CARE.
    */
    ProcessorAffinity();
    /// Creates an ProcessorAffinity object with members fully qualified and initialized.
    ProcessorAffinity(Processor idealProcessor, efd::UInt32 affinityMask);

    //@}

    /// @name Supported Member Functions
    //@{

    /**
    Get the processor affinity mask which should be an OR'd set of the Processor enumeration above.
    */
    inline efd::UInt32 GetAffinityMask() const;

    /**
    Set the processor affinity mask which should be an OR'd set of the Processor enumeration above.
    */
    inline void SetAffinityMask(efd::UInt32 affinityMask);


    /// Get the ideal processor.
    Processor GetIdealProcessor() const;
    /// Set the ideal processor.
    inline void SetIdealProcessor(Processor processor);

    //@}



private:
    Processor m_idealProcessor;
    unsigned int m_affinityMask;
};

}

#include <efd/ProcessorAffinity.inl>

#endif
