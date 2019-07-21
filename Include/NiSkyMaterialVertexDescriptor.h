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

#ifndef NISKYMATERIALVERTEXDESCRIPTOR_H
#define NISKYMATERIALVERTEXDESCRIPTOR_H

#include <NiGPUProgramDescriptor.h>
#include <NiBitfield.h>
#include <NiString.h>

#include "NiEnvironmentLibType.h"

/** 
    This class encapuslates a bit field used to describe a vertex shader for
    NiSkyMaterial. The vertex material descriptor provides a way of easily
    describing all the information needed to produce a vertex shader that
    matches the requirements of a provided NiSky object. 
*/
class NIENVIRONMENT_ENTRY NiSkyMaterialVertexDescriptor :
    public NiGPUProgramDescriptor
{

public:

    /// Returns a string representation of the state of the bitfield.
    NiString ToString();

    /// Returns true if the vertex shader needs to output the normals of the verts
    bool OutputNormals();

    /// Returns true if the vertex shader needs to output the world view vector
    bool OutputWorldView();


    /// @cond EMERGENT_INTERNAL
    //@{
    NiBeginDefaultBitfieldEnum()

    // first byte index 0;
    NiDeclareDefaultIndexedBitfieldEntry(ATMOSPHERE_CALC_MODE, 2, BITFIELDSTART, 0)
    NiDeclareDefaultIndexedBitfieldEntry(USES_NORMALS, 1, ATMOSPHERE_CALC_MODE, 0)

    NiEndDefaultBitfieldEnum();
    //@}
    /// @endcond
};

#endif
