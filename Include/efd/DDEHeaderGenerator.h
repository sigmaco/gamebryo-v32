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
#ifndef EE_DDEHeaderGenerator_h
#define EE_DDEHeaderGenerator_h

#include <efd/DataDrivenEnum.h>
#include <efd/TinyXML.h>


namespace efd
{

    class IDDEHeaderGenerator : public efd::RefCount
    {
    public:
        /// Parse the attributes for the header tag in an enum file
        virtual bool ParseHeaderTag(const efd::utf8string& sourceFile,
                                     const TiXmlAttributeSet& attrs) = 0;

        /// Generate a header file using the settings obtained during the ParseHeaderTag call
        /// and the given enumeration.
        virtual bool GenerateEnum(efd::DataDrivenEnumBase* pEnum) = 0;
    };

    /// SmartPointer for the IDDEHeaderGenerator class
    typedef efd::SmartPointer< IDDEHeaderGenerator > IDDEHeaderGeneratorPtr;

} // end namespace efd


#endif // EE_DDEHeaderGenerator_h
