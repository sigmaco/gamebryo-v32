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
inline efd::Bool AssetConfigService::GetPreloadGraphs() const
{
    return m_preloadGraphs;
}

//------------------------------------------------------------------------------------------------
inline const efd::utf8string& AssetConfigService::GetAssetWebRoot() const
{
    return m_assetWebRoot;
}

//------------------------------------------------------------------------------------------------
} // end namespace efd
