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
#ifndef EE_KFMFACTORYREQUEST_H
#define EE_KFMFACTORYREQUEST_H

#include <efd/AssetLoadRequest.h>
#include <ecr/ecrMessageIDs.h>
#include <egmAnimation/egmAnimationLibType.h>

namespace egmAnimation
{

/**
    The KFMFactoryRequest is used to request an asynchronous flat model file load. The
    resulting NiActorManager instance is returned to the caller in an KFMFactoryResponse.

    This is the only type of request that the KFMFactory will respond to.

    The accumulation parameter can be used to specify whether or not the actor
    created is set up to use accumulation.
*/
class EE_EGMANIMATION_ENTRY KFMFactoryRequest : public efd::AssetLoadRequest
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(
        KFMFactoryRequest,
        efd::kMSGID_KFMFactoryRequest,
        efd::AssetLoadRequest);
    /// @endcond

public:
    /// @name Constructors and Destructors
    //@{

    /// Default constructor
    KFMFactoryRequest();

    /**
        Construct a new KFMFactoryRequest.

        @param urn URN for the model required by the Entity.
        @param responseCategory Category to send the response.
        @param assetPath the fully qualified path to the underlying asset.
        @param isBackground if true, load is attempted in the background thread.
        @param isPreemptive if true, load is done as soon as possible.
        @param cumulativeAnimations if true, the asset will use animation accumulation.
    */
    KFMFactoryRequest(
        const efd::utf8string& urn,
        const efd::Category& responseCategory,
        const efd::utf8string& assetPath = "",
        const bool isBackground = true,
        const bool isPreemptive = false,
        const bool cumulativeAnimations = false);
    //@}

    /// Sets whether or not the asset loaded by this request will use animation accumulation.
    void SetAccumulation(bool cumulativeAnimations);
    /// Gets whether or not the asset loaded by this request will use animation accumulation.
    bool GetAccumulation() const;

protected:
    bool m_cumulative;
};

typedef efd::SmartPointer<KFMFactoryRequest> KFMFactoryRequestPtr;
typedef efd::SmartPointer<const KFMFactoryRequest> KFMFactoryRequestConstPtr;

} // end namespace egmAnimation

#endif // EE_KFMFACTORYREQUEST_H
