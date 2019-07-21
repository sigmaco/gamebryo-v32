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
#ifndef NISHADERPARSER_H
#define NISHADERPARSER_H

#include "NiMainLibType.h"
#include "NiRefObject.h"
#include "NiSmartPointer.h"
#include "NiTSet.h"
#include "NiTArray.h"
#include "NiFixedString.h"

class NIMAIN_ENTRY NiShaderParser : public NiRefObject
{
public:
    /// Function definition for creating an arbitrary shader parser.
    typedef NiShaderParser* (*NISHADERPARSER_CLASSCREATIONCALLBACK)();

    /// Parse a single file.  Returns true if it was successful.
    /// The number of generated files is returned in uiCount.
    /// If non-NULL, pkFileNames will be filled with the generated filenames.
    virtual bool ParseFile(const char* pcFile, unsigned int& uiCount,
        NiTObjectArray<NiFixedString>* pkFileNames = NULL) = 0;

    /// Parses all of the files in a given directory (optionally recursing.)
    /// The number of generated files is returned in uiCount.
    /// If non-NULL, pkFileNames will be filled with the generated filenames.
    virtual void ParseAllFiles(const char* pszDirectory,
        bool bRecurseDirectories, unsigned int& uiCount,
        NiTObjectArray<NiFixedString>* pkFileNames = NULL) = 0;

    /// Returns the number of mime types that this parser can parse.
    virtual unsigned int GetNumSupportedMimeTypes() const = 0;
    /// Returns the name of a given mime type.
    virtual const char* GetSupportedMimeType(unsigned int uiIdx) const = 0;
    /// Returns the mime type for files that this parser generates.
    virtual const char* GetOutputMimeType() const = 0;

    /// Add shader parser create function. Used by SDM init chain.
    /// Parser names must be unique.  This function will replace the
    /// callback if the parser name already exists.
    static void AddParserCallback(const char* pcName,
        NISHADERPARSER_CLASSCREATIONCALLBACK pkCallback);
    /// Remove shader parser create function. Used by SDM shutdown chain.
    static void RemoveParserCallback(
        NISHADERPARSER_CLASSCREATIONCALLBACK pkCallback);
    /// Return the total number of parser creation functions.
    static unsigned int GetNumParserCallbacks();
    static const char* GetParserName(unsigned int uiIdx);
    static NISHADERPARSER_CLASSCREATIONCALLBACK GetParserCallback(
        unsigned int uiIdx);

    // *** begin Emergent internal use only ***
    static void _SDMInit();
    static void _SDMShutdown();
    // *** end Emergent internal use only ***

protected:
    struct ParserCallbackInfo
    {
        const char* pcName;
        NISHADERPARSER_CLASSCREATIONCALLBACK pfnCallback;
    };
    /// Set of parsers libs that have been loaded through the SDM chain.
    static NiTPrimitiveSet<ParserCallbackInfo>* ms_pkParserCallbacks;
};

typedef efd::SmartPointer<NiShaderParser> NiShaderParserPtr;

#endif  // #ifndef NISHADERPARSER_H
