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
#ifndef EE_KFMCACHERESPONSE_H
#define EE_KFMCACHERESPONSE_H

#include <egmAnimation/egmAnimationLibType.h>

#include <efd/AssetCacheResponse.h>

#include <ecr/ecrMessageIDs.h>
#include <egmAnimation/KFMCache.h>

namespace egmAnimation
{

/**
    A message class for responses to requests to cache a KFM asset.

    Messages of this type are sent by the egmAnimation::KFMCache class when a request has been
    met.
*/
class EE_EGMANIMATION_ENTRY KFMCacheResponse : public efd::AssetCacheResponse
{
    /// @cond EMERGENT_INTERNAL

    EE_DECLARE_CLASS1(
        KFMCacheResponse,
        efd::kMSGID_KFMCacheResponse,
        efd::AssetCacheResponse);

    /// @endcond

public:
    /// @name Construction and Destruction
    //@{

    /// Default constructor.
    inline KFMCacheResponse();

    /// Constructor requires the original request identifier, the category on which to send
    /// the response, a handle, and the additional request data.
    inline KFMCacheResponse(
        const efd::utf8string& identifier,
        const efd::Category& responseCategory,
        KFMCache::IKFMCacheRequestData* pRequestData,
        const efd::AssetCacheResponse::AssetCacheResult result,
        const efd::AssetCacheResponse::AssetCacheType type);

    /// Destructor
    inline virtual ~KFMCacheResponse();

    //@}

    /// @name Getters

    /**
        Get the identifier.
    */
    inline const efd::utf8string& GetIdentifier() const;

    /**
        Get the request data.
    */
    inline KFMCache::IKFMCacheRequestData* GetRequestData() const;

    /**
        Get the number of handles.
    */
    inline efd::UInt32 GetHandleCount() const;

    /**
        Get a handle.

        Index must be less than the value returned by GetHandleCount and it is not range-checked.

    */
    inline KFMCache::KFMCacheHandle GetHandle(const efd::UInt32 index) const;

    //@}

    /// @cond EMERGENT_INTERNAL

    /// Add a handle
    inline void AddHandle(const KFMCache::KFMCacheHandle handle);

    /// @endcond

protected:
    KFMCache::IKFMCacheRequestData* m_pRequestData;
    efd::vector<KFMCache::KFMCacheHandle> m_handles;
};

/// A SmartPointer for the KFMCacheResponse class
typedef efd::SmartPointer<KFMCacheResponse> KFMCacheResponsePtr;
/// A SmartPointer for the const SceneGraphCacheResponse class
typedef efd::SmartPointer<const KFMCacheResponse> KFMCacheResponseConstPtr;

} // end namespace egmAnimation

#include <egmAnimation/KFMCacheResponse.inl>

#endif // EE_KFMCACHERESPONSE_H
