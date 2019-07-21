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
#ifndef NSBRENDERSTATES_H
#define NSBRENDERSTATES_H

#include "NSBShaderLibLibType.h"
#include <NiMemObject.h>

class NSBSHADERLIB_ENTRY NSBRenderStates : public NiMemObject
{
public:
    enum NSBRenderStateEnum
    {
        // NOTE: This enum is used in the streaming code, and deprecated
        // enumerants must be left in place to maintain ordering.

        // NOTE: This enum is duplicated across all platforms, and changes
        // in one should be reflected in the others.

        // Render states supported under these platforms:
        // 9 = DX9, x = Xenon, p = PS3, 0 = D3D10, 1 = D3D11
        NSB_RS_ZENABLE = 0,                     // 9xp01
        NSB_RS_FILLMODE,                        // 9xp01
        NSB_RS_SHADEMODE,                       // 9
        NSB_RS_ZWRITEENABLE,                    // 9xp01
        NSB_RS_ALPHATESTENABLE,                 // 9xp
        NSB_RS_LASTPIXEL,                       // 9
        NSB_RS_SRCBLEND,                        // 9xp01
        NSB_RS_DESTBLEND,                       // 9xp01
        NSB_RS_CULLMODE,                        // 9x 01
        NSB_RS_ZFUNC,                           // 9xp01
        NSB_RS_ALPHAREF,                        // 9xp
        NSB_RS_ALPHAFUNC,                       // 9xp
        NSB_RS_DITHERENABLE,                    // 9xp
        NSB_RS_ALPHABLENDENABLE,                // 9xp01
        NSB_RS_FOGENABLE,                       // 9
        NSB_RS_SPECULARENABLE,                  // 9
        NSB_RS_FOGCOLOR,                        // 9
        NSB_RS_FOGTABLEMODE,                    // 9
        NSB_RS_FOGSTART,                        // 9
        NSB_RS_FOGEND,                          // 9
        NSB_RS_FOGDENSITY,                      // 9
        NSB_RS_RANGEFOGENABLE,                  // 9
        NSB_RS_STENCILENABLE,                   // 9xp01
        NSB_RS_STENCILFAIL,                     // 9xp01
        NSB_RS_STENCILZFAIL,                    // 9xp01
        NSB_RS_STENCILPASS,                     // 9xp01
        NSB_RS_STENCILFUNC,                     // 9xp01
        NSB_RS_STENCILREF,                      // 9xp01
        NSB_RS_STENCILMASK,                     // 9xp01
        NSB_RS_STENCILWRITEMASK,                // 9xp01
        NSB_RS_TEXTUREFACTOR,                   // 9
        NSB_RS_WRAP0,                           // 9x
        NSB_RS_WRAP1,                           // 9x
        NSB_RS_WRAP2,                           // 9x
        NSB_RS_WRAP3,                           // 9x
        NSB_RS_WRAP4,                           // 9x
        NSB_RS_WRAP5,                           // 9x
        NSB_RS_WRAP6,                           // 9x
        NSB_RS_WRAP7,                           // 9x
        NSB_RS_CLIPPING,                        // 9
        NSB_RS_LIGHTING,                        // 9
        NSB_RS_AMBIENT,                         // 9
        NSB_RS_FOGVERTEXMODE,                   // 9
        NSB_RS_COLORVERTEX,                     // 9
        NSB_RS_LOCALVIEWER,                     // 9
        NSB_RS_NORMALIZENORMALS,                // 9
        NSB_RS_DIFFUSEMATERIALSOURCE ,          // 9
        NSB_RS_SPECULARMATERIALSOURCE,          // 9
        NSB_RS_AMBIENTMATERIALSOURCE,           // 9
        NSB_RS_EMISSIVEMATERIALSOURCE,          // 9
        NSB_RS_VERTEXBLEND,                     // 9
        NSB_RS_CLIPPLANEENABLE,                 // 9x 01
        NSB_RS_POINTSIZE,                       // 9xp
        NSB_RS_POINTSIZE_MIN,                   // 9x
        NSB_RS_POINTSPRITEENABLE,               // 9xp
        NSB_RS_POINTSCALEENABLE,                // 9
        NSB_RS_POINTSCALE_A,                    // 9
        NSB_RS_POINTSCALE_B,                    // 9
        NSB_RS_POINTSCALE_C,                    // 9
        NSB_RS_MULTISAMPLEANTIALIAS,            // 9xp01
        NSB_RS_MULTISAMPLEMASK,                 // 9xp01
        NSB_RS_PATCHEDGESTYLE,                  // 9x
        NSB_RS_DEBUGMONITORTOKEN,               // 9
        NSB_RS_POINTSIZE_MAX,                   // 9x
        NSB_RS_INDEXEDVERTEXBLENDENABLE,        // 9
        NSB_RS_COLORWRITEENABLE,                // 9x 01
        NSB_RS_TWEENFACTOR,                     // 9
        NSB_RS_BLENDOP,                         // 9xp01
        NSB_RS_POSITIONDEGREE,                  // 9x
        NSB_RS_NORMALDEGREE,                    // 9x
        NSB_RS_SCISSORTESTENABLE,               // 9xp01
        NSB_RS_SLOPESCALEDEPTHBIAS,             // 9x 01
        NSB_RS_ANTIALIASEDLINEENABLE,           // 9xp01
        NSB_RS_MINTESSELLATIONLEVEL,            // 9x
        NSB_RS_MAXTESSELLATIONLEVEL,            // 9x
        NSB_RS_ADAPTIVETESS_X,                  // 9x
        NSB_RS_ADAPTIVETESS_Y,                  // 9x
        NSB_RS_ADAPTIVETESS_Z,                  // 9x
        NSB_RS_ADAPTIVETESS_W,                  // 9x
        NSB_RS_ENABLEADAPTIVETESSELLATION,      // 9x
        NSB_RS_TWOSIDEDSTENCILMODE,             // 9xp
        NSB_RS_CCW_STENCILFAIL,                 // 9xp01
        NSB_RS_CCW_STENCILZFAIL,                // 9xp01
        NSB_RS_CCW_STENCILPASS,                 // 9xp01
        NSB_RS_CCW_STENCILFUNC,                 // 9xp01
        NSB_RS_COLORWRITEENABLE1,               // 9x 01
        NSB_RS_COLORWRITEENABLE2,               // 9x 01
        NSB_RS_COLORWRITEENABLE3,               // 9x 01
        NSB_RS_BLENDFACTOR,                     // 9x 01
        NSB_RS_SRGBWRITEENABLE,                 // 9xp
        NSB_RS_DEPTHBIAS,                       // 9x 01
        NSB_RS_WRAP8,                           // 9x
        NSB_RS_WRAP9,                           // 9x
        NSB_RS_WRAP10,                          // 9x
        NSB_RS_WRAP11,                          // 9x
        NSB_RS_WRAP12,                          // 9x
        NSB_RS_WRAP13,                          // 9x
        NSB_RS_WRAP14,                          // 9x
        NSB_RS_WRAP15,                          // 9x
        NSB_RS_SEPARATEALPHABLENDENABLE,        // 9xp
        NSB_RS_SRCBLENDALPHA,                   // 9xp01
        NSB_RS_DESTBLENDALPHA,                  // 9xp01
        NSB_RS_BLENDOPALPHA,                    // 9xp01
        NSB_RS_VIEWPORTENABLE,                  //  x
        NSB_RS_HIGHPRECISIONBLENDENABLE,        //  x
        NSB_RS_HIGHPRECISIONBLENDENABLE1,       //  x
        NSB_RS_HIGHPRECISIONBLENDENABLE2,       //  x
        NSB_RS_HIGHPRECISIONBLENDENABLE3,       //  x
        NSB_RS_TESSELLATIONMODE,                //  x

        // Begin PS3-only states
        NSB_RS_COLORLOGICOPENABLE,              //       (deprecated)
        NSB_RS_CULLFACEENABLE,                  //   p
        NSB_RS_MULTISAMPLEENABLE,               //   p
        NSB_RS_POINTSMOOTHENABLE,               //       (deprecated)
        NSB_RS_POLYGONOFFSETFILLENABLE,         //   p
        // End PS3-only states

        // PS3 and D3D10/11 states
        NSB_RS_SAMPLEALPHATOCOVERAGEENABLE,     //   p01

        // Begin PS3-only states
        NSB_RS_SAMPLEALPHATOONEENABLE,          //   p
        NSB_RS_SAMPLECOVERAGEENABLE,            //       (deprecated)
        NSB_RS_VERTEXPROGRAMPOINTSIZEENABLE,    //       (deprecated)
        NSB_RS_BLENDCOLORR,                     //   p
        NSB_RS_BLENDCOLORG,                     //   p
        NSB_RS_BLENDCOLORB,                     //   p
        NSB_RS_BLENDCOLORA,                     //   p
        NSB_RS_SRCBLENDSEPARATERGB,             //       (deprecated)
        NSB_RS_DSTBLENDSEPARATERGB,             //       (deprecated)
        NSB_RS_BLENDEQUATIONSEPARATERGB,        //       (deprecated)
        NSB_RS_CULLFACE,                        //   p
        NSB_RS_COLORMASKR,                      //   p
        NSB_RS_COLORMASKG,                      //   p
        NSB_RS_COLORMASKB,                      //   p
        NSB_RS_COLORMASKA,                      //   p
        NSB_RS_DEPTHRANGENEAR,                  //   p
        NSB_RS_DEPTHRANGEFAR,                   //   p
        NSB_RS_FRONTFACE,                       //   p
        NSB_RS_LINEWIDTH,                       //   p
        NSB_RS_POINTSPRITECOORDREPLACE,         //       (deprecated)
        NSB_RS_POLYGONMODEFACE,                 //       (deprecated)
        NSB_RS_POLYGONOFFSETFACTOR,             //   p
        NSB_RS_POLYGONOFFSETUNITS,              //   p
        NSB_RS_SCISSORX,                        //   p
        NSB_RS_SCISSORY,                        //   p
        NSB_RS_SCISSORWIDTH,                    //   p
        NSB_RS_SCISSORHEIGHT,                   //   p
        // End PS3-only states

        // Begin D3D10/11-only states.
        NSB_RS_ALPHABLENDENABLE1,               //    01
        NSB_RS_ALPHABLENDENABLE2,               //    01
        NSB_RS_ALPHABLENDENABLE3,               //    01
        NSB_RS_ALPHABLENDENABLE4,               //    01
        NSB_RS_ALPHABLENDENABLE5,               //    01
        NSB_RS_ALPHABLENDENABLE6,               //    01
        NSB_RS_ALPHABLENDENABLE7,               //    01
        NSB_RS_COLORWRITEENABLE4,               //    01
        NSB_RS_COLORWRITEENABLE5,               //    01
        NSB_RS_COLORWRITEENABLE6,               //    01
        NSB_RS_COLORWRITEENABLE7,               //    01
        NSB_RS_FRONTCCW,                        //    01
        NSB_RS_DEPTHBIASCLAMP,                  //    01
        // End D3D10/11-only states.

        // Begin D3D11-only states.
        NSB_RS_INDEPENDENTBLENDENABLE,          //     1
        NSB_RS_SRCBLEND1,                       //     1
        NSB_RS_SRCBLEND2,                       //     1
        NSB_RS_SRCBLEND3,                       //     1
        NSB_RS_SRCBLEND4,                       //     1
        NSB_RS_SRCBLEND5,                       //     1
        NSB_RS_SRCBLEND6,                       //     1
        NSB_RS_SRCBLEND7,                       //     1
        NSB_RS_DESTBLEND1,                      //     1
        NSB_RS_DESTBLEND2,                      //     1
        NSB_RS_DESTBLEND3,                      //     1
        NSB_RS_DESTBLEND4,                      //     1
        NSB_RS_DESTBLEND5,                      //     1
        NSB_RS_DESTBLEND6,                      //     1
        NSB_RS_DESTBLEND7,                      //     1
        NSB_RS_BLENDOP1,                        //     1
        NSB_RS_BLENDOP2,                        //     1
        NSB_RS_BLENDOP3,                        //     1
        NSB_RS_BLENDOP4,                        //     1
        NSB_RS_BLENDOP5,                        //     1
        NSB_RS_BLENDOP6,                        //     1
        NSB_RS_BLENDOP7,                        //     1
        NSB_RS_SRCBLENDALPHA1,                  //     1
        NSB_RS_SRCBLENDALPHA2,                  //     1
        NSB_RS_SRCBLENDALPHA3,                  //     1
        NSB_RS_SRCBLENDALPHA4,                  //     1
        NSB_RS_SRCBLENDALPHA5,                  //     1
        NSB_RS_SRCBLENDALPHA6,                  //     1
        NSB_RS_SRCBLENDALPHA7,                  //     1
        NSB_RS_DESTBLENDALPHA1,                 //     1
        NSB_RS_DESTBLENDALPHA2,                 //     1
        NSB_RS_DESTBLENDALPHA3,                 //     1
        NSB_RS_DESTBLENDALPHA4,                 //     1
        NSB_RS_DESTBLENDALPHA5,                 //     1
        NSB_RS_DESTBLENDALPHA6,                 //     1
        NSB_RS_DESTBLENDALPHA7,                 //     1
        NSB_RS_BLENDOPALPHA1,                   //     1
        NSB_RS_BLENDOPALPHA2,                   //     1
        NSB_RS_BLENDOPALPHA3,                   //     1
        NSB_RS_BLENDOPALPHA4,                   //     1
        NSB_RS_BLENDOPALPHA5,                   //     1
        NSB_RS_BLENDOPALPHA6,                   //     1
        NSB_RS_BLENDOPALPHA7,                   //     1
        // End D3D11-only states.
        //
        NSB_RS_COUNT,
        NSB_RS_DEPRECATED = 0x7ffffffe,
        NSB_RS_INVALID    = 0x7fffffff
    };

    enum NSBZBufferType
    {
        NSB_ZB_FALSE   = 0,
        NSB_ZB_TRUE,
        NSB_ZB_USEW,
        //
        NSB_ZB_COUNT,
        NSB_ZB_INVALID = 0x7fffffff
    };

    enum NSBFillMode
    {
        NSB_FILL_POINT     = 0,
        NSB_FILL_WIREFRAME,
        NSB_FILL_SOLID,
        //
        NSB_FILL_COUNT,
        NSB_FILL_INVALID   = 0x7fffffff
    };

    enum NSBShadeMode
    {
        NSB_SHADE_FLAT     = 0,
        NSB_SHADE_GOURAUD,
        NSB_SHADE_PHONG,
        //
        NSB_SHADE_COUNT,
        NSB_SHADE_INVALID  = 0x7fffffff
    };

    enum NSBBlend
    {
        NSB_BLEND_ZERO     =  0,
        NSB_BLEND_ONE,
        NSB_BLEND_SRCCOLOR,
        NSB_BLEND_INVSRCCOLOR,
        NSB_BLEND_SRCALPHA,
        NSB_BLEND_INVSRCALPHA,
        NSB_BLEND_DESTALPHA,
        NSB_BLEND_INVDESTALPHA,
        NSB_BLEND_DESTCOLOR,
        NSB_BLEND_INVDESTCOLOR,
        NSB_BLEND_SRCALPHASAT,
        // DX9
        NSB_BLEND_BOTHSRCALPHA,
        NSB_BLEND_BOTHINVSRCALPHA,
        // DX9, Xenon, PS3, D3D10, D3D11
        NSB_BLEND_BLENDFACTOR,
        NSB_BLEND_INVBLENDFACTOR,
        // Xenon, PS3
        NSB_BLEND_CONSTANTALPHA,
        NSB_BLEND_INVCONSTANTALPHA,
        // D3D10, D3D11
        NSB_BLEND_SRC1_COLOR,
        NSB_BLEND_INV_SRC1_COLOR,
        NSB_BLEND_SRC1_ALPHA,
        NSB_BLEND_INV_SRC1_ALPHA,
        //
        NSB_BLEND_COUNT,
        NSB_BLEND_INVALID  = 0x7fffffff
    };

    enum NSBCull
    {
        NSB_CULL_NONE      = 0,
        NSB_CULL_CW,
        NSB_CULL_CCW,
        //
        NSB_CULL_COUNT,
        NSB_CULL_INVALID   = 0x7fffffff
    };

    enum NSBCmpFunc
    {
        NSB_CMP_NEVER    = 0,
        NSB_CMP_LESS,
        NSB_CMP_EQUAL,
        NSB_CMP_LESSEQUAL,
        NSB_CMP_GREATER,
        NSB_CMP_NOTEQUAL,
        NSB_CMP_GREATEREQUAL,
        NSB_CMP_ALWAYS,
        //
        NSB_CMP_COUNT,
        NSB_CMP_INVALID  = 0x7fffffff
    };

    enum NSBFogMode
    {
        // DX9
        NSB_FOG_NONE     = 0,
        NSB_FOG_EXP,
        NSB_FOG_EXP2,
        NSB_FOG_LINEAR,
        //
        NSB_FOG_COUNT,
        NSB_FOG_INVALID  = 0x7fffffff
    };

    enum NSBStencilOp
    {
        NSB_STENCTIL_OP_KEEP     = 0,
        NSB_STENCTIL_OP_ZERO,
        NSB_STENCTIL_OP_REPLACE,
        NSB_STENCTIL_OP_INCRSAT,
        NSB_STENCTIL_OP_DECRSAT,
        NSB_STENCTIL_OP_INVERT,
        NSB_STENCTIL_OP_INCR,
        NSB_STENCTIL_OP_DECR,
        //
        NSB_STENCTIL_OP_COUNT,
        NSB_STENCTIL_OP_INVALID  = 0x7fffffff
    };

    enum NSBWrap
    {
        NSB_WRAP_DISABLED  = 0,
        NSB_WRAP_U,
        NSB_WRAP_V,
        NSB_WRAP_W,
        NSB_WRAP_UV,
        NSB_WRAP_UW,
        NSB_WRAP_VW,
        NSB_WRAP_UVW,
        //
        NSB_WRAP_COUNT,
        NSB_WRAP_INVALID   = 0x7fffffff
    };

    enum NSBMaterialColorSource
    {
        NSB_MCS_MATERIAL   = 0,
        NSB_MCS_COLOR1,
        NSB_MCS_COLOR2,
        //
        NSB_MCS_COUNT,
        NSB_MCS_INVALID    = 0x7fffffff
    };

    enum NSBVertexBlendFlags
    {
        // DX9
        NSB_VBF_DISABLE    = 0,
        NSB_VBF_1WEIGHTS,
        NSB_VBF_2WEIGHTS,
        NSB_VBF_3WEIGHTS,
        NSB_VBF_TWEENING,
        NSB_VBF_0WEIGHTS,
        //
        NSB_VBF_COUNT,
        NSB_VBF_DEPRECATED = 0x7ffffffe,
        NSB_VBF_INVALID    = 0x7fffffff
    };

    enum NSBPatchEdgeStyle
    {
        NSB_PATCH_EDGE_DISCRETE = 0,
        NSB_PATCH_EDGE_CONTINUOUS,
        //
        NSB_PATCH_EDGE_COUNT,
        NSB_PATCH_EDGE_INVALID  = 0x7fffffff,
    };

    enum NSBDebugMonitorTokens
    {
        // DX9
        NSB_DMT_ENABLE     = 0,
        NSB_DMT_DISABLE,
        //
        NSB_DMT_COUNT,
        NSB_DMT_INVALID    = 0x7fffffff
    };

    enum NSBBlendOp
    {
        NSB_BLENDOP_ADD          = 0,
        NSB_BLENDOP_SUBTRACT,
        NSB_BLENDOP_REVSUBTRACT,
        NSB_BLENDOP_MIN,
        NSB_BLENDOP_MAX,
        //
        NSB_BLENDOP_COUNT,
        NSB_BLENDOP_DEPRECATED = 0x7ffffffe,
        NSB_BLENDOP_INVALID    = 0x7fffffff
    };

    enum NSBDegreeType
    {
        NSB_DEGREE_LINEAR      = 1,
        NSB_DEGREE_QUADRATIC   = 2,
        NSB_DEGREE_CUBIC       = 3,
        NSB_DEGREE_QUINTIC     = 5,
        NSB_DEGREE_INVALID     = 0x7fffffff
    };

    enum NSBTessellationMode
    {
        // Xenon
        NSB_TM_DISCRETE    = 0,
        NSB_TM_CONTINUOUS,
        NSB_TM_PEREDGE,
        //
        NSB_TM_COUNT,
        NSB_TM_INVALID     = 0x7fffffff
    };

    enum NSBFace
    {
        NSB_FACE_FRONT = 0,
        NSB_FACE_BACK,
        NSB_FACE_FRONT_AND_BACK,
        //
        NSB_FACE_COUNT,
        NSB_FACE_INVALID     = 0x7fffffff
    };

    static NSBRenderStateEnum LookupRenderState(const char* pcRenderState);
    static bool LookupRenderStateValue(NSBRenderStateEnum eRenderState,
        const char* pcValue, unsigned int& uiValue);

#if defined(NIDEBUG)
    static const char* LookupRenderStateString(NSBRenderStateEnum eRS);
#endif  //#if defined(NIDEBUG)
};

#endif  //NSBRENDERSTATES_H
