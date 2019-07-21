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
#ifndef EE_FLATMODELFACTORYRESPONSE_H
#define EE_FLATMODELFACTORYRESPONSE_H

#include <efd/AssetLoadRequest.h>
#include <efd/AssetLoadResponse.h>
#include <egf/egfMessageIDs.h>
#include <egf/egfLibType.h>
#include <egf/FlatModel.h>
#include <efd/StdContainers.h>
#include <egf/ScriptFactoryResponse.h>

namespace egf
{
// forward declarations
class FlatModelFactory;
class FlatModelFactoryRequest;

/**
    The FlatModelFactoryResponse is used to return a FlatModel in response to a flat model load
    request. The response also includes any additional flat models needed by the runtime and
    any scripts associated with the model.
*/
class EE_EGF_ENTRY FlatModelFactoryResponse : public efd::AssetLoadResponse
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(
        FlatModelFactoryResponse,
        efd::kMSGID_FlatModelFactoryResponse,
        efd::AssetLoadResponse);
    /// @endcond

public:
    typedef efd::map<efd::utf8string, egf::FlatModelPtr> FlatModelMap;
    typedef efd::set<egf::ScriptFactoryResponsePtr> DependentScriptSet;

    /// default constructor
    FlatModelFactoryResponse();

    /**
        Construct a new FlatModelFactoryResponse.

        @param urn the original request URN.
        @param responseCategory category expecting the response.
        @param result the result of the load.
        @param assetPath the asset path.
        @param isReload specify if is reload or not.
        @param modelName the model name.
        @param flatModelMap map of flat model name to FlatModel objects.
        @param scriptFactoryResponseSet messages containing dependent script files.
    */
    FlatModelFactoryResponse(
        const efd::utf8string& urn,
        const efd::Category& responseCategory,
        efd::AssetLoadResponse::AssetLoadResult result,
        const efd::utf8string& assetPath = "",
        bool isReload = false,
        const efd::utf8string& modelName = "",
        FlatModelMap flatModelMap = FlatModelMap(),
        DependentScriptSet scriptFactoryResponseSet = DependentScriptSet());

    /**
        Get the name of the flat model.

        @return model name, or empty string if the load failed.
    */
    const efd::utf8string& GetModelName() const;

    /**
        Get the requested flat model.

        @return FlatModePtr The resulting flat model or 0 if the load failed.
    */
    egf::FlatModelPtr GetFlatModel() const;

    /**
        Get the flat model mix in models.

        @return FlatModelMap Map of flat model name to FlatModel objects.
    */
    const FlatModelMap& GetFlatModelMap() const;

    /**
        Add a dependent script to this response.

        @param pResponse dependent script load response.
    */
    void AddDependentScript(egf::ScriptFactoryResponse* pResponse);

    /**
        Get scripts required by this flat model.

        @return egf::ScriptFactoryResponseSet set of ScriptFactoryResponse messages.
    */
    const DependentScriptSet& GetDependentScripts() const;

protected:
    // let the FlatModelFactory have direct access to our member variables to avoid
    // having to make these variables public or creating accessor for them.
    friend class egf::FlatModelFactory;

    efd::utf8string m_modelName;
    mutable FlatModelMap m_flatModelMap;
    DependentScriptSet m_dependentScriptSet;
};

/// A SmartPointer for the FlatModelFactoryResponse class
typedef efd::SmartPointer<FlatModelFactoryResponse> FlatModelFactoryResponsePtr;
/// An efd::set of efd::SmartPointers to egf::FlatModelFactoryResponse class instances
typedef efd::set<FlatModelFactoryResponsePtr> FlatModelFactoryResponseSet;

} // end namespace egf

#endif // EE_FLATMODELFACTORYRESPONSE_H
