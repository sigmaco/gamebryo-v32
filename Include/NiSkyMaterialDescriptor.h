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

#ifndef NISKYMATERIALDESCRIPTOR_H
#define NISKYMATERIALDESCRIPTOR_H

#include <NiMaterialDescriptor.h>
#include <NiBitfield.h>

#include "NiEnvironmentLibType.h"

/**
     This class encapuslates a bit field used to describe a NiSkyMaterial 
     shader. The NiSkyMaterial generates shaders based on a user configuration
     of a NiSky object, this allows generic skys to be quickly added to a 
     scene. The NiSkyMaterialDescriptor provides an easy way of describing 
     all the information that is needed to generate a shader.
 */
class NIENVIRONMENT_ENTRY NiSkyMaterialDescriptor : public NiMaterialDescriptor
{
public:

    /**
        Default constructor.
    */
    NiSkyMaterialDescriptor();

    /// @cond EMERGENT_INTERNAL
    //@{
    NiBeginDefaultBitfieldEnum()

    // Begin index 0;        
    NiDeclareDefaultIndexedBitfieldEntry(STAGE0_COLORMAP_SELECTION, 3, 
        BITFIELDSTART, 0)
    NiDeclareDefaultIndexedBitfieldEntry(STAGE0_BLENDMODE_SELECTION, 2,
        STAGE0_COLORMAP_SELECTION, 0)
    NiDeclareDefaultIndexedBitfieldEntry(STAGE0_MODIFIER_SELECTION, 3, 
        STAGE0_BLENDMODE_SELECTION, 0)
    NiDeclareDefaultIndexedBitfieldEntry(STAGE1_COLORMAP_SELECTION, 3, 
        STAGE0_MODIFIER_SELECTION, 0)
    NiDeclareDefaultIndexedBitfieldEntry(STAGE1_BLENDMODE_SELECTION, 2, 
        STAGE1_COLORMAP_SELECTION, 0)
    NiDeclareDefaultIndexedBitfieldEntry(STAGE1_MODIFIER_SELECTION, 3, 
        STAGE1_BLENDMODE_SELECTION, 0)
    NiDeclareDefaultIndexedBitfieldEntry(STAGE2_COLORMAP_SELECTION, 3, 
        STAGE1_MODIFIER_SELECTION, 0)
    NiDeclareDefaultIndexedBitfieldEntry(STAGE2_BLENDMODE_SELECTION, 2, 
        STAGE2_COLORMAP_SELECTION, 0)
    NiDeclareDefaultIndexedBitfieldEntry(STAGE2_MODIFIER_SELECTION, 3, 
        STAGE2_BLENDMODE_SELECTION, 0)
    NiDeclareDefaultIndexedBitfieldEntry(STAGE3_COLORMAP_SELECTION, 3, 
        STAGE2_MODIFIER_SELECTION, 0)
    NiDeclareDefaultIndexedBitfieldEntry(STAGE3_BLENDMODE_SELECTION, 2, 
        STAGE3_COLORMAP_SELECTION, 0)
    NiDeclareDefaultLastIndexedBitfieldEntry(STAGE3_MODIFIER_SELECTION, 3, 
        STAGE3_BLENDMODE_SELECTION, 0)

    // Begin index 1
    NiDeclareDefaultIndexedBitfieldEntry(STAGE4_COLORMAP_SELECTION, 2, 
        BITFIELDSTART, 1)
    NiDeclareDefaultIndexedBitfieldEntry(STAGE4_BLENDMODE_SELECTION, 2, 
        STAGE4_COLORMAP_SELECTION, 1)
    NiDeclareDefaultIndexedBitfieldEntry(STAGE4_MODIFIER_SELECTION, 3, 
        STAGE4_BLENDMODE_SELECTION, 1)

    NiDeclareDefaultIndexedBitfieldEntry(ATMOSPHERE_CALC_MODE, 2, 
        STAGE4_MODIFIER_SELECTION, 1)

    // 6 bits + 2 bytes free in index 1

    // Total Free: 6 bits + 2 bytes + 2 indices left.

    NiEndDefaultBitfieldEnum();

    //@}
    /// @endcond
};

#endif
