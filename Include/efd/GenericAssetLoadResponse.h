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
#ifndef EE_GENERICASSETLOADRESPONSE_H
#define EE_GENERICASSETLOADRESPONSE_H

#include <efd/AssetLoadResponse.h>
#include <efd/SmartPointer.h>
#include <efd/efdLibType.h>
#include <efd/efdMessageIDs.h>

namespace efd
{
// forward declarations
class utf8string;
class Category;

/**
    A response message to a generic Asset load request.

    The response contains the original request URN, a result, the size of the asset,
    and buffer containing the asset data.
 */
class EE_EFD_ENTRY GenericAssetLoadResponse : public efd::AssetLoadResponse
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(
        GenericAssetLoadResponse,
        efd::kMSGID_GenericAssetLoadResponse,
        efd::AssetLoadResponse);
    /// @endcond

public:

    /// @name Construction and Destruction
    //@{

    /// Default constructor for message handler registration.
    GenericAssetLoadResponse();

    /**
        Construct a new GenericAssetLoadResponse. Each response contains the original request
        URN, a result code, the size of the asset, and the asset data.

        @param urn original request URN.
        @param responseCategory original request response category.
        @param result result of the load request.
        @param assetPath Fully qualified path to the asset.
        @param isReload hint to the factory indicating this is a reload.
        @param assetSizeInBytes the size of the asset, in bytes. 0 if the asset failed to load.
        @param assetData buffer, of size assetSizeInBytes, contain the Asset data from disk.
            0 if the asset failed to load. The GenericAssetLoadResponse takes ownership of
            this data.
    */
    GenericAssetLoadResponse(
        const efd::utf8string& urn,
        const efd::Category& responseCategory,
        efd::AssetLoadResponse::AssetLoadResult result,
        const efd::utf8string& assetPath = "",
        bool isReload = false,
        efd::UInt32 assetSizeInBytes = 0,
        char* assetData = 0);

    /**
        Cleanup any resources.
    */
    virtual ~GenericAssetLoadResponse();

    //@}

    /// @name Getters and Setters
    //@{

    /**
        Get the size of the asset read into memory, in bytes.
        @return UInt32 size read into memory, in bytes, or 0 if the asset was empty or
            failed to load.
    */
    efd::UInt32 GetAssetSize() const;

    /**
        Set the size of the asset data.
        @param size asset size.
    */
    void SetAssetSize(efd::UInt32 size);

    /**
        Get the asset raw data buffer.

        This data is owned by the message and will be released when the message is deleted.
        Make a copy if you need the data to live beyond the message.

        @return char* asset raw data. This will be NULL if the asset size is 0 or
            there was an error.
    */
    const char* GetAssetData() const;

    /**
        Set the asset raw data buffer.

        @param data Pointer to asset raw data.
    */
    void SetAssetData(char* data);

    //@}

protected:
    efd::UInt32 m_assetSize;  // in bytes
    char* m_assetData;
};

/// A SmartPointer for the GenericAssetLoadResponse class
typedef efd::SmartPointer<GenericAssetLoadResponse> GenericAssetLoadResponsePtr;

} // end namespace efd

#endif // EE_GENERICASSETLOADRESPONSE_H
