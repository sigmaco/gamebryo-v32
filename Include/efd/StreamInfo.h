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
#ifndef EE_STREAMINFO_H
#define EE_STREAMINFO_H

#include <efd/IBase.h>
#include <efd/UniversalTypes.h>
#include <efd/utf8string.h>
#include <efd/efdLibType.h>

namespace efd
{

/**
    Information about a data stream.

    The StreamInfo class encapsulates information used when transferring data streams over the
    wire.
*/
class EE_EFD_ENTRY StreamInfo : public MemObject
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CONCRETE_REFCOUNT
    /// @endcond

public:

    /// List of supported endian types.
    enum Endian
    {
        /// Big Endian (non-intel architecture, typically).
        Endian_Big = 0,

        /// Little Endian (Intel machines).
        Endian_Little,

        /// Network byte order is the same as Little Endian.
        Endian_NetworkOrder = Endian_Little,
    };

    /// Constructor.
    StreamInfo();

    /// @name Stream support methods.
    //@{
    /**
        Set the endianness for the associated stream.

        @param eType Endian setting for the stream.
    */
    inline void SetEndian(Endian eType);

    /**
        Get the endianness for the associated stream.

        @return Endian setting for the stream.
    */
    inline Endian GetEndian() const;

    /**
        Set the variant (state ID) for this stream.

        Variants are a state enumeration that can be used to differentiate a stream condition (in
        packing/unpacking).

        @param var Variant setting for the stream.
    */
    inline void SetVariant(efd::SInt32 var);

    /**
        Get the variant (state ID) for this stream.

        Variants are a state enumeration that can be used to differentiate a stream condition (in
        packing/unpacking).

        @return Variant setting for the stream.
    */
    inline efd::SInt32 GetVariant() const;

    /**
        Set the version ID for this stream.

        @param version Version ID for the stream.
    */
    inline void SetVersion(efd::UInt32 version);

    /**
        Get the version ID for this stream.

        @return Version ID for the stream.
    */
    inline efd::UInt32 GetVersion() const;
    //@}

    /// Determine if the host is little Endian.
    static inline bool IsHostLittleEndian();

    /// Determine if Endian swapping is needed.
    inline bool NeedsSwap() const;

protected:
     /// Protected destructor to make sure that one can't delete a StreamInfo pointer directly.
     ~StreamInfo();

private:
    /// Variant for use with stream.
    efd::SInt32 m_variant;

    /// Endianness of this stream.
    Endian m_endian;

    /// Version number of this stream.
    efd::UInt32 m_version;
};

/// A smart pointer for the StreamInfo class.
typedef efd::SmartPointer<StreamInfo> StreamInfoPtr;


}   // End namespace efd.

#endif  // EE_STREAMINFO_H
