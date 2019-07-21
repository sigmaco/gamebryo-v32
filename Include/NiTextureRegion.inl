// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not 
// be copied or disclosed except in accordance with the terms of that 
// agreement.
//
//      Copyright (c) 1996-2008 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Chapel Hill, North Carolina 27517
// http://www.emergent.net

inline NiTextureRegion::NiTextureRegion() :
    m_kTextureOffset(0.0f, 0.0f),
    m_fTextureScale(1.0f)
{
}
//---------------------------------------------------------------------------
inline NiTextureRegion::~NiTextureRegion()
{
}
//---------------------------------------------------------------------------
inline void NiTextureRegion::InitializeTextureRegion(NiTexture* pkTexture, 
    NiPoint2 kOffset, float fScale)
{
    m_spTexture = pkTexture;
    m_fTextureScale = fScale;
    m_kTextureOffset = kOffset;
}
//---------------------------------------------------------------------------
inline void NiTextureRegion::SetTexture(NiTexture* pkTexture)
{
    if (m_spTexture)
        m_spTexture = 0;

    m_spTexture = pkTexture;
}
//---------------------------------------------------------------------------
inline void NiTextureRegion::SetRegion(NiPoint2 kOffset, float fTextureScale)
{
    m_fTextureScale = fTextureScale;
    m_kTextureOffset = kOffset;
}
//---------------------------------------------------------------------------
inline NiPoint2 NiTextureRegion::GetTextureOffset() const
{
    return m_kTextureOffset;
}
//---------------------------------------------------------------------------
inline float NiTextureRegion::GetTextureScale() const
{
    return m_fTextureScale;
}
//---------------------------------------------------------------------------
inline NiTexture* NiTextureRegion::GetTexture() const
{
    return m_spTexture;
}
//---------------------------------------------------------------------------
inline NiIndex NiTextureRegion::GetStartPixelIndex() const
{    
    EE_ASSERT(m_spTexture);
    NiUInt32 uiTexWidth = m_spTexture->GetWidth();

    // Calculate the starting pixel
    NiIndex kStartPoint; 
    kStartPoint.x = (NiUInt32)(m_kTextureOffset.x * uiTexWidth);
    kStartPoint.y = (NiUInt32)(m_kTextureOffset.y * uiTexWidth);

    return kStartPoint;
}   
//---------------------------------------------------------------------------
inline NiIndex NiTextureRegion::GetEndPixelIndex() const
{
    EE_ASSERT(m_spTexture);
    NiUInt32 uiTexWidth = m_spTexture->GetWidth();
    float fCellTexRange = 1.0f / m_fTextureScale;

    // Calculate the end of the pixels used in this region
    NiIndex kEndPoint = GetStartPixelIndex(); 
    // The 0.5f here performs a rounding to the nearest integer
    kEndPoint.x += (NiUInt32)(fCellTexRange * uiTexWidth + 0.5f);
    kEndPoint.y += (NiUInt32)(fCellTexRange * uiTexWidth + 0.5f);

    return kEndPoint;
}
//---------------------------------------------------------------------------