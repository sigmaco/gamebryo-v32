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


//--------------------------------------------------------------------------------------------------
inline void ILogDestination::IndexedFileName(utf8string& fileName)
{
    // Pull the filename apart
    efd::utf8string name;
    efd::utf8string type;

    efd::utf8string::size_type pos = fileName.rfind('.');
    name = fileName.substr(0, pos);
    type = fileName.substr(pos + 1);

    // Create a new filename
    efd::UInt32 index = m_uniqueIndex.GetIndex(); 
    fileName.sprintf("%s_%i.%s", name.c_str(), index, type.c_str());
}

