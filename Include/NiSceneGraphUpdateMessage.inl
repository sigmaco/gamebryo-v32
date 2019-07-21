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
inline efd::IMessagePtr NiSceneGraphUpdateMessage::FactoryMethod()
{
    return EE_NEW NiSceneGraphUpdateMessage();
}

//--------------------------------------------------------------------------------------------------
inline void NiSceneGraphUpdateMessage::AddObjectId(NiSceneGraphUpdate::MessageType eType,
    const NiSceneGraphUpdateObjectId& kObjectId, NiSceneGraphUpdateObject* pkObject)
{
    // Handle a special case for replace and update.
    if (eType != NiSceneGraphUpdate::MESSAGE_REPLACE_OBJECT &&
        eType != NiSceneGraphUpdate::MESSAGE_UPDATE_OBJECT)
    {
        m_kObjects[eType].SetAt(kObjectId, pkObject);
    }
    else
    {
        if (eType == NiSceneGraphUpdate::MESSAGE_UPDATE_OBJECT)
        {
            NiSceneGraphUpdateObjectPtr spOtherObject;
            m_kObjects[NiSceneGraphUpdate::MESSAGE_REPLACE_OBJECT].GetAt(kObjectId, spOtherObject);
            if (!spOtherObject)
            {
                m_kObjects[eType].SetAt(kObjectId, pkObject);
            }
        }
        else
        {
            m_kObjects[NiSceneGraphUpdate::MESSAGE_UPDATE_OBJECT].RemoveAt(kObjectId);
            m_kObjects[eType].SetAt(kObjectId, pkObject);
        }
    }
}

//--------------------------------------------------------------------------------------------------
inline NiUInt32 NiSceneGraphUpdateMessage::GetBufferSize(
    NiSceneGraphUpdate::MessageType eType) const
{
    return m_auiBufferSize[eType];
}

//--------------------------------------------------------------------------------------------------
inline const char* NiSceneGraphUpdateMessage::GetBuffer(NiSceneGraphUpdate::MessageType eType) const
{
    return m_apcBuffer[eType];
}

//--------------------------------------------------------------------------------------------------