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

//--------------------------------------------------------------------------------------------------
inline const char* NiSceneGraphUpdateService::GetDisplayName() const
{
    return "NiSceneGraphUpdateService";
}
//--------------------------------------------------------------------------------------------------
inline const char* NiSceneGraphUpdateService::GetStatusMsg() const
{
    return m_acStatusMsg;
}

//--------------------------------------------------------------------------------------------------
inline bool NiSceneGraphUpdateService::IsConnectedToNetwork() const
{
    return m_bConnectedToNetwork;
}

//--------------------------------------------------------------------------------------------------
inline bool NiSceneGraphUpdateService::IsConnectedToEditor() const
{
    return m_bConnectedToEditor;
}

//--------------------------------------------------------------------------------------------------
inline efd::Category NiSceneGraphUpdateService::GetPrivateCategory(const bool bViewerService)
{
    if (bViewerService)
    {
        return efd::Category(efd::UniversalID::ECU_Any, 0, CLASS_ID);
    }
    else
    {
        return efd::Category(efd::UniversalID::ECU_Any, 1, CLASS_ID);
    }
}

//--------------------------------------------------------------------------------------------------
