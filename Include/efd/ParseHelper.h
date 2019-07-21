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
#ifndef EE_PARSEHELPER_H
#define EE_PARSEHELPER_H

#include <efd/utf8string.h>
#include <efd/Point2.h>
#include <efd/Point3.h>
#include <efd/Matrix3.h>
#include <efd/Color.h>
#include <efd/ID128.h>
#include <efd/AssetID.h>

namespace efd
{

template< typename T >
struct ParseHelper
{
    static bool FromString(const efd::utf8string& i_value, T& o_result)
    {
        return o_result.FromString(i_value);
    }
    static bool ToString(const T& i_b, efd::utf8string& o_result)
    {
        o_result = i_b.ToString();
        return !o_result.empty();
    }
};

template<>
struct ParseHelper< efd::Bool >
{
    static inline bool FromString(const efd::utf8string& i_value, efd::Bool& o_result);
    static inline bool ToString(efd::Bool i_value, efd::utf8string& o_result);
    static inline const char* GetNameOfType() { return "efd::Bool"; }
};

template<>
struct ParseHelper< efd::UInt8 >
{
    static inline bool FromString(const efd::utf8string& i_value, efd::UInt8& o_result);
    static inline bool ToString(efd::UInt8 i_value, efd::utf8string& o_result);
    static inline const char* GetNameOfType() { return "efd::UInt8"; }
};

template<>
struct ParseHelper< efd::SInt8 >
{
    static inline bool FromString(const efd::utf8string& i_value, efd::SInt8& o_result);
    static inline bool ToString(efd::SInt8 i_value, efd::utf8string& o_result);
    static inline const char* GetNameOfType() { return "efd::SInt8"; }
};

template<>
struct ParseHelper< efd::UInt16 >
{
    static inline bool FromString(const efd::utf8string& i_value, efd::UInt16& o_result);
    static inline bool ToString(efd::UInt16 i_value, efd::utf8string& o_result);
    static inline const char* GetNameOfType() { return "efd::UInt16"; }
};

template<>
struct ParseHelper< efd::SInt16 >
{
    static inline bool FromString(const efd::utf8string& i_value, efd::SInt16& o_result);
    static inline bool ToString(efd::SInt16 i_value, efd::utf8string& o_result);
    static inline const char* GetNameOfType() { return "efd::SInt16"; }
};

template<>
struct ParseHelper< efd::UInt32 >
{
    static inline bool FromString(const efd::utf8string& i_value, efd::UInt32& o_result);
    static inline bool ToString(efd::UInt32 i_value, efd::utf8string& o_result);
    static inline const char* GetNameOfType() { return "efd::UInt32"; }
};

template<>
struct ParseHelper< efd::SInt32 >
{
    static inline bool FromString(const efd::utf8string& i_value, efd::SInt32& o_result);
    static inline bool ToString(efd::SInt32 i_value, efd::utf8string& o_result);
    static inline const char* GetNameOfType() { return "efd::SInt32"; }
};

template<>
struct ParseHelper< efd::UInt64 >
{
    static inline bool FromString(const efd::utf8string& i_value, efd::UInt64& o_result);
    static inline bool ToString(efd::UInt64 i_value, efd::utf8string& o_result);
    static inline const char* GetNameOfType() { return "efd::UInt64"; }
};

template<>
struct ParseHelper< efd::SInt64 >
{
    static inline bool FromString(const efd::utf8string& i_value, efd::SInt64& o_result);
    static inline bool ToString(efd::SInt64 i_value, efd::utf8string& o_result);
    static inline const char* GetNameOfType() { return "efd::SInt64"; }
};

template<>
struct ParseHelper< efd::Float32 >
{
    static inline bool FromString(const efd::utf8string& i_value, efd::Float32& o_result);
    static inline bool ToString(efd::Float32 i_value, efd::utf8string& o_result);
    static inline const char* GetNameOfType() { return "efd::Float32"; }
};

template<>
struct ParseHelper< efd::Float64 >
{
    static inline bool FromString(const efd::utf8string& i_value, efd::Float64& o_result);
    static inline bool ToString(efd::Float64 i_value, efd::utf8string& o_result);
    static inline const char* GetNameOfType() { return "efd::Float64"; }
};

template<>
struct ParseHelper< efd::utf8char_t >
{
    static inline bool FromString(const efd::utf8string& i_value, efd::utf8char_t& o_result);
    static inline bool ToString(const efd::utf8char_t& i_value, efd::utf8string& o_result);
    static inline const char* GetNameOfType() { return "efd::utf8char_t"; }
};

template<>
struct ParseHelper< efd::utf16char_t >
{
    static inline bool FromString(const efd::utf8string& i_value, efd::utf16char_t& o_result);
    static inline bool ToString(const efd::utf16char_t& i_value, efd::utf8string& o_result);
    static inline const char* GetNameOfType() { return "efd::utf16char_t"; }
};

template<>
struct ParseHelper< efd::utf8string >
{
    static inline bool FromString(const efd::utf8string& i_value, efd::utf8string& o_result);
    static inline bool ToString(const efd::utf8string& i_value, efd::utf8string& o_result);
    static inline const char* GetNameOfType() { return "efd::utf8string"; }
};

template<>
struct ParseHelper< efd::Point2 >
{
    static inline bool FromString(const efd::utf8string& i_value, efd::Point2& o_result);
    static inline bool ToString(const efd::Point2& i_value, efd::utf8string& o_result);
    static inline const char* GetNameOfType() { return "efd::Point2"; }
};

template<>
struct ParseHelper< efd::Point3 >
{
    static inline bool FromString(const efd::utf8string& i_value, efd::Point3& o_result);
    static inline bool ToString(const efd::Point3& i_value, efd::utf8string& o_result);
    static inline const char* GetNameOfType() { return "efd::Point3"; }
};

template<>
struct ParseHelper< efd::Point4 >
{
    static inline bool FromString(const efd::utf8string& i_value, efd::Point4& o_result);
    static inline bool ToString(const efd::Point4& i_value, efd::utf8string& o_result);
    static inline const char* GetNameOfType() { return "efd::Point4"; }
};

template<>
struct ParseHelper< efd::Matrix3 >
{
    static bool FromString(const efd::utf8string& i_value, efd::Matrix3& o_result);
    static bool ToString(const efd::Matrix3& i_value, efd::utf8string& o_result);
    static const char* GetNameOfType() { return "efd::Matrix3"; }
};

template<>
struct ParseHelper< efd::Color >
{
    static inline bool FromString(const efd::utf8string& i_value, efd::Color& o_result);
    static inline bool ToString(const efd::Color& i_value, efd::utf8string& o_result);
    static inline const char* GetNameOfType() { return "efd::Color"; }
};

template<>
struct ParseHelper< efd::ColorA >
{
    static inline bool FromString(const efd::utf8string& i_value, efd::ColorA& o_result);
    static inline bool ToString(const efd::ColorA& i_value, efd::utf8string& o_result);
    static inline const char* GetNameOfType() { return "efd::ColorA"; }
};

template<>
struct ParseHelper< efd::ID128 >
{
    static inline bool FromString(const efd::utf8string& i_value, efd::ID128& o_result);
    static inline bool ToString(const efd::ID128& i_value, efd::utf8string& o_result);
    static inline const char* GetNameOfType() { return "efd::ID128"; }
};

template<>
struct ParseHelper< efd::AssetID >
{
    static inline bool FromString(const efd::utf8string& i_value, efd::AssetID& o_result);
    static inline bool ToString(const efd::AssetID& i_value, efd::utf8string& o_result);
    static inline const char* GetNameOfType() { return "efd::AssetID"; }
};


} // end namespace efd


#include <efd/ParseHelper.inl>


#endif // EE_PARSEHELPER_H
