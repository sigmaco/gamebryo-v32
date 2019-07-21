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

//------------------------------------------------------------------------------------------------
inline Category::Category() : efd::UniversalID()
{
    EE_ASSERT(IsZero());    // Base constructor should leave me invalid.

    UID_SET_VALUE(ChannelID,system,1);
    UID_SET_VALUE(ChannelID,type,kIDT_ChannelID);
}

//------------------------------------------------------------------------------------------------
inline Category::~Category()
{
}

//------------------------------------------------------------------------------------------------
inline Category::Category(efd::UInt64 cat) : efd::UniversalID(cat)
{
    // Please do not remove these asserts.  If you hit these asserts, it is because you are not
    // using a Category properly.
    EE_ASSERT(IsZero() || GetSystem());
    EE_ASSERT(IsZero() || UID_GET_VALUE(InternalMasks, isCategory));
}

//------------------------------------------------------------------------------------------------
inline Category::Category(const Category &other)
    : efd::UniversalID(other)
{
    EE_ASSERT(IsZero() || GetSystem());
    EE_ASSERT(IsZero() || UID_GET_VALUE(InternalMasks, isCategory));
}

//------------------------------------------------------------------------------------------------
inline Category::Category(ExpectedChannelUsage usage, efd::UInt32 netID, efd::UInt32 baseID)
    : efd::UniversalID()
{
    UID_SET_VALUE(ChannelID,system,1);
    UID_SET_VALUE(ChannelID,type,kIDT_ChannelID);
    SetUsage(usage);
    SetNetID(netID);
    SetBaseID(baseID);
}

//------------------------------------------------------------------------------------------------
inline Category Category::operator=(efd::UInt64 rhs)
{
    UniversalID::operator=(rhs);
    EE_ASSERT(IsZero() || GetSystem());
    EE_ASSERT(IsZero() || UID_GET_VALUE(InternalMasks, isCategory));
    return *this;
}

//------------------------------------------------------------------------------------------------
inline Category Category::operator=(const Category& rhs)
{
    UniversalID::operator=(rhs);
    EE_ASSERT(IsZero() || GetSystem());
    EE_ASSERT(IsZero() || UID_GET_VALUE(InternalMasks, isCategory));
    return *this;
}

//------------------------------------------------------------------------------------------------
inline bool Category::operator==(const Category& rhs) const
{
    return m_uid == rhs.m_uid;
}

//------------------------------------------------------------------------------------------------
inline bool Category::operator!=(const Category& rhs) const
{
    return m_uid != rhs.m_uid;
}

//------------------------------------------------------------------------------------------------
inline bool Category::operator<(const Category& rhs) const
{
    return m_uid < rhs.m_uid;
}

//------------------------------------------------------------------------------------------------
inline bool Category::operator>(const Category &rhs) const
{
    return m_uid > rhs.m_uid;
}

//------------------------------------------------------------------------------------------------
inline efd::utf8string Category::ToString() const
{
    // Returning an instance *should* make the compiler give a warning if used without .c_str().
    // Since it is used for logging, performance is not a primary consideration.
    utf8string name(efd::Formatted, "Category(0x%016llX)", GetValue());
    return name;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt32 Category::GetNetID() const
{
    return UID_GET_VALUE(ChannelID,net);
}

//------------------------------------------------------------------------------------------------
inline efd::Bool Category::SetNetID(efd::UInt32 i_netID)
{
    if (i_netID > efd::BitUtils::MakeBitMask<efd::UInt32, kNumNetBits, 0>())
    {
        EE_FAIL_MESSAGE(("Category Error: Net value (%d) exceeds available space for net ID bits "
            "(%d).", i_netID, kNumNetBits));
        return false;
    }

    UID_SET_VALUE(ChannelID,net,i_netID);
    return true;
}

//------------------------------------------------------------------------------------------------
inline efd::UInt64 Category::GetBaseID() const
{
    return UID_GET_VALUE(ChannelID,base);
}

//------------------------------------------------------------------------------------------------
inline efd::Bool Category::SetBaseID(efd::UInt64 i_base)
{
    if (i_base > efd::BitUtils::MakeBitMask<efd::UInt64, kNumChannelBaseBits, 0>())
    {
        // If you hit this assert it means you are trying to construct a system Category with a
        // baseid larger than is allowed (~27bits, see declaration of kNumChannelBaseBits)
        // use a smaller number (if kNumChannelBaseBits == 27, then <= 0x07FFFFFF)
        EE_FAIL_MESSAGE(("ID Error: Base value 0x%016llX exceeds available space for Channel Base "
            "ID bits (%d).", i_base, kNumChannelBaseBits));
        return false;
    }

    UID_SET_VALUE(ChannelID,base,i_base);
    return true;
}

//------------------------------------------------------------------------------------------------
// Determines whether this category represents a valid category.  To be valid, it must have the
// system bit set and be of type Channel or EntityID, and it must have some other bits set to
// non-zero values.
inline bool Category::IsValid() const
{
    return UID_GET_VALUE(UnknownTypeID,system) && UID_GET_VALUE(InternalMasks,isCategory)
        && 0 != UID_GET_VALUE(UnknownTypeID,base);
}

//------------------------------------------------------------------------------------------------
// Note:  This function is not the opposite of IsValid.  It tests for the specific case of a
// completely zero value, which is used for the sentinel value kCAT_INVALID.  We allow a category
// to be set to all zero without assert, but any other invalid assignment will result in an
// assert.
inline bool Category::IsZero() const
{
    return m_uid == 0;
}

//------------------------------------------------------------------------------------------------
inline void Category::Serialize(efd::Archive& io_archive)
{
    efd::Serializer::SerializeObject(m_uid, io_archive);
}

//------------------------------------------------------------------------------------------------
} // end namespace efd.
