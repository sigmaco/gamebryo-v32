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
#ifndef NITERRAINVERTEXDESCRIPTOR_H
#define NITERRAINVERTEXDESCRIPTOR_H

#include "NiTerrainLibType.h"
#include <NiGPUProgramDescriptor.h>
#include <NiBitfield.h>
#include <NiString.h>

/**
    This class manages the bit fields that are constructed from the terrain
    material descriptor.

    It is used when determining how to construct a shade tree in order to
    generate a vertex shader.
*/
class NITERRAIN_ENTRY NiTerrainMaterialVertexDescriptor :
    public NiGPUProgramDescriptor
{
public:

    /// Convert the bit field to a human readable string.
    ///
    /// This is useful when debugging the values in the bit field.
    NiString ToString();

    /// @cond EMERGENT_INTERNAL
    NiBeginDefaultBitfieldEnum()

    // First byte, index 0 (1 bit left)
    NiDeclareDefaultIndexedBitfieldEntry(FOGTYPE, 2, BITFIELDSTART, 0)
    NiDeclareDefaultIndexedBitfieldEntry(SPECULAR, 1, FOGTYPE, 0)
    NiDeclareDefaultIndexedBitfieldEntry(VERTEXCOLORS, 1, SPECULAR, 0)
    NiDeclareDefaultIndexedBitfieldEntry(AMBDIFFEMISSIVE, 2, VERTEXCOLORS, 0)
    NiDeclareDefaultIndexedBitfieldEntry(APPLYMODE, 1, AMBDIFFEMISSIVE, 0)

    // Second byte, index 0 (1 bit left)
    NiDeclareDefaultIndexedBitfieldEntry(LIGHTINGMODE, 2, APPLYMODE, 0)
    NiDeclareDefaultIndexedBitfieldEntry(DIRLIGHTCOUNT, 4, LIGHTINGMODE, 0)
    NiDeclareDefaultIndexedBitfieldEntry(VERTEXLIGHTSONLY, 1, DIRLIGHTCOUNT, 0)

    // Third byte, index 0
    NiDeclareDefaultIndexedBitfieldEntry(POINTLIGHTCOUNT, 4, VERTEXLIGHTSONLY, 0)
    NiDeclareDefaultIndexedBitfieldEntry(SPOTLIGHTCOUNT, 4, POINTLIGHTCOUNT, 0)

    // Fourth byte, index 0
    NiDeclareDefaultIndexedBitfieldEntry(RENDER_MODE, 4, SPOTLIGHTCOUNT, 0)
    NiDeclareDefaultLastIndexedBitfieldEntry(NUM_LAYERS, 4, RENDER_MODE, 0);
    
    // First byte, index 1
    NiDeclareDefaultIndexedBitfieldEntry(MORPH_MODE, 2, BITFIELDSTART, 1);
    NiDeclareDefaultIndexedBitfieldEntry(INPUT_MORPHING, 1, MORPH_MODE, 1);
    NiDeclareDefaultIndexedBitfieldEntry(INPUT_LIGHTING_COMPRESSED, 1, INPUT_MORPHING, 1);
    NiDeclareDefaultIndexedBitfieldEntry(INPUT_NORMALS, 1, INPUT_LIGHTING_COMPRESSED, 1)
    NiDeclareDefaultIndexedBitfieldEntry(INPUT_TANGENTS, 1, INPUT_NORMALS, 1)
    NiDeclareDefaultIndexedBitfieldEntry(OUTPUT_WORLDNBT, 1, INPUT_TANGENTS, 1)
    NiDeclareDefaultIndexedBitfieldEntry(OUTPUT_WORLDVIEW, 1, OUTPUT_WORLDNBT, 1);

    // Second byte, index 1 (7 bits left)
    NiDeclareDefaultIndexedBitfieldEntry(OUTPUT_WORLDPOSITION, 1, OUTPUT_WORLDVIEW, 1)
    NiDeclareDefaultIndexedBitfieldEntry(OUTPUT_WORLDNORMAL, 1, OUTPUT_WORLDPOSITION, 1)
    
    NiEndDefaultBitfieldEnum()
    /// @endcond
};

#endif
