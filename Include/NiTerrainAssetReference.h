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
#ifndef NITERRAINASSETREFERENCE_H
#define NITERRAINASSETREFERENCE_H

#include <NiMemManager.h>
#include <NiRefObject.h>
#include <NiSmartPointer.h>
#include <NiUniversalTypes.h>
#include <efd/utf8string.h>
#include <efd/TinyXML.h>
#include <efd/PathUtils.h>

#include "NiTerrainLibType.h"
#include "NiTerrainEvents.h"

class NiTerrainAssetReference;

/**
    This class is a base class to implement the concept of a Terrain asset resolver from
    within the core runtime libraries. An implementer may derive from this class to create
    a new mechanism for resolving terrain asset references into filenames. A default implementation
    is provided to allow pre-stored file locations within the reference to be used as the file 
    location. For an implementation using the AssetLocatorService, please see the implementation
    provided in egmTerrain::TerrainService::AssetResolver.
*/
class NITERRAIN_ENTRY NiTerrainAssetResolverBase : public NiRefObject
{

public:
    /// Destructor
    virtual ~NiTerrainAssetResolverBase();

    /**
        Request that a particular asset reference be resolved. 
        Upon completion of the resolution, the reference's SetResolvedLocation function
        will be called with the resolved location of the asset. If the resolution failed, 
        the reference will be given an empty string as the resolved location. If the reference
        has already been marked as resolved then the resolved event on the reference will be
        fired immediately without attempting a second resolve. 

        @param pkReference The reference to resolve.
    */
    void ResolveAssetLocation(NiTerrainAssetReference* pkReference);

protected:

    /**
        An internal function used to process the resolution of a reference into a file location.
        Sub classes of NiTerrainAssetResolverBase should implement this function to provide
        their own mechanism for resolving assetID's to filenames. 

        @param pkReference The reference to resolve.
    */
    virtual void InternalResolveReference(NiTerrainAssetReference* pkReference) = 0;
};
/// Smartpointer typedef for NiTerrainAssetResolverBase
NiSmartPointer(NiTerrainAssetResolverBase);

/**
    This class is an implementation of the NiTerrainAssetResolverBase class and is 
    used under CoreRuntime only applications that do not support the GameFramework. 
    This class immediately returns all resolution requests and report that the resolved
    asset location is the same as the asset reference's last known location.
*/
class NITERRAIN_ENTRY NiTerrainAssetResolverDefault : public NiTerrainAssetResolverBase
{
protected:
    /// @see NiTerrainAssetResolverBase
    virtual void InternalResolveReference(NiTerrainAssetReference* pkReference);
};

/**
    This class and it's derivatives are used to represent references to other assets from an
    initial asset. Supporting loading/saving to XML format, and resolution through an appropriate
    NiTerrainAssetResolver class. 
*/
class NITERRAIN_ENTRY NiTerrainAssetReference: public NiRefObject, 
    public NiTerrainObservable<NiTerrainAssetReference>
{
public:
    /// Constructor
    NiTerrainAssetReference();
    /// Destructor
    virtual ~NiTerrainAssetReference();
    /// Assignment operator
    NiTerrainAssetReference& operator=(const NiTerrainAssetReference& kOther);

    /**
        Get the location that has been resolved by a NiTerrainAssetResolver class for this 
        reference. If a resolution has not been attempted or has failed, then an empty string
        will be returned. 
    */
    const efd::utf8string& GetResolvedLocation() const;

    /**
        Get the expected location of the asset based on the relative path that was stored and 
        the location of the referring asset. 
    */
    efd::utf8string GetStoredLocation() const;

    /**
        Get the asset ID of the referenced asset
    */
    const efd::utf8string& GetAssetID() const;

    /**
        Get the referring asset's location
    */
    const efd::utf8string& GetReferingAssetLocation() const;

    /**
        Get the relative path that is stored in the reference
    */
    const efd::utf8string& GetRelativeAssetLocation() const;

    /**
        Get the last known relative location. If the asset has been resolved, then this
        will be the relative path to that resolved asset.
    */
    efd::utf8string GetLastRelativeLocation() const;

    /**
        Query the reference to find out if it has been resolved. Note that this does not 
        indicate if the resolution was successful.

        @return True if a resolution has been completed on this reference
    */
    bool IsResolved() const;

    /**
        Mark this reference as resolved.
        May trigger further events waiting on the resolution of this reference.

        @param bResolved True if a resolution of the asset has been completed.
    */
    void MarkResolved(bool bResolved);

    /**
        Set the resolved location of the reference.

        @param kLocation The resolved absolute filepath of the asset
    */
    void SetResolvedLocation(const efd::utf8string& kLocation);

    /**
        Set the location of the referring asset.

        @param kLocation The absolute filepath of the file that stored this reference.
    */
    void SetReferringAssetLocation(const efd::utf8string& kLocation);

    /**
        Set the relative path of the asset reference

        @param kLocation The relative path to the asset based on the refering asset's location
    */
    void SetRelativeAssetLocation(const efd::utf8string& kLocation);

    /**
        Set the AssetID of the referenced asset

        @param kAssetID The asset ID of the asset being referenced.
    */
    void SetAssetID(const efd::utf8string& kAssetID);

private:
    /**
        Private copy constructor to disable the use of stack variables of this object. 
        The NiRefObject interface does not support copying of objects in that way. 
    */
    NiTerrainAssetReference(const NiTerrainAssetReference&);
    
    /// Function to raise the reference updated event
    void OnResolved();

    /// The location of the asset that is referring to this asset
    efd::utf8string m_kReferingAssetLocation;
    /// The relative path stored inside the referring asset
    efd::utf8string m_kRelativeAssetLocation;
    /// The asset ID stored inside the referring asset
    efd::utf8string m_kAssetID;
    /// The location that has been resolved for the referring asset
    efd::utf8string m_kResolvedLocation;
    /// Has the asset been resolved (or attempted to be resolved)
    efd::Bool m_bIsResolved;
};
/// Smartpointer typedef for NiTerrainAssetReference
NiSmartPointer(NiTerrainAssetReference);

#include "NiTerrainAssetReference.inl"

#endif // NITERRAINASSETREFERENCE_H
