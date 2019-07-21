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
#ifndef EE_GENERICASSETFACTORY_H
#define EE_GENERICASSETFACTORY_H

#include <efd/efdLibType.h>
#include <efd/efdClassIDs.h>
#include <efd/CriticalSection.h>

#include <efd/BaseAssetFactory.h>

namespace efd
{

class GenericAssetLoadResponse;

/*
    If you change anything in this code, please check for corresponding changes to the
    Programmer's Guide documentation for adding a new asset type.
*/


/**
    The GenericAssetFactory extends the efd::BaseAssetFactory and is used for loading data from
    a file directly into a memory buffer.

    Optionally, an additional byte containing '\\0' may be appended to the data from the asset,
    allowing it to be interpreted as a string. This extra byte will be included in the data size
    in the response.
*/
class EE_EFD_ENTRY GenericAssetFactory : public efd::BaseAssetFactory
{
    /// @cond EMERGENT_INTERNAL
    EE_DECLARE_CLASS1(
        GenericAssetFactory,
        efd::kCLASSID_GenericAssetFactory,
        efd::BaseAssetFactory);
    EE_DECLARE_CONCRETE_REFCOUNT;

    /// @endcond

public:
    /// @name Construction and destruction
    //@{

    /**
        Constructor.

        @param appendNULL When true, an additional byte containing '\\0' will be appended
            to the data from the asset.
        @param bytesPerTick The maximum number of bytes to read from the file in one tick.
            Modify this parameter to control the amount of time a read by this factory may
            block preventing other work. The default is just under 100MB.
    */
    GenericAssetFactory(const bool appendNULL = false, const UInt32 bytesPerTick = 0x4FFFFFF);

    /// Virtual destructor.
    virtual ~GenericAssetFactory();

    //@}


    /// @name Generic Data Loading
    //@{

    /**
        The loader for generic data.

        The returned message is of type efd::GenericLoadResponse.
    */
    virtual LoadStatus LoadAsset(
        AssetFactoryManager* pFactoryManager,
        const AssetLoadRequest* pRequest,
        SmartPointer<AssetLoadResponse>& pResponse);

    //@}


    /// @name Option Get/Set
    //@{

    /// Determine if a NULL is appended to loaded data.
    inline bool GetAppendNULL() const;

    // Do not implement SetAppendNULL because it would not be thread safe.

    /// Thread status description.
    ///
    /// This loader is thread safe for foreground or background use.
    inline ThreadSafetyDescription GetThreadSafety() const;

    //@}

protected:
    /// Internal helper class to hold response data while waiting to locate assets.
    class ResponseData : public efd::IAssetResponseData
    {
        /// @cond EMERGENT_INTERNAL
        EE_DECLARE_CLASS1(
            ResponseData,
            efd::kCLASSID_GenericAssetFactoryData,
            efd::IAssetResponseData);
        EE_DECLARE_CONCRETE_ATOMIC_REFCOUNT;
        /// @endcond

    public:

        // The file currently open for this load
        File* m_pFile;

        // The buffer for this load
        char* m_pBuffer;

        // Bytes read so far
        UInt32 m_bytesRead;
    };

    /// A SmartPointer for the GenericAssetFactory::ResponseData class
    typedef efd::SmartPointer<ResponseData> ResponseDataPtr;

    // Functions for managing the map of response data
    // Gets an existing response data or creates a new one
    ResponseDataPtr HandleNewRequest(const AssetLoadRequest* pRequest);

    bool m_appendNULL;
    UInt32 m_bytesPerTick;
};

/// A SmartPointer for the GenericAssetFactory class
typedef efd::SmartPointer<GenericAssetFactory> GenericAssetFactoryPtr;

} // namespace efd

#include <efd/GenericAssetFactory.inl>

#endif // EE_GENERICASSETFACTORY_H
