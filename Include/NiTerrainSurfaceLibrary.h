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
#ifndef NITERRAINSURFACELIBRARY_H
#define NITERRAINSURFACELIBRARY_H

#include <NiMemManager.h>
#include <NiRefObject.h>
#include <NiUniversalTypes.h>
#include <efd/utf8string.h>

#include "NiTerrainLibType.h"
#include "NiSurfacePackage.h"
#include "NiTerrainEvents.h"
#include "NiTerrainAssetReference.h"

/**
    This class is used to store and manage a set of Surface packages that can be used on multiple 
    terrains at a time. 
*/
class NITERRAIN_ENTRY NiTerrainSurfaceLibrary : public NiRefObject, 
    public NiTerrainObservable<NiTerrainSurfaceLibrary, NiSurfacePackage*>
{
public:
    /**
        Constructor specifying the asset resolver implementation to use when loading 
        packages.

        @param pkResolver The implementation of NiTerrainAssetResolverBase to use
    */
    NiTerrainSurfaceLibrary(NiTerrainAssetResolverBase* pkResolver);

    /**
        Find a loaded package by the package name

        @param kPackageName The name of the package to find
        @return A pointer to the package if it has been loaded into the library
    */
    NiSurfacePackage* FindPackageByName(efd::utf8string kPackageName);

    /**
        Find a loaded package by the package asset ID

        @param kPackageAssetID The asset ID of the package to find
        @return A pointer to the package if it has been loaded into the library
    */
    NiSurfacePackage* FindPackageByAsset(efd::utf8string kPackageAssetID);

    /**
        Find a loaded package by the absolute filename

        @param kPackageFilename The absolute filename of the package to find
        @return A pointer to the package if it has been loaded into the library
    */
    NiSurfacePackage* FindPackageByFile(efd::utf8string kPackageFilename);

    /**
        Find a surface that has been loaded by the surface name and the package name

        @param kPackageName The name of the package containing the surface
        @param kSurfaceName The name of the surface being queried
        @return A pointer to the surface if it has been loaded into the library
    */
    NiSurface* FindSurfaceByName(efd::utf8string kPackageName, efd::utf8string kSurfaceName);

    /**
        Find a surface that has been loaded by the surface name and the package asset ID

        @param kPackageAssetID The asset ID of the package containing the surface
        @param kSurfaceName The name of the surface being queried
        @return A pointer to the surface if it has been loaded into the library
    */
    NiSurface* FindSurfaceByAsset(efd::utf8string kPackageAssetID, efd::utf8string kSurfaceName);

    /**
        Find a surface that has been loaded by the surface name and the package filename

        @param kPackageFilename The absolute filename of the package containing the surface
        @param kSurfaceName The name of the surface being queried
        @return A pointer to the surface if it has been loaded into the library
    */
    NiSurface* FindSurfaceByFile(efd::utf8string kPackageFilename, efd::utf8string kSurfaceName);

    /**
        Add a package object to the surface library manually. 
        NOTE: Any packages that already exist within the library under the same name, assetID, or
        filename will be removed.

        @param pkPackage The package to add to the library
    */
    void AddPackage(NiSurfacePackage* pkPackage);

    /**
        Inject a package reference into the library to request it to load that package. 

        @param kReference The reference to the package to bring into the library
    */
    void InjectReference(const NiTerrainAssetReference& kReference);

    /**
        Register a package reference with the surface library to indicate that an object
        requires the data stored in the referenced package. The Surface library will attempt to load
        the surface package at the reference, and notify the caller through the callback interface
        by calling the following code:

            pkTarget->kCallback(NiSurfacePackage* pkPackage, const efd::utf8string& kAssetID)

        NOTE: The callback must match this signature for the function to compile correctly.
        
        Calls to this function must be matched with similar calls to DeregisterReference
        The library will continue calling this callback every time the surface package is loaded.

        @param kReference A reference to the package the caller is referencing
        @param pkTarget The object to callback to when the referenced package is available
        @param kCallback The function pointer to the member function of the target to callback to.
            The callback function must be of the described type.
    */
    template <class TargetType, typename CallbackType>
    void RegisterReference(const NiTerrainAssetReference& kReference, TargetType* pkTarget, 
        CallbackType kCallback);
    
    /**
        Deregister a package reference from the library. The library will remove the target object
        from the list of objects to callback to when the package changes.

        Calls to this function must be matched with similar calls to RegisterReference
    
        @param kReference A reference to the package the caller is referencing
        @param pkTarget The object to callback to when the referenced package is available
        @param kCallback The function pointer to the member function of the target to callback to.
            The callback function must be of the described type.
    */
    template <class TargetType, typename CallbackType>
    void DeregisterReference(const NiTerrainAssetReference& kReference, TargetType* pkTarget, 
        CallbackType kCallback);
    
    /**
        Request that a package be reloaded from disk

        @param pkPackage The package to reload
    */
    void RequestReload(NiSurfacePackage* pkPackage);
    
    /**
        Save a package back to it's file.

        @param pkPackage The package to save to disk
        @return true if the save was successful
    */
    bool SavePackage(NiSurfacePackage* pkPackage);

    /**
        Remove all packages from the library completely. 
        This function should not be called unless the caller is sure that no packages in the library
        are being used.
    */
    void FlushLoadedPackages();

    /**
        Read a package from a file. This package will not be added to library and this function is
        exposed to allow a user to inspect packages without needing to load the textures of the
        package. Useful when migrating data or inspecting the configuration. The caller
        must take ownership of the returned object.

        @param kFilename the filename of the package to load
        @return A new NiSurfacePackage loaded from the file or NULL if the package could not be read
    */
    NiSurfacePackage* ReadPackage(efd::utf8string kFilename);

protected:

    /// Typedef to define the type of event used to notify referencing objects
    typedef NiTerrainEvent<NiSurfacePackage, const efd::utf8string&> EventType;

    /**
        A new event delegate object to store the number of times a delegate like it
        has been added to the owning event. This reference count is used to determine
        when to actually attach new and remove old handlers whilst ensuring that 
        each callback only ever gets called once.
    */
    template <class Sender, class EventArgs, class TargetType> 
    class EventDelegate_PackageReference: 
        public NiTerrainEventHandlerDelegate<Sender, EventArgs, TargetType>
    {
    public:
        /// The type of the callback function on the referrer type
        typedef void (TargetType::*CallbackType)(Sender* pkSender, EventArgs kEventArgs);

        /// Constructor
        EventDelegate_PackageReference(TargetType* pkTarget, CallbackType kCallback);

        /// Attach handler check that implements reference counting on event delegates
        bool CanAttachHandler(const NiTerrainEventHandlerBase<Sender, EventArgs>* kOtherHandler);
        /// Detach handler check that implements reference counting on event delegates
        bool CanDetachHandler();

    protected:

        /// The number of times this delegate has been attached to the event
        efd::UInt32 m_uiReferenceCount;
    };

    /**
        Internal function to register a reference to a package and attach a callback to
        the library to notify the caller when the referenced package changes. The referenced
        package will be queued to load during this function if it is not already available.

        @param kReference The reference to the package being referenced by the caller
        @param pkCallback The event delegate object to use to callback with when the referenced 
            package changes
    */
    void RegisterReference_Internal(const NiTerrainAssetReference& kReference, 
        EventType::HandlerType* pkCallback);

    /**
        Internal function to deregister a reference to a package and detach a callback from
        the library. 

        @param kReference The reference to the package being referenced by the caller
        @param pkCallback The event delegate object that was previously registered with the
            library.
    */
    void DeregisterReference_Internal(const NiTerrainAssetReference& kReference,
        EventType::HandlerType* pkCallback);

    /**
        Remove the given package from the library. 
        NOTE: The user must be sure that this package is no longer being used

        @param pkPackage The package to remove
    */
    void RemovePackage(NiSurfacePackage* pkPackage);

    /**
        Raise the event for all listening objects that the package bearing the given assetID
        has been updated (i.e. It has just loaded or reloaded).
    */
    void RaisePackageUpdated(const efd::utf8string& kAssetID);
    
    /**
        Begin the process of resolving a package reference into a filename and loading
        that package into the library.

        @param kReference The reference to load into memory.
    */
    void RequestLoadPackage(const NiTerrainAssetReference& kReference);

    /**
        Load a package from disk, associate it with an assetID, and add it to the library. 
        This function will begin the process of loading the package and loading it's textures.
        This function is intended to be called after the package's assetID has been resolved to a
        filename via the AssetResolver.

        @param kAssetID The assetID of the package being loaded
        @param kFilename the filename of the package to be loaded.
    */
    void LoadPackage(efd::utf8string kAssetID, efd::utf8string kFilename);

    /**
        Go through the package and attempt to resolve all the textures into filenames.
        This function is called as a part of the loading process and when completed will attempt
        to add the package to the library.
            
        @param pkPackage
    */
    void RequestLoadSurfaces(NiSurfacePackage* pkPackage);

    /**
        Event callback triggered when a packages asset reference has been resolved

        @param pkReference The reference that has been resolved
        @param uiEventID Unused.
    */
    void OnPackageResolved(NiTerrainAssetReference* pkReference, efd::UInt32 uiEventID);

    /**
        Event callback triggered when a texture map asset reference has been resolved.

        @param pkReference The reference that has been resolved
        @param uiEventID Unused.
    */  
    void OnTextureResolved(NiTerrainAssetReference* pkReference, efd::UInt32 uiEventID);

    /**
        Determine if a package is currently attempting to load. 

        @return true if the package is already loading
    */
    bool IsPackageLoading(const efd::utf8string& kAssetID);

    /// Set of all packages in the library
    efd::set<NiSurfacePackagePtr> m_kPackages;

    /// A typedef to define a mapping between a string and a surface package
    typedef efd::map<efd::utf8string, NiSurfacePackage*> PackageMap;
    /// A map of assetID's to the corresponding package
    PackageMap m_kAssetIDToPackage;
    /// A map of filenames to the corresponding package
    PackageMap m_kFilenameToPackage;
    /// A map of package names to the corresponding package
    PackageMap m_kNameToPackage;

    /// A typedef to define a map of AssetID's to Events
    typedef efd::map< efd::utf8string, NiPointer<EventType> > ReferenceMap;
    /// A map of AssetID's to events to allow listeners to be updated when packages change
    ReferenceMap m_kReferences;

    /// A typedef to define a set of AssetReference objects
    typedef efd::set<NiTerrainAssetReferencePtr> PendingPackageSet;
    /// A set of asset references of packages with pending filename lookups
    PendingPackageSet m_kPendingReferences;

    /// A typdef to define a map of asset references to surfaces
    typedef efd::map<NiTerrainAssetReferencePtr, NiSurface*> PendingTextureMap;
    /// A map of asset references to surfaces to store pending texture map lookups
    PendingTextureMap m_kPendingTextureReferences;

    /// The asset resolver to use to resolve assetID's to filenames
    NiTerrainAssetResolverBasePtr m_spAssetResolver;
};
/// Smart pointer typedef
NiSmartPointer(NiTerrainSurfaceLibrary);

#include "NiTerrainSurfaceLibrary.inl"

#endif // NITERRAINSURFACELIBRARY_H
