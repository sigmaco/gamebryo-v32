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

#ifndef EE_PHYSXPROPMESSAGE_H
#define EE_PHYSXPROPMESSAGE_H

#include "ecrPhysXLibType.h"

#include <efd/Category.h>
#include <efd/IDs.h>
#include <efd/IMessage.h>
#include <efd/SystemFrameworkEnums.h>
#include <efdPhysX/PhysXSDKManager.h>
#include <ecr/ecrMessageIDs.h>
#include <egf/EntityID.h>

namespace ecrPhysX
{

/**
    Message class for PhysXPropAddedToScene and PhysXPropRemovingFromScene messages sent by
    the ecrPhysX::PropService class.
    
    Receivers must subscribe to the egfPhysX::kCAT_egfPhysXMessage category.
    
    Use EE_HANDLER_WRAP to set up a handler for these messages.
*/
class EE_ECRPHYSX_ENTRY PhysXPropMessage :
    public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(PhysXPropMessage, efd::kMSGID_PhysXPropMessage, IMessage);
    /// @endcond

public:
    PhysXPropMessage();

    virtual void Serialize(efd::Archive& ar);

    inline const egf::EntityID& GetEntityID() const;
    inline void SetEntityID(const egf::EntityID& entityID);

    inline static efd::IBasePtr FactoryMethod();

protected:
    egf::EntityID m_entityID;
};

typedef efd::SmartPointer<PhysXPropMessage> PhysXPropMessagePtr;

/// @name MessageWrappers from SceneMessage.h
//@{
typedef efd::MessageWrapper<PhysXPropMessage, efd::kMSGID_PhysXPropAddedToScene>
    PhysXPropAddedToScene;
typedef efd::MessageWrapper<PhysXPropMessage, efd::kMSGID_PhysXPropRemovingFromScene>
    PhysXPropRemovingFromScene;
//@}

} // namespace ecrPhysX

#include <ecrPhysX/PhysXPropMessage.inl>

#endif // EE_PHYSXPROPMESSAGE_H