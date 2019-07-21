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
#ifndef NIMATRIX3_H
#define NIMATRIX3_H

#include <efd/Matrix3.h>

#if !defined(_PS3) && !defined(_XENON)
#include <NiSystem.h>
#endif

#include "NiPoint3.h"

#if defined(_XENON) || defined (_PS3)
#include "NiPoint4.h"
#endif  //#if defined(_XENON)

#ifndef __SPU__
class NiStream;
#endif

class NiMatrix3 : public efd::Matrix3
{
public:
    // Declare NiTransform as a friend so that platform specific math routines
    // can get access to the internal vector representation of NiMatrix3.
    friend class NiTransform;
    friend class NiMatrix3x4;

    inline NiMatrix3();
    inline NiMatrix3(const NiPoint3& col0, const NiPoint3& col1, const NiPoint3& col2);
    inline NiMatrix3(const efd::Matrix3& kMatrix);

    // *** begin Emergent internal use only ***
#ifndef __SPU__
    // streaming
    void LoadBinary(NiStream& stream);
    void SaveBinary(NiStream& stream);
    char* GetViewerString(const char* pPrefix) const;
#endif
    // *** end Emergent internal use only ***
};

#include "NiMatrix3.inl"

#endif // NIMATRIX3_H
