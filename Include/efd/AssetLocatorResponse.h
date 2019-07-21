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
#ifndef EE_ASSETLOCATORRESPONSEMESSAGE_H
#define EE_ASSETLOCATORRESPONSEMESSAGE_H

#include <efd/IMessage.h>
#include <efd/AssetUriReader.h>
#include <efd/efdMessageIDs.h>

namespace efd
{

/**
    Message class used for AssetLocatorService response messages.
*/
class EE_EFD_ENTRY AssetLocatorResponse : public IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(AssetLocatorResponse, efd::kCLASSID_AssetLocatorResponse, IMessage);
    /// @endcond

public:

    /**
        Response details are contained in a map of <AssetID, AssetLoc>.

        The AssetID is the "urn:uuid:xxxx" format as used in the Asset Locator server, where
        'xxxx' is the Asset logical ID. The request itself can take either the urn::tag
        format or the urn::uuid format. Most requests are made using the former.

        See the How the Asset Locating Services Work page for further details.
    */
    struct AssetLoc
    {
        /// The name of the asset. This is the file name of the asset without path or extension.
        efd::utf8string name;

        /// Tags associated with the asset as defined in the asset web metadata.
        efd::utf8string tagset;

        /// Reserved for future use.
        efd::utf8string classes;

        /// The fully qualified path to the asset on disk.
        efd::utf8string url;

        /// The logical asset ID for the asset.
        efd::utf8string llid;

        /// Serialization
        void Serialize(efd::Archive& ar);
    };
    typedef efd::map<efd::utf8string, AssetLoc> AssetURLMap;

    /// Constructor
    AssetLocatorResponse();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void Serialize(efd::Archive& ar);

    /**
        Set the URI used in the request that this message is in response to.
    */
    virtual void SetResponseURI(const efd::utf8string& uri) { m_uri = uri; }

    /**
        Get the URI used in the request that this message is responding.

        @return const utf8string The asset URI
    */
    virtual const efd::utf8string& GetResponseURI() const { return m_uri; }

   /**
        Set the category (of the requesting client) that the response will be delivered to
   */
   virtual void ClientCategory(const efd::Category& callback) { m_client_category = callback; }

    /**
        Get the client callback category to deliver to.

        @return const Category The category
    */
    virtual const efd::Category& ClientCategory() const {return m_client_category; }

    /**
        Set all the key response attributes for the specified Asset ID

        @param assetId The asset Id in the form of "urn:uuid:(GUID value)"
        @param assetName The name property of the asset
        @param tagSet The list of all label tags the asset possesses
        @param clasSet The list of all classification tags the asset possesses
        @param assetUrl The physical URL location of the asset
        @param llid The logical asset Id in the form of "urn:llid:(GUID value)"
    */
    virtual void SetAssetLoc(
        const efd::utf8string& assetId,
        const efd::utf8string& assetName,
        const efd::utf8string& tagSet,
        const efd::utf8string& clasSet,
        const efd::utf8string& assetUrl,
        const efd::utf8string& llid)
    {
        AssetLoc loc = {assetName, tagSet, clasSet, assetUrl, llid};
        m_AssetLocations[assetId] = loc;
    }

    /**
        Set all the key response attributes for the specified Asset ID

        @param assetId The asset Id in the form of "urn:uuid:(GUID value)"
        @param loc The key attributes as an instance of an AssetLoc struct
    */
    virtual void SetAssetLoc(const efd::utf8string& assetId, const AssetLoc& loc)
    {
        m_AssetLocations[assetId] = loc;
    }

    /**
        Get the map of Asset ID / Asset Physical URL matches for the
        requested URI.

        @return AssetURLMap containing the key attributes for each asset Id in the response.
    */
    virtual const efd::AssetLocatorResponse::AssetURLMap& GetAssetURLMap() const
    {
        return m_AssetLocations;
    }

protected:
    /// Asset URI
    efd::utf8string m_uri;
    /// Category for delivery
    efd::Category m_client_category;
    /// Map of asset locations and key attributes
    efd::AssetLocatorResponse::AssetURLMap m_AssetLocations;
};

/// A SmartPointer for the AssetLocatorResponse class
typedef efd::SmartPointer<AssetLocatorResponse> AssetLocatorResponsePtr;
/// A SmartPointer for a const AssetLocatorResponse class
typedef efd::SmartPointer<const AssetLocatorResponse> AssetLocatorResponseConstPtr;

/**
    Response containing the size, in bytes, of an asset.
*/
class EE_EFD_ENTRY AssetSizeResponse : public AssetLocatorResponse
{
public:
    AssetSizeResponse() : m_size(0) { }

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void Serialize(efd::Archive& ar);

    efd::UInt32 GetSize() { return m_size; }

    void SetSize(efd::UInt32 size) { m_size = size; }


private:
    efd::UInt32 m_size;
};

/// A SmartPointer for the AssetSizeResponse class
typedef efd::SmartPointer<AssetSizeResponse> AssetSizeResponsePtr;


/**
    Some responses will include additional BrowseInfo. This is a list of tags and counts that are
    related to the query in that they can be used as modifiers. Useful for creating an asset
    browser GUI.
*/
struct BrowseInfoDescriptor
{
    /// The type of tag.
    efd::AWebTagType ttype;

    /// The name of the tag.
    efd::utf8string tvalue;

    /// The number of assets with this tag.
    efd::UInt32 count;

    /// Serialization
    void Serialize(efd::Archive& ar);
};
typedef efd::vector<BrowseInfoDescriptor> AssetBrowseInfo;


/**
    Response to a TagsInfo request.
*/
class EE_EFD_ENTRY AssetTagsInfoResponse : public IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(AssetTagsInfoResponse, kMSGID_AssetTagsInfoResponse, IMessage);
    /// @endcond
public:

    /// Constructor
    AssetTagsInfoResponse() {}

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void Serialize(efd::Archive& ar);

    /**
        Set asset tag information

        @param tag_type The uri reference for the type of the tag
        @param tag_value The literal value for the tag
    */
    virtual void SetTagInfo(const efd::AWebTagType& tag_type, const efd::utf8string& tag_value)
    {
        BrowseInfoDescriptor bi;
        bi.ttype = tag_type;
        bi.tvalue = tag_value;
        bi.count = 0;
        m_TagInfo.push_back(bi);
    }

    /**
        Get the asset tag info.

        @return AssetBrowseInfo containing the asset tag info for the response.
    */
    virtual const efd::AssetBrowseInfo& GetAssetBrowseInfo() const
    {
        return m_TagInfo;
    }

protected:
    /// Vector of tag information
    efd::AssetBrowseInfo m_TagInfo;
};

/// A SmartPointer for the AssetTagsInfoResponse class
typedef efd::SmartPointer<AssetTagsInfoResponse> AssetTagsInfoResponsePtr;


/**
 Response to a BrowseInfo request. Contains all the AssetLocatorResponse data, plus
 an additional set of tag values that are used for browsing assets.
*/
class EE_EFD_ENTRY AssetBrowseInfoResponse : public AssetLocatorResponse
{
public:

    /// Constructor
    AssetBrowseInfoResponse() {}

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void Serialize(efd::Archive& ar);

    /**
        Set asset tag browse information

        @param tag_type The uri reference for the type of the tag
        @param tag_value The literal value for the tag
        @param count The count of assets in the result set with this tag
    */
    virtual void SetTagInfo(
        const efd::AWebTagType& tag_type,
        const efd::utf8string& tag_value,
        efd::UInt32 count);

    /**
        Get the asset browse info for the requested URI.

        @return AssetBrowseInfo containing the asset browse info for the response.
    */
    virtual const efd::AssetBrowseInfo& GetAssetBrowseInfo() const
    {
        return m_TagBrowseInfo;
    }

    /**
        Set the root of the asset-web for the response.
    */
    virtual void SetAssetWebRoot(const efd::utf8string& root) { m_root = root; }

    /// Retrieves the asset-web root
    virtual const efd::utf8string& GetAssetWebRoot() const { return m_root; }

protected:
    /// Asset root
    efd::utf8string m_root;

    /// Vector of tag browse information
    efd::AssetBrowseInfo m_TagBrowseInfo;
};

typedef efd::SmartPointer<AssetBrowseInfoResponse> AssetBrowseInfoResponsePtr;

/**
    Response to an Asset Fetch request. Contains the number of bytes retrieved and a buffer to hold
    the data.
*/
class EE_EFD_ENTRY FetchAssetDataResponse : public AssetLocatorResponse
{
public:
    enum FetchResult
    {
        kFETCH_SUCCESS,
        kFETCH_ASSET_NOT_FOUND,
        kFETCH_ASSET_PERMISSION_DENIED,
        kFETCH_ASSET_EOF
    };

    /// Constructor
    FetchAssetDataResponse();
    /// Destructor
    ~FetchAssetDataResponse();

    /**
        Allocate a buffer of the given size. The returned buffer is owned by the
        FetchAssetDataResponse message and should not be freed. Use it only to populate the payload
        for this message.
    */
    char* AllocateBuffer(efd::UInt32 size);

    inline efd::UInt32 GetBufferSize() const
    {
        return m_size;
    }

    inline void SetBytesRead(efd::UInt32 bytesRead)
    {
        m_size = bytesRead;
    }

    inline void SetResult(FetchResult result)
    {
        m_result = result;
    }

    inline FetchResult GetResult() const
    {
        return m_result;
    }

    inline const char *GetAssetData() const
    {
        return m_buffer;
    }

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void Serialize(efd::Archive& ar);

private:
    /// number of bytes in the buffer
    efd::UInt32 m_size;

    /// result of the fetch
    FetchResult m_result;

    /// raw data buffer
    char* m_buffer;
};

typedef efd::SmartPointer<FetchAssetDataResponse> FetchAssetDataResponsePtr;

} // end namespace efd

EE_SPECIALIZE_ENUM(efd::FetchAssetDataResponse::FetchResult, efd::UInt8);

#endif // EE_ASSETLOCATORRESPONSEMESSAGE_H

