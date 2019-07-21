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
#ifndef EE_CORERUNTIMEPROPERTYTYPES_H
#define EE_CORERUNTIMEPROPERTYTYPES_H

#include "ecrLibType.h"

#include <egf/TProperty.h>

#include <ecr/ecrPropertyIDs.h>

#include <ecr/AttachNifData.h>

namespace egf
{
    class FlatModelManager;
}

namespace ecr
{

/**
    Register property factories for Core Runtime services.

    @param pFlatModelManager Pointer to the FlatModelManager object
*/
void EE_ECR_ENTRY RegisterCorePropertyFactories(
    class egf::FlatModelManager* pFlatModelManager);

/// Macro to create Point2 scalar property
EE_DECLARE_PRIMITIVE_SCALAR_PROPERTY(AttachedNifAsset, ecr::AttachNifData,
    efd::kPropID_AttachNif);
/// Macro to create Point2 associative array property
EE_DECLARE_PRIMITIVE_ASSOCIATIVE_ARRAY_PROPERTY(AttachedNifAsset,
    ecr::AttachNifData, efd::kPropID_AttachNifAssocArray);

}; // namespace

#endif // EE_CORERUNTIMEPROPERTYTYPES_H
