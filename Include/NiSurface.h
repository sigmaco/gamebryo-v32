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
#ifndef NISURFACE_H
#define NISURFACE_H

#include <NiTexturingProperty.h>
#include <NiString.h>
#include <NiPoint2.h>

#include "NiTerrainLibType.h"
#include "NiMetaData.h"
#include "NiSurfacePackage.h"

/**
    NiSurface objects are used to describe different patches of terrain.

    An NiSurface object can be painted onto the terrain to create patches
    of grass, sand, snow, gravel, etc. This class is mainly used to define
    how these patches will be rendered by correlating all the relevant data
    ready to be sent to the NiTerrainMaterial.
 */
class NITERRAIN_ENTRY NiSurface : public NiMemObject
{

public:

    /// Key used to get the NiExtraData registered with a terrain cell's texture property. The 
    /// extra data encodes information about that surfaces are on a given cell.
    static const char* CONFIG_EXTRADATA_KEY;

    /// String used to identify a texture that has failed to resolve
    static const char* MISSING_TEXTURE_PATH;

    /// The enumeration used to select different map channels:
    enum SurfaceMapID
    {
        /// Diffuse map which may or may not contain an alpha
        /// channel. If the alpha channel is present then alpha is interpreted
        /// as a detail map.
        SURFACE_MAP_DIFFUSE,
		/// Single channel detail map.
        SURFACE_MAP_DETAIL,

        /// Normal map which may or may not contain an alpha
        /// channel. If the alpha channel is present then alpha is interpreted
        /// as a parallax map.
        SURFACE_MAP_NORMAL,
		/// Single channel parallax map.
        SURFACE_MAP_PARALLAX,

        /// Distrubtion map is tiled the same number of times as the diffuse and normal map
        /// but is used to provide additional blending information per layer. This allows
        /// a non-linear blend around the borders of layers.
        SURFACE_MAP_DISTRIBUTION,
		
		/// Specular map.
        SURFACE_MAP_SPECULAR,

        /// Maximum number of maps that may be assigned to a surface/material.
        NUM_SURFACE_MAPS
    };

    /// An enumeration used to select different textures from the surface's texturing property
    enum SurfaceTextureID
    {
        /// The texture with RBG = Diffuse, A = Detail
        SURFACE_TEX_DIFFUSE_DETAIL,
        /// The texture with RBG = Normals, A = Parallax
        SURFACE_TEX_NORMAL_PARALLAX,
        /// The texture with RBG = Specular, A = Distribution
        SURFACE_TEX_SPECULAR_DISTRIBUTION,

        /// Maximum number of textures in the texturing property
        NUM_SURFACE_TEXTURES
    };
    
    /// Values used to control layer capabilities.
    enum SurfaceMapCaps
    {
		/// Surface can support diffuse maps.
        SURFACE_CAPS_DIFFUSE = 0x0001,
		/// Surface can support detail maps.
        SURFACE_CAPS_DETAIL = 0x0002,
		/// Surface can support normal maps.
        SURFACE_CAPS_NORMAL = 0x0004,
		/// Surface can support parallax maps.
        SURFACE_CAPS_PARALLAX = 0x0008,
		/// Surface can support distribution maps.
        SURFACE_CAPS_DISTRIBUTION = 0x0010,
		/// Surface can support specular maps.
        SURFACE_CAPS_SPECULAR = 0x0020,
		/// Surface can support all map types.
        SURFACE_CAPS_ALL = SURFACE_CAPS_DIFFUSE | SURFACE_CAPS_DETAIL | SURFACE_CAPS_NORMAL |
            SURFACE_CAPS_PARALLAX | SURFACE_CAPS_DISTRIBUTION | SURFACE_CAPS_SPECULAR
    };

    /// Simple structure for storing each texture entry for a surface.
    struct TextureSlotEntry : efd::MemObject
    {
        /// The texture slot's file path
        NiString m_kFilePath;
        /// The associated asset id
        efd::utf8string m_kAssetId;
    };

    /// @name Constructors
    //@{

    /**
        Constructor with parameters.
    */
    NiSurface();
    //@}

    /// Destructor
    virtual ~NiSurface();

    /// @name Package Management
    //@{

    /**
        Sets a reference to the package that contains this surface instance.

        This function will update both the new and the old package to reflect
        the package change.

        @note If the new package is set to NULL, the user claims responsibility
            for deleting this surface when it is no longer used.
        @param pkPackage The package that owns this surface instance.
    */
    inline void SetPackage(NiSurfacePackage* pkPackage);

    /// Gets a reference to the package that contains this surface instance.
    ///
    /// @return The package that owns this surface instance.
    inline NiSurfacePackage* GetPackage() const;

    //@}

    /// @name Properties
    //@{
    /// Get the name of this surface.
    inline const NiString& GetName() const;

    /**
        Set the name of this surface.

        This function will also update the containing package to reflect
        the name change.
        @param kName Name of this surface.
    */
    inline void SetName(const NiString& kName);

    //@}

    /// @name Surface Configuration
    //@{
    /**
        Sets a texture slot on the surface. If a texture already exists, it is deleted and the 
        specified texture is assigned in its place.
        @param eMapID Texture type to assign.
        @param pkTexSlot New texture information. Specified NULL to clear the entry.
    */
    inline void SetTextureSlotEntry(SurfaceMapID eMapID, TextureSlotEntry* pkTexSlot);
     
    /// Gets a pointer to the specified texture slot on the surface.
    inline TextureSlotEntry* GetTextureSlotEntry(SurfaceMapID eMapID) const;

    /// Checks for any non-null texture slots. If at least one is found, this method returns true, 
    /// else, it returns false.
    inline bool HasValidTextureSlots() const;

    /// Gets a bit-mask containing bits set for each of the valid types of texture maps on the 
    /// surface.
    NiUInt32 GetSurfaceCaps() const;

    /// Gets the amount of times the surface repeats across the terrain.
    inline float GetTextureTiling() const;

    /// Sets the amount of times the surface repeats across the terrain.
    inline void SetTextureTiling(float fValue);

    /// Gets the amount of times the detail texture repeats across the terrain.
    inline float GetDetailTextureTiling() const;

    /// Sets the amount of times the detail texture repeats across the terrain.
    inline void SetDetailTextureTiling(float fValue);

    /// Gets the rotation of the surface. The rotation is about the axis perpendicular to the 
    /// surface as projected on the terrain.
    inline float GetRotation() const;

    /// Sets the rotation of the surface.
    inline void SetRotation(float fValue);

    /// Gets the amount of influence from the parallax map on the surface.
    inline float GetParallaxStrength() const;

    /// Sets the amount of influence from the parallax map on the surface.
    inline void SetParallaxStrength(float fValue);

    /// Gets the scaler value applied to the distribution mask.
    inline float GetDistributionMaskStrength() const;

    /// Sets the distribution mask strength.
    inline void SetDistributionMaskStrength(float fValue);

    /// Gets the specular power.
    inline float GetSpecularPower() const;

    /// Sets the specular power. This is only used if a valid specular map is assigned to the 
    /// surface.
    inline void SetSpecularPower(float fValue);

    /// Gets the strength at which the specular map affects the surface.
    inline float GetSpecularIntensity() const;

    /// Sets the strength at which the specular map affects the surface.
    inline void SetSpecularIntensity(float fValue);

    /// Retrieve a reference to the NiMetaData object that this surface uses.
    inline NiMetaData& GetMetaData();

    /// Retrieve a const reference to the NiMetaData object that this surface
    /// uses.
    inline const NiMetaData& GetMetaData() const;
    //@}

    /// @name Shader Interface
    //@{
    /**
        This function prepares the surface for use in a shader by making sure the surface has a 
        valid texturing property available. This may be done by either loading compiled textures
        from disk, or compiling the textures from their input textures.
    */
    void PrepareForUse();

    /**
        Loads this surface's precompiled textures from disk and assigns them to the texturing
        property.
    */
    void LoadCachedTextures();

    /// This function loads all the texture files that have been specified and packs them into a 
    /// platform specific format optimal for a given platform. Once this function is called, 
    /// the surface is ready to be used for rendering if the compilation was successful. Check the
    /// existance of texturing property to see if it succeeded.
    void CompileSurface();

    /// This function loads all the texture files that have been specified and packs them into a 
    /// platform specific format optimal for a given platform. This function then returns this
    /// generated set of textures to the caller (used for saving) and does not prepare the surface
    /// to be rendered at all.
    NiTexturingProperty* GenerateSurfaceTextures() const;

    /// Return true if this surface has been compiled through the
    /// CompileSurface function
    inline bool IsCompiled() const;

    /// Returns true if all texture asset ids have been resolved meaning this surface is ready to 
    /// be compiled.
    inline bool IsResolved() const;

    /// Sets the texturing property representing the surface. This will mark the
    /// surface as compiled.
    inline void SetTexturingProperty(NiTexturingProperty* pkTexProp);

    /// Gets the texturing property representing the surface. Note, this is only valid after a 
    /// surface has been successfully compiled.
    inline NiTexturingProperty* GetTexturingProperty() const;

    /// Helper function to get a string representation of the surface map enum.
    static const char* GetTextureSlotName(SurfaceMapID eMapID);

    //@}

    /// @cond EMERGENT_INTERNAL
    static void _SDMInit();
    static void _SDMShutdown();

    inline void MarkResolved(bool bResolved);
    inline void SetActive(bool bActive);

    /**
        Helper function to merge the different textures of this surface with the specified surface.
        @param pkTexProp The texture property to merge the result into. If NULL, the result of this 
            method is simply the texture property of the surface.
        @param pkSurface The surface with which to merge into the specified texture property.
        @return A texturing property containing the existing textures plus the textures from the 
            specified surface.
        @remarks This is a quick operation since all it does is set pointers to the existing 
            textures on the surfaces.
        @remarks All surface textures are stored as SHADER_MAPs. The shader map list is then sorted
            based on the type of texture map. (DIFFUSE, SPECULAR, DISTRIBUTION, etc.).
    */
    NiTexturingProperty* MergeSurfaces(NiTexturingProperty* pkTexProp, 
        const NiSurface* pkSurface) const;

    /// @endcond

    /// Set the surface to use when other surfaces are unavailable
    static void SetErrorSurface(NiSurface* pkSurface);
    /// Set the surface to use when a surface is still loading
    static void SetLoadingSurface(NiSurface* pkSurface);
    /// Get the error surface
    static NiSurface* GetErrorSurface();
    /// Get the loading surface
    static NiSurface* GetLoadingSurface();

protected:

    /// Creates a surface with the given texture as it's base map
    static NiSurface* CreateSpecialSurface(NiTexture* pkBaseTexture);

    /// The array of map ID names:
    static NiFixedString* ms_pkSurfaceMapNames;

    /// The special surfaces
    static NiSurface* ms_pkLoadingSurface;
    static NiSurface* ms_pkErrorSurface;

    /// The special surface names
    static NiFixedString ms_kErrorSurfaceName;
    static NiFixedString ms_kLoadingSurfaceName;

    /// MetaData storage. (E.g. footfall information)
    NiMetaData m_kMetaData;

    /// The name of this surface
    NiString m_kName;

    // Array of slots used for each texture.
    TextureSlotEntry* m_apkTextureSlots[NUM_SURFACE_MAPS];

    /// The package that we belong to
    NiSurfacePackage* m_pkPackage;

    /// Texturing property containing the compiled and packed surface data.
    NiTexturingPropertyPtr m_spTexProp;

    /// Number of times the texture repeats across the terrain.
    float m_fTextureTiling;

    /// Number of times the detail texture map repeats across the terrain.
    float m_fDetailTextureTiling;

    /// Z rotation of the texture.
    float m_fRotation;

    /// Controls how strong the parallax map affects the surface.
    float m_fParallaxStrength;

    /// Controls the fall off of the distribution map.
    float m_fDistributionMaskStrength;

    /// Controls the specular power on the surface.
    float m_fSpecularPower;

    /// General scalar controlling the amount of influence from the specular map on the surface.
    float m_fSpecularIntensity;

private:

    /// Marks whether the surface has had all of its texture references located (not loaded) meaning
    /// the surface can be compiled.
    bool m_bIsResolved;

    /// If true the surface has been packed and is ready for use on the terrain.
    bool m_bCompiled;

    /// True if the surface is currently assigned to the terrain and used for rendering.
    bool m_bIsActive;

    friend class NiSurfacePackage;
};

#include "NiSurface.inl"

#endif // NISURFACE_H
