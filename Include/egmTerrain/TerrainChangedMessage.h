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
#ifndef EE_EGFTERRAINCHANGEDMESSAGE_H
#define EE_EGFTERRAINCHANGEDMESSAGE_H

#include <ecr/ecrMessageIDs.h>
#include <efd/IMessage.h>
#include <egf/IProperty.h>
#include <egf/Entity.h>
#include <NiNode.h>

#include "egmTerrainLibType.h"

namespace egmTerrain
{

/**
    This message type is used for all terrain entity events: additions, removals, and updates.
*/
class EE_EGMTERRAIN_ENTRY TerrainChangedMessage : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(TerrainChangedMessage, efd::kMSGID_TerrainChanged, efd::IMessage);
    /// @endcond

public:

    /// @name Construction and Destruction
    //@{
    /// Default Constructor.
    inline TerrainChangedMessage();

    /// Virtual Destructor.
    inline virtual ~TerrainChangedMessage();
    //@}

    /// Factory method to create this message.
    static efd::IBasePtr FactoryMethod();
};

/// Defines a smart pointer (reference counted) for the TerrainChangedMessage class
typedef efd::SmartPointer<TerrainChangedMessage> TerrainChangedMessagePtr;

#include "TerrainChangedMessage.inl"

} // namespace

#endif // EE_EGFTERRAINCHANGEDMESSAGE_H
