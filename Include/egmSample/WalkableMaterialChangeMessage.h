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
#ifndef EE_WALKABLEMATERIALCHANGEMESSAGE_H
#define EE_WALKABLEMATERIALCHANGEMESSAGE_H

#include <efd/IMessage.h>
#include <egf/Entity.h>
#include "egfDemoSystemServiceIDs.h"
#include "egmSampleLibType.h"


namespace egmSample
{

/**
    Notifies any subscribers that an entity has moved onto a surface marked with
    different material metadata.
*/
class EE_EGMSAMPLE_ENTRY WalkableMaterialChangeMessage : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL

    EE_DECLARE_CLASS1(
        WalkableMaterialChangeMessage,
        efd::kCLASSID_WalkableMaterialChanged,
        efd::IMessage);

    /// @endcond

public:
    /// Construction and Destruction
    inline WalkableMaterialChangeMessage();
    virtual ~WalkableMaterialChangeMessage();

    // overrides for IMessage
    virtual void Serialize(efd::Archive& ar);

    /// Retrieve the entity that has changed material
    inline egf::Entity* GetEntity();

    /// Set the entity reported by the message
    inline void SetEntity(egf::Entity* pEntity);

    /// Retrieve the name of the new material the entity is standing on
    inline efd::utf8string GetMaterial();

    /// Set the material reported by the message
    inline void SetMaterial(efd::utf8string material);

protected:
    egf::Entity* m_pEntity;
    efd::utf8string m_newMaterial;
};

typedef efd::SmartPointer<WalkableMaterialChangeMessage> WalkableMaterialChangeMessagePtr;

} // end namespace egmSample

#include "WalkableMaterialChangeMessage.inl"

#endif // EE_WALKABLEMATERIALCHANGEMESSAGE_H
