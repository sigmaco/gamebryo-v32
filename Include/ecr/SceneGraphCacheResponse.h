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
#ifndef EE_SCENEGRAPHCACHERESPONSE_H
#define EE_SCENEGRAPHCACHERESPONSE_H

#include <ecr/ecrLibType.h>

#include <efd/AssetCacheResponse.h>

#include <ecr/ecrMessageIDs.h>
#include <ecr/SceneGraphCache.h>

namespace ecr
{

/**
    A message class for responses to requests to cache a scene graph asset.

    Messages of this type are sent by the ecr::SceneGraphCache class when a request has been
    met.
*/
class EE_ECR_ENTRY SceneGraphCacheResponse : public efd::AssetCacheResponse
{
    /// @cond EMERGENT_INTERNAL

    EE_DECLARE_CLASS1(
        SceneGraphCacheResponse,
        efd::kMSGID_SceneGraphCacheResponse,
        efd::AssetCacheResponse);

    /// @endcond

public:
    /// @name Construction and Destruction
    //@{

    /// Default constructor.
    inline SceneGraphCacheResponse();

    /// Constructor requires the original request identifier, the category on which to send
    /// the response, a handle, and the additional request data.
    inline SceneGraphCacheResponse(
        const efd::utf8string& identifier,
        const efd::Category& responseCategory,
        SceneGraphCache::ISceneGraphCacheRequestData* pRequestData,
        const efd::AssetCacheResponse::AssetCacheResult result,
        const efd::AssetCacheResponse::AssetCacheType type);

    /// Destructor
    inline virtual ~SceneGraphCacheResponse();

    //@}

    /// @name Getters

    /**
        Get the identifier.
    */
    inline const efd::utf8string& GetIdentifier() const;

    /**
        Get the request data.
    */
    inline SceneGraphCache::ISceneGraphCacheRequestData* GetRequestData() const;

    /**
        Get the number of handles.
    */
    inline efd::UInt32 GetHandleCount() const;

    /**
        Get a handle.

        Index must be less than the value returned by GetHandleCount and it is not range-checked.

    */
    inline SceneGraphCache::SceneGraphCacheHandle GetHandle(const efd::UInt32 index) const;

    //@}

    /// @cond EMERGENT_INTERNAL

    /// Add a handle
    inline void AddHandle(const SceneGraphCache::SceneGraphCacheHandle handle);

    /// @endcond

protected:
    SceneGraphCache::ISceneGraphCacheRequestData* m_pRequestData;
    efd::vector<SceneGraphCache::SceneGraphCacheHandle> m_handles;
};

/// A SmartPointer for the SceneGraphCacheResponse class
typedef efd::SmartPointer<SceneGraphCacheResponse> SceneGraphCacheResponsePtr;
/// A SmartPointer for the const SceneGraphCacheResponse class
typedef efd::SmartPointer<const SceneGraphCacheResponse> SceneGraphCacheResponseConstPtr;

} // end namespace efd

#include <ecr/SceneGraphCacheResponse.inl>

#endif // EE_SCENEGRAPHCACHERESPONSE_H
