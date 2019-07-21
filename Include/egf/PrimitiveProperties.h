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
#ifndef EE_PRIMITIVEPROPERTIES_H
#define EE_PRIMITIVEPROPERTIES_H

#include <egf/egfLibType.h>

#include <egf/egfPropertyIDs.h>
#include <egf/TProperty.h>
#include <egf/EntityID.h>

namespace egf
{

/// @name Properties from PrimitiveProperties.h
//@{

void EE_EGF_ENTRY RegisterPrimitivePropFactories(class FlatModelManager* i_pfmm);


/// Scalar properties
EE_DECLARE_PRIMITIVE_SCALAR_PROPERTY(Boolean, efd::Bool, efd::kPropID_Boolean);
EE_DECLARE_PRIMITIVE_SCALAR_PROPERTY(Char, efd::utf8char_t, efd::kPropID_Char);
EE_DECLARE_PRIMITIVE_SCALAR_PROPERTY(SInt16, efd::SInt16, efd::kPropID_SInt16);
EE_DECLARE_PRIMITIVE_SCALAR_PROPERTY(UInt16, efd::UInt16, efd::kPropID_UInt16);
EE_DECLARE_PRIMITIVE_SCALAR_PROPERTY(SInt32, efd::SInt32, efd::kPropID_SInt32);
EE_DECLARE_PRIMITIVE_SCALAR_PROPERTY(UInt32, efd::UInt32, efd::kPropID_UInt32);
EE_DECLARE_PRIMITIVE_SCALAR_PROPERTY(SInt64, efd::SInt64, efd::kPropID_SInt64);
EE_DECLARE_PRIMITIVE_SCALAR_PROPERTY(UInt64, efd::UInt64, efd::kPropID_UInt64);
EE_DECLARE_PRIMITIVE_SCALAR_PROPERTY(Float32, efd::Float32, efd::kPropID_Float32);
EE_DECLARE_PRIMITIVE_SCALAR_PROPERTY(Float64, efd::Float64, efd::kPropID_Float64);
EE_DECLARE_PRIMITIVE_SCALAR_PROPERTY(String, efd::utf8string, efd::kPropID_String);
EE_DECLARE_PRIMITIVE_SCALAR_PROPERTY(EntityRef, egf::EntityID, efd::kPropID_EntityRef);


/// Associative Array properties
EE_DECLARE_PRIMITIVE_ASSOCIATIVE_ARRAY_PROPERTY(Boolean, efd::Bool, efd::kPropID_BooleanAssocArray);
EE_DECLARE_PRIMITIVE_ASSOCIATIVE_ARRAY_PROPERTY(Char, efd::utf8char_t, efd::kPropID_CharAssocArray);
EE_DECLARE_PRIMITIVE_ASSOCIATIVE_ARRAY_PROPERTY(SInt16, efd::SInt16, efd::kPropID_SInt16AssocArray);
EE_DECLARE_PRIMITIVE_ASSOCIATIVE_ARRAY_PROPERTY(UInt16, efd::UInt16, efd::kPropID_UInt16AssocArray);
EE_DECLARE_PRIMITIVE_ASSOCIATIVE_ARRAY_PROPERTY(SInt32, efd::SInt32, efd::kPropID_SInt32AssocArray);
EE_DECLARE_PRIMITIVE_ASSOCIATIVE_ARRAY_PROPERTY(UInt32, efd::UInt32, efd::kPropID_UInt32AssocArray);
EE_DECLARE_PRIMITIVE_ASSOCIATIVE_ARRAY_PROPERTY(SInt64, efd::SInt64, efd::kPropID_SInt64AssocArray);
EE_DECLARE_PRIMITIVE_ASSOCIATIVE_ARRAY_PROPERTY(UInt64, efd::UInt64, efd::kPropID_UInt64AssocArray);
EE_DECLARE_PRIMITIVE_ASSOCIATIVE_ARRAY_PROPERTY(Float32, efd::Float32,
    efd::kPropID_Float32AssocArray);
EE_DECLARE_PRIMITIVE_ASSOCIATIVE_ARRAY_PROPERTY(Float64, efd::Float64,
    efd::kPropID_Float64AssocArray);
EE_DECLARE_PRIMITIVE_ASSOCIATIVE_ARRAY_PROPERTY(String, efd::utf8string,
    efd::kPropID_StringAssocArray);
EE_DECLARE_PRIMITIVE_ASSOCIATIVE_ARRAY_PROPERTY(EntityRef, egf::EntityID,
    efd::kPropID_EntityRefAssocArray);

//@}

}; // end namespace egf

#endif // EE_PRIMITIVEPROPERTIES_H
