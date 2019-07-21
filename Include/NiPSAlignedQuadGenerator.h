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

#ifndef NIPSALIGNEDQUADGENERATOR_H
#define NIPSALIGNEDQUADGENERATOR_H

#include "NiParticleLibType.h"
#include <NiMeshModifier.h>
#include <NiPSAlignedQuadGeneratorKernelFF.h>
#include <NiPSAlignedQuadGeneratorKernelFV.h>
#include <NiPSAlignedQuadGeneratorKernelVF.h>
#include <NiPSAlignedQuadGeneratorKernelVV.h>
#include <NiPSAlignedQuadTextureKernel.h>
#include <NiSPTask.h>
#include <NiSPStream.h>
#include <NiCamera.h>
#include <NiDataStream.h>

class NiDataStreamRef;
class NiPSParticleSystem;

/**
    A mesh modifier that uses particle system data to generate aligned quads
    for each particle.

    Each quad is actually two triangles. If texture animation is enabled, the texture
    coordinates will be set to select a sub-texture/cell from the supplied texture
    which contains multiple frames. If texture animation is disabled, the texture coordinates
    for each quad are fixed and range from 0 to 1. The orientation of the quad is determined
    by the alignment parameters of the particle system: each of the normal and
    "v" texture coordinate (up) directions must be specified. These directions can
    be fixed for all particles or computed per-particle. The "u" texture direction
    is perpendicular to both the normal and up direction. Specifying the same
    method for both up and normal will result in undefined behavior, with the
    exception of the camera method.

    The normals for each vertex are perpendicular to the quad face. Vertex
    colors are used if color data exists. Rotation data, if present, is applied
    after alignment. Hence, the alignment may be viewed as defining the local
    coordinate system for the particle.

    @note This mesh modifier must be attached to an NiPSParticleSystem object.
*/

class NIPARTICLE_ENTRY NiPSAlignedQuadGenerator : public NiMeshModifier
{
    /// @cond EMERGENT_INTERNAL

    NiDeclareRTTI;
    NiDeclareClone(NiPSAlignedQuadGenerator);
    NiDeclareStream;
    NiDeclareViewerStrings;

    /// @endcond

public:
    /// @name Construction and Destruction
    //@{
    /// Default constructor.
    NiPSAlignedQuadGenerator();
    //@}

    /// @name Base Class Overrides
    //@{
    virtual bool Attach(NiMesh* pkMesh);
    virtual bool Detach(NiMesh* pkMesh);
    virtual bool SubmitTasks(NiMesh* pkMesh, NiSyncArgs* pkArgs,
        NiSPWorkflowManager* pkWFManager);
    virtual bool CompleteTasks(NiMesh* pkMesh, NiSyncArgs* pkArgs);
    virtual bool IsComplete(NiMesh* pkMesh, NiSyncArgs* pkArgs);
    virtual bool AreRequirementsMet(
        NiMesh* pkMesh,
        NiSystemDesc::RendererID eRenderer) const;
    virtual void RetrieveRequirements(NiMeshRequirements&
        kRequirements) const;
    //@}

    /**
        @name Stretching/Squashing with Speed

        These functions provide access to the variables controlling the shape of the
        particle as a function of particle speed. The V direction is up (the V direction
        of a texture applied to the particle) while U is perpendicular to V.
    */
    //@{
    /**
        Specify a ratio for stretching/squashing of particles along
        the U direction with respect to the velocity.

        A positive ratio will stretch particles up to a limited scale
        specified using SetScaleLimitU.
        A positive ratio will squash particles down to a limited scale
        specified using SetScaleLimitU.
    */
    inline void SetScaleAmountU(const float fValue);

    /**
        Specify a limit for stretching/squashing of particles along
        the U direction.

        Set limit < 1 for a positive ratio (stretching).
        Set limit > 1 for a negative ratio (squashing).
    */
    inline void SetScaleLimitU(const float fValue);

    /**
        Specify a scale for stretching/squashing of particles along
        the U direction when the speed is zero.

        Set limit < rest for a positive ratio (stretching).
        Set limit > rest for a negative ratio (squashing).
    */
    inline void SetScaleRestU(const float fValue);

    /**
        Specify a ratio for stretching/squashing of particles along
        the V direction with respect to the velocity.

        A positive ratio will stretch particles up to a limited scale
        specified using SetScaleLimitV.
        A negative ratio will squash particles down to a limited scale
        specified using SetScaleLimitV.
    */
    inline void SetScaleAmountV(const float fValue);

    /**
        Specify a limit for stretching/squashing of particles along
        the V direction.

        Set limit < 1 for a positive ratio (stretching).
        Set limit > 1 for a negative ratio (squashing).
    */
    inline void SetScaleLimitV(const float fValue);

    /**
        Specify a scale for stretching/squashing of particles along
        the V direction when the speed is zero.

        Set limit < rest for a positive ratio (stretching).
        Set limit > rest for a negative ratio (squashing).
    */
    inline void SetScaleRestV(const float fValue);


    /**
        Returns the ratio for stretching/squashing of particles along
        the U direction with respect to the velocity.

        A positive ratio will stretch particles up to a limited scale
        specified using SetScaleLimitU.
        A positive ratio will squash particles down to a limited scale
        specified using SetScaleLimitU.
    */
    inline float GetScaleAmountU() const;

    /**
        Returns the limit for stretching/squashing of particles along
        the U direction.
    */
    inline float GetScaleLimitU() const;

    /**
        Returns the scale for stretching/squashing of particles along
        the U direction when the speed is zero.
    */
    inline float GetScaleRestU() const;

    /**
        Returns the ratio for stretching/squashing of particles along
        the V direction with respect to the velocity.

        A positive ratio will stretch particles up to a limited scale
        specified using SetScaleLimitV.
        A negative ratio will squash particles down to a limited scale
        specified using SetScaleLimitV.
    */
    inline float GetScaleAmountV() const;

    /**
        Returns the limit for stretching/squashing of particles along
        the V direction.
    */
    inline float GetScaleLimitV() const;

    /**
        Returns the scale for stretching/squashing of particles along
        the V direction when the speed is zero.
    */
    inline float GetScaleRestV() const;

    //@}

    /**
        @name Animating sprite texture over the particle's lifespan

        These functions provide access to the variables controlling the animation of the texture
        applied to each particle over its lifespan. A single texture holds several frames for the
        texture animation. The LoopBehavior specifies the sequencing through the frames while the
        initial and final frames along with the initial and final times specifies how quickly to
        run through the sequence.
    */
    //@{
    /**
        Specify whether or not to scroll smoothly through texture coordinates or snap to frames
        in the sprite animation texture.

        If true, the texture coordinates can vary continuously. In effect, this textures the
        sprite with a sliding window over the texture, which gives a particular effect that might
        be good in some cases such as con trails, or lightning.

        If false, the sprite will always show a complete frame.
    */
    inline void SetUVScrolling(const bool bValue);

    /**
        Specify the number of frames across in the supplied texture.
    */
    inline void SetNumFramesAcross(const NiUInt16 uiValue);

    /**
        Specify the number of frames down in the supplied texture.
    */
    inline void SetNumFramesDown(const NiUInt16 uiValue);

    /**
        Specify if we wish to ping pong when sprite texture animation frames are played.
    */
    inline void SetPingPong(const bool bValue);

    /**
        Specify the initial texture frame to be displayed.
    */
    inline void SetInitialFrame(const NiUInt16 uiValue);

    /**
        Specify the initial texture frame variance.
    */
    inline void SetInitialFrameVar(const float fValue);

    /**
        Specify the number of frames to play.
    */
    inline void SetNumFrames(const NiUInt16 uiValue);

    /**
        Specify the number of frames to play variance.
    */
    inline void SetNumFramesVar(const float fValue);

   /**
        Specify the time that the initial texture frame should be displayed.
    */
    inline void SetInitialTime(const float fValue);

    /**
        Specify the time that the final texture frame should be displayed.
    */
    inline void SetFinalTime(const float fValue);

    /**
        Returns true when scrolling smoothly through texture coordinates or false when snapping to
        frames in the sprite animation texture.

        If true, the texture coordinates can vary continuously. In effect, this textures the
        sprite with a sliding window over the texture, which gives a particular effect that might
        be good in some cases such as con trails, or lightning.

        If false, the sprite will always show a complete frame.
    */
    inline bool GetUVScrolling() const;

    /**
        Returns the number of frames across in the supplied texture.
    */
    inline NiUInt16 GetNumFramesAcross() const;

    /**
        Returns the number of frames down in the supplied texture.
    */
    inline NiUInt16 GetNumFramesDown() const;

    /**
        Returns the ping pong state of the sprite texture animation .
    */
    inline bool GetPingPong() const;

     /**
        Returns the initial texture frame to be displayed.
    */
    inline NiUInt16 GetInitialFrame() const;

    /**
        Returns the initial texture frame variance.
    */
    inline float GetInitialFrameVar() const;

    /**
        Returns the number of frames to play.
    */
    inline NiUInt16 GetNumFrames() const;

    /**
        Returns the number of frames to play variance.
    */
    inline float GetNumFramesVar() const;

    /**
        Returns the time that the initial texture frame should be displayed.
    */
    inline float GetInitialTime() const;

    /**
        Returns the time that the final texture frame should be displayed.
    */
    inline float GetFinalTime() const;

   /**
        Specify a pivot point offset in the U direction.

        The point at which the particles will rotate.
    */
    inline void SetCenterU(const float fValue);

    /**
        Specify a pivot point offset in the V direction.

        The point at which the particles will rotate.
    */
    inline void SetCenterV(const float fValue);

    /**
        Returns the pivot point offset in the U direction.

        The point at which the particles will rotate.
    */
    inline float GetCenterU() const;

    /**
        Returns the pivot point offset in the V direction.

        The point at which the particles will rotate.
    */
    inline float GetCenterV() const;

    //@}

protected:
    /// Perform attachment work that depends on the active alignment methods.
    bool AttachAlignMethods(NiPSParticleSystem* pkParticleSystem);

    /// Perform submission work that depends on the active alignment methods.
    bool SubmitAlignMethods(NiPSParticleSystem* pkParticleSystem, NiSyncArgs* pkArgs);

    /// Functions for normalizing the scale amounts to be independent of limit and rest.
    void NormalizeScaleAmountU();
    void NormalizeScaleAmountV();


    /**
        Helper function to add a data stream with the specified parameters
        to the mesh.

        If a data stream with the specified parameters already exists on the
        mesh, this function will assert that all the parameters match and then
        return that data stream instead.
    */
    static NiDataStream* AddDataStream(
        NiMesh* pkMesh,
        const NiFixedString& kSemantic,
        NiUInt32 uiSemanticIndex,
        NiDataStreamElement::Format eFormat,
        NiUInt32 uiCount,
        NiUInt8 uiAccessMask,
        NiDataStream::Usage eUsage,
        NiObject::CloningBehavior eCloningBehavior,
        size_t stElementSize,
        const void* pvData = NULL);

    /// Determine if this stream meets the requirements
    static bool ValidateStream(const NiDataStreamRef* pkStreamRef,
        NiUInt8 uiAccessMask,
        NiDataStream::Usage eUsage,
        NiObject::CloningBehavior eCloningBehavior,
        NiDataStreamElement::Format eFormat);

    /// Floodgate workflow
    NiSPWorkflowPtr m_spWorkflow;

    /// @name Quad Generator Floodgate kernel
    //@{

    /// The Floodgate quad generator kernel to use for this mesh modifier.
    NiSPKernel* m_pkGeneratorKernel;

    /// A structure containing the general input data for the quad generator Floodgate kernel.
    NiPSAlignedQuadGeneratorKernelStruct m_kGeneratorKernelStruct;

    /// Floodgate quad generator task.
    NiSPTaskPtr m_spGeneratorTask;
    //@}

    /// @name Quad Generator Input Floodgate Streams
    //@{
    NiTSPFixedInput<NiPSAlignedQuadGeneratorKernelStruct> m_kGeneratorKernelStructIS;
    NiTSPStream<NiPoint3> m_kPositionIS;
    NiTSPStream<float> m_kRadiusIS;
    NiTSPStream<float> m_kSizeIS;
    NiTSPStream<NiRGBA> m_kColorIS;
    NiTSPStream<float> m_kRotAngleIS;
    NiTSPStream<NiPoint3> m_kVelocityIS;
    //@}

    /// @name Quad Generator Output Floodgate Streams
    //@{
    NiTSPStream<NiPoint3> m_kVertexOS;
    NiTSPStream<NiPoint3> m_kNormalOS;
    NiTSPStream<NiRGBA> m_kColorOS;
    //@}

    /// @name Animated Quad Texture Floodgate kernel
    //@{

    /// The Floodgate animated quad texture kernel to use for this mesh modifier.
    NiSPKernel* m_pkTextureKernel;

    /// A structure containing the general input data for the animated quad texture Floodgate
    /// kernel.
    NiPSAlignedQuadTextureKernelStruct m_kTextureKernelStruct;

    /// Floodgate animated texture task.
    NiSPTaskPtr m_spTextureTask;
    //@}

    /// @name Animated Quad Texture Input Floodgate Streams
    //@{
    NiTSPFixedInput<NiPSAlignedQuadTextureKernelStruct> m_kTextureKernelStructIS;
    NiTSPStream<float> m_kAgeIS;
    NiTSPStream<float> m_kLifeSpanIS;
    NiTSPStream<float> m_kVarianceIS;
    //@}

    /// @name Animated Quad Texture Output Floodgate Stream

    //@{
    NiTSPStream<NiPoint3> m_kTexCoordOS;
    //@}

    /**
        Indicates whether or not the maximum number of particles requires
        32-bit indices.

        This value is set during the Attach function by comparing the max
        number of particles reported by the particle system to
        MAX_PARTICLES_FOR_16BIT_INDICES.
    */
    bool m_b32BitIndices;

    /**
        Indicates whether or not a color stream is required.

        This value is set during the Attach function by inspecting whether or
        not the particle system has color data.
    */
    bool m_bColors;

    /**
        Indicates whether or not the mesh modifier is currently attached to
        a particle system.

        This value is set to true during the Attach function and to false
        during the Detach function.
    */
    bool m_bAttached;

    /// The maximum number of particles supported by this mesh modifier.
    static const NiUInt32 MAX_SUPPORTED_PARTICLES;

    /// The maximum number of particles for which 16-bit indices can be used.
    static const NiUInt16 MAX_PARTICLES_FOR_16BIT_INDICES;
};

NiSmartPointer(NiPSAlignedQuadGenerator);

#include <NiPSAlignedQuadGenerator.inl>

#endif  // #ifndef NIPSALIGNEDQUADGENERATOR_H
