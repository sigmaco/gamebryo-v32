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
#ifndef EE_IPROPERTYTYPE_H
#define EE_IPROPERTYTYPE_H

#include <efd/TemplateHelpers.h>
#include <egf/EntityID.h>
#include <efd/ClassIDHelpers.h>

namespace efd
{

    const efd::ClassID CLASS_ID_ENTITYID    = 0x00004BA1;
} // end namespace efd


/// ClassID mapping for egf::EntityID
EE_SPECIALIZE_TYPE(egf::EntityID, CLASS_ID_ENTITYID);


#endif //EE_IPROPERTYTYPE_H
