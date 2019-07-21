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
#ifndef EE_BASEASSETFACTORY_H
#define EE_BASEASSETFACTORY_H

#include <efd/efdLibType.h>
#include <efd/IAssetFactory.h>
#include <efd/CriticalSection.h>
#include <efd/StdContainers.h>
#include <efd/efdClassIDs.h>

namespace efd
{

// Forward declarations
class AssetLoadResponse;

/**
    Base class for intermediate information needed by IAssetFactory instances when processing load
    requests. Children of this class need to declare either a non-atomic or atomic reference count
    using EE_DECLARE_CONCRETE_REFCOUNT or EE_DECLARE_CONCRETE_ATOMIC_REFCOUNT, respectively.
 */
class EE_EFD_ENTRY IAssetResponseData : public efd::IBase
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_INTERFACE1(IAssetResponseData, efd::kCLASSID_IAssetResponseData, efd::IBase);
    /// @endcond

public:
    /// Default constructor
    IAssetResponseData();

    /// Response eventually returned to the caller.
    efd::SmartPointer<AssetLoadResponse> m_spResponse;

    /// True if this a response to a foreground load request.
    bool m_isForeground;

    /// Get the response as a specific type. This will dynamically cast the existing
    /// AssetLoadResponse to the provided type.
    template<typename T>
    T* GetResponseAs() const;
};

/// A SmartPointer for the IAssetResponseData class
typedef efd::SmartPointer<IAssetResponseData> IAssetResponseDataPtr;


/**
    Abstract base class for Asset Factory classes. Provides common functionality typically
    needed by an implementation of an IAssetFactory class.
 */
class EE_EFD_ENTRY BaseAssetFactory : public efd::IAssetFactory
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_INTERFACE1(BaseAssetFactory, efd::kCLASSID_BaseAssetFactory, efd::IAssetFactory);
    EE_DECLARE_ABSTRACT_REFCOUNT;
    /// @endcond

public:

    /// @name Construction and Destruction
    //@{

    /// Default constructor
    BaseAssetFactory();

    /// Pure virtual destructor. BaseAssetFactory can not be directly instantiated.
    virtual ~BaseAssetFactory() = 0;

    //@}

protected:
    /**
        Get the current IAssetResponseData for the provided request, or NULL if a current
        response does not exist.

        @param pRequest AssetLoadRequest to lookup.
        @param ppResponse Current response data associated with the request.
        @return LOAD_BLOCKED if an existing request is already processing the URN,
            LOAD_RUNNING if not.
    */
    efd::IAssetFactory::LoadStatus GetResponseData(
        const efd::AssetLoadRequest *pRequest,
        IAssetResponseData*& ppResponse);

    /**
        Get the current response data for the provided request. If no response data exists
        for this requests, return NULL. This template attempts to dynamically cast the
        IAssetResponseData into the provided type.

        @param pRequest AssetLoadRequest to lookup.
        @param pResponseData Current response data associated with the request.
        @return LOAD_BLOCKED if an existing request is already processing the URN,
            LOAD_RUNNING if not.
    */
    template<typename T>
    efd::IAssetFactory::LoadStatus GetResponseDataAs(
        const efd::AssetLoadRequest* pRequest,
        T*& pResponseData);
    template<typename T>
    efd::IAssetFactory::LoadStatus GetResponseDataAs(
        const efd::AssetLoadRequest* pRequest,
        efd::SmartPointer<T>& spResponseData);

    /**
        Remove the response data associated with the given AssetLoadRequest.
    */
    void RemoveResponseData(const efd::AssetLoadRequest* pRequest);

    /// lock the request map to support reentrancy.
    efd::CriticalSection m_pendingRequestLock;

    /// Map of asset load request to pending response data.
    typedef efd::map<efd::SmartPointer<const AssetLoadRequest>, IAssetResponseDataPtr> PendingRequestMap;
    PendingRequestMap m_pendingRequestMap;

    // Flag indicating we have subscribed for messages.
    bool m_subscribed;
};

} // end namespace efd

#include <efd/BaseAssetFactory.inl>

#endif // EE_BASEASSETFACTORY_H
