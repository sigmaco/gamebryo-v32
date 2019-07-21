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
#ifndef EE_WORLDFACTORYREQUEST_H
#define EE_WORLDFACTORYREQUEST_H

#include <efd/AssetLoadRequest.h>
#include <egf/egfMessageIDs.h>
#include <egf/egfLibType.h>

namespace egf
{
/**
    The WorldFactoryRequest is used to request an asynchronous World (xblock file) load. These
    requests are passed to the AssetFactoryManager for processing. The resulting
    world information is returned to the caller in a WorldFactoryResponse object.

    The requester only needs to provide the urn to the xblock file. The AssetFactoryManager
    is responsible for providing the fully qualified path to the asset.
 */
class EE_EGF_ENTRY WorldFactoryRequest : public efd::AssetLoadRequest
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(WorldFactoryRequest, efd::kMSGID_WorldFactoryRequest, efd::AssetLoadRequest);
    /// @endcond

public:

    /// @name Construction and Destruction
    //@{

    /// Default constructor
    WorldFactoryRequest();

    /**
        Construct a new WorldFactoryRequest.

        @param urn Request URN.
        @param responseCategory category used to send responses.
        @param assetPath fully qualified path to the underlying .xblock asset.
        @param isBackground if true, load is attempted in the background thread.
        @param isPreemptive if true, load is done as soon as possible.
        @param isReload hint to the factory indicating this is a reload.
    */
    WorldFactoryRequest(
        const efd::utf8string& urn,
        const efd::Category& responseCategory,
        const efd::utf8string& assetPath = "",
        bool isBackground = true,
        bool isPreemptive = false,
        bool isReload = false);

    //@}
};

/// A SmartPointer for the WorldFactoryRequest class
typedef efd::SmartPointer<WorldFactoryRequest> WorldFactoryRequestPtr;

} // end namespace egf

#endif // EE_WORLDFACTORYREQUEST_H
