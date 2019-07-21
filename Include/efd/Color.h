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
#ifndef EE_COLOR_H
#define EE_COLOR_H

#include <efd/MemObject.h>
#include <efd/EEMath.h>

namespace efd
{
class Archive;
class ColorA_UInt8;

/**
    This class represents floating-point RGB colors without alpha.  Normally,
    colors are assumed to range between 0.0 and 1.0 for each component, but
    this assumption is not required inherently.  The m_r, m_g, and m_b data
    members are all declared public for application convenience.
*/
class EE_EFD_ENTRY Color : public MemObject
{
public:
#if !defined(SWIG)
    union
    {
        efd::Float32 m_r;
        efd::Float32 r;
    };

    union
    {
        efd::Float32 m_g;
        efd::Float32 g;
    };

    union
    {
        efd::Float32 m_b;
        efd::Float32 b;
    };
#else
    // SWIG doesn't support nested unions
    efd::Float32 r;
    efd::Float32 g;
    efd::Float32 b;
#endif

    /**
        Constructs a new color instance. If no parameters are specified, the
        color set set to (0,0,0) or black.
    */
    inline Color(efd::Float32 initR = 0.0f, efd::Float32 initG = 0.0f, efd::Float32 initB = 0.0f);

    /**
        Assigns a single scalar value to this color object.
        @param scalar The scalar value. This is copied to each color channel.
        @return A reference to this color instance.
    */
    inline Color& operator=(efd::Float32 scalar);

    /**
        Performs an <b>EXACT</b> equality test.
        @param c The color with which to compare to this one.
        @return True if exactly equal, false otherwise.
    */
    inline bool operator==(const Color& c) const;

    /**
        Performs an <b>EXACT</b> in-equality test.
        @param c The color with which to compare to this one.
        @return True if not equal, false otherwise.
    */
    inline bool operator!=(const Color& c) const;

    /**
        Member wise addition.
        @param c The color to add to this one.
        @return A new color representing the addition of this color and the
            other color.
    */
    inline Color operator+(const Color& c) const;

    /**
        Member wise subtraction.
        @param c The color to subtract from this one.
        @return A new color representing the difference of this color and the
            other color.
    */
    inline Color operator-(const Color& c) const;

    /**
        Scales all channels of this color by the specified scalar.
        @param scalar The scalar value to apply to this color.
        @return A new color representing the scaled version of this color.
        @note This color is not modified.
    */
    inline Color operator*(efd::Float32 scalar) const;

    /**
        Member wise multiplication of two colors. (NOT a dot product)
        @param c Color value to multiply with this one.
        @return A new color representing the product of this color and the one
            specified.
    */
    inline Color operator*(const Color& c) const;

    /**
        Divides all channels of this color by the specified scalar.
        @param scalar The scalar with which to divide.
        @return A new color representing the division of this color by the
            specified scalar.
    */
    inline Color operator/(efd::Float32 scalar) const;

    /**
        Member wise division.
        @param c Color with which to divide.
        @return A new color containing the member wise division of this color
            by the specified color.
    */
    inline Color operator/(const Color& c) const;

    /**
        Unary negation.
        @return A new color containing the negated version of this color.
    */
    inline Color operator-() const;

    /**
        Multiples a color and a scalar.
        @param scalar Scalar to apply to the color.
        @param c Color with which to scale.
        @return A new color containing the scaled version of the color
            specified.
    */
    EE_EFD_ENTRY friend Color operator*(efd::Float32 scalar, const Color& c);

    /**
        In place addition.
        @param c The color to add with this color.
        @return A reference to this color plus the specified color.
    */
    inline Color& operator+=(const Color& c);

    /**
        In place subtraction.
        @param c The color to subtract from this color.
        @return A reference to this color minus the specified color.
    */
    inline Color& operator-=(const Color& c);

    /**
        In place color scale.
        @param scalar The amount with which to scale this color.
        @return A reference to this color scaled by the specified scalar.
    */
    inline Color& operator*=(efd::Float32 scalar);

    /**
        In place member wise multiplication. (NOT a dot product)
        @param c The color to multiply with this color.
        @return A reference to this color multiplied with the specified color.
    */
    inline Color& operator*=(const Color& c);

    /**
        In place division.
        @param scalar A scalar value with which to divide.
        @return A reference to this color divided by the specified scalar.
    */
    inline Color& operator/=(efd::Float32 scalar);

    /**
        In place member wise division.
        @param c The color with which to divide.
        @return A reference to this color divided by the specified color.
    */
    inline Color& operator/=(const Color& c);

    /**
        Ensure RGB components are within the range [0.0,1.0] by clamping any
        components above 1.0 to 1.0. Note that all the components are assumed
        to be >= 0.0, so no such check is performed.
    */
    inline void Clamp();

    /**
        Ensure RGB components are within the range [0.0,1.0] by scaling down
        all components by the max component. This function sets the components
        in the correct range and preserves the hue of the final color. Note
        that all the components are assumed to be >= 0.0, so no such check is
        performed.
    */
    inline void Scale();

    /// Function to return the color as an unsigned integer.
    inline void GetAs(ColorA_UInt8& kColor) const;

    /// Convenience color representing white. (1,1,1)
    static const Color WHITE;

    /// Convenience color representing black. (0,0,0)
    static const Color BLACK;

#if !defined(SWIG)
    /// Serialization
    void Serialize(efd::Archive& ar);
#endif
};


/**
    This class represents floating-point RGBA colors. Normally, colors are
    assumed to be in the range [0.0,1.0] for each component, but this
    assumption is not required inherently. The data members m_r, m_g, m_b, and
    m_a are all declared public for application convenience.
*/
class EE_EFD_ENTRY ColorA : public MemObject
{
public:
#if !defined(SWIG)
    union
    {
        efd::Float32 m_r;
        efd::Float32 r;
    };

    union
    {
        efd::Float32 m_g;
        efd::Float32 g;
    };

    union
    {
        efd::Float32 m_b;
        efd::Float32 b;
    };

    union
    {
        efd::Float32 m_a;
        efd::Float32 a;
    };
#else
        // SWIG doesn't support nested unions
    efd::Float32 r;
    efd::Float32 g;
    efd::Float32 b;
    efd::Float32 a;
#endif


    /**
        Constructs a new color instance. If no parameters are specified, the
        color set set to (0,0,0,0) or translucent black.
    */
    ColorA(
        efd::Float32 initR = 0.0f,
        efd::Float32 initG = 0.0f,
        efd::Float32 initB = 0.0f,
        efd::Float32 initA = 0.0f);

    /**
        Assigns a single scalar value to this color object.
        @param scalar The scalar value. This is copied to each color channel.
        @return A reference to this color instance.
    */
    inline ColorA& operator=(efd::Float32 scalar);

    /**
        Performs an <b>EXACT</b> equality test.
        @param c The color with which to compare to this one.
        @return True if exactly equal, false otherwise.
    */
    inline bool operator==(const ColorA& c) const;

    /**
        Performs an <b>EXACT</b> in-equality test.
        @param c The color with which to compare to this one.
        @return True if not equal, false otherwise.
    */
    inline bool operator!=(const ColorA& c) const;

    /**
        Member wise addition.
        @param c The color to add to this one.
        @return A new color representing the addition of this color and the
            other color.
    */
    inline ColorA operator+(const ColorA& c) const;

    /**
        Member wise subtraction.
        @param c The color to subtract from this one.
        @return A new color representing the difference of this color and the
            other color.
    */
    inline ColorA operator-(const ColorA& c) const;

    /**
        Scales all channels of this color by the specified scalar.
        @param scalar The scalar value to apply to this color.
        @return A new color representing the scaled version of this color.
        @note This color is not modified.
    */
    inline ColorA operator*(efd::Float32 scalar) const;

    /**
        Member wise multiplication of two colors. (NOT a dot product)
        @param c Color value to multiply with this one.
        @return A new color representing the product of this color and the one
            specified.
    */
    inline ColorA operator*(const ColorA& c) const;

    /**
        Divides all channels of this color by the specified scalar.
        @param scalar The scalar with which to divide.
        @return A new color representing the division of this color by the
            specified scalar.
    */
    inline ColorA operator/(efd::Float32 scalar) const;

    /**
        Member wise division.
        @param c Color with which to divide.
        @return A new color containing the member wise division of this color
            by the specified color.
    */
    inline ColorA operator/(const ColorA& c) const;

    /**
        Unary negation.
        @return A new color containing the negated version of this color.
    */
    inline ColorA operator-() const;

    /**
        Multiples a color and a scalar.
        @param scalar Scalar to apply to the color.
        @param c Color with which to scale.
        @return A new color containing the scaled version of the color
            specified.
    */
    EE_EFD_ENTRY friend ColorA operator*(
        efd::Float32 scalar,
        const ColorA& c);

    /**
        In place addition.
        @param c The color to add with this color.
        @return A reference to this color plus the specified color.
    */
    inline ColorA& operator+=(const ColorA& c);

    /**
        In place subtraction.
        @param c The color to subtract from this color.
        @return A reference to this color minus the specified color.
    */
    inline ColorA& operator-=(const ColorA& c);

    /**
        In place color scale.
        @param scalar The amount with which to scale this color.
        @return A reference to this color scaled by the specified scalar.
    */
    inline ColorA& operator*=(efd::Float32 scalar);

    /**
        In place member wise multiplication. (NOT a dot product)
        @param c The color to multiply with this color.
        @return A reference to this color multiplied with the specified color.
    */
    inline ColorA& operator*=(const ColorA& c);

    /**
        In place division.
        @param scalar A scalar value with which to divide.
        @return A reference to this color divided by the specified scalar.
    */
    inline ColorA& operator/=(efd::Float32 scalar);

    /**
        In place member wise division.
        @param c The color with which to divide.
        @return A reference to this color divided by the specified color.
    */
    inline ColorA& operator/=(const ColorA& c);

    /**
        Ensure RGBA components are within the range [0.0,1.0] by clamping any
        components above 1.0 to 1.0. Note that all the components are assumed
        to be >= 0.0, so no such check is performed.
    */
    inline void Clamp();

    /**
        Ensure RGBA components are within the range [0.0,1.0] by scaling down
        all components by the max component. This function sets the components
        in the correct range and preserves the hue of the final color. Note
        that all the components are assumed to be >= 0.0, so no such check is
        performed.
    */
    inline void Scale();

    /// Function to return the color as an unsigned integer.
    inline void GetAs(ColorA_UInt8& kColor) const;

    /// Convenience color representing opaque white. (1,1,1,1)
    static const ColorA WHITE;

    /// Convenience color representing opaque black. (0,0,0,1)
    static const ColorA BLACK;  // (0,0,0,1)

#if !defined(SWIG)
    /// Serialization
    void Serialize(efd::Archive& ar);
#endif
};

/**
    Same as ColorA but using efd::UInt8 for r,g,b and a instead of efd::Float32
*/
class EE_EFD_ENTRY ColorA_UInt8 : public MemObject
{
public:

    inline ColorA_UInt8 (efd::UInt8 uiR = 0, efd::UInt8 uiG = 0, efd::UInt8 uiB = 0,
        efd::UInt8 uiA = 0);

    inline efd::UInt8& r();
    inline const efd::UInt8& r() const;
    inline efd::UInt8& g();
    inline const efd::UInt8& g() const;
    inline efd::UInt8& b();
    inline const efd::UInt8& b() const;
    inline efd::UInt8& a();
    inline const efd::UInt8& a() const;

    inline ColorA_UInt8& operator= (efd::UInt8 uiValue);
    inline bool operator== (const ColorA_UInt8& c) const;
    inline bool operator!= (const ColorA_UInt8& c) const;

    inline ColorA_UInt8 operator+ (const ColorA_UInt8& c) const;
    inline ColorA_UInt8 operator- (const ColorA_UInt8& c) const;
    inline ColorA_UInt8 operator* (float fScalar) const;
    inline ColorA_UInt8 operator* (const ColorA_UInt8& c) const;
    inline ColorA_UInt8 operator/ (float fScalar) const;
    inline ColorA_UInt8 operator/ (const ColorA_UInt8& c) const;
    inline ColorA_UInt8 operator- () const;
    EE_EFD_ENTRY friend ColorA_UInt8 operator* (float fScalar, const ColorA_UInt8& c);

    inline ColorA_UInt8& operator+= (const ColorA_UInt8& c);
    inline ColorA_UInt8& operator-= (const ColorA_UInt8& c);
    inline ColorA_UInt8& operator*= (float fScalar);
    inline ColorA_UInt8& operator*= (const ColorA_UInt8& c);
    inline ColorA_UInt8& operator/= (float fScalar);
    inline ColorA_UInt8& operator/= (const ColorA_UInt8& c);

    // Function to return the color as an unsigned integer.
    inline void GetAs(efd::UInt32& uiColor) const;
    inline void GetAsBGRA(efd::UInt32& uiColor) const;

    // Function to return the color as floats between 0 - 1.
    inline void GetAs(Color& kColor) const;
    inline void GetAs(ColorA& kColor) const;


    static const ColorA_UInt8 WHITE; // (1,1,1,1)
    static const ColorA_UInt8 BLACK; // (0,0,0,1)

#if !defined(SWIG)
    /// Serialization
    void Serialize(efd::Archive& ar);
#endif

protected:
#if !defined(SWIG)
    struct ColorComponents
    {
        efd::UInt8 r, g, b, a;
    };

    union
    {
        ColorComponents m_kColor;
        efd::UInt32 m_uiColor;
    };
#else
    // SWIG doesn't support nested unions/structs.
    efd::UInt8 r;
    efd::UInt8 g;
    efd::UInt8 b;
    efd::UInt8 a;
#endif
};

//------------------------------------------------------------------------------------------------
//  Inline include
#include <efd/Color.inl>

} // end namespace efd

//------------------------------------------------------------------------------------------------

#endif
