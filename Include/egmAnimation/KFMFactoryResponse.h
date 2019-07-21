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
#ifndef EE_KFMFACTORYRESPONSE_H
#define EE_KFMFACTORYRESPONSE_H

#include "egmAnimationLibType.h"
#include <efd/AssetLoadResponse.h>
#include <NiActorManager.h>
#include <ecr/ecrMessageIDs.h>

namespace egmAnimation
{

/**
    The KFMFactoryResponse is used to return an NiActorManager from a
    KFMFactoryRequest sent to a KFMFactory.

    If GetStatus() == ALR_Success, then GetActor() will return the
    successfully completed actor.

    If GetStatus() == ALR_PartialSuccess, then GetActor() will return
    the actor, but some of the animation sequences may not have loaded.
    The actor will display on screen, but may not animate properly.

    If GetStatus() is some error, then GetActor() will return false.
*/
class EE_EGMANIMATION_ENTRY KFMFactoryResponse : public efd::AssetLoadResponse
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(
        KFMFactoryResponse,
        efd::kMSGID_KFMFactoryResponse,
        efd::AssetLoadResponse);
    /// @endcond

public:
    /// Default constructor.
    KFMFactoryResponse();

    /// Constructor.
    KFMFactoryResponse(
        const efd::utf8string& urn,
        const efd::Category& responseCategory,
        AssetLoadResponse::AssetLoadResult result,
        const efd::utf8string& assetPath,
        bool isReload);

    /// @name Accessors for the NiActorManager
    //@{
    NiActorManager* GetActor() const;
    void SetActor(NiActorManager* pActor);
    //@}

protected:

    NiActorManagerPtr m_spActor;
};

/// A SmartPointer for the KFMFactoryResponse class
typedef efd::SmartPointer<KFMFactoryResponse> KFMFactoryResponsePtr;

} // end namespace egmAnimation

#endif // EE_KFMFACTORYRESPONSE_H
