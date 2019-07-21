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
#ifndef EE_ASSETLOADRESPONSE_H
#define EE_ASSETLOADRESPONSE_H

#include <efd/efdLibType.h>

#include <efd/IMessage.h>
#include <efd/efdMessageIDs.h>

namespace efd
{

/**
    A message class for responses to asset load requests.

    Applications are expected to sub-class this type in order to provide storage
    for their specific asset type. The message must free any resources it holds
    upon deletion when it is the only holder of such information. In practice, this
    strongly suggests the use of smart pointers to hold pointers to any resources.

    The handler for any AssetLoadResponse-derived message should handle the base class
    (egf::AssetLoadResponse) because the AssetFactoryService will send this message
    type in error conditions.
*/
class EE_EFD_ENTRY AssetLoadResponse : public IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(AssetLoadResponse, kMSGID_AssetLoadResponse, IMessage);
    /// @endcond

public:
    enum AssetLoadResult
    {
        /// The provided URN was invalid.
        ALR_InvalidURN,

        /// The asset for URN was not found by the AssetLocatorService.
        ALR_AssetNotFound,

        /// No factory was registered for the response category.
        ALR_FactoryNotFound,

        /// The asset file provided by AssetLocatorService was not found.
        ALR_FileNotFound,

        /// The asset file could not be opened for reading.
        ALR_FileAccessDenied,

        /// The load request is not supported by the registered factory.
        ALR_RequestNotSupported,

        /// The asset file was opened but there was an error parsing the file.
        ALR_ParseError,

        /// The asset load failed for an unspecified reason, check the log.
        ALR_UnknownError,

        /// The asset was loaded, but there were errors.  Check the log.
        ALR_PartialSuccess,

        /// The asset was successfully loaded.
        ALR_Success
    };

    /// @name Construction and Destruction
    //@{


    /// Default constructor.
    inline AssetLoadResponse();

    /// Constructor requires the URN and the category on which to send the response.
    ///
    /// The category is also used to select the appropriate loader for the asset.
    inline AssetLoadResponse(
        const utf8string& urn,
        const Category& responseCategory,
        AssetLoadResponse::AssetLoadResult result,
        const utf8string& assetPath = "",
        bool isReload = false);

    /// Destructor
    inline virtual ~AssetLoadResponse();

    //@}

    ///{ @name Getters

    /**
        Get the response URN provided by the requester.
        @return utf8string URN.
    */
    inline const utf8string& GetURN() const;

    /**
        Get the response Category provided by the requester.
        @return Category response category.
    */
    inline const Category& GetResponseCategory() const;

    /**
        Set the response Category.
        @return Category response category.
    */
    inline void SetResponseCategory(const Category& category);

    /**
        Get the AssetLoadResult for this Response.
        @return AssetLoadResult the result of the load.
    */
    inline AssetLoadResponse::AssetLoadResult GetResult() const;

    /**
        Set the AssetLoadResult for this Response.
        @param result The result of the load.
    */
    inline void SetResult(AssetLoadResponse::AssetLoadResult result);

    /**
        Get the asset path.
        @return utf8string asset path, or empty string if not set.
    */
    inline const utf8string& GetAssetPath() const;

    /**
        Return true if the request was a reload request.
        @return true if this is a reload, false otherwise.
    */
    inline bool GetIsReload() const;

    /**
        Set the flag identifying this as a response to a reload request.

        @param isReload True if this this a reload request, false otherwise.
    */
    inline void SetIsReload(bool isReload);

    //@}

    /// @name IStreamable interface methods.
    //@{

    /// This function asserts and should never be called.
    virtual void Serialize(efd::Archive& ar);

    //@}

protected:
    utf8string m_urn;
    Category m_responseCategory;
    AssetLoadResponse::AssetLoadResult m_result;
    utf8string m_assetPath;
    bool m_isReload;
};

/// A SmartPointer for the AssetLoadResponse class
typedef SmartPointer<AssetLoadResponse> AssetLoadResponsePtr;
/// A SmartPointer for const AssetLoadResponse class instances
typedef SmartPointer<const AssetLoadResponse> AssetLoadResponseConstPtr;

} // namespace efd

#include <efd/AssetLoadResponse.inl>

#endif // EE_ASSETLOADRESPONSE_H
