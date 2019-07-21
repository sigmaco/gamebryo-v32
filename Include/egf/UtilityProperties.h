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
#ifndef __UtilityProperties_h__
#define __UtilityProperties_h__

#include <egf/TProperty.h>
#include <egf/egfLibType.h>
#include <egf/egfPropertyIDs.h>

#include <efd/AssetID.h>
#include <efd/Point2.h>
#include <efd/Point3.h>
#include <efd/Matrix3.h>
#include <efd/Color.h>


namespace egf
{
/// @name Properties from UtilityProperties.h
//@{

/**
    Register property factories for various basic property types

    @param[in] i_pfmm pointer to FlatModelManager
*/
void EE_EGF_ENTRY RegisterUtilityPropFactories(class FlatModelManager* i_pfmm);

/// Macro to create Point2 scalar property
EE_DECLARE_PRIMITIVE_SCALAR_PROPERTY(Point2, efd::Point2, efd::kPropID_Point2);
/// Macro to create Point2 associative array property
EE_DECLARE_PRIMITIVE_ASSOCIATIVE_ARRAY_PROPERTY(Point2, efd::Point2, efd::kPropID_Point2AssocArray);

/// Macro to create Point3 scalar property
EE_DECLARE_PRIMITIVE_SCALAR_PROPERTY(Point3, efd::Point3, efd::kPropID_Point3);
/// Macro to create Point3 associative array property
EE_DECLARE_PRIMITIVE_ASSOCIATIVE_ARRAY_PROPERTY(Point3, efd::Point3, efd::kPropID_Point3AssocArray);

/// Macro to create Matrix3 scalar property
EE_DECLARE_PRIMITIVE_SCALAR_PROPERTY(Matrix3, efd::Matrix3, efd::kPropID_Matrix3);
/// Macro to create Matrix3 associative array property
EE_DECLARE_PRIMITIVE_ASSOCIATIVE_ARRAY_PROPERTY(Matrix3, efd::Matrix3,
    efd::kPropID_Matrix3AssocArray);

/// Macro to create Color scalar property
EE_DECLARE_PRIMITIVE_SCALAR_PROPERTY(Color, efd::Color, efd::kPropID_Color);
/// Macro to create Color associative array property
EE_DECLARE_PRIMITIVE_ASSOCIATIVE_ARRAY_PROPERTY(Color, efd::Color, efd::kPropID_ColorAssocArray);

/// Macro to create ColorA scalar property
EE_DECLARE_PRIMITIVE_SCALAR_PROPERTY(ColorA, efd::ColorA, efd::kPropID_ColorA);
/// Macro to create ColorA associative array property
EE_DECLARE_PRIMITIVE_ASSOCIATIVE_ARRAY_PROPERTY(ColorA, efd::ColorA, efd::kPropID_ColorAAssocArray);

/// Macro to create Asset scalar property
EE_DECLARE_PRIMITIVE_SCALAR_PROPERTY(AssetID, efd::AssetID, efd::kPropID_AssetID);
/// Macro to create Asset associative array property
EE_DECLARE_PRIMITIVE_ASSOCIATIVE_ARRAY_PROPERTY(AssetID, efd::AssetID, efd::kPropID_AssetIDAssocArray);

//@}

} // end namespace egf

#endif // __UtilityProperties_h__
