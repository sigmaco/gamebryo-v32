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
#ifndef EE_ASSETCHANGEHANDLER_H
#define EE_ASSETCHANGEHANDLER_H

#include <efd/utf8string.h>


namespace efd
{

/**
    Interface class for an asset change handler.

    The asset change handler is called by the ReloadManager when an asset change is
    detected and that asset is tagged appropriately. Classes that want these notifications
    should extend this interface and implement the HandleAssetChange callback method.
*/
class EE_EFD_ENTRY AssetChangeHandler
{
protected:
    virtual ~AssetChangeHandler() {}

public:
    /**
        Pure virtual interface method to implement an Asset Change Handler instance.

        @param assetId The ID of the asset that changed.
        @param tag the matching tag, the same as that used to register the handler.
    */
    virtual void HandleAssetChange(
        const efd::utf8string& assetId,
        const efd::utf8string& tag) = 0;
};

} // end namespace efd

#endif // EE_ASSETCHANGEHANDLER_H
