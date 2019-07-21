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
#ifndef EE_ASSETCACHERESPONSE_H
#define EE_ASSETCACHERESPONSE_H

#include <efd/efdLibType.h>

#include <efd/IMessage.h>
#include <efd/efdMessageIDs.h>

namespace efd
{

/**
    A message class for responses to requests to cache an asset.

    Currently, individual services that cache assets use this message to inform
    a requestor that the cache action has been completed. There is no centralized service
    for caching all asset types.
*/
class EE_EFD_ENTRY AssetCacheResponse : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(AssetCacheResponse, efd::kMSGID_AssetCacheResponse, efd::IMessage);
    /// @endcond

public:
    enum AssetCacheResult
    {
        /// The provided URN was invalid.
        ACR_InvalidURN,

        /// The asset for URN was not found by the AssetLocatorService.
        ACR_AssetNotFound,

        /// No factory was registered for the asset type.
        ACR_FactoryNotFound,

        /// The asset file provided by AssetLocatorService was not found.
        ACR_FileNotFound,

        /// The asset file could not be opened for reading.
        ACR_FileAccessDenied,

        /// The asset file was opened but there was an error parsing the file.
        ACR_ParseError,

        /// The asset load failed for an unspecified reason, check the log.
        ACR_UnknownError,

        /// The asset was loaded, but there were errors.  Check the log.
        ACR_PartialSuccess,

        /// The cache action was successful. Depending on the request, this may mean the asset was
        /// loaded into the cache, it was already cached or it was flushed from the cache.
        ACR_Success
    };

    enum AssetCacheType
    {
        /// This request was to add things to the cache.
        ACT_CacheAdd,

        /// This request was to remove things from the cache.
        ACT_CacheRemove,

        /// This request was to reload things in the cache.
        ACT_CacheReload,

        /// Unknown request type
        ACT_UnknownType
    };

    /// @name Construction and Destruction
    //@{


    /// Default constructor.
    inline AssetCacheResponse();

    /// Constructor requires the URN and the category on which to send the response.
    ///
    /// The category is also used to select the appropriate loader for the asset.
    inline AssetCacheResponse(
        const efd::utf8string& urn,
        const efd::Category& responseCategory,
        AssetCacheResponse::AssetCacheResult result,
        AssetCacheResponse::AssetCacheType type);

    /// Destructor
    inline virtual ~AssetCacheResponse();

    //@}

    ///{ @name Getters

    /**
        Get the response URN provided by the requester.
        @return utf8string URN.
    */
    inline const efd::utf8string& GetURN() const;

    /**
        Get the response Category provided by the requester.
        @return Category response category.
    */
    inline const efd::Category& GetResponseCategory() const;

    /**
        Set the response Category.
        @return Category response category.
    */
    inline void SetResponseCategory(const efd::Category& category);

    /**
        Get the AssetCacheResult for this Response.
        @return AssetCacheResult the result of the load.
    */
    inline AssetCacheResponse::AssetCacheResult GetResult() const;

    /**
        Set the AssetCacheResult for this Response.
        @param result The result of the load.
    */
    inline void SetResult(AssetCacheResponse::AssetCacheResult result);

    /**
        Get the AssetCacheType for this Response
        @return AssetCacheType The type of the cache request that generated this response.
    */
    inline AssetCacheResponse::AssetCacheType GetType() const;

    /**
        Set the AssetCacheType for this Response.
        @param type The type of the cache request that generated this response.
    */
    inline void SetType(AssetCacheResponse::AssetCacheType type);

    //@}

    /// @name IStreamable interface methods.
    //@{

    /// This function asserts and should never be called.
    virtual void Serialize(efd::Archive& ar);

    //@}

protected:
    efd::utf8string m_urn;
    efd::Category m_responseCategory;
    AssetCacheResponse::AssetCacheResult m_result;
    AssetCacheResponse::AssetCacheType m_type;
};

/// A SmartPoint for an AssetCacheResponse
typedef efd::SmartPointer<AssetCacheResponse> AssetCacheResponsePtr;
/// A SmartPoint for a const AssetCacheResponse
typedef efd::SmartPointer<const AssetCacheResponse> AssetCacheResponseConstPtr;

} // namespace efd

#include <efd/AssetCacheResponse.inl>

#endif // EE_ASSETCACHERESPONSE_H
