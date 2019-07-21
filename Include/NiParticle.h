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
#ifndef NIPARTICLE_H
#define NIPARTICLE_H

// DLL support
#include "NiParticleLibType.h"

// General classes.
#include "NiPSAlignedQuadGenerator.h"
#include "NiPSBoundUpdater.h"
#include "NiPSCommonSemantics.h"
#include "NiPSConverter.h"
#include "NiPSFacingQuadGenerator.h"
#include "NiPSFlagsHelpers.h"
#include "NiPSKernelDefinitions.h"
#include "NiPSMeshParticleSystem.h"
#include "NiPSMetrics.h"
#include "NiPSParticleSystem.h"
#include "NiPSSimulator.h"

// Kernels.
#include <NiPSAlignedQuadGeneratorKernelFF.h>
#include <NiPSAlignedQuadGeneratorKernelFV.h>
#include <NiPSAlignedQuadGeneratorKernelVF.h>
#include <NiPSAlignedQuadGeneratorKernelVV.h>
#include <NiPSFacingQuadGeneratorKernel.h>
#include <NiPSSimulatorCollidersKernel.h>
#include <NiPSSimulatorFinalKernel.h>
#include <NiPSSimulatorForcesKernel.h>
#include <NiPSSimulatorGeneralKernel.h>
#include <NiPSSimulatorMeshAlignKernelFF.h>
#include <NiPSSimulatorMeshAlignKernelFV.h>
#include <NiPSSimulatorMeshAlignKernelVF.h>
#include <NiPSSimulatorMeshAlignKernelVV.h>

// Colliders.
#include "NiPSCollider.h"
#include "NiPSColliderDefinitions.h"
#include "NiPSColliderHelpers.h"
#include "NiPSPlanarCollider.h"
#include "NiPSSphericalCollider.h"

// Controllers.
#include "NiPSAirFieldAirFrictionCtlr.h"
#include "NiPSAirFieldInheritedVelocityCtlr.h"
#include "NiPSAirFieldSpreadCtlr.h"
#include "NiPSEmitParticlesCtlr.h"
#include "NiPSEmitterCtlr.h"
#include "NiPSEmitterDeclinationCtlr.h"
#include "NiPSEmitterDeclinationVarCtlr.h"
#include "NiPSEmitterFloatCtlr.h"
#include "NiPSEmitterLifeSpanCtlr.h"
#include "NiPSEmitterLifeSpanVarCtlr.h"
#include "NiPSEmitterPlanarAngleCtlr.h"
#include "NiPSEmitterPlanarAngleVarCtlr.h"
#include "NiPSEmitterRadiusCtlr.h"
#include "NiPSEmitterRadiusVarCtlr.h"
#include "NiPSEmitterRotAngleCtlr.h"
#include "NiPSEmitterRotAngleVarCtlr.h"
#include "NiPSEmitterRotSpeedCtlr.h"
#include "NiPSEmitterRotSpeedVarCtlr.h"
#include "NiPSEmitterSpeedCtlr.h"
#include "NiPSEmitterSpeedVarCtlr.h"
#include "NiPSEmitterSpeedFlipRatioCtlr.h"
#include "NiPSFieldAttenuationCtlr.h"
#include "NiPSFieldMagnitudeCtlr.h"
#include "NiPSFieldMaxDistanceCtlr.h"
#include "NiPSForceActiveCtlr.h"
#include "NiPSForceBoolCtlr.h"
#include "NiPSForceCtlr.h"
#include "NiPSForceFloatCtlr.h"
#include "NiPSGravityStrengthCtlr.h"
#include "NiPSResetOnLoopCtlr.h"

// Emitters.
#include "NiPSBoxEmitter.h"
#include "NiPSCurveEmitter.h"
#include "NiPSCylinderEmitter.h"
#include "NiPSEmitter.h"
#include "NiPSMeshEmitter.h"
#include "NiPSSpawner.h"
#include "NiPSSphereEmitter.h"
#include "NiPSTorusEmitter.h"
#include "NiPSVolumeEmitter.h"

// Forces.
#include "NiPSAirFieldForce.h"
#include "NiPSBombForce.h"
#include "NiPSDragFieldForce.h"
#include "NiPSDragForce.h"
#include "NiPSFieldForce.h"
#include "NiPSForce.h"
#include "NiPSForceDefinitions.h"
#include "NiPSForceHelpers.h"
#include "NiPSGravityFieldForce.h"
#include "NiPSGravityForce.h"
#include "NiPSRadialFieldForce.h"
#include "NiPSTurbulenceFieldForce.h"
#include "NiPSVortexFieldForce.h"

// Simulator steps.
#include "NiPSSimulatorCollidersStep.h"
#include "NiPSSimulatorFinalStep.h"
#include "NiPSSimulatorForcesStep.h"
#include "NiPSSimulatorKernelHelpers.h"
#include "NiPSSimulatorGeneralStep.h"
#include "NiPSSimulatorMeshAlignStep.h"
#include "NiPSSimulatorStep.h"

// Static data manager.
#include "NiParticleSDM.h"
static NiParticleSDM NiParticleSDMObject;

#endif  // #ifndef NIPARTICLE_H
