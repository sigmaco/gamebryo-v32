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


//------------------------------------------------------------------------------------------------
inline efd::MemHint::Bits efd::MemHint::GetPlatform() const
{
    return(Bits)(m_eValue & 0x000000FFU);
}

//------------------------------------------------------------------------------------------------
inline efd::MemHint::Bits efd::MemHint::GetLifetime() const
{
    return(Bits)(m_eValue & 0x00000300U);
}

//------------------------------------------------------------------------------------------------
inline bool efd::MemHint::CompilerProvidesSizeOnDeallocate() const
{
    return(m_eValue & COMPILER_PROVIDES_SIZE_ON_DEALLOCATE) != 0;
}

//------------------------------------------------------------------------------------------------
inline efd::MemHint::Bits efd::MemHint::GetAccess() const
{
    return(Bits)(m_eValue & 0x0000F800U);
}

//------------------------------------------------------------------------------------------------
inline efd::MemHint::Bits efd::MemHint::GetUsage() const
{
    return(Bits)(m_eValue & 0x00FF0000U);
}

//------------------------------------------------------------------------------------------------
inline bool efd::MemHint::IsBulk() const
{
    return(m_eValue & IS_BULK) != 0;
}

//------------------------------------------------------------------------------------------------
inline bool efd::MemHint::IsCustomHint() const
{
    return(m_eValue & TYPE_CUSTOM) != 0;
}

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
inline unsigned int efd::MemHint::GetRaw() const
{
    return(unsigned int)m_eValue;
}

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
inline efd::MemHint::MemHint()
{
    m_eValue = NONE;
}

//------------------------------------------------------------------------------------------------
inline efd::MemHint::MemHint(Bits eValue)
{
    m_eValue = eValue;
}

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
inline efd::MemHint& efd::MemHint::operator|=(const efd::MemHint kRhs)
{
    m_eValue = (efd::MemHint::Bits)(m_eValue | kRhs.m_eValue);
    return *this;
}

//------------------------------------------------------------------------------------------------
inline efd::MemHint& efd::MemHint::operator|=(const efd::MemHint::Bits eRhs)
{
    m_eValue = (efd::MemHint::Bits)(m_eValue | eRhs);
    return *this;
}

//------------------------------------------------------------------------------------------------
inline efd::MemHint efd::MemHint::operator|(const efd::MemHint kRhs) const
{
    return efd::MemHint((efd::MemHint::Bits)(m_eValue | kRhs.m_eValue));
}

//------------------------------------------------------------------------------------------------
inline efd::MemHint efd::MemHint::operator|(const efd::MemHint::Bits eRhs) const
{
    return efd::MemHint((efd::MemHint::Bits)(m_eValue | eRhs));
}

//------------------------------------------------------------------------------------------------
inline bool efd::MemHint::operator==(const efd::MemHint kRHS) const
{
    return m_eValue == kRHS.m_eValue;
}

//------------------------------------------------------------------------------------------------
inline bool efd::MemHint::operator!=(const efd::MemHint kRHS) const
{
    return m_eValue != kRHS.m_eValue;
}

//------------------------------------------------------------------------------------------------
inline efd::MemHint::Bits efd::operator|(const efd::MemHint::Bits eLhs,
    const efd::MemHint::Bits eRhs)
{
    return(efd::MemHint::Bits)((unsigned int)eLhs | (unsigned int)eRhs);
}

//------------------------------------------------------------------------------------------------
