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

//--------------------------------------------------------------------------------------------------
inline Color::Color(efd::Float32 initR, efd::Float32 initG, efd::Float32 initB)
{
    m_r = initR;
    m_g = initG;
    m_b = initB;
}

//--------------------------------------------------------------------------------------------------
inline Color& Color::operator=(efd::Float32 scalar)
{
    m_r = scalar;
    m_g = scalar;
    m_b = scalar;
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline bool Color::operator==(const Color& c) const
{
    return (m_r == c.m_r && m_g == c.m_g && m_b == c.m_b);
}

//--------------------------------------------------------------------------------------------------
inline bool Color::operator!=(const Color& c) const
{
    return !(*this == c);
}

//--------------------------------------------------------------------------------------------------
inline Color Color::operator+(const Color& c) const
{
    Color result = *this;
    result.m_r += c.m_r;
    result.m_g += c.m_g;
    result.m_b += c.m_b;
    return result;
}

//--------------------------------------------------------------------------------------------------
inline Color Color::operator-(const Color& c) const
{
    Color result = *this;
    result.m_r -= c.m_r;
    result.m_g -= c.m_g;
    result.m_b -= c.m_b;
    return result;
}

//--------------------------------------------------------------------------------------------------
inline Color Color::operator*(efd::Float32 scalar) const
{
    Color result = *this;
    result.m_r *= scalar;
    result.m_g *= scalar;
    result.m_b *= scalar;
    return result;
}

//--------------------------------------------------------------------------------------------------
inline Color Color::operator*(const Color &c) const
{
    Color result = *this;
    result.m_r *= c.m_r;
    result.m_g *= c.m_g;
    result.m_b *= c.m_b;
    return result;
}

//--------------------------------------------------------------------------------------------------
inline Color Color::operator/(efd::Float32 scalar) const
{
    Color result = *this;
    result.m_r /= scalar;
    result.m_g /= scalar;
    result.m_b /= scalar;
    return result;
}

//--------------------------------------------------------------------------------------------------
inline Color Color::operator/(const Color &c) const
{
    Color result = *this;
    result.m_r /= c.m_r;
    result.m_g /= c.m_g;
    result.m_b /= c.m_b;
    return result;
}

//--------------------------------------------------------------------------------------------------
inline Color Color::operator-() const
{
    return Color(-m_r,-m_g,-m_b);
}

//--------------------------------------------------------------------------------------------------
inline Color operator*(efd::Float32 scalar, const Color& c)
{
    return c*scalar;
}

//--------------------------------------------------------------------------------------------------
inline Color& Color::operator+=(const Color& c)
{
    m_r += c.m_r;
    m_g += c.m_g;
    m_b += c.m_b;
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline Color& Color::operator-=(const Color& c)
{
    m_r -= c.m_r;
    m_g -= c.m_g;
    m_b -= c.m_b;
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline Color& Color::operator*=(efd::Float32 scalar)
{
    m_r *= scalar;
    m_g *= scalar;
    m_b *= scalar;
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline Color& Color::operator*=(const Color &c)
{
    m_r *= c.m_r;
    m_g *= c.m_g;
    m_b *= c.m_b;
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline Color& Color::operator/=(efd::Float32 scalar)
{
    m_r /= scalar;
    m_g /= scalar;
    m_b /= scalar;
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline Color& Color::operator/=(const Color &c)
{
    m_r /= c.m_r;
    m_g /= c.m_g;
    m_b /= c.m_b;
    return *this;
}

//--------------------------------------------------------------------------------------------------
void Color::Clamp()
{
    // Clamp to [0,1]^3.  Assumes that (m_r,m_g,m_b) >= (0,0,0).  This is a
    // reasonable assumption since colors are only added or multiplied in
    // the lighting system.  Note that clamping can cause significant
    // changes in the final color.
    if (m_r > 1.0f)
        m_r = 1.0f;

    if (m_g > 1.0f)
        m_g = 1.0f;

    if (m_b > 1.0f)
        m_b = 1.0f;
}

//--------------------------------------------------------------------------------------------------
void Color::Scale()
{
    // Scale down by maximum component (preserves the final color).
    Float32 maxComponent = m_r;

    if (m_g > maxComponent)
        maxComponent = m_g;
    if (m_b > maxComponent)
        maxComponent = m_b;

    if (maxComponent > 1.0f)
    {
        Float32 invMax = 1.0f/maxComponent;
        m_r *= invMax;
        m_g *= invMax;
        m_b *= invMax;
    }
}

//--------------------------------------------------------------------------------------------------
inline void Color::GetAs(ColorA_UInt8& kColor) const
{
    // Note we do not clamp or scale down the values.  If these values are out of range, you will
    // get incorrect color values.  You should use the Scale() or Clamp() operations to make sure
    // the values are in range.
    kColor.r() = (efd::UInt8)(m_r * 255.0f);
    kColor.g() = (efd::UInt8)(m_g * 255.0f);
    kColor.b() = (efd::UInt8)(m_b * 255.0f);
    kColor.a() = 255;
}

//--------------------------------------------------------------------------------------------------
inline ColorA::ColorA(efd::Float32 initR, efd::Float32 initG, efd::Float32 initB,
    efd::Float32 initA)
{
    m_r = initR;
    m_g = initG;
    m_b = initB;
    m_a = initA;
}

//--------------------------------------------------------------------------------------------------
inline ColorA& ColorA::operator=(efd::Float32 scalar)
{
    m_r = scalar;
    m_g = scalar;
    m_b = scalar;
    m_a = scalar;
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline bool ColorA::operator==(const ColorA& c) const
{
    return (m_r == c.m_r && m_g == c.m_g && m_b == c.m_b && m_a == c.m_a);
}

//--------------------------------------------------------------------------------------------------
inline bool ColorA::operator!= (const ColorA& c) const
{
    return !(*this == c);
}

//--------------------------------------------------------------------------------------------------
inline ColorA ColorA::operator+(const ColorA& c) const
{
    ColorA result = *this;
    result.m_r += c.m_r;
    result.m_g += c.m_g;
    result.m_b += c.m_b;
    result.m_a += c.m_a;
    return result;
}

//--------------------------------------------------------------------------------------------------
inline ColorA ColorA::operator-(const ColorA& c) const
{
    ColorA result = *this;
    result.m_r -= c.m_r;
    result.m_g -= c.m_g;
    result.m_b -= c.m_b;
    result.m_a -= c.m_a;
    return result;
}

//--------------------------------------------------------------------------------------------------
inline ColorA ColorA::operator*(efd::Float32 scalar) const
{
    ColorA result = *this;
    result.m_r *= scalar;
    result.m_g *= scalar;
    result.m_b *= scalar;
    result.m_a *= scalar;
    return result;
}

//--------------------------------------------------------------------------------------------------
inline ColorA ColorA::operator*(const ColorA &c) const
{
    ColorA result = *this;
    result.m_r *= c.m_r;
    result.m_g *= c.m_g;
    result.m_b *= c.m_b;
    result.m_a *= c.m_a;
    return result;
}

//--------------------------------------------------------------------------------------------------
inline ColorA ColorA::operator/(efd::Float32 scalar) const
{
    ColorA result = *this;
    result.m_r /= scalar;
    result.m_g /= scalar;
    result.m_b /= scalar;
    result.m_a /= scalar;
    return result;
}

//--------------------------------------------------------------------------------------------------
inline ColorA ColorA::operator/(const ColorA &c) const
{
    ColorA result = *this;
    result.m_r /= c.m_r;
    result.m_g /= c.m_g;
    result.m_b /= c.m_b;
    result.m_a /= c.m_a;
    return result;
}

//--------------------------------------------------------------------------------------------------
inline ColorA ColorA::operator-() const
{
    return ColorA(-m_r,-m_g,-m_b,-m_a);
}

//--------------------------------------------------------------------------------------------------
inline ColorA operator*(efd::Float32 scalar, const ColorA& c)
{
    return c*scalar;
}

//--------------------------------------------------------------------------------------------------
inline ColorA& ColorA::operator+=(const ColorA& c)
{
    m_r += c.m_r;
    m_g += c.m_g;
    m_b += c.m_b;
    m_a += c.m_a;
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline ColorA& ColorA::operator-=(const ColorA& c)
{
    m_r -= c.m_r;
    m_g -= c.m_g;
    m_b -= c.m_b;
    m_a -= c.m_a;
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline ColorA& ColorA::operator*=(efd::Float32 scalar)
{
    m_r *= scalar;
    m_g *= scalar;
    m_b *= scalar;
    m_a *= scalar;
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline ColorA& ColorA::operator*=(const ColorA &c)
{
    m_r *= c.m_r;
    m_g *= c.m_g;
    m_b *= c.m_b;
    m_a *= c.m_a;
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline ColorA& ColorA::operator/=(efd::Float32 scalar)
{
    m_r /= scalar;
    m_g /= scalar;
    m_b /= scalar;
    m_a /= scalar;
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline ColorA& ColorA::operator/=(const ColorA &c)
{
    m_r /= c.m_r;
    m_g /= c.m_g;
    m_b /= c.m_b;
    m_a /= c.m_a;
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline void ColorA::Clamp()
{
    // Clamp to [0,1]^4.  Assumes that (m_r,m_g,m_b,m_a) >= (0,0,0).  This is a
    // reasonable assumption since colors are only added or multiplied in
    // the lighting system.  Note that clamping can cause significant
    // changes in the final color.
    if (m_r > 1.0f)
        m_r = 1.0f;

    if (m_g > 1.0f)
        m_g = 1.0f;

    if (m_b > 1.0f)
        m_b = 1.0f;

    if (m_a > 1.0f)
        m_a = 1.0f;
}

//--------------------------------------------------------------------------------------------------
void ColorA::Scale()
{
    // Scale down by maximum component (preserves the final color).
    Float32 maxComponent = m_r;

    if (m_g > maxComponent)
        maxComponent = m_g;
    if (m_b > maxComponent)
        maxComponent = m_b;

    if (maxComponent > 1.0f)
    {
        Float32 invMax = 1.0f/maxComponent;
        m_r *= invMax;
        m_g *= invMax;
        m_b *= invMax;
    }

    if (m_a > 1.0f)
        m_a = 1.0f;
}

//--------------------------------------------------------------------------------------------------
inline void ColorA::GetAs(ColorA_UInt8& kColor) const
{
    // Node we do not clamp or scale down the values.  If these values are
    // out of range you will get incorrect color values.  You should use the
    // Scale() or Clamp() operations to make sure the values are in range.
    kColor.r() = (efd::UInt8)(m_r * 255.0f);
    kColor.g() = (efd::UInt8)(m_g * 255.0f);
    kColor.b() = (efd::UInt8)(m_b * 255.0f);
    kColor.a() = (efd::UInt8)(m_a * 255.0f);
}

//--------------------------------------------------------------------------------------------------



inline ColorA_UInt8::ColorA_UInt8(efd::UInt8 uiR, efd::UInt8 uiG, efd::UInt8 uiB, efd::UInt8 uiA)
{
    r() = uiR;
    g() = uiG;
    b() = uiB;
    a() = uiA;
}

//--------------------------------------------------------------------------------------------------
inline efd::UInt8& ColorA_UInt8::r()
{
    return m_kColor.r;
}

//--------------------------------------------------------------------------------------------------
inline const efd::UInt8& ColorA_UInt8::r() const
{
    return m_kColor.r;
}

//--------------------------------------------------------------------------------------------------
inline efd::UInt8& ColorA_UInt8::g()
{
    return m_kColor.g;
}

//--------------------------------------------------------------------------------------------------
inline const efd::UInt8& ColorA_UInt8::g() const
{
    return m_kColor.g;
}

//--------------------------------------------------------------------------------------------------
inline efd::UInt8& ColorA_UInt8::b()
{
    return m_kColor.b;
}

//--------------------------------------------------------------------------------------------------
inline const efd::UInt8& ColorA_UInt8::b() const
{
    return m_kColor.b;
}

//--------------------------------------------------------------------------------------------------
inline efd::UInt8& ColorA_UInt8::a()
{
    return m_kColor.a;
}

//--------------------------------------------------------------------------------------------------
inline const efd::UInt8& ColorA_UInt8::a() const
{
    return m_kColor.a;
}

//--------------------------------------------------------------------------------------------------
inline ColorA_UInt8& ColorA_UInt8::operator= (efd::UInt8 uiValue)
{
    r() = uiValue;
    g() = uiValue;
    b() = uiValue;
    a() = uiValue;
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline bool ColorA_UInt8::operator== (const ColorA_UInt8& c) const
{
    return (r() == c.r() && g() == c.g() && b() == c.b() && a() == c.a());
}

//--------------------------------------------------------------------------------------------------
inline bool ColorA_UInt8::operator!= (const ColorA_UInt8& c) const
{
    return !(*this == c);
}

//--------------------------------------------------------------------------------------------------
inline ColorA_UInt8 ColorA_UInt8::operator+ (const ColorA_UInt8& c) const
{
    ColorA_UInt8 result;
    result.r() = (efd::UInt8)Min(255, r() + c.r());
    result.g() = (efd::UInt8)Min(255, g() + c.g());
    result.b() = (efd::UInt8)Min(255, b() + c.b());
    result.a() = (efd::UInt8)Min(255, a() + c.a());
    return result;
}

//--------------------------------------------------------------------------------------------------
inline ColorA_UInt8 ColorA_UInt8::operator- (const ColorA_UInt8& c) const
{
    ColorA_UInt8 result;
    result.r() = (efd::UInt8)Max(0, r() - c.r());
    result.g() = (efd::UInt8)Max(0, g() - c.g());
    result.b() = (efd::UInt8)Max(0, b() - c.b());
    result.a() = (efd::UInt8)Max(0, a() - c.a());
    return result;
}

//--------------------------------------------------------------------------------------------------
inline ColorA_UInt8 ColorA_UInt8::operator* (float fScalar) const
{
    ColorA_UInt8 result;
    result.r() = (efd::UInt8)Min(255.0f, (float)r() * fScalar);
    result.g() = (efd::UInt8)Min(255.0f, (float)g() * fScalar);
    result.b() = (efd::UInt8)Min(255.0f, (float)b() * fScalar);
    result.a() = (efd::UInt8)Min(255.0f, (float)a() * fScalar);
    return result;
}

//--------------------------------------------------------------------------------------------------
inline ColorA_UInt8 ColorA_UInt8::operator* (const ColorA_UInt8 &c) const
{
    ColorA_UInt8 result;
    result.r() = (efd::UInt8)Min(255, r() * c.r());
    result.g() = (efd::UInt8)Min(255, g() * c.g());
    result.b() = (efd::UInt8)Min(255, b() * c.b());
    result.a() = (efd::UInt8)Min(255, a() * c.a());
    return result;
}

//--------------------------------------------------------------------------------------------------
inline ColorA_UInt8 ColorA_UInt8::operator/ (float fScalar) const
{
    ColorA_UInt8 result;
    result.r() = (efd::UInt8)((float)r() / fScalar);
    result.g() = (efd::UInt8)((float)g() / fScalar);
    result.b() = (efd::UInt8)((float)b() / fScalar);
    result.a() = (efd::UInt8)((float)a() / fScalar);
    return result;
}

//--------------------------------------------------------------------------------------------------
inline ColorA_UInt8 ColorA_UInt8::operator/ (const ColorA_UInt8 &c) const
{
    ColorA_UInt8 result;
    result.r() = r() / c.r();
    result.g() = g() / c.g();
    result.b() = b() / c.b();
    result.a() = a() / c.a();
    return result;
}

//--------------------------------------------------------------------------------------------------
inline ColorA_UInt8 ColorA_UInt8::operator- () const
{
    return ColorA_UInt8(-r(),-g(),-b(),-a());
}

//--------------------------------------------------------------------------------------------------
inline ColorA_UInt8 operator* (float fScalar, const ColorA_UInt8& c)
{
    return c*fScalar;
}

//--------------------------------------------------------------------------------------------------
inline ColorA_UInt8& ColorA_UInt8::operator+= (const ColorA_UInt8& c)
{
    r() = (efd::UInt8)Min(255, r() + c.r());
    g() = (efd::UInt8)Min(255, g() + c.g());
    b() = (efd::UInt8)Min(255, b() + c.b());
    a() = (efd::UInt8)Min(255, a() + c.a());
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline ColorA_UInt8& ColorA_UInt8::operator-= (const ColorA_UInt8& c)
{
    r() = (efd::UInt8)Max(0, r() - c.r());
    g() = (efd::UInt8)Max(0, g() - c.g());
    b() = (efd::UInt8)Max(0, b() - c.b());
    a() = (efd::UInt8)Max(0, a() - c.a());
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline ColorA_UInt8& ColorA_UInt8::operator*= (float fScalar)
{
    r() = (efd::UInt8)Min(255.0f, (float)r() * fScalar);
    g() = (efd::UInt8)Min(255.0f, (float)g() * fScalar);
    b() = (efd::UInt8)Min(255.0f, (float)b() * fScalar);
    a() = (efd::UInt8)Min(255.0f, (float)a() * fScalar);
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline ColorA_UInt8& ColorA_UInt8::operator*= (const ColorA_UInt8 &c)
{
    r() = (efd::UInt8)Min(255, r() * c.r());
    g() = (efd::UInt8)Min(255, g() * c.g());
    b() = (efd::UInt8)Min(255, b() * c.b());
    a() = (efd::UInt8)Min(255, a() * c.a());
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline ColorA_UInt8& ColorA_UInt8::operator/= (float fScalar)
{
    r() = (efd::UInt8)((float)r() / fScalar);
    g() = (efd::UInt8)((float)g() / fScalar);
    b() = (efd::UInt8)((float)b() / fScalar);
    a() = (efd::UInt8)((float)a() / fScalar);
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline ColorA_UInt8& ColorA_UInt8::operator/= (const ColorA_UInt8 &c)
{
    r() = (efd::UInt8)(r() / c.r());
    g() = (efd::UInt8)(g() / c.g());
    b() = (efd::UInt8)(b() / c.b());
    a() = (efd::UInt8)(a() / c.a());
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline void ColorA_UInt8::GetAs(efd::UInt32& uiColor) const
{
    // We simply return the color value as a NiUInt32
    uiColor = m_uiColor;
}

//--------------------------------------------------------------------------------------------------
inline void ColorA_UInt8::GetAsBGRA(efd::UInt32& uiColor) const
{
    // We need to flip b and r.
    ColorA_UInt8 result(b(), g(), r(), a());
    uiColor = result.m_uiColor;
}

//--------------------------------------------------------------------------------------------------
inline void ColorA_UInt8::GetAs(Color& kColor) const
{
    kColor.m_r = ((float)r() / 255.0f);
    kColor.m_g = ((float)g() / 255.0f);
    kColor.m_b = ((float)b() / 255.0f);
}

//--------------------------------------------------------------------------------------------------
inline void ColorA_UInt8::GetAs(ColorA& kColor) const
{
    kColor.m_r = ((float)r() / 255.0f);
    kColor.m_g = ((float)g() / 255.0f);
    kColor.m_b = ((float)b() / 255.0f);
    kColor.m_a = ((float)a() / 255.0f);
}

//--------------------------------------------------------------------------------------------------
