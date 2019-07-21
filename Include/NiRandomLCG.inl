// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not 
// be copied or disclosed except in accordance with the terms of that 
// agreement.
//
//      Copyright (c) 1996-2007 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Chapel Hill, North Carolina 27517
// http://www.emergent.net

//---------------------------------------------------------------------------
NiRandomLCG::NiRandomLCG(NiUInt32 uiSeed) : m_uiSeed(uiSeed)
{
}
//---------------------------------------------------------------------------
NiRandomLCG::~NiRandomLCG()
{
}
//---------------------------------------------------------------------------
void NiRandomLCG::SetSeed(NiUInt32 uiSeed)
{
    m_uiSeed = uiSeed;
}
//---------------------------------------------------------------------------
NiUInt32 NiRandomLCG::GetNextReal()
{
	m_uiSeed = m_uiSeed * 214013L + 2531011L;
    return (m_uiSeed >> 16) & NIRANDOMLCG_MAX;
}
//---------------------------------------------------------------------------
float NiRandomLCG::GetNextUnit()
{
    return float(GetNextReal()) / float(NIRANDOMLCG_MAX);
}
//---------------------------------------------------------------------------
float NiRandomLCG::GetNextSymmetricUnit()
{
    return -1.0f + float(GetNextReal() << 1) / float(NIRANDOMLCG_MAX);
}
//---------------------------------------------------------------------------
