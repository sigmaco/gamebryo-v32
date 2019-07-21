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
#ifndef EE_CLASSIDHELPERS_INCLUDE
#define EE_CLASSIDHELPERS_INCLUDE

#include <efd/efdPrimitiveTypeIDs.h>
#include <efd/utf8string.h>

namespace efd
{
    /**
        A series of overloaded functions that can return a ClassID for
        a primitive type, or a type derived from IBase.
    */

/// @name ClassID type mapping functions from ClassIDHelpers.h
//@{

    /// IBase requires some special handling in order to implement the ClassID query methods that
    /// we use in the templated Property methods:
    inline efd::ClassID GetClassIDFromObject(const efd::IBase& var)
    {
        return var.GetClassDesc()->GetClassID();
    }
    inline efd::ClassID GetClassIDFromObject(const efd::IBase* const var)
    {
        return var->GetClassDesc()->GetClassID();
    }


    /// template function to return CLASS_ID for a type T.  The default implementation assumes that
    /// the type T derives from IBase.
    template<typename T>
    inline efd::ClassID GetClassIDFromType()
    {
        return T::CLASS_ID;
    }
} // end namespace efd


/// All the plain old data types and most simple non-IBase classes can simply use this macro
/// to define the required ClassID mapping functions:
#define EE_SPECIALIZE_TYPE(TYPE, CID)                                                       \
namespace efd                                                                               \
{                                                                                           \
    inline efd::ClassID GetClassIDFromObject(const TYPE&)                                   \
    {                                                                                       \
        return CID;                                                                         \
    }                                                                                       \
    template<>                                                                              \
    inline efd::ClassID GetClassIDFromType<TYPE>()                                          \
    {                                                                                       \
        return CID;                                                                         \
    }                                                                                       \
}

/// ClassID mapping for efd::Bool
EE_SPECIALIZE_TYPE(efd::Bool, efd::kTypeID_Bool);
/// ClassID mapping for efd:SInt8
EE_SPECIALIZE_TYPE(efd::SInt8, efd::kTypeID_SInt8);
/// ClassID mapping for efd:UInt8
EE_SPECIALIZE_TYPE(efd::UInt8, kTypeID_UInt8);
/// ClassID mapping for efd::SInt16
EE_SPECIALIZE_TYPE(efd::SInt16, kTypeID_SInt16);
/// ClassID mapping for efd::UInt16
EE_SPECIALIZE_TYPE(efd::UInt16, kTypeID_UInt16);
/// ClassID mapping for efd::SInt32
EE_SPECIALIZE_TYPE(efd::SInt32, kTypeID_SInt32);
/// ClassID mapping for efd::UInt32
EE_SPECIALIZE_TYPE(efd::UInt32, kTypeID_UInt32);
/// ClassID mapping for efd::SInt64
EE_SPECIALIZE_TYPE(efd::SInt64, kTypeID_SInt64);
/// ClassID mapping for efd::UInt64
EE_SPECIALIZE_TYPE(efd::UInt64, kTypeID_UInt64);
/// ClassID mapping for efd::Float32
EE_SPECIALIZE_TYPE(efd::Float32, kTypeID_Float32);
/// ClassID mapping for efd::Float64
EE_SPECIALIZE_TYPE(efd::Float64, kTypeID_Float64);
/// ClassID mapping for efd::utf8string
EE_SPECIALIZE_TYPE(efd::utf8string, kTypeID_utf8string);
/// ClassID mapping for efd::utf8char_t
EE_SPECIALIZE_TYPE(efd::utf8char_t, efd::kTypeID_Utf8Char);

namespace efd
{
    // Forward declares:
    class Point2;
    class Point3;
    class Point4;
    class Matrix3;
    class Color;
    class ColorA;
    class Quaternion;
    class AssetID;
    class ID128;
} // end namespace efd

/// ClassID mapping for efd::Point2
EE_SPECIALIZE_TYPE(efd::Point2, kTypeID_Point2);
/// ClassID mapping for efd::Point3
EE_SPECIALIZE_TYPE(efd::Point3, kTypeID_Point3);
/// ClassID mapping for efd::Point4
EE_SPECIALIZE_TYPE(efd::Point4, kTypeID_Point4);
/// ClassID mapping for efd::Matrix3
EE_SPECIALIZE_TYPE(efd::Matrix3, kTypeID_Matrix3);
/// ClassID mapping for efd::Color
EE_SPECIALIZE_TYPE(efd::Color, kTypeID_Color);
/// ClassID mapping for efd::ColorA
EE_SPECIALIZE_TYPE(efd::ColorA, kTypeID_ColorA);
/// ClassID mapping for efd::Quaternion
EE_SPECIALIZE_TYPE(efd::Quaternion, kTypeID_Quaternion);
/// ClassID mapping for efd::AssetID
EE_SPECIALIZE_TYPE(efd::AssetID, kTypeID_AssetID);
/// ClassID mapping for efd::ID128
EE_SPECIALIZE_TYPE(efd::ID128, kTypeID_ID128);

//@}



#endif

