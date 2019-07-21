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
#ifndef _ASSETSERVER_WEB_URIREADER_H
#define _ASSETSERVER_WEB_URIREADER_H

#include <efd/UniversalTypes.h>
#include <efd/utf8string.h>
#include <efd/Serialize.h>

namespace efd
{
/// Tags have a type and a value
enum AWebTagType
{
    AWEB_NONE_TAG_TYPE,
    AWEB_STANDARD_TAG_TYPE,
    AWEB_LABEL_TAG_TYPE,
    AWEB_CLASSIFICATION_TAG_TYPE
};

struct AssetTagDescriptor
{
    AWebTagType ttype;
    efd::utf8string tvalue;
    efd::Bool operator ==(const efd::AssetTagDescriptor& other) const
    {
        return ((ttype==other.ttype) && (tvalue==other.tvalue));
    }
};

/**
    This class provides methods for creating and dealing with URIs as they are used by
    the other Asset Service classes. The fundamental purpose is to parse a URI string into
    its constituent parts, like individual tags, the asset name, the asset Id, etc.
*/
class EE_EFD_ENTRY URIReader
{
    public:
        /// @name Constants
        /// We define several string constants for predicates used in the asset web metadata.
        //@{

        static const char* GlobalNamespace;
        static const char* GlobalNamespace_tag;
        static const char* GlobalNamespace_label;
        static const char* GlobalNamespace_class;
        static const char* GlobalNamespace_name;
        static const char* GlobalNamespace_relpath;
        static const char* GlobalNamespace_canonical;
        static const char* GlobalNamespace_llid;
        static const char* GlobalNamespace_logpath;
        static const char* GlobalNamespace_stdtags;
        static const char* GlobalNamespace_stdtags_value;
        static const char* GlobalNamespace_usertags;
        static const char* GlobalNamespace_usertags_value;
        static const char* GlobalNamespace_userenums;
        static const char* GlobalNamespace_userenums_value;
        static const char* GlobalNamespace_ids;
        static const char* GlobalNamespace_ids_instance;
        static const char* GlobalNamespace_ids_author;
        static const char* GlobalNamespace_ckpt;
        static const char* GlobalNamespace_ckpt_success;
        static const char* GlobalNamespace_ckpt_hash;
        static const char* GlobalNamespace_ckpt_version;
        static const char* GlobalNamespace_llid_persist;
         //@}

        /// @name Constructors
        //@{
        /// Create a URIReader class from the given URI string value.
        URIReader (const efd::utf8string& uri);
        /// Create a URIReader class for the 'uri' string, but allow it to contain any tags in
        /// 'tagNames'.
        URIReader (const efd::utf8string& uri,
            const efd::vector<AssetTagDescriptor>& tagNames);
        //@}

        /// Specifies whether the URI represents a valid physical asset id (format urn:uuid:X)
        static efd::Bool isAssetId (const utf8string& uri);
        efd::Bool isAssetId();

        /// Retrieves the URI in the typical asset id format like 'urn:uuid:XXXXX'
        void getAssetId (efd::utf8string& uri);

        /// Retrieve the scheme of the URI. Should always be equal to 'urn'
        void getScheme(efd::utf8string& scheme);

        /// Retrieve the asset name element of the URI, if present
        void getNameLiteral(efd::utf8string& name);

        /// Retrieve the canonical path for the asset URI, if present
        void getCanonicalLiteral(efd::utf8string& name);

        /// Retrieve the logical asset id for the asset URI, if present
        void getLogicalId(efd::utf8string& id);

        /// Retrieve a list of all the tags in the URI
        void getTagLiterals(efd::vector<efd::utf8string>& tagNames);

        /// Retrieve a list of all the label tags in the URI
        void getLabels(efd::vector<efd::utf8string>& labelNames);

        /// Retrieve a list of all the classification tags in the URI
        void getClassifications(efd::vector<efd::utf8string>& classNames);

        /// Check and return True if 'tag' is one of the tags in the URI
        efd::Bool hasTag(const efd::utf8string& tag);

        /// Retrieve the decimal value of the upper 8 bits of the name for isAssetId()==True
        int UpperBitsValue();

        // *** begin Emergent internal use only ***
        static void _SDMInit();
        static void _SDMShutdown();
        // *** end Emergent internal use only ***
    private:
        /// Private method that does the URI parsing
        void splitURI(const efd::vector<efd::AssetTagDescriptor>& tagNames);

        /// List of tags that the URI has
        efd::map<efd::utf8string, AWebTagType> m_uriTags;
        efd::vector<efd::utf8string> m_uriOverrides;

        /// Parts of the URI
        efd::utf8string m_uri, m_scheme, m_canonical, m_name, m_logical_id;
        /// Flag to indicate the URI has Asset Id format like 'urn:uuid:X'
        bool m_isUid;
};
} // end namespace efd

EE_SPECIALIZE_ENUM(efd::AWebTagType, efd::UInt8);

#endif

