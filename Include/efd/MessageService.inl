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

namespace efd
{

//------------------------------------------------------------------------------------------------
inline void MessageService::SendImmediate(const IMessage* pMessage)
{
   SendImmediate(pMessage, pMessage->GetDestinationCategory());
}

//------------------------------------------------------------------------------------------------
inline void MessageService::SendLocal(const IMessage* pMessage)
{
    SendLocal(pMessage, pMessage->GetDestinationCategory());
}

//------------------------------------------------------------------------------------------------
inline void MessageService::SendLocalDelayed(const IMessage* pMessage, efd::TimeType fDelay)
{
    SendLocalDelayed(pMessage, fDelay, pMessage->GetDestinationCategory());
}

//------------------------------------------------------------------------------------------------
inline void MessageService::SendRemote(IMessage* pMessage)
{
    SendRemote(pMessage, pMessage->GetDestinationCategory());
}

//------------------------------------------------------------------------------------------------
inline void MessageService::Send(const IMessage* pMessage)
{
    Send(pMessage,pMessage->GetDestinationCategory());
}

//------------------------------------------------------------------------------------------------
// MessageService::DelayedMessage
//------------------------------------------------------------------------------------------------
inline MessageService::DelayedMessage::DelayedMessage(
    const IMessage* pMessage,
    Category targetCategory,
    efd::TimeType sendTime,
    bool isProducerMessage)
    : m_spMessage(pMessage)
    , m_targetCategory(targetCategory)
    , m_sendTime(sendTime)
    , m_isProducerMessage(isProducerMessage)
{
}

//------------------------------------------------------------------------------------------------
inline MessageService::DelayedMessage::DelayedMessage(
    const MessageService::DelayedMessage& delayedMessage)
    : m_spMessage(delayedMessage.m_spMessage)
    , m_targetCategory(delayedMessage.m_targetCategory)
    , m_sendTime(delayedMessage.m_sendTime)
    , m_isProducerMessage(delayedMessage.m_isProducerMessage)
{}

//------------------------------------------------------------------------------------------------
MessageService::DelayedMessage::~DelayedMessage()
{
    // Ensure the smart pointer gets freed.
    m_spMessage = NULL;
}

//------------------------------------------------------------------------------------------------
inline bool MessageService::DelayedMessage::operator==(
    const MessageService::DelayedMessage& delayedMessage)
{
    return (m_spMessage == delayedMessage.m_spMessage)
        && (m_targetCategory == delayedMessage.m_targetCategory)
        && (m_sendTime == delayedMessage.m_sendTime)
        && (m_isProducerMessage == delayedMessage.m_isProducerMessage);
}

//------------------------------------------------------------------------------------------------
inline bool MessageService::DelayedMessage::operator!=(
    const MessageService::DelayedMessage& delayedMessage)
{
    return (m_spMessage != delayedMessage.m_spMessage)
        || (m_targetCategory != delayedMessage.m_targetCategory)
        || (m_sendTime != delayedMessage.m_sendTime)
        || (m_isProducerMessage == delayedMessage.m_isProducerMessage);
}

//------------------------------------------------------------------------------------------------
// MessageService::MessageWithCategory
//------------------------------------------------------------------------------------------------
inline MessageService::MessageWithCategory::MessageWithCategory(
    const IMessage* pMessage,
    Category targetCategory,
    bool isProducerMessage)
    : m_spMessage(pMessage)
    , m_targetCategory(targetCategory)
    , m_isProducerMessage(isProducerMessage)
{}

//------------------------------------------------------------------------------------------------
inline MessageService::MessageWithCategory::MessageWithCategory(
    const MessageService::MessageWithCategory& messageWithCategory)
    : m_spMessage(messageWithCategory.m_spMessage)
    , m_targetCategory(messageWithCategory.m_targetCategory)
    , m_isProducerMessage(messageWithCategory.m_isProducerMessage)
{
}

//------------------------------------------------------------------------------------------------
inline MessageService::MessageWithCategory::~MessageWithCategory()
{
    // Ensure the smart pointer gets freed.
    m_spMessage = NULL;
}

//------------------------------------------------------------------------------------------------
inline bool MessageService::MessageWithCategory::operator==(
    const MessageService::MessageWithCategory& messageWithCategory)
{
    return (m_spMessage == messageWithCategory.m_spMessage)
        && (m_targetCategory == messageWithCategory.m_targetCategory)
        && (m_isProducerMessage == messageWithCategory.m_isProducerMessage);
}

//------------------------------------------------------------------------------------------------
inline bool MessageService::MessageWithCategory::operator!=(
    const MessageService::MessageWithCategory& messageWithCategory)
{
    return (m_spMessage != messageWithCategory.m_spMessage)
        || (m_targetCategory != messageWithCategory.m_targetCategory)
        || (m_isProducerMessage != messageWithCategory.m_isProducerMessage);
}

//------------------------------------------------------------------------------------------------
// MessageService::TargetSubscription
//------------------------------------------------------------------------------------------------
inline MessageService::TargetSubscription::TargetSubscription(
    efd::ClassID msgClassID,
    IBase* pIAppTarget,
    Category targetChannel,
    QualityOfService qualityOfService,
    SUBSCRIBE_TYPE subscribe)
    : m_subscribe(subscribe)
    , m_typeID(msgClassID)
    , m_targetChannel(targetChannel)
    , m_pIAppTarget(pIAppTarget)
    , m_qualityOfService(qualityOfService)
{}

//------------------------------------------------------------------------------------------------
inline MessageService::TargetSubscription::TargetSubscription(
    const MessageService::TargetSubscription& handlerSub)
    : m_subscribe(handlerSub.m_subscribe)
    , m_typeID(handlerSub.m_typeID)
    , m_targetChannel(handlerSub.m_targetChannel)
    , m_pIAppTarget(handlerSub.m_pIAppTarget)
    , m_qualityOfService(handlerSub.m_qualityOfService)
{}

//------------------------------------------------------------------------------------------------
inline bool MessageService::TargetSubscription::operator==(
    const MessageService::TargetSubscription& handlerSub)
{
    return (m_typeID == handlerSub.m_typeID)
        && (m_subscribe == handlerSub.m_subscribe)
        && (m_pIAppTarget == handlerSub.m_pIAppTarget)
        && (m_targetChannel == handlerSub.m_targetChannel)
        && (m_qualityOfService == handlerSub.m_qualityOfService);
}

//------------------------------------------------------------------------------------------------
inline bool MessageService::TargetSubscription::operator!=(
    const MessageService::TargetSubscription& handlerSub)
{
    return (m_typeID != handlerSub.m_typeID)
        || (m_subscribe != handlerSub.m_subscribe)
        || (m_pIAppTarget != handlerSub.m_pIAppTarget)
        || (m_targetChannel != handlerSub.m_targetChannel)
        || (m_qualityOfService != handlerSub.m_qualityOfService);
}

//------------------------------------------------------------------------------------------------
} // end namespace efd
