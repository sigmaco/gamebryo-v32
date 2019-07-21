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
#ifndef EE_INTERACTIONSERVICE_H
#define EE_INTERACTIONSERVICE_H

#include "egmToolServicesLibType.h"
#include "egmToolServicesClassIDs.h"

#include <efd/IMessage.h>
#include <efd/MessageHandlerBase.h>
#include <efd/ISystemService.h>
#include <efd/MessageService.h>
#include <ecr/ecrSystemServiceIDs.h>

#include "IInteractionDelegate.h"

namespace egmToolServices
{

class EE_EGMTOOLSERVICES_ENTRY InteractionService : public efd::ISystemService
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(InteractionService, efd::kCLASSID_InteractionService, efd::ISystemService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond
public:

    /**
    */
    InteractionService();


    void AddInteractionDelegate(IInteractionDelegate* pInteractionDelegate);
    void RemoveInteractionDelegate(IInteractionDelegate* pInteractionDelegate);

    /**
        Handle incoming mouse move message from the input service.
        @param pMsg The input message.
        @param targetChannel Channel the message was sent on.
    */
    void HandleMouseMoveMessage(const ecrInput::MouseMoveMessage* pMsg,
        efd::Category targetChannel);

    /**
        Handle incoming mouse up message from the input service.
        @param pMsg The input message.
        @param targetChannel Channel the message was sent on.
    */
    void HandleMouseUpMessage(const ecrInput::MouseUpMessage* pMsg,
        efd::Category targetChannel);

    /**
        Handle incoming mouse down message from the input service.
        @param pMsg The input message.
        @param targetChannel Channel the message was sent on.
    */
    void HandleMouseDownMessage(const ecrInput::MouseDownMessage* pMsg,
        efd::Category targetChannel);

protected:
    /// Destructor
    virtual ~InteractionService();

    // ISystemService methods inherit base documentation
    virtual const char* GetDisplayName() const;
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);
    virtual efd::AsyncResult OnShutdown();

protected:
    efd::MessageService* m_pMessageService;

    typedef efd::vector<IInteractionDelegate*> InteractionDelegates;
    InteractionDelegates m_delegates;
};

typedef efd::SmartPointer<InteractionService> InteractionServicePtr;

} // namespace

#endif // EE_INTERACTION_SERVICE_H
