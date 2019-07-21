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
#ifndef NISURFACEPACKAGE_H
#define NISURFACEPACKAGE_H

#include "NiTerrainLibType.h"

#include <NiString.h>
#include <NiTSet.h>
#include <NiTStringMap.h>

class NiSurface;

/**
    A surface package contains a set of surfaces (NiSurface) to be used in the
    terrain engine.

    A package can be saved to and loaded from an XML file, which contains the
    actual surface definitions. The texture paths used by the surfaces in the
    XML file should be relative to the location of the package, not the
    application.
 */
class NITERRAIN_ENTRY NiSurfacePackage : public NiRefObject
{

public:

    /// Destructor
    virtual ~NiSurfacePackage();

    /// Create a new surface package with the specified name.
    static NiSurfacePackage* Create(const NiString& kPackageName);

    /// @name Surface manipulation
    //@{
    /**
        Create a new blank surface with the given name and adds it to this
        package.

        If the given meta data store is null then the default static
        store is used. If a surface already exists by the given name, no new
        surface is created.

        @param kName Name given to the new surface.
        @param pkSurface Pointer to the newly created surface.
        @return True if the surface was successfully added to the package,
            otherwise false.
    */
    bool CreateSurface(const NiString& kName, NiSurface*& pkSurface);

    /**
        Compile all surfaces contained in the package.

        This will load all images from disk into memory for ALL contained
        surfaces into compressed runtime data.

        @return True if at least 1 surface was compiled, false otherwise.
    */
    bool PrecompileSurfaces();

    /**
        Populate the given set with pointers to all surfaces that are
        currently within this package

        @param kSurfaces Set to be populated with pointers to all loaded
            surfaces.
    */
    void GetSurfaces(NiTPrimitiveSet<NiSurface*>& kSurfaces) const;

    /**
        Find a surface contained in this package with the given name.

        @param kName Name of the surface to find.
        @param pkSurface Pointer to the found surface. Set to 0 if no surface
            is found
        @return True if a surface was found, false otherwise.
    */
    bool GetSurface(const NiString& kName, NiSurface*& pkSurface) const;

    /**
        Attempt to rename the given surface within this package.

        If a surface already exists with the new name, or the initial surface
        is not contained within this package, the surface will not be renamed.

        @param pkSurface Surface, contained in this package, to rename.
        @param kNewSurfaceName New name to set to the given surface.
        @return True if the surface was successfully renamed, false otherwise.
    */
    bool RenameSurface(NiSurface* pkSurface, const NiString& kNewSurfaceName);

    /**
        Move the given surface from its current package to this one.

        If a surface already exists in this package with the same name, the
        surface will not be moved. This function will also update the actual
        surface to reflect the package change.

        @param pkSurface Surface to move into this package.
        @return True if the surface was successfully moved, false otherwise.
    */
    bool ClaimSurface(NiSurface* pkSurface);

    /**
        Remove the given surface from this package, but do not delete it.

        By calling this function, the user is taking ownership of the surface.
        If the surface is not found within this package, no action is taken.
        This function will also update the actual surface to reflect the
        package release.

        @param pkSurface Surface to remove from this package.
        @return True if the surface was found and released successfully, false
            otherwise.
    */
    bool ReleaseSurface(NiSurface* pkSurface);

    /**
        Deletes the surface with the given name from memory.

        If no surface was found with the given name, no action is taken.

        @note Since the surface is immediately deleted, care must be taken to
            un-assign any existing user pointers.
    */
    void UnloadSurface(const NiString& kName);
    //@}

    /**
        @name Package manipulation
    */
    //@{

    /**
        Delete all contained surfaces from memory and removes them from the
        package.

        Only call this function if the surfaces are not currently in use
        elsewhere.

        @note Since the surfaces are immediately deleted, care must be taken to
            un-assign any existing user pointers.
    */
    void UnloadSurfaces();

    /**
        Get the relative or absolute XML file path that this package will
        load from and save data to.
    */
    const char* GetFilename() const;

    /**
        Get the Asset ID that this package can be uniquely identified by.
    */
    const char* GetAssetID() const;

    /// Get the visible name of this surface package, to be used in browsers,
    /// error messages etc.
    const NiString& GetName() const;

    /// Get the iteration value of this package
    efd::UInt32 GetIteration() const;

    /// Mark this package as dirty
    void MarkDirty(bool bDirty);

    //@}

    /// @cond EMERGENT_INTERNAL

    /// Sets the full path to the package file.
    void SetFileName(const NiString& kFilePath);
    /// brief Sets the asset ID of the package
    void SetAssetID(const NiString& kAssetID);
    /// Sets the value of the iteration of the package
    void SetIteration(efd::UInt32 uiIteration);

    /// @endcond

protected:

    /// @name Constructors
    //@{

    /// Default Constructor.
    NiSurfacePackage();

    /**
        Parameterized constructor.
        @param kPackageName Visible name of the package - this is NOT used in
        the file name.
    */
    NiSurfacePackage(const NiString& kPackageName);

    //@}

    /// @cond EMERGENT_INTERNAL

    /**
        A map of all surfaces contained in this package. The key is the surface name.
    */
    NiTStringPointerMap<NiSurface*> m_kSurfaces;

    /// The name of this package, used in error messages, surface browser etc
    NiString m_kPackageName;

    /// The file that this package is stored in.
    NiString m_kFileSrc;

    /// The asset ID of this package
    NiString m_kAssetID;

    /// The iteration number of this package
    efd::UInt32 m_uiIteration;

    /// Has this package changed since it was loaded?
    bool m_bDirty;

    /// @endcond
};

typedef NiPointer<NiSurfacePackage> NiSurfacePackagePtr;

#endif // NISURFACEPACKAGE_H
