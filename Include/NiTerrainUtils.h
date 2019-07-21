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
#ifndef NITERRAINUTILS_H
#define NITERRAINUTILS_H

#include <NiCollision.h>

#include <NiPixelData.h>
#include <NiRenderClick.h>

class NiAVObject;
class NiTerrainCell;
class NiTerrainSector;
class NiRay;
class NiSurface;

/// @cond EMERGENT_INTERNAL

/**
    Namespace containing collision utilities functions.
    @internal
    @note Intended for Emergent internal use only
*/
namespace NiTerrainUtils
{

    /// A const variable used to identify the MAXIMUM level of detail
    /// in searching functions:
    static const NiUInt32 ms_uiMAX_LOD = (NiUInt32)(-1);

    /**
        Tests the given ray against the given NiTerrainCell to find the collision point.
        
        The given ray origin and direction MUST be in terrain space coordinate.
        The 2D test Assumes the colliding leaf has ALREADY been resolved. This means there MUST
        be a collision with the terrain and we are now resolving the collision point and colision 
        normal. 

        This function can however return false in 3 different cases:
            - Parameters are invalid (Cell is null or is not the one we are colliding with)
            - The ray cast is performed in the oppsite direction to the terrain 
              (When start point is below / above the terrain and the direction is vertically 
              down / up respectively)
            - The ray intersects with a triangle's back face in which case no collision should occur
            - the ray's length (in the case where a ray's length is != 0 and therefore is in use) 
              is smaller than the distance between the point's height and the height of the ray's 
              origin.
        
        @param kRay ray to test against
        @param pkRootCell The cell that the 2D ray is colliding with
        @return True if the calculation of the collision data was successfull
    */
    bool TestRay2D(NiRay& kRay, NiTerrainCell* pkRootCell);

    /**
        Tests the given ray against an NiTerrainDataLeaf tree for
        collision. The ray should be set with LOCAL space coordinate

        @param kRay ray to test against
        @param pkRootCell Optional root of QuadTree to use as 
            beginning of search
        @return True if the Bound intersects the quad tree
    */
    bool TestRay(NiRay& kRay, NiTerrainCell* pkRootCell = 0, 
        NiUInt32 uiDetailLOD = NiTerrainUtils::ms_uiMAX_LOD);

    /**
        Tests the given bounding sphere against an NiTerrainDataLeaf tree
        for collision. This test is only used if the bound is static. The
        bound should be in LOCAL space coordinates.

        @param kVolume Bounding sphere to test against
        @param pkRootCell Optional root of Quad Tree to use as 
        beginning of search
        @return True if the Bound intersects the quad tree
    */
    bool TestBound(const NiBound& kVolume, NiTerrainCell* pkRootCell = NULL);

    /**
        Tests the given bounding sphere against an NiTerrainDataLeaf tree
        for collision. This test is only used if the bound is static
        and only tests the bound against the horizontal plane of the
        quadleaf. The bound should be in LOCAL space coordinates

        @param kVolume Bounding sphere to test against
        @param pkRootCell Optional root of QuadTree to use as
        beginning of search
        @return True if the Bound intersects the quad tree
    */
    bool TestBound2D(const NiBound& kVolume, NiTerrainCell* pkRootCell = NULL);

    /**
        @name Surface mask pixel retrieval functions

        @internal
        @note Intended for Emergent internal use only
    */
    //@{

    /**
        This attempts to return the opacity of the given surface, at the
        given WORLD location. Does not take into account surfaces on higher
        levels of detail. Does not take into account the Z component of the
        given world location

        @note Assumes the bound is in world space coordinates
    */
    bool GetSurfaceOpacity(
        const NiSurface* pkSurface, const NiPoint3& kLocation,
        NiUInt8& ucValue, NiUInt32 uiDetailLevel = NiTerrainUtils::ms_uiMAX_LOD, 
        bool bSearchLowerDetail = true,
        const NiTerrainCell* pkDataCell = 0) ;

    /**
        This function will resize an image using Bilinear filtering.
        The size of the image in bytes will be:
            Width * Width * NumChannels
    */
    void ResizeImage(NiUInt8* pucSrcPixels, 
        NiUInt32 uiSrcWidth, NiUInt8* pucDstPixels,NiUInt32 uiDstWidth, 
        NiUInt32 uiNumChannels);

    /**
        This function will crop an image using Bilinear filtering.
    */
    void CropImage(const NiRect<float>& kCropRegion, NiUInt8* pucSrcPixels, 
        NiUInt32 uiSrcWidth, NiUInt8* pucDstPixels,NiUInt32 uiDstWidth, 
        NiUInt32 uiNumChannels);

    /**
        This function will resample a region of an image using Bilinear filtering.
    */
    void ResampleImage(const NiRect<float>& kCropRegion, NiUInt8* pucSrcPixels, 
        NiUInt32 uiSrcWidth, const NiRect<NiInt32>& kSampleRegion, NiUInt8* pucDstPixels, 
        NiUInt32 uiDstWidth, NiUInt32 uiNumChannels);

    /**
        Saves the content of the NiPixelData into the specified file

        @param pcFilePath should be pointing to a .tga image
        @param pkPixelData the texture to save
    */
    bool WriteTexture(const char* pcDestFilePath, NiPixelData* pkPixelData);

    /**
        Exracts the source pixel data from the texture if it is available
    */
    NiPixelData* ExtractPixelData(NiTexture* pkTexture);

    /**
        Takes a screenshot of the render target and outputs the pixel data if it is available.
    */
    NiPixelData* ExtractPixelData(NiRenderClick* pkRenderClick);

    /**
        Attempt to update a portion of the texture instead of uploading the entire texture again.
        This function will attempt to use renderer specific code to acheive it's goals. If renderer
        specific code is not available then the "MarkAsChanged" function on the Src pixel data will
        simply be flagged.

        NOTE: The destination texture MUST have source pixel data available
    */
    void UpdateTextureRegion(NiSourceTexture* pkDstTexture, NiRect<efd::SInt32> kRegion);

    //@}

    /**
        Helper function that will create a new source texture from the components of up to 4 sets
        of pixel data.
    */
    NiSourceTexture* CombineImageChannelsToTexture(
        NiPixelData* pkRedImage, NiPixelFormat::Component eRedComponent, 
        NiPixelData* pkGreenImage, NiPixelFormat::Component eGreenComponent,
        NiPixelData* pkBlueImage, NiPixelFormat::Component eBlueComponent,
        NiPixelData* pkAlphaImage, NiPixelFormat::Component eAlphaComponent);

    #include "NiTerrainUtils.inl"
}

/// @endcond

#endif // NITERRAINUTILS_H
