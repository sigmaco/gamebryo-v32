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

#ifndef NIPSALIGNEDQUADTEXTUREKERNEL_H
#define NIPSALIGNEDQUADTEXTUREKERNEL_H

#include <NiParticleLibType.h>
#include <NiSPKernelMacros.h>
#include <NiPSKernelDefinitions.h>
#include <NiPSAlignedQuadTextureKernelStruct.h>

/**
    Generates texture coordinates for quads representing particles in a particle system to
    simulate sprite animation that depends on each particle's age and looping behavior.
*/
NiSPDeclareKernelLib(NiPSAlignedQuadTextureKernel, NIPARTICLE_ENTRY)

#endif  // #ifndef NIPSALIGNEDQUADTEXTUREKERNEL_H
