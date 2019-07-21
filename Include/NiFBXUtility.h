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

#ifndef NIFBXUTILITY_H
#define NIFBXUTILITY_H

#include "NiFBXConverterLibType.h"
#include <NiAVObject.h>
#include <fbxsdk.h>

/**
    Internal use only class for FBX export.
*/
class NIFBXCONVERTER_ENTRY NiFBXUtility
{
public:

    static void ConvertTransform(NiAVObject* pkObject, KFbxNode* pkTarget);
    static KFbxVector4 ConvertNiPoint(const NiPoint3& k);
    static KFbxVector2 ConvertNiPoint(const NiPoint2& k);
    static KFbxColor ConvertNiColor(const NiColor& k);
    static fbxDouble3 ConvertNiColorToDouble3(const NiColor& k);
};

#include "NiFBXUtility.inl"

#endif // NIFBXUTILITY_H