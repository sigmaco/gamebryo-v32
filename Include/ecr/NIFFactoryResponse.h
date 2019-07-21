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
#ifndef EE_NIFFACTORYRESPONSE_H
#define EE_NIFFACTORYRESPONSE_H

#include <efd/AssetLoadResponse.h>
#include <ecr/ecrMessageIDs.h>

#include <ecr/ecrLibType.h>

#include <NiStream.h>

namespace ecr
{

/**
    The NIFFactoryResponse message is sent by the ecr::NIFFactory, via the
    efd::AssetFactoryManager, when a request for a NIF asset has been completed.

    The message will be send even on failure. However, for some failure modes it is
    necessary to register for efd::AssetLoadResponse messages also.
*/
class EE_ECR_ENTRY NIFFactoryResponse : public efd::AssetLoadResponse
{
    /// @cond EMERGENT_INTERNAL

    EE_DECLARE_CLASS1(
        NIFFactoryResponse,
        efd::kMSGID_NIFFactoryResponse,
        efd::AssetLoadResponse);
    /// @endcond

public:
    /// @name Constructors and Destructors
    //@{

    /// Default constructor
    inline NIFFactoryResponse();

    /**
        Constructor requires the URN and the category on which to send the response.

        The parameter set match those of efd::AssetLoadResponse, with the addition of the return
        NiStream object. The message object takes ownership of the stream and will delete it.
    */
    inline NIFFactoryResponse(
        const efd::utf8string& urn,
        const efd::Category& responseCategory,
        const efd::AssetLoadResponse::AssetLoadResult result,
        const efd::utf8string& assetPath = "",
        bool isReload = false,
        NiStream* pStream = NULL);

    /// Destructor deletes the internal stream object.
    inline virtual ~NIFFactoryResponse();

    //@}

    /// @name Access to Loaded Data
    //@{

    /// Get the number of top level objects in the loaded stream.
    inline efd::UInt32 GetObjectCount() const;

    /// Get the top level object loaded at the given index.
    ///
    /// The index must be less than the value returned by GetObjectCount.
    inline NiObject* GetObjectAt(efd::UInt32 index) const;

    //@}

protected:
    NiStream* m_pStream;
};

typedef efd::SmartPointer<NIFFactoryResponse> NIFFactoryResponsePtr;

}// end namespace ecr

#include "NIFFactoryResponse.inl"

#endif // EE_NIFFACTORYRESPONSE_H
