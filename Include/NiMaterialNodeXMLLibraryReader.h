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

#ifndef NIMATERIALNODEXMLLIBRARYREADER_H
#define NIMATERIALNODEXMLLIBRARYREADER_H

#include "NiMaterialNodeXMLLibraryReaderLibType.h"
#include <NiMaterialNodeLibraryReader.h>


namespace efd
{
class TiXmlElement;
}
class NiMaterialFragmentNode;


class NIMATERIALNODEXMLLIBRARYREADER_ENTRY NiMaterialNodeXMLLibraryReader :
    public NiMaterialNodeLibraryReader
{
public:
    NiMaterialNodeXMLLibraryReader();
    virtual NiMaterialNodeLibrary* Load(const char* pcFilename);
protected:
    void ProcessXML(NiMaterialNodeLibrary*& pkLib, efd::TiXmlElement* pkElement);
    bool ProcessFragment(efd::TiXmlElement* pkElement,
        NiMaterialFragmentNode* pkFrag);
    bool ProcessResource(efd::TiXmlElement* pkElement,
        NiMaterialNode* pkNode, bool bInput);
    bool ProcessCode(efd::TiXmlElement* pkElement, NiMaterialFragmentNode* pkNode);
    bool ProcessDesc(efd::TiXmlElement* pkElement, NiMaterialFragmentNode* pkNode);
};

typedef efd::SmartPointer<NiMaterialNodeXMLLibraryReader>
    NiMaterialNodeXMLLibraryReaderPtr;

#endif  //#ifndef NIMATERIALNODEXMLLIBRARYREADER_H
