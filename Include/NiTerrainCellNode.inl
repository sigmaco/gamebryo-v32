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

//---------------------------------------------------------------------------
inline const NiTerrainCell* NiTerrainCellNode::GetChildAt(
    NiUInt32 uiIndex) const
{
    return m_apkChildren[uiIndex];
}
//---------------------------------------------------------------------------
inline NiTerrainCell* NiTerrainCellNode::GetChildAt(NiUInt32 uiIndex)
{
    return m_apkChildren[uiIndex];
}
//---------------------------------------------------------------------------
inline void NiTerrainCellNode::SetChildAt(NiUInt32 uiIndex, 
    NiTerrainCell* pkChild)
{
    m_apkChildren[uiIndex] = pkChild;
    if (pkChild)
    {
        pkChild->SetParent(this);
        AttachChild(pkChild);
    }    
}
//---------------------------------------------------------------------------
