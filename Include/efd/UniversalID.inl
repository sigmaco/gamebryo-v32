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

namespace efd
{

//--------------------------------------------------------------------------------------------------
inline UniversalID::UniversalID()
: m_uid(0)
{
}


//--------------------------------------------------------------------------------------------------
inline UniversalID::UniversalID(efd::UInt64 i_id)
: m_uid(i_id)
{
}


//--------------------------------------------------------------------------------------------------
inline UniversalID::UniversalID(const UniversalID& i_uid)
: m_uid(i_uid.m_uid)
{
}


//--------------------------------------------------------------------------------------------------
inline UniversalID& UniversalID::operator=(const efd::UInt64& other)
{
    m_uid = other;
    return *this;
}


//--------------------------------------------------------------------------------------------------
inline UniversalID& UniversalID::operator=(const UniversalID& other)
{
    m_uid = other.m_uid;
    return *this;
}


//--------------------------------------------------------------------------------------------------
inline bool UniversalID::operator==(const UniversalID& other) const
{
    return m_uid == other.m_uid;
}


//--------------------------------------------------------------------------------------------------
inline bool UniversalID::operator!=(const UniversalID& other) const
{
    return m_uid != other.m_uid;
}


//--------------------------------------------------------------------------------------------------
inline bool UniversalID::operator<(const UniversalID& rhs) const
{
    return m_uid < rhs.m_uid;
}


//--------------------------------------------------------------------------------------------------
inline bool UniversalID::operator>(const UniversalID &lhs) const
{
    return m_uid > lhs.m_uid;
}


//--------------------------------------------------------------------------------------------------
inline bool UniversalID::IsValid() const
{
    return 0 != m_uid;
}


//--------------------------------------------------------------------------------------------------
inline bool UniversalID::operator!() const
{
    return !m_uid;
}


//--------------------------------------------------------------------------------------------------
inline efd::UInt64 UniversalID::GetValue() const
{
    return m_uid;
}

//--------------------------------------------------------------------------------------------------
inline efd::Bool UniversalID::GetSystem() const
{
    return 0 != UID_GET_VALUE(UserDefinedID,system);
}


//--------------------------------------------------------------------------------------------------
inline efd::Bool UniversalID::SetSystem(efd::Bool i_system)
{
    if (i_system)
    {
        UID_SET_VALUE(UserDefinedID,system, 1);
    }
    else
    {
        UID_SET_VALUE(UserDefinedID,system, 0);
    }
    return true;
}

} // end namespace efd
