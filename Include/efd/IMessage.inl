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

namespace efd {

//--------------------------------------------------------------------------------------------------
inline efd::UInt32 IMessage::GetDebugFlags() const
{
    return m_flags;
}


//--------------------------------------------------------------------------------------------------
inline void IMessage::SetDebugFlags(efd::UInt32 i_flags) const
{
    m_flags = i_flags;
}

//--------------------------------------------------------------------------------------------------
inline IMessage::ParentClassMap* IMessage::GetParentClassMap()
{
    if (ms_pParentClassMap == NULL)
        ms_pParentClassMap = EE_NEW ParentClassMap();

    return ms_pParentClassMap;
}

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
template <class BaseMessageClass>
inline void RegisterMessageFactory(MessageFactory* pMessageFactory)
{
    pMessageFactory->RegisterDefaultFactoryMethod<BaseMessageClass>(BaseMessageClass::CLASS_ID);
}

//------------------------------------------------------------------------------------------------
template <class BaseMessageClass, efd::UInt32 newMsgClassID>
inline void RegisterMessageWrapperFactory(MessageFactory* pMessageFactory)
{
    // This is to be used for wrappers, wrappers change the class ID. If this compile time assert
    // goes off then you most likely should be using 
    EE_COMPILETIME_ASSERT(BaseMessageClass::CLASS_ID != newMsgClassID);

    efd::UInt32 baseClassID;

    efd::IMessage::ParentClassMap* pParentMap = efd::IMessage::GetParentClassMap();

    if (pParentMap->find(newMsgClassID, baseClassID))
    {
        if (baseClassID != BaseMessageClass::CLASS_ID)
        {
            EE_LOG(efd::kMessageService, efd::ILogger::kLVL2,
                ("RegisterMessageWrapperFactory(): "
                "Target: 0x%08X registered base: 0x%08X, "
                "target previously registered base: 0x%08X",
                newMsgClassID,
                BaseMessageClass::CLASS_ID,
                baseClassID));
        }
        // If you hit this assert it means that RegisterMessageWrapperFactory has been called with
        // the same class id but a different class to wrap.  The EE_HANDLER_WRAP and
        // EE_HANDLER_SUBCLASS_WRAPPER macros also trigger calls to RegisterMessageWrapperFactory.
        // If this assert goes from because of a call in
        // MessageService::RegisterMessageHandler, look at the BaseMessageHandler::m_targetClassID.
        // This is the class that called the EE_HANDLER* macro.
        // If you are having trouble tracking down where the macro is being called from you can put
        // an EE_ASSERT in the else clause below that goes off the first time newMsgClassID ==
        // the value it does now.
        EE_ASSERT(baseClassID == BaseMessageClass::CLASS_ID);
    }
    else
    {
        (*pParentMap)[newMsgClassID] = BaseMessageClass::CLASS_ID;
    }

    pMessageFactory->RegisterFactoryMethod(
        newMsgClassID,
        &MessageWrapper<BaseMessageClass, newMsgClassID>::FactoryMsg);
}

//------------------------------------------------------------------------------------------------
}  // namespace efd
