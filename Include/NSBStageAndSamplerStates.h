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
#ifndef NSBSTAGEANDSAMPLERSTATES_H
#define NSBSTAGEANDSAMPLERSTATES_H

#include "NSBShaderLibLibType.h"
#include <NiMemObject.h>

class NSBSHADERLIB_ENTRY NSBStageAndSamplerStates : public NiMemObject
{
public:
    NSBStageAndSamplerStates();
    ~NSBStageAndSamplerStates();

    // Texture stage state values
    enum NSBTextureStageState
    {
        NSB_TSS_COLOROP    = 0,
        NSB_TSS_COLORARG0,
        NSB_TSS_COLORARG1,
        NSB_TSS_COLORARG2,
        NSB_TSS_ALPHAOP,
        NSB_TSS_ALPHAARG0,
        NSB_TSS_ALPHAARG1,
        NSB_TSS_ALPHAARG2,
        NSB_TSS_RESULTARG,
        NSB_TSS_BUMPENVMAT00,
        NSB_TSS_BUMPENVMAT01,
        NSB_TSS_BUMPENVMAT10,
        NSB_TSS_BUMPENVMAT11,
        NSB_TSS_BUMPENVLSCALE,
        NSB_TSS_BUMPENVLOFFSET,
        NSB_TSS_TEXCOORDINDEX,
        NSB_TSS_TEXTURETRANSFORMFLAGS,
        //
        NSB_TSS_COUNT,
        NSB_TSS_INVALID    = 0x7fffffff
    };

    enum NSBTextureOp
    {
        NSB_TOP_DISABLE    = 0,
        NSB_TOP_SELECTARG1,
        NSB_TOP_SELECTARG2,
        NSB_TOP_MODULATE,
        NSB_TOP_MODULATE2X,
        NSB_TOP_MODULATE4X,
        NSB_TOP_ADD,
        NSB_TOP_ADDSIGNED,
        NSB_TOP_ADDSIGNED2X,
        NSB_TOP_SUBTRACT,
        NSB_TOP_ADDSMOOTH,
        NSB_TOP_BLENDDIFFUSEALPHA,
        NSB_TOP_BLENDTEXTUREALPHA,
        NSB_TOP_BLENDFACTORALPHA,
        NSB_TOP_BLENDTEXTUREALPHAPM,
        NSB_TOP_BLENDCURRENTALPHA,
        NSB_TOP_PREMODULATE,
        NSB_TOP_MODULATEALPHA_ADDCOLOR,
        NSB_TOP_MODULATECOLOR_ADDALPHA,
        NSB_TOP_MODULATEINVALPHA_ADDCOLOR,
        NSB_TOP_MODULATEINVCOLOR_ADDALPHA,
        NSB_TOP_BUMPENVMAP,
        NSB_TOP_BUMPENVMAPLUMINANCE,
        NSB_TOP_DOTPRODUCT3,
        NSB_TOP_MULTIPLYADD,
        NSB_TOP_LERP,
        //
        NSB_TOP_COUNT,
        NSB_TOP_INVALID    = 0x7fffffff
    };

    enum NSBTextureArg
    {
        NSB_TA_CURRENT         = 0,
        NSB_TA_DIFFUSE,
        NSB_TA_SELECTMASK,
        NSB_TA_SPECULAR,
        NSB_TA_TEMP,
        NSB_TA_TEXTURE,
        NSB_TA_TFACTOR,
        //
        NSB_TA_COUNT,
        // Modifier flags
        NSB_TA_ALPHAREPLICATE  = 0x40000000,
        NSB_TA_COMPLEMENT      = 0x80000000,
        NSB_TA_INVALID         = 0x7fffffff
    };

    enum NSBTextureTransformFlags
    {
        NSB_TTFF_DISABLE   = 0,
        NSB_TTFF_COUNT1,
        NSB_TTFF_COUNT2,
        NSB_TTFF_COUNT3,
        NSB_TTFF_COUNT4,
        NSB_TTFF_PROJECTED = 0x00000100,
        //
        NSB_TTFF_INVALID   = 0x7fffffff
    };

    enum NSBTexCoordIndexFlags
    {
        NSB_TSI_PASSTHRU                       = 0x00000000,
        NSB_TSI_CAMERASPACENORMAL              = 0x10000000,
        NSB_TSI_CAMERASPACEPOSITION            = 0x20000000,
        NSB_TSI_CAMERASPACEREFLECTIONVECTOR    = 0x30000000,
        NSB_TSI_SPHEREMAP                      = 0x40000000,
        //
        NSB_TSI_INVALID    = 0x7fffffff
    };

    // Texture sampler states
    enum NSBTextureSamplerState
    {
        NSB_SAMP_ADDRESSU      = 0,
        NSB_SAMP_ADDRESSV,
        NSB_SAMP_ADDRESSW,
        NSB_SAMP_BORDERCOLOR,
        NSB_SAMP_MAGFILTER,
        NSB_SAMP_MINFILTER,
        NSB_SAMP_MIPFILTER,
        NSB_SAMP_MIPMAPLODBIAS,
        NSB_SAMP_MAXMIPLEVEL,
        NSB_SAMP_MAXANISOTROPY,
        // DX9, Xenon
        NSB_SAMP_SRGBTEXTURE,
        // DX9
        NSB_SAMP_ELEMENTINDEX,
        NSB_SAMP_DMAPOFFSET,
        // D3D10
        NSB_SAMP_MINMIPLEVEL,
        NSB_SAMP_COMPARISONFUNC,
        //
        NSB_SAMP_COUNT,
        NSB_SAMP_DEPRECATED    = 0x7ffffffe,
        NSB_SAMP_INVALID       = 0x7fffffff
    };

    enum NSBTextureAddress
    {
        NSB_TADDRESS_WRAP      = 0,
        NSB_TADDRESS_MIRROR,
        NSB_TADDRESS_CLAMP,
        NSB_TADDRESS_BORDER,
        // DX9, D3D10
        NSB_TADDRESS_MIRRORONCE,
        //
        NSB_TADDRESS_COUNT,
        NSB_TADDRESS_INVALID   = 0x7fffffff
    };

    enum NSBTextureFilter
    {
        NSB_TEXF_NONE      = 0,
        NSB_TEXF_POINT,
        NSB_TEXF_LINEAR,
        NSB_TEXF_ANISOTROPIC,
        // DX9
        NSB_TEXF_PYRAMIDALQUAD,
        NSB_TEXF_GAUSSIANQUAD,
        //
        NSB_TEXF_COUNT,
        NSB_TEXF_INVALID   = 0x7fffffff
    };

    static NSBTextureStageState LookupTextureStageState(
        const char* pcTextureStageState);
    static unsigned int LookupTextureStageStateValue(
        NSBTextureStageState eStageState, const char* pcValue);

    static NSBTextureSamplerState LookupTextureSamplerState(
        const char* pcTextureSamplerState);
    static unsigned int LookupTextureSamplerStateValue(
        NSBTextureSamplerState eSamplerState, const char* pcValue);

#if defined(NIDEBUG)
    static const char* LookupTextureStageString(
        NSBTextureStageState eState);
    static const char* LookupTextureStageValueString(
        NSBTextureStageState eState, unsigned int uiValue);
    static const char* LookupTextureSamplerString(
        NSBTextureSamplerState eState);
    static const char* LookupTextureSamplerValueString(
        NSBTextureSamplerState eState, unsigned int uiValue);
#endif  //#if defined(NIDEBUG)
};

#endif  //NSBSTAGEANDSAMPLERSTATES_H
