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
inline const NiVideoDecoder::CallbackObject*
    NiVideoDecoder::GetCallbackObject() const
{
    return m_pkCallback;
}

//--------------------------------------------------------------------------------------------------
inline void NiVideoDecoder::SetCallbackObject(
    NiVideoDecoder::CallbackObject* pkCallback)
{
    m_pkCallback = pkCallback;
}

//--------------------------------------------------------------------------------------------------
inline NiVideoDecoder::Method NiVideoDecoder::GetDecodeMethod() const
{
    return m_eMethod;
}

//--------------------------------------------------------------------------------------------------
inline NiVideoDecoder::Status NiVideoDecoder::GetStatus() const
{
    return m_eStatus;
}

//--------------------------------------------------------------------------------------------------
inline unsigned int NiVideoDecoder::GetFlags() const
{
    return m_uiFlags;
}

//--------------------------------------------------------------------------------------------------
inline bool NiVideoDecoder::GetFrameSync() const
{
    return m_bFrameSync;
}

//--------------------------------------------------------------------------------------------------
inline void NiVideoDecoder::SetFrameSync(bool bSync)
{
    m_bFrameSync = bSync;
}

//--------------------------------------------------------------------------------------------------
inline const NiColor& NiVideoDecoder::GetBorderColor() const
{
    return m_kBorderColor;
}

//--------------------------------------------------------------------------------------------------
inline void NiVideoDecoder::SetBorderColor(const NiColor& kColor)
{
    m_kBorderColor = kColor;
}

//--------------------------------------------------------------------------------------------------
inline unsigned int NiVideoDecoder::GetCurrentFrame() const
{
    return m_uiCurrentFrame;
}

//--------------------------------------------------------------------------------------------------
inline unsigned int NiVideoDecoder::GetTotalFrames() const
{
    return m_uiTotalFrames;
}

//--------------------------------------------------------------------------------------------------
inline NiVideoDecoder::Error NiVideoDecoder::GetLastError() const
{
    return m_eLastError;
}

//--------------------------------------------------------------------------------------------------
