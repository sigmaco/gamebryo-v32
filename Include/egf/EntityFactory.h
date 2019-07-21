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
#ifndef EE_ENTITYFACTORY_H
#define EE_ENTITYFACTORY_H

#include <egf/egfLibType.h>
#include <egf/egfClassIDs.h>
#include <efd/BaseAssetFactory.h>
#include <egf/FlatModelFactoryRequest.h>
#include <efd/CriticalSection.h>
#include <egf/FlatModelFactory.h>

namespace efd
{
// forward declarations
class AssetLoadRequest;
class AssetLoadResponse;
}

namespace egf
{
// forward declarations
class EntityFactoryRequest;
class EntityFactoryResponse;
class FlatModelFactoryResponse;

/**
    An IAssetFactory that takes an EntityFactoryRequest and attempts to load the flat model
    from disk and create a Entity instance. The result of this request is returned using
    an EntityFactoryResponse. All mix in models that are not already registered with
    the FlatModelManager are also added to the response.

    Callers to EntityLoader::LoadAsset are responsible for looking up and setting the
    asset path to the underlying flat model file in the EntityFactoryRequest.

    The EntityFactory is not typically called directly. Instead, it responds to a request from
    the AssetFactoryManager to load a particular asset. The AssetFactoryManager is responsible
    for locating the fully qualified path using the provided URN and setting this value in
    the EntityFactoryRequest object.

    For mix in models, the EntityLoader uses FlatModelFactory, which in turn directly uses the
    AssetLocatorService directly to locate mix in underlying flat model file fully qualified
    paths.

    The caller is responsible for allocating and deallocating the EnityFactoryRequest.

    The EntityFactory allocates the response, it is the callers responsibility to
    deallocate it.

    The EntityFactory does not add the resulting Entities to the EntityManager nor any
    flat model(s) to the FlatModelManager. The caller is responsible for doing so if required.
*/
class EE_EGF_ENTRY EntityFactory : public efd::BaseAssetFactory
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(EntityFactory, efd::kCLASSID_EntityFactory, efd::BaseAssetFactory);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

public:
    /// @name Construction and Destruction
    //@{

    /**
        Construct a new EntityLoader. The EntityLoader uses an egf::FlatModelLoader to load
        required flat models. It use the FlatModelManager::FactoryEntity method to factory
        the resulting Entity pointer.

        @param fmLoader FlatModelFactory used to load flat model files.
    */
    EntityFactory(egf::FlatModelFactory* fmLoader);

    /// Cleanup any open resources.
    ~EntityFactory();

    //@}

    /**
        Attempt to load an entity. If the loader is processing a URN and a new request
        arrives for that same URN, the loader will not attempt to load them simultaneously.
        Instead, LoadAsset returns IAssetFactory::LOAD_BLOCKED to indicate the request was
        blocked. The caller can make the same request again later.

        @see efd::IAssetFactory::LoadStatus for further details.

        @param pFactoryManager The AssetFactoryManager instance invoking this function.
        @param pRequest asset load request.
        @param ppResponse asset load response allocated by this factory.
        @return IAssetFactory::LoadStatus status of this load.
    */
    IAssetFactory::LoadStatus LoadAsset(
        efd::AssetFactoryManager* pFactoryManager,
        const efd::AssetLoadRequest* pRequest,
        efd::AssetLoadResponsePtr& ppResponse);

    /// Thread status description.
    ///
    /// This loader is thread safe for foreground or background use.
    IAssetFactory::ThreadSafetyDescription GetThreadSafety() const;

protected:
    class EntityFactoryData : public efd::IAssetResponseData
    {
        /// @cond EMERGENT_INTERNAL

        EE_DECLARE_CLASS1(
            EntityFactory::EntityFactoryData,
            efd::kCLASSID_EntityFactoryData,
            efd::IAssetResponseData);

        EE_DECLARE_CONCRETE_REFCOUNT;

        /// @endcond

    public:
        FlatModelFactoryRequestPtr m_spFlatModelRequest;
    };

    /// A SmartPointer for the EntityFactory::EntityFactoryData class
    typedef efd::SmartPointer<EntityFactoryData> EntityFactoryDataPtr;

private:
    // Don't let the compiler generate these. We don't provide a deep-copy function
    // so any compiler-generated versions of these functions would be incorrect.
    EntityFactory& operator=(const EntityFactory&);
    EntityFactory(const EntityFactory&);

    // helper function. This loads the Entity using the FlatModelManager once
    // the Entity's flat model is successfully loaded using the FlatModelLoader.
    efd::IAssetFactory::LoadStatus LoadEntity(
        const egf::EntityFactoryRequest* pCurrentRequest,
        egf::FlatModelFactoryResponse* pFlatModelLoadResponse,
        efd::AssetLoadResponsePtr& ppResponse);

    egf::FlatModelFactoryPtr m_spFMLoader;
};

/// A SmartPointer for the egf::EntityFactory class
typedef efd::SmartPointer<egf::EntityFactory> EntityFactoryPtr;

} // end namespace egf

#endif // EE_ENTITYFACTORY_H
