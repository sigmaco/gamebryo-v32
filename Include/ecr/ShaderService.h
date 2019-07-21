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
#ifndef EE_SHADERSERVICE_H
#define EE_SHADERSERVICE_H

#include "ecrLibType.h"
#include <efd/MessageHandlerBase.h>
#include <efd/IMessage.h>
#include <efd/ISystemService.h>
#include <efd/AssetLocatorResponse.h>
#include <ecr/ecrClassIDs.h>
#include <ecr/ecrSystemServiceIDs.h>

#include <NiShaderParser.h>
#include <NiShaderLibrary.h>

namespace efd
{
    class AssetLocatorResponse;
    class AssetLocatorService;
    class MessageService;
};

namespace ecr
{

/**
    The ShaderService service manages the creation of Gamebryo shaders from
    shader files, using the shader libraries that have been loaded.

    In the ShaderService constructor, a Boolean parameter is provided that indicates
    whether the ShaderService should attempt to create new instances of the shader
    libraries. Once this is done, the ShaderService will maintain a list of all
    the loaded shader parsers and shader libraries, and what file types they can use.

    The shader service requires that a efd::MessageService object and an
    efd::AssetLocatorService object be available at the time the ShaderService object
    is added to the ServiceManager. Hence, the Message Service and Asset Locator Service
    must be registered before the Shader Service.
*/
class EE_ECR_ENTRY ShaderService : public efd::ISystemService
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(ShaderService, efd::kCLASSID_ShaderService, efd::ISystemService);
    EE_DECLARE_CONCRETE_REFCOUNT;
    /// @endcond
public:
    /**
        Constructor.

        The constructor prepares a list of MIME types for shaders that it will be responsible
        for managing.

        @param createShaderLibs If true, any shader libraries that have been linked will have
            their respective Create functions called in order to create new instances of the
            NiShaderLibrary objects. Otherwise, the service assumes that the NiShaderLibrary
            objects have already been created.
    */
    ShaderService(bool createShaderLibs);

    /**
        Destructor.
    */
    virtual ~ShaderService();

    /**
        Return the name of the service, in this case "ShaderService".
    */
    virtual const char* GetDisplayName() const;

    /**
        OnPreInit subscribes to messages.
    */
    virtual efd::SyncResult OnPreInit(efd::IDependencyRegistrar* pDependencyRegistrar);

    /**
        OnInit manages the initialization of the shader parsers and shader libraries.
        It also runs the parsers on libraries on the shader assets, generating shaders.
    */
    virtual efd::AsyncResult OnInit();

    /// The OnTick function does nothing and always succeeds.
    virtual efd::AsyncResult OnTick();

    /**
        Shuts down the shader service, and releases the shader parsers and
        shader libraries.
    */
    virtual efd::AsyncResult OnShutdown();

    /// Asset locator response message handler
    void HandleAssetLocatorResponse(const efd::AssetLocatorResponse* pMessage,
        efd::Category targetChannel);

    /// The ShaderService loads a number of shader programs by MIME type.
    /// This function can be used to add additional MIME types
    /// e.g. assembly-vertex-shader.  This function must be called pre-OnInit.
    void AddShaderProgramType(const char* pMimeType);

    /**
        Sets the maximum amount of time (in seconds) the ShaderService is allowed 
        to spend in OnInit() while parsing & loading shaders.
        
        Smaller values of 
        fMaxTimeInSec result in more OnInit() cycles. Note that it is possible for
        more than fMaxTimeInSec time to be spent in OnInit() if a single shader
        takes longer than fMaxTimeInSec to be parsed or loaded. ShaderService uses
        a default max on OnInit() time of 10 ms.

        This method must be called pre-OnInit.
    */
    void SetMaxOnInitTime(float fMaxTimeInSec);

    /**
        Returns the maximum amount of time (in seconds) that the ShaderService is
        allowed to spend in OnInit().
    */
    float GetMaxOnInitTime();

protected:

    /**
        Custom class used to store a shader path along with the parser & library
        that should be used to for the shader. Each PendingWork object represents
        a shader that needs to be either parsed or loaded.
    */
    class EE_ECR_ENTRY PendingWork : public efd::MemObject
    {
    EE_DECLARE_CONCRETE_REFCOUNT;

    public:
        PendingWork()
        {
            m_pLibrary = NULL;
            m_pParser = NULL;
            m_pFileName = "";
        }

        NiShaderLibrary* m_pLibrary;
        NiShaderParser* m_pParser;
        efd::utf8string m_pFileName;
    };
    typedef efd::SmartPointer<PendingWork> PendingWorkPtr;

    /**
        Creates NiShaderParser objects from the shader parser libraries that have been loaded
    */
    void CreateShaderParsers();

    /**
        Creates NiShaderLibrary objects from the shader libraries that have been loaded
    */
    void CreateShaderLibraries();

    /**
        Creates the mapping of asset MIME type to NiShaderParser or NiShaderLibrary objects
        that are capable of loading them.
    */
    void AddInitialFiles();

    /**
        Registers the path of all the shader program files with the NiShaderFactory.
    */
    void CreateProgramMap(const efd::AssetLocatorResponse* msg);

    void ParseShader(PendingWork* pPendingWork);
    bool LoadShader(PendingWork* pPendingWork);

    NiShaderLibrary* FindShaderLibForMimeType(const char* pMimeType);

    efd::MessageService* m_pMessageService;
    efd::AssetLocatorService* m_pAssetLocator;

    NiTObjectArray<NiShaderParserPtr> m_parsers;
    NiTObjectArray<NiShaderLibraryPtr> m_libraries;

    /// Parsed shaders get loaded automatically.  This keeps tracks of those shaders.
    efd::vector<efd::FixedString> m_parsedShaders;
    /// uri -> parser mapping.  Used to handle results of asset location.
    efd::map<efd::utf8string, NiShaderParser*> m_pendingParseLocate;
    /// uri -> library mapping.  Used to handle results of asset location.
    efd::map<efd::utf8string, NiShaderLibrary*> m_pendingLoadLocate;     

    /// List of shader program types to load.
    efd::vector<efd::utf8string> m_shaderProgramTypes;

    enum ShaderServiceState
    {
        SS_STATE_INITIAL,
        SS_STATE_FINDING_PROGRAMS,
        SS_STATE_FOUND_PROGRAMS,
        SS_STATE_PARSING,
        SS_STATE_LOADING,
        SS_STATE_READY,
        SS_STATE_MAX
    };
    ShaderServiceState m_state;

    /// Category for loading shaders to parse
    efd::Category m_parseCategory;
    /// Category for shader technique files to load
    efd::Category m_loadCategory;
    /// Category for shader program files to load
    efd::Category m_programCategory;

    /// List of shaders that need to be parsed. Shader parsing will occur over multiple
    /// OnInit() calls.
    efd::list<PendingWorkPtr> m_pendingParse;

    /// List of shaders that need to be loaded. Shader loading will occur over multiple
    /// OnInit() calls.
    efd::list<PendingWorkPtr> m_pendingLoad;

    /// Tracking information used for parsing and loading shaders over multiple
    /// OnInit() calls.
    efd::map<efd::utf8string, NiShaderParser*>::const_iterator m_parsingIterator;
    efd::map<efd::utf8string, NiShaderLibrary*>::const_iterator m_loadingIterator;

    /// Max time, in seconds, that ShaderService::OnInit() is allowed
    /// to spend parsing & loading shaders.
    float m_maxOnInitTime;

    /// Tracking information used for locating all possible shader paths over multiple
    /// OnInit() calls.
    efd::UInt32 m_findingProgramsIndex;
    efd::UInt32 m_programLocateMessageCount;

    bool m_createShaderLibs;

};
typedef efd::SmartPointer<ShaderService> ShaderServicePtr;

}; // namespace

#endif // EE_SHADERSERVICE_H
