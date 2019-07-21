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
#ifndef EE_SAXENTITYPARSER_H
#define EE_SAXENTITYPARSER_H

#include <efd/ServiceManager.h>
#include <efd/TinyXML.h>
#include <egf/FlatModelManager.h>
#include <egf/IProperty.h>
#include <egf/Entity.h>
#include <egf/egfLibType.h>

namespace efd
{
    class TiXmlDocument;
}

namespace egf
{
    struct XmlEntityStringConstants;

/**
    A SAX-based XML parser for the Emergent Entity Set file format
*/
class EE_EGF_ENTRY SAXEntityParser
    : public efd::TiXmlDefaultHandler
    , public efd::MemObject
{
    /// Possible states for the SAX parsing.
    enum ParserState
    {
        NotParsing = 0,
        InDocument,
        InEntity,
        SkipEntity,
        InProperty,
        InPropertyValue,
        InToolSettings
    };

public:

    /// Result enum
    enum Result
    {
        /// An invalid value
        sep_Unknown = 0,

        /// Success values. All success values are greater than zero.
        //@{
        /// The parser has completed loading a portion of the entities.
        sep_Loading,

        /// The parser has finished loading the remaining entities.
        sep_Loaded,
        //@}

        /// Error values. All errors are negative values.
        //@{
        /// Generic non-specific failure
        sep_Failed = -1000,
        //@}
    };

    /**
        Constructs a SAXEntityParser that can be used to parse a block file piecemeal.

        @param xmlBuffer Buffer containing content from a block file
        @param documentName Descriptive name (such as a filename) used for parser error messages
        @param blockInstance The block instance being loaded
        @param pfmm Pointer to an instance of the FlatModelManager service
        @param pEntityManager Pointer to the EntityManager used for resolving cross-block links
        @param pPreviouslyLoaded If reloading a block, this is the set of entities previously in
            the block.
        @return SAXEntityParser::Result The result of the parsed data.
    */
    SAXEntityParser(const char* xmlBuffer,
                    const efd::utf8string& documentName,
                    efd::UInt32 blockInstance,
                    egf::FlatModelManager* pfmm,
                    egf::EntityManager* pEntityManager,
                    efd::set<egf::EntityID>* pPreviouslyLoaded = NULL);

    /// Destructor
    virtual ~SAXEntityParser();

    /**
        Gets the maximum number of entity loads per parse.

        @return efd::UInt32 The maximum number of entities to parse each pass.
    */
    efd::UInt32 GetMaxEntityLoadsPerParsing() const;

    /**
        Sets the maximum number of entity loads per parse.

        @param entities The maximum number of entities to parse each pass.
    */
    void SetMaxEntityLoadsPerParsing(efd::UInt32 entities);

    /**
        Apply a rotation about the origin to all loaded entities. The rotation is described using
        three Euler angles expressed in degrees representing the rotation about each axis. This is
        the same form used by the "Rotation" property on the "Placeable" model
    */
    void ApplyRotation(const efd::Point3& rotation);

    /**
        Apply an offset to all loaded entities.
    */
    void ApplyOffset(const efd::Point3& offset);

    /**
        Gets the number of entities parsed.

        @return efd::UInt32 The number of entities parsed last time Parse was called.
    */
    efd::UInt32 GetEntitiesParsed() const;

    /**
        Begins the parsing of a block file.  This should only be called once.

        @param [out] o_errors The number of errors encountered while parsing
        @return SAXEntityParser::Result The result of the parsed data.
    */
    Result BeginParse(efd::UInt32& o_errors);

    /**
        Parse a block file.

        @param [out] o_entityList List of entity pointers parsed from the file
        @param [out] o_errors The number of errors encountered while parsing
        @return SAXEntityParser::Result The result of the parsed data.
    */
    Result Parse(efd::list<EntityPtr>*& o_entityList, efd::UInt32& o_errors);

    /**
        Return the list of entities parsed. This is the same list returned by calls to Parse.
    */
    efd::list<EntityPtr>* GetParserResults();

    /**
        Modified Parse function used for testing.

        This version of parse is only for use by testing code and tools that need to create
        non-master entities.

        @return The number of errors encountered while parsing
    */
    static efd::UInt32 ParseForReplicationTesting(
        const efd::utf8string& i_blockFile,
        egf::FlatModelManager* pfmm,
        efd::list<EntityPtr>& o_entityList);

    /**
        Modified Parse function used for testing.

        This version of parse is only for use by testing code and tools that need to create
        non-master entities.

        @return The number of errors encountered while parsing
    */
    static efd::UInt32 DeprecatedParse(
        const efd::utf8string& i_blockFile,
        egf::FlatModelManager* pfmm,
        efd::list<EntityPtr>& o_entityList);

    /// @cond EMERGENT_INTERNAL

    //@{
    static void _SDMInit();
    static void _SDMShutdown();
    //@}

    /// @endcond

protected:
    static XmlEntityStringConstants* ms_constants;

    /// @name XML Handlers
    /// overridden methods from SAX parser
    //@{
    virtual void startElement(
        const EE_TIXML_STRING& localname,
        const efd::TiXmlAttributeSet& attrs);

    virtual void endElement(const EE_TIXML_STRING& localname);

    virtual void characters(const EE_TIXML_STRING& chars);
    //@}

    /// Helper used by Parse and ParseForReplicationTesting
    static efd::UInt32 _Parse(
        const efd::utf8string& modelFile,
        egf::FlatModelManager* pfmm,
        bool createMasterEntities,
        efd::list<EntityPtr>& o_entityList,
        efd::ServiceManager* pServiceManager = NULL);

    /// Called after parsing is complete in order to link together all entities
    void ApplyEntityLinks();

    /// Filename of the file currently being processed
    efd::utf8string m_blockFile;

    /// The block instance ID for the block being loaded
    efd::UInt32 m_blockInstance;

    const char* m_pXmlBuffer;

    /// The document we're parsing
    efd::TiXmlDocument* m_pDocument;

    /// current state of the parser
    ParserState m_parserState;

    /// Cached for convenience
    FlatModelManager* m_pfmm;

    /// As we parse each entity we store them here until done
    EntityPtr m_spEntity;

    /// As we parse each property we remember its name and ID
    efd::utf8string m_propertyName;
    egf::PropertyID m_propID;

    /// Properties that contain EntityRef data have special linking handling, so we need to
    /// know when we are parsing one of those:
    bool m_propIsEntityRef;

    /// Created entities are returned to the caller via this list
    efd::list<EntityPtr> m_entityList;

    /// @name Created entities are also stored in a map in order to facilitate entity linking
    //@{
    typedef efd::map< efd::ID128, egf::Entity* > DataIdToEntityMap;
    DataIdToEntityMap m_entityMap;
    //@}

    /// The current number of entities we've parsed so far.
    efd::UInt32 m_entitiesParsed;

    /// The maximum number of entities to parse each time SAXParse is called.
    efd::UInt32 m_maxEntityLoadsPerParse;

    /// A flag indicating if we're partial loading the world when parsing the entity set.
    efd::Bool m_bPartialLoading;

    /// Optional pointer to the EntityManager.
    egf::EntityManager* m_pEntityManager;

    /// If non-NULL, this parse is a reload and this is the set of entities previously remaining in
    /// the block.
    efd::set<egf::EntityID>* m_pPreviouslyLoadedEntities;

    /// As we parse the data we store linking information.  Once all the entities are created we
    /// use this LinkData to update the EntityRef properties to their correct run-time values.
    struct LinkData
    {
        /// The entity with the property pointing to another entity
        egf::Entity* m_pSource;
        /// The property on the source entity to be set
        egf::PropertyID m_PropertyToLink;
        /// If the property is assoc, this is the key, otherwise its an empty string
        efd::utf8string m_key;
        /// The destination entity's DataID that the source property should point to.
        efd::ID128 m_idDest;

        LinkData(egf::Entity* pSource,
                  egf::PropertyID propertyToLink,
                  const efd::utf8string& key,
                  efd::ID128 idDest)
            : m_pSource(pSource)
            , m_PropertyToLink(propertyToLink)
            , m_key(key)
            , m_idDest(idDest)
        {
        }

        /// Use the information in the LinkData to set the link property to the given EntityID.
        /// @return The number of errors encountered, which will be either zero or one.
        efd::UInt32 SetLink(const efd::utf8string& blockFile, egf::EntityID targetID);
    };
    typedef efd::list<LinkData> LinkDataList;
    LinkDataList m_ldl;

    /// Total errors are returned from parsing
    efd::UInt32 m_errors;

    /// True if we are loading owned entities, false otherwise.  Only test programs and tools
    /// would ever set this to false.
    bool m_createMasterEntities;

    /// Rotation about the origin to apply to each entity
    efd::Point3 m_rotation;
    efd::Point3 m_rotInRads;
    bool m_useRotation;

    /// Offset to apply to each entity
    efd::Point3 m_offset;
    bool m_useOffset;

    /// parse the attributes contained within the model tag and create a model
    bool ParseEntity(const efd::TiXmlAttributeSet& attrs);

    /// parse the attributes contained with the property tag and create a prop
    void ParseProperty(const efd::TiXmlAttributeSet& attrs);

    /// parse any attributes contained in the set tag.  This currently only
    /// applies to the key element for associative array properties.
    void ParsePropertyValue(const efd::TiXmlAttributeSet& attrs);

    /// Called after reaching a closing model tag.
    void FinishedEntity(bool isNewEntity);

    /// Called after reaching a closed property tag.
    void FinishedProperty();

private:
    /// Disables default assignment operator
    void operator=(const SAXEntityParser&) {}
};

} // end namespace egf

#endif //EE_SAXENTITYPARSER_H
