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
#ifndef EE_IASSETIMPORTER_H
#define EE_IASSETIMPORTER_H

#include <efd/IDs.h>
#include <efd/utf8string.h>
#include <efd/StdContainers.h>
#include <efd/AssetUriReader.h>
#include <efd/AssetMetaGraph.h>
#include <efd/efdClassIDs.h>

namespace efd
{
// forward declared
class AssetWeb;

/**
    IAssetImporter is a virtual interface class used to define asset importing extensions
    in the Asset Controller application.  Each import extension that is registered gets
    invoked for every new asset when it is first discovered.  A child class can process
    the asset to determine whether certain tag or property values ought to be set for the
    asset.  Tags that are created in this way become part of the generated metadata for
    the asset web.
*/
class IAssetImporter : public efd::IBase
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_INTERFACE1(IAssetImporter, efd::kCLASSID_AssetImporter, efd::IBase);
    /// @endcond

public:
    /**
        Returns a list of tag descriptors for all the tags that can possibly be applied by this
        extension.

        @param tags Vector container for the tag descriptors
    */
    virtual void GetTagValues (efd::vector<efd::AssetTagDescriptor>& tags) = 0;

    /**
        Process the new asset indicated by the relativePath and create metadata.

        @param relativePath The relative path of the asset file
        @param triples A SimpleGraph container that will hold any metadata that the Import() method
            wants to create for the asset.
    */
    virtual void Import (const efd::utf8string& relativePath, SimpleGraph& triples) = 0;

    /// Set the AssetWeb metadata store that this extension is registered with
    void SetAssetWeb (AssetWeb* web)
    {
        m_web = web;
    }

protected:
    /// Associated AssetWeb
    AssetWeb* m_web;
};

/// A SmartPointer for the IAssetImporter class
typedef efd::SmartPointer<IAssetImporter> AssetImporterPtr;

} // end namespace efd

#endif // EE_IASSETIMPORTER_H

