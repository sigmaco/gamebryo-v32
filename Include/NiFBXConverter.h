// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not 
// be copied or disclosed except in accordance with the terms of that 
// agreement.
//
//      Copyright (c) 1996-2008 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Chapel Hill, North Carolina 27517
// http://www.emergent.net

#ifndef NIFBXCONVERTER_H
#define NIFBXCONVERTER_H

#include "NiFBXConverterLibType.h"
#include <NiMain.h>

/**
    This class is responsible for converting a list of scene graphs into a single 
    FBX file. Applications wishing to export to FBX should directly reference this header file. 
    All FBX export details have been encapsulated inside other classes within this library and
    are not meant for external use.

    FBX export is currently limited to the following capabilities:
    + Node transforms
    + Node visibility
    + Diffuse material color
    + Triangle-based meshes with positions and normals
*/
class NIFBXCONVERTER_ENTRY NiFBXConverter
{
public:

    /**
        This method is responsible for converting a list of scene graphs into a single 
        FBX file. 

        @param pcFilename The target filename for the FBX export
        @param kScenes The set of scene graphs to export. Each scene graph will be exported 
            as a child of the FBX root scene.
        @param kNames The names to use for the FBX nodes that correspond to the items in the
            scene array.
        @return Whether or not the export was successful.
    */
    static bool ExportToFBX(const char* pcFilename, NiTPrimitiveArray<NiAVObject*>& kScenes,
        NiTObjectArray<NiString>& kNames);
};

#endif