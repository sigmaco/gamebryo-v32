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
#ifndef EE_REMOVE_BACK_COMPAT_STREAMING
#ifndef NIGEOMMORPHERCONVERTER_H
#define NIGEOMMORPHERCONVERTER_H

#include <NiRenderObject.h>
#include <NiAnimation.h>

class NIANIMATION_ENTRY NiGeomMorpherConverter
{
public:
    static void Convert(NiStream& kStream,
        NiTLargeObjectArray<NiObjectPtr>& kTopObjects);

    static void RecurseScene(NiObject* pkObject);
    static void ConvertGeomMorpherController(NiGeomMorpherController* pkMorph,
        NiMesh* pkMesh);
protected:
    static bool m_bAttachModifiers;
};

#endif // #ifndef NIGEOMMORPHERCONVERTER_H
#endif // #ifndef EE_REMOVE_BACK_COMPAT_STREAMING
