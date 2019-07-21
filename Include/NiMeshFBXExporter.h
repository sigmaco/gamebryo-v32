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

#ifndef NIMESHFBXEXPORTER_H
#define NIMESHFBXEXPORTER_H

#include "NiFBXConverterLibType.h"
#include <NiMeshLib.h>
#include <NiAnimation.h>
#pragma warning(disable:4996)
#include <fbxsdk.h>

/**
    Internal use only class for FBX export.
*/
class NIFBXCONVERTER_ENTRY NiMeshFBXExporter : public NiRefObject
{
public:
    NiMeshFBXExporter(
        KFbxSdkManager* pkSdkManager, 
        NiString kTexturePath);
    ~NiMeshFBXExporter();

    KFbxMesh* ConvertMesh(NiMesh* pkMesh, NiString kName);

    KFbxSurfacePhong* ConvertMaterial(KFbxMesh* pMesh, NiMesh* pkMesh, NiString kName);

    static int GetUVSetIndex(NiMesh* pkMesh, unsigned int uiMap);

protected:
    KFbxSdkManager* m_pkSdkManager;
};


#endif // #ifndef NIMESHFBXEXPORTER_H
