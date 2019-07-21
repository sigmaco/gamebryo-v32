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
#ifndef EE_KFMFACTORY_H
#define EE_KFMFACTORY_H

#include "egmAnimationLibType.h"
#include <efd/BaseAssetFactory.h>
#include <efd/AssetFactoryManager.h>
#include <efd/GenericAssetFactory.h>
#include <ecr/ecrClassIDs.h>
#include <egmAnimation/KFMFactoryRequest.h>

#include "NiKFMTool.h"

// forward declarations
namespace efd
{
    class AssetLoadResponse;
}

namespace egmAnimation
{
class KFMFactoryResponse;

/**
    An IAssetFactory that takes a KFMFactoryRequest and attempts to load the flat model from disk
    and create an NiActorManager instance. The result of this request is returned using an
    KFMFactoryResponse.  This actor manager contains the loaded KFM and KF files, but the NIF root
    will not be set.  It is the caller's responsibility to load this asset separately.  (This will
    likely be done via the SceneGraphService.)

    Callers to KFMFactory::LoadAsset are responsible for looking up and setting the asset path to
    the underlying flat model file in the KFMFactoryRequest.

    The KFMFactory is not typically called directly. Instead, it responds to a request from the
    AssetFactoryManager to load a particular asset. The AssetFactoryManager is responsible for
    locating the fully qualified path using the provided URN and setting this value in the
    KFMFactoryRequest object.  These requests are usually made by the AnimationService directly.

    The caller is responsible for allocating and deallocating the KFMFactoryRequest.

    The KFMFactory allocates the response, it is the callers responsibility to deallocate it.
*/
class EE_EGMANIMATION_ENTRY KFMFactory : public efd::BaseAssetFactory
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(KFMFactory, efd::kCLASSID_KFMFactory, efd::BaseAssetFactory);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

public:
    /// @name Constructors and Destructors
    //@{

    /**
        Construct a new KFMFactory.

        @param pFactoryManager The efd::AssetFactoryManager responsible for this factory.
        @param pMessageService Message service used to subscribe for foreground locate requests.
    */
    KFMFactory(efd::AssetFactoryManager* pFactoryManager, efd::MessageService* pMessageService);

    /// Clean up any open resources.
    virtual ~KFMFactory();

    //@}

    /**
        Attempt to load an actor.
        @see efd::IAssetFactory::LoadStatus for further details.

        @param pFactoryManager The AssetFactoryManager instance invoking this function.
        @param pRequest The KFMFactoryRequest.  Other types will be ignored.
        @param ppResponse KFMFactoryResponse The response message allocated by this factory.
        @return The status of this load request.
    */
    virtual IAssetFactory::LoadStatus LoadAsset(
        efd::AssetFactoryManager* pFactoryManager,
        const efd::AssetLoadRequest* pRequest,
        efd::AssetLoadResponsePtr& ppResponse);

    /// Thread status description.
    ///
    /// This loader is thread safe for foreground or background use.
    virtual IAssetFactory::ThreadSafetyDescription GetThreadSafety() const;

    /// Shutdown function cleans up message subscriptions and smart pointers
    virtual void Shutdown();

protected:

    /// Internal helper class for load requests to the NIFAssetLoader.
    class KFRequest : public efd::AssetLoadRequest
    {
    public:
        KFRequest(const NiFixedString& filename);

        NiFixedString m_filename;
        efd::vector<efd::UInt32> m_sequenceIDs;
    };
    typedef efd::SmartPointer<KFRequest> KFRequestPtr;

    /// Internal helper class to hold response data while waiting to locate assets.
    class ResponseData : public efd::IAssetResponseData
    {
        /// @cond EMERGENT_INTERNAL
        EE_DECLARE_CLASS1(
            KFMFactory::ResponseData,
            efd::kCLASSID_KFMFactoryData,
            efd::IBase);
        EE_DECLARE_CONCRETE_ATOMIC_REFCOUNT;
        /// @endcond

    public:
        ResponseData();
        virtual ~ResponseData();

        /// Create an actor manager, and generate nif and kf requests.
        void LoadKFMTool(NiKFMTool* pKFMTool, const KFMFactoryRequest* pRequest);

        /// Response we'll eventually return to the caller
        efd::SmartPointer<KFMFactoryResponse> m_spResponse;

        /// Sequence requests.
        efd::vector<KFRequestPtr> m_sequences;
    };
    typedef efd::SmartPointer<ResponseData> ResponseDataPtr;

    efd::IAssetFactory::LoadStatus LoadKFMAsset(
        const KFMFactoryRequest* pRequest,
        ResponseData* pResponseData);

    // Don't let the compiler generate these. We don't provide a deep-copy function
    // so any compiler-generated versions of these functions would be incorrect.
    KFMFactory& operator=(const KFMFactory&);
    KFMFactory(const KFMFactory&);

    /// We need to hold the message service so we can subscribe/unsubscribe
    efd::MessageServicePtr m_spMessageService;

    /// Hold onto the factory manager to subscribe and unsubscribe
    efd::AssetFactoryManagerPtr m_spAssetFactoryManager;

    /// Generic asset factory to load KFMs.
    efd::GenericAssetFactoryPtr m_spGenericAssetFactory;
};

/// A SmartPointer for the egmAnimation::KFMFactory class
typedef efd::SmartPointer<egmAnimation::KFMFactory> KFMFactoryPtr;

} // end namespace egmAnimation

#endif // EE_KFMFACTORY_H
