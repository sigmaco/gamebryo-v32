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

#ifndef NIFBXEXPORTER_H
#define NIFBXEXPORTER_H

#include "NiFBXConverterLibType.h"
#include <NiMeshLib.h>

#pragma warning(disable:4996)
#include <fbxsdk.h>

/**
    Internal use only class for FBX export.
*/
class NIFBXCONVERTER_ENTRY NiFBXExporter :
    public NiRefObject
{
public:
    NiFBXExporter();
    ~NiFBXExporter();

    bool IsValid() const;

    void AddSceneGraph(NiAVObject* pkObj, NiString kName);

    bool SaveScene(const char* pFilename, int pFileFormat  = -1, bool pEmbedMedia  = false);


protected:
    KFbxSdkManager* m_pkSdkManager;
    KFbxScene* m_pkFbxScene;
    KFbxNode* m_pkActiveEntityObjectNode;

    NiString m_kActiveName;
    NiUInt32 m_uiNodeId;

    NiString CreateName(const NiString& kName);

    bool ConvertSceneGraph(NiAVObject* pkObj, KFbxNode* pkFbxParentNode);

    void AddFbxPropertyDouble(KFbxObject *object, const NiString& propertyName, 
        double value);

    void AddFbxPropertyInt(KFbxObject *object, const NiString& propertyName, 
        int value);

    void AddFbxPropertyBool(KFbxObject *object, const NiString& propertyName, 
        bool value);
};


#endif // #ifndef NIFBXEXPORTER_H
