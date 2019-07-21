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


namespace egf
{

//------------------------------------------------------------------------------------------------
inline BuiltinModelDescriptor::BuiltinModelDescriptor()
: m_id(0)
, m_traits(0)
{
}

//------------------------------------------------------------------------------------------------
inline BuiltinModelDescriptor::BuiltinModelDescriptor(const BuiltinModelDescriptor& other)
: m_name(other.m_name)
, m_id(other.m_id)
, m_traits(other.m_traits)
{
}

//------------------------------------------------------------------------------------------------
inline BuiltinModelDescriptor::~BuiltinModelDescriptor()
{
}

//------------------------------------------------------------------------------------------------
inline BuiltinModelDescriptor& BuiltinModelDescriptor::operator=(
    const BuiltinModelDescriptor& other)
{
    m_id = other.m_id;
    m_name = other.m_name;
    return *this;
}

//------------------------------------------------------------------------------------------------
inline FlatModelID BuiltinModelDescriptor::GetID() const
{
    return m_id;
}

//------------------------------------------------------------------------------------------------
inline void BuiltinModelDescriptor::SetID(FlatModelID compID)
{
    m_id = compID;
}

//------------------------------------------------------------------------------------------------
inline const efd::utf8string& BuiltinModelDescriptor::GetName() const
{
    return m_name;
}

//------------------------------------------------------------------------------------------------
inline void BuiltinModelDescriptor::SetName(const efd::utf8string& name)
{
    m_name = name;
}

//------------------------------------------------------------------------------------------------
inline efd::Bool BuiltinModelDescriptor::GetTrait(ModelTraits trait) const
{
    return efd::BitUtils::AllBitsAreSet(m_traits, (efd::UInt32)trait);
}

//------------------------------------------------------------------------------------------------
inline void BuiltinModelDescriptor::SetTrait(ModelTraits trait, efd::Bool val)
{
    m_traits = efd::BitUtils::SetBitsOnOrOff(m_traits, (efd::UInt32)trait, val);
}

//------------------------------------------------------------------------------------------------

} // end namespace egf
