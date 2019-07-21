// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION.
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
#ifndef EE_ASSETID_H
#define EE_ASSETID_H

#include <efd/UniversalTypes.h>
#include <efd/MemObject.h>
#include <efd/utf8string.h>
#include <efd/SerializeEfdHelpers.h>

namespace efd
{

/**
    Encapsulation of an individual asset ID. This can hold either a fully qualified UUID or
    a logical asset identifier.
 */
class EE_EFD_ENTRY AssetID : public MemObject
{
public:

    /**
        Caching hint for the asset. This hint can be used to intelligently cache assets in
        the system.
    */
    enum CachingPolicy
    {
        /// The asset is never cached. Each fetch reads the asset from disk.
        NEVER_CACHE,
        /// Cache the asset when appropriate.
        CACHE,
        /// Always keep this asset cached for quick lookup.
        ALWAYS_CACHE,
    };

    /// @name Construction and Destruction
    //@{

    /// Default constructor.
    inline AssetID();

    /**
        Construct a new AssetID from a URN.

        @param urn The URN for the asset.
        @param multiplicity The number of assets represented by this id. (default=0)
        @param cachingPolicy The policy for caching the asset. (default=NEVER_CACHE)
    */
    inline AssetID(
        const efd::utf8string& urn,
        efd::UInt8 multiplicity=0,
        CachingPolicy cachingPolicy=NEVER_CACHE);

    /**
        Construct a new AssetID from a const char URN.

        @param urn The URN for the asset.
        @param multiplicity The number of assets represented by this id. (default=0)
        @param cachingPolicy The policy for caching the asset. (default=NEVER_CACHE)
    */
    inline AssetID(
        const char* urn,
        efd::UInt8 multiplicity=0,
        CachingPolicy cachingPolicy=NEVER_CACHE);

    /// Copy constructor
    inline AssetID(const efd::AssetID& other);

    /// Virtual destructor.
    inline virtual ~AssetID();
    //@}

    /// @name Assignment operators
    //@{
    inline AssetID& operator=(const AssetID& other);
    inline AssetID& operator=(const efd::utf8string& urn);
    inline AssetID& operator=(const char* urn);
    //@}

    /// implicit conversion to const const utf8string &
    inline operator const efd::utf8string&() const;

    /// Convert this AssetID to a string.
    inline const char* c_str() const;

    /// @name comparison operators
    //@{
    inline bool operator==(const AssetID& other) const;
    inline bool operator!=(const AssetID& other) const;
    inline bool operator<(const AssetID& other) const;
    //@}

    /// returns true if the AssetID is a valid URN.
    inline virtual bool IsValidURN() const;

    /// Set the asset URN
    inline void SetURN(const efd::utf8string& urn);

    /// Get the asset URN as a utf8string
    inline const efd::utf8string& GetURN() const;

    /**
        Set the multiplicity between this assetID and the underlying asset(s).  An assetID can
        represent a single asset or a class of assets. When fetching an asset by ID it is
        important to know how many responses to expect.

        @param val 1 if there is a 1-1 correspondence between assetID and Asset.
                   n if this AssetID maps to n distinct assets.
                   0 if this assetID maps to any number of assets.
    */
    inline virtual void SetMultiplicity(efd::UInt8 val);

    /**
        Get the multiplicity between this assetID and the underlying asset(s).  An assetID can
        represent a single asset or a class of assets. When fetching an asset by ID it is
        important to know how many responses to expect.

        @return 1 if there is a 1-1 correspondence between assetID and Asset.
                n if this AssetID maps to n distinct assets.
                0 if this assetID maps to any number of assets.
    */
    inline virtual efd::UInt8 GetMultiplicity() const;

    /// Set the caching policy for the asset(s) represented by this ID.
    inline void SetCachingPolicy(CachingPolicy policy);

    /// Get the caching policy for the asset(s) represented by this ID.
    inline CachingPolicy GetCachingPolicy() const;

    /// Serialize method for using AssetID with Archive and ParameterList
    inline void Serialize(efd::Archive& io_archive);

    /// Returns true if this AssetID represents a universal unique ID as opposed to a 
    /// query URN.
    inline bool IsUUID() const;

    /// Convenience static AssetID for an invalid asset.
    static const AssetID INVALID_ASSET_ID;

private:
    efd::utf8string m_urn;
    efd::UInt8 m_multiplicity;
    CachingPolicy m_cachingPolicy;
};

} // end namespace efd

#include <efd/AssetID.inl>

#endif // EE_ASSETID_H
