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
#ifndef EE_IMESSAGE_H
#define EE_IMESSAGE_H

#include <efd/SystemLogger.h>
#include <efd/MessageFactory.h>
#include <efd/efdLogIDs.h>
#include <efd/IStreamable.h>

namespace efd
{
///
/// Messages are used for interaction between two systems that need to remain loosely coupled.
/// One system can create and send a message without knowing that the second system exists. When
/// first system changes, there is much less chance that the second system must change, or even
/// recompile.
///
/// Messages can be sent between processes, when they are addressed using a Category. This requires
/// a Message to be able to be streamed into/out of a binary buffer in a network neutral manner.
///
/// Messages can be sent thread-safely. Messages are handled (their handler code is executed) by
/// the MessageService and always on the main thread that is running the SystemServiceManager.
///
/// Messages are handled in a type safe manner. Each type of message must be implemented as a class
/// that has a unique ClassID. For message types that can be reused for more than one purpose
/// the "MessageWrapper" template is used to morph the ClassID into one that is logically unique.
/// A Message is handled in one of a number of ways (in preferred order):
///
/// 1) Register a class method and instance pointer that will be invoked when a message of the
///    selected class arrives.
///
/// 2) Create and register a MessageHandler that either invokes a selected method or implements
///    a concrete handler function.
///
/// 3) Derive a class from IMessageTarget and implement a concrete handler function. This last
///    and non-preferred approach is the only one that may require the use of a switch statement
///    across message class types.
///
/// There are several helper Macros and templates that are designed to make creating and handling
/// messages very simple. Ideally this will require a single line of code for any operation.
///
/// @name Constants from IMessage.h
//@{

/// This is a special category used by MessageService to send local messages.
static const efd::Category kCAT_LocalMessage =
    Category(UniversalID::ECU_Any, kNetID_Any, kBASEID_LocalMessage);

/// This is a special category used to indicate an invalid setting.
static const efd::ClassID k_invalidMessageClassID = 0;
//@}


/**
    \brief The base-level message class used as the prototype for other message classes.

    IMessage is an interface. It must be derived from before being used. Derived classes must
    properly use Foundation RTTI to provide a unique ClassID.

    A Message can be transmitted over the network, so must be able to be streamed. When it arrives
    it must be able to be Factoried, requiring the application to register a Factory method.

    IMessage has rich debugging support. Each Message instance will have a unique identifier
    (counter) assigned to it as it is being transmitted. This allows the developer to use the
    Emergent logging system to track a message as it moves around the system. There are several
    settings available to explicitly log or break execution as a message passes certain phases.
    This can be done on a per instance basis. The class id system and message-specific support
    allows rich text logging of messages.
    All messaged sent via MessageService must be subclassed from IMessage. The IMessage interface
    is use throughout the system to abstract specific message implementations.

    IMessage instances are instantiated using EE_NEW. To facilitate delivery, consumers of the
    message must register a factory method with the Service Manager that knows how to construct
    a new message. This is then used in the messaging layer when receiving messages of a particular
    class. These behaviors are encapsulated in the IMessageWrapper and
    RegisterMessageWrapperFactory macros defined below.

    The following sequence shows how to successfully create a new message class, and
    send / receive an IMessage base message.

    -# Subclass IMessage and give your new message class a unique ClassID.
    -# Implement Serialize to marshal the contents of your message to an Archive.
    -# Instantiate an instance of your message class using EE_NEW.
    -# Use one of the MessageService 'Send' methods to deliver the message to the Message Service.
    -# On the receiving end, register a Message Factory for you message ClassID with the Service
       Manager so it knows how to demarshal your message.
    -# Create a IMessageTarget instance that receives the incoming message and register this with
       the MessageService giving it the message ClassID as an identifier.
    -# Messages received are then routed to your IMessageHandler.
    .

    The message, once delivered to the Message Service, is then owned by the Message Service. The
    receiver is not responsible for deallocation and can depend on memory being freed at the
    network layer.
 */
class EE_EFD_ENTRY IMessage : public IStreamable
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(IMessage, kCLASSID_IMessage, IStreamable);
    EE_DECLARE_CONCRETE_ATOMIC_REFCOUNT;
    /// @endcond

public:

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    void Serialize(efd::Archive& io_ar);

    /**
        A set of debugging flags that enables the sender of the message to trace the message
        as it works its way through the system. These flags can be combined using the or (|)
        operator.
    */
    enum MessageDebugFlags
    {
        // note: the order of these enum values must match the structure below.

        /** Break when MessageServer considers delivery of this message.  Will break even
             if no handlers are present. */
        mdf_BreakOnFirstLocalDelivery   = 0x00000001,
        /** Break in MessageService before calling each handler. */
        mdf_BreakOnEachLocalDelivery    = 0x00000002,
        /** Break when NetService considers delivery of this message.  Will break even
             if no handlers are present. */
        mdf_BreakOnFirstNetDelivery     = 0x00000004,
        /** Break in NetService before passing this message to each handler. */
        mdf_BreakOnEachNetDelivery      = 0x00000008,
        /** Break in recv thread when adding this to the delivery queue. */
        mdf_BreakOnNetQueue             = 0x00000010,
        /** Break when this message is read off the wire. */
        mdf_BreakOnNetReceive           = 0x00000020,
        /** Break before this message is sent out on a transport. */
        mdf_BreakOnNetSend              = 0x00000040,
        /** Break when posted added to the MessageService. */
        mdf_BreakOnLocalPost            = 0x00000080,
        /** Break when posted with a delay to the MessageService. */
        mdf_BreakOnDelayedLocalPost     = 0x00000100,
        /** Only print trace statements, do not break */
        mdf_TraceOnly                   = 0x00000200,
    };

    /// Check if a debug flag or set of flags is set on this message
    bool CheckDebugFlag(efd::UInt32 i_flag) const;

    /// Get all of the set debug flags for this message.
    efd::UInt32 GetDebugFlags() const;

    /// Set the debug flags for this message.
    void SetDebugFlags(efd::UInt32 i_flags) const;

    /// The unique id (message instance counter) that can be used to track a message instance as it
    /// moves around the system. This is intended for debugging, not core system logic.
    efd::UInt32 GetUniqueIdentifier() const;

    /// A message sub-class specific text description/dump of the message for use in
    /// logging/debugging.
    virtual efd::utf8string GetDescription() const;

    /// A Category that can be used to send a reply message to the logical process that originally
    /// sent this message. Local messages don't contain the space; this returns a default value.
    virtual const efd::Category& GetSenderCategory() const;

    /// The Category that is used to route this message. Local messages use a default value.
    virtual const efd::Category& GetDestinationCategory() const;

    /// Utility method to convert a message's classID into a human readable string.
    static efd::utf8string ClassIDToString(efd::ClassID type);

    /// The IMessage base construct is declared protected to prevent direct creation of
    /// an IMessage. You must construct a class derived from IMessage to use this class.
    IMessage();


    /// @cond EMERGENT_INTERNAL
    typedef efd::RefCountedMemObj< efd::map< efd::UInt32, efd::UInt32 > > ParentClassMap;

    static inline ParentClassMap* GetParentClassMap();

    static void DeleteParentClassMap();

protected:

    static ParentClassMap* ms_pParentClassMap;

    // note: the order of these structure members must match the enum above
    union
    {
        struct
        {
            bool mdf_BreakOnFirstLocalDelivery   : 1;
            bool mdf_BreakOnEachLocalDelivery    : 1;
            bool mdf_BreakOnFirstNetDelivery     : 1;
            bool mdf_BreakOnEachNetDelivery      : 1;
            bool mdf_BreakOnNetQueue             : 1;
            bool mdf_BreakOnNetReceive           : 1;
            bool mdf_BreakOnNetSend              : 1;
            bool mdf_BreakOnLocalPost            : 1;
            bool mdf_BreakOnDelayedLocalPost     : 1;
            bool mdf_TraceOnly                   : 1;
        } m_MessageDebugFlags;

        mutable efd::UInt32 m_flags;
    };
    /// @endcond

    // An id that uniquely identifies this message instance for tracking it through the system.
    mutable efd::UInt32 m_uniqueIdentifier;
};


/// A smart pointer (reference counting, self deleting pointers) for IMessage instances.
typedef efd::SmartPointer<IMessage> IMessagePtr;
/// A smart pointer (reference counting, self deleting pointer) for const IMessage instances.
typedef efd::SmartPointer< const IMessage > IMessageConstPtr;

/**
\brief Used for messages that need sender and destination Categories.

This is used in NetMessage and StreamMessage.
*/
class EE_EFD_ENTRY DirectedMessage : public IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(DirectedMessage, kCLASSID_DirectedMessage, IMessage);
    /// @endcond

public:
    DirectedMessage()
        : m_destinationCategory(kCAT_INVALID)
        , m_senderCategory(kCAT_INVALID)
    {}

    /// A Category that can be used to send a reply message to the logical process that originally
    /// sent this message. Local messages don't contain the space; this returns a default value.
    virtual const efd::Category& GetSenderCategory() const;
    inline void SetSenderCategory(const efd::Category& sender)
    {
        m_senderCategory = sender;
    }

    /// The Category that is used to route this message. Local messages use a default value.
    virtual const efd::Category& GetDestinationCategory() const;
    inline void SetDestinationCategory(const efd::Category& dest)
    {
        m_destinationCategory = dest;
    }

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    void Serialize(efd::Archive& io_ar);

private:
    efd::Category m_destinationCategory;
    efd::Category m_senderCategory;
};

/**
    A helper template class to make creating new message types easier. This template defines
    both GetClassID and a factory method that knows how to create a new instance of the base
    message class.

    usage: MessageWrapper< Base message class, new message Class ID>

    example: MessageWrapper<EnvelopeMessage, kMSGID_RemoteWrapper>

    @note Incorrect usage of MessageWrapper can generate a compile time assert. This will happen
    if you attempt to wrap a class using the same ClassID that the base class is already using.
    In such a case the base class should simply be directly used instead.

    @param BaseMessageClass The IMessage based concrete class to modify.
    @param newMsgClassID The new ClassID to use for this type of Message
*/
template<class BaseMessageClass, efd::UInt32 newMsgClassID>
class MessageWrapper : public BaseMessageClass
{
public:
    // For use by macros/templates that expect the use of EE_BEGIN_DECLARE_CLASS
    static const efd::ClassID CLASS_ID = newMsgClassID;

    /// @name Construction and Destruction
    //@{
    MessageWrapper()
    {
        // This class is used to change the base class id so the new ID should be different
        EE_COMPILETIME_ASSERT(newMsgClassID != BaseMessageClass::CLASS_ID);
    }
    //@}

    /// Get the class id for this instance. Note: overriding GetClassID like this saves some
    /// boiler plate that would be needed if we used EE_DECLARE_CLASS, and
    /// EE_IMPLEMENT_CONCRETE...
    virtual efd::ClassID GetClassID() const { return newMsgClassID; }

    /// Factory a new message with the appropriate base class and message type ID.
    static efd::IMessagePtr FactoryMsg()
        { return EE_NEW MessageWrapper< BaseMessageClass, newMsgClassID >; }

};

#if !defined(EE_DISABLE_LOGGING)
/**
    Macro to log a trace entry for a message.
    @param pMessage A standard pointer (non-smart) to the message.
    @param module The module the message is being sent from.
    @param level1 The level1 log level is used if any debug flags are set on the IMessage.
    @param level2 The level2 log level is used when there are no debug flags set on the IMessage.
    @param args The message to log.
*/
#define EE_MESSAGE_TRACE(pMessage, module, level1, level2, args)                        \
{                                                                                       \
    if (pMessage->GetDebugFlags())                                                      \
    {                                                                                   \
        if (efd::GetLogger()->IsLogging(module, level1))                                \
        {                                                                               \
            efd::GetLogger()->Log(                                                      \
                module,                                                                 \
                level1,                                                                 \
                __FILE__,                                                               \
                __LINE__,                                                               \
                efd::LogHelper args);                                                   \
        }                                                                               \
    }                                                                                   \
    else                                                                                \
    {                                                                                   \
        if (efd::GetLogger()->IsLogging(module, level2))                                \
        {                                                                               \
            efd::GetLogger()->Log(                                                      \
                module,                                                                 \
                level2,                                                                 \
                __FILE__,                                                               \
                __LINE__,                                                               \
                efd::LogHelper args);                                                   \
        }                                                                               \
    }                                                                                   \
} //EE_MESSAGE_TRACE

/**
    Macro to debug break if the flags are set, or trace if the flags and TraceOnly are set

    @param pMessage A standard pointer (non-smart) to the message.
    @param flags Any currently set IMessage debug/trace flags.
    @param args The message to log.
*/
#define EE_MESSAGE_BREAK(pMessage, flags, args)                                         \
{                                                                                       \
    if (pMessage->CheckDebugFlag(IMessage::mdf_TraceOnly))                              \
    {                                                                                   \
        if ((efd::GetLogger()->IsLogging(efd::kMessageTrace, efd::ILogger::kLVL0)) &&   \
              pMessage->CheckDebugFlag(flags))                                          \
        {                                                                               \
            efd::GetLogger()->Log(                                                      \
                efd::kMessageTrace,                                                     \
                efd::ILogger::kLVL0,                                                    \
                __FILE__,                                                               \
                __LINE__,                                                               \
                efd::LogHelper args);                                                   \
        }                                                                               \
    }                                                                                   \
    else                                                                                \
    {                                                                                   \
        EE_ASSERT_MESSAGE(!pMessage->CheckDebugFlag(flags), args);                      \
    }                                                                                   \
}

#else //!defined(EE_DISABLE_LOGGING)

#define EE_MESSAGE_TRACE(pMessage, module, level1, level2, args)
#define EE_MESSAGE_BREAK(pMessage, flags, args)

#endif //!defined(EE_DISABLE_LOGGING)

/**
    Helper function to register Message factory of a specific class type. The class must use
    Foundation RTTI to define a unique MessageClass::CLASS_ID which is used by the factory.

    @param pMessageFactory A MessageFactory pointer.
*/
template <class MessageClass>
inline void RegisterMessageFactory(MessageFactory* pMessageFactory);

/**
    Helper function to register a message factory for an efd::MessageWrapper<BaseMessageClass,
    newMsgClassID> message class.

    @param pMessageFactory A MessageFactory pointer.
*/
template <class BaseMessageClass, efd::UInt32 newMsgClassID>
inline void RegisterMessageWrapperFactory(MessageFactory* pMessageFactory);

} // end namespace efd

#include <efd/IMessage.inl>

#endif // EE_IMESSAGE_H
