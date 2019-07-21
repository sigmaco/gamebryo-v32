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

namespace efd
{

//------------------------------------------------------------------------------------------------
template< typename T >
T* IAssetResponseData::GetResponseAs() const
{
    return EE_DYNAMIC_CAST(T, m_spResponse);
}

//------------------------------------------------------------------------------------------------
template<typename T>
efd::IAssetFactory::LoadStatus BaseAssetFactory::GetResponseDataAs(
    const efd::AssetLoadRequest* pRequest,
    T*& o_pResponseData)
{
    efd::IAssetResponseData* data = 0;
    efd::IAssetFactory::LoadStatus status = GetResponseData(pRequest, data);

    o_pResponseData = EE_DYNAMIC_CAST(T, data);

    return status;
}

//------------------------------------------------------------------------------------------------
template<typename T>
efd::IAssetFactory::LoadStatus BaseAssetFactory::GetResponseDataAs(
    const efd::AssetLoadRequest* pRequest,
    efd::SmartPointer<T>& o_spResponseData)
{
    efd::IAssetResponseData* data = 0;
    efd::IAssetFactory::LoadStatus status = GetResponseData(pRequest, data);

    o_spResponseData = EE_DYNAMIC_CAST(T, data);

    return status;
}

//------------------------------------------------------------------------------------------------
} // end namespace efd
