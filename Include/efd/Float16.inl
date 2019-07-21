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
// http://www.emergent.net//


namespace efd
{

//--------------------------------------------------------------------------------------------------
inline Float16::Float16()
{
}

//--------------------------------------------------------------------------------------------------
inline void Float16::Set(efd::Float32 i_f)
{
    if (i_f >= FLOAT16_MIN || i_f <= -FLOAT16_MIN)
    {
        union
        {
            float f;
            efd::UInt32 ui;
        } val;

        val.f = i_f;
        efd::UInt32 uiData = val.ui;
        m_uiData = efd::UInt16(
            ((uiData >> 16) & 0x8000) |
            (((((uiData >> 23) & 0xFF) - 127) + 15) << 10) |
            ((uiData >> (23-10)) & 0x3FF));
    }
    else
    {
        m_uiData = 0;
    }
}

//--------------------------------------------------------------------------------------------------
inline efd::Float32 Float16::Get() const
{
    if (m_uiData)
    {
        union
        {
            efd::Float32 f;
            efd::UInt32 ui;
        } val;
        efd::UInt32 uiData = m_uiData;
        val.ui =
            ((uiData & 0x8000) << 16) |
            ((((uiData >> 10) & 0x1F) + (127-15)) << 23) |
            ((uiData & 0x3FF) << (23-10));
        return val.f;
    }
    else
    {
        return 0;
    }
}

//--------------------------------------------------------------------------------------------------
inline Float16::Float16(const Float16& f)
{
    m_uiData = f.m_uiData;
}

//--------------------------------------------------------------------------------------------------
inline Float16::Float16(efd::Float32 f)
{
    Set(f);
}

//--------------------------------------------------------------------------------------------------
inline efd::UInt16 Float16::GetData() const
{
    return m_uiData;
}

//--------------------------------------------------------------------------------------------------
inline Float16::operator float () const
{
    return Get();
}

//--------------------------------------------------------------------------------------------------
inline Float16 Float16::operator - () const
{
    Float16 f;
    f.m_uiData = m_uiData ^ 0x8000;
    return f;
}

//--------------------------------------------------------------------------------------------------
inline Float16& Float16::operator = (Float16 f)
{
    m_uiData = f.m_uiData;
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline Float16& Float16::operator = (efd::Float32 f)
{
    Set(f);
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline Float16& Float16::operator += (Float16 f)
{
    Set(Get() + (float)f);
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline Float16& Float16::operator += (efd::Float32 f)
{
    Set(Get() + f);
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline Float16& Float16::operator -= (Float16 f)
{
    Set(Get() - (float)f);
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline Float16& Float16::operator -= (efd::Float32 f)
{
    Set(Get() - f);
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline Float16& Float16::operator *= (Float16 f)
{
    Set(Get() * (float)f);
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline Float16& Float16::operator *= (float f)
{
    Set(Get() * f);
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline Float16& Float16::operator /= (Float16 f)
{
    Set(Get() / (float)f);
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline Float16& Float16::operator /= (efd::Float32 f)
{
    Set(Get() / f);
    return *this;
}

//--------------------------------------------------------------------------------------------------
inline bool Float16::operator == (Float16 f) const
{
    return (m_uiData == f.m_uiData);
}

//--------------------------------------------------------------------------------------------------
inline bool Float16::operator == (efd::Float32 f) const
{
    Float16 f16(f);
    return (m_uiData == f16.m_uiData);
}

//--------------------------------------------------------------------------------------------------
inline bool Float16::operator == (const efd::Float64& d) const
{
    Float16 f((float)d);
    return (m_uiData == f.m_uiData);
}

//--------------------------------------------------------------------------------------------------
inline bool Float16::operator != (Float16 f) const
{
    return (m_uiData != f.m_uiData);
}

//--------------------------------------------------------------------------------------------------
inline bool Float16::operator != (efd::Float32 f) const
{
    Float16 f16(f);
    return (m_uiData != f16.m_uiData);
}

//--------------------------------------------------------------------------------------------------
inline bool Float16::operator != (const efd::Float64& d) const
{
    Float16 f((efd::Float32)d);
    return (m_uiData != f.m_uiData);
}

//--------------------------------------------------------------------------------------------------

} // end namespace efd
