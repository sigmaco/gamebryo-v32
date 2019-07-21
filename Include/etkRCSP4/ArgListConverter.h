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
// Emergent Game Technologies, Chapel Hill, North Carolina 27517
// http://www.emergent.net

#pragma once
#ifndef EE_ARGLISTCONVERTER_H
#define EE_ARGLISTCONVERTER_H

namespace etk
{
    class ArgListConverter
    {
    public:
        ArgListConverter(const efd::list<efd::utf8string>& args, const char* pChangelistID);
        ~ArgListConverter();

        const char** GetArgv() const;
        efd::UInt32  GetSize() const;

    protected:   
        const char** m_ppArgv;
        efd::UInt32 m_size;
    };
} // namespace etk

#endif // EE_ARGLISTCONVERTER_H