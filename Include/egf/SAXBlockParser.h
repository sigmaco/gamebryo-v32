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
#ifndef EE_SAXBLOCKPARSER_H
#define EE_SAXBLOCKPARSER_H

#include <efd/TinyXML.h>
#include <egf/IProperty.h>
#include <egf/egfLibType.h>


namespace egf
{


/**
    A SAX-based XML parser for Emergent's Block file format. This parser reads a block file
    and generates a set of flat model file names required by the block.
*/
class EE_EGF_ENTRY SAXBlockParser
    : public efd::TiXmlDefaultHandler
    , public efd::MemObject
{

    enum ParserState
    {
        NotParsing = 0,
        InDocument
    };

public:
    /**
         Parse a .xblock file.

         @param xblockFile The full path to the xblock file to parse.
         @param [in,out] o_flatModelNameSet Set of utf8string flat model names.
         @return UInt32 The number of errors encountered while parsing.
    */
    static efd::UInt32 Parse(
        const efd::utf8string& xblockFile,
        efd::set<efd::utf8string>& o_flatModelNameSet);

    /**
        Parse a buffer with the contents of an .xblock file.

        @param name Name of the buffer, mainly for logging purposes.
        @param buffer Buffer containing the contents of the xblock file.
        @param [in, out] o_flatModelNameSet Set of utf8string flat model names.
        @return UInt32 The number of errors encountered while parsing.
    */
    static efd::UInt32 ParseBuffer(
        const efd::utf8string& name,
        const char* buffer,
        efd::set<efd::utf8string>& o_flatModelNameSet);

protected:
    /// @name XML Handlers
    /// overridden methods from SAX parser
    //@{
    virtual void startElement(
        const EE_TIXML_STRING& localname,
        const efd::TiXmlAttributeSet& attrs);

    virtual void endElement(const EE_TIXML_STRING& localname);

    virtual void characters(const EE_TIXML_STRING& chars);

    //@}

    /// Filename of the file currently being processed
    efd::utf8string m_blockFile;

    /// current state of the parser
    ParserState m_parserState;

    /// Identified flat models are added to this set.
    efd::set<efd::utf8string>& m_flatModelNameSet;

    /// Total errors are returned from parsing
    efd::UInt32 m_errors;

    /// parse the attributes contained within the model tag.
    bool ParseEntity(const efd::TiXmlAttributeSet& attrs);

    /// Called after reaching a closing model tag.
    void FinishedEntity();

private:
    /// Hidden constructor
    SAXBlockParser(
        const efd::utf8string& blockFile,
        efd::set<efd::utf8string>& o_flatModelNameSet);

    /// Disables default assignment operator
    void operator=(const SAXBlockParser&) {}

    /// Hidden destructor, use reference counting
    virtual ~SAXBlockParser();
};


} // end namespace egf

#endif // EE_SAXBLOCKPARSER_H
