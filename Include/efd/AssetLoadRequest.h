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
#ifndef EE_ASSETLOADREQUEST_H
#define EE_ASSETLOADREQUEST_H

#include <efd/efdLibType.h>

#include <efd/IMessage.h>
#include <efd/efdMessageIDs.h>

namespace efd
{

/**
    A message class for requests to load an asset.
*/
class EE_EFD_ENTRY AssetLoadRequest : public efd::IMessage
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(AssetLoadRequest, efd::kMSGID_AssetLoadRequest, efd::IMessage);
    /// @endcond

public:

    /// @name Construction and Destruction
    //@{

    /// Default constructor to allow handler definition
    inline AssetLoadRequest();

    /**
        Constructor requires the asset URN and the category on which to send the response.

        The category is also used to select the appropriate loader for the asset.

        If the assetPath value is non-empty when the message is received by the
        efd::AssetFactoryManager service, the file will be loaded directly from the path and
        the URN in the message will be ignored. Otherwise, an asset locator request will be done
        for the URN and the resulting file passed to the factory.

        @param urn The asset to load, or ignored if assetPath is specified.
        @param responseCategory The category to send results to. Each loader has a unique response
            category so this category can also identify which loader should be used.
        @param assetPath An optional file path for loading the asset. If provided, the urn is
            ignored and the asset is loaded from the specified file.
        @param isBackground Is true the load is done in the background thread, unless the factory
            can only operate in the foreground thread.
        @param isPreemptive If true the load is done as soon as possible in the requested thread.
            Request will be placed in a high priority queue that is emptied before items from the
            normal queue are processed.
        @param isReload A hint to the factory indicating this is a reload request. This hint might
            bypass checks for the asset already being cached on the assumption the source data has
            changed.
    */
    AssetLoadRequest(
        const efd::utf8string& urn,
        const efd::Category& responseCategory,
        const efd::utf8string& assetPath = efd::utf8string::NullString(),
        const bool isBackground = true,
        const bool isPreemptive = false,
        bool isReload = false);
    //@}

    ///{ @name Getters

    /**
        Get the request asset URN.
        @return utf8string request asset URN.
    */
    inline const efd::utf8string& GetURN() const;

    /**
        Get the request response category.
        @return Category& request response category.
    */
    inline const efd::Category& GetResponseCategory() const;

    /**
        Get the fully qualified path to the underlying asset on disk.
        @return utf8string AssetPath.
    */
    inline const efd::utf8string& GetAssetPath() const;

    /**
        Get the flag controlling background loading.

        @return bool True if the load should be done in the background.
    */
    inline bool GetIsBackground() const;

    /**
        Get the flag controlling preemptive loading.

        See efd::AssetFactoryManager for the definition of preemptive in this context.

        @return bool True if the load should be done as soon as possible.
    */
    inline bool GetIsPreemptive() const;

    /**
        Get the flag indicating this is a reload request.

        @return bool True if this is a reload, false otherwise.
    */
    inline bool GetIsReload() const;

    /**
        Set the request asset URN.
        @param urn The request asset URN.
    */
    inline void SetURN(const efd::utf8string& urn);

    /**
        Set the request response category.
        @param responseCategory The request response category.
    */
    inline void SetResponseCategory(const efd::Category& responseCategory);

    /**
    Set the fully qualified path to the underlying flat model asset on disk.

    If this value is non-empty when the message is received by the efd::AssetFactoryManager
    service the file will be loaded directly from the path and the URN in the message will
    be ignored.

    @param assetPath The fully qualified path to the asset.
    */
    inline void SetAssetPath(const efd::utf8string& assetPath);

    /**
        Set the flag controlling background loading.

        This flag may not be respected if the factory for the asset can only operate in the
        foreground thread.

        @param isBackground True if the load should be tried in the background.
    */
    inline void SetIsBackground(const bool isBackground);

    /**
        Set the flag controlling preemptive loading.

        See efd::AssetFactoryManager for the definition of preemptive in this context.

        @param isPreemptive True if the load should be done as soon as possible, false for an
            in-requested-order load.
    */
    inline void SetIsPreemptive(const bool isPreemptive);

    /**
        Set the flat identifying this as a reload request.

        @param isReload True if this this a reload request, false otherwise.
    */
    inline void SetIsReload(bool isReload);

    //@}

    /// @name IStreamable interface methods.
    //@{
    virtual void Serialize(efd::Archive& ar);
    //@}

protected:
    efd::utf8string m_urn;
    efd::Category m_responseCategory;
    efd::utf8string m_assetPath;
    bool m_isBackground;
    bool m_isPreemptive;
    bool m_isReload;
};

/// A SmartPointer for the AssetLoadRequest class
typedef efd::SmartPointer<AssetLoadRequest> AssetLoadRequestPtr;
/// A SmartPointer for const AssetLoadRequest pointers
typedef efd::SmartPointer<const AssetLoadRequest> AssetLoadRequestConstPtr;

} // end namespace efd

#include <efd/AssetLoadRequest.inl>

#endif // EE_ASSETLOADREQUEST_H
