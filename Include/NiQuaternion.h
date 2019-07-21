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
#ifndef NIQUATERNION_H
#define NIQUATERNION_H

#include <efd/Quaternion.h>
#include "NiMatrix3.h"

class NiPoint3;


class NIMAIN_ENTRY NiQuaternion : public efd::Quaternion
{
public:
    inline NiQuaternion() : efd::Quaternion() {};

    /// Constructs a quaternion from the specified values.
    inline NiQuaternion(float w, float x, float y, float z) : efd::Quaternion(w, x, y, z) {};

    /// Copy constructor for conversion between const efd::Quaternion and NiQuaternion
    inline NiQuaternion(const efd::Quaternion& kSrc) : efd::Quaternion(kSrc) {}

    /**
        Constructs a unit quaternion that corresponds to the rotation about the
        specified axis. This rotation is counter clockwise about the axis when
        looking towards the origin.
        @param angle The angle in radians.
        @param axis The axis to rotate about.
    */
    inline NiQuaternion(float angle, const NiPoint3& axis) : efd::Quaternion(angle, axis) {};

    // streaming
#ifndef __SPU__
    void LoadBinary (NiStream& stream);
    void SaveBinary (NiStream& stream);

    // Utility methods for streaming arrays of NiPoint3's.
    // Note that the array's must be pre-allocated for Loading,
    // meaning that the external caller is responsible for
    // streaming the size.
    static void LoadBinary (
        NiStream& stream,
        NiQuaternion* pkValues,
        unsigned int uiNumValues);
    static void SaveBinary (
        NiStream& stream,
        NiQuaternion* pkValues,
        unsigned int uiNumValues);

    char* GetViewerString (const char* pPrefix) const;
#endif

};

//--------------------------------------------------------------------------------------------------
//  Inline include
#include "NiQuaternion.inl"

//--------------------------------------------------------------------------------------------------

#endif


