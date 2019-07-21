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
#ifndef EE_INETCALLBACK_H
#define EE_INETCALLBACK_H

#include <efd/efdLibType.h>
#include <efd/ReferenceCounting.h>
#include <efd/SmartPointer.h>
#include <efd/StdContainers.h>

namespace efd
{
    class IMessage;
    class ConnectionID;

    /**
        \brief Network Message notification callback Interface
    */
    class EE_EFD_ENTRY INetCallback
    {
    public:
        /// Virtual destructor
        virtual ~INetCallback() {}

        /**
            Callback method used by network code to deliver messages received from remote
            connections.
            @param pIncomingMessage The message received.
            @param senderConnectionID The ConnectionID the message was received from.
        */
        virtual void HandleNetMessage(
            const IMessage* pIncomingMessage,
            const ConnectionID& senderConnectionID) = 0;
    };


    /**
        This class is a helper for handling multiple INetCallback callbacks in a single class

        You can use NetCallbackForward to route the HandleNetMessage call to another function
        with a different name but the same syntax.  Simply declare a variable of type
        NetCallbackForward using the parent class and the handler method as the template
        parameters.  For example, to add two different handlers to class Foo you might use:

        @code
          class Foo : public efd::ISystemService
          {
          public:
              void HandleServerMessage(const IMessage* pIncoming, const ConnectionID& sender);
              void HandleClientMessage(const IMessage* pIncoming, const ConnectionID& sender);

          public:
              void OnInit()
              {
                  INetService* pNet = m_pServiceManager->GetSystemServiceAs<INetService>();
                  pNet->Subscribe(ServerCategory, kMASK_ALL, &m_ServerMessageHandler);
                  pNet->Subscribe(ClientCategory, kMASK_ALL, &m_ClientMessageHandler);
              }
          };
        @endcode
    */
    template< typename T, void (T::*HandlerMethod)(const IMessage*, const ConnectionID&) >
    class NetCallbackForward : public INetCallback
    {
    public:
        // NOTE: This version will cause a compiler warning C4355 on MSVC.  You may wish to use
        // the default constructor and the Set method to avoid this warning.
        NetCallbackForward(T* i_pHandler)
            : m_pHandler(i_pHandler)
        {
        }

        // NOTE: If using this constructor, you must call Set prior to usage or it will result
        // in a crash.
        NetCallbackForward()
            : m_pHandler(NULL)
        {
        }

        void Set(T* i_pHandler)
        {
            m_pHandler = i_pHandler;
        }

    protected:
        // the proxy directly handles connection callbacks on behalf of the client:
        virtual void HandleNetMessage(const IMessage* pIncomingMessage,
                                       const ConnectionID& senderPrivateCat)
        {
            (m_pHandler->*HandlerMethod)(pIncomingMessage, senderPrivateCat);
        }

        T* m_pHandler;
    };

    typedef efd::RefCountedMemObj< efd::set< INetCallback* > > INetCallbackSet;
    typedef efd::SmartPointer< INetCallbackSet > INetCallbackSetPtr;

} // end namespace efd

#endif // EE_INETCALLBACK_H
