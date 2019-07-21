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
#ifndef _IASSETTAGGER_H
#define _IASSETTAGGER_H

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
      IAssetTagger is a virtual interface class used to define tagging extensions for use
      in the Asset Controller application.  Each tagging extension that is registered gets
      invoked for every new asset when it is first discovered.  A child class can process
      the asset to determine whether certain tag or property values ought to be set for the
      asset.  Tags that are created in this way become part of the generated metadata for
      the asset web.
    */
    class IAssetTagger : public efd::IBase
    {
        /// @cond EMERGENT_INTERNAL
            
        EE_DECLARE_INTERFACE1(IAssetTagger, efd::kCLASSID_AssetTagger, efd::IBase);
        
        /// @endcond
        
    public:
        /**
          Returns a list of tag descriptors for all the tags that can possibly be applied
          by this tagging extension.

          @param tags Vector container for the tag descriptors
        */
        virtual void GetTagValues (efd::vector<efd::AssetTagDescriptor>& tags)=0;

        /**
          Apply any desired tags or properties to the new asset indicated by the physical
          asset Id.

          @param assetid The physical Id (urn:uuid:XXXXXX) for newly discovered asset
          @param triples A SimpleGraph container that will hold any persistent metadata
            that already existed, or ought to be created, for this new asset.
        */
        virtual void DoTags (const efd::utf8string& assetid, SimpleGraph& triples)=0;

        /// Set the AssetWeb metadata store that this tagging extension is registered with
        void SetAssetWeb (AssetWeb* web)
        {
            m_web = web;
        }

    protected:
        /// Associated AssetWeb
        AssetWeb* m_web;
    };

    typedef efd::SmartPointer<IAssetTagger> AssetTaggerPtr;

} // namespace
#endif

