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

#ifndef NISKYMATERIALPIXELDESCRIPTOR_H
#define NISKYMATERIALPIXELDESCRIPTOR_H

#include <NiGPUProgramDescriptor.h>
#include <NiBitfield.h>
#include <NiString.h>

#include "NiEnvironmentLibType.h"

class NiSkyMaterialDescriptor;

/** 
    This class encapsulates a bit field used to describe a pixel shader for
    NiSkyMaterial. The pixel material descriptor provides a way of easily
    describing all the information needed to produce a pixel shader that
    matches the requirements of a provided NiSky object.
*/
class NIENVIRONMENT_ENTRY NiSkyMaterialPixelDescriptor : 
    public NiGPUProgramDescriptor
{

public:

    /**
        Returns a string representation of the state of the bitfield.
    */
    NiString ToString();

    /**
        Returns true if the vertex shader needs to output the normals of the verts.
    */
    bool InputNormals();

    /**
        Returns true if the vertex shader needs to output the world view vector.
    */
    bool InputWorldView();

    /**
        Returns the configuration for a specific blend stage.
    */
    void GetStageConfiguration(NiUInt32 uiStageIndex, NiUInt32& kColorMap, 
        NiUInt32& kModifierSource, NiUInt32& kBlendMethod);

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
    NiDeclareDefaultIndexedBitfieldEntry(STAGE4_COLORMAP_SELECTION, 3, 
        BITFIELDSTART, 1)
    NiDeclareDefaultIndexedBitfieldEntry(STAGE4_BLENDMODE_SELECTION, 2, 
        STAGE4_COLORMAP_SELECTION, 1)
    NiDeclareDefaultIndexedBitfieldEntry(STAGE4_MODIFIER_SELECTION, 3, 
        STAGE4_BLENDMODE_SELECTION, 1)

    NiDeclareDefaultIndexedBitfieldEntry(ATMOSPHERE_CALC_MODE, 2, 
        STAGE4_MODIFIER_SELECTION, 1);

    NiEndDefaultBitfieldEnum();
    //@}
    /// @endcond
};

#endif
