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
inline egf::IProperty::~IProperty()
{
}

//------------------------------------------------------------------------------------------------
inline void egf::IProperty::SerializeProperty(egf::PropertyID i_propID, efd::Archive& ar) const
{
    EE_ASSERT(ar.IsPacking());
    const_cast<IProperty*>(this)->SerializeProperty(i_propID, ar);
}

//------------------------------------------------------------------------------------------------
