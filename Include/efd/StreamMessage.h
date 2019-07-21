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
#ifndef EE_STREAMMESSAGE_H
#define EE_STREAMMESSAGE_H

#include <efd/IMessage.h>
#include <efd/efdClassIDs.h>

namespace efd
{

/**
    A message class that can be used for fast prototyping.

    StreamMessage can be used to quickly prototype messages without the need to create a custom
    message type and implement Serialize.  The drawback to this is that an implementation detail of
    what order and what the data is stored in the message must be known everywhere the message is
    sent and received.

    @note This class has been replaced by ParameterMessage which offers the addition of named
        parameters, random access of parameters, and type safe parameters. Consider upgrading from
        StreamMessage to ParameterMessage.
*/
class EE_EFD_ENTRY StreamMessage : public IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(StreamMessage, efd::kCLASSID_StreamMessage, IMessage);
    /// @endcond

public:
    /// Creates an archive in packing mode
    StreamMessage();

    /// Virtual destructor.
    virtual ~StreamMessage();

    /// Pack data into the message, message must be in packing mode
    template<typename T>
    StreamMessage& operator << (const T& data)
    {
        Serializer::SerializeConstObject(data, m_archive);
        return *this;
    }

    /// Read data from the message, message must be in unpacking mode
    template<typename T>
    const StreamMessage& operator >> (T& data) const
    {
        Serializer::SerializeObject(data, m_archive);
        return *this;
    }

    /// Resets the archive to the beginning and converts the archive to Unpacking mode if needed.
    void ResetForUnpacking() const;

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void Serialize(efd::Archive& ar);

    /// Sets the message to unpack from the given buffer. The buffer becomes shared between the
    /// caller and the Archive within this message.
    inline void SetBuffer(const efd::SmartBuffer& i_buffer);

    /// Access the archive inside the message
    //@{
    inline efd::Archive& GetArchive();
    inline efd::Archive& GetArchive() const;
    //@}

    /**
        Get the total number of bytes this stream uses.

        This count does not include padded space that is not yet allocated.

        @return Number of bytes used by this stream.
    */
    inline efd::UInt32 GetBufferSize() const;

protected:
    mutable efd::Archive m_archive;
};

/// Define a smart pointer for the StreamMessage class.
typedef efd::SmartPointer<StreamMessage> StreamMessagePtr;

} // end namespace efd.

#include <efd/StreamMessage.inl>

#endif  // EE_STREAMMESSAGE_H
