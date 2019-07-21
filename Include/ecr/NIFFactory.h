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
#ifndef EE_NIFFACTORY_H
#define EE_NIFFACTORY_H

#include <ecr/ecrLibType.h>
#include <ecr/ecrClassIDs.h>
#include <efd/BaseAssetFactory.h>

#include <NiTexturePalette.h>

// forward declarations
namespace efd
{
    class AssetFactoryRequest;
    class AssetFactoryResponse;
    class AssetFactoryManager;
}

namespace ecr
{

/**
    The NIFFactory creates NIF assets.
*/
class EE_ECR_ENTRY NIFFactory : public efd::BaseAssetFactory
{
    /// @cond EMERGENT_INTERNAL

    EE_DECLARE_CLASS1(NIFFactory, efd::kCLASSID_NIFFactory, efd::BaseAssetFactory);
    EE_DECLARE_CONCRETE_ATOMIC_REFCOUNT;

    /// @endcond

public:
    /// @name Constructors and Destructors
    //@{

    /**
        Constructor.

        @param pTexturePalette The texture palette to use when loading NIF files with this
            factory.
    */
    NIFFactory(NiTexturePalette* pTexturePalette = 0);

    /// Cleanup any open resources.
    virtual ~NIFFactory();

    //@}

    /**
        Load a NIF asset.

        The asset is loaded in pieces, as supported by NiStream. It may take several calls to
        this function to complete the load of a single asset.
    */
    efd::IAssetFactory::LoadStatus LoadAsset(
        efd::AssetFactoryManager* pFactoryManager,
        const efd::AssetLoadRequest* pRequest,
        efd::SmartPointer<efd::AssetLoadResponse>& pResponse);

    /**
        The NIFFactory is safe for use in the foreground or background.
    */
    virtual ThreadSafetyDescription GetThreadSafety() const;

private:
    // Don't let the compiler generate these. We don't provide a deep-copy function
    // so any compiler-generated versions of these functions would be incorrect.
    NIFFactory& operator=(const NIFFactory&);
    NIFFactory(const NIFFactory&);

    NiTexturePalettePtr m_spTexturePalette;
};

/// A SmartPointer for the NIFFactory class
typedef efd::SmartPointer<ecr::NIFFactory> NIFFactoryPtr;

#include "NIFFactory.inl"

} // end namespace ecr

#endif // EE_NIFFACTORY_H
