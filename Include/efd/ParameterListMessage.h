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
#ifndef EE_PARAMETERLISTMESSAGE_H
#define EE_PARAMETERLISTMESSAGE_H

#include <efd/IMessage.h>
#include <efd/efdClassIDs.h>
#include <efd/ParameterList.h>

namespace efd
{

/**
    A message class that can be used for fast prototyping. Like StreamMessage only:
        1) type safe
        2) supports named parameters
        3) supports random access
*/
class EE_EFD_ENTRY ParameterListMessage : public IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(ParameterListMessage, efd::kCLASSID_ParameterListMessage, IMessage);
    EE_DECLARE_FORWARDED_CONCRETE_REFCOUNT(IMessage);
    /// @endcond

public:
    ParameterListMessage();

    /// Virtual destructor.
    virtual ~ParameterListMessage();

    /**
        Stream-style operator for legacy compatibility with StreamMessage.
    */
    template<typename T>
    const ParameterListMessage& operator >>(T& data) const;

    /**
        Stream-style operator for legacy compatibility with StreamMessage:
    */
    template<typename T>
    ParameterListMessage& operator <<(const T& data);

    /// Accessor for the ParameterList
    //@{
    inline efd::ParameterList& GetParameters();
    inline const efd::ParameterList& GetParameters() const;
    //@}

    /// @name ParameterList methods
    /// Some of the methods on the contained parameter list are exposed for convenience. To call
    /// other methods use GetParameters to access the underlying list
    //@{
    /**
        Adds a new unnamed parameter to the end of the parameter list.

        @param parameter The data being added
        @return The index at which the data was added, or -1 on error
    */
    template<typename T>
    efd::SInt32 AddParameter(const T& parameter);

    /**
        Adds a new named parameter to the end of the parameter list.

        @param pszName The name of this data item
        @param parameter The data being added
        @return The index at which the data was added, or -1 on error
    */
    template<typename T>
    efd::SInt32 AddParameter(const efd::utf8string& pszName, const T& parameter);

    /// Get the number of parameters in the list
    inline efd::UInt32 GetSize() const;

    /**
        Read a parameter from the list.

        @param[in] i_index The parameter to read
        @param[out] o_result The resulting value
        @return A ParameterResult indicating the result
    */
    template<typename T>
    ParameterResult GetParameter(efd::SInt32 i_index, T& o_result) const;

    /**
        Read a parameter from the list.

        @param[in] i_index The parameter to read
        @param[out] o_result The resulting value
        @return A ParameterResult indicating the result
    */
    template<typename T>
    ParameterResult GetParameter(efd::UInt32 i_index, T& o_result) const;

    /**
        Read a parameter from the list by name.

        @param[in] i_pszName The parameter to read
        @param[out] o_result The resulting value
        @return A ParameterResult indicating the result
    */
    template<typename T>
    ParameterResult GetParameter(const char* i_pszName, T& o_result) const;
    //@}

    /// Resets the read cursor of this message.
    inline void Reset() const;

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void Serialize(efd::Archive& ar);

protected:
    /// The parameter storage
    efd::ParameterList m_params;

    /// To act like legacy DataStream we have to store our own iterator:
    mutable efd::UInt32 m_nextIndex;
};

/// Define a smart pointer for the StreamMessage class.
typedef efd::SmartPointer<ParameterListMessage> ParameterListMessagePtr;

} // end namespace efd.

#include <efd/ParameterListMessage.inl>

#endif  // EE_PARAMETERLISTMESSAGE_H
