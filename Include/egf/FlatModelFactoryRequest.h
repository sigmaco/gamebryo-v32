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
#ifndef EE_FLATMODELFACTORYREQUEST_H
#define EE_FLATMODELFACTORYREQUEST_H

#include <efd/AssetLoadRequest.h>
#include <egf/egfMessageIDs.h>
#include <egf/egfLibType.h>
#include <egf/EntityID.h>

namespace egf
{
/**
    The FlatModelFactoryRequest is used to request an asynchronous flat model file load. The
    resulting FlatModel instance is returned to the caller in an FlatModelFactoryResponse.

    The requester only needs to provide the urn. The AssetFactoryManager is responsible for
    providing the fully qualified path to the asset and setting this path on the request. If
    using the FlatModelFactory separate from the AssetFactoryManager, the caller is
    responsible for providing this path.
*/
class EE_EGF_ENTRY FlatModelFactoryRequest : public efd::AssetLoadRequest
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(
        FlatModelFactoryRequest,
        efd::kMSGID_FlatModelFactoryRequest,
        efd::AssetLoadRequest);
    /// @endcond

public:
    /// @name Constructors and Destructors
    //@{

    /// Default constructor
    FlatModelFactoryRequest();

    /**
        Construct a new FlatModelFactoryRequest.

        @param urn URN for the model required by the Entity.
        @param responseCategory Category to send the response.
        @param assetPath the fully qualified path to the underlying asset.
        @param isBackground if true, load is attempted in the background thread.
        @param isPreemptive if true, load is done as soon as possible.
        @param isReload hint to the factory indicating this is a reload.
    */
    FlatModelFactoryRequest(
        const efd::utf8string& urn,
        const efd::Category& responseCategory,
        const efd::utf8string& assetPath = "",
        bool isBackground = true,
        bool isPreemptive = false,
        bool isReload = false);

    //@}
};

/// A SmartPointer for the FlatModelFactoryRequest class
typedef efd::SmartPointer<FlatModelFactoryRequest> FlatModelFactoryRequestPtr;

} // end namespace egf

#endif // EE_FLATMODELFACTORYREQUEST_H
