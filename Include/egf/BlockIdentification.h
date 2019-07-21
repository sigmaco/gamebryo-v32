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
#ifndef EE_BLOCKIDENTIFICATION_H
#define EE_BLOCKIDENTIFICATION_H

#include <egf/egfLibType.h>
#include <efd/AssetID.h>


namespace egf
{

/**
    To support instancing of blocks both an AssetID and an instance number are needed to fully
    specify a block. The BlockIdentification class stores this combined information.
*/
class EE_EGF_ENTRY BlockIdentification : public efd::MemObject
{
public:
    /// @name Construction
    //@{
    inline BlockIdentification();

    inline BlockIdentification(const efd::AssetID& asset, efd::UInt32 instance = 0);
    inline BlockIdentification(const efd::utf8string& asset, efd::UInt32 instance = 0);
    inline BlockIdentification(const char* asset, efd::UInt32 instance = 0);

    inline BlockIdentification(const BlockIdentification& other);
    //@}

    /// Casting operator for treating this class as an efd::AssetID
    inline operator efd::AssetID();
    inline operator const efd::AssetID() const;

    /// Helper method to call GetURN on the AssetID of this block
    inline const efd::utf8string& GetURN() const;

    /// Helper method to call IsUUID on the AssetID of this block
    inline bool IsUUID() const;

    bool operator == (const BlockIdentification& other) const;
    bool operator != (const BlockIdentification& other) const;
    inline bool operator < (const BlockIdentification& other) const;
    bool operator > (const BlockIdentification& other) const;
    bool operator <= (const BlockIdentification& other) const;
    bool operator >= (const BlockIdentification& other) const;

    void Serialize(efd::Archive& io_ar);

    efd::AssetID m_blockAsset;
    efd::UInt32 m_instance;
};

} // end namespace egf

#include <egf/BlockIdentification.inl>

#endif // EE_BLOCKIDENTIFICATION_H
