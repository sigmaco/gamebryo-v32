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

#ifndef EE_NIPHYSXSCENEADDED_H
#define EE_NIPHYSXSCENEADDED_H

#include "ecrPhysXLibType.h"

#include <efd/Category.h>
#include <efd/IDs.h>
#include <efd/IMessage.h>
#include <efd/SystemFrameworkEnums.h>
#include <efdPhysX/PhysXSDKManager.h>
#include <ecr/ecrMessageIDs.h>

namespace ecrPhysX
{

/**
    Message class for NiPhysXSceneAdded messages sent by the ecrPhysX::PropService class.

    Receivers must subscribe to the egfPhysX::kCAT_egfPhysXMessage category.
*/
class EE_ECRPHYSX_ENTRY NiPhysXSceneAdded :
    public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(NiPhysXSceneAdded, efd::kMSGID_NiPhysXSceneAdded, IMessage);
    /// @endcond

public:
    NiPhysXSceneAdded();

    virtual void Serialize(efd::Archive& ar);

    inline const efd::utf8string& GetSceneName() const;
    inline void SetSceneName(const efd::utf8string& sceneName);

    inline static efd::IBasePtr FactoryMethod();

protected:
    efd::utf8string m_sceneName;
};

typedef efd::SmartPointer<NiPhysXSceneAdded> NiPhysXSceneAddedPtr;

} // namespace ecrPhysX

#include <ecrPhysX/NiPhysXSceneAdded.inl>

#endif // EE_NIPHYSXSCENEADDED_H