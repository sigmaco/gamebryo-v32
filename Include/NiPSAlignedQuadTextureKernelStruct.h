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

#ifndef NIPSALIGNEDQUADTEXTUREKERNELSTRUCT_H
#define NIPSALIGNEDQUADTEXTUREKERNELSTRUCT_H

#include <NiParticleLibType.h>
#include <NiTransform.h>

/// A structure containing data required by the NiPSAlignedQuadTextureKernel Floodgate kernel.
struct NiPSAlignedQuadTextureKernelStruct
{
    /**
        Indicates whether or not to scroll smoothly through texture coordinates or snap to frames
        in the sprite animation texture.

        If true, the texture coordinates can vary continuously. In effect, this textures the
        sprite with a sliding window over the texture, which gives a particular effect that might
        be good in some cases such as con trails, or lightning.

        If false, the sprite will always show a complete frame.
    */
    bool m_bUVScrolling;

    /**
        Indicates whether or not we want to ping pong when we have reached our final time.
    */
    bool m_bPingPong;

    /**
        The number of frames across in the supplied texture.
    */
    NiUInt16 m_uiNumFramesAcross;

    /**
        The number of frames down in the supplied texture.
    */
    NiUInt16 m_uiNumFramesDown;

    /**
        The zero based index of the initial frame.

        The initial frame should exist in the supplied texture image.
    */
    NiUInt16 m_uiInitialFrame;

    /**
        Number of frames to play starting from the initial frame.

        The number of frames can be 1 - n.
    */
    NiUInt16 m_uiNumFrames;

    /**
    The variance for the initial frame.

    OutputInitialFrame = m_uiInitialFrame +- (m_fInitialFrameVar * m_uiInitialFrame)
    */
    float m_fInitialFrameVar;

    /**
    The variance for the number of frames.

    OutputNumFrame = m_uiNumFrames +- (m_fNumFramesVar * m_uiNumFrames)
    */
    float m_fNumFramesVar;

    /**
        The time that the initial frame should be displayed.
    */
    float m_fInitialTime;

    /**
        The time that the final frame should be displayed.
    */
    float m_fFinalTime;
};

#endif  // #ifndef NIPSALIGNEDQUADTEXTUREKERNELSTRUCT_H
