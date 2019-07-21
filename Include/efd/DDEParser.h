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
#ifndef EE_DDEParser_h
#define EE_DDEParser_h

#include <efd/UniversalTypes.h>
#include <efd/utf8string.h>
#include <efd/TinyXML.h>
#include <efd/DataDrivenEnum.h>
#include <efd/DDEHeaderGenerator.h>


namespace efd
{
    class EnumManager;

    /**
        A SAX-based XML parser for Emergent's DataDrivenEnum (.enum) file format
    */
    class EE_EFD_ENTRY DDEParser
        : public efd::TiXmlDefaultHandler
        , public efd::MemObject
    {

        enum ParserState
        {
            NotParsing = 0,
            InHeader,
            InEnum,
            InItem,
            InAlias,
        };

    public:
        /**
            Constructor
        */
        DDEParser(EnumManager* pEnumMgr, IDDEHeaderGenerator* pHeaderGen = NULL);

        /// Destructor
        virtual ~DDEParser();

        /**
            Perform parsing on the given file

            @param[in] enumName friendly name for the enum to parse
            @param[in] sourceFile file name for the enum to parse
            @return The DataDrivenEnum object which supports mapping between names and ids.
        */
        void Parse(const efd::utf8string& enumName, const efd::utf8string& sourceFile);

    protected:
        /// @name Xerces Handlers
        /// overridden methods from Xerces DefaultHandler
        //@{
        virtual void startElement(
            const EE_TIXML_STRING& localname,
            const TiXmlAttributeSet& attrs);

        virtual void endElement(const EE_TIXML_STRING& localname);

        virtual void characters(const EE_TIXML_STRING& chars);
        //@}

    protected:
        /// storage for errors
        efd::UInt32 m_errors;

        /// The number of enums we have added added
        efd::UInt32 m_enumsAdded;

        /// Name of the enum being processed
        efd::utf8string m_enumName;

        /// Filename of the file currently being processed
        efd::utf8string m_sourceFile;

        /// current state of the parser
        ParserState m_parserState;

        /// The EnumManager used for finding base enums and storing the result
        EnumManager* m_pEnumMgr;

        /// The current header file that is being generated.
        IDDEHeaderGeneratorPtr m_spHeaderGen;

        /// temporary data driven enum.  Created at start of an enum element, completely
        /// constructed with items and aliases, then added to the enum manager.
        DataDrivenEnumPtr m_spDataDrivenEnum;

        /**
            parse the attributes contained within the header tag

            @param[in] attrs a TiXmlAttributeSet
        */
        void ParseHeader(const TiXmlAttributeSet& attrs);

        /**
            parse attributes from an enum tag

            @param[in] attrs a TiXmlAttributeSet
        */
        void ParseEnum(const TiXmlAttributeSet& attrs);

        /**
            parse attributes from an item tag

            @param[in] attrs a TiXmlAttributeSet
        */
        void ParseItem(const TiXmlAttributeSet& attrs);

        /**
            parse attributes from an item tag

            @param[in] attrs a TiXmlAttributeSet
        */
        void ParseAlias(const TiXmlAttributeSet& attrs);

        /// Called after reaching a closing enum tag.
        void FinishedEnum();

        /// Helper for ParseEnum
        template< typename T >
        void ParseEnumHelper(const TiXmlAttributeSet& attrs, efd::DataDrivenEnumBase* pBaseEnum);

        /// Helper for ParseItem
        template< typename T >
        void ParseItemHelper(const TiXmlAttributeSet& attrs);

        /// Helper for ParseAlias
        template< typename T >
        void ParseAliasHelper(const TiXmlAttributeSet& attrs);

        /// Helper to parse the "invalid" attribute strings
        template< typename T >
        bool SplitNameAndValue(efd::utf8string& io_invalid, T& o_value);

        /// Helper to parse a value from a string, understands the special strings EE_MAX and
        /// EE_MIN.
        template< typename T >
        bool ParseValue(const efd::utf8string& i_strValue, T& o_value);


        // <header useNamespace="efd" prefix="k" suffix=""
        //      includes="efd/Whatever.h;efd/Something.h"/>
        EE_TIXML_STRING kTagHeader;

        // <enum type="Normal" storage="efd::UInt32" bitSize="32" base="base.enum" start="1">
        EE_TIXML_STRING kTagEnum;
        EE_TIXML_STRING kAttrType;
        EE_TIXML_STRING kAttrStorage;
        EE_TIXML_STRING kAttrMax;
        EE_TIXML_STRING kAttrBase;
        EE_TIXML_STRING kAttrStart;
        EE_TIXML_STRING kAttrInvalid;

        // <item name="Whatever" value="1234"/>
        EE_TIXML_STRING kTagItem;
        EE_TIXML_STRING kAttrName;
        EE_TIXML_STRING kAttrValue;

        // <alias name="AliasedName" value="RealEnumValue" />
        EE_TIXML_STRING kTagAlias;
    };


} // end namespace efd

#endif // EE_DDEParser_h
