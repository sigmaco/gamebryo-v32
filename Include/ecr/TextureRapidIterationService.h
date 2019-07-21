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
#ifndef EE_TEXTURERAPIDITERATIONSERVICE_H
#define EE_TEXTURERAPIDITERATIONSERVICE_H

#include "ecrLibType.h"

#include "RenderService.h"
#include "SceneGraphService.h"
#include <ecr/ecrSystemServiceIDs.h>

namespace ecr
{

/**
    The texture rapid iteration service is responsible for handling rapid iteration of external
    textures.

    If a texture in the asset web is modified and the reload service is initialized, then this
    service will search through all NiSourceTexture objects for ones with a matching filename.
    Any matching textures will be reloaded from disk.

    The currently supported formats include:
     - BMP
     - DDS
     - SGI
     - TGA

    To add additional formats:
     - Register a subclass of NiImageReader capable of handling the format with NiDevImageConverter
     - Verify that the file extension is listed in the asset-web-config\MimeTagger.ini file, with a
       type of image\<whatever> (this service watches for assets with a tag including "image")

   Additional notes:
     - This class will do no work if a RapidIterationSystemService instance is not also registered
       with the service manager.
     - The AppPixelData will be destroyed as part of reloading a texture when it is rapidly
       iterated.  Titles using this service should not cache pointers returned from
       pkTexture->GetSourcePixelData().
     - As with all other rapid iteration mechanisms, it is recommended that this service is not
       used in a shipping title (wrap service creation/registration in an
       if !defined(EE_CONFIG_SHIPPING)).
*/
class EE_ECR_ENTRY TextureRapidIterationService :
    public efd::ISystemService,
    public efd::AssetChangeHandler
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(
        TextureRapidIterationService,
        efd::kCLASSID_TextureRapidIterationService,
        efd::ISystemService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond

public:
    /**
        Constructs the texture rapid iteration service and performs pre-init operations.
    */
    TextureRapidIterationService();

    /**
        Handles the asset changed message
    */
    virtual void HandleAssetChange(const efd::utf8string& physicalID, const efd::utf8string& tag);

    /**
        Handle an asset locator response message.
        @param pMessage The asset locator response message.
        @param targetChannel Channel the message was sent on.
    */
    virtual void HandleAssetLocatorResponse(
        const efd::AssetLocatorResponse* pMessage,
        efd::Category targetChannel);

protected:
    /// Cleans up any remaining resources used by the texture service.
    virtual ~TextureRapidIterationService();
    /**
        Returns the name of the service, "TextureRapidIterationService".
    */
    virtual const char* GetDisplayName() const;

    /**
        The texture service subscribes to asset locator response messages and caches pointers to
        other services.

        @return SyncResult_Complete
    */
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);

    /**
        OnInit registers for Reload Manager callbacks on supported texture types.

        @returns AsyncResult_Complete.
    */
    virtual efd::AsyncResult OnInit();

    /**
        The texture service unregisters it's message subscriptions and releases cached pointers
        during shutdown.

        @return AsyncResult_Complete
    */
    virtual efd::AsyncResult OnShutdown();

    /// Finds any existing NiSourceTexture objects that came from filename and forces them to
    /// reload the texture
    void RefreshTextureAsset(const efd::utf8string& filename);

    /// Registers an additional MIME type that will be treated as a texture format.  This is
    /// useful to enable rapid iteration when a custom texture loader has been registered with
    /// NiDevImageConverter.  It's not usually needed, since "image" is added by default.
    virtual void AddSupportedMimeType(const char* pMimeString);

    /// Pointers to other services
    //@{
    SceneGraphServicePtr m_spSceneGraphService;
    efd::MessageServicePtr m_spMessageService;
    efd::ReloadManagerPtr m_spReloadManager;
    //@}

    /// Types of textures supported
    efd::vector<efd::utf8string> m_supportedMimeTags;

    /// Categories used for asset lookup responses
    efd::Category m_assetRefreshCategory;
};

/// A SmartPointer for the TextureRapidIterationService class
typedef efd::SmartPointer<TextureRapidIterationService> TextureRapidIterationServicePtr;

} // end namespace ecr

#endif
