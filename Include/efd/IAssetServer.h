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
#ifndef IASSETSERVERSERVICE_H
#define IASSETSERVERSERVICE_H

#include <efd/ISystemService.h>
#include <efdNetwork/NetCategory.h>
#include <efd/AssetLocatorResponse.h>

namespace efd
{

extern EE_EFD_ENTRY const Category& GetAssetServerServiceCategory();
extern EE_EFD_ENTRY const Category& GetAssetServerProxyCategory();

class EE_EFD_ENTRY IAssetServer : public ISystemService
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_INTERFACE1(IAssetServer, efd::kCLASSID_IAssetServer, ISystemService);
    /// @endcond

public:

    /**
        Sends an asset message to a specific category.

        This simply forwards the message to the MessageService while ensuring that the message
        being sent is of the correct message type.

        @param pMessage Pointer to the Asset Response message to send.
        @param category The Category to send the response message to.
    */
    virtual void SendResponse(
        AssetLocatorResponse* pMessage,
        const Category& category) = 0;

    /// Enumeration of possible asset change types used in the ChangeNotify method.
    enum AssetChangeType
    {
        /// A new asset was added
        kASSET_ADDED,
        /// An existing asset was modified
        kASSET_UPDATED,
        /// An existing asset was deleted
        kASSET_DELETED,
    };

    /**
        Notify the Asset Server that a particular asset file has been changed. No message is sent
        to clients until SendChangeNotifications() is called.

        @param assetRelativePath Relative path of the changed file in the Asset Web.
        @param changeType The type of change that has occurred
    */
    virtual void ChangeNotify(
        const efd::utf8string& assetRelativePath,
        AssetChangeType changeType) = 0;

    /**
        Check that an asset file is accounted for in the metadata. This is used during
        initialization to ensure that the assets in the file system are also listed in the metadata.
        @param assetRelativePath Relative path to the file in the asset-web.
        
        @return true if it succeeds, false if it fails.
        */
        virtual bool CheckAsset(const efd::utf8string& assetRelativePath) = 0;

        /**
        Check that an asset directory actually contains all of the asset files that it is
        supposed to contain. Update metadata for any asset files that are missing, probably
        because they were intentionally deleted.
        
        @param assetDirectroy Relative path to the directory in the asset-web.
    */
    virtual void CheckAssetDir(const efd::utf8string& assetDirectroy) = 0;

    /**
        Sends broadcast message to all client listeners notifying them that one or more assets have
        been updated in the Asset Web. The sent message will include the Asset ID and all its tags
        for each change. From this information, the listeners determine whether to initiate a
        reload of the assets.
    */
    virtual void SendChangeNotifications() = 0;

    /**
        Open the specified asset web location.

        @param web_root The path of the asset-web to use for asset lookups. This can be a relative
            path or a platform-specific absolute path.
    */
    virtual efd::Bool AssetWebOpen (const efd::utf8string& web_root) = 0;
};

/// A SmartPointer for the IAssetServer class
typedef efd::SmartPointer<IAssetServer> IAssetServerPtr;

} // end namespace efd

#endif //IASSETSERVERSERVICE_H

